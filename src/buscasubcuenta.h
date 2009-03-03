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

#ifndef BUSCASUBCUENTA_H
#define BUSCASUBCUENTA_H
#include <QSqlTableModel>
#include "ui_buscasubcuenta.h"


class buscasubcuenta : public QDialog {
    Q_OBJECT
	public:
                buscasubcuenta(QString cadena);
                ~buscasubcuenta();
                QString seleccioncuenta( void );
                void cambiatitulo(QString titulo);
        private:
                Ui::buscasubcuenta ui;
                QSqlTableModel *modeloplan;
        private slots :
                void ComienceRadioBotoncambiado();
                void ContengaRadioBotoncambiado();
                void codigosubcuentacambiado();
                void titulocuentacambiado();
                void fuerafocosubcuenta();

};


#endif
