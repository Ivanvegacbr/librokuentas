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

#ifndef DIARIO_H
#define DIARIO_H

#include <QtGui>
#include "ui_diario.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "funciones.h"

class CustomSqlModel : public QSqlQueryModel
    {
        Q_OBJECT

    public:
        CustomSqlModel(QObject *parent = 0);
        void pasainfo(bool qcomadecimal, bool qsindecimales);
        QVariant data(const QModelIndex &item, int role) const;
        QVariant datagen(const QModelIndex &index, int role) const;
        void chknumeracion();
    private:
        bool primerasiento1, comadecimal, sindecimales;
        // qlonglong primas;
    };


class diario: public QWidget {
    Q_OBJECT
        public:
 	   diario();
           void activaconfiltro(QString filtro,bool qcomadecimal,bool sindecimales);
           void pasafiltro(QString filtro,bool qcomadecimal, bool sindecimales);
           void pasafiltroedlin(QString filtro);
           int anchocolumna(int columna);
           void pasaanchocolumna(int columna,int ancho);
           void pasaanchos(int ancho[]);
           void muestratabla(void);
           void refresca();
           void irfinal();
           QString subcuentaactual();
           qlonglong asientoactual();
           QDate fechapaseactual();
           QString conceptoactual();
           QString documentoactual();
           QModelIndex indiceactual(void);
           void situate(QModelIndex indice);
           CustomSqlModel *modelo();
           QTableView *tabladiario();
           QDate ciactual();
           qlonglong paseactual();
           double debe();
           double haber();
           void copiar();
           ~diario();
        private:
           Ui::diario ui;
           CustomSqlModel *model;
           bool comadecimal, sindecimales;
       private slots:
           void infocuentapase(QModelIndex primaryKeyIndex);
           void ordenarColumna(QModelIndex headerIndex);

};



#endif
