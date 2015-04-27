/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

    Copyright (C) 2008  José Manuel Díez Botella

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



#include "tabla_asientos.h"
#include "basedatos.h"
#include "funciones.h"
#include "subcuentas.h"
#include "buscasubcuenta.h"
#include "buscaconcepto.h"
#include "conceptos.h"
#include "imprimediario.h"
#include "pidenombre.h"
//#include "ivarepercutido.h"
//#include "aib.h"
//#include "eib.h"
//#include "introci.h"
#include "consmayor.h"
//#include "ivadatosadic.h"


tabla_asientos::tabla_asientos(bool concomadecimal, bool condecimales) : QDialog() {
  ui.setupUi(this);
  comadecimal=concomadecimal;
  decimales=condecimales;
  editando=false;
  //eseib=false;
  //esaibautonomo=false;
  //eseibautonomo=false;
  // tener en cuenta coma decimal y sindecimales
  // columnas debe y haber con justificación a la derecha
 QStringList columnas;
 columnas << tr("SUBCUENTA") << tr("CONCEPTO") << tr("DEBE");
 columnas << tr("HABER") << tr("DOCUMENTO") << tr("CTABASEIVA");
 columnas << tr("BASEIVA") << tr("C.IVA") << tr("TIPOIVA");
 columnas << tr("TIPORE") << tr("CUOTAIVA") << tr("CUENTAFRA");
 columnas << tr("DIA") << tr("MES") << tr("AÑO");
 columnas << tr("PASE") << tr("PAGO");

 ui.Tablaapuntes->setHorizontalHeaderLabels(columnas);
 ui.Tablaapuntes->setColumnWidth(0,115);
 if (conanalitica()) ui.Tablaapuntes->setColumnWidth(1,260);
    else ui.Tablaapuntes->setColumnWidth(1,365);
 ui.Tablaapuntes->hideColumn(1); // concepto
 ui.Tablaapuntes->setColumnWidth(2,100);
 ui.Tablaapuntes->setColumnWidth(3,100);
 ui.Tablaapuntes->setColumnWidth(4,130);
 ui.Tablaapuntes->hideColumn(4); // documento
 ui.Tablaapuntes->hideColumn(5); // ctabaseiva
 ui.Tablaapuntes->hideColumn(6); // baseiva
 ui.Tablaapuntes->setColumnWidth(7,60);
 //ui.Tablaapuntes->hideColumn(7); // claveiva
 ui.Tablaapuntes->hideColumn(8); // tipoiva
 ui.Tablaapuntes->hideColumn(9); // tipore
 ui.Tablaapuntes->hideColumn(10); // cuotaiva
 ui.Tablaapuntes->hideColumn(11); //cuentafra
 ui.Tablaapuntes->setColumnWidth(12,30);
 //ui.Tablaapuntes->hideColumn(12); //día
 ui.Tablaapuntes->setColumnWidth(13,35);
 //ui.Tablaapuntes->hideColumn(13); //mes
 ui.Tablaapuntes->hideColumn(14); //año
 ui.Tablaapuntes->hideColumn(15); //soportado(pase)
 ui.Tablaapuntes->setColumnWidth(15,45);
 ui.Tablaapuntes->setColumnWidth(16,80);//ci(fecha pago)

 if (!conanalitica()) ui.Tablaapuntes->hideColumn(16);

 if (conigic())
     {
       // modificamos mensajes en botones
       ui.ivaLabel->setText("Tipo IGIC");
     }
 ui.actionPegar-> setShortcut(QKeySequence::Paste);
  // Tenemos que cargar clave IVA por defecto y resto de IVA'S en el combo box
    QString pasalinea;
    QString Clavedefecto, laclave;
    double tipo;
    double re;
    QString qdescrip;
    QString convert;
    Clavedefecto=clave_iva_defecto();
    if (Clavedefecto.length()>0 && existeclavetipoiva(Clavedefecto,&tipo,&re,&qdescrip))
        {
		pasalinea=Clavedefecto;
		if (!conigic()) pasalinea+=tr(" // IVA:");
	            else pasalinea+=tr(" // IGIC:");
		convert.setNum(tipo,'f',2);
		if (comadecimal) pasalinea+=convacoma(convert);
	            else pasalinea+=convert;
		pasalinea+=tr(" RE:");
		convert.setNum(re,'f',2);
		if (comadecimal) pasalinea+=convacoma(convert);
	            else pasalinea+=convert;
		ui.ClaveivaComboBox->insertItem ( 0,pasalinea) ;
        }
    ui.ClaveivaComboBox->insertItem ( 1,diario_no_asignado() ) ;
    ui.ClaveivaComboBox->insertItem ( 2,iva_mixto() );
    // ahora cargamos el resto de los tipos de IVA
    
 QString cadquery;
 cadquery="SELECT clave,tipo,re from tiposiva where clave != '";
 cadquery+=Clavedefecto;
 cadquery+="';";
 
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      while (query.next())
         {
	  laclave=query.value(0).toString();
	  tipo=query.value(1).toDouble();
	  re=query.value(2).toDouble();
               qdescrip=query.value(3).toString();
	  pasalinea=laclave;
	  pasalinea+=tr(" // IVA:");
	  convert.setNum(tipo,'f',2);
	  if (comadecimal) pasalinea+=convacoma(convert);
              else pasalinea+=convert;
	  pasalinea+=tr(" RE:");
	  convert.setNum(re,'f',2);
	  if (comadecimal) pasalinea+=convacoma(convert);
              else pasalinea+=convert;
	  ui.ClaveivaComboBox->insertItem ( -1,pasalinea) ;
	     }
    }

 //connect(ui.Tablaapuntes,SIGNAL( cellChanged ( int , int )),this,
 //          SLOT(contenidocambiado(int,int )));
 connect(ui.Tablaapuntes,SIGNAL( currentCellChanged ( int , int, int, int )),this,
           SLOT(posceldacambiada ( int, int, int, int  )));
 
 connect(ui.Tablaapuntes,SIGNAL( itemChanged (QTableWidgetItem *)),this,
           SLOT(itemCambiado( QTableWidgetItem *)));
 
 
 connect(ui.ClaveivaComboBox,SIGNAL(activated(int)),this,SLOT(comboIvaCambiado()));
 
 connect(ui.actionBorrarLinea,SIGNAL(triggered()),this,SLOT(borralinea( void )));
 connect(ui.actionBorrarTodo,SIGNAL(triggered()),this,SLOT(borratodo( void )));
 connect(ui.actionImprimir,SIGNAL(triggered()),this,SLOT(imprimirAsiento()));
 connect(ui.actionIncorporar,SIGNAL(triggered()),this,SLOT(incorporar()));
 connect(ui.checkClaveiva,SIGNAL(stateChanged(int)),SLOT(verIvas()));
 connect(ui.checkConcepto,SIGNAL(stateChanged(int)),SLOT(verConcepto()));
 connect(ui.checkDocumento,SIGNAL(stateChanged(int)),SLOT(verDocumento()));
 connect(ui.actionPasarAEspera,SIGNAL(triggered()),SLOT(botonesperapulsado()));
 connect(ui.actionPegar,SIGNAL(triggered()),SLOT(pegar()));
 //connect(ui.editarcipushButton,SIGNAL(clicked()),SLOT(procesabotonci()));
 connect(ui.mayorpushButton,SIGNAL(clicked()),SLOT(mayor()));
 connect(ui.actionCancelar,SIGNAL(triggered()),SLOT(cancelar()));
 connect(ui.CalendarioMes,SIGNAL(clicked(QDate)),SLOT(fechacambiada()));
 
 setWindowTitle(tr("tabla apuntes"));
 time =  QTime::currentTime();
 
}

void tabla_asientos::backup(){
	QTime ahora = QTime::currentTime();
	if ((time.addSecs(5*60) < ahora) && ui.actionPasarAEspera->isEnabled()){
		pasarEspera(TRUE);
		time =  QTime::currentTime();
	}
	
}

void tabla_asientos::verIvas()
{
  if (ui.checkClaveiva->isChecked())
    {
    	ui.Tablaapuntes->showColumn(6);
 		ui.Tablaapuntes->showColumn(8);
 		ui.Tablaapuntes->showColumn(9);
 		ui.Tablaapuntes->showColumn(10);
 		
    }
   else 
    {
    	ui.Tablaapuntes->hideColumn(6);
 		ui.Tablaapuntes->hideColumn(8);
 		ui.Tablaapuntes->hideColumn(9);
 		ui.Tablaapuntes->hideColumn(10);
 		
    }
}

void tabla_asientos::verConcepto()
{
  if (ui.checkConcepto->isChecked())
    {
    	ui.Tablaapuntes->showColumn(1);
 	}
   else 
    {
    	ui.Tablaapuntes->hideColumn(1);
 	}
}

void tabla_asientos::verDocumento()
{
  if (ui.checkDocumento->isChecked())
    {
    	ui.Tablaapuntes->showColumn(4);
 	}
   else 
    {
    	ui.Tablaapuntes->hideColumn(4);
 	}
}

void tabla_asientos::rellenaLinea (int fila,bool nueva)
{
	for (int veces=0;veces<17;veces++){
         if (ui.Tablaapuntes->item(fila,veces)==0){
           QTableWidgetItem *newItem = new QTableWidgetItem("");
           if (veces==2 || veces==3)
           	newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter); 
           if (veces==16 && nueva){
           	newItem->setData(Qt::CheckStateRole,bool());
           	newItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
           }
           ui.Tablaapuntes->setItem(fila,veces,newItem);
		 }
	 }
    
}

void tabla_asientos::itemCambiado(QTableWidgetItem *check){
	if (check->row()<0) return;
	int qfila = check->row();
	int qcol = check->column();
	ui.Tablaapuntes->disconnect(SIGNAL(itemChanged(QTableWidgetItem *)));
	contenidocambiado(qfila,qcol);
	connect(ui.Tablaapuntes,SIGNAL( itemChanged (QTableWidgetItem *)),this,
    	SLOT(itemCambiado( QTableWidgetItem *)));
 
	if (check->column()!=16) return;
	if (check->checkState()==Qt::Checked){
		int dia = ui.Tablaapuntes->item(check->row(),12)->text().toInt();
		int mes = ui.Tablaapuntes->item(check->row(),13)->text().toInt();
		int anyo = ui.Tablaapuntes->item(check->row(),14)->text().toInt();
		if (QDate::isValid(anyo,mes,dia)){
			check->setText(ui.Tablaapuntes->item(check->row(),14)->text()+"-"+
					ui.Tablaapuntes->item(check->row(),13)->text()+"-"+
					ui.Tablaapuntes->item(check->row(),12)->text());
			check->setToolTip(ui.Tablaapuntes->item(check->row(),14)->text()+"-"+
					ui.Tablaapuntes->item(check->row(),13)->text()+"-"+
					ui.Tablaapuntes->item(check->row(),12)->text());
		}else{
			check->setText(ui.CalendarioMes->selectedDate().toString("yyyy-MM-dd"));
			check->setToolTip(ui.CalendarioMes->selectedDate().toString("dd-MM-yyyy"));
		}
	}
	if(check->checkState()==Qt::Unchecked){
		if(check->text() == check->toolTip()){
			check->setText("");
			check->setToolTip(tr("Pendiente de pago"));
		}
	}
	//ui.Tablaapuntes->setCurrentCell(ui.Tablaapuntes->currentRow()+1,0); return;
	
}

// IGIC y analítica
void tabla_asientos::contenidocambiado(int fila,int columna)
{
 if (ui.Tablaapuntes->currentColumn()!=columna || ui.Tablaapuntes->currentRow()!=fila) return;
 QMessageBox msgBox;
 QPushButton *aceptarButton = msgBox.addButton(tr("&Sí"), QMessageBox::ActionRole);
 QPushButton *botonCancelar = msgBox.addButton(tr("&No"), QMessageBox::ActionRole);
 msgBox.setWindowTitle(tr("ADVERTENCIA"));
 msgBox.setIcon(QMessageBox::Warning);

    //backup();
    
if (columna==0) {
    //ui.Tablaapuntes->disconnect(SIGNAL(itemChanged(QTableWidgetItem *)));
 	rellenaLinea(fila,TRUE);
 	//connect(ui.Tablaapuntes,SIGNAL( itemChanged (QTableWidgetItem *)),this,
    //       SLOT(itemCambiado( QTableWidgetItem *)));
 
    if (ui.Tablaapuntes->item(fila,columna)!=0)
       ui.Tablaapuntes->item(fila,columna)->setText(
        expandepunto(ui.Tablaapuntes->item(fila,columna)->text(),
		anchocuentas()));
    if (ui.Tablaapuntes->item(fila,columna)->text().length()==anchocuentas()
    	 && cadnumvalido(ui.Tablaapuntes->item(fila,columna)->text())) {
	if (!existesubcuenta(ui.Tablaapuntes->item(fila,columna)->text())) 
	  {
	 // preguntar si se desea añadir la cuenta, si no o si se cancela lo anterior dejar en blanco
            QString TextoAviso = tr("El código suministrado no existe \n"
                         "¿ desea añadir la subcuenta ?");
            msgBox.setText(TextoAviso);
            msgBox.exec();
	    if (msgBox.clickedButton() == aceptarButton) {
	               subcuentas *lasubcuenta2=new subcuentas();
		       lasubcuenta2->pasacodigo(ui.Tablaapuntes->item(fila,columna)->text());
		       lasubcuenta2->exec();
	               lasubcuenta2->~subcuentas(); 
	               if (!existesubcuenta(ui.Tablaapuntes->item(fila,columna)->text()))
                           {
                            //ui.Tablaapuntes->disconnect(SIGNAL(cellChanged(int,int)));
                            if (ui.Tablaapuntes->item(fila,columna)==0)
                                ui.Tablaapuntes->setItem(fila,columna,new QTableWidgetItem(""));
                              else
                                  ui.Tablaapuntes->item(fila,columna)->setText("");
                            //connect(ui.Tablaapuntes,SIGNAL( cellChanged ( int , int )),this,
                            //SLOT(contenidocambiado(int,int )));
                            return;
                           }
		     }
		  else
                       {
                        //ui.Tablaapuntes->disconnect(SIGNAL(cellChanged(int,int)));
                        if (ui.Tablaapuntes->item(fila,columna)==0)
                                ui.Tablaapuntes->setItem(fila,columna,new QTableWidgetItem(""));
                              else
                                  ui.Tablaapuntes->item(fila,columna)->setText("");
                        ui.Tablaapuntes->item(fila,0)->setText("");
                        //connect(ui.Tablaapuntes,SIGNAL( cellChanged ( int , int )),this,
                        //   SLOT(contenidocambiado(int,int )));
                        return;
                       }
	   }
	   
	   
    }else { // la longitud de la subcuenta no es la correcta
	    QString cadena2;
	    //unicoCodigoSubcuenta(&cadena2,ui.Tablaapuntes->item(fila,columna)->text())
	    
	    if (unicoCodigoSubcuenta(&cadena2,ui.Tablaapuntes->item(fila,columna)->text()))
	    {
	    	ui.Tablaapuntes->item(fila,columna)->setText(cadena2);
    	}else{
		    //QString cadena2;
		    buscasubcuenta *labusqueda=new buscasubcuenta(ui.Tablaapuntes->item(fila,columna)->text());
		    int cod=labusqueda->exec();
		    cadena2=labusqueda->seleccioncuenta();
		    QString texto;
		    if (cod==QDialog::Accepted && cadena2.length()==anchocuentas())
		    	ui.Tablaapuntes->item(fila,columna)->setText(cadena2);
		    else{
		              //ui.Tablaapuntes->disconnect(SIGNAL(cellChanged(int,int)));
		              ui.Tablaapuntes->item(fila,columna)->setText("");
		              //connect(ui.Tablaapuntes,SIGNAL( cellChanged ( int , int )),this,
		              //  SLOT(contenidocambiado(int,int )));
		    }
		    labusqueda->~buscasubcuenta();
    	}
    }
   //if (ui.Tablaapuntes->item(fila,columna)->text().length()==0) borralinea();
    //else
     // copiamos fecha del pase anterior
     if (ui.Tablaapuntes->item(fila,12)->text().length()==0 
        && ui.Tablaapuntes->item(fila,0)->text().length()>0 && fila>0)
      {
        if (ui.Tablaapuntes->item(fila-1,12)!=0)
          {
           ui.Tablaapuntes->item(fila,12)->setText(ui.Tablaapuntes->item(fila-1,12)->text());
           ui.Tablaapuntes->item(fila,13)->setText(ui.Tablaapuntes->item(fila-1,13)->text());
           ui.Tablaapuntes->item(fila,14)->setText(ui.Tablaapuntes->item(fila-1,14)->text());
          }
      }
      
  }

if (columna==1)
	{
		// conceptos
        QString cadena,cadena3;
        /*if (ui.Tablaapuntes->item(fila,columna)->text().length()==0)
          {
	        
                buscaconcepto *labusqueda2=new buscaconcepto("");
                labusqueda2->exec();
                cadena3=labusqueda2->seleccionconcepto();
                if (cadena3.length()>0)
		        {
                 //QString cadena;
			 	 existecodigoconcepto(cadena3,&cadena);
			 	 ui.Tablaapuntes->item(fila,columna)->setText(cadena);
		     	}
                else
                	ui.Tablaapuntes->item(fila,columna)->setText("");
                labusqueda2->~buscaconcepto();
	      }
        */
    
        if (ui.Tablaapuntes->item(fila,columna)->text().length()<4 && 
            ui.Tablaapuntes->item(fila,columna)->text().length()>0) 
        {
            //QString cadena;
		 if(ui.Tablaapuntes->item(fila,columna)->text().length()==3)
		 {
			if (existecodigoconcepto(ui.Tablaapuntes->item(fila,columna)->text(),&cadena))
	        	ui.Tablaapuntes->item(fila,columna)->setText(cadena);
        	else
	    	{
        		QString TextoAviso = tr("El código suministrado no existe \n"
        			"¿ desea añadir el concepto ?");
        		msgBox.setText(TextoAviso);
        	    msgBox.exec();
	    	    if (msgBox.clickedButton() == aceptarButton) 
	    	    {
				  conceptos *elconcepto=new conceptos();
				  elconcepto->pasacodigo(ui.Tablaapuntes->item(fila,columna)->text());
				  elconcepto->exec();
				  elconcepto->~conceptos();
	    	      if (existecodigoconcepto(ui.Tablaapuntes->item(fila,columna)->text(),&cadena))
	    	 	     ui.Tablaapuntes->item(fila,columna)->setText(cadena);
			      else 
			      	 ui.Tablaapuntes->item(fila,columna)->setText("");
			    }
		    	else
	               ui.Tablaapuntes->item(fila,columna)->setText("");
	       	}
       	 }else{
       	 	if (cadnumvalido(ui.Tablaapuntes->item(fila,columna)->text()))
          	 {
	        
                buscaconcepto *labusqueda2=new buscaconcepto(ui.Tablaapuntes->item(fila,columna)->text());
                labusqueda2->exec();
                cadena3=labusqueda2->seleccionconcepto();
                if (cadena3.length()>0)
		        {
                 //QString cadena;
			 	 existecodigoconcepto(cadena3,&cadena);
			 	 ui.Tablaapuntes->item(fila,columna)->setText(cadena);
		     	}
                else
                	ui.Tablaapuntes->item(fila,columna)->setText("");
                labusqueda2->~buscaconcepto();
	      	 }
      	 	}
       	 
        }
    }


double valor = 0;
bool ok;


if (columna==2 || columna==3) 
{
   //ui.Tablaapuntes->disconnect(SIGNAL(cellChanged(int,int)));
   QString valores = convapunto(ui.Tablaapuntes->item(fila,columna)->text());
   valores.replace('-',"+-");
   if (valores.contains('/') || valores.contains(':') || valores.contains('(') || valores.contains(')')){
        QString TextoAviso = tr("Las únicas operaciones permitidas son <+>, <-> y <*> sin paréntesis.");
   	 msgBox.removeButton(botonCancelar);
   	 msgBox.removeButton(aceptarButton);
     msgBox.addButton(tr("&Aceptar"), QMessageBox::ActionRole);
     msgBox.setText(TextoAviso);
     msgBox.exec();
     ui.Tablaapuntes->item(fila,columna)->setText("");
     aceptarButton = msgBox.addButton(tr("&Sí"), QMessageBox::ActionRole);
     botonCancelar = msgBox.addButton(tr("&No"), QMessageBox::ActionRole);
     return;
  	}
   if (!valores.contains('+') && !valores.contains('*')){
	   valor=valores.toDouble(&ok);
	   
   }else{
   	QStringList val = valores.split('+',QString::SkipEmptyParts);
   	QStringList mas;
   	valor = 1;
    for (int i = 0; i < val.size(); ++i) {
     	mas = val.at(i).split('*',QString::SkipEmptyParts);
     	for (int j = 0; j < mas.size(); ++j){
     		if (mas.at(j) > 0){
     			valor*=mas.at(j).toDouble(&ok);
			} 
    	}
    	val[i]=valores.setNum(valor);
    	valor = 1;
    }
    valor = 0;
    for (int i = 0; i < val.size(); ++i){
    	if (val.at(i) > 0) valor+=val.at(i).toDouble(&ok);
   	}
   }
   if (ok)
      {
       int ndecimales=2;
       if (!decimales) ndecimales=0;
       if (comadecimal)
           ui.Tablaapuntes->item(fila,columna)->setText(
                    convacoma(QString( "%1" ).arg(
                                valor, 0, 'f',ndecimales ) ));
          else
           ui.Tablaapuntes->item(fila,columna)->setText(
                                QString( "%1" ).arg(
                                valor, 0, 'f',ndecimales ) );

       if (ui.checkAutoiva->isChecked()) comboIvaCambiado();
      }
    else
	         ui.Tablaapuntes->item(fila,columna)->setText("");
	
	ui.Tablaapuntes->item(fila,columna)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
   //connect(ui.Tablaapuntes,SIGNAL( cellChanged ( int , int )),this,
   //	SLOT(contenidocambiado(int,int )));

 }    


if (columna==2)
   {
     if (ui.Tablaapuntes->item(fila,3)!=0)
        {
         QString guarda;
         guarda=ui.Tablaapuntes->item(fila,columna)->text();
         ui.Tablaapuntes->item(fila,3)->setText("");
         ui.Tablaapuntes->item(fila,columna)->setText(guarda);
        }
     ui.Tablaapuntes->item(fila,16)->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
  }

if (columna==3)
   {
     if (ui.Tablaapuntes->item(fila,2)!=0)
      {
         QString guarda;
         guarda=ui.Tablaapuntes->item(fila,columna)->text();
         ui.Tablaapuntes->item(fila,2)->setText("");
         ui.Tablaapuntes->item(fila,columna)->setText(guarda);
      }
      ui.Tablaapuntes->item(fila,16)->setFlags(Qt::NoItemFlags);
   }

if (columna==12)
   {
     if(ui.Tablaapuntes->item(fila,13)!=0 && ui.Tablaapuntes->item(fila,14)!=0){
     	QDate fecha;
     	fecha.setYMD(ui.Tablaapuntes->item(fila,14)->text().toInt()
     	 ,ui.Tablaapuntes->item(fila,13)->text().toInt()
     	 ,ui.Tablaapuntes->item(fila,12)->text().toInt());
     	if(fecha.isValid()){
     		ui.CalendarioMes->setSelectedDate(fecha);
		}else{
			fecha = ui.CalendarioMes->selectedDate();
			ui.Tablaapuntes->item(fila,12)->setText(fecha.toString("dd"));
		}
     }
     if (ui.Tablaapuntes->item(fila,12)->text().length()==1){
		ui.Tablaapuntes->item(fila,12)->setText("0"+ui.Tablaapuntes->item(fila,12)->text());
	 }
   }

if (columna==13)
   {
     if(ui.Tablaapuntes->item(fila,12)!=0 && ui.Tablaapuntes->item(fila,14)!=0){
     	QDate fecha;
     	fecha.setYMD(ui.Tablaapuntes->item(fila,14)->text().toInt(),ui.Tablaapuntes->item(fila,13)->text().toInt()
     	,ui.Tablaapuntes->item(fila,12)->text().toInt());
     	if(fecha.isValid()){
     		ui.CalendarioMes->setSelectedDate(fecha);
    	}else{
			fecha = ui.CalendarioMes->selectedDate();
			ui.Tablaapuntes->item(fila,13)->setText(fecha.toString("MM"));
		}
	 }
     if (ui.Tablaapuntes->item(fila,13)->text().length()==1){
		ui.Tablaapuntes->item(fila,13)->setText("0"+ui.Tablaapuntes->item(fila,13)->text());
	 }
   }

actualizaestado();

ui.Tablaapuntes->setFocus();
// si estamos en el último campo (documento o código de imputación)
// pasar a la línea inferior, columna 0
 if (ui.Tablaapuntes->currentItem()==0) return;
 if (ui.Tablaapuntes->currentRow()>ui.Tablaapuntes->rowCount()-2) return;
 if (ui.Tablaapuntes->currentColumn()==3)
     { ui.Tablaapuntes->setCurrentCell(ui.Tablaapuntes->currentRow()+1,0); return;}
 if (conanalitica())
     {
       QString codcuenta=ui.Tablaapuntes->item(ui.Tablaapuntes->currentRow(),0)->text();
       if (escuentadegasto(codcuenta)
        || escuentadeingreso(codcuenta)) return;
     }

}//fin contenidocambiado


void tabla_asientos::posceldacambiada ( int row , int col, int previousRow, int previousColumn )
{
    backup();
    QString cadena;
    if (ui.Tablaapuntes->item(row,0)==0) ui.Tablaapuntes->setCurrentCell(ultimafila(),0);
      else
          if (ui.Tablaapuntes->item(row,0)->text().length()==0) 
        	ui.Tablaapuntes->setCurrentCell(ultimafila(),0);

    ui.CodigoEd->setText("");
    ui.NombreEd->setText("");
    ui.saldolineEdit->setText("");

    if (ui.Tablaapuntes->item(row,0)!=0)
        {
         ui.CodigoEd->setText(ui.Tablaapuntes->item(row,0)->text());
         existecodigoplan(ui.Tablaapuntes->item(row,0)->text(),&cadena);
         ui.NombreEd->setText(cadena);
         ui.saldolineEdit->setText("");

         if (col==16 && !escuentadegasto(ui.Tablaapuntes->item(row,0)->text())
              && !escuentadeingreso(ui.Tablaapuntes->item(row,0)->text()))
             ui.Tablaapuntes->setCurrentCell(previousRow,previousColumn);

         if (ui.Tablaapuntes->item(row,0)->text().length()>0) 
            {
             QString cadquery;
             cadquery="SELECT saldo from saldossubcuenta where codigo = '";
             cadquery+=ui.Tablaapuntes->item(row,0)->text();
             cadquery+="';";
             QSqlQuery query = ejecutarSQL(cadquery);
             if ( query.isActive() )
              {
               if (query.size()>0)
                 {
                   query.first();
                   bool ok;
                   double valor=query.value(0).toDouble(&ok);
                   if (ok )
                       {
                        ui.saldolineEdit->setText(formateanumero(valor,comadecimal,decimales));
                       }
                 }
               }
             }
         }
    if  (row>0 && ui.Tablaapuntes->item(row-1,0)==0)
        	ui.Tablaapuntes->setCurrentCell(ultimafila(),0);
        else
             if  (row>0 && ui.Tablaapuntes->item(row-1,0)->text().length()==0)
        		ui.Tablaapuntes->setCurrentCell(ultimafila(),0);

    if (ui.Tablaapuntes->item(row,0)!=0){
    	if ((escuentadeivasoportado(ui.Tablaapuntes->item(row,0)->text()) ||
	   		escuentadeivarepercutido(ui.Tablaapuntes->item(row,0)->text()))
	   		&& ui.Tablaapuntes->item(row,6)->text().length()>0)
	   		
			ui.actionImprimir->setEnabled(TRUE);
		else
			ui.actionImprimir->setEnabled(FALSE);
   	}
        

    if (conanalitica() && ui.Tablaapuntes->item(row,0)!=0){
    	if (escuentadegasto(ui.Tablaapuntes->item(row,0)->text()) ||
	   		escuentadeingreso(ui.Tablaapuntes->item(row,0)->text()))
	   		
		 	ui.actionImprimir->setEnabled(TRUE);
		else
			ui.actionImprimir->setEnabled(FALSE); 
   	}
       

    if (ui.Tablaapuntes->item(0,0)!=0 && cadasientoreal.length() > 0)
      {
       if (ui.Tablaapuntes->item(0,0)->text().length()>0 && !ui.actionPasarAEspera->isEnabled())
         ui.actionPasarAEspera->setEnabled(TRUE);
       if (ui.Tablaapuntes->item(0,0)->text().length()==0 && ui.actionPasarAEspera->isEnabled())
         ui.actionPasarAEspera->setEnabled(FALSE);
      } else ui.actionPasarAEspera->setEnabled(FALSE);
    
    if(ui.Tablaapuntes->item(row,12)!=0 && ui.Tablaapuntes->item(row,13)!=0
    	&& ui.Tablaapuntes->item(row,14)!=0)
    {
     	QDate fecha;
     	fecha.setYMD(ui.Tablaapuntes->item(row,14)->text().toInt()
     		,ui.Tablaapuntes->item(row,13)->text().toInt()
     		,ui.Tablaapuntes->item(row,12)->text().toInt());
     	
     	ui.CalendarioMes->setSelectedDate(fecha);
    }

}



int tabla_asientos::ultimafila()
{
  int veces=0;
  while (veces<ui.Tablaapuntes->rowCount ())
    {
      if (ui.Tablaapuntes->item(veces,0)==0) break;
      if (ui.Tablaapuntes->item(veces,0)->text().length()==0) break; 
      veces++;
    }
  if (veces==ui.Tablaapuntes->rowCount()) return veces-1;
 return veces;
}


void tabla_asientos::borralinea( void )
{
 int fila=ui.Tablaapuntes->currentRow();
 ui.Tablaapuntes->removeRow(fila);
 actualizaestado();
}


void tabla_asientos::borratodo()
{

   if (QMessageBox::question(
            this,
            tr("Tabla de asientos"),
            tr("¿ Desea borrar todo el contenido ?"),
            tr("&Sí"), tr("&No"),
            QString::null, 0, 1 ) ==1 )
                          return;

 ui.Tablaapuntes->clearContents();
 ui.lcds->reset();
 ui.actionIncorporar->setEnabled(FALSE);
 ui.actionPasarAEspera->setEnabled(FALSE);
 ui.actionImprimir->setEnabled(FALSE);
 ui.Tablaapuntes->setCurrentCell(0,0);

}

void tabla_asientos::incorporar()
{
    //Comprovamos las fechas de todas las entradas
    QSqlQuery query;
    QDate fecha = ui.CalendarioMes->selectedDate();
    QString caddia; caddia.setNum(fecha.day());
    QString cadmes; cadmes.setNum(fecha.month());
    QString cadanyo; cadanyo.setNum(fecha.year());
    int veces=0;
      while (veces<ultimafila())
      {
        fecha.setYMD(ui.Tablaapuntes->item(veces,14)->text().toInt(),
        			 ui.Tablaapuntes->item(veces,13)->text().toInt(),
        			 ui.Tablaapuntes->item(veces,12)->text().toInt());
        if (!fecha.isValid())
        {
	      if(QMessageBox::question( this, tr("Tabla de apuntes"),
             tr("ERROR: Fecha incompleta para ingresos/gastos en fila: ")
             +QString::number(veces)+tr("\nSe añadirá la fecha del calendario."),
             tr("&Aceptar"), tr("&Cancelar"),
             QString::null, 0, 1 ) ==1 )
	         	return;
	         else{
	              fecha.setYMD(cadanyo.toInt(),cadmes.toInt(),caddia.toInt());
	              ui.Tablaapuntes->item(veces,12)->setText(caddia);
	              ui.Tablaapuntes->item(veces,13)->setText(cadmes);
	              ui.Tablaapuntes->item(veces,14)->setText(cadanyo);
              }
        }
        if (fechadejerciciocerrado(fecha))
        {
        	QMessageBox::warning( this, tr("Tabla de apuntes"),
        	tr("ERROR: La fecha de la entrada %1 corresponde a un ejercicio cerrado").arg(veces+1));
        	return;
       	}
       	if (!fechacorrespondeaejercicio(fecha))
       	{
       		QMessageBox::warning( this, tr("Tabla de apuntes"),
       		tr("ERROR: La fecha de la entrada %1 no corresponde a ningún ejercicio definido").arg(veces+1));
        	return;
      	}
      	//Comprovamos que no se ha añadido ya el mismo pase en el libro
        if(existePase(veces,fecha,QString("%1").arg(fecha.weekNumber())) && !editando)
	    {
	    	QMessageBox::warning( this, tr("Tabla de apuntes"),
            tr("ERROR: La entrada %1 de la tabla ya existe en el Diario.\nLa entrada se BORRARÁ del diario si no se borra el pase del libro antes de Incorporar.").arg(veces+1));
            if (QMessageBox::question(
                     this,
                     tr("Tabla de apuntes"),
                     tr("¿ Desea borrar el pase en conflicto ?"),
                     tr("&Sí"), tr("&No"),
                     QString::null, 0, 1 ) ==1 )
                                   return;
            else{
                QString caddel;
                caddel="delete from libroiva where pase=";
                caddel+=ui.Tablaapuntes->item(veces,15)->text();
                query = ejecutarSQL(caddel);
                caddel="delete from diario where pase=";
                caddel+=ui.Tablaapuntes->item(veces,15)->text();
                query = ejecutarSQL(caddel);
                if (!query.isActive() && query.size() == 0)
                    QMessageBox::critical(this,tr("Tabla de apuntes"),tr("Ha habido un error al borrar el pase del diario. Es posible que el pase no exista en el libro de IVA o ya se haya borrado."));
                else
                    QMessageBox::information(this,tr("Tabla de apuntes"),tr("El pase %1 se ha borrado correctamente del diario.").arg(ui.Tablaapuntes->item(veces,15)->text()));

            }

            return;
    	}
    	
	    veces++;
      }

    // -------------------------------------------------------------
    QSqlDatabase contabilidad=QSqlDatabase::database();
    contabilidad.transaction();
    
    //if (ui.AsientoLabel->isEnabled()) incorporaedicion();
    
    /*QString cadquery;
    cadquery="LOCK TABLE configuracion WRITE,diario WRITE,saldossubcuenta WRITE";
    cadquery+=",libroiva WRITE,ejercicios WRITE;";
    ejecutarSQL(cadquery);
    */
    bloqueaTablasAsientos();
    
    qlonglong vnum=0;
    vnum=cadasientoreal.toLongLong();
    
    QString cadnum; cadnum.setNum(vnum+1);
    QString cadnumasiento; cadnumasiento.setNum(vnum);
    
    //if (!ui.AsientoLabel->isEnabled())
    ejecutarSQL("update configuracion set prox_asiento="+cadnum);
    
    query = ejecutarSQL("select prox_pase from configuracion;");
    qlonglong vnum2=0;
    if ( query.isActive() )
    {
      if (query.next())
         {
           vnum2=query.value(0).toLongLong();
           if (vnum2==0) vnum2=1;
         }else vnum2=1;
    }else vnum2=1;
    
        
    int fila=0;

    QString cadnumpase,cad1;
    qlonglong pase=vnum2;
	
	if (cadasientoreal.length()>0){
		//borramos las entradas existentes en el diario de la semana actual
		borraAsientoEjercicio(cadnumasiento,ejerciciodelafecha(fecha));
	}
	
    while (fila<ultimafila())
    {
	    
	    fecha.setYMD(ui.Tablaapuntes->item(fila,14)->text().toInt(),
        			 ui.Tablaapuntes->item(fila,13)->text().toInt(),
        			 ui.Tablaapuntes->item(fila,12)->text().toInt());
        //Para entradas sin semana definida y para semana 53
        if (cadasientoreal.length()==0){
	        int semana = fecha.weekNumber();
	        cadnumasiento.setNum(semana);
	        if (semana == 1){
	        	if (ejerciciodelafecha(fecha) != ejerciciodelafecha(fecha.addDays(8)))
	        		cadnumasiento.setNum(semana+52);
        	}
       	}
        ///////////////////////////////////////////////////////
	    //Ajuste contador de pases
        if(ui.Tablaapuntes->item(fila,15)->text().length()==0){
	    	cadnumpase.setNum(pase);
	    	pase++;
	    }else{
	    	cadnumpase = ui.Tablaapuntes->item(fila,15)->text();
    	}
	    ////////////////////////////////////////////////////
        cad1="INSERT into diario (asiento,pase,fecha,cuenta,debe,haber,concepto,documento,"
                 "diario,usuario,ci) VALUES(";
	    cad1+=cadnumasiento;
	    cad1+=",";
	    cad1+=cadnumpase;
	    cad1+=",'";
	    
             cad1+=ui.Tablaapuntes->item(fila,14)->text();//cadanyo;
             cad1+="/";
             cad1+=ui.Tablaapuntes->item(fila,13)->text();//cadmes;
             cad1+="/";
             cad1+=ui.Tablaapuntes->item(fila,12)->text();//caddia;
             cad1+="','";
	
	     cad1+=ui.Tablaapuntes->item(fila,0)->text();
	     cad1+="',";
	     if (ui.Tablaapuntes->item(fila,2)->text().length()==0) cad1+="0";
	       else cad1+=convapunto(ui.Tablaapuntes->item(fila,2)->text());
	     cad1+=",";
	     if (ui.Tablaapuntes->item(fila,3)->text().length()==0) cad1+="0";
	       else cad1+=convapunto(ui.Tablaapuntes->item(fila,3)->text());
	     cad1+=",'";
	     cad1+=ui.Tablaapuntes->item(fila,1)->text().replace("'","''");
	     cad1+="','";
	     cad1+=ui.Tablaapuntes->item(fila,4)->text().replace("'","''");
	
             cad1+="','";
             //if (ui.ClaveivaComboBox->currentText()!=diario_no_asignado())
             //   cad1+=ui.ClaveivaComboBox->currentText();
             cad1+="',";
             cad1+="CURRENT_USER,'";
             cad1+=ui.Tablaapuntes->item(fila,16)->text();
             cad1+="');";

             ejecutarSQL(cad1);
	      
             QString cadq2;
             //QSqlQuery query2;
             cadq2="update saldossubcuenta set saldo=saldo+";
             if (ui.Tablaapuntes->item(fila,16)->text().length()==0)
             {
             	
             	if (ui.Tablaapuntes->item(fila,2)->text().length()==0) cadq2+="0";
	         	else cadq2+=convapunto(ui.Tablaapuntes->item(fila,2)->text());
         	 }else{
         	 	cadq2+="0";
        	 }
             cadq2+="-";
             if (ui.Tablaapuntes->item(fila,3)->text().length()==0) cadq2+="0";
	         else cadq2+=convapunto(ui.Tablaapuntes->item(fila,3)->text());
             cadq2+=" where codigo='";
             cadq2+= ui.Tablaapuntes->item(fila,0)->text();
             cadq2+="';";
             ejecutarSQL(cadq2);
	   
	
	    // Examinamos columnas para el libroiva
	    if (ui.Tablaapuntes->item(fila,6)->text().length()>0)
	     {
	     //la cuenta del diario se copia a la cuenta del libro IVA
	     ui.Tablaapuntes->item(fila,11)->setText(ui.Tablaapuntes->item(fila,0)->text());
	     cad1="INSERT into libroiva (pase,cta_base_iva,base_iva,clave_iva,tipo_iva,tipo_re,";
	     cad1+="cuota_iva,cuenta_fra,fecha_fra,soportado,aib,eib) VALUES(";
	     cad1+=cadnumpase;
	     cad1+=",'";
	     cad1+=ui.Tablaapuntes->item(fila,5)->text(); // cta_base_iva
	     cad1+="',";
	     cad1+=convapunto(ui.Tablaapuntes->item(fila,6)->text()); // base_iva
	     cad1+=",'";
	     cad1+=ui.Tablaapuntes->item(fila,7)->text(); // clave_iva
	     cad1+="',";
	     if (ui.Tablaapuntes->item(fila,8)->text().length()==0) cad1+="0"; // tipo_iva
	       else cad1+=convapunto(ui.Tablaapuntes->item(fila,8)->text());
	     cad1+=",";
  	     if (ui.Tablaapuntes->item(fila,9)->text().length()==0) cad1+="0"; // tipo_re
	       else cad1+=convapunto(ui.Tablaapuntes->item(fila,9)->text());
	     cad1+=",";
	     cad1+=convapunto(ui.Tablaapuntes->item(fila,10)->text()); // cuota_iva
	     cad1+=",'";
	     cad1+=ui.Tablaapuntes->item(fila,11)->text(); // cuenta_fra
	     cad1+="','";
	     cad1+=ui.Tablaapuntes->item(fila,14)->text();
	     cad1+="/";
	     cad1+=ui.Tablaapuntes->item(fila,13)->text();
	     cad1+="/";
	     cad1+=ui.Tablaapuntes->item(fila,12)->text();
	     cad1+="',";
	     //if (ui.Tablaapuntes->item(fila,15)->text()=="1") cad1+="TRUE"; else cad1+="FALSE";
	     cad1+="TRUE";
	     //
	     cad1+=",";
	     //if (ui.aibcheckBox->isChecked()) cad1+="TRUE"; else cad1+="FALSE";
	     cad1+="FALSE,";
	     //if (ui.eibcheckBox->isChecked()) cad1+="TRUE"; else cad1+="FALSE";
	     cad1+="FALSE);";
         ejecutarSQL(cad1);
	 }
		
	//pase++;
	//ui.Tablaapuntes->removeRow(fila);
	fila++;
    }
    
    cadnumpase.setNum(pase);
    ejecutarSQL("update configuracion set prox_pase="+cadnumpase);
    calculaprimerasientoejercicio(ejerciciodelafecha(ui.CalendarioMes->selectedDate()));
    //contabilidad.commit();
    desbloqueaTablas();
    pasarEspera(FALSE);
    
    accept();
}

void tabla_asientos::incorporaEdicion()
{
    ui.actionIncorporar->setEnabled(TRUE);
    editando = false;
  
}


void tabla_asientos::pasanumasiento( QString  cadasiento)
{
  //if (numeracionrelativa()) ui.AsientolineEdit->setText(numrelativa(cadasiento));
  //  else ui.AsientolineEdit->setText(cadasiento);
  cadasientoreal=cadasiento;
  setWindowTitle(tr("tabla apuntes")+" - "+tr("Semana")+":"+cadasientoreal);
}

void tabla_asientos::botonesperapulsado(){
	//QString cadquery="delete from borrador where asiento=";
	//cadquery+=cadasientoreal;
	//QSqlQuery query(cadquery);
	pasarEspera(TRUE);
	cancelar();
}

void tabla_asientos::pasarEspera(bool guardar)
{
    QSqlDatabase contabilidad=QSqlDatabase::database();
    contabilidad.transaction();
    
    QString cadquery;
    //cadquery="LOCK TABLE borrador WRITE;";
    //ejecutarSQL(cadquery);
    //bloqueaTabla("borrador");
    
    cadquery="delete from borrador where asiento='";
	cadquery+=cadasientoreal;
	cadquery+="'";
	ejecutarSQL(cadquery);
    //query.exec("select max(asiento) from borrador;");
	
	if (!guardar) return;
    
    //int vnum=0;
    /*if ( query.isActive() )
    {
      if (query.next())
         {
           vnum=query.value(0).toInt()+1;
           } else vnum=1;
    } else vnum=1;
    */        
    QString cadnum;
    //cadnum.setNum(vnum);
    //el numero de asiento corresponde a una semana
    cadnum=cadasientoreal;
    QString cad1("insert into borrador ( asiento,  usuario");
    int fila=0;
    while (fila<ultimafila())
    {
	ejecutarSQL(cad1 +  ",cuenta, concepto, debe, haber,"+
      "documento, ctabaseiva, baseiva,"+" claveiva, tipoiva, tipore, cuotaiva, "+
	  "cuentafra,diafra, mesfra, anyofra, soportado, ci ) VALUES  ('"+ cadnum + "',"+
	  "CURRENT_USER,'"+ui.Tablaapuntes->item(fila,0)->text()+"','"+
	  ui.Tablaapuntes->item(fila,1)->text()+"','"+
	  convapunto(ui.Tablaapuntes->item(fila,2)->text())+"','"+ //debe
	  convapunto(ui.Tablaapuntes->item(fila,3)->text())+"','"+ //haber
	  ui.Tablaapuntes->item(fila,4)->text()+"','"+ //documento
	  ui.Tablaapuntes->item(fila,5)->text()+"','"+ //ctabaseiva
	  convapunto(ui.Tablaapuntes->item(fila,6)->text())+"','"+ //baseiva
	  ui.Tablaapuntes->item(fila,7)->text()+"','"+ //claveiva
	  convapunto(ui.Tablaapuntes->item(fila,8)->text())+"','"+ //tipoiva
	  convapunto(ui.Tablaapuntes->item(fila,9)->text())+"','"+ //tipore
	  convapunto(ui.Tablaapuntes->item(fila,10)->text())+"','"+ //cuotaiva
	  ui.Tablaapuntes->item(fila,11)->text()+"','"+ //cuentafra
	  ui.Tablaapuntes->item(fila,12)->text()+"','"+ //diafra
	  ui.Tablaapuntes->item(fila,13)->text()+"','"+ //mesfra
	  ui.Tablaapuntes->item(fila,14)->text()+"','"+ //anyofra
	  ui.Tablaapuntes->item(fila,15)->text()+"','"+ //soportado(pase)
	  ui.Tablaapuntes->item(fila,16)->text()+"');"); //ci(fecha pago)
	fila++;
    }
   contabilidad.commit();
   //desbloqueaTablas();
   //borratodo();
}


void tabla_asientos::pegar()
{
	QString texto;
    
    int fila=ui.Tablaapuntes->currentRow();
	//if (DEBUG) QMessageBox::warning(this, tr("Debug"), "Fila actual: "+texto.setNum(fila));
	if (fila >= ultimafila())
		rellenaLinea(fila,TRUE);
	QClipboard *cb = QApplication::clipboard();
    texto = cb->text(QClipboard::Clipboard);
    if ( !texto.isNull() && texto.length()<80 && !texto.contains("\t"))
      {
        if (ui.Tablaapuntes->currentColumn()==2 || ui.Tablaapuntes->currentColumn()==3)
            {
	     if (comadecimal) texto=convacoma(texto); 
            }
       ui.Tablaapuntes->item(ui.Tablaapuntes->currentRow(),ui.Tablaapuntes->currentColumn())->setText(texto);
       
      }
}

void tabla_asientos::mayor()
{

  if (ui.CodigoEd->text().length()>0)
            {
               QString subcuenta="";
               QDate fecha;
               consmayor *elmayor=new consmayor(comadecimal,decimales);
 	       subcuenta=ui.CodigoEd->text();
	       fecha=ui.CalendarioMes->selectedDate();
	       elmayor->pasadatos(subcuenta,fecha);
               elmayor->exec();
               elmayor->~consmayor();
            }

}


void tabla_asientos::pasadatos( int fila, QString col0, QString col1, QString col2, QString col3, QString col4, QString col5, QString col6, QString col7, QString col8, QString col9, QString col10, QString col11, QString col12, QString col13, QString col14, QString col15, QString col16 )
{
    ui.Tablaapuntes->disconnect(SIGNAL( itemChanged (QTableWidgetItem *)));
    
    rellenaLinea(fila,col16.isEmpty());
    
  ui.Tablaapuntes->item(fila,0)->setText(col0);
  ui.Tablaapuntes->item(fila,1)->setText(col1);

  QString cadnum;

  double num=convapunto(col2).toDouble();
  if (num<-0.001 || num>0.001)
     {
      cadnum=formateanumero(num,comadecimal,decimales);
      ui.Tablaapuntes->item(fila,2)->setText(cadnum);
     }
  num=convapunto(col3).toDouble();
  if (num<-0.001 || num>0.001)
     {
      cadnum=formateanumero(num,comadecimal,decimales);
      ui.Tablaapuntes->item(fila,3)->setText(cadnum);
     }
  ui.Tablaapuntes->item(fila,4)->setText(col4);
  ui.Tablaapuntes->item(fila,5)->setText(col5);

  num=convapunto(col6).toDouble();
  if (num>0.001)
      {
       cadnum=formateanumero(num,comadecimal,decimales);
       ui.Tablaapuntes->item(fila,6)->setText(cadnum);
      }
  ui.Tablaapuntes->item(fila,7)->setText(col7);

  num=convapunto(col8).toDouble();
  cadnum=formateanumero(num,comadecimal,decimales);
  ui.Tablaapuntes->item(fila,8)->setText(cadnum);

  num=convapunto(col9).toDouble();
  cadnum=formateanumero(num,comadecimal,decimales);
  ui.Tablaapuntes->item(fila,9)->setText(cadnum);

  num=convapunto(col10).toDouble();
  cadnum=formateanumero(num,comadecimal,decimales);
  ui.Tablaapuntes->item(fila,10)->setText(cadnum);

  ui.Tablaapuntes->item(fila,11)->setText(col11);
  ui.Tablaapuntes->item(fila,12)->setText(col12);
  ui.Tablaapuntes->item(fila,13)->setText(col13);
  ui.Tablaapuntes->item(fila,14)->setText(col14);
  ui.Tablaapuntes->item(fila,15)->setText(col15);
  ui.Tablaapuntes->item(fila,16)->setText(col16);
  ui.Tablaapuntes->item(fila,16)->setToolTip(col16);
  connect(ui.Tablaapuntes,SIGNAL( itemChanged (QTableWidgetItem *)),this,
           SLOT(itemCambiado( QTableWidgetItem *)));
 
}


void tabla_asientos::pasaFechaInicial( QDate lafecha)
{
 ui.CalendarioMes->setMinimumDate(lafecha);
 ui.CalendarioMes->setSelectedDate(lafecha);
 int dia;
 for(dia = 4; dia < 20; dia++){
 	if(lafecha.addDays(dia).dayOfWeek() == Qt::Monday)
 		break;
 }
 ui.CalendarioMes->setMaximumDate(lafecha.addDays(dia-1));
}

void tabla_asientos::pasaFechasAsiento( QDate fechaini, QDate fechafin)
{
	if (fechaini.isValid()) ui.CalendarioMes->setMinimumDate(fechaini);
	if (fechafin.isValid()) ui.CalendarioMes->setMaximumDate(fechafin);
}

void tabla_asientos::pasadiario(QString qdiario)
{
 for (int veces=0; veces < ui.ClaveivaComboBox->count(); veces++)
     {
       if (ui.ClaveivaComboBox->itemText(veces)==qdiario) ui.ClaveivaComboBox->setCurrentIndex(veces);
     }
}


void tabla_asientos::pasadatos1( int fila, QString col0, QString col1, QString col2,
                                 QString col3, QString col4, QDate fecha, QString col15, QString col16)
{
	rellenaLinea(fila,col16.isEmpty());
    
  ui.Tablaapuntes->item(fila,0)->setText(col0);
  ui.Tablaapuntes->item(fila,1)->setText(col1);

 QString cadnum;
  double num=convapunto(col2).toDouble();
  if (num<-0.001 || num>0.001)
      {
       cadnum=formateanumero(num,comadecimal,decimales);
       ui.Tablaapuntes->item(fila,2)->setText(cadnum);
      }
  num=convapunto(col3).toDouble();
  if (num<-0.001 || num>0.001)
      {
       cadnum=formateanumero(num,comadecimal,decimales);
       ui.Tablaapuntes->item(fila,3)->setText(cadnum);
      }
  ui.Tablaapuntes->item(fila,4)->setText(col4);
  ui.Tablaapuntes->item(fila,12)->setText(fecha.toString("dd"));
  ui.Tablaapuntes->item(fila,13)->setText(fecha.toString("MM"));
  ui.Tablaapuntes->item(fila,14)->setText(fecha.toString("yyyy"));
  ui.Tablaapuntes->item(fila,15)->setText(col15);
  ui.Tablaapuntes->item(fila,16)->setText(col16);
  ui.Tablaapuntes->item(fila,16)->setToolTip(ui.Tablaapuntes->item(fila,12)->text()+
  											"-"+ui.Tablaapuntes->item(fila,13)->text()+
  											"-"+ui.Tablaapuntes->item(fila,14)->text());

}


void tabla_asientos::pasadatos2(int fila, QString col5, QString col6, QString col7, QString col8, QString col9, QString col10, QString col11, QString col15)
{
   //RellenaLinea(fila,FALSE);
    
  ui.Tablaapuntes->item(fila,5)->setText(col5);

  double num=convapunto(col6).toDouble();
  QString cadnum=formateanumero(num,comadecimal,decimales);
  ui.Tablaapuntes->item(fila,6)->setText(cadnum);

  ui.Tablaapuntes->item(fila,7)->setText(col7);

  num=convapunto(col8).toDouble();
  cadnum=formateanumero(num,comadecimal,decimales);
  ui.Tablaapuntes->item(fila,8)->setText(cadnum);

  num=convapunto(col9).toDouble();
  cadnum=formateanumero(num,comadecimal,decimales);
  ui.Tablaapuntes->item(fila,9)->setText(cadnum);

  num=convapunto(col10).toDouble();
  if (num<-0.001 || num>0.001)
  	{
  		cadnum=formateanumero(num,comadecimal,decimales);
  		ui.Tablaapuntes->item(fila,10)->setText(cadnum);
 	}
  ui.Tablaapuntes->item(fila,11)->setText(col11);
  ui.Tablaapuntes->item(fila,15)->setText(col15);

}

void tabla_asientos::activaparaedicion()
{
  ui.actionIncorporar->setEnabled(TRUE);
  editando = true;
  //ui.Tablaapuntes->showColumn(15);//pase
  //ui.AsientoLabel->setEnabled(TRUE);
  //ui.AsientolineEdit->setEnabled(TRUE);
}

void tabla_asientos::actualizaestado()
{
// Escribimos número en LCD de debe
double debe0=0;
double debe1=0;
double sumadebe=0;
double valor=0;
//double valor1=0;
double sumahaber=0;
bool ok0=false;
bool ok1=false;
for (int veces=0;veces<ui.Tablaapuntes->rowCount();veces++)
{
	if (ui.Tablaapuntes->item(veces,0)==0) break;
	ok0 = ok1 = false;
	valor = 0;
	//DEBES
	if (ui.Tablaapuntes->item(veces,2)->text().length()>0)
		valor=convapunto(ui.Tablaapuntes->item(veces,2)->text()).toDouble(&ok0);
	if (ok0 && escuentadegasto(ui.Tablaapuntes->item(veces,0)->text())) debe0+=valor;
	if (ok0 && esCuentadeGenero(ui.Tablaapuntes->item(veces,0)->text())) debe1+=valor;
	//HABERES
	if (ui.Tablaapuntes->item(veces,3)->text().length()>0)
		valor=convapunto(ui.Tablaapuntes->item(veces,3)->text()).toDouble(&ok1);
	if (ok1 && escuentadeingreso(ui.Tablaapuntes->item(veces,0)->text())) sumahaber+=valor;
	/*if ((ok0 && valor == 0)||(ok1 && valor == 0)){
		QMessageBox::warning( this, tr("Tabla de apuntes"),
		tr("ERROR: El valor de la entrada %1 no puede ser nulo").arg(veces+1));

		ui.actionIncorporar->setEnabled(FALSE);
		return;
	}*/
}
sumadebe=debe0;

ui.lcds->pasaValores(debe1,sumadebe,sumahaber,decimales);
 
 if (cadasientoreal.length()>0){
	 if ((sumadebe>0.0001 || sumadebe<-0.0001)
         || (sumahaber>0.0001 || sumahaber<-0.0001))
	 { ui.actionIncorporar->setEnabled(TRUE);
	     // ui.BotonIncorporar->setFocus();
	     return;
	 }
	     else ui.actionIncorporar->setEnabled(FALSE);
 }
}

void tabla_asientos::chequeatotales(){
	actualizaestado();
}

bool tabla_asientos::botonincorporaractivado()
{
  if (ui.actionIncorporar->isEnabled()) return true;
    else return false;
}


void tabla_asientos::fechacambiada()
{

QString cadena;
QDate fecha = ui.CalendarioMes->selectedDate();
QString caddia; caddia.setNum(fecha.day());
QString cadmes; cadmes.setNum(fecha.month());
QString cadanyo; cadanyo.setNum(fecha.year());
if (caddia.length()==1){
	caddia="0"+caddia;
}
if (cadmes.length()==1){
	cadmes="0"+cadmes;
}
int fila=ui.Tablaapuntes->currentRow();
//if (DEBUG) QMessageBox::warning(this, tr("Debug"), "Fila actual: "+cadena.setNum(fila));

if (ui.Tablaapuntes->item(fila,0)==0) rellenaLinea(fila,TRUE);

if (fila != -1)
	{
	 ui.Tablaapuntes->item(fila,12)->setText(caddia);
	 ui.Tablaapuntes->item(fila,13)->setText(cadmes);
	 ui.Tablaapuntes->item(fila,14)->setText(cadanyo);
	}
actualizaestado();

  if (fechadejerciciocerrado(ui.CalendarioMes->selectedDate()) || !fechacorrespondeaejercicio(ui.CalendarioMes->selectedDate()))
  {
  	QMessageBox::warning( this, tr("Tabla de apuntes"),
    	tr("ERROR: La fecha de la entrada %1 no corresponde a un ejercicio activo").arg(fila+1));
        	
  	ui.actionIncorporar->setEnabled(FALSE);
  }
  //else
  //	ui.actionIncorporar->setEnabled(TRUE);
  if (ui.Tablaapuntes->item(fila,0)->text().length()==0) ui.Tablaapuntes->item(fila,0)->setText("");
}

void tabla_asientos::comboIvaCambiado()
{
	int fila=ui.Tablaapuntes->currentRow();
	QString cadenaiva=ui.ClaveivaComboBox->currentText();
	if (cadenaiva == diario_no_asignado()){
		if (ui.Tablaapuntes->item(fila,0)!=0){
			for(int i=6;i<12;i++)
				ui.Tablaapuntes->item(fila,i)->setText("");
		}
		return;
	}
	bool bien;
	double bi,re;
	double base;
	QString cadena;
	if (cadenaiva == iva_mixto()){
		if (ui.Tablaapuntes->item(fila,0)!=0){
			for(int i=6;i<12;i++)
				ui.Tablaapuntes->item(fila,i)->setText("");
		}
		pidenombre *iva = new pidenombre();
		iva->asignanombreventana(tr("Introducir valor"));
		iva->asignaetiqueta(tr("Cuota IVA:"));
		int resultado = iva->exec();
   		bi = calculaValor( iva->contenido() );
   		if (!resultado==QDialog::Accepted) return;
   		if (bi <= 0){
   			QMessageBox::critical(this,tr("Tabla de apuntes"),
   						tr("ERROR: Debe introducir un valor u operación correctos"));
   			return;
  		}
		iva->asignaetiqueta(tr("Cuota RE:"));
                iva->setContenido(cadena.setNum(bi,'f',2));
		resultado = iva->exec();
   		re = calculaValor( iva->contenido() );
   		if (!resultado==QDialog::Accepted) return;
   		if (re <= 0 || re == bi){
   			QMessageBox::warning(this,tr("Tabla de apuntes"),
   						tr("El valor del RE se establecerá en zero (0.00)"));
   			re = 0.0;
  		}
		if (ui.Tablaapuntes->item(fila,0)==0) rellenaLinea(fila,TRUE);
		base = convapunto(ui.Tablaapuntes->item(fila,2)->text()).toDouble()
			  +convapunto(ui.Tablaapuntes->item(fila,3)->text()).toDouble();
		if (base >= 0)
			base = base-bi-re;
		else
			base = base+bi+re;
		ui.Tablaapuntes->item(fila,7)->setText(iva_mixto());
		if (decimales) cadena.setNum(bi,'f',2);
		else cadena.setNum(bi,'f',0);
		if (comadecimal) ui.Tablaapuntes->item(fila,10)->setText(convacoma(cadena));
		else ui.Tablaapuntes->item(fila,10)->setText(cadena);
		if (decimales) cadena.setNum(base,'f',2);
		else cadena.setNum(base,'f',0);
		if (comadecimal) ui.Tablaapuntes->item(fila,6)->setText(convacoma(cadena));
		else ui.Tablaapuntes->item(fila,6)->setText(cadena);
		return;
	}
	QString extracto=cadenaiva.section(':',1,1);
	QString recargo=cadenaiva.section(':',2,2);
	QString clave=cadenaiva.section("//",0,0);
	if (ui.Tablaapuntes->item(fila,0)==0) rellenaLinea(fila,TRUE);
	if (fila != -1){
		ui.Tablaapuntes->item(fila,7)->setText(clave.remove(' '));
		ui.Tablaapuntes->item(fila,8)->setText(extracto.remove(tr(" RE")));
		ui.Tablaapuntes->item(fila,9)->setText(recargo);
	}
	
	//if (DEBUG) QMessageBox::warning(this, tr("Debug"), "Iva+re: "+extracto.remove(tr(" RE"))+"+"+recargo);
		
	bi = convapunto(ui.Tablaapuntes->item(fila,2)->text()).toDouble(& bien);
	if (!bien) bi=0;
	double bi2 = convapunto(ui.Tablaapuntes->item(fila,3)->text()).toDouble(& bien);
	if (!bien) bi2=0;
	double tipo = convapunto(ui.Tablaapuntes->item(fila,8)->text()).toDouble(& bien)/100;
	if (!bien) tipo=0;
	re = convapunto(ui.Tablaapuntes->item(fila,9)->text()).toDouble(& bien)/100;
	if (!bien) re=0;
	base = (bi+bi2)/(tipo+re+1);
	//valor base
	if (decimales)
		cadena.setNum(base,'f',2);
	else cadena.setNum(base,'f',0);
    if (comadecimal) ui.Tablaapuntes->item(fila,6)->setText( convacoma(cadena));
    else ui.Tablaapuntes->item(fila,6)->setText(cadena);
	//valor iva
	if (decimales)
		cadena.setNum(base*tipo,'f',2);
	else cadena.setNum(base*tipo,'f',0);
    if (comadecimal) ui.Tablaapuntes->item(fila,10)->setText( convacoma(cadena));
    else ui.Tablaapuntes->item(fila,10)->setText(cadena);
	
}

void tabla_asientos::imprimirAsiento(){
	pasarEspera(TRUE);
	imprimediario *impres=new imprimediario();
   impres->pasafiltro( "asiento='"+cadasientoreal+"'" );
   impres->pasaTabla("borrador");
   impres->setWindowIcon(ui.actionImprimir->icon());
   impres->exec();
   impres->~imprimediario();
}

void tabla_asientos::cancelar()
{
   if (QMessageBox::question(
            this,
            tr("Tabla de asientos"),
            tr("¿ Desea salir y cancelar la edición ?"),
            tr("&Sí"), tr("&No"),
            QString::null, 0, 1 ) ==0 )
                          reject();
}

int tabla_asientos::existePase(int fil, QDate date, QString semana)
{
	QString importe;
	importe.setNum(calculaValor(ui.Tablaapuntes->item(fil,2)->text()+"+"+ui.Tablaapuntes->item(fil,3)->text()));
	return existePaseDiario(semana,date,ui.Tablaapuntes->item(fil,0)->text(),importe);
}

