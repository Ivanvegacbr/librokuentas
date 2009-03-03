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

#ifndef ACUMULADOSMES_H
#define ACUMULADOSMES_H

#include <QtGui>
#include <QSqlQuery>
#include "ui_acumuladosmes.h"



class acumuladosmes : public QDialog {
    Q_OBJECT
      public:
                acumuladosmes();
                void pasacodigocuenta(QString codigo,QDate fecha);
                QSqlQuery selectDatos (QString tipo_diario,QDate fechainicial,QDate fechafinal,QString sub);
                QSqlQuery selectDatosRestantes (QDate fechainicial, QDate fechafinal, QString sub);
      private:
                Ui::acumuladosmes ui;
                bool comadecimal,decimales;
                void cargadatos();
                void ctaexpandepunto();
      private slots:
                void botonbuscasubcuentapulsado();
                void subcuentacambiada();
                void finedicsubcuenta();
                void refrescar();
                void subcuentaprevia();
                void subcuentasiguiente();
                void txtexport();

};



#endif 
