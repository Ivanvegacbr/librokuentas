/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

    Copyright (C)  José Manuel Díez Botella

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

#include "consmayor.h"
#include "basedatos.h"
//#include "funciones.h"
//#include "basedatos.h"
#include "buscasubcuenta.h"
#include "tabla_asientos.h"
#include "cuadimprimayor.h"
//#include "editarasiento.h"
#include "principal.h"
#include "interfechas.h"

consmayor::consmayor(bool concomadecimal, bool condecimales) : QDialog() {
   ui.setupUi(this);
  comadecimal=concomadecimal;
  decimales=condecimales;
  
 QStringList columnas;
 columnas << tr("CUENTA") << tr("FECHA") << tr("ASTO.") << tr("CONCEPTO");
 columnas << tr("DEBE") << tr("HABER") << tr("SALDO");
 columnas << tr("DOCUMENTO") << tr("DIARIO") << tr("PAGO");
 columnas << tr("DEUDA") << tr("PLAZO");
 
 ui.mayortable->setColumnCount(12);

 ui.mayortable->hideColumn(0); // el intervalo de cuentas está desactivado por defecto

 ui.mayortable->setEditTriggers ( QAbstractItemView::NoEditTriggers );

 ui.mayortable->setHorizontalHeaderLabels(columnas);

 ui.mayortable->setColumnWidth(1,80);
 ui.mayortable->setColumnWidth(2,50);
 ui.mayortable->setColumnWidth(3,150);
 ui.mayortable->setColumnWidth(4,80);
 ui.mayortable->setColumnWidth(5,80);
 ui.mayortable->setColumnWidth(6,80);
 ui.mayortable->setColumnWidth(7,100);
 ui.mayortable->setColumnWidth(8,50);
 ui.mayortable->setColumnWidth(9,80);
ui.mayortable->setColumnWidth(10,80);
ui.mayortable->setColumnWidth(11,80);

 if (!conanalitica()) ui.mayortable->hideColumn(8);

//rellenamos el combobox para intervalos de cuentas
	//ui.iniciallineEdit->setText("0");
    QStringList conts;
    conts << tr("Gastos") << tr("Ingresos") << tr("Gastos y ingresos");
    conts << tr("Otras cuentas") << tr("Todas");
    ui.intervaloComboBox->addItems(conts);
    ui.intervaloComboBox->setCurrentIndex(4);
    /*QString cadena;
    for (int veces=0;veces<anchocuentas();veces++) cadena=cadena+"9";
    ui.finallineEdit->setText(cadena);*/
    
 connect(ui.buscapushButton,SIGNAL(clicked()),SLOT(botonsubcuentapulsado()));
 connect(ui.refrescarpushButton,SIGNAL(clicked()),SLOT(refrescar()));
 connect(ui.fechas,SIGNAL(ejercicioActivado(QString)),SLOT(refrescar()));
 connect(ui.subcuentalineEdit,SIGNAL(returnPressed()),SLOT(finedicsubcuenta()));
 connect(ui.previapushButton,SIGNAL(clicked()),SLOT(subcuentaprevia()));
 connect(ui.siguientepushButton,SIGNAL(clicked()),SLOT(subcuentasiguiente()));
 connect(ui.imprimirpushButton,SIGNAL(clicked()),SLOT(imprimir()));
 connect(ui.subcuentalineEdit,SIGNAL(textChanged(QString)),SLOT(subcuentacambiada()));
 connect(ui.editarpushButton,SIGNAL(clicked()),SLOT(editarpulsado()));

 //connect(ui.origencheckBox,SIGNAL(stateChanged(int)), SLOT(origenpercambiado()));
 //connect(ui.fincheckBox,SIGNAL(stateChanged(int)), SLOT(finalpercambiado()));

 connect(ui.intervalogroupBox,SIGNAL(toggled(bool)),this,SLOT(intervalogroupcambiado()));
 connect(ui.intervaloComboBox,SIGNAL(activated(int)),this,SLOT(intervaloCambiado( int )));
 
 connect(ui.copiarpushButton,SIGNAL(clicked()),SLOT(copiar()));

}



void consmayor::botonsubcuentapulsado()
{
    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.subcuentalineEdit->text());
    int cod=labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();
    if (cod==QDialog::Accepted && existesubcuenta(cadena2))
      ui.subcuentalineEdit->setText(cadena2);
       else ui.subcuentalineEdit->setText("");
    delete labusqueda;

}



void consmayor::cargadatos()
{
   bool intervalo=false;
   //bool interfechas = true;
   QString condicion;
   QDate fIni,fFin;
   if (ui.intervalogroupBox->isChecked()) intervalo=true;
   //if (!ui.fechas->isChecked()) interfechas=false;
   if (!intervalo)
      {
       if (!existesubcuenta(ui.subcuentalineEdit->text())) return;
       if (!escuentadegasto(ui.subcuentalineEdit->text()) && !escuentadeingreso(ui.subcuentalineEdit->text()))
         ui.mayortable->hideColumn(9);
        else ui.mayortable->showColumn(9);
       condicion="cuenta='";
       condicion+=ui.subcuentalineEdit->text();
       condicion+="'";
      }
      else
           {
             if (conanalitica()) ui.mayortable->showColumn(9);
                else ui.mayortable->hideColumn(9);
             if (ui.iniciallineEdit->text().length()==0 || ui.finallineEdit->text().length()==0)
                {
                 QMessageBox::warning( this, tr("Consulta de mayor"),
	 	 tr("ERROR: se debe de suministrar información correcta para el intervalo de cuentas"));
                 return;
                }
             condicion+="cuenta>='";
             condicion+=ui.iniciallineEdit->text();
             condicion+="' and ";
             condicion+="cuenta<='";
             condicion+=ui.finallineEdit->text();
             condicion+="'";
             ui.nombrelabel->setText(tr("Intervalo: ")+ui.iniciallineEdit->text()+
                                      " - "+ui.finallineEdit->text());
           }

	//if (interfechas){
		fIni = ui.fechas->fecha(interFechas::inicial);
		fFin = ui.fechas->fecha(interFechas::final);
	//}
    qlonglong num = selectCountAsiento( fIni, fFin, condicion );
    if (num > 15000)
    {
	    switch( QMessageBox::warning( this, tr("Consultas de Mayor"),
            tr("La consulta excede de 15000 registros,\n"
            "¿ desea cargarlos de todas formas ?"),
            tr("&Sí"), tr("&No"), 0, 0,1 ) ) 
	    {
            case 0: // proseguimos.
                break;
            case 1: // Cancelamos la carga
                ui.refrescarpushButton->setEnabled(true);
			   ui.previapushButton->setEnabled(true);
			   ui.siguientepushButton->setEnabled(true);
			   return;
        }
	}
   ui.mayortable->setRowCount(num);

   QSqlQuery query = selectDiario( fIni, fFin, condicion );
   int fila=0;
    if (query.isActive())
    while ( query.next() ) {
        QTableWidgetItem *newItemcta = new QTableWidgetItem(query.value(0).toString());
        ui.mayortable->setItem(fila,0,newItemcta);
        QTableWidgetItem *newItem = new QTableWidgetItem(query.value(1).toDate().toString(Qt::SystemLocaleShortDate));
        newItem->setToolTip(query.value(1).toDate().toString(Qt::ISODate));
        ui.mayortable->setItem(fila,1,newItem);
        if (numeracionrelativa())
        {
   	      QString cdnum;
	      cdnum.setNum(query.value(2).toLongLong()
	         -primasejerciciodelafecha(query.value(1).toDate())+1);
              QTableWidgetItem *newItems = new QTableWidgetItem(cdnum);
              newItems->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
	      ui.mayortable->setItem(fila,2,newItems);  // asiento
        }
        else
        {
                 QTableWidgetItem *newItemx = new QTableWidgetItem(query.value(2).toString());
                 newItemx->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                 ui.mayortable->setItem(fila,2,newItemx);  // asiento
        }
        QTableWidgetItem *newItemp = new QTableWidgetItem(query.value(3).toString());
        ui.mayortable->setItem(fila,3,newItemp);  // concepto
        // ***************************************************************************************
        // ***************************************************************************************
        double valdebe=query.value(4).toDouble();
		if (valdebe>0.0001 || valdebe<-0.0001)
          {
           QTableWidgetItem *newItem = new QTableWidgetItem(formateanumero(valdebe,comadecimal,decimales));
           newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
           ui.mayortable->setItem(fila,4,newItem);  // debe
          }
          else 
               {
                QTableWidgetItem *newItempp = new QTableWidgetItem("");
                ui.mayortable->setItem(fila,4,newItempp);
               }
        double valhaber=query.value(5).toDouble();
        if (valhaber>0.0001 || valhaber<-0.0001)
          {
           QTableWidgetItem *newItemjj = new QTableWidgetItem(formateanumero(valhaber,comadecimal,decimales));
           newItemjj->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
           ui.mayortable->setItem(fila,5,newItemjj);  // haber
          }
          else 
               {
                QTableWidgetItem *newItemkk = new QTableWidgetItem("");
                ui.mayortable->setItem(fila,5,newItemkk);
               }
        QTableWidgetItem *newItemj = new QTableWidgetItem(query.value(6).toString());
        ui.mayortable->setItem(fila,7,newItemj); // documento
        QTableWidgetItem *newItem2 = new QTableWidgetItem(query.value(7).toString());
        ui.mayortable->setItem(fila,8,newItem2); // diario
        QTableWidgetItem *newItem3 = new QTableWidgetItem(query.value(8).toDate().toString(Qt::SystemLocaleShortDate));
        newItem3->setToolTip(query.value(8).toDate().toString(Qt::ISODate));
        ui.mayortable->setItem(fila,9,newItem3); // ci
        fila++;
    }
  // calculamos acumulado de saldo inicial
    // primero observamos si el ejercicio anterior está cerrado
    QString ejercicio=ui.fechas->ejercicio();
    QDate fechainiejercicio=inicioejercicio(ejercicio);
    QDate fechaejercicioanterior=fechainiejercicio.addDays(-1);
    QString ejercicioanterior=ejerciciodelafecha(fechaejercicioanterior);
    if (ejerciciocerrado(ejercicioanterior) || escuentadegasto(ui.subcuentalineEdit->text()) || 
	   escuentadeingreso(ui.subcuentalineEdit->text()))		
       {
        query = selectSumasDiario(fechainiejercicio, fIni, condicion);
       }
       else
       	query = selectSumasDiarioHasta(fechainiejercicio,condicion);
    double saldoin=0;
    double sumadebe=0;
    double sumahaber=0;
    if ( (query.isActive()) && (query.first()) )
      {
        saldoin=query.value(0).toDouble()-query.value(1).toDouble();
        sumadebe=query.value(0).toDouble();
        sumahaber=query.value(1).toDouble();
      }
    fila=0;
    while (fila<ui.mayortable->rowCount())
       {
          if (ui.mayortable->item(fila,4)->text().length()>0) 
	{
	      sumadebe+=ui.mayortable->item(fila,4)->text().toDouble();
	      saldoin+=ui.mayortable->item(fila,4)->text().toDouble();
	}
          if (ui.mayortable->item(fila,5)->text().length()>0)
	  {
	      sumahaber+=ui.mayortable->item(fila,5)->text().toDouble();
	      saldoin-=ui.mayortable->item(fila,5)->text().toDouble();
	  }
        QTableWidgetItem *newItemx = new QTableWidgetItem(formateanumero(saldoin,comadecimal,decimales));
        newItemx->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
        ui.mayortable->setItem(fila,6,newItemx); // saldo
	    if (escuentadegasto(ui.mayortable->item(fila,0)->text()))
	    {
	        QDate d1,d2;
	        int day = ui.mayortable->item(fila,1)->toolTip().section("-",2,2).toInt();
	        int month = ui.mayortable->item(fila,1)->toolTip().section("-",1,1).toInt();
	        int year = ui.mayortable->item(fila,1)->toolTip().section("-",0,0).toInt();
	        d1.setDate(year,month,day);
	        day = ui.mayortable->item(fila,9)->toolTip().section("-",2,2).toInt();
	        month = ui.mayortable->item(fila,9)->toolTip().section("-",1,1).toInt();
	        year = ui.mayortable->item(fila,9)->toolTip().section("-",0,0).toInt();
	        d2.setDate(year,month,day);
	        if (!d2.isValid())
	        	d2 = d1;
	        QTableWidgetItem *newItemd = new QTableWidgetItem(formateanumero(deudaCuentaenDiario(
	        													ui.mayortable->item(fila,0)->text(),
	        													d1)
	        													,comadecimal,decimales));
	        newItemd->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
	        ui.mayortable->setItem(fila,10,newItemd); // deuda
	        QTableWidgetItem *newItempl;
	        //if (d1.daysTo(d2) || d1 == d2)
	        	newItempl = new QTableWidgetItem(tr("%1 días").arg(d1.daysTo(d2)));
	        //else
	        //	newItempl = new QTableWidgetItem(tr("No pagado"));
	        ui.mayortable->setItem(fila,11,newItempl); // plazo
        }
        fila++;
       }
   ui.debelineEdit->setText(formateanumero(sumadebe,comadecimal,decimales));
   ui.haberlineEdit->setText(formateanumero(sumahaber,comadecimal,decimales));
   ui.saldolineEdit->setText(formateanumero(saldoin,comadecimal,decimales));
   ui.mayortable->resizeColumnToContents(0);
   ui.mayortable->resizeColumnToContents(1);
   ui.mayortable->resizeColumnToContents(2);
   ui.mayortable->resizeColumnToContents(4);
   ui.mayortable->resizeColumnToContents(5);
   ui.mayortable->resizeColumnToContents(6);
   ui.mayortable->resizeColumnToContents(9);
   ui.mayortable->resizeColumnToContents(11);
   
   
}


void consmayor::refrescar()
{
   ctaexpandepunto();
   if (ui.intervalogroupBox->isChecked()) 
      {
       cargadatos();
       return;
      }

    /*if (ejerciciodelafecha(ui.fechas->DFecha(interFechas::inicial))
    	!=ejerciciodelafecha(ui.fechas->DFecha(interFechas::final))
		&&(escuentadegasto(ui.subcuentalineEdit->text()) || 
	   	escuentadeingreso(ui.subcuentalineEdit->text())))
	{
	   QMessageBox::warning( this, tr("Consultas de Mayor"),
				 tr("En consultas de cuentas de ingresos/gastos\n"
				      "las fechas han de pertenecer al mismo período"));
	   QString ejercicio=ejerciciodelafecha(ui.fechas->DFecha(interFechas::inicial));
	   //QMessageBox::warning( this, tr("Consultas de Mayor"),ejercicio);
	   if (ejercicio.length()!=0) ui.fechas->setFecha(interFechas::final,finejercicio(ejercicio));
	   else ui.fechas->setFecha(interFechas::final,ui.fechas->DFecha(interFechas::inicial));
    }*/

   if ( existesubcuenta(ui.subcuentalineEdit->text())) {
     QString cadena="Consultas de Mayor: ";
     cadena+=descripcioncuenta(ui.subcuentalineEdit->text());
     ui.previapushButton->setEnabled(false);
     ui.siguientepushButton->setEnabled(false);
     cargadatos();
     setWindowTitle(cadena);
     ui.nombrelabel->setText(descripcioncuenta(ui.subcuentalineEdit->text()));
     ui.previapushButton->setEnabled(true);
     ui.siguientepushButton->setEnabled(true);
   
   }
}


void consmayor::ctaexpandepunto()
{
  ui.iniciallineEdit->setText(expandepunto(ui.iniciallineEdit->text(),anchocuentas()));
  ui.finallineEdit->setText(expandepunto(ui.finallineEdit->text(),anchocuentas()));
  ui.subcuentalineEdit->setText(expandepunto(ui.subcuentalineEdit->text(),anchocuentas()));
}



void consmayor::finedicsubcuenta()
{
 ctaexpandepunto();
 if (ui.subcuentalineEdit->text().length()<anchocuentas()) botonsubcuentapulsado();
}


void consmayor::pasadatos( QString qsubcuenta, QDate qfecha )
{
   ui.subcuentalineEdit->setText(qsubcuenta);
   QString ejercicio=ejerciciodelafecha(qfecha);
   ui.fechas->setEjercicio(ejercicio);
   QString cadena="Consultas de Mayor: ";
   cadena+=descripcioncuenta(qsubcuenta);
   setWindowTitle(cadena);
   ui.nombrelabel->setText(descripcioncuenta(ui.subcuentalineEdit->text()));
   if (existesubcuenta(ui.subcuentalineEdit->text())) refrescar();
}


void consmayor::subcuentaprevia()
{
    QString cadena=subcuentaanterior(ui.subcuentalineEdit->text());
    if (cadena=="") return;
    ui.subcuentalineEdit->setText(cadena);
    refrescar();
}


void consmayor::subcuentasiguiente()
{
    QString cadena=subcuentaposterior(ui.subcuentalineEdit->text());
    if (cadena=="") return;
    ui.subcuentalineEdit->setText(cadena);
    refrescar();
}


void consmayor::imprimir()
{
  //QMessageBox::warning(this,tr("Consultas de Mayor"),"Imprimir");
  if (ui.intervalogroupBox->isChecked())
     {
       latexintervalo();
       int valor=imprimelatex(tr("mayor_int"));
       if (valor==1)
         QMessageBox::warning( this, tr("Imprimir plan"),tr("PROBLEMAS al llamar a Latex"));
       if (valor==2)
         QMessageBox::warning( this, tr("Imprimir plan"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
       if (valor==3)
         QMessageBox::warning( this, tr("Imprimir plan"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());
       return;
     }
     
  cuadimprimayor *cuadimpri=new cuadimprimayor(comadecimal,decimales);
  cuadimpri->generalatexmayor( ui.subcuentalineEdit->text(),ui.subcuentalineEdit->text(),
 		ui.fechas->fecha(interFechas::inicial),ui.fechas->fecha(interFechas::final) );
  delete cuadimpri;

   int valor=imprimelatex(tr("mayor"));
   if (valor==1)
       QMessageBox::warning( this, tr("IMPRIMIR MAYOR"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("IMPRIMIR MAYOR"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
   if (valor==3)
       QMessageBox::warning( this, tr("IMPRIMIR MAYOR"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());

}


void consmayor::subcuentacambiada()
{
  if (existesubcuenta(ui.subcuentalineEdit->text()))
      refrescar();
}




void consmayor::editarpulsado()
{
    QString asiento;

    if (ui.mayortable->currentItem()==0) return;
    int dia=ui.mayortable->item(ui.mayortable->currentRow(),1)->text().left(2).toInt();
    int mes=ui.mayortable->item(ui.mayortable->currentRow(),1)->text().mid(3,2).toInt();
    int anyo=ui.mayortable->item(ui.mayortable->currentRow(),1)->text().right(4).toInt();
    QDate fecha(anyo,mes,dia);
    if (numeracionrelativa())
    {
		 qlonglong numrel=ui.mayortable->item(ui.mayortable->currentRow(),2)->text().toLongLong();
	     qlonglong numabs=primasejerciciodelafecha(fecha)+numrel-1;
		 asiento.setNum(numabs);
    }else
         asiento=ui.mayortable->item(ui.mayortable->currentRow(),2)->text();
    
    QString ejercicio=ui.fechas->ejercicio();
       
    //fecha=fechaMaxAsiento(asiento,ejercicio);

    QString qdiario;
    qdiario=diariodeasiento(asiento);
    
    if (qdiario==diario_apertura() || qdiario==diario_cierre() || qdiario==diario_regularizacion())
       {
         QMessageBox::warning( this, tr("Consultas de Mayor"),
			       tr("ERROR: No se pueden editar asientos del diario de apertura, "
				  "regularización o cierre\n"));
         return;
       }

    if (!existeasiento(asiento,ejercicio))
       {
         QMessageBox::warning( this, tr("Consultas de Mayor"),
			       tr("ERROR: El asiento seleccionado ya no existe"));
         return;
       }

    Mrconta *mr = new Mrconta();
    mr->funcedasiento(asiento,ejercicio);
    delete mr;

}

void consmayor::intervalogroupcambiado()
{
  if (ui.intervalogroupBox->isChecked())
     {
      ui.nombrelabel->clear();
      ui.subcuentalineEdit->setEnabled(false);
      ui.subcuentalineEdit->clear();
      ui.buscapushButton->setEnabled(false);
      ui.previapushButton->setEnabled(false);
      ui.siguientepushButton->setEnabled(false);
      QString cadena="Consultas de Mayor";
      setWindowTitle(cadena);
      ui.mayortable->showColumn(0);
     }
   else
       {
        ui.nombrelabel->clear();
        ui.subcuentalineEdit->setEnabled(true);
        ui.buscapushButton->setEnabled(true);
        ui.previapushButton->setEnabled(true);
        ui.siguientepushButton->setEnabled(true);
        ui.iniciallineEdit->clear();
        ui.finallineEdit->clear();
        QString cadena="Consultas de Mayor";
        setWindowTitle(cadena);
        ui.mayortable->hideColumn(0);
       }
}

void consmayor::intervaloCambiado( int index )
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
	ui.iniciallineEdit->setText(desde);
	ui.finallineEdit->setText(hasta);
}

void consmayor::latexintervalo()
{
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero=qfichero+tr("mayor_int.tex");
   // QMessageBox::warning( this, tr("Estados Contables"),qfichero);
   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(qfichero);
       else pasa=qfichero;
   QFile fichero(pasa);

    if (! fichero.open( QIODevice::WriteOnly ) ) return;
    QTextStream stream( &fichero );
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

    stream << "\\begin{center}" << "\n";
    stream << "{\\Large \\textbf {" << filtracad(nombreempresa()) << "}}" << "\n";
    stream << "\\end{center}" << "\n";
    stream << "\n";

    stream << "\\begin{center}" << "\n";
    stream << "{\\Large \\textbf {" << tr("MAYOR ") << filtracad(ui.nombrelabel->text()) <<  "}}" << "\n";
    stream << "\\end{center}" << "\n";

    // cuerpo de listado (tabla)
    stream << "\\begin{center}\n";
    stream << "\\begin{longtable}{|l|l|r|p{6cm}|r|r|r|}\n";
    stream << "\\hline\n";
    QDate fechainicial=ui.fechas->fecha(interFechas::inicial);
    QDate fechafinal=ui.fechas->fecha(interFechas::final);
    stream << "\\multicolumn{7}{|c|} {\\textbf{";
    stream << tr("Extracto de ") << fechainicial.toString("dd.MM.yyyy") <<
                         tr(" a ") << fechafinal.toString("dd.MM.yyyy");
    stream <<  "}} \\\\";
    stream << "\\hline" << "\n";

    stream << "{\\scriptsize {" << tr("CUENTA") << "}} & {\\scriptsize {" << tr("FECHA") << 
             "}} & {\\scriptsize {" << tr("ASTO.") << "}} & {\\scriptsize {" <<
            tr("CONCEPTO") << "}} & {\\scriptsize {" << tr("DEBE") << "}} & {\\scriptsize {" << tr("HABER") << 
            "}} & {\\scriptsize {" << tr("SALDO") << "}} \\\\\n";
    stream << "\\hline\n";
    stream << "\\endfirsthead";
    // --------------------------------------------------------------------------------------------------
    stream << "\\hline" << "\n";
    stream << "{\\scriptsize {" << tr("CUENTA") << "}} & {\\scriptsize {" << tr("FECHA") << 
               "}} & {\\scriptsize {" << tr("ASTO.") << "}} & {\\scriptsize {" <<
             tr("CONCEPTO") << "}} & {\\scriptsize {" << tr("DEBE") << "}} & {\\scriptsize {" << tr("HABER") << 
             "}} & {\\scriptsize {" << tr("SALDO") << "}} \\\\\n";
    stream << "\\hline\n";
    stream << "\\endhead";
    // --------------------------------------------------------------------------------------------------

    double importe=0;
    int linactu=0;
    while (linactu<ui.mayortable->rowCount())
          {
           stream << "{\\scriptsize " << filtracad(ui.mayortable->item(linactu,0)->text()) << "} & {\\scriptsize ";
           stream << filtracad(ui.mayortable->item(linactu,1)->text()) << "} & {\\scriptsize ";
           stream << filtracad(ui.mayortable->item(linactu,2)->text()) << "} & {\\scriptsize ";
           stream << filtracad(ui.mayortable->item(linactu,3)->text()) << "} & {\\scriptsize ";
           importe=convapunto(ui.mayortable->item(linactu,4)->text()).toDouble();
           stream << formateanumerosep(importe,comadecimal,decimales) << "} & {\\scriptsize ";
           importe=convapunto(ui.mayortable->item(linactu,5)->text()).toDouble();
           stream << formateanumerosep(importe,comadecimal,decimales) << "} & {\\scriptsize ";
           importe=convapunto(ui.mayortable->item(linactu,6)->text()).toDouble();
           stream << formateanumerosep(importe,comadecimal,decimales) << "} ";
           stream << " \\\\ \n ";
           stream << "\\hline\n";
           linactu++;
          }
      importe=convapunto(ui.debelineEdit->text()).toDouble();
      stream  << "\\multicolumn{4}{|r|}{" << tr("Sumas ...") << "} & {\\scriptsize " <<
              formateanumerosep(importe,comadecimal,decimales);
      importe=convapunto(ui.haberlineEdit->text()).toDouble();
      stream << "} & {\\scriptsize " << formateanumerosep(importe,comadecimal,decimales) << "} & \\\\";
      stream << "\\hline\n";
      // final de la tabla
      stream << "\\end{longtable}\n";
      stream << "\\end{center}\n";

    // imprimimos final del documento latex
    stream << "% FIN_CUERPO" << "\n";
    stream << "\\end{document}" << "\n";

    fichero.close();

    if (filtrartexaxtivado()) filtratex(qfichero);

}


void consmayor::copiar()
{
   QClipboard *cb = QApplication::clipboard();
   QString global;

   global=nombreempresa();
   global+="\n";
   global+=ui.nombrelabel->text();
   global+="\n";
   global+=tr("INICIAL:");
   global+="\t";
   global+=ui.fechas->fecha(interFechas::inicial).toString("dd/MM/yyyy");
   global+="\n";
   global+=tr("FINAL:");
   global+="\t";
   global+=ui.fechas->fecha(interFechas::final).toString("dd/MM/yyyy");
   global+="\n\n";
   if (ui.intervalogroupBox->isChecked())
      {
       global+=tr("CUENTA") +"\t";
      }
   global+=tr("FECHA") +"\t"+ tr("ASTO.") +"\t"+ tr("CONCEPTO") +
           "\t"+ tr("DEBE") +"\t"+ tr("HABER") +"\t"+ tr("SALDO")+
           "\t"+ tr("DOCUMENTO")+"\t"+ tr("DIARIO");
   if (conanalitica()) global+="\t"+ tr("CI");

   global+="\n";

    int linactu=0;
    while (linactu<ui.mayortable->rowCount())
          {
           if (ui.intervalogroupBox->isChecked())
              {
                global+=ui.mayortable->item(linactu,0)->text();
                global+="\t";
              }
           global+=ui.mayortable->item(linactu,1)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,2)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,3)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,4)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,5)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,6)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,7)->text();
           global+="\t";
           global+=ui.mayortable->item(linactu,8)->text();
           if (conanalitica())
              {
               global+="\t";
               global+=ui.mayortable->item(linactu,9)->text();
              }
           global+="\n";
           linactu++;
          }

   cb->setText(global);
   QMessageBox::information( this, tr("Consulta de mayor"),
                             tr("Se ha pasado el contenido al portapapeles") );

}

//BASEDATOS
qlonglong consmayor::selectCountAsiento(QDate inicial, QDate final, QString condicion) {
    QString cadena = "select count(asiento) from diario where ";
    if (inicial.isValid() && final.isValid()){
	    cadena += "fecha>='";
	    cadena += inicial.toString("yyyy/MM/dd");
	    cadena += "' and fecha<='";
	    cadena += final.toString("yyyy/MM/dd");
	    cadena += "' and ";
    }
    cadena += condicion;

    QSqlQuery query = ejecutarSQL(cadena);
    if ( (query.isActive()) && (query.first()) )
    {
        return query.value(0).toLongLong();
    }
    return 0;
}

QSqlQuery consmayor::selectDiario (QDate inicial, QDate final, QString condicion) {
    QString cadena = "select cuenta,fecha,asiento,concepto,debe,haber,documento,diario,ci from diario where ";
    if (inicial.isValid() && final.isValid()){
	    cadena += "fecha>='";
		cadena += inicial.toString("yyyy/MM/dd");
	    cadena += "' and fecha<='";
	    cadena += final.toString("yyyy/MM/dd");
	    cadena += "' and ";
    }
    cadena += condicion;
    cadena += " order by fecha,pase";
    return ejecutarSQL(cadena);
}

QSqlQuery consmayor::selectSumasDiario (QDate fechainiejercicio, QDate final, QString condicion) {
    QString cadena = "select sum(debe),sum(haber) from diario where ";
    if (fechainiejercicio.isValid() && final.isValid()){
	    cadena += "fecha>='";
		cadena += fechainiejercicio.toString("yyyy.MM.dd");
	    cadena += "' and fecha<='";
	    cadena += final.toString("yyyy.MM.dd");
	    cadena += "' and ";
    }
    cadena += condicion;
    return ejecutarSQL(cadena);
}

QSqlQuery consmayor::selectSumasDiarioHasta (QDate final, QString condicion) {
    QString cadena="select sum(debe),sum(haber) from diario where ";
    if (final.isValid()){
	    cadena += "fecha<='";
	    cadena += final.toString("yyyy.MM.dd");
	    cadena += "' and ";
    }
    cadena += condicion;
    return ejecutarSQL(cadena);
}
