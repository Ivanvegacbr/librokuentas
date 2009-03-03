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

#ifndef BSS_H
#define BSS_H

#include <QtGui>
#include "ui_bss.h"
#include "grafico.h"
#include <QSqlTableModel>


class bss : public QDialog {
    Q_OBJECT
	public:
                bss();
        private:
                Ui::bss ui;
                grafico *gr;
                bool comadecimal;
                bool decimales;
                int numdiarios,numPeriodos;
                QString fichero;
                QString sumadh(bool subcuenta, bool debe, QString codigo, QDate desde,
                               QDate hasta);
                void generalatex();
                void actualizar(bool table);

        private slots:
                void refrescar();
                void varsinmovs();
                void txtexport();
                void imprimir();
                void gentex();
                void fijaFechas();
                //void buscapulsado();
                void activaactualiza();
                void ejercicioCambiado();
                void intervaloCambiado( int index );
                void verGrafico();
};




#endif 
 
