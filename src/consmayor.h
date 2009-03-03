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

#ifndef CONSMAYOR_H
#define CONSMAYOR_H

#include <QtGui>
#include <QtSql>
#include "ui_consmayor.h"

class consmayor : public QDialog {
    Q_OBJECT
	public:
                consmayor(bool concomadecimal, bool condecimales);
                void pasadatos( QString qsubcuenta, QDate qfecha );
                qlonglong selectCountAsiento(QDate inicial, QDate final, QString condicion);
                QSqlQuery selectDiario (QDate inicial, QDate final, QString condicion);
                QSqlQuery selectSumasDiario (QDate fechainiejercicio, QDate inicial, QString condicion);
                QSqlQuery selectSumasDiarioHasta (QDate inicial, QString condicion);

        private:
                Ui::consmayor ui;
                bool comadecimal;
                bool decimales;
                void cargadatos();
                void ctaexpandepunto();
                void latexintervalo();

	private slots:
                void botonsubcuentapulsado();
                void refrescar();
                void finedicsubcuenta();
                void subcuentaprevia();
                void subcuentasiguiente();
                void imprimir();
                void subcuentacambiada();
                void editarpulsado();
                //void origenpercambiado();
                //void finalpercambiado();
                void intervalogroupcambiado();
                void intervaloCambiado( int index );
                void copiar();

};


#endif
