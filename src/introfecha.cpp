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

#include "introfecha.h"
#include <QSqlQuery>
#include "funciones.h"


introfecha::introfecha() : QDialog() {
    ui.setupUi(this);
    QDate fecha;
    ui.calendario->setSelectedDate(fecha.currentDate());
  /*QStringList diarios;

 diarios << diario_no_asignado();

    QString cadena2="select codigo from diarios order by codigo";
    QSqlQuery query(cadena2);
    while (query.next())
       {
           diarios << query.value(0).toString();
       }

  ui.diariocomboBox->addItems(diarios);*/
}

QDate introfecha::fecha()
{
  return ui.calendario->selectedDate();
}

int introfecha::semana()
{
  QDate fecha = ui.calendario->selectedDate();
  int semana = fecha.weekNumber();
  return semana;
}

void introfecha::fijarDiaMinimo(QDate dia)
{
	//QDate fecha = fechaMaxAsiento(asiento);
	ui.calendario->setMinimumDate(dia.addDays(1));
}
