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

#ifndef LISTAVENCI_H
#define LISTAVENCI_H

#include <QtGui>
#include "ui_listavenci.h"
#include <QSqlTableModel>
#include "diario.h"

class CustomSqlModel5 : public QSqlTableModel
    {
        Q_OBJECT

    public:
        CustomSqlModel5(QObject *parent = 0);
        QVariant data(const QModelIndex &item, int role) const;
        QVariant datagen(const QModelIndex &index, int role) const;
    private:
        bool comadecimal, decimales;
    };


class listavenci : public QDialog {
    Q_OBJECT
        public:
                 listavenci();
                ~listavenci();
                void pasaSemana(QString qsem, QString ejer);
                void pasaCuenta(QString subcuenta);
        private:
                Ui::listavenci ui;
                bool comadecimal, decimales;
                CustomSqlModel5 *model;
                void asignafiltro();
                QString paseActual();
                QString documentoActual();
                QString cuentaActual();
                double debeActual();
                double haberActual();
                QDate fechaActual();
                void calculasuma();
                void generalatex();
       private slots:
                void cuentacheckBoxcambiado( int activado );
                void trasctaordenante();
                void buscacuenta();
                void ctaordenantecambiada();
                void refrescar();
                void infovencipase();
                void procesar();
                void anular();
                void editar();
                void imprimir();
};

#endif
