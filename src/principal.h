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

#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "ui_principal.h"
#include <QtSql>
#include <QSqlQueryModel>
#include "preferencias.h"
#include "diario.h"
#include "inicial.h"
//#include "ivarepercutido.h"
//#include "amortbi.h"
//#include "diarios.h"


class Mrconta : public QMainWindow {
      Q_OBJECT
	  public:
                  Mrconta();
		  void funcedasiento(QString elasiento, QString eje);
                  bool cargapreferencias(bool *bdabierta);
                  QString condicionesfiltrodefecto(void);
                  QString ordenarpor(void);
                  bool oknosalir();
                  bool abrebasedatos(QString vpghost,QString vpgdbname,QString vpguser,
                            QString vpgpassword,QString vcontrolador, QString vpuerto);
                  bool conexion0();

          private:
                  Ui::Mrconta ui;
                  QString entrada;
                  QString dirtrabajo;
                  QString fichconexiones;
	              QString dirconfig;
		          QString fichconfig;
                  QString visordvi;
                  QString aplicacionimprimir;
                  QString navegador;
                  int filtrarpor;
                  int ordendiario;
                  int estilonumerico;
                  int numeracion;
                  bool sindecimales;
                  int anchocol[11];
                  bool filtrartex;
                  QString filtropersonalizado;
                  QString filtroactivo;
                  int idioma;
                  diario *punterodiario;
                  QString ulmodelo;
                  //void testigic();
                  bool exportaplan(QString fichero,bool subcuentas);
                  bool importarfichplan(QString cadfich);
                  void actualizade07();

    private slots:
	          void salir();
                  void qpreferencias();
		  void grabapreferencias();
                  void conexionc();
                  void nuevaempresa();
                  void filtrardiario();
                  void ejs();
                  void configuracion();
                  void refrescardiario();
                  void edplan();
                  void edsubcuentas();
                  void edicionconceptos();
                  void buscasubcuentas();
                  void ayuda();
                  void seguridad();
                  void infoconex();
                  void cuadacercade();
                  void acuerdolicencia();
                  void acuerdolicenciaesp();
                  //void borranuevoplan();
                  void qordendiario(bool numero);
                  void buscarconcepto();
                  void nuevoasiento();
                  void actualizaplan();
                  void exportplan();
                  void exportplansubcuentas();
                  void ImprimeDiario();
                  void generarpdf();
                  void actuSaldos();
                  void asientosEspera();
                  void editaasiento();
                  void editaNumAsiento();
                  void borraasiento();
                  void nuevoAsientoAuto();
                  void genbss();
                  void procvencimientos();
                  void vtosSemana();
                  void vtosCuenta();
                  void qtiposiva();
                  void edPase();
                  void edcondoc();
                  void librosagr();
                  void grafOper();
                  void consultatex();
                  void libroFactRec();
                  void acummes();
                  void consultaplan();
                  void consultamayor();
                  void importaLaCaixa();
                  void imprimemayor();
                  void marcarcerrado();
                  void suprimircierre();
                  void editarEquivalencias();
                  void importasientos();
                  void copiar();
                  void tiposdiario();
                  void asignardiario();

};


#endif 
