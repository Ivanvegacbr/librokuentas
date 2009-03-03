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

#ifndef TABLA_ASIENTOS_H
#define TABLA_ASIENTOS_H

//#include <QMainWindow>
#include <QtGui>
#include "ui_tabla_asientos.h"

class tabla_asientos  : public QDialog {
    Q_OBJECT
	public:
                tabla_asientos(bool concomadecimal, bool condecimales);
                //void preparaaib();
                //void preparaeib();
                void pasanumasiento( QString  cadasiento);
                void pasadatos( int fila, QString col0, QString col1, QString col2, QString col3, QString col4, QString col5, QString col6, QString col7, QString col8, QString col9, QString col10, QString col11, QString col12, QString col13, QString col14, QString col15, QString col16 );
                void pasaFechaInicial( QDate lafecha);
                void pasaFechasAsiento( QDate fechaini, QDate fechafin);
                void pasadiario(QString qdiario);
                void pasadatos1( int fila, QString col0, QString col1, QString col2,
                                 QString col3, QString col4, QDate fecha, QString col15, QString col16);
                void pasadatos2(int fila, QString col5, QString col6, QString col7,
                                 QString col8, QString col9, QString col10, QString col11, QString col15);
                void activaparaedicion();
                void incorporaEdicion();
                void chequeatotales();
                //void soportadoautonomo();
                //void repercutidoautonomo();
                //void aibautonomo();
                //void eibautonomo();
                bool botonincorporaractivado();

        private:
                Ui::tabla_asientos ui;
                QString cadasientoreal;
                QTime time;
                bool comadecimal;
                bool decimales;
                bool editando;
                //bool esaib;
                //bool eseib;
                //bool esaibautonomo;
                //bool eseibautonomo;
                //void procesaivasoportado(int fila,int columna);
                //void procesaivarepercutido(int fila, int columna);
                int ultimafila();
                //void procesabotonivarepercutido();
                //void incorporaedicion();
                void actualizaestado();
                void rellenaLinea(int fila,bool nueva);
                void backup();
                int existePase(int fil, QDate date, QString semana);
       private slots:
                void itemCambiado(QTableWidgetItem *check);
                void contenidocambiado(int fila,int columna);
                void posceldacambiada ( int currentRow, int col, int previousRow, int previousColumn );
                void borralinea( void );
                void borratodo();
                //void botonivapulsado();
                void verIvas();
                void verConcepto();
                void verDocumento();
                void botonesperapulsado();
                void pasarEspera(bool guardar);
                void pegar();
                void comboIvaCambiado();
                void mayor();
                void fechacambiada();
                void imprimirAsiento();
                void cancelar();
       public slots:
                void incorporar();
};


#endif 
 
 
