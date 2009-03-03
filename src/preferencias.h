/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

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

#ifndef PREFERENCIAS_H
#define PREFERENCIAS_H

#include <QtGui>
#include "ui_preferencias.h"

#define NADA 0
#define EJERCICIOACTUAL 1
#define ULTIMOS30DIAS 2
#define ULTIMOS30ASIENTOS 3

#define FECHA 0
#define ASIENTO 1
#define CUENTA 2

#define COMADECIMAL 1
#define PUNTODECIMAL 0

// #define NUMERACIONORIGINAL 0
// #define PRIMERASIENTO1 1

class preferencias : public QDialog {
    Q_OBJECT
	public:
        preferencias();
        void pasadirtrabajo(QString directorio);
        void pasavisordvi(QString visor);
        void pasaaplicimprimir(QString aplic);
        void pasanavegador(QString navegador);
        void pasafiltropor(int filtro);
        void pasaordenarpor(int orden);
        void pasaestilonumerico(int estilo);
        void pasasindecimales(bool sindecimales);
        // void pasanumeracion(int numeracion);
        void pasafiltrodiariopersonalizado(QString filtro);
        void pasafiltrartex(bool filtrartext);
        void pasaidioma(int qidioma);

        QString dirtrabajo();
        QString visordvi();
        QString aplicimprimir();
        QString navegador();
        int filtropor();
        int ordenarpor();
        int estilonumerico();
        bool sindecimales();
        int numeracion();
        bool esfiltrartex();
        QString filtrodiariopersonalizado();
        int qidioma();
                

    private:
        Ui::preferencias ui;
        QString selectDir(bool dir, QString dirIni);
	private slots:
		void dirTrabajoPulsado();
		void visorPulsado();
		void imprPulsado();
		void navegadorPulsado();
	    void filtrarporcambiado();
		void filtrarinicambiado();

};

#endif 
