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

#ifndef LIBROIVA_H
#define LIBROIVA_H

#include <QtGui>
#include "ui_libroiva.h"



class libroiva : public QDialog {
    Q_OBJECT
      public:
                libroiva();
                void hazaib();
                void hazeib();
                void hazrepercutido();
                void hazsoportadoprorrata();
                void hazrecibidas_autofactura();
                void hazemitidas_autofactura();
                void hazemitidas_rectificativa();
                double totalProveedor(QString cuenta, QDate FIni, QDate FFin);
      private:
                Ui::libroiva ui;
                bool soportado,aib,eib,soportadoprorrata;
                bool recibidas_autofactura,emitidas_autofactura,emitidas_rectificativa;
                bool comadecimal,decimales;
                void generalatexsoportado();
                void generalatexrepercutido();
                void generalatexsoportadoprorrata();
                QString nombrefichero();

      private slots:
                void consultatex();
                void imprime();

};



#endif 
