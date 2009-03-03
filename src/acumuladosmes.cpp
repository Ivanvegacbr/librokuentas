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

#include "acumuladosmes.h"
#include "funciones.h"
#include "buscasubcuenta.h"
#include "basedatos.h"

acumuladosmes::acumuladosmes() : QDialog() {
  ui.setupUi(this);
  comadecimal=haycomadecimal();
  decimales=haydecimales();

  QSqlQuery query = ejecutarSQL("select codigo from ejercicios order by codigo DESC;");
  QStringList ej1;

  if ( query.isActive() ) {
          while ( query.next() )
                ej1 << query.value(0).toString();
	  }
  ui.ejerciciocomboBox->addItems(ej1);
 QDate fechaactual;
 QString ejercicio;
 ejercicio=ejerciciodelafecha(fechaactual.currentDate());

 if (ejercicio!="") ui.ejerciciocomboBox->setCurrentIndex(
        ui.ejerciciocomboBox->findText ( ejercicio, Qt::MatchExactly ));

 QStringList columnas;
 columnas << tr("MES") << tr("AÑO") << tr("SUMA DEBE");
 columnas << tr("SUMA HABER") << tr("SALDO") ;


 ui.tabla->setHorizontalHeaderLabels(columnas);

 connect(ui.buscapushButton,SIGNAL(clicked()),this,SLOT(botonbuscasubcuentapulsado()));
 connect(ui.subcuentalineEdit,SIGNAL(textChanged(QString)),this,SLOT(subcuentacambiada()));
 connect(ui.subcuentalineEdit,SIGNAL(editingFinished()),this,SLOT(finedicsubcuenta()));
 connect(ui.refrescarpushButton,SIGNAL(clicked()),this,SLOT(refrescar()));

 connect(ui.anteriorpushButton,SIGNAL(clicked()),this,SLOT(subcuentaprevia()));
 connect(ui.posteriorpushButton,SIGNAL(clicked()),this,SLOT(subcuentasiguiente()));

 connect(ui.copiarpushButton,SIGNAL(clicked()),this,SLOT(txtexport()));

}



void acumuladosmes::pasacodigocuenta(QString codigo,QDate fecha)
{
  QString cadena;
  ui.subcuentalineEdit->setText(codigo);
  if (existecodigoplan(codigo,&cadena)) ui.titulotextLabel->setText(cadena);
  cadena=ejerciciodelafecha(fecha);
  if (cadena!="") ui.ejerciciocomboBox->setCurrentIndex(
        ui.ejerciciocomboBox->findText ( cadena, Qt::MatchExactly ));
}


void acumuladosmes::cargadatos()
{
  if (ui.subcuentalineEdit->text().length()!=anchocuentas()) return;
  QDate fechainicial; fechainicial=inicioejercicio(ui.ejerciciocomboBox->currentText());
  QDate fechafinal; fechafinal=finejercicio(ui.ejerciciocomboBox->currentText());
  QDate fechacorriente;
  fechacorriente.setYMD(fechainicial.year(),fechainicial.month(),1);
  int veces=0;
  ui.progressBar->setMaximum(3);
  while (fechacorriente<fechafinal)
       {
          fechacorriente=fechacorriente.addMonths(1);
          veces++;
       }
  ui.tabla->setRowCount(veces+3);
  fechacorriente.setYMD(fechainicial.year(),fechainicial.month(),1);
  if (ui.tabla->item(0,0)==0)
      {
       QTableWidgetItem *newItem = new QTableWidgetItem("");
       ui.tabla->setItem(0,0,newItem);
      }
  ui.tabla->item(0,0)->setText(diario_apertura());

  veces=1;
  while (fechacorriente<fechafinal)
       {
          if (ui.tabla->item(veces,0)==0)
             { 
              QTableWidgetItem *newItem = new QTableWidgetItem("");
              ui.tabla->setItem(veces,0,newItem);
             }
          ui.tabla->item(veces,0)->setText(cadmes(fechacorriente.month()));
          QString cadnum;
          cadnum.setNum(fechacorriente.year());
          if (ui.tabla->item(veces,1)==0)
             { 
              QTableWidgetItem *newItem = new QTableWidgetItem("");
              ui.tabla->setItem(veces,1,newItem);
             }

          ui.tabla->item(veces,1)->setText(cadnum);
          fechacorriente=fechacorriente.addMonths(1);
          veces++;
       }

   if (ui.tabla->item(veces,0)==0)
       { 
         QTableWidgetItem *newItem = new QTableWidgetItem("");
         ui.tabla->setItem(veces,0,newItem);
       }
  ui.tabla->item(veces,0)->setText(diario_regularizacion());

   if (ui.tabla->item(veces+1,0)==0)
       { 
         QTableWidgetItem *newItem = new QTableWidgetItem("");
         ui.tabla->setItem(veces+1,0,newItem);
       }
  ui.tabla->item(veces+1,0)->setText(diario_cierre());

  int posreg=veces;
  
  QSqlQuery query = selectDatos (diario_apertura(),fechainicial,fechafinal,ui.subcuentalineEdit->text());
  if ( (query.isActive()) && (query.next()) )
       {
               if (ui.tabla->item(0,2)==0)
                  { 
                   QTableWidgetItem *newItem = new QTableWidgetItem("");
                   newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                   ui.tabla->setItem(0,2,newItem);
                  }
	       ui.tabla->item(0,2)->setText(formateanumero(query.value(0).toDouble(),comadecimal,decimales));
               if (ui.tabla->item(0,3)==0)
                  { 
                   QTableWidgetItem *newItem = new QTableWidgetItem("");
                   newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                   ui.tabla->setItem(0,3,newItem);
                  }
	       ui.tabla->item(0,3)->setText(formateanumero(query.value(1).toDouble(),comadecimal,decimales));
               if (ui.tabla->item(0,4)==0)
                  { 
                   QTableWidgetItem *newItem = new QTableWidgetItem("");
                   newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                   ui.tabla->setItem(0,4,newItem);
                  }
	       ui.tabla->item(0,4)->setText(formateanumero(query.value(2).toDouble(),comadecimal,decimales));
      }
  double saldo=0;
  saldo=query.value(2).toString().toDouble();
  ui.progressBar->setValue(1);

  query = selectDatosRestantes(fechainicial,fechafinal,ui.subcuentalineEdit->text());
 if ( query.isActive() ) {
          while ( query.next() )
             {
	      veces=0;
	      while (veces<posreg)
	       {
	        if (cadmes(query.value(0).toInt())==ui.tabla->item(veces,0)->text() &&
		   query.value(1).toString()==ui.tabla->item(veces,1)->text())
	         {
                     if (ui.tabla->item(veces,2)==0)
                       { 
                        QTableWidgetItem *newItem = new QTableWidgetItem("");
                        newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                        ui.tabla->setItem(veces,2,newItem);
                       }
	             ui.tabla->item(veces,2)->setText(formateanumero(query.value(2).toDouble(),
                                                      comadecimal,decimales));
                     if (ui.tabla->item(veces,3)==0)
                       { 
                        QTableWidgetItem *newItem = new QTableWidgetItem("");
                        newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                        ui.tabla->setItem(veces,3,newItem);
                       }
	             ui.tabla->item(veces,3)->setText(formateanumero(query.value(3).toDouble(),
                                       comadecimal,decimales));
	             saldo+=query.value(4).toDouble();
                     if (ui.tabla->item(veces,4)==0)
                       { 
                        QTableWidgetItem *newItem = new QTableWidgetItem("");
                        newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                        ui.tabla->setItem(veces,4,newItem);
                       }
	             ui.tabla->item(veces,4)->setText(formateanumero(saldo,comadecimal,decimales));
	         }
	       veces++;
	      }
             }
      }
 
   ui.progressBar->setValue(2);
 
  query = selectDatos(diario_regularizacion(),fechainicial, fechafinal, ui.subcuentalineEdit->text());
 if ( query.isActive() ) {
          if ( query.next() )
              {
                if (ui.tabla->item(posreg,2)==0)
                   { 
                    QTableWidgetItem *newItem = new QTableWidgetItem("");
                    newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                    ui.tabla->setItem(posreg,2,newItem);
                   }
	        ui.tabla->item(posreg,2)->setText(formateanumero(query.value(0).toDouble(),
                    comadecimal,decimales));
                if (ui.tabla->item(posreg,3)==0)
                   { 
                    QTableWidgetItem *newItem = new QTableWidgetItem("");
                    newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                    ui.tabla->setItem(posreg,3,newItem);
                   }
	        ui.tabla->item(posreg,3)->setText(formateanumero(query.value(1).toDouble(),
                    comadecimal,decimales));
                saldo+=query.value(2).toDouble();
                if (ui.tabla->item(posreg,4)==0)
                   { 
                    QTableWidgetItem *newItem = new QTableWidgetItem("");
                    newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                    ui.tabla->setItem(posreg,4,newItem);
                   }
	        ui.tabla->item(posreg,4)->setText(formateanumero(saldo,comadecimal,decimales));
              }
      }
 
  query = selectDatos(diario_cierre(),fechainicial,  fechafinal, ui.subcuentalineEdit->text());
 if ( query.isActive() ) {
          if ( query.next() )
              {
                if (ui.tabla->item(posreg+1,2)==0)
                   { 
                    QTableWidgetItem *newItem = new QTableWidgetItem("");
                    newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                    ui.tabla->setItem(posreg+1,2,newItem);
                   }
                ui.tabla->item(posreg+1,2)->setText(formateanumero(query.value(0).toDouble(),
                      comadecimal,decimales));
                if (ui.tabla->item(posreg+1,3)==0)
                   { 
                    QTableWidgetItem *newItem = new QTableWidgetItem("");
                    newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                    ui.tabla->setItem(posreg+1,3,newItem);
                   }
                ui.tabla->item(posreg+1,3)->setText(formateanumero(query.value(1).toDouble(),
                    comadecimal,decimales));
                saldo+=query.value(2).toDouble();
                if (ui.tabla->item(posreg+1,4)==0)
                   { 
                    QTableWidgetItem *newItem = new QTableWidgetItem("");
                    newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
                    ui.tabla->setItem(posreg+1,4,newItem);
                   }
	        ui.tabla->item(posreg+1,4)->setText(formateanumero(saldo,comadecimal,decimales));
              }
      }
 ui.progressBar->setValue(3);
 
 veces=1;
 QString cad4;
 if (ui.tabla->item(0,4)==0)
     {
       QTableWidgetItem *newItem = new QTableWidgetItem("");
       newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
       ui.tabla->setItem(0,4,newItem);
     }
 cad4=ui.tabla->item(0,4)->text();
 if (cad4=="0" || cad4.length()==0) cad4=formateanumero(0,comadecimal,decimales);
 while (veces<ui.tabla->rowCount())
    {
       if (ui.tabla->item(veces,2)==0)
           { 
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
            ui.tabla->setItem(veces,2,newItem);
           }
       if (ui.tabla->item(veces,2)->text().length()==0) ui.tabla->item(veces,2)->setText(
                                                      formateanumero(0,comadecimal,decimales));
       if (ui.tabla->item(veces,3)==0)
           { 
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
            ui.tabla->setItem(veces,3,newItem);
           }
       if (ui.tabla->item(veces,3)->text().length()==0) ui.tabla->item(veces,3)->setText(
                                                      formateanumero(0,comadecimal,decimales));
       if (ui.tabla->item(veces,4)==0)
           { 
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
            ui.tabla->setItem(veces,4,newItem);
           }
       if (ui.tabla->item(veces,4)->text().length()==0) ui.tabla->item(veces,4)->setText(cad4);
       cad4=ui.tabla->item(veces,4)->text();
       veces++;
    }
 ui.progressBar->reset();
 ui.tabla->resizeColumnToContents(0);
 ui.tabla->resizeColumnToContents(1);
}


void acumuladosmes::botonbuscasubcuentapulsado()
{
    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.subcuentalineEdit->text());
    int cod=labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();
    if (cod==QDialog::Accepted && existesubcuenta(cadena2)) ui.subcuentalineEdit->setText(cadena2);
       else ui.subcuentalineEdit->setText("");
    delete labusqueda;
}


void acumuladosmes::subcuentacambiada()
{
  ui.tabla->setRowCount(0);
  if (existesubcuenta(ui.subcuentalineEdit->text()))
     { 
       ui.titulotextLabel->setText(descripcioncuenta(ui.subcuentalineEdit->text()));
       cargadatos();
     }
}


void acumuladosmes::ctaexpandepunto()
{
  ui.subcuentalineEdit->setText(expandepunto(ui.subcuentalineEdit->text(),anchocuentas()));
}


void acumuladosmes::finedicsubcuenta()
{
 ctaexpandepunto();
 if (ui.subcuentalineEdit->text().length()<anchocuentas() && ui.subcuentalineEdit->text().length()>0)
    botonbuscasubcuentapulsado();
}


void acumuladosmes::refrescar()
{
  cargadatos();
}

void acumuladosmes::subcuentaprevia()
{
    QString cadena=subcuentaanterior(ui.subcuentalineEdit->text());
    if (cadena=="") return;
    ui.subcuentalineEdit->setText(cadena);
    // refrescar();
}


void acumuladosmes::subcuentasiguiente()
{
    QString cadena=subcuentaposterior(ui.subcuentalineEdit->text());
    if (cadena=="") return;
    ui.subcuentalineEdit->setText(cadena);
    // refrescar();
}


void acumuladosmes::txtexport()
{
   QClipboard *cb = QApplication::clipboard();
   QString global;
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero=qfichero+tr("acum_cuenta.txt");
   // QMessageBox::warning( this, tr("HOLA"),qfichero);
   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(qfichero);
       else pasa=qfichero;
    QFile fichero(pasa);
    if (! fichero.open( QIODevice::WriteOnly ) ) return;
    QTextStream stream( &fichero );
    stream.setCodec("UTF-8");
    stream << tr("SUBCUENTA:") << "\t" << ui.subcuentalineEdit->text() << "\t" 
           << ui.titulotextLabel->text() <<"\n";
    global=tr("SUBCUENTA:") + "\t"; global+=ui.subcuentalineEdit->text(); global+="\t";
    global+=ui.titulotextLabel->text();
    global+="\n";
    stream << tr("EJERCICIO:") <<" \t" << ui.ejerciciocomboBox->currentText()  << "\n";

    global+=tr("EJERCICIO") +": \t"; global+=ui.ejerciciocomboBox->currentText(); global+="\n";

    stream << tr("MES") << ": \t" << tr("AÑO") << ": \t" << tr("SUMA DEBE");
    stream << ": \t" << tr("SUMA HABER") << ": \t" << tr("SALDO") << "\n";

    global+=tr("MES"); global+=": \t"; global+=tr("AÑO"); global+=": \t"; global+=tr("SUMA DEBE");
    global+=": \t"; global+=tr("SUMA HABER"); global+=": \t"; global+=tr("SALDO"); global+="\n";

    for (int veces=0;veces<ui.tabla->rowCount();veces++)
       {
          QString cad;
          if (ui.tabla->item(veces,0)!=0) cad=ui.tabla->item(veces,0)->text(); else cad="";
          stream << cad << "\t";
          global+= cad + "\t";
          if (ui.tabla->item(veces,1)!=0) cad=ui.tabla->item(veces,1)->text(); else cad="";
          stream << cad << "\t";
          global+= cad + "\t";
          if (ui.tabla->item(veces,2)!=0) cad=ui.tabla->item(veces,2)->text(); else cad="";
          stream << cad << "\t";
          global+= cad + "\t";
          if (ui.tabla->item(veces,3)!=0) cad=ui.tabla->item(veces,3)->text(); else cad="";
          stream << cad << "\t";
          global+= cad + "\t";
          if (ui.tabla->item(veces,4)!=0) cad=ui.tabla->item(veces,4)->text(); else cad="";
          stream << cad << "\n";
          global+= cad + "\n";

       }
    fichero.close();
    cb->setText(global);
    QMessageBox::information( this, tr("ACUMULADOS MES"),
			      tr("Se ha pasado el contenido al portapales"));

}

QSqlQuery acumuladosmes::selectDatos (QString tipo_diario,QDate fechainicial,QDate fechafinal,QString sub) {
    QString cadena="select sum(debe),sum(haber), sum(debe-haber) from diario where diario='";
    cadena+=tipo_diario.left(-1).replace("'","''");
    cadena+="' and fecha>='";
    cadena+=fechainicial.toString("yyyy.MM.dd");
    cadena+="' and fecha<='";
    cadena+=fechafinal.toString("yyyy.MM.dd");
    cadena+="' and cuenta='";
    cadena+=sub.left(-1).replace("'","''");
    cadena+="'";
    return ejecutarSQL(cadena);
}

QSqlQuery acumuladosmes::selectDatosRestantes (QDate fechainicial, QDate fechafinal, QString sub) {
    QString cadena;
    if (cualControlador() == SQLITE) {
        cadena = "select substr(fecha,6,2),substr(fecha,1,4),sum(debe),sum(haber),";
    }
    else {
    cadena =  "select extract(month from fecha),extract(year from fecha),sum(debe),sum(haber),";
    }
    cadena += "sum(debe-haber) from diario where fecha>='";
    cadena += fechainicial.toString("yyyy.MM.dd");
    cadena += "' and fecha<='";
    cadena += fechafinal.toString("yyyy.MM.dd");
    cadena += "' and cuenta='";
    cadena += sub.left(-1).replace("'","''");
    cadena += "' and diario!='";
    cadena += diario_apertura();
    cadena += "' and diario!='";
    cadena += diario_regularizacion();
    cadena += "' and diario!='";
    cadena += diario_cierre();
    if (cualControlador() == SQLITE) {
        cadena += "' group by substr(fecha,6,2),substr(fecha,1,4) ";
        cadena += "order by substr(fecha,6,2),substr(fecha,1,4);";
    }
    else {
        cadena += "' group by extract(month from fecha),extract(year from fecha) ";
        cadena += "order by extract(month from fecha),extract(year from fecha);";
    }
    return ejecutarSQL(cadena);
}
