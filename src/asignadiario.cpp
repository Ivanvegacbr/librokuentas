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

#include "asignadiario.h"
#include <QSqlQuery>
#include "funciones.h"
#include "basedatos.h"

asignadiario::asignadiario() : QDialog() {
    ui.setupUi(this);

  QStringList diarios;

 diarios << diario_apertura();
 diarios << diario_cierre();
 diarios << diario_regularizacion();
 diarios << diario_no_asignado();

    QString cadena2="select codigo,descripcion from diarios order by codigo";
    QSqlQuery query = ejecutarSQL(cadena2);
    while (query.next())
       {
           diarios << query.value(1).toString();
       }

  ui.diariocomboBox->addItems(diarios);

  connect(ui.aceptarpushButton,SIGNAL(clicked()),SLOT(procesar()));


}


void asignadiario::pasaPases( QStringList qpases )
{
	ui.listWidget->addItems(qpases);
}

void asignadiario::pasaPase (QString pase)
{
	ui.listWidget->addItem(pase);
}

void asignadiario::procesar()
{
    QString qdiario;
    if (ui.diariocomboBox->currentText()!=diario_no_asignado()) 
        qdiario = ui.diariocomboBox->currentText().left(-1).replace("'","''");
    else
        qdiario = "";
    for (int veces=0;veces<ui.listWidget->count();veces++)
        if (ui.listWidget->item(veces)->text()>0)
        	updateDiariodiarioasiento(qdiario,ui.listWidget->item(veces)->text());
    accept();
}

// Actualiza el diario de diario en un asiento
void asignadiario::updateDiariodiarioasiento (QString diario, QString pase) {
    QString cadquery = "update diario set diario='";
    cadquery += diario.left(-1).replace("'","''");
    cadquery += "' where pase=";
    cadquery += pase.left(-1).replace("'","''");
    ejecutarSQL(cadquery);
}

