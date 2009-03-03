/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

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

#include "infobd.h"
#include <QSqlDatabase>
#include <QSqlQuery>

infobd::infobd() : QDialog() {
    ui.setupUi(this);

    QSqlDatabase bd;
    bd=QSqlDatabase::database();
    ui.bdtextLabel->setText(bd.databaseName());
    ui.usuariotextLabel->setText(bd.userName());
    ui.hosttextLabel->setText(bd.hostName());
    ui.conttextLabel->setText(bd.driverName());

    QString consulta="select version();";
    QSqlQuery query(consulta);
    QString laversion;

    if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           if (bd.driverName()=="QMYSQL3" || bd.driverName()=="QMYSQL") laversion="MySQL ";
           laversion+=query.value(0).toString();
           ui.vtextEdit->setText(laversion);
         }
    }

}

