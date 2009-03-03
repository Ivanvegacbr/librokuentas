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

#ifndef ASIGNADIARIO_H
#define ASIGNADIARIO_H

#include <QtGui>
#include "ui_asignadiario.h"



class asignadiario : public QDialog {
    Q_OBJECT
      public:
                asignadiario();
                void pasaPases( QStringList qpases );
                void pasaPase(QString pase);
      private:
                Ui::asignadiario ui;
                void updateDiariodiarioasiento (QString diario, QString pase);
                //QString asiento;
      private slots :
                void procesar();

};



#endif 
 
