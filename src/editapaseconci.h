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

#ifndef EDITAPASECONCI_H
#define EDITAPASECONCI_H

#include <QtGui>
#include "ui_editapaseconci.h"



class editapaseconci : public QDialog {
    Q_OBJECT
      public:
                editapaseconci();
                void pasadatos(QString numpase,QDate fecha,QString descripcion, QString debe, QString haber);
                //void recuperadatos(QDate *fecha,QString *descripcion, QString *debe, QString *haber);
                void updateDiarioFDHwP (QDate fecha, QString debe, QString haber, QString pase);
                void updateLibroivaFBCwP (QDate fecha, QString base, QString cuota, QString pase);
      private:
                Ui::editapaseconci ui;
                bool comadecimal;
                QString pase,claveiva;
                double civa,cre;
                int recalcularIvas();
      private slots:
                void debecambiado();
                void habercambiado();
                void botonaceptar();

};



#endif
