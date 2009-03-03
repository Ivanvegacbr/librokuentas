/* ----------------------------------------------------------------------------------
    KEME-Contabilidad ; aplicación para llevar contabilidades

    Copyright (C)   José Manuel Díez Botella

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

#include "subcuentas.h"
#include "basedatos.h"
#include "funciones.h"
#include <QMessageBox>



subcuentas::subcuentas() : QDialog() {
  ui.setupUi(this);
  cargaarbol();
  ui.treeView->setModel(&modeloarbol);
  ui.treeView->expandAll();
  TreeItem *elemento;
  elemento=NULL;
  /*bool encontrada;
  QModelIndex indice;
  elemento=modeloarbol.buscacadena(modeloarbol.raiz(),grupoGastos(),&encontrada);
  if (encontrada){
      indice = modeloarbol.creaindice(elemento);ui.treeView->resizeColumnToContents(0);
      ui.treeView->expand(indice);
  }else{
  	ui.treeView->expandAll();
 	}
  elemento=modeloarbol.buscacadena(modeloarbol.raiz(),grupoIngresos(),&encontrada);
  if (encontrada){
      indice = modeloarbol.creaindice(elemento);ui.treeView->resizeColumnToContents(0);
      ui.treeView->expand(indice);
  }else{
  	ui.treeView->expandAll();
 	}
  */
  ui.treeView->setAlternatingRowColors ( true);
  ui.treeView->setEditTriggers ( QAbstractItemView::NoEditTriggers );
  ui.codigolineEdit->setFocus();
  connect(ui.codigolineEdit,SIGNAL(textChanged(QString)),this,SLOT(codigocambiado(QString)));
  connect(ui.codigolineEdit,SIGNAL(editingFinished()),this,SLOT(codigofinedicion()));
  connect(ui.treeView,SIGNAL( clicked (QModelIndex )),this,SLOT(filaclicked(QModelIndex)));
  connect(ui.descripcionlineEdit,SIGNAL( textChanged(QString)),this,SLOT(descripcambiada()));
  connect(ui.aceptarpushButton,SIGNAL( clicked()),this,SLOT(botonaceptar()));
  connect(ui.borrarpushButton,SIGNAL( clicked()),this,SLOT(botonborrar()));
  connect(ui.datosgroupBox,SIGNAL( clicked(bool)),this,SLOT(grupodatospulsado()));

}

void subcuentas::cargaarbol()
{
  QSqlQuery query("select codigo,descripcion from plancontable order by codigo;");
  if ( query.isActive() ) {
          while ( query.next() )
              {
                insertacuentaarbol(query.value(0).toString(),query.value(1).toString());
	      }

          }
}

void subcuentas::insertacuentaarbol(QString cadena1,QString cadena2)
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

void subcuentas::codigocambiado(QString codigo)
{
 if (codigo.length()==0) 
   {
    ui.datosgroupBox->setChecked(false);
    resetdatosaccesorios();
    ui.datosgroupBox->setEnabled(false);
    
   }
 if (ui.datosgroupBox->isEnabled())
     {
      if (ui.datosgroupBox->isChecked())
          {
            resetdatosaccesorios();
            ui.datosgroupBox->setChecked(false);
          }
     }
 if (codigo.length()==anchocuentas()) 
   {
    ui.descripcionlineEdit->setEnabled(true);
    ui.descripcionlineEdit->setFocus();
   }
     else
          {
           ui.descripcionlineEdit->setText("");
           ui.descripcionlineEdit->setEnabled(false);
           ui.borrarpushButton->setEnabled(false);
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
      if (codigo.length()==anchocuentas())
          {
           ui.descripcionlineEdit->setText(descripcioncuenta(codigo));
           ui.aceptarpushButton->setEnabled(false);
           ui.borrarpushButton->setEnabled(true);
           // habilitar grupo de datossubcuenta
           ui.datosgroupBox->setEnabled(true);
           
           // ver si hay datossubcuenta, activar groupbox y cargarcampos

           QString razon;
           QString ncomercial;
           QString cif;
           QString nifcomunitario;
           QString domicilio;
           QString poblacion;
           QString codigopostal;
           QString provincia;
           QString pais;
           QString tfno;
           QString fax;
           QString email;
           QString observaciones;
           QString ccc;
           QString cuota;
    
           if (existendatosaccesorios(codigo, &razon, &ncomercial, &cif,   &nifcomunitario, &domicilio, 
			       &poblacion,&codigopostal, &provincia, &pais, &tfno,
			       &fax, &email, &observaciones, &ccc, &cuota))
            {
             ui.datosgroupBox->setChecked(true);
	     // Pasamos datos a campos
	     ui.NombreLineEdit->setText(razon);
             ui.ncomerciallineEdit->setText(ncomercial);
	     ui.DomicilioLineEdit->setText(domicilio);
	     ui.PoblacionLineEdit->setText(poblacion);
	     ui.ProvinciaLineEdit->setText(provincia);
	     ui.CpLineEdit->setText(codigopostal);
	     ui.NifLineEdit->setText(cif);
	     ui.NifComLineEdit->setText(nifcomunitario);
	     ui.PaisLineEdit->setText(pais);
	     ui.TfnoLineEdit->setText(tfno);
	     ui.FaxLineEdit->setText(fax);
	     ui.EmailLineEdit->setText(email);
	     ui.ObservacionesLineEdit->setText(observaciones);
             ui.ccclineEdit->setText(ccc);
             ui.cuotalineEdit->setText(cuota);
             ui.aceptarpushButton->setEnabled(true);
            }
          }
          else
              { 
               ui.borrarpushButton->setEnabled(false);
               ui.descripcionlineEdit->setText("");
               // borrar todos los datos subcuenta y deshabilitar datossubcuenta y chequear false
               // si el grupo está habilitado
               if (ui.datosgroupBox->isEnabled())
                   {
                    resetdatosaccesorios();
                    ui.datosgroupBox->setChecked(false);
                    ui.datosgroupBox->setEnabled(false);
                   }
              }
     }
     else 
          { 
            ui.borrarpushButton->setEnabled(false);
            ui.descripcionlineEdit->setText("");
            if (ui.datosgroupBox->isEnabled())
              {
               resetdatosaccesorios();
               ui.datosgroupBox->setChecked(false);
               ui.datosgroupBox->setEnabled(false);
              }
          }

}

void subcuentas::resetdatosaccesorios()
{
	     ui.NombreLineEdit->setText("");
             ui.ncomerciallineEdit->setText("");
	     ui.DomicilioLineEdit->setText("");
	     ui.PoblacionLineEdit->setText("");
	     ui.ProvinciaLineEdit->setText("");
	     ui.CpLineEdit->setText("");
	     ui.NifLineEdit->setText("");
	     ui.NifComLineEdit->setText("");
	     ui.PaisLineEdit->setText("");
	     ui.TfnoLineEdit->setText("");
	     ui.FaxLineEdit->setText("");
	     ui.EmailLineEdit->setText("");
	     ui.ObservacionesLineEdit->setText("");
             ui.ccclineEdit->setText("");
             ui.cuotalineEdit->setText("");
}

void subcuentas::codigofinedicion()
{
  ui.codigolineEdit->setText(expandepunto(ui.codigolineEdit->text(),anchocuentas()));
  if (ui.codigolineEdit->text().length()==0)
      return;
 /* if (ui.codigolineEdit->text().length()!=anchocuentas())
             {
              QMessageBox::warning( this, tr("Edición de plan contable"),
              tr("ERROR: EL CÓDIGO %1 NO TIENE EL ANCHO REQUERIDO PARA SER SUBCUENTA").arg(ui.codigolineEdit->text()) );
              ui.codigolineEdit->setFocus();
              ui.codigolineEdit->setText("");
             }
*/
 if (ui.codigolineEdit->text().length()!=anchocuentas())
     ui.datosgroupBox->setChecked(false);

  if (ui.codigolineEdit->text().length()>3)
     {
      if (!codigoconcuenta3digitos(ui.codigolineEdit->text()))
             {
              QMessageBox::warning( this, tr("Edición de plan contable"),
              tr("ERROR: EL CÓDIGO %1 NO ESTÁ ASIGNADO A CUENTA DE TRES DÍGITOS").arg(ui.codigolineEdit->text()) );
              ui.codigolineEdit->setFocus();
              ui.codigolineEdit->setText("");
              ui.datosgroupBox->setChecked(false);
             }
        else if (ui.codigolineEdit->text().length()!=anchocuentas()) ui.descripcionlineEdit->setFocus();
      }


}


void subcuentas::filaclicked(QModelIndex indice)
{
 QList<QVariant> datos = modeloarbol.datosfiladeindice(indice);
 if (datos.at(0).toString().length()==anchocuentas())
   {
    ui.codigolineEdit->setText(datos.at(0).toString());
    ui.descripcionlineEdit->setText(datos.at(1).toString());
    ui.aceptarpushButton->setEnabled(false);
    if (ui.datosgroupBox->isChecked()) ui.aceptarpushButton->setEnabled(true);
   }
}

void subcuentas::descripcambiada()
{
 if (ui.descripcionlineEdit->text().length()==0)
     {
      ui.aceptarpushButton->setEnabled(false);
     }
   else
     {
      ui.aceptarpushButton->setEnabled(true);
      ui.datosgroupBox->setEnabled(true);
     }
}

void subcuentas::botonaceptar()
{
 QString cadena;
 if (ui.codigolineEdit->text().length()==0){
 	QMessageBox::warning( this, tr("Edición de subcuentas"),
       tr("Debe introducir un código válido para la cuenta."));
       return;
	}
 if (existecodigoplan(ui.codigolineEdit->text(),&cadena))
      {
       guardacambiosplan(ui.codigolineEdit->text(),ui.descripcionlineEdit->text());
       if (existecodigoplan(ui.codigolineEdit->text(),&cadena))
         {
           if (ui.datosgroupBox->isChecked())
             guardadatosaccesorios(
              ui.codigolineEdit->text(),
	      ui.NombreLineEdit->text(),
              ui.ncomerciallineEdit->text(),
	      ui.NifLineEdit->text(),
	      ui.NifComLineEdit->text(),
	      ui.DomicilioLineEdit->text(),
	      ui.PoblacionLineEdit->text(),
	      ui.CpLineEdit->text(),
	      ui.ProvinciaLineEdit->text(),
	      ui.PaisLineEdit->text(),
	      ui.TfnoLineEdit->text(),
	      ui.FaxLineEdit->text(),
	      ui.EmailLineEdit->text(),
	      ui.ObservacionesLineEdit->text(),
              ui.ccclineEdit->text(),
              ui.cuotalineEdit->text() );
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
      }
  else
      {
       insertaenplan(ui.codigolineEdit->text(),ui.descripcionlineEdit->text());
       if (existecodigoplan(ui.codigolineEdit->text(),&cadena))
           {
           if (ui.datosgroupBox->isChecked())
            guardadatosaccesorios(
              ui.codigolineEdit->text(),
	      ui.NombreLineEdit->text(),
              ui.ncomerciallineEdit->text(),
	      ui.NifLineEdit->text(),
	      ui.NifComLineEdit->text(),
	      ui.DomicilioLineEdit->text(),
	      ui.PoblacionLineEdit->text(),
	      ui.CpLineEdit->text(),
	      ui.ProvinciaLineEdit->text(),
	      ui.PaisLineEdit->text(),
	      ui.TfnoLineEdit->text(),
	      ui.FaxLineEdit->text(),
	      ui.EmailLineEdit->text(),
	      ui.ObservacionesLineEdit->text(),
              ui.ccclineEdit->text(),
              ui.cuotalineEdit->text() );
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

  if (!existecodigosaldosubcuenta(ui.codigolineEdit->text()))
     insertasaldosubcuenta(ui.codigolineEdit->text());

 QMessageBox::information( this, tr("Edición de plan contable"),
                             tr("Se han efectuado los cambios en el plan contable"));

 ui.codigolineEdit->setText("");
 ui.descripcionlineEdit->setText("");

}

void subcuentas::botonborrar()
{
   // falta mensaje está seguro ?

  QMessageBox msgBox;
  msgBox.addButton(QObject::tr("Sí"), QMessageBox::ActionRole);
  QPushButton *abortButton = msgBox.addButton(QObject::tr("No"), QMessageBox::ActionRole);


  msgBox.setIcon(QMessageBox::Warning);
  msgBox.setText(tr("¿ DESEA ELEMINAR LA SUBCUENTA SELECCIONADA ?"));

  msgBox.exec();

  if (msgBox.clickedButton() == abortButton) 
      return;

   if (cuentaendiario(ui.codigolineEdit->text()))
    {
       QMessageBox::warning( this, tr("Edición de subcuentas"),
       tr("No se puede elimimar la subcuenta porque existe en el diario"));
       return;
    }
   eliminasubcuenta(ui.codigolineEdit->text());
   modeloarbol.borraarbol();
   QModelIndex indice;
   cargaarbol();
   modeloarbol.resetea();
   ui.treeView->expandAll();
   QMessageBox::information( this, tr("Edición de subcuentas"),
                             tr("Se ha eliminado el código seleccionado"));
   ui.codigolineEdit->setText("");
   ui.descripcionlineEdit->setText("");

}
 
void subcuentas::grupodatospulsado()
{
 if (!ui.datosgroupBox->isChecked())
    {
     QMessageBox msgBox;
     msgBox.addButton(QObject::tr("Sí"), QMessageBox::ActionRole);
     QPushButton *abortButton = msgBox.addButton(QObject::tr("No"), QMessageBox::ActionRole);


     msgBox.setIcon(QMessageBox::Warning);
     msgBox.setText(tr("¿ DESEA ELIMINAR LOS DATOS ACCESORIOS ? (OPERACIÓN IRREVERSIBLE)"));

     msgBox.exec();

     if (msgBox.clickedButton() == abortButton) 
      { ui.datosgroupBox->setChecked(true); return;}
     resetdatosaccesorios();
     // queda borrar datos accesorios físicamente
     eliminadatosaccesorios(ui.codigolineEdit->text());
    }
  else
    ui.aceptarpushButton->setEnabled(true);

}

void subcuentas::pasacodigo(QString qcodigo)
{
  ui.codigolineEdit->setText(qcodigo);
}
