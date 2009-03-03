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

#include "editaplan.h"
#include "basedatos.h"
//#include "funciones.h"
#include <QMessageBox>



editaplan::editaplan() : QDialog() {
  ui.setupUi(this);
  cargaarbol();
  ui.treeView->setModel(&modeloarbol);
  ui.treeView->expandAll();
  ui.treeView->resizeColumnToContents(0);
  ui.treeView->setEditTriggers ( QAbstractItemView::NoEditTriggers );

  ui.codigolineEdit->setFocus();
  connect(ui.codigolineEdit,SIGNAL(textChanged(QString)),this,SLOT(codigocambiado(QString)));
  connect(ui.codigolineEdit,SIGNAL(editingFinished()),this,SLOT(codigofinedicion()));
  connect(ui.treeView,SIGNAL( clicked (QModelIndex )),this,SLOT(filaclicked(QModelIndex)));
  connect(ui.descripcionlineEdit,SIGNAL( textChanged(QString)),this,SLOT(descripcambiada()));
  connect(ui.aceptarpushButton,SIGNAL( clicked()),this,SLOT(botonaceptar()));
  connect(ui.borrarpushButton,SIGNAL( clicked()),this,SLOT(botonborrar()));

}

void editaplan::cargaarbol()
{
  QSqlQuery query("select codigo,descripcion from plancontable order by codigo;");
  if ( query.isActive() ) {
          while ( query.next() )
              {
                insertacuentaarbol(query.value(0).toString(),query.value(1).toString());
	      }

          }
}

void editaplan::insertacuentaarbol(QString cadena1,QString cadena2)
{
  QString cadactual;
  cadactual=cadena1;
  bool seencuentra=false;
  TreeItem *elemento;
  // QListViewItem *elemento;
  for (int veces=1; veces<cadactual.length(); veces++)
  {
    	QString extract;
    	extract=cadactual.left(cadactual.length()-veces);
    	bool encontrada=false;
    	elemento=modeloarbol.buscacadena(modeloarbol.raiz(),extract,&encontrada);
    	if (encontrada)
    	{
    	  QList<QVariant> datos;
    	  datos << cadena1 << cadena2;
    	  elemento->appendChild(new TreeItem(datos, elemento));
    	  seencuentra=true;
    	  break;
    	}
  }
  if (!seencuentra)
  {
  	QList<QVariant> datos;
  	datos << cadena1 << cadena2;
  	modeloarbol.raiz()->appendChild(new TreeItem(datos, modeloarbol.raiz()));
  }
}

void editaplan::codigocambiado(QString codigo)
{
 if (codigo.length()>0) ui.descripcionlineEdit->setEnabled(true);
     else
          {
           ui.descripcionlineEdit->setText("");
           ui.descripcionlineEdit->setEnabled(false);
           return;
          }
 TreeItem *elemento;
 elemento=NULL;
 bool encontrada;
 elemento=modeloarbol.buscacadena(modeloarbol.raiz(),codigo,&encontrada);
 if (encontrada)
     {
      QModelIndex indice;
      indice = modeloarbol.creaindice(elemento);
      ui.treeView->setCurrentIndex(indice);
      ui.descripcionlineEdit->setText(descripcioncuenta(codigo));
      ui.borrarpushButton->setEnabled(true);
     }
     else 
          { 
            ui.borrarpushButton->setEnabled(false);
            ui.descripcionlineEdit->setText("");
          }

}

void editaplan::codigofinedicion()
{
  if (ui.codigolineEdit->text().length()==2)
      if (!subgrupocongrupo(ui.codigolineEdit->text()))
             {
              QMessageBox::warning( this, tr("Edición de plan contable"),
              tr("ERROR: EL CÓDIGO %1 NO TIENE GRUPO DEFINIDO").arg(ui.codigolineEdit->text()) );
              ui.codigolineEdit->setFocus();
              ui.codigolineEdit->setText("");
             }

  if (ui.codigolineEdit->text().length()==3)
      if (!cuentaconsubgrupo(ui.codigolineEdit->text()))
             {
              QMessageBox::warning( this, tr("Edición de plan contable"),
              tr("ERROR: EL CÓDIGO %1 NO TIENE SUBGRUPO DEFINIDO").arg(ui.codigolineEdit->text()) );
              ui.codigolineEdit->setFocus();
              ui.codigolineEdit->setText("");
             }

  if (ui.codigolineEdit->text().length()>3)
      if (!codigoconcuenta3digitos(ui.codigolineEdit->text()))
             {
              QMessageBox::warning( this, tr("Edición de plan contable"),
              tr("ERROR: EL CÓDIGO %1 NO ESTÁ ASIGNADO A CUENTA DE TRES DÍGITOS").arg(ui.codigolineEdit->text()) );
              ui.codigolineEdit->setFocus();
              ui.codigolineEdit->setText("");
             }
  if (ui.codigolineEdit->text().length()>=anchocuentas())
      {
              QMessageBox::warning( this, tr("Edición de plan contable"),
              tr("ERROR: La longitud del código %1 es igual o superior "
                 "al ancho de las subcuentas").arg(ui.codigolineEdit->text()) );
              ui.codigolineEdit->setFocus();
              ui.codigolineEdit->setText("");
      }
}


void editaplan::filaclicked(QModelIndex indice)
{
 QList<QVariant> datos = modeloarbol.datosfiladeindice(indice);
 if (datos.at(0).toString().length()<anchocuentas())
   {
    ui.codigolineEdit->setText(datos.at(0).toString());
    ui.descripcionlineEdit->setText(datos.at(1).toString());
    ui.aceptarpushButton->setEnabled(false);
   }
}

void editaplan::descripcambiada()
{
 if (ui.descripcionlineEdit->text().length()==0) ui.aceptarpushButton->setEnabled(false);
   else ui.aceptarpushButton->setEnabled(true);
}

void editaplan::botonaceptar()
{
 QString cadena;
 if (existecodigoplan(ui.codigolineEdit->text(),&cadena))
      {
       guardacambiosplan(ui.codigolineEdit->text(),ui.descripcionlineEdit->text());
       existecodigoplan(ui.codigolineEdit->text(),&cadena);
       bool encontrada;
       TreeItem *elemento;
       elemento=modeloarbol.buscacadena(modeloarbol.raiz(),ui.codigolineEdit->text(),&encontrada);
       if (encontrada)
          {
           modeloarbol.setData(elemento, cadena, Qt::EditRole);
           // comprobar datos del modelo
           QVariant dato=elemento->data(1);
           //QMessageBox::information( this, tr("Edición de plan contable"),
           //                  tr("ENCONTRADA")+dato.toString());
          }
      }
  else
      {
       insertaenplan(ui.codigolineEdit->text(),ui.descripcionlineEdit->text());
       if (existecodigoplan(ui.codigolineEdit->text(),&cadena))
           {
            modeloarbol.borraarbol();
            QModelIndex indice;
            cargaarbol();
            modeloarbol.resetea();
            ui.treeView->expandAll();
            bool encontrada;
            TreeItem *elemento;
            elemento=modeloarbol.buscacadena(modeloarbol.raiz(),ui.codigolineEdit->text(),&encontrada);
            if (encontrada)
               {
                indice = modeloarbol.creaindice(elemento);
                ui.treeView->setCurrentIndex(indice);
               }
           }
      }

 QMessageBox::information( this, tr("Edición de plan contable"),
                             tr("Se han efectuado los cambios en el plan contable"));

 ui.codigolineEdit->setText("");
 ui.descripcionlineEdit->setText("");

}

void editaplan::botonborrar()
{

   if (!itemplaneliminado(ui.codigolineEdit->text()))
    {
       QMessageBox::warning( this, tr("Edición de plan contable"),
    tr("No se puede elimimar el código porque éste se subdivide en otros"));
    return;
    }
   modeloarbol.borraarbol();
   QModelIndex indice;
   cargaarbol();
   modeloarbol.resetea();
   ui.treeView->expandAll();
   QMessageBox::information( this, tr("Edición de plan contable"),
                             tr("Se ha eliminado el código seleccionado"));
   ui.codigolineEdit->setText("");
   ui.descripcionlineEdit->setText("");

}
