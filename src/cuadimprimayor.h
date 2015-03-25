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

#ifndef CUADIMPRIMAYOR_H
#define CUADIMPRIMAYOR_H
#include <QSqlTableModel>

#include <QtGui>
#include <QtSql>
#include "ui_cuadimprimayor.h"
#include "consmayor.h"


class cuadimprimayor : public QDialog {
    Q_OBJECT
	public:
                cuadimprimayor(bool concomadecimal, bool condecimales);
                void pasadatos( QString qsubcuenta, QDate qfecha );
                void generalatexmayor( QString qsubcuentaini, QString qsubcuentafinal, QDate fechainicial, QDate fechafinal );
                QString generalatexfactura( QString qsubcuentaini, QString qsubcuentafinal, QDate fechainicial, QDate fechafinal );
                QSqlQuery select5Diariofechascuentaorderfechapase (QDate inicial, QDate final, QString cuenta);
                
        private:
                Ui::cuadimprimayor ui;
                bool comadecimal;
                bool decimales;
                void ctaexpandepunto();
                void finalexpandepunto();
                void fechasok();
                QDate selectAperturaejerciciosaperturacierre(QString ini, QString fin);
                QDate selectCierreejerciciosaperturacierre(QString ini, QString fin);
                consmayor *c;
                QDate fechaactual;
                
        private slots:
                void finedicsubcuenta();
                void botonsubcuentapulsado();
                void botonimprimepulsado();
                void botonGenFactura();
                void botonprevisualizapulsado();
                void ctainicialcambiada();
                void botonctafinalpulsado();
                void finedicfinsubcuenta();

};





#endif 
 
 
