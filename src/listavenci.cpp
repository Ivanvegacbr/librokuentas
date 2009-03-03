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

#include "listavenci.h"
#include "basedatos.h"
//#include "funciones.h"
//#include <QSqlRecord>
#include "buscasubcuenta.h"
#include "introfecha.h"
#include "editapaseconci.h"


CustomSqlModel5::CustomSqlModel5(QObject *parent)
        : QSqlTableModel(parent)
    {
     comadecimal=haycomadecimal(); decimales=haydecimales();
    }


QVariant CustomSqlModel5::datagen(const QModelIndex &index, int role) const
    {
        QVariant value = QSqlQueryModel::data(index, role);
        return value;
    }

QVariant CustomSqlModel5::data(const QModelIndex &index, int role) const
    {
        QString vacio;
        QVariant value = QSqlQueryModel::data(index, role);
        if (value.isValid() && role == Qt::DisplayRole) {
            if (index.column() == 3)
            {
            	return value.fromValue(descripcioncuenta(value.toString()));
           	}
            //if (index.column() == 9)
            //	return value.toString();
            
            if (index.column() == 2 || index.column() == 9)
               {
                return value.toDate().toString(Qt::SystemLocaleDate);
               }
            
            if (index.column() == 4 || index.column() == 5)
	       {
   	        if (value.toDouble()<0.0001 && value.toDouble()>-0.0001)
                   return value.fromValue(vacio);
                else
                      {
                        return value.fromValue(formateanumerosep(value.toDouble(),comadecimal, decimales));
                      }
	       }
        }
        if (role == Qt::TextAlignmentRole && (index.column() == 4 || index.column() == 5))
            return qVariantFromValue(int(Qt::AlignVCenter | Qt::AlignRight));
        if (role == Qt::TextAlignmentRole && (index.column()==2 || index.column()==9))
            return qVariantFromValue(int(Qt::AlignCenter));
        if (role == Qt::TextColorRole && index.column() == 4)
        	return qVariantFromValue(QColor(Qt::darkBlue));
        if (role == Qt::TextColorRole && index.column() == 5)
        	return qVariantFromValue(QColor(Qt::darkRed));
        return value;
    }




listavenci::listavenci() : QDialog() {
    ui.setupUi(this);

    CustomSqlModel5 *elmodelo = new CustomSqlModel5;
    model = elmodelo;
    comadecimal=haycomadecimal(); decimales=haydecimales();
        
    model->setTable("diario");
    model->setHeaderData(0, Qt::Horizontal, tr("asiento"));
    model->setHeaderData(1, Qt::Horizontal, tr("pase"));
    model->setHeaderData(2, Qt::Horizontal, tr("fecha"));
    model->setHeaderData(3, Qt::Horizontal, tr("cuenta"));
    model->setHeaderData(4, Qt::Horizontal, tr("debe"));
    model->setHeaderData(5, Qt::Horizontal, tr("haber"));
    model->setHeaderData(6, Qt::Horizontal, tr("concepto"));
    model->setHeaderData(7, Qt::Horizontal, tr("documento"));
    model->setHeaderData(8, Qt::Horizontal, tr("diario"));
    model->setHeaderData(9, Qt::Horizontal, tr("pago"));
    model->setHeaderData(10, Qt::Horizontal, tr("usuario"));
     
	ui.latablavencipase->setEditTriggers (QAbstractItemView::NoEditTriggers);
     // ui.latablavencipase->setEditable(FALSE);
     ui.latablavencipase->setSortingEnabled(TRUE);

     ui.latablavencipase->setModel(model);
     ui.latablavencipase->setAlternatingRowColors ( true);

     ui.latablavencipase->setColumnHidden(0,true);
     ui.latablavencipase->setColumnHidden(1,true);
     //ui.latablavencipase->setColumnHidden(3,true);
     //ui.latablavencipase->setColumnHidden(5,true);
     ui.latablavencipase->setColumnHidden(6,true);
     //ui.latablavencipase->setColumnHidden(7,true);
     ui.latablavencipase->setColumnHidden(8,true);
     //ui.latablavencipase->setColumnHidden(9,true);
     ui.latablavencipase->setColumnHidden(10,true);
     ui.latablavencipase->setColumnHidden(11,true);
     ui.latablavencipase->setColumnHidden(12,true);
     ui.fechas->setCheckable(true);
     // model->select();
     refrescar();

     ui.latablavencipase->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui.latablavencipase->setSelectionMode(QAbstractItemView::ExtendedSelection);

     ui.latablavencipase->sortByColumn(2,Qt::AscendingOrder);
     
  connect(ui.cuentacheckBox,SIGNAL(stateChanged(int)),this,SLOT(cuentacheckBoxcambiado( int )));
  connect(ui.cuentalineEdit,SIGNAL(editingFinished ()),this,SLOT(trasctaordenante()));
  connect(ui.buscapushButton,SIGNAL( clicked()),this,SLOT(buscacuenta()));
  connect(ui.cuentalineEdit,SIGNAL(textChanged(QString)),this,SLOT(ctaordenantecambiada()));

  connect(ui.refrescapushButton,SIGNAL( clicked()),this,SLOT(refrescar()));

  connect(ui.infopushButton,SIGNAL( clicked()),this,SLOT(infovencipase()));

  connect(ui.procesapushButton,SIGNAL( clicked()),this,SLOT(procesar()));
  connect(ui.editapushButton,SIGNAL( clicked()),this,SLOT(editar()));
  connect(ui.anularpushButton,SIGNAL( clicked()),this,SLOT(anular()));
  
  connect(ui.imprimirButton,SIGNAL( clicked()),this,SLOT(imprimir()));
  
}


listavenci::~listavenci()
{
 ui.latablavencipase->~QTableView();
 model->~CustomSqlModel5();
}


void listavenci::refrescar()
{
 asignafiltro();
 model->select();
 calculasuma();
}

void listavenci::pasaSemana(QString qsem, QString ejer)
{
	ui.fechas->setSemana(qsem,ejer);
	refrescar();
}

void listavenci::pasaCuenta(QString subcuenta)
{
	ui.cuentacheckBox->setCheckState(Qt::Checked);
	ui.cuentalineEdit->setText(subcuenta);
	ctaordenantecambiada();
	refrescar();
}

void listavenci::cuentacheckBoxcambiado( int activado )
{
    if (activado) 
      { 
        ui.cuentalineEdit->setEnabled(TRUE);
        ui.descriplineEdit->setEnabled(TRUE);
        ui.buscapushButton->setEnabled(TRUE);
     }
    else
      { 
        ui.cuentalineEdit->setText("");
        ui.descriplineEdit->setText("");
        ui.cuentalineEdit->setEnabled(FALSE);
        ui.descriplineEdit->setEnabled(FALSE);
        ui.buscapushButton->setEnabled(FALSE);
        refrescar();
     }
}


void listavenci::trasctaordenante()
{
  QString cadena,codigo;
  cadena=expandepunto(ui.cuentalineEdit->text(),anchocuentas());
  if (cadnumvalido(cadena))
  	ui.cuentalineEdit->setText(cadena);
  else
  {
  	if(unicoCodigoSubcuenta(&codigo,cadena))
  		ui.cuentalineEdit->setText(codigo);
 	else
 		buscacuenta();
  }
}


void listavenci::ctaordenantecambiada()
{
    QString descrip;
   if(ui.cuentalineEdit->text().length()==anchocuentas())
     {
       if (existecodigoplan(ui.cuentalineEdit->text(),&descrip))
          ui.descriplineEdit->setText(descrip);
       else
          ui.descriplineEdit->setText("");
     }
     else ui.descriplineEdit->setText("");
}



void listavenci::buscacuenta()
{
    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.cuentalineEdit->text());
    int cod=labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();

    if (cod==QDialog::Accepted && cadena2.length()==anchocuentas()) ui.cuentalineEdit->setText(cadena2);
       else ui.cuentalineEdit->setText("");
    labusqueda->~buscasubcuenta();
}


void listavenci::asignafiltro()
{
  QString cadfiltro("position('");
  cadfiltro+=grupoGastos();
  cadfiltro+="' in cuenta)=1";//solo cuentas a pagar
  if (ui.fechas->isChecked())
     {
      cadfiltro+=" AND fecha>='";
      cadfiltro+=ui.fechas->fecha(interFechas::inicial).toString("yyyy.MM.dd");
      cadfiltro+="' and fecha<='";
      cadfiltro+=ui.fechas->fecha(interFechas::final).toString("yyyy.MM.dd");
      cadfiltro+="'";
     }
  if (ui.pendientescheckBox->isChecked() && !ui.procesadoscheckBox->isChecked())
    {
      if (cadfiltro.length()>0) cadfiltro+=" AND ";
      cadfiltro+="char_length(ci)=0";
    }
  if (ui.procesadoscheckBox->isChecked() && !ui.pendientescheckBox->isChecked())
    {
      if (cadfiltro.length()>0) cadfiltro+=" AND ";
      cadfiltro+="char_length(ci)>0";
    }
  if (!ui.procesadoscheckBox->isChecked() && !ui.pendientescheckBox->isChecked())
   {
      if (cadfiltro.length()>0) cadfiltro+=" AND ";
      cadfiltro+="char_length(ci)=0 and char_length(ci)>0";
   }

  if (ui.cuentacheckBox->isChecked())
    {
      if (cadfiltro.length()>0) cadfiltro+=" AND ";
      cadfiltro+="cuenta='";
      cadfiltro+=ui.cuentalineEdit->text();
      cadfiltro+="'";
    }
  //QMessageBox::information( this, tr("Vencimientos"),cadfiltro);
  model->setFilter(cadfiltro);
  
}


QString listavenci::paseActual()
{
  QString resultado="";
  if (!ui.latablavencipase->currentIndex().isValid()) return resultado;
  int fila=ui.latablavencipase->currentIndex().row();
  return model->record(fila).value("pase").toString();
}

QString listavenci::documentoActual()
{
  QString resultado="";
  if (!ui.latablavencipase->currentIndex().isValid()) return resultado;
  int fila=ui.latablavencipase->currentIndex().row();
  return model->record(fila).value("documento").toString();
}

QString listavenci::cuentaActual()
{
  QString resultado="";
  if (!ui.latablavencipase->currentIndex().isValid()) return resultado;
  int fila=ui.latablavencipase->currentIndex().row();
  return model->record(fila).value("cuenta").toString();
}

double listavenci::debeActual()
{
	if (!ui.latablavencipase->currentIndex().isValid()) return 0.0;
	int fila=ui.latablavencipase->currentIndex().row();
	return model->record(fila).value("debe").toDouble();
}

double listavenci::haberActual()
{
	if (!ui.latablavencipase->currentIndex().isValid()) return 0.0;
	int fila=ui.latablavencipase->currentIndex().row();
	return model->record(fila).value("haber").toDouble();
}

QDate listavenci::fechaActual()
{
	QDate nula;
	if (!ui.latablavencipase->currentIndex().isValid()) return nula;
	int fila=ui.latablavencipase->currentIndex().row();
	return model->record(fila).value("fecha").toDate();
}

void listavenci::infovencipase()
{
   QString cadena=paseActual();
   int fila=ui.latablavencipase->currentIndex().row();
   //QModelIndex ind = ui.latablavencipase->currentIndex();
   if (cadena.length()>0)
      {
       QString asiento=numAsiento(cadena);
       QString cad2="";
       if (numeracionrelativa()) cad2=tr("Asiento correspondiente: ")+numrelativa(asiento);
          else cad2=tr("Asiento correspondiente: ")+asiento;
       if (ui.procesadoscheckBox->isChecked())
          {
             //QDate f = model->datagen(ind,Qt::DisplayRole).toDate();
             QDate f = model->record(fila).value("ci").toDate();
             if(f.isValid()){//no funciona
	             cad2+=tr("\nPase vencimiento procesado: ");
		         cad2+=f.toString(Qt::SystemLocaleDate);
         	 }else{
         	 	cad2+=tr("\nPase vencimiento NO procesado.");
        	 }
         	     
          }
       cad2+=tr("\nCuenta ordenante: ");
       cad2+=model->record(fila).value("cuenta").toString();
       cadena.setNum(saldocuentaendiario(model->record(fila).value("cuenta").toString()));
       if (comadecimal) cadena=convacoma(cadena);
	   cad2+=tr("\nSaldo cuenta: ")+cadena;
       if (model->record(fila).value("concepto").toString().length()>0)
       	cad2+=tr("\nConcepto: ")+model->record(fila).value("concepto").toString();
       QMessageBox::information( this, tr("Vencimientos"),cad2);
      }
}


void listavenci::calculasuma()
{
  QString cadval;
  QString cons="select sum(debe-haber) from diario where ";
  cons+=model->filter();
  //cons+=" and derecho";
  double total=0;
  QSqlQuery query(cons);
  if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           total=query.value(0).toDouble();
         }
     }

  /*cons="select sum(haber) from diario where ";
  cons+=model->filter();
  //cons+=" and not derecho";

  query.exec(cons);
  if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           total-=query.value(0).toDouble();
         }
     }
*/
 ui.sumaimportelineEdit->setText(formateanumero(total,comadecimal,decimales));
}


void listavenci::procesar()
{
 introfecha *fci = new introfecha();
 QDate ci;
 double suma = 0;
 QItemSelectionModel *seleccion;
 seleccion=ui.latablavencipase->selectionModel();
 if (seleccion->hasSelection())
 {
 	QList<QModelIndex> listaPase;
 	QList<QModelIndex> listaFecha;
	QList<QModelIndex> listaCuenta;
	QList<QModelIndex> listaDoc;
	QList<QModelIndex> listaCi;
	QList<QModelIndex> listaDebe;
	listaPase=seleccion->selectedRows (1);
	listaFecha=seleccion->selectedRows (2);
	listaCuenta=seleccion->selectedRows (3);
	listaDebe=seleccion->selectedRows(4);
	listaDoc=seleccion->selectedRows (7);
	listaCi=seleccion->selectedRows (9);
	
    // comprobar fecha pase y fecha vencimiento
    if (listaPase.size()>1)
    {
    	for (int i = 0; i < listaPase.size(); ++i){
        	suma+=model->datagen(listaDebe.at(i),Qt::DisplayRole).toDouble();
        	if (!fechacorrespondeaejercicio(
        		model->datagen(listaFecha.at(i),Qt::DisplayRole).toDate()))
         	{
            	QMessageBox::warning( this, tr("Vencimientos"),tr("ERROR en procesar vencimientos: en la "
                        "selección hay fechas que no corresponden a ejercicios definidos"));
            	return;
         	}
      		if (model->datagen(listaCi.at(i),Qt::DisplayRole).toDate().isValid())
          	{
            	QMessageBox::warning( this, tr("Vencimientos"),tr("ERROR en procesar vencimientos: en la "
                        "selección hay vencimientos que ya han sido procesados"));
            	return;
          	}
        }
        if (QMessageBox::question(
            this,
            tr("Vencimientos"),
            tr("Total vencimientos: ")+formateanumero(suma,comadecimal,decimales)+"\n"+
            tr("Se van a procesar los vencimientos selecccionados.\n¿Desea continuar?"),
            tr("&Sí"), tr("&No"),
            QString::null, 0, 1 ) )
            return ;
        fci->fijarDiaMinimo(model->datagen(listaFecha.at(0),Qt::DisplayRole).toDate());
     	int resultado=fci->exec();
     	ci=fci->fecha();
     	fci->~introfecha();
     	if (!resultado==QDialog::Accepted) return;
     	for (int i = 0; i < listaPase.size(); ++i){
     		guardaFechaPago(
     			model->datagen(listaCuenta.at(i),Qt::DisplayRole).toString(),
     			model->datagen(listaPase.at(i),Qt::DisplayRole).toString(),
     			ci,model->datagen(listaDoc.at(i),Qt::DisplayRole).toString());
     			
    	}
    	QMessageBox::information( this, tr("Vencimientos"),
                             tr("Se han procesado los vencimientos seleccionados"));
     	refrescar();
   		return;
    }else{
    	QString pase=model->datagen(listaPase.at(0),Qt::DisplayRole).toString();
   		ci=model->datagen(listaCi.at(0),Qt::DisplayRole).toDate();
   		// está ya procesado ??: pendiente==FALSE ??
   		if (ci.isValid())
   		{
       		QMessageBox::warning( this, tr("Vencimientos"),tr("El vencimiento ya está procesado"));
       		return;
     	}else{
     		fci->fijarDiaMinimo(model->datagen(listaFecha.at(0),Qt::DisplayRole).toDate());
     		int resultado=fci->exec();
     		ci=fci->fecha();
     		fci->~introfecha();
     		if (!resultado==QDialog::Accepted) return;
     		//if (DEBUG) QMessageBox::warning( this, tr("Vencimientos"),
     		//		model->datagen(listaCuenta.at(0),Qt::DisplayRole).toString());
     		guardaFechaPago(model->datagen(listaCuenta.at(0),Qt::DisplayRole).toString(),
     			pase,ci,model->datagen(listaDoc.at(0),Qt::DisplayRole).toString());
    	 }
    	refrescar();
    }
 }else
         {
          QMessageBox::warning( this, tr("Vencimientos"),tr("ERROR en procesar vencimiento: no se ha "
                             "seleccionado ningún vencimiento"));
          return;
         }
}


void listavenci::anular()
{
   QString pase=paseActual();
   QString doc=documentoActual();
   QString cuenta=cuentaActual();
   QDate nula;
   if (pase.length()==0) return;
  // para marcar como anulado, no debe de estar procesado el vencimiento
   /*if (vencimientoprocesado(cadena))
     {
       QMessageBox::warning( this, tr("Vencimientos"),tr("No se puede anular un vencimiento procesado"));
       return;
     }*/
   if (QMessageBox::question(
            this,
            tr("Vencimientos"),
            tr("¿ Desea anular el vencimiento seleccionado ?"),
            tr("&Sí"), tr("&No"),
            QString::null, 0, 1 ) )
        return ;
   guardaFechaPago(cuenta,pase,nula,doc);
   refrescar();
   return;
}

void listavenci::editar()
{
   QString pase=paseActual();
   QDate fecha=fechaActual();
   if(!fecha.isValid())
   	QMessageBox::warning( this, tr("Vencimientos"),
       		tr("ERROR: La fecha %1 del pase %1 no es válida").arg(fecha.toString("dd-MM-yyyy"),pase));
   if (pase.length()==0) return;
   editapaseconci *e = new editapaseconci();
   e->pasadatos(pase,fecha,cuentaActual(),formateanumero(debeActual(),comadecimal,decimales),
   							formateanumero(haberActual(),comadecimal,decimales));
   e->exec();
   delete(e);
   refrescar();
   return;
}

void listavenci::generalatex()
{
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero+=tr("vencimientos.tex");
   QFile fichero(adapta(qfichero));

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
    
    stream << "% CUERPO\n";

    stream << "\\begin{center}" << "\n";
    stream << "{\\Large \\textbf {";
    stream << filtracad(nombreempresa()) << "}}";
    stream << "\\end{center}";
    
    stream << "\\begin{center}" << "\n";
    stream << "{\\textbf {";
    if (ui.fechas->isChecked()) 
       {
         stream << tr("FECHA DE ANOTACIÓN: ");
         stream << ui.fechas->fecha(interFechas::inicial).toString("dd.MM.yyyy");
         stream << tr(" A ") << ui.fechas->fecha(interFechas::final).toString("dd.MM.yyyy");
       }
   
    stream << "}}";
    stream << "\\end{center}";

    stream << "\\begin{center}" << "\n";
    stream << "\\begin{longtable}{|r|l|c|r|c|c|}" << "\n";
    stream << "\\hline" << "\n";

   stream << "\\multicolumn{6}{|c|} {\\textbf{";
   QString cadena=tr("VENCIMIENTOS ");
   if (ui.pendientescheckBox->isChecked()) cadena+=tr("PENDIENTES, ");
   if (ui.procesadoscheckBox->isChecked()) cadena+=tr("PROCESADOS, ");
   stream << cadena;
   stream <<  "}} \\\\";
   stream << "\\hline" << "\n";
    // ---------------------------------------------------------------------------------------------------
    stream << "{\\scriptsize{" << tr("Núm. Pase") << "}} & ";
    stream << "{\\scriptsize{" << tr("Cuenta ordenante") << "}} & ";
    stream << "{\\scriptsize{" << tr("Fecha operación") << "}} & ";
    stream << "{\\scriptsize{" << tr("Importe operación") << "}} & ";
    stream << "{\\scriptsize{" << tr("Factura/Doc.") << "}} & ";
    stream << "{\\scriptsize{" << tr("Fecha vencimiento") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endfirsthead";
    // --------------------------------------------------------------------------------------------------
    stream << "\\hline" << "\n";
    stream << " \\\\" << "\n";
    stream << "{\\scriptsize{" << tr("Núm. Pase") << "}} & ";
    stream << "{\\scriptsize{" << tr("Cuenta ordenante") << "}} & ";
    stream << "{\\scriptsize{" << tr("Fecha operación") << "}} & ";
    stream << "{\\scriptsize{" << tr("Importe operación") << "}} & ";
    stream << "{\\scriptsize{" << tr("Factura/Doc.") << "}} & ";
    stream << "{\\scriptsize{" << tr("Fecha vencimiento") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endhead" << "\n";
    // ----------------------------------------------------------------------------------------------------
    int pos=0;
    int linea=0; 
    double total=0;
    int filas=model->rowCount();
    while (pos<filas)
          {
             double importe=model->record(pos).value("debe").toDouble();
             if (!model->record(pos).value("derecho").toBool()) importe=-importe;
             total+=importe;
             stream << "{\\scriptsize " << model->record(pos).value("pase").toString() << "} & {\\scriptsize ";

             stream << descripcioncuenta(model->record(pos).value("cuenta").toString()) << "} & {\\scriptsize ";
             stream << model->record(pos).value("fecha").toDate().toString(Qt::SystemLocaleDate)
                     << "} & {\\scriptsize ";
             stream << formateanumerosep(importe,comadecimal,decimales) << "} & {\\scriptsize ";
             stream << model->record(pos).value("documento").toString() << "} & {\\scriptsize ";
             stream << model->record(pos).value("ci").toDate().toString(Qt::SystemLocaleDate)
                 << "} \\\\ \n  " << "\\hline\n";
             pos++;
             linea++;
             if (linea>(LINEASPAGINA+6)){
             	stream << "\\newpage \n";
             	linea=0;
             }
          }
    stream  << "\\multicolumn{3}{|r|}{" << tr("TOTAL VENCIMIENTOS:") << "} & {\\scriptsize " <<
             formateanumerosep(total,comadecimal,decimales) ;
    stream << "} &  & \\\\ \n"  << "\\hline\n";

    stream << "\\end{longtable}" << "\n";
    stream << "\\end{center}" << "\n";

    stream << "% FIN_CUERPO\n";
    stream << "\\end{document}" << "\n";

    fichero.close();

}


void listavenci::imprimir()
{
    QString fichero=tr("vencimientos");

    generalatex();

   int valor=imprimelatex(fichero);
   if (valor==1)
       QMessageBox::warning( this, tr("Imprimir vencimientos"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("Imprimir vencimientos"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
   if (valor==3)
       QMessageBox::warning( this, tr("Imprimir vencimientos"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());

}


