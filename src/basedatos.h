#ifndef __BASEDATOS_H__
#define __BASEDATOS_H__

#include <QString>
#include <QDateTime>
#include <QtSql>

static const char NINGUNA = 0;
static const char MYSQL = 1;
static const char POSTGRES = 2;
static const char SQLITE = 3;


QString ejerciciodelafecha(QDate fecha);
void calculaprimerasientoejercicio(QString ejercicio);
void calculaprimerosasientos();
bool numeracionrelativa();
qlonglong primerasiento(QString ejercicio);
qlonglong primasejerciciodelafecha(QDate fecha);
QString numrelativa(QString numabsoluta);
QDate inicioejercicio(QString ejercicio);
QDate finejercicio(QString ejercicio);
QString ultimonumasiento(QString filtro);
QString descripcioncuenta(QString qcodigo);
double saldocuentaendiarioejercicio(QString cuenta,QString ejercicio);
QString nombreempresa();
int anchocuentas();
bool sobreescribeproxasiento();
qlonglong proximoAsiento ();
qlonglong proximoPase();
int existecodigoplan(QString cadena,QString *qdescrip);
int escuentadeivasoportado(const QString subcuenta);
int escuentadeivarepercutido(const QString subcuenta);
int ejerciciocerrado(QString ejercicio);
bool paseenasiento(QString pase, QString asiento);
int subgrupocongrupo(QString cadena);
int cuentaconsubgrupo(QString cadena);
int codigoconcuenta3digitos(QString cadena);
int unicoCodigoSubcuenta(QString *qcodigo,QString qdescrip);
void insertaenplan(QString codigo,QString descripcion);
void guardacambiosplan(QString codigo,QString descripcion);
int itemplaneliminado(QString qcodigo);
void eliminasubcuenta(QString qcodigo);
int cuentaendiario(QString cadena);
int existendatosaccesorios(QString cuenta, QString *razon, QString *ncomercial, QString *cif,
            QString *nifcomunitario, QString *domicilio, QString *poblacion,
            QString *codigopostal, QString *provincia, QString *pais,
            QString *tfno, QString *fax, QString *email, QString *observaciones,
            QString *ccc, QString *cuota);
void guardadatosaccesorios(QString cuenta, QString razon, QString ncomercial,QString cif,
            QString nifcomunitario, QString domicilio, QString poblacion,
            QString codigopostal, QString provincia, QString pais,
            QString tfno, QString fax, QString email, QString observaciones,
            QString ccc, QString cuota);
void eliminadatosaccesorios(QString qcodigo);
bool conanalitica(void);
bool conigic(void);
int existecodigoconcepto(QString cadena,QString *qdescrip);
void guardacambiosconcepto(QString codigo,QString descripcion);
void insertaenconceptos(QString codigo,QString descripcion);
void eliminaconcepto(QString qcodigo);
int existeclavetipoiva(QString cadena,double *tipo,double *re,QString *qdescrip);
QString clave_iva_defecto(void);
int esCuentadeGenero(const QString subcuenta);
int escuentadegasto(const QString subcuenta);
int escuentadeingreso(const QString subcuenta);
int existecodigosaldosubcuenta(QString cadena);
void insertasaldosubcuenta(QString codigo);
QString cuentadeivasoportado();
QString cuentadeivarepercutido();
void borraAsientoEjercicio(QString asiento,QString ejercicio);
void guardaFechaPago(QString cuenta, QString pase, QDate fecha , QString fact);
QString subcuentaanterior(QString qcodigo);
QString subcuentaposterior(QString qcodigo);
int ejerciciocerrando(QString ejercicio);
QDate fechaMaxAsiento(QString qasiento, QString ejercicio);
QDate fechaMinAsiento(QString qasiento, QString ejercicio);
QString diariodeasiento(QString qasiento);
int existeasiento(QString asiento, QString ejercicio);
int existeAsientoEspera(QString asiento);
void cadvalorestipoiva(QString cadena,QString *tipo,QString *re);
QString claveIva (QString pase);
double tipoivaefectivo(QString clave);
double tipoivanore(QString clave);
void actualizasaldo(QString cuenta,QString importe,bool cargo);
double saldocuentaendiario(QString cuenta);
double deudaCuentaenDiario(QString cuenta, QDate fecha);
QString ejercicio_igual_o_maxigual(QDate fecha);
QString numAsiento(QString pase);
int existeclaveiva(QString cadena,QString *qtipo,QString *qre,QString *qdescrip);
void guardacambiostiposiva(QString clave,QString tipo,QString re,QString descripcion);
void insertatipoiva(QString clave,QString tipo, QString re, QString descripcion);
void eliminatipoiva(QString qclave);
QString nifcomunitariocta(QString codigo);
QString cifcta(QString codigo);
void desbloqueasaldosmedios();
bool int_asientos_ej_cerrado(QString asientoinicial,QString asientofinal);
void pasasaldo(QString cuenta,QString importe,bool cargo);
bool cuentaenlibroiva(QString cuenta);
bool paseapertura(QString pase);
bool paseLibroiva(QString pase);
void actualizasaldos();
QString versionbd();
bool codsubdivis(QString qcodigo);
void cambiacuentaconta(QString origen, QString destino);
int existecodigodiario(QString cadena,QString *qdescrip);
void guardacambiosdiario(QString codigo,QString descripcion);
void insertaendiarios(QString codigo,QString descripcion);
int eliminadiario(QString qcodigo);
QString grupoGastos();
QString grupoIngresos();
QStringList listaOrdenadaSubcuentas(QString cuenta);
QStringList listaSubcuentas(QString cuenta);
int existeEquivalencia(QString busqueda,QString *qcuenta,bool *incor);
void guardaEquivalencia(QString equiv,QString cuenta, bool incorpora);
void insertaEquivalencia(QString equiv,QString cuenta, bool incorpora);
void eliminaEquivalencia(QString equiv);
int existePaseDiario(QString asiento,QDate fecha,QString cuenta,QString valor);

QSqlQuery ejecutarSQL (QString cadena);
//void updateDiarioCDwP (QString concepto, QString documento, QString numpase);
//void updateDiarioFDHwP (QDate fecha, QString debe, QString haber, QString pase);
void bloqueaTabla (QString tabla);
void bloqueaTablasAsientos();
void desbloqueaTablas();
char cualControlador ();
QString controlador ();

#endif // __BASEDATOS_H__


