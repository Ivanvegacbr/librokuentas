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

#include "editafechacierre.h"
#include "basedatos.h"
//#include "funciones.h"

editafechacierre::editafechacierre() : QDialog()
 {
    ui.setupUi(this);
   connect(ui.aceptarpushButton,SIGNAL( clicked()),this,
           SLOT(aceptar()));

 }

void editafechacierre::pasafecha( QDate fecha )
{
  ui.fechadateEdit->setDate(fecha);
}


void editafechacierre::pasaapertura( QDate fecha )
{
 apertura=fecha;
}


void editafechacierre::pasaejercicio( QString qejercicio )
{
  ejercicio=qejercicio;
  QString cadena;
  cadena="Cierre, ejercicio: ";
  cadena+=ejercicio;
  setWindowTitle(cadena);
}

void editafechacierre::aceptar()
{
   // comprobamos que la fecha de cierre no sea menor que la de apertura
    if (ui.fechadateEdit->date()<apertura)
       {
         QMessageBox::warning( this, tr("FECHA DE CIERRE"),
			              tr("Error, la fecha de cierre no  puede ser\n"
				  "inferior a la fecha de apertura de ejercicio."));
         return;
       }
   QString cadena="update ejercicios set cierre='";
   cadena+=ui.fechadateEdit->date().toString("yyyy.MM.dd");
   cadena+="' where codigo='";
   cadena+=ejercicio;
   cadena+="'";
   QSqlQuery query(cadena);
   accept();
}
