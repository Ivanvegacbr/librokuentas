/* ----------------------------------------------------------------------------------
    KEME-Contabilidad 2.1; aplicación para llevar contabilidades

    Copyright (C) 2007  José Manuel Díez Botella

    Este programa es software libre: usted puede redistribuirlo y/o modificarlo 
    bajo los términos de la Licencia Pública General GNU publicada 
    por la Fundación para el Software Libre, ya sea la versión 3 
    de la Licencia, o (a su elección) cualquier versión posterior.

    Este programa se distribuye con la esperanza de que sea útil, pero 
    SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
    MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
    Consulte los detalles de la Licencia Pública General GNU para obtener 
    una información más detallada. 

    Debería haber recibido una copia de la Licencia Pública General GNU 
    junto a este programa. 
    En caso contrario, consulte <http://www.gnu.org/licenses/>.
  ----------------------------------------------------------------------------------*/

#include "bss.h"
#include "basedatos.h"
#include "funciones.h"
#include "pidenombre.h"
#include "pastel.h"
#include "interfechas.h"

bss::bss() : QDialog() {
    ui.setupUi(this);
    comadecimal=haycomadecimal();
    decimales=haydecimales();
	
    //rellenar intervalos de cuentas
    ui.desdelineEdit->setText("0");
    QStringList conts;
    conts << tr("Gastos") << tr("Ingresos") << tr("Gastos y ingresos");
    conts << tr("Otras cuentas") << tr("Todas");
    ui.intervaloComboBox->addItems(conts);
    ui.intervaloComboBox->setCurrentIndex(4);
    QString cadena;
    for (int veces=0;veces<anchocuentas();veces++) cadena=cadena+"9";
    ui.hastalineEdit->setText(cadena);
    
    fichero=tr("bss");
    
    ejercicioCambiado(ui.datas->ejercicio());
    
    
    QStringList columnas;
    columnas << tr("CUENTA") << tr("DESCRIPCIÓN") << tr("SUMA DEBE");
    columnas << tr("SUMA HABER") << tr("SALDO") ;

    ui.table->setHorizontalHeaderLabels(columnas);
    
    ui.table->setAlternatingRowColors(true);
    ui.table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.table->setEditTriggers ( QAbstractItemView::NoEditTriggers );

    ui.diariostableWidget->verticalHeader()->hide();
    ui.diariostableWidget->horizontalHeader()->hide();
    ui.diariostableWidget->setColumnWidth(0,150);

    QCheckBox *checkbox0 = new QCheckBox(diario_apertura(), this);
    ui.diariostableWidget->insertRow(0);
    ui.diariostableWidget->setCellWidget ( 0, 0, checkbox0 );
    connect((QCheckBox*)ui.diariostableWidget->cellWidget(0,0),
         SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
    
    QCheckBox *checkbox1 = new QCheckBox(diario_no_asignado(), this);
    ui.diariostableWidget->insertRow(1);
    ui.diariostableWidget->setCellWidget ( 1, 0, checkbox1 );
    ((QCheckBox*)ui.diariostableWidget->cellWidget(1,0))->setCheckState(Qt::Checked);
    connect((QCheckBox*)ui.diariostableWidget->cellWidget(1,0),
         SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
    
    QCheckBox *checkbox2 = new QCheckBox(diario_regularizacion(), this);
    ui.diariostableWidget->insertRow(2);
    ui.diariostableWidget->setCellWidget ( 2, 0, checkbox2 );
    connect((QCheckBox*)ui.diariostableWidget->cellWidget(2,0),
         SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
    numdiarios=3;
    QString cadena2="select codigo,descripcion from diarios order by codigo";
    //rellenar diarios
    QSqlQuery query = ejecutarSQL(cadena2);
    while (query.next())
       {
           QCheckBox *checkbox = new QCheckBox(query.value(1).toString(), this);
           ui.diariostableWidget->insertRow(numdiarios);
           ui.diariostableWidget->setCellWidget ( numdiarios, 0, checkbox );
           ui.diariostableWidget->cellWidget ( numdiarios, 0)->setToolTip(query.value(0).toString());
           connect((QCheckBox*)ui.diariostableWidget->cellWidget(numdiarios,0),
             SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
	   numdiarios++;

       }
	ui.periodosTableWidget->verticalHeader()->hide();
    ui.periodosTableWidget->horizontalHeader()->hide();
    ui.periodosTableWidget->setColumnWidth(0,110);
    ui.periodosTableWidget->hideColumn(1);
    ui.periodosTableWidget->hideColumn(2);
    ui.datas->setCheckable(false);
    ui.datas->setFlat(true);
    ui.datas->setTitle("");

    //if (!conanalitica()) ui.analiticagroupBox->setEnabled(false);

    connect(ui.actualizapushButton,SIGNAL(clicked()),this,SLOT(actualizar()));
    connect(ui.conmovcheckBox,SIGNAL(stateChanged(int)),this,SLOT(varsinmovs()));
    connect(ui.fichpushButton,SIGNAL(clicked()),this,SLOT(txtexport()));
    connect(ui.ImprimirpushButton,SIGNAL(clicked()),this,SLOT(imprimir()));
    connect(ui.gentexpushButton,SIGNAL(clicked()),this,SLOT(gentex()));
connect(ui.graficoButton,SIGNAL(clicked()),this,SLOT(verGrafico()));

  //connect(ui.cilineEdit,SIGNAL(textChanged(QString)),this,SLOT(fijadescripciones()));
  //connect(ui.buscapushButton,SIGNAL(clicked()),this,SLOT(buscapulsado()));

  connect(ui.cuentascheckBox,SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
  connect(ui.gruposcheckBox,SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
  connect(ui.subcuentascheckBox,SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
  connect(ui.subgruposcheckBox,SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
  connect(ui.radioReal,SIGNAL(toggled(bool)),this,SLOT(activaactualiza()));
  // connect(ui.radioVirtual,SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
  // connect(ui.regularizacioncheckBox,SIGNAL(stateChanged(int)),this,SLOT(activaactualiza()));
  connect(ui.datas,SIGNAL(ejercicioActivado(QString)),this,SLOT(ejercicioCambiado(QString)));
  
  connect(ui.intervaloComboBox,SIGNAL(activated(int)),this,SLOT(intervaloCambiado( int )));
 
  connect(ui.datas,SIGNAL(fechaCambiada(Fecha)),this,SLOT(activaactualiza()));
  //connect(ui.hastadateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(activaactualiza()));

  connect(ui.desdelineEdit,SIGNAL(textChanged(QString)),this,SLOT(activaactualiza()));
  connect(ui.hastalineEdit,SIGNAL(textChanged(QString)),this,SLOT(activaactualiza()));
 }

void bss::intervaloCambiado( int index )
{
	QString desde,hasta,nueves;
    int cont;
    for (int veces=1;veces<anchocuentas();veces++) nueves=nueves+"9";
		
    switch (index)
	{
		case 0:
			desde = grupoGastos();
			hasta = desde;
			break;
		case 1:
			desde = grupoIngresos();
			hasta = desde;
			break;
		case 2:
			desde = grupoGastos();
			hasta = grupoIngresos();
			break;
		case 3:
			desde = "0";
			hasta = grupoGastos();
			cont = hasta.toInt();
			hasta.setNum(cont-1);
			break;
		case 4:
			desde = "0";
			hasta = "9";
			break;
		default:
			desde = "0";
			hasta = "9";
			break;
	}
	//desde.append(zeros);
	hasta.append(nueves);
	ui.desdelineEdit->setText(desde);
	ui.hastalineEdit->setText(hasta);
}

void bss::ejercicioCambiado(QString ejercicio)
{
	/*QString ejercicio;
    ejercicio=ui.ejercicioComboBox->currentText();
    if (ejercicio.length()>0)
    {
    	ui.desdedateEdit->setDate(inicioejercicio(ejercicio));
    	ui.hastadateEdit->setDate(finejercicio(ejercicio));
    }
    else
    {
        ui.desdedateEdit->setDate(QDate::currentDate());
        ui.hastadateEdit->setDate(QDate::currentDate());
    }*/
    ui.periodosTableWidget->clearContents();
    ui.periodosTableWidget->setRowCount(0);
    numPeriodos=0;
	QString cadena2="select codigo,inicio,fin from periodos";
	cadena2+=" WHERE ejercicio='";
	cadena2+=ejercicio;
	cadena2+="'";
	cadena2+=" order by inicio";
    //rellenar periodos
    QSqlQuery query = ejecutarSQL(cadena2);
    while (query.next())
       {
         QCheckBox *checkbox = new QCheckBox(query.value(0).toString(), this);
         ui.periodosTableWidget->insertRow(numPeriodos);
         ui.periodosTableWidget->setCellWidget ( numPeriodos, 0, checkbox );
         ((QCheckBox*)ui.periodosTableWidget->cellWidget(numPeriodos,0))->setCheckState(Qt::Checked);
         connect((QCheckBox*)ui.periodosTableWidget->cellWidget(numPeriodos,0),
           SIGNAL(stateChanged(int)),this,SLOT(fijaFechas()));
         QTableWidgetItem *newItem = new QTableWidgetItem(query.value(1).toString());
         ui.periodosTableWidget->setItem ( numPeriodos, 1, newItem );
         QTableWidgetItem *newItem2 = new QTableWidgetItem(query.value(2).toString());
         ui.periodosTableWidget->setItem ( numPeriodos, 2, newItem2 );
	     numPeriodos++;

       }
}

void bss::actualizar()
{
   if (!ui.actualizapushButton->isEnabled()) return;
   ui.table->setRowCount(0);
   bool vacio=TRUE;
   int selecciones = 0;
   QString cadena="select codigo,descripcion from plancontable where ";
   QString filtro,cadnum;
   filtro="(";
   if (ui.gruposcheckBox->isChecked()) { filtro+="char_length(codigo)=1"; vacio=false; selecciones++;}
   if (ui.subgruposcheckBox->isChecked()) 
       {
         if (filtro.length()>1) filtro+=" OR ";
         filtro+="char_length(codigo)=2";
         vacio=FALSE;
         selecciones++;
       }
   if (ui.cuentascheckBox->isChecked())
      {
        if (filtro.length()>1) filtro+=" OR ";
         filtro+="(char_length(codigo)>2 and char_length(codigo)<";
         filtro+=  cadnum.setNum(uint(anchocuentas()));
         filtro+= ")" ;
         vacio=FALSE;
         selecciones++;
      }
   if (ui.subcuentascheckBox->isChecked()) 
      {
        if (filtro.length()>1) filtro+=" OR ";
        filtro+="char_length(codigo)=";
        filtro+=  cadnum.setNum(uint(anchocuentas()));
         vacio=FALSE;
         selecciones++;
      }
   
   if (vacio)
      {
         return;
      }
   filtro+=")";
   // añadimos en filtro intervalo de cuentas
   //if (ui.cuentasgroupBox->isChecked())
     //  {
          ui.desdelineEdit->setText(expandepunto(ui.desdelineEdit->text(),anchocuentas()));
		  ui.hastalineEdit->setText(expandepunto(ui.hastalineEdit->text(),anchocuentas()));
          filtro+=" AND (codigo>='";
          filtro+=ui.desdelineEdit->text();
          filtro+="' and codigo<='";
          filtro+=ui.hastalineEdit->text();
          filtro+="')";
       //}
   cadena+=filtro;
  cadena+=" ORDER by codigo";
  //qdebug() << tr("BSS") << cadena;
  int filas=0;
  QString cadconsulta="select count(codigo) from plancontable where ";
  cadconsulta+=filtro;
  QSqlQuery consulta = ejecutarSQL(cadconsulta);
   if (consulta.next())
      {
          ui.table->setRowCount(consulta.value(0).toInt());
          filas=consulta.value(0).toInt();
          
	          for (int veces=0; veces<filas; veces++)
		  	  {
	
	           for (int veces2=0;veces2<5;veces2++)
	                {
	                 QTableWidgetItem *newItem = new QTableWidgetItem("");
	                 if (veces2>=2 && veces2<=4) newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
	                 ui.table->setItem(veces,veces2,newItem);
	                }
	
		  	  }
	  	  
      }
   consulta = ejecutarSQL(cadena);
   int fila=0;
   while (consulta.next())
      {
        ui.table->item(fila,0)->setText(consulta.value(0).toString());
        ui.table->item(fila,1)->setText(consulta.value(1).toString());
        fila++;
      }
  ui.progressBar->setMaximum(filas-1);
  
  // averiguamos información de saldos y sumas para subcuentas
   for (int veces=0;veces<filas;veces++)
   {
      if (ui.table->item(veces,0)->text().length()==anchocuentas())
      {
        ui.table->item(veces,2)->setText(sumadh(true,true,
                                          ui.table->item(veces,0)->text(),
                                          ui.datas->fecha(interFechas::inicial),
                                          ui.datas->fecha(interFechas::final)));
        ui.table->item(veces,3)->setText(sumadh(true,false,
                                     ui.table->item(veces,0)->text(),
                                     ui.datas->fecha(interFechas::inicial),
                                     ui.datas->fecha(interFechas::final)));
        ui.progressBar->setValue(veces+1);
      }
   }
  // cargamos información de cuentas,subgrupos y grupos si hace falta
   // -----------------------------------------------------------------------------------
   // aquí nos hemos quedado
   // -----------------------------------------------------------------------------------
   
   if (!ui.subcuentascheckBox->isChecked())
          for (int veces=0;veces<filas;veces++)
	      {
            ui.table->item(veces,2)->setText(sumadh(false,true,ui.table->item(veces,0)->text(),
                        ui.datas->fecha(interFechas::inicial),ui.datas->fecha(interFechas::final)));
            ui.table->item(veces,3)->setText(sumadh(false,false,ui.table->item(veces,0)->text(),
                        ui.datas->fecha(interFechas::inicial),ui.datas->fecha(interFechas::final)));
            ui.progressBar->setValue(veces+1);
          }
   // llenamos celdas en blanco sólo para el caso de que hayan subcuentas
   double suma=0;
   for (int columna=2;columna<4;columna++)
	   {   
	     for (int veces=0;veces<filas;veces++)
	     {
	         if (ui.table->item(veces,columna)->text().length()==0)
		     {
		       suma=0;
		       for (int veces2=0;veces2<filas;veces2++)
		       {
		         if (ui.table->item(veces2,columna)->text().length()>0)
			     if (ui.table->item(veces2,0)->text().startsWith(ui.table->item(veces,0)->text()) &&
				     ui.table->item(veces2,0)->text().length()==anchocuentas())
			             suma+=convapunto(ui.table->item(veces2,columna)->text()).toDouble();
		       }
		       ui.table->item(veces,columna)->setText(formateanumero(suma,comadecimal,decimales));
		     }
	     }
	     ui.progressBar->reset();
	   }
 
 
 // queda calcular la diferencia entre sumas para calcular los saldos
 double saldo=0;
 double ingr=0;
 double gast=0;
 double gen=0;
 
 for (int veces=0;veces<filas;veces++)
     {
       saldo=saldocuentaendiario(ui.table->item(veces,0)->text());
       if (selecciones == 1){
        if (esCuentadeGenero(ui.table->item(veces,0)->text()))
        	gen+=convapunto(ui.table->item(veces,2)->text()).toDouble();
        if (escuentadegasto(ui.table->item(veces,0)->text()))
        	gast+=convapunto(ui.table->item(veces,2)->text()).toDouble();
        if (escuentadeingreso(ui.table->item(veces,0)->text()))
        	ingr+=convapunto(ui.table->item(veces,3)->text()).toDouble();
      	}
       ui.table->item(veces,4)->setText(formateanumero(saldo,comadecimal,decimales));
       ui.progressBar->setValue(veces+1);
     }
 varsinmovs();
 ui.progressBar->reset();
 ui.table->resizeColumnsToContents();
 ui.lcds->pasaValores(gen,gast,ingr,decimales);
 ui.actualizapushButton->setEnabled(false);
}


QString bss::sumadh(bool subcuenta, bool debe, QString codigo, QDate desde, QDate hasta)
{
  QString cadena;
  if (debe) cadena="select sum(debe) from diario" ;
  else cadena="select sum(haber) from diario" ;
  if (subcuenta)
  {
     cadena+=" where cuenta='";
     cadena+=codigo;
     cadena+="'";
  }else
   {
	  cadena+=" where position('";
	  cadena+=codigo;
	  cadena+="' in cuenta)=1";
   }
  QString filtro2 = "";
  for (int veces=0;veces<numdiarios;veces++)
      {
        if (((QCheckBox*)ui.diariostableWidget->cellWidget(veces,0))->isChecked())
           {
            if (filtro2.length()>0) filtro2+=" or ";
            if (((QCheckBox*)ui.diariostableWidget->cellWidget(veces,0))->text()==diario_no_asignado())
               {
                 filtro2+="diario=''";
               } else
                 {
                  filtro2+="diario='";
                  filtro2+=((QCheckBox*)ui.diariostableWidget->cellWidget(veces,0))->text();
                  filtro2+="'";
                 }
           }
      }
  //if (DEBUG) QMessageBox::warning( this, tr("BSS"),filtro2);
  
  if (filtro2.length()==0) return "0";
  cadena+=" and (";
  cadena+=filtro2;
  cadena+=")";
  // añadimos el filtro de semana
  if (ui.datas->semana().length()>0 && cadnumvalido(ui.datas->semana()) 
   	   && ui.radioVirtual->isChecked())
  {
   		cadena+=" AND asiento='";
   		cadena+=ui.datas->semana();
   		cadena+="'";
  }

  //filtro fechas
  if (ui.radioReal->isChecked() && ui.datas->semana().length()>0 && cadnumvalido(ui.datas->semana()))
  {
  	//corregir fecha inicial
  	for (int i=1 ;desde.weekNumber() < ui.datas->semana().toInt();i++)
  	{
  		desde = desde.addDays(i);
 	}
  	ui.datas->setFecha(interFechas::inicial,desde);
  }
  if (ui.radioVirtual->isChecked() || !debe){
  	cadena+=" and (fecha>='";
  	cadena+=desde.toString("yyyy.MM.dd");
  	cadena+="' and fecha<='";
  	cadena+=hasta.toString("yyyy.MM.dd");
  	cadena+="')";
  }else{
  	cadena+=" and (ci BETWEEN cast('";
  	cadena+=desde.toString("yyyy.MM.dd");
  	cadena+="' as date) and cast('";
  	cadena+=hasta.toString("yyyy.MM.dd");
  	cadena+="' as date))";
 	}
  
   //QMessageBox::warning( this, tr("BSS"),cadena);
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
         double valor=query.value(0).toDouble();
         return formateanumero(valor,comadecimal,decimales);
     }
  return "0";
}





void bss::varsinmovs()
{
 // eliminamos, si procede las cuentas sin movimientos
 if  (ui.conmovcheckBox->isChecked())
    {
       int veces=0;
       while (veces<ui.table->rowCount())
          {
	    double sumadebe=convapunto(ui.table->item(veces,2)->text()).toDouble();
	    double sumahaber=convapunto(ui.table->item(veces,3)->text()).toDouble();
	    if ((sumadebe>-0.001 && sumadebe<0.001) && (sumahaber>-0.001 && sumahaber<0.001))
		ui.table->setRowHidden ( veces, true );
            veces++;
          }
    }
      else
             {
               int veces=0;
               while (veces<ui.table->rowCount())
                {
	         double sumadebe=convapunto(ui.table->item(veces,2)->text()).toDouble();
	         double sumahaber=convapunto(ui.table->item(veces,3)->text()).toDouble();
	         if ((sumadebe>-0.001 && sumadebe<0.001) && (sumahaber>-0.001 && sumahaber<0.001))
		   ui.table->setRowHidden(veces,false);
                 veces++;	    
                }
            }

}




// ------------------------------------------------------------------------------------------------------


void bss::txtexport()
{
    if (ui.table->rowCount()==0)
       QMessageBox::warning( this, tr("Balance de sumas y saldos"),tr("No hay registros, operación cancelada"));
   QClipboard *cb = QApplication::clipboard();
   QString global;
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero=qfichero+tr("bss.txt");
    QFile fichero(QFile::encodeName(qfichero));
    if (! fichero.open( QIODevice::WriteOnly ) ) return;
    QTextStream stream( &fichero );
    stream.setCodec("UTF-8");

    // ---------------------------------------------------------------------------------------------
    /*if (ui.analiticagroupBox->isChecked() && ui.cilineEdit->text().length()>0)
        {
         global+=tr("CÓDIGO DE IMPUTACIÓN\t");
         global+=ui.cilineEdit->text();
         global+="\n";
         stream << tr("CÓDIGO DE IMPUTACIÓN\t");
         stream << ui.cilineEdit->text();
         stream << "\n";
         QString codigo=ui.cilineEdit->text();
         QString cadena,descripcion;
         QString qnivel=0;


         if (codigo.startsWith("???"))
            {
             global+= tr("CUALQUIERA");
             stream << tr("CUALQUIERA");
            }
         else
           {
            bool encontrada=buscaci(codigo.left(3),&descripcion,&qnivel);
            if (encontrada && qnivel.toInt()==1)
               {
                global+= descripcion;
                stream << descripcion;
               }
           }
         if (codigo.length()>3) { global+="\t"; stream << "\t";}
         if (codigo.length()>3 && codigo.mid(3,3)==QString("???")) 
             { global+= tr("CUALQUIERA"); stream << tr("CUALQUIERA");}
         else
          {
           bool encontrada=buscaci(codigo.mid(3,3),&descripcion,&qnivel);
           int elnivel=qnivel.toInt();
           if (encontrada && elnivel==2)
              { global += descripcion; stream << descripcion; }
          }

         if (codigo.length()>6) { global+="\t"; stream << "\t";}
         if (codigo.length()==7 && codigo[6]=='*')
             { global+= tr("CUALQUIERA"); stream << tr("CUALQUIERA");}
         else
           {
             bool encontrada=buscaci(codigo.right(codigo.length()-6),&descripcion,&qnivel);
             if (encontrada && qnivel.toInt()==3)
               {global+=descripcion; stream << descripcion;}
           }
         global+= "\n";
         stream << "\n";
        }

    // -----------------------------------------------------------------------------------------------------
*/

    stream << "DESDE:\t" << ui.datas->fecha(interFechas::inicial).toString("dd.MM.yyyy") << "\t";
    global+="DESDE:\t";
    global+=ui.datas->fecha(interFechas::inicial).toString("dd.MM.yyyy");
    global+="\t";
    stream << "HASTA: \t" << ui.datas->fecha(interFechas::final).toString("dd.MM.yyyy") << "\n";
    global+="HASTA: \t";
    global+=ui.datas->fecha(interFechas::final).toString("dd.MM.yyyy");
    global+="\n";
    stream << "DESDE CUENTA:\t" << ui.desdelineEdit->text() << "\t";
    global+="DESDE CUENTA:\t";
    global+=ui.desdelineEdit->text();
    global+="\t";
    stream << "HASTA CUENTA: \t" << ui.hastalineEdit->text() << "\n";
    global+="HASTA CUENTA: \t";
    global+=ui.hastalineEdit->text();
    global+="\n";
    for (int veces2=0;veces2<5;veces2++)
             {
               stream << ui.table->horizontalHeaderItem ( veces2 )->text();
               global+=ui.table->horizontalHeaderItem ( veces2 )->text();
               if (veces2!=4) { stream << "\t"; global+="\t"; }
	       if (veces2==4)  { stream << "\n"; global+="\n"; }
              }
    for (int veces=0;veces<ui.table->rowCount();veces++)
      for (int veces2=0;veces2<5;veces2++)
	{
	   QString cad=ui.table->item(veces,veces2)->text();
	   // if (cad[cad.length()-3]=='.') cad[cad.length()-3]=',';
	   stream << cad;
	   global+=cad;
	   if (veces2!=4) { stream << "\t"; global+="\t"; }
	   if (veces2==4) { stream << "\n"; global+="\n"; }
        }
    
    fichero.close();
    cb->setText(global);
    QMessageBox::information( this, tr("Balance de sumas y saldos"),
			      tr("Se ha pasado el contenido al portapales"));

}


// vamos por aquí

void bss::generalatex()
{
    /*int maxlin=38;
    if (ui.cilineEdit->text().length()>0 && ui.analiticagroupBox->isChecked())
        {
          maxlin-=4;
        }
*/
    
    if (ui.table->rowCount()==0) return;
    
    bool haysubcuentas=false;
    int veces=0;
    while (veces<ui.table->rowCount())
      {
        if (ui.table->item(veces,0)->text().length()==anchocuentas())
	{
	    haysubcuentas=true;
	    break;
	}
        veces++;
      }
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero+=fichero;
   qfichero+=".tex";
   // QMessageBox::warning( this, tr("Estados Contables"),qfichero);
   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(qfichero);
       else pasa=qfichero;
   QFile fichero2(pasa);
    if (! fichero2.open( QIODevice::WriteOnly ) ) return;
    QTextStream stream( &fichero2 );
    stream.setCodec("UTF-8");
    stream << "\\documentclass[11pt,a4paper]{article}" << "\n";
    stream << "\\usepackage{ucs}" << "\n";
    stream << "\\usepackage[utf8x]{inputenc}" << "\n";
    stream << "\\usepackage[spanish]{babel}" << "\n";
    stream << "\\usepackage{longtable}" << "\n";
    stream << "\\addtolength{\\hoffset}{-2.8cm}" << "\n";
    stream << "\\addtolength{\\textwidth}{5.6cm}" << "\n";
    stream << "\\addtolength{\\voffset}{-1.5cm}" << "\n";
    stream << "\\addtolength{\\textheight}{3cm}" << "\n";
    stream << "\\begin{document}" << "\n";
    stream << "% CUERPO" << "\n";
    int pos=0;
    int lineapagina=0;
    double sumadebe=0;
    double sumahaber=0;
    double sumasaldodebe=0;
    double sumasaldohaber=0;
    while (pos<ui.table->rowCount())
     {
        if (ui.conmovcheckBox->isChecked())
           {
              double sumadebe=convapunto(ui.table->item(pos,2)->text()).toDouble();
              double sumahaber=convapunto(ui.table->item(pos,3)->text()).toDouble();
              if ((sumadebe>-0.001 && sumadebe<0.001) && (sumahaber>-0.001 && sumahaber<0.001))
	         {pos++; continue;}
           }
        if (lineapagina==0)
          {	
           stream << "\\begin{center}" << "\n";
           stream << "{\\Large \\textbf {" << filtracad(nombreempresa()) << "}}" << "\n";
           stream << "\\end{center}" << "\n";
           stream << "\n";
           stream << "\\begin{center}" << "\n";
           stream << "{\\Large \\textbf {" << tr("BALANCE DE SUMAS Y SALDOS") <<  "}}" << "\n";
           stream << "\\end{center}" << "\n";
           /*if (ui.cilineEdit->text().length()>0 && ui.analiticagroupBox->isChecked())
              {
               stream << "\\begin{center}" << "\n";
               stream << "{\\normalsize \\textbf {" << tr("CÓDIGO DE IMPUTACIÓN:") << " " <<
                         ui.cilineEdit->text() <<  "}}" << "\n";
               stream << "\\end{center}" << "\n";

               QString codigo=ui.cilineEdit->text();
               QString cadena,descripcion;
               QString qnivel=0;

               stream << "\\begin{center}" << "\n";
               stream << "{\\normalsize {" ;

               if (codigo.startsWith("???"))
                   {
                    stream << tr("CUALQUIERA");
                   }
               else
                   {
                     bool encontrada=buscaci(codigo.left(3),&descripcion,&qnivel);
                     if (encontrada && qnivel.toInt()==1)
                     stream << descripcion;
                   }
               if (codigo.length()>3) stream << " - ";
               if (codigo.length()>3 && codigo.mid(3,3)==QString("???")) stream << tr("CUALQUIERA");
               else
                    {
                     bool encontrada=buscaci(codigo.mid(3,3),&descripcion,&qnivel);
                     int elnivel=qnivel.toInt();
                     if (encontrada && elnivel==2)
                     stream << descripcion;
                    }

               if (codigo.length()>6) stream << " - ";
               if (codigo.length()==7 && codigo[6]=='*')  stream << tr("CUALQUIERA");
                else
                   {
                     bool encontrada=buscaci(codigo.right(codigo.length()-6),&descripcion,&qnivel);
                     if (encontrada && qnivel.toInt()==3)
                     stream << descripcion;
                   }
               stream << "}}" << "\n";
               stream << "\\end{center}" << "\n";
            }
*/
           stream << "{\\textbf {" << tr("Período de") << " " << ui.datas->fecha(interFechas::inicial).toString("dd.MM.yyyy") <<
	                         tr(" a ") << ui.datas->fecha(interFechas::final).toString("dd.MM.yyyy") << "}}" << "\n";
           // cuerpo de listado (tablas)
           stream << "\\begin{center}\n";
           stream << "\\begin{tabular}{|l|p{7.2cm}|r|r|r|r|}\n";
           stream << "\\hline\n";
           stream << "{\\scriptsize " << tr("CUENTA") << "} & {\\scriptsize " << tr("TITULO") << 
             "} & {\\scriptsize " << tr("Sumas Debe") << "} & {\\scriptsize " << tr("Sumas Haber") <<
             "} & {\\scriptsize " << tr("Saldo Deudor") << "} & {\\scriptsize " << tr("Saldo Acreedor") << 
             "} \\\\\n";
           stream << "\\hline\n";
          }
       QString descrip;
        descrip=mcortaa(filtracad(ui.table->item(pos,1)->text()),50);
       if (ui.table->item(pos,1)->text().length()>descrip.length()) descrip=descrip+"\\#";
       if (ui.table->item(pos,0)->text().length()!=anchocuentas()) 
         {
           descrip=mcortaa(filtracad(ui.table->item(pos,1)->text()),50);
           if (ui.table->item(pos,1)->text().length()>descrip.length()) descrip=descrip+"\\#";
         }
       // descrip.remove('&');
       stream << "{\\scriptsize " << ui.table->item(pos,0)->text() 
              << "} & {\\scriptsize " << descrip << "} & {\\scriptsize ";
       double numero1=convapunto(ui.table->item(pos,2)->text()).toDouble();
       double numero2=convapunto(ui.table->item(pos,3)->text()).toDouble();
       stream << formateanumerosep(numero1,comadecimal,decimales) << "} & {\\scriptsize "
              << formateanumerosep(numero2,comadecimal,decimales) << "} & {\\scriptsize ";
       if (ui.table->item(pos,0)->text().length()==anchocuentas())
         {
          sumadebe+=convapunto(ui.table->item(pos,2)->text()).toDouble();
          sumahaber+=convapunto(ui.table->item(pos,3)->text()).toDouble();
         }
      if (convapunto(ui.table->item(pos,4)->text()).toDouble()>0.001) 
         { 
            double num=convapunto(ui.table->item(pos,4)->text()).toDouble();
            stream << formateanumerosep(num,comadecimal,decimales);
            if (ui.table->item(pos,0)->text().length()==anchocuentas())
		sumasaldodebe+=convapunto(ui.table->item(pos,4)->text()).toDouble();
         }
           else { stream << "0,00";}
       stream << "} & {\\scriptsize ";
       if (convapunto(ui.table->item(pos,4)->text()).toDouble()<0.001) 
          {
             double num=convapunto(ui.table->item(pos,4)->text()).toDouble();
             stream << formateanumerosep(num,comadecimal,decimales).remove('-');
             if (ui.table->item(pos,0)->text().length()==anchocuentas())
		 sumasaldohaber+=-convapunto(ui.table->item(pos,4)->text()).toDouble();
          }
           else { stream << "0,00";}
      stream << "} \\\\ \n " << "\\hline\n";
       QString cadnum;
       if (lineapagina==38 && haysubcuentas && pos<ui.table->rowCount()-1)
          {
               if (ui.conmovcheckBox->isChecked() && pos<ui.table->rowCount()-1)
                {
                 double sumadebe2=convapunto(ui.table->item(pos+1,2)->text()).toDouble();
                 double sumahaber2=convapunto(ui.table->item(pos+1,3)->text()).toDouble();
                 if ((sumadebe2>-0.001 && sumadebe2<0.001) && (sumahaber2>-0.001 && sumahaber2<0.001))
	            {pos++; continue;}
                }
		   lineapagina=0;
	           stream  << "\\multicolumn{2}{|r|}{" << tr("Sumas y siguen ...") << "} & {\\scriptsize " <<
	              formateanumerosep(sumadebe,comadecimal,decimales) ;
		   stream << "} & {\\scriptsize " << formateanumerosep(sumahaber,comadecimal,decimales);
		   stream << "} & {\\scriptsize " << formateanumerosep(sumasaldodebe,comadecimal,decimales);
		   stream << "} & {\\scriptsize " << formateanumerosep(sumasaldohaber,comadecimal,decimales);
		   stream << "} \\\\";
	           stream << "\\hline\n";
	     	   stream << "\\end{tabular}\n";
	           stream << "\\end{center}\n";
	           stream << "\\newpage";
		   pos++;
           continue;
          }
       pos++; lineapagina++;
     }
    if (haysubcuentas)
     {
      QString cadnum;
      stream  << tr("\\multicolumn{2}{|r|}{Sumas ...} & {\\scriptsize ") <<
         formateanumerosep(sumadebe,comadecimal,decimales);
      stream << "} & {\\scriptsize " << formateanumerosep(sumahaber,comadecimal,decimales);
      stream << "} & {\\scriptsize " << formateanumerosep(sumasaldodebe,comadecimal,decimales);
      stream << "} & {\\scriptsize " << formateanumerosep(sumasaldohaber,comadecimal,decimales);
      stream << "} \\\\";
      stream << "\\hline\n";
      stream << tr("\\multicolumn{2}{|r|}{Porcentajes ... (Bruto - Neto - Beneficio neto)} & {\\scriptsize "); 
      stream << formateanumerosep(ui.lcds->valorBruto(),comadecimal,decimales) << " \\%} & {\\scriptsize " << 
      	formateanumerosep(ui.lcds->valorNeto(),comadecimal,decimales) << " \\%} &";
      stream << "\\multicolumn{2}{|c|}{" << 
      	formateanumerosep(ui.lcds->valorBeneficio(),comadecimal,decimales);
      stream << "} \\\\";
      stream << "\\hline\n";
    }
   stream << "\\end{tabular}\n";
   stream << "\\end{center}\n";
    
    // imprimimos final del documento latex
    stream << "% FIN_CUERPO" << "\n";
    stream << "\\end{document}" << "\n";

    fichero2.close();

    if (filtrartexaxtivado()) filtratex(qfichero);

}


void bss::imprimir()
{
   fichero=tr("bss");
    generalatex();

   int valor=imprimelatex(tr("bss"));
   if (valor==1)
       QMessageBox::warning( this, tr("IMPRIMIR BALANCE SUMAS Y SALDOS"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("IMPRIMIR BALANCE SUMAS Y SALDOS"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
   if (valor==3)
       QMessageBox::warning( this, tr("IMPRIMIR BALANCE SUMAS Y SALDOS"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());

}


void bss::gentex()
{
   pidenombre *p=new pidenombre();
   int resultado=0;
   p->asignanombreventana(tr("Balance sumas y saldos"));
   p->asignaetiqueta(tr("NOMBRE FICHERO (sin extensión):"));
   resultado=p->exec();
   if (resultado==QDialog::Accepted)
      {
       if (p->contenido().length()>0) fichero=p->contenido();
       fichero.remove('*');
       fichero.remove("..");
       fichero.remove('/');
       fichero.replace(' ','_');
      }
   p->~pidenombre();
   generalatex();

   int valor=consultalatex2(fichero);
   if (valor==1)
       QMessageBox::warning( this, tr("VISTA PREVIA BALANCE SUMAS Y SALDOS"),
                             tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("VISTA PREVIA MAYOR BALANCE SUMAS Y SALDOS"),
                             tr("PROBLEMAS al llamar a ")+visordvi());

}


void bss::fijaFechas()
{
  QDate fechaini, fechafin;
  
  for (int veces=0;veces<numPeriodos;veces++)
      {
        if (((QCheckBox*)ui.periodosTableWidget->cellWidget(veces,0))->isChecked())
           {
            if(!fechaini.isValid())
            	fechaini = QDate::fromString(ui.periodosTableWidget->item(veces,1)->text(),
            		"yyyy-MM-dd");          
            fechafin = QDate::fromString(ui.periodosTableWidget->item(veces,2)->text(),
            	"yyyy-MM-dd");
           }
      }
  ui.datas->setFecha(interFechas::inicial,fechaini);
  ui.datas->setFecha(interFechas::final,fechafin);
  
  //ui.desdedateEdit->setDate(fechaini);
  //ui.hastadateEdit->setDate(fechafin);
  
  activaactualiza();
  /*QString codigo=ui.cilineEdit->text();
  QString cadena,descripcion;
  QString qnivel=0;
  ui.nivel1lineEdit->setText("");
  ui.nivel2lineEdit->setText("");
  ui.nivel3lineEdit->setText("");

 if (codigo.length()==0) return;

  if (codigo.startsWith("???"))
      {
       ui.nivel1lineEdit->setText(tr("CUALQUIERA"));
      }
      else
           {
            bool encontrada=buscaci(codigo.left(3),&descripcion,&qnivel);
            if (encontrada && qnivel.toInt()==1)
                ui.nivel1lineEdit->setText(descripcion);
           }

 if (codigo.length()<=3) return;

 if (codigo.mid(3,3)==QString("???")) ui.nivel2lineEdit->setText(tr("CUALQUIERA"));
     else
          {
           bool encontrada=buscaci(codigo.mid(3,3),&descripcion,&qnivel);
           int elnivel=qnivel.toInt();
           if (encontrada && elnivel==2)
              ui.nivel2lineEdit->setText(descripcion);
          }

 if (codigo.length()<=6) return;

 if (codigo.length()==7 && codigo[6]=='*')  ui.nivel3lineEdit->setText(tr("CUALQUIERA"));
    else
         {
          bool encontrada=buscaci(codigo.right(codigo.length()-6),&descripcion,&qnivel);
          if (encontrada && qnivel.toInt()==3)
             ui.nivel3lineEdit->setText(descripcion);
         }
*/
}

void bss::activaactualiza()
{
 ui.actualizapushButton->setEnabled(true);
}

void bss::verGrafico()
{
	if (ui.table->rowCount()==0) return;
	int s = 0;
	if (ui.subcuentascheckBox->isChecked()) s++;
	if (ui.cuentascheckBox->isChecked()) s++;
	if (ui.subgruposcheckBox->isChecked()) s++;
	if (ui.gruposcheckBox->isChecked()) s++;
	if (s != 1) return;
	ui.graficoButton->setEnabled(false);
	if (ui.actualizapushButton->isEnabled()) actualizar();
        int bola = ui.table->rowCount()*5;
	if(bola < 350) bola = 350;
        if(bola > 600) bola = 600;
        pastel *p = new pastel(bola);
	int pos=0;
	double val=0.0;
	QColor c;
    while (pos<ui.table->rowCount())
    {
    	val = convapunto(ui.table->item(pos,2)->text()).toDouble()-convapunto(ui.table->item(pos,3)->text()).toDouble();
    	if(val < 0.00) val = val*(-1);
    	if(val > 0.00)
    		p->addPorcion(c, ui.table->item(pos,1)->text(), val);
    	pos++;
   	}
   	p->exec();
   	delete(p);
    ui.graficoButton->setEnabled(true);
	
}
