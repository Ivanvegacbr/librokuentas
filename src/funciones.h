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

#include <QString>
//#include <QtSql>
#include <QVariant>

#define LINEASPAGINA 35
//#define DEBUG 1
//#define APPDIRNAME "libroK"


QString convacoma(QString cad);
QString puntuanumerocomadec(QString origen);
QString puntuanumeropuntodec(QString origen);
QString trad_fecha();
QString trad_usuario();
QString trad_asiento();
QString trad_cuenta();
QString trad_concepto();
QString trad_documento();
QString trad_debe();
QString trad_haber();
QString trad_diario();
QString trad_pase();
QString filtro_a_lingu(QString fuente);
QString lingu_a_filtro(QString fuente);
QString trayconfig(void);
QString convapunto(QString cadena);
QString quitacomillas(QString cadena);
bool fechacorrespondeaejercicio(QDate fecha);
bool fechadejerciciocerrado(QDate fecha);
int existesubcuenta(QString codigo);
QString encriptarTexto(QString texto);
QString desencriptarTexto(QString llave);
QString expandepunto(QString cadena,int anchocad);
QString formateanumero(double numero,bool comadecimal, bool decimales);
QString diario_apertura();
QString diario_general();
QString diario_no_asignado();
QString iva_mixto();
QString diario_cierre();
QString previsiones();
QString diario_regularizacion();
QString dirtrabajodefecto();
QString dirtrabajo(void);
int idiomaconfig(void);
QString fich_ingles();
QString fich_catalan();
QString filtracad(QString origen);
QString mcortaa(QString cadena, uint num);
QString programa_imprimir();
QString programa_imprimir_defecto();
QString visordvidefecto();
QString visordvi();
bool filtrartexaxtivado();
QString adapta(QString cadena);
void filtratex(QString cadfich);
bool haycomadecimal();
bool haydecimales();
QString formateanumerosep(double numero,bool comadecimal, bool decimales);
QString cadenamedia();
QString cadpositivo();
QString tipoNumerico();
QString tipoFecha();
QString tipoCaracteres();
QString tipoSubcuenta();
QString tipoDEBE();
QString tipoHABER();
QString tipoCI();
bool chequeaformula(QString formula);
bool cadnumvalido(QString cadnum);
bool cadfechavalida(QString cadfecha);
QString ciamort();
QString cadmes(int mes);
int imprimelatex(QString qfichero);
//int imprimelatex2(QString qfichero);
//int consultalatex(QString qfichero);
int consultalatex2(QString qfichero);
int consultalatex2fichabs(QString qfichero);
int generapdffichabs(QString qfichero);
QString traydoc(void);
QString traynombrefichayuda(void);
QString fsplash();
bool eswindows();
QString windirprogram();
QString noejercicio();
QString comandodescrip();
double calculaValor( QString calculo );
QColor randomColor(bool trans);

