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

#include "nuevoejercicio.h"
#include "basedatos.h"
//#include "funciones.h"

nuevoejercicio::nuevoejercicio() : QDialog() {
    ui.setupUi(this);
    QDate vfecha;
    vfecha.setYMD(QDate::currentDate().year(),1,1);
    QSqlQuery query("select max(cierre),count(cierre) from ejercicios;");
     if ( query.isActive() )
          {
              if (query.next() && query.value(1).toInt()>0)
                   {
                      vfecha=query.value(0).toDate().addDays(1);
                   } 
          }
    ui.aperturadateEdit->setDate(vfecha);
    QDate vfecha2;
    vfecha2=vfecha.addDays(vfecha.daysInYear()-1);
    // vfecha.setYMD(QDate::currentDate().year(),12,31);
    ui.cierredateEdit->setDate(vfecha2);

   connect(ui.aceptarpushButton,SIGNAL(clicked()),SLOT(guardarejercicio()));

}

void nuevoejercicio::guardarejercicio()
{
    if (ui.codigolineEdit->text().length()==0) 
        {
            QMessageBox::warning( this, tr("Nuevo ejercicio"),
            tr("ERROR: El código introducido no tiene contenido"));
           return;
        }

    QString cadena;
    cadena="select codigo from ejercicios where codigo='";
    cadena+=ui.codigolineEdit->text();
    cadena+="';";
    QSqlQuery query(cadena);
     if ( query.isActive() )
          {
              if (query.next())
                   {
                     QMessageBox::warning( this, tr("Nuevo ejercicio"),
                     tr("ERROR: El código de ejercicio ya existe"));
                     return;
                   } 
          }
    if (ui.aperturadateEdit->date()>ui.cierredateEdit->date())
        {
            QMessageBox::warning( this, tr("Nuevo ejercicio"),
            tr("ERROR: Las fechas del ejercicio no son correctas"));
           return;
         }
    
    
    cadena="select apertura,cierre from ejercicios;";
    query.exec(cadena);
     if ( query.isActive() )
          {
              while (query.next())
                   {
                     if (ui.aperturadateEdit->date()>=query.value(0).toDate() &&
	                  ui.aperturadateEdit->date()<=query.value(1).toDate())
		            {
                              QMessageBox::warning( this, tr("Nuevo ejercicio"),
                               tr("ERROR: La fecha de apertura está contenida en otro ejercicio"));
                               return;
                             } 
                   }
          }

// Parece que se puede insertar  el registro
  cadena="insert into ejercicios (codigo,apertura,cierre,cerrado,cerrando,primerasiento) values ('";
  cadena+=ui.codigolineEdit->text();
  cadena+="','";
  cadena+=ui.aperturadateEdit->date().toString("yyyy/MM/dd");
  cadena+="','";
  cadena+=ui.cierredateEdit->date().toString("yyyy/MM/dd");
  cadena+="',FALSE,FALSE,0);";
  query.exec(cadena);
  accept();
}
