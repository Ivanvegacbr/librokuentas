/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

    Copyright (C) José Manuel Díez Botella

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

#include "edit_conc_doc.h"
#include "funciones.h"
#include "basedatos.h"


edit_conc_doc::edit_conc_doc() : QDialog() {
    ui.setupUi(this);

   connect(ui.aceptarpushButton,SIGNAL(clicked()),this,SLOT(botonaceptar()));

}


void edit_conc_doc::pasadatos( QString qnumpase, QDate qfecha, QString concepto, QString documento )
{
  ui.conceptolineEdit->setText(concepto);
  ui.documentolineEdit->setText(documento);
  fecha=qfecha;
  numpase=qnumpase;
}

void edit_conc_doc::pasaEtiqueta( QString etiq )
{
	QLabel *l = new QLabel(this);
	l->setText(etiq);
	ui.titleLayout->addWidget(l);
}

void edit_conc_doc::botonaceptar()
{
 if (ejerciciocerrado(ejerciciodelafecha(fecha)))
   {
       QMessageBox::warning( this, tr("Editar apunte"),
		tr("ERROR: No se puede editar un pase de ejercicio cerrado"));
       return;
   }

    updateDiarioCDwP( ui.conceptolineEdit->text() , ui.documentolineEdit->text() , numpase);

  QMessageBox::information( this, tr("Editar apunte"),
	     tr("Operación realizada correctamente"));
  accept();

}

void edit_conc_doc::updateDiarioCDwP (QString concepto, QString documento, QString numpase)
{
    if (!cadnumvalido(numpase)) return;
	QString cadena = "update diario set concepto='";
    cadena += concepto.left(-1).replace("'","''");
    cadena += "', documento='";
    cadena += documento.left(-1).replace("'","''");
    cadena += "' where pase=";
    cadena += numpase.left(-1).replace("'","''");
    ejecutarSQL(cadena);
}
