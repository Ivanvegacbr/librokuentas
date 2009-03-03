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

#include "creaempresa.h"
#include "basedatos.h"
#include "funciones.h"
#include <QMessageBox>

creaempresa::creaempresa() : QDialog() {
    ui.setupUi(this);
   ui.plancomboBox->insertItem(0,planvacio());
   QDir directorio(trayconfig());

   QStringList filters;
   filters << "*.pln";
   directorio.setNameFilters(filters);

   directorio.setSorting(QDir::Name);
   ui.plancomboBox->insertItems(0,directorio.entryList());
   QStringList list = QSqlDatabase::drivers();
   int veces=0;
   while (veces<list.size())
      {
       if ( !list.at(veces).contains("PSQL") && !list.at(veces).contains("MYSQL")) list.removeAt(veces);
          else veces++;
      }
   ui.controladorcomboBox->insertItems(0,list);

}

QString creaempresa::planvacio()
{
 return (tr("Plan contable vacío"));
}

bool creaempresa::creabd()
{
  if (ui.bdlineEdit->text().length()==0)
     {
      QMessageBox::warning( this, tr("Nueva empresa"),tr("ERROR EN NOMBRE DE BASE DE DATOS"));
      return false;
     }
  
   QString vcontrolador=ui.controladorcomboBox->currentText();
   QSqlDatabase defaultDB = QSqlDatabase::addDatabase( vcontrolador );
   if ( defaultDB.isDriverAvailable (vcontrolador) )
       {
         if (ui.controladorcomboBox->currentText()=="QPSQL7"
             || ui.controladorcomboBox->currentText()=="QPSQL") defaultDB.setDatabaseName("template1");
         else
            {
              if (ui.controladorcomboBox->currentText()=="QMYSQL3"
                   || ui.controladorcomboBox->currentText()=="QMYSQL") defaultDB.setDatabaseName("mysql");
	      else return false;
            } 
         defaultDB.setUserName(ui.usuariolineEdit->text().toLower());
         defaultDB.setPassword(ui.clavelineEdit->text());
         defaultDB.setHostName(ui.hostlineEdit->text());
         ui.puertolineEdit->setText(ui.puertolineEdit->text().trimmed());
         if (ui.puertolineEdit->text().length()>0)
            {
             defaultDB.setPort(ui.puertolineEdit->text().toInt());
            }
         if ( !defaultDB.open() ) 
            {
             QMessageBox::warning( this, tr("Apertura de base de datos"),
              tr("IMPOSIBLE ABRIR BASE DE DATOS ")+defaultDB.databaseName());
             return false;
            }
         // La base de datos se ha abierto, ya podemos executar comandos
       }
        else
              {
                 QMessageBox::warning( this, tr("Apertura de base de datos"),
                 tr("IMPOSIBLE OPERAR BASE DE DATOS CON ")+vcontrolador);
	         return false;
              }

// ---------------------------------------------------------------------------------------------------
   QString cadena;
   cadena="create database ";
   cadena+=ui.bdlineEdit->text().toLower();
   if (ui.controladorcomboBox->currentText()=="QMYSQL3" || ui.controladorcomboBox->currentText()=="QMYSQL")
     {
       cadena+=" default character set ";
       cadena+="utf8;";
     }
   if ((ui.controladorcomboBox->currentText()=="QPSQL7") ||(ui.controladorcomboBox->currentText()=="QPSQL") )
     {
       cadena+=" encoding='";
       cadena+="UNICODE';";
     }
   ejecutarSQL(cadena);
   // abrimos la base de datos
   defaultDB.close();
   defaultDB.setDatabaseName(ui.bdlineEdit->text().toLower());
   defaultDB.setUserName(ui.usuariolineEdit->text().toLower());
   defaultDB.setPassword(ui.clavelineEdit->text());
   defaultDB.setHostName(ui.hostlineEdit->text());
   if (ui.puertolineEdit->text().length()>0)
       {
        defaultDB.setPort(ui.puertolineEdit->text().toInt());
       }
   if (!defaultDB.open())
     {
        QMessageBox::warning( this, tr("Apertura de base de datos"),
        tr("No se puede abrir la base de datos creada"));
        return false;
     }  else
	     {
	      // llamanos a crear la estructura de la base de datos
	      creatablasiniciales();
	      importaplan();
	      return true;
	     }

}



void creaempresa::creatablasiniciales()
{

 // AQUÍ partimos siempre de cero, es decir, no hay conexión
  QSqlDatabase bd=QSqlDatabase::database ();
  QString acontrolador= bd.driverName();
  bool cmysql=(acontrolador=="QMYSQL3" || acontrolador=="QMYSQL") ;

   /*QSqlQuery query("CREATE TABLE amortcontable ("
                                    "ejercicio     varchar(40),"
                                    "asiento       bigint );");
      
  ejecutarSQL("CREATE TABLE amortfiscalycontable ("
                       "ejercicio         varchar(40),"
                       "cuenta_activo     varchar(40),"
                       "codigo_activo     varchar(40),"
                       "cuenta_am_acum    varchar(40),"
                       "cuenta_gasto      varchar(40),"
                       "dotacion_contable numeric(14,2),"
                       "dotacion_fiscal   numeric(14,2));");*/
      
  ejecutarSQL("CREATE TABLE borrador ("
                       "asiento       bigint,"
                       "usuario       varchar(80),"
                       "cuenta        varchar(40),"
                       "concepto      varchar(255),"
                       "debe          varchar(40),"
                       "haber         varchar(40),"
                       "documento     varchar(255),"
                       "ctabaseiva    varchar(40),"
                       "baseiva       varchar(40),"
                       "claveiva      varchar(40),"
                       "tipoiva       varchar(40),"
                       "tipore        varchar(40),"
                       "cuotaiva      varchar(40),"
                       "cuentafra     varchar(40),"
                       "diafra        varchar(40),"
                       "mesfra        varchar(40),"
                       "anyofra       varchar(40),"
                       "soportado     varchar(40),"
                       "ci            varchar(40),"
                       "prorrata      varchar(40) default '',"
                       "rectificativa varchar(40) default '',"
                       "autofactura   varchar(40) default '');");
                       //"PRIMARY KEY (asiento) );");
  
  // -------------------------------------------------------------------------------------------------
     /*if (cmysql)
                     ejecutarSQL("CREATE TABLE cab_as_modelo ("
                          "asientomodelo         varchar(255),"
                          "fecha                 varchar(255) ) ;");
	 else
                     ejecutarSQL("CREATE TABLE cab_as_modelo ("
                          "asientomodelo         varchar,"
                          "fecha                 varchar ) ;");
   // ----------------------------------------------------------------------------------------------------
   if (cmysql)
              ejecutarSQL("CREATE TABLE cabeceraestados ("
                         "titulo                  varchar(255),"
                         "cabecera               varchar(255),"
                         "parte1                  varchar(255),"
                         "parte2                  varchar(255),"
                         "observaciones           varchar(255),"
                         "formulabasepor          varchar(255),"
                         "fechacalculo            date,"
                         "ejercicio1              varchar(255),"
                         "ejercicio2              varchar(255),"
                         "analitica               bool,"
                         "haycolref               bool,"
                         "colref                  varchar(80),"
                         "ci                      varchar(80),"
                         "desglose                bool,"
                         "des_cabecera            varchar(255),"
                         "des_pie                 varchar(255),"
                         "diarios                 varchar(255),"
                         "estadosmedios           bool,"
                         "valorbasepor1           numeric(14,2),"
                         "valorbasepor2           numeric(14,2) ) ;");
       else
              ejecutarSQL("CREATE TABLE cabeceraestados ("
                         "titulo                  varchar,"
                         "cabecera                varchar,"
                         "parte1                  varchar,"
                         "parte2                  varchar,"
                         "observaciones           varchar,"
                         "formulabasepor          varchar,"
                         "fechacalculo            date,"
                         "ejercicio1              varchar,"
                         "ejercicio2              varchar,"
                         "analitica               bool,"
                         "haycolref               bool,"
                         "colref                  varchar(80),"
                         "ci                      varchar(80),"
                         "desglose                bool,"
                         "des_cabecera            varchar,"
                         "des_pie                 varchar,"
                         "diarios                 varchar,"
                         "estadosmedios           bool,"
                         "valorbasepor1           numeric(14,2),"
                         "valorbasepor2           numeric(14,2) ) ;");*/
       
// -------------------------------------------------------------------------------------------------         
   ejecutarSQL("CREATE TABLE conceptos ("
                        "clave        varchar(10),"
                        "descripcion  varchar(255),"
                        "PRIMARY KEY (clave) );");
// -------------------------------------------------------------------------------------------------      
   if (cmysql)
             ejecutarSQL("CREATE TABLE configuracion ("
                        "empresa        varchar(255),"
                        "nif            varchar(255),"
                        "domicilio      varchar(255),"
                        "poblacion      varchar(255),"
                        "cpostal        varchar(255),"
                        "provincia      varchar(255),"
                         "email          varchar(255),"
                         "web            varchar(255),"
                         "anchocuentas   integer,"
                         "cuenta_iva_soportado varchar(255),"
                         "cuenta_iva_repercutido varchar(255),"
                         "cuenta_ret_irpf varchar(255),"
                         "cuentasapagar   varchar(255),"
                         "cuentasacobrar  varchar(255),"
                         "clave_iva_defecto varchar(255),"
                         "clave_gastos   varchar(255),"
                         "clave_ingresos  varchar(255),"
                         "cuenta_pyg  varchar(255),"
                         "prox_asiento     bigint,"
                         "prox_pase        bigint,"
                          "prox_vencimiento bigint,"
                          "id_registral varchar(255),"
                          "numrel bool,"
                          "igic     bool,"
                          "analitica bool,"
                          "version varchar(40),"
                          "bloqsaldosmedios bool,"
                          "prorrata_iva     numeric(5,2) default 0,"
                          "prorrata_especial bool default false);");
       else
             ejecutarSQL("CREATE TABLE configuracion ("
                        "empresa        varchar,"
                        "nif            varchar,"
                        "domicilio      varchar,"
                        "poblacion      varchar,"
                        "cpostal        varchar,"
                        "provincia      varchar,"
                         "email          varchar,"
                         "web            varchar,"
                         "anchocuentas   integer,"
                         "Cuenta_IVA_Soportado varchar,"
                         "Cuenta_IVA_Repercutido varchar,"
                         "cuenta_ret_irpf varchar,"
                         "cuentasapagar   varchar,"
                         "cuentasacobrar  varchar,"
                         "Clave_IVA_defecto varchar,"
                         "Clave_gastos   varchar,"
                         "Clave_ingresos  varchar,"
                         "cuenta_pyg  varchar,"
                         "prox_asiento     bigint,"
                         "prox_pase        bigint,"
                          "prox_vencimiento bigint,"
                          "id_registral varchar(255),"
                          "numrel bool,"
                          "igic     bool,"
                          "analitica bool,"
                          "version varchar(40),"
                          "bloqsaldosmedios bool,"
                          "prorrata_iva     numeric(5,2) default 0,"
                          "prorrata_especial bool default false);");
// ----------------------------------------------------------------------------------------------------------      
 ejecutarSQL("CREATE TABLE datossubcuenta ("
                      "cuenta         varchar(40),"
                       "razon          varchar(80),"
                       "nombrecomercial varchar(80),"
                       "cif            varchar(80),"
                        "nifcomunitario varchar(40),"
                       "domicilio      varchar(80),"
                       "poblacion      varchar(80),"
                       "codigopostal   varchar(40),"
                       "provincia      varchar(80),"
                       "pais           varchar(80),"
                       "tfno           varchar(80),"
                        "fax            varchar(80),"
                       "email          varchar(80),"
                       "ccc            varchar(80),"
                       "cuota          varchar(40),"
                       "observaciones  varchar(80),"
                       "PRIMARY KEY (cuenta) );");
//---------------------------------------------------------------------------------------------------------      
// ----------------------------------------------------------------------------------------------------------      
/* ejecutarSQL("CREATE TABLE ci ("
                       "codigo         varchar(40),"
                       "descripcion    varchar(80),"
                       "nivel          integer );");
//---------------------------------------------------------------------------------------------------------      
 if (cmysql)
            ejecutarSQL("CREATE TABLE det_as_modelo ("
                      "asientomodelo           varchar(255),"
                      "cuenta                  varchar(255),"
                      "concepto                varchar(255),"
                      "expresion               varchar(255),"
                      "d_h                     varchar(255),"
                      "ci                      varchar(255),"
                      "baseiva                 varchar(255),"
                     "cuentafra               varchar(255),"
                     "cuentabaseiva           varchar(255),"
                     "claveiva                varchar(255),"
                     "documento               varchar(255),"
                     "orden                    int ) ;");
     else
            ejecutarSQL("CREATE TABLE det_as_modelo ("
                      "asientomodelo           varchar,"
                      "cuenta                  varchar,"
                      "concepto                varchar,"
                      "expresion               varchar,"
                      "d_h                     varchar,"
                      "ci                      varchar,"
                      "baseiva                 varchar,"
                     "cuentafra               varchar,"
                     "cuentabaseiva           varchar,"
                     "claveiva                varchar,"
                     "documento               varchar,"
                     "orden                   int ) ;");*/
// -----------------------------------------------------------------------------------------------------      
 ejecutarSQL("CREATE TABLE diario ("
      "asiento       bigint,"
      "pase          bigint,"
      "fecha         date,"
      "cuenta        varchar(40),"
      "debe          numeric(14,2),"
      "haber         numeric(14,2),"
      "concepto      varchar(255),"
      "documento     varchar(255),"
      "diario        varchar(40),"
      "ci            varchar(40),"
      "usuario       varchar(80),"
      "conciliado    bool default false,"
      "dif_conciliacion varchar(40) default '',"
      "PRIMARY KEY (pase), KEY (cuenta), UNIQUE (pase) );");
// ---------------------------------------------------------------------------------------------------------
ejecutarSQL("CREATE TABLE ejercicios ("
      "codigo        varchar(40),"
      "apertura      date,"
      "cierre        date,"
      "cerrado       bool,"
      "cerrando      bool,"
      "primerasiento bigint,"
      "base_ejercicio varchar(80) default '',"
      "base_presupuesto varchar(80) default '',"
      "presupuesto_base_cero bool default true,"
      "incremento numeric(14,4) default 0,"
      "PRIMARY KEY (codigo));");
// -----------------------------------------------------------------------------------------------------------      
/*if (cmysql)
     ejecutarSQL("CREATE TABLE estados ("
      "titulo                  varchar(255),"
      "apartado                varchar(255),"
      "parte1                  bool,"
      "clave                   varchar(255),"
      "nodo                    varchar(255),"
      "formula                 varchar(2000),"
      "referencia              varchar(80),"
      "importe1                numeric(14,2),"
      "importe2                numeric(14,2),"
      "calculado               bool,"
      "primary key (titulo, nodo, parte1)) ;");
    else
     ejecutarSQL("CREATE TABLE estados ("
      "titulo                  varchar,"
      "apartado                varchar,"
      "parte1                  bool,"
      "clave                   varchar,"
      "nodo                    varchar,"
      "formula                 varchar,"
      "referencia              varchar(80),"
      "importe1                numeric(14,2),"
      "importe2                numeric(14,2),"
      "calculado               bool,"
      "primary key (titulo, nodo, parte1)) ;");*/
      
 // --------------------------------------------------------------------------------------------
    
ejecutarSQL("CREATE TABLE libroiva ("
      "pase          bigint,"
      "cta_base_iva  varchar(40),"
      "base_iva      numeric(14,2),"
      "clave_iva     varchar(4),"
      "tipo_iva      numeric(5,2),"
      "tipo_re       numeric(5,2),"
      "cuota_iva     numeric(14,2),"
      "cuenta_fra    varchar(40),"
      "fecha_fra     date,"
      "soportado     bool,"
      "aib                  bool,"
      "eib                  bool,"
      "prorrata numeric(5,2) default 1,"
      "rectificativa bool default false,"
      "autofactura bool default false,"
      "PRIMARY KEY (pase) );");
// ----------------------------------------------------------------------------------------------      
/*ejecutarSQL("CREATE TABLE planamortizaciones ("
      "cuenta_activo     varchar(40),"
      "fecha_func        date,"
      "codigo_activo     varchar(40),"
      "cuenta_am_acum    varchar(40),"
      "cuenta_gasto      varchar(40),"
      "valor_residual      numeric(14,2),"
      "amort_personalizada bool,"
      "coef_amort_contable float8,"
      "coef_amort_fiscal   float8,"
      "amort_fiscal_1ejer  bool );");
 // --------------------------------------------------------------------------------------------
ejecutarSQL("CREATE TABLE amortpers ("
      "cuenta         varchar(40),"
      "ejercicio      varchar(40),"
      "importe        numeric(14,2));");*/
// --------------------------------------------------------------------------------------------
if (cmysql)
      ejecutarSQL("CREATE TABLE plancontable ("
      "codigo       varchar(40),"
      "descripcion  varchar(255),"
      "auxiliar bool default false,"
      "PRIMARY KEY (codigo) );");
    else
      ejecutarSQL("CREATE TABLE plancontable ("
      "codigo       varchar(40),"
      "descripcion  varchar,"
      "auxiliar bool default false,"
      "PRIMARY KEY (codigo) );");

if (cmysql)
      ejecutarSQL("CREATE TABLE nuevoplan ("
      "codigo       varchar(40),"
      "descripcion  varchar(255),"
      "PRIMARY KEY (codigo) );");
    else
      ejecutarSQL("CREATE TABLE nuevoplan ("
      "codigo       varchar(40),"
      "descripcion  varchar,"
      "PRIMARY KEY (codigo) );");

ejecutarSQL("CREATE TABLE equivalenciasplan ("
      "cod       varchar(40),"
      "equiv     varchar(40),"
      "incorporar bool default true,"
      "PRIMARY KEY (cod) );");

ejecutarSQL("CREATE TABLE saldossubcuenta ("
      "codigo       varchar(40),"
      "saldo        numeric(14,2),"
      "saldomedio1  numeric(14,2),"
      "saldomedio2  numeric(14,2),"
      "PRIMARY KEY (codigo) );");
      
ejecutarSQL("CREATE TABLE tiposiva ("
      "clave        varchar(4),"
      "tipo         numeric(5,2),"
      "re           numeric(5,2),"
      "descripcion  varchar(80),"
      "PRIMARY KEY (clave) );");
      
/*if (cmysql)
      ejecutarSQL("CREATE TABLE var_as_modelo ("
      "asientomodelo         varchar(255),"
      "variable              varchar(255),"
      "tipo                  varchar(255),"
      "descripcion           varchar(255),"
      "orden                 int ) ;");
  else
      ejecutarSQL("CREATE TABLE var_as_modelo ("
      "asientomodelo         varchar,"
      "variable              varchar,"
      "tipo                  varchar,"
      "descripcion           varchar,"
      "orden                 int ) ;");
      
ejecutarSQL("CREATE TABLE vencimientos ("
      "num                     bigint,"
      "cta_ordenante           varchar(40),"
      "fecha_operacion         date,"
      "importe                 numeric(14,2),"
      "cuenta_tesoreria        varchar(40),"
      "fecha_vencimiento       date,"
      "derecho                 bool,"
      "pendiente               bool,"
      "anulado                 bool,"
      "pase_diario_operacion   bigint,"
      "pase_diario_vencimiento bigint,"
      "concepto                varchar(160),"
      "usuario                 varchar(80) );");
*/
ejecutarSQL("CREATE TABLE diarios ("
      "codigo       varchar(40),"
      "descripcion  varchar(255),"
      "PRIMARY KEY (codigo) );");

/*ejecutarSQL("CREATE TABLE presupuesto ("
      "ejercicio         varchar(40),"
      "cuenta            varchar(40),"
      "ejerciciobase     varchar(40) default '',"
      "presupuestobase   varchar(40) default '',"
      "base              numeric(14,2) default 0,"
      "base1             numeric(14,2) default 0,"
      "base2             numeric(14,2) default 0,"
      "base3             numeric(14,2) default 0,"
      "base4             numeric(14,2) default 0,"
      "base5             numeric(14,2) default 0,"
      "base6             numeric(14,2) default 0,"
      "base7             numeric(14,2) default 0,"
      "base8             numeric(14,2) default 0,"
      "base9             numeric(14,2) default 0,"
      "base10            numeric(14,2) default 0,"
      "base11            numeric(14,2) default 0,"
      "base12            numeric(14,2) default 0,"
      "base13            numeric(14,2) default 0,"
      "base14            numeric(14,2) default 0,"
      "base15            numeric(14,2) default 0,"
      "presupuesto       numeric(14,2) default 0,"
      "presupuesto1      numeric(14,2) default 0,"
      "presupuesto2      numeric(14,2) default 0,"
      "presupuesto3      numeric(14,2) default 0,"
      "presupuesto4      numeric(14,2) default 0,"
      "presupuesto5      numeric(14,2) default 0,"
      "presupuesto6      numeric(14,2) default 0,"
      "presupuesto7      numeric(14,2) default 0,"
      "presupuesto8      numeric(14,2) default 0,"
      "presupuesto9      numeric(14,2) default 0,"
      "presupuesto10      numeric(14,2) default 0,"
      "presupuesto11      numeric(14,2) default 0,"
      "presupuesto12      numeric(14,2) default 0,"
      "presupuesto13      numeric(14,2) default 0,"
      "presupuesto14      numeric(14,2) default 0,"
      "presupuesto15      numeric(14,2)  default 0);");*/

ejecutarSQL("CREATE TABLE periodos ("
      "ejercicio        varchar(40),"
      "codigo           varchar(40),"
      "inicio           date,"
      "fin              date,"
      "PRIMARY KEY (ejercicio,codigo) );");

ejecutarSQL("insert into configuracion (empresa,nif,domicilio,poblacion,cpostal,provincia,"
	     "email,web,anchocuentas,Cuenta_IVA_Soportado,Cuenta_IVA_Repercutido,"
	     "cuentasapagar,cuentasacobrar,Clave_IVA_defecto,Clave_gastos,Clave_ingresos,id_registral,"
	     "prox_asiento,prox_pase,prox_vencimiento,bloqsaldosmedios,cuenta_pyg,igic,analitica)"
	      "values (''     ,'' ,''       ,''       ,''     ,''       ,''   ,'' ,0 ,'',"
              "     ''   ,''           ,''            ,''    ,'' ,'' ,'',"
	      "   1          ,1        ,1                ,FALSE,'',FALSE,TRUE);");

QString cadena="update configuracion set anchocuentas=";
cadena+=ui.digitosspinBox->text();
ejecutarSQL(cadena);
ejecutarSQL("update configuracion set clave_iva_defecto='GN'");
ejecutarSQL("update configuracion set version='0.7'");
ejecutarSQL("insert into tiposiva (clave,tipo,re,descripcion) values ('GN',16,0,'TIPO GENERAL');");
ejecutarSQL("insert into tiposiva (clave,tipo,re,descripcion) values ('GN2',16,4,'TIPO GENERAL CON RECARGO DE EQUIVALENCIA');");
ejecutarSQL("insert into tiposiva (clave,tipo,re,descripcion) values ('RD',7,0,'TIPO REDUCIDO');");
ejecutarSQL("insert into tiposiva (clave,tipo,re,descripcion) values ('RD2',7,1,'TIPO REDUCIDO CON RECARGO DE EQUIVALENCIA');");
ejecutarSQL("insert into tiposiva (clave,tipo,re,descripcion) values ('SRD',4,0,'TIPO SUPERREDUCIDO');");
ejecutarSQL("insert into tiposiva (clave,tipo,re,descripcion) values ('SRD2',4,0.5,'TIPO SUPERREDUCIDO CON RECARGO DE EQUIVALENCIA');");

ejecutarSQL("update configuracion set clave_gastos='6,600',clave_ingresos='7'");

//ejecutarSQL("create index cuenta on diario (cuenta);");//error duplicated column


}


void creaempresa::importaplan()
{

/*  if (ui.plancomboBox->currentText()==planvacio()) return;
  QString cadfich=trayconfig();
  cadfich.append(QDir::separator());
  
  cadfich+=ui.plancomboBox->currentText();
  if (eswindows()) cadfich=QFile::encodeName(cadfich);
  // ----------------------------------------------------------------------------------------------------
  QSqlDatabase bd;
  bd=QSqlDatabase::database ();
  QString acontrolador= bd.driverName();
QString cadena;

  if (acontrolador=="QPSQL7" || acontrolador=="QPSQL")
     {
      cadena="copy plancontable from '";
      cadena+=cadfich;
      cadena+="'";
     }
  
  if (acontrolador=="QMYSQL3" || acontrolador=="QMYSQL") 
    {
      cargaplanmysql();
      // cadena="LOAD DATA LOCAL INFILE """;
      // cadena+=cadfich;
      // cadena+=""" INTO TABLE plancontable";
    } */
  cargaplan();
  // QMessageBox::warning( this, tr("Nueva empresa"),cadena);
  // QSqlQuery query(cadena);  
  QString cadena="insert into saldossubcuenta (codigo,saldo,saldomedio1,saldomedio2)"
	   " select codigo,0,0,0 from plancontable where char_length(codigo)=";
  QString cadnum;
  cadnum.setNum(anchocuentas());
  cadena+=cadnum;
  QSqlQuery query(cadena);  

}

void creaempresa::cargaplan()
{
  QString cadfich=trayconfig();
  cadfich.append(QDir::separator());
  
  cadfich+=ui.plancomboBox->currentText();
   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(cadfich);
       else pasa=cadfich;
  QFile fichero(pasa);
  if (!fichero.exists()) return;
  QSqlQuery query;
   if ( fichero.open( QIODevice::ReadOnly ) ) 
     {
        QTextStream stream( &fichero );
        stream.setCodec("UTF-8");
        QString linea;
         while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            QString codigo,descripcion;
            codigo=linea.section('\t',0,0);
            descripcion=linea.section('\t',1,1);
            QString cad1="insert into plancontable (codigo,descripcion) values ('";
            cad1+=codigo;
            cad1+="','";
            cad1+=descripcion;
            cad1+="');";
            ejecutarSQL(cad1);	    
           }
         fichero.close();
      }

}

void creaempresa::actufichconex(QString archconex)
{
 QStringList listaconex;

   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(archconex);
       else pasa=archconex;
 QFile fichero(pasa);
  if (!fichero.exists()) return;
    else
     {
      if ( fichero.open( QIODevice::ReadOnly ) ) 
          {
           QTextStream stream( &fichero );
           stream.setCodec("UTF-8");
           QString linea;
           while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            listaconex << linea;
           }
          } else return;
     }


 for (int veces=0;veces<listaconex.size();veces++)
     {
      if (listaconex[veces].section('\t',0,0)==ui.bdlineEdit->text())
          {
           listaconex.removeAt(veces);
           break;
          }
     }
 QString linea;
 linea=ui.bdlineEdit->text();
 linea+="\t";
 linea+=ui.controladorcomboBox->currentText();
 linea+="\t";
 linea+=ui.usuariolineEdit->text();
 //linea+="\t";
 //linea+=encriptarTexto(ui.clavelineEdit->text());
 linea+="\t";
 linea+=ui.hostlineEdit->text();
 if (ui.puertolineEdit->text().length()>0)
    {
     linea+="\t";
     linea+=ui.puertolineEdit->text();
    }


 listaconex.insert(0,linea);


  fichero.close();

  // QFile fichero(archconex);
  if (! fichero.open( QIODevice::WriteOnly ) ) return;
  QTextStream stream( &fichero );
  stream.setCodec("UTF-8");
  for (int veces=0;veces<listaconex.size();veces++)
     {
      stream << listaconex[veces] << "\n";
     }
  fichero.close();

}

