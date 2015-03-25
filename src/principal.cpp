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

#include <QtGui>
#include <QProgressDialog>
#include <QEventLoop>

#include "bss.h"
#include "principal.h"
#include "basedatos.h"
#include "funciones.h"
#include "inicial.h"
#include "conexion.h"
#include "creaempresa.h"
#include "editconfig.h"
#include "filtrodiario.h"
#include "editaplan.h"
#include "subcuentas.h"
#include "conceptos.h"
#include "ejercicios.h"
#include "infobd.h"
#include "acercade.h"
#include "licencia.h"
#include "inicio.h"
#include "periodos.h"
#include "copiaseg.h"
#include "buscasubcuenta.h"
#include "buscaconcepto.h"
#include "tabla_asientos.h"
#include "introfecha.h"
#include "imprimediario.h"
#include "cargaespera.h"
#include "pidenombre.h"
#include "listavenci.h"
#include "pideejercicio.h"
#include "tiposiva.h"
#include "edit_conc_doc.h"
#include "libros.h"
#include "libroiva.h"
//#include "grafico.h"
#include "consmayor.h"
#include "editapaseconci.h"
#include "lacaixa.h"
#include "pastel.h"
#include "acumuladosmes.h"
#include "cuadimprimayor.h"
#include "consplan.h"
#include "cierres.h"
#include "equivalencias.h"
#include "importasemanas.h"
#include "diarios.h"
#include "asignadiario.h"
#include "editarasiento.h"

#define VERSION "0.7"
#define APPNAME "Libro KUENTAS"

Mrconta::Mrconta(){
    ui.setupUi(this);
     punterodiario=NULL;
     QString directorio;
     QString nombredir;
     directorio=dirtrabajodefecto();
     // QDir d(directorio);
     // if (!d.exists()) d.mkdir(directorio);
     dirtrabajo=directorio;

     dirconfig=trayconfig();

     nombredir="/libroK.cfg";
     //nombredir += APPDIRNAME;
     //nombredir += ".cfg";
     nombredir[0]=QDir::separator();
     fichconfig=dirconfig+nombredir;

     nombredir="/conexiones.cfg";
     nombredir[0]=QDir::separator();
     fichconexiones=dirconfig+nombredir;

     visordvi=visordvidefecto();
     aplicacionimprimir=programa_imprimir_defecto();
     navegador="konqueror";
     if (eswindows()) 
       {
        navegador=windirprogram();
        navegador+="\\Internet Explorer\\iexplore";
       }
       
     filtrarpor=NADA;
     ordendiario=FECHA;
     estilonumerico=COMADECIMAL;
     sindecimales=false;
     // numeracion=NUMERACIONORIGINAL;
     filtropersonalizado="";
     filtrartex=false;
     idioma=0;
     // if (eswindows()) filtrartex=true;
     anchocol[0]=130;
     anchocol[1]=120;
     anchocol[2]=120;
     anchocol[3]=300;
     anchocol[4]=130;
     anchocol[5]=130;
     anchocol[6]=130;
     anchocol[7]=130;
     anchocol[8]=130;
     anchocol[9]=130;
     anchocol[10]=130;


     connect(ui.actionSalir, SIGNAL(triggered()), this, SLOT(salir()));
     connect(ui.actionPreferencias, SIGNAL(triggered()), this, SLOT(qpreferencias()));
     connect(ui.actionConexi_n, SIGNAL(triggered()), this, SLOT (conexionc()));
     connect(ui.actionNuevaempresa, SIGNAL(triggered()), this, SLOT (nuevaempresa()));
     connect(ui.actionFiltrar_diario, SIGNAL(triggered()), this, SLOT (filtrardiario()));
     connect(ui.actionCopiar, SIGNAL(triggered()), this, SLOT (copiar()));
     ui.actionCopiar->setEnabled(true);
     connect(ui.actionConfiguraci_n, SIGNAL(triggered()), this, SLOT (configuracion()));
     //connect(ui.actionPegar, SIGNAL(triggered()), this, SLOT (pegar()));
     ui.actionPegar->setEnabled(FALSE);
     connect(ui.actionRefrescar, SIGNAL(triggered()), this, SLOT (refrescardiario()));
     //connect(ui.actionCortar, SIGNAL(triggered()), this, SLOT (cortar()));
     ui.actionCortar->setEnabled(FALSE);
     connect(ui.actionImportar_asientos, SIGNAL(triggered()), this, SLOT (importasientos()));
     connect(ui.actionCuentas, SIGNAL(triggered()), this, SLOT (edplan()));
     connect(ui.actionSubcuentas, SIGNAL(triggered()), this, SLOT (edsubcuentas()));
     connect(ui.actionBusca_subcuenta, SIGNAL(triggered()), this, SLOT (buscasubcuentas()));
     connect(ui.actionNuevo_asiento, SIGNAL(triggered()), this, SLOT (nuevoasiento()));
     connect(ui.actionConceptos, SIGNAL(triggered()), this, SLOT (edicionconceptos()));
     connect(ui.actionBusca_concepto, SIGNAL(triggered()), this, SLOT (buscarconcepto()));
     //connect(ui.actionNuevo_registro_de_IVA_soportado, SIGNAL(triggered()), this,
     //          SLOT (apunteivasoportado()));
     ui.actionNuevo_registro_de_IVA_soportado->setEnabled(FALSE);
     //connect(ui.actionNuevo_registro_de_IVA_repercutido, SIGNAL(triggered()), this,
     //          SLOT (apunteivarepercutido()));
     //connect(ui.actionAdquisici_n_intracomunitaria_de_bienes, SIGNAL(triggered()), this,
     //          SLOT (apunteaib()));
     //connect(ui.actionEntrega_intracomunitaria_de_bienes, SIGNAL(triggered()), this,
     //          SLOT (apunteeib()));
     //connect(ui.actionC_digos_imputaci_n_primer_nivel, SIGNAL(triggered()), this,
     //          SLOT (ci1()));
     //connect(ui.actionC_digos_imputaci_n_segundo_nivel, SIGNAL(triggered()), this,
     //          SLOT (ci2()));
     //connect(ui.actionC_digos_imputaci_n_tercer_nivel, SIGNAL(triggered()), this,
     //          SLOT (ci3()));
     connect(ui.actionConsultas_de_mayor, SIGNAL(triggered()), this,
               SLOT (consultamayor()));
     ui.actionConsultas_de_mayor->setEnabled(TRUE);
     connect(ui.actionEditar_asiento, SIGNAL(triggered()), this,
               SLOT (editaasiento()));
     ui.actionEditar_asiento->setEnabled(TRUE);
     connect(ui.actionImprime_mayor, SIGNAL(triggered()), this,
               SLOT (imprimemayor()));
     ui.actionImprime_mayor->setEnabled(TRUE);
     connect(ui.actionBalance_de_sumas_y_saldos, SIGNAL(triggered()), this,
               SLOT (genbss()));
     ui.actionBalance_de_sumas_y_saldos->setEnabled(TRUE);
     //connect(ui.actionConsulta_imputaciones, SIGNAL(triggered()), this,
     //          SLOT (cinput()));
     //connect(ui.actionNuevo_estado_contable, SIGNAL(triggered()), this,
     //          SLOT (nuevogenestado()));
     //connect(ui.actionEditar_estado_contable, SIGNAL(triggered()), this,
     //          SLOT (edgenestado()));
     //connect(ui.actionCalcular_estado, SIGNAL(triggered()), this,
     //          SLOT (calculaestado()));
     //connect(ui.actionNuevo_asiento_autom, SIGNAL(triggered()), this,
     //          SLOT (nuevoasautomatico()));
     //connect(ui.actionEdicion_asiento_autom, SIGNAL(triggered()), this,
     //          SLOT (editaasmodelo()));
     //connect(ui.actionPlan_de_amortizaciones, SIGNAL(triggered()), this,
     //          SLOT (plamort()));
     //connect(ui.actionAsiento_de_amortizaciones, SIGNAL(triggered()), this,
     //          SLOT (asamort()));
     //connect(ui.actionDiferencias_base_imponible, SIGNAL(triggered()), this,
     //          SLOT (difbi()));
     //connect(ui.actionHcodif, SIGNAL(triggered()), this,
     //          SLOT (hamort()));

     //connect(ui.actionInmovilizado_neto, SIGNAL(triggered()), this,
     //          SLOT (ineto()));

     connect(ui.actionEjercicios_contables, SIGNAL(triggered()), this,
               SLOT (ejs()));

     connect(ui.actionVencimientos_a_partir_diario, SIGNAL(triggered()), this,
               SLOT (vtosCuenta()));
               
     connect(ui.actionProcesar_vencimientos, SIGNAL(triggered()), this,
               SLOT (procvencimientos()));
	ui.actionVencimientos_a_partir_diario->setEnabled(TRUE);
     connect(ui.actionExportar_plan, SIGNAL(triggered()), this,
               SLOT (exportplan()));

     connect(ui.actionExportar_plan_con_subcuentas, SIGNAL(triggered()), this,
               SLOT (exportplansubcuentas()));

     connect(ui.actionEditar_asiento_num, SIGNAL(triggered()), this,
               SLOT (editaNumAsiento()));

     connect(ui.actionBorra_asiento, SIGNAL(triggered()), this,
               SLOT (borraasiento()));
	ui.actionBorra_asiento->setEnabled(TRUE);
     connect(ui.actionImprimir_diario, SIGNAL(triggered()), this,
               SLOT (ImprimeDiario()));
	ui.actionImprimir_diario->setEnabled(TRUE);
     //connect(ui.actionDiario_resumen, SIGNAL(triggered()), this,
     //          SLOT (dresumen()));

     connect(ui.actionCargar_asiento_en_espera, SIGNAL(triggered()), this,
               SLOT (asientosEspera()));
	ui.actionCargar_asiento_en_espera->setEnabled(TRUE);
     connect(ui.actionNuevo_asiento_autom, SIGNAL(triggered()), this,
               SLOT (nuevoAsientoAuto()));
     //connect(ui.actionEjecutar_asiento_autom, SIGNAL(triggered()), this,
     //          SLOT (execasmodelo()));

     //connect(ui.actionEjecutar_ult_autom, SIGNAL(triggered()), this,
     //          SLOT (ulmodeloexec()));

     //connect(ui.actionBorrar_asiento_autom, SIGNAL(triggered()), this,
     //          SLOT (borramodelo()));

     //connect(ui.actionRegularizacion, SIGNAL(triggered()), this,
     //          SLOT (regulariza()));

     //connect(ui.actionCierre_de_ejercicio, SIGNAL(triggered()), this,
     //          SLOT (cierra()));

     connect(ui.actionDeshacer_cierre, SIGNAL(triggered()), this,
               SLOT (suprimircierre()));

     //connect(ui.actionAsiento_de_apertura, SIGNAL(triggered()), this,
     //          SLOT (apert()));

     connect(ui.actionAcumulados_mes, SIGNAL(triggered()), this,
               SLOT (acummes()));
	ui.actionAcumulados_mes->setEnabled(true);
     connect(ui.actionConsulta_plan, SIGNAL(triggered()), this,
               SLOT (consultaplan()));
	ui.actionConsulta_plan->setEnabled(true);
     connect(ui.actionOperaciones, SIGNAL(triggered()), this,
               SLOT (grafOper()));

     //connect(ui.actionAsignar_vencimientos_cuentas_a_cobrar, SIGNAL(triggered()), this,
     //          SLOT (vtosacobrar()));

     connect(ui.actionVencimientosSemana, SIGNAL(triggered()), this,
               SLOT (vtosSemana()));

     //connect(ui.actionVencimientos_anulados, SIGNAL(triggered()), this,
     //          SLOT (vanul()));

     connect(ui.actionTipos_de_IVA, SIGNAL(triggered()), this,
               SLOT (qtiposiva()));
	ui.actionTipos_de_IVA->setEnabled(TRUE);
     connect(ui.actionLibro_de_Facturas_Recibidas, SIGNAL(triggered()), this,
               SLOT (libroFactRec()));
	ui.actionLibro_de_Facturas_Recibidas->setEnabled(TRUE);
     //connect(ui.actionLibro_de_Facturas_Emitidas, SIGNAL(triggered()), this,
     //          SLOT (librofactemitidas()));

     //connect(ui.actionLibro_IVA_soportado_por_AIB, SIGNAL(triggered()), this,
     //          SLOT (librofactrecibidasaib()));

     //connect(ui.actionLibro_IVA_repercutido_por_AIB, SIGNAL(triggered()), this,
     //          SLOT (librofactemitidasaib()));

     //connect(ui.actionLibro_de_entregas_intracomunitarias, SIGNAL(triggered()), this,
     //          SLOT (librofactemitidaseib()));

     //connect(ui.actionLiquidaci_n_de_IVA, SIGNAL(triggered()), this,
     //          SLOT (liqiva()));

     //connect(ui.actionRelopiva, SIGNAL(triggered()), this,
     //          SLOT (relopiva()));

     //connect(ui.actionBorrar_estado_contable, SIGNAL(triggered()), this,
     //          SLOT (borrarestado()));

     //connect(ui.actionLibera_calculo, SIGNAL(triggered()), this,
     //          SLOT (liberacalcmedios()));

     //connect(ui.actionExportar_estado_contable, SIGNAL(triggered()), this,
     //          SLOT (exportestado()));

     //connect(ui.actionImportar_estado_contable, SIGNAL(triggered()), this,
     //          SLOT (importestado()));

     //connect(ui.actionRenumerar_asientos, SIGNAL(triggered()), this,
     //          SLOT (renumera()));

     //connect(ui.actionIntercambiar_numeros, SIGNAL(triggered()), this,
     //          SLOT (intercambiaas()));

     connect(ui.actionAsignar_diario, SIGNAL(triggered()), this,
               SLOT (asignardiario()));

     connect(ui.actionMarcar_como_cerrado_ejercicio, SIGNAL(triggered()), this,
               SLOT (marcarcerrado()));
	
     connect(ui.actionAgrupar_TEX, SIGNAL(triggered()), this,
               SLOT (librosagr()));

     connect(ui.actionConsulta_TEX, SIGNAL(triggered()), this,
               SLOT (consultatex()));

     connect(ui.actionGenerar_PDF, SIGNAL(triggered()), this,
               SLOT (generarpdf()));

     //connect(ui.actionBorrar_intervalo, SIGNAL(triggered()), this,
     //          SLOT (borraint()));

     //connect(ui.actionIntercambiar_cuenta, SIGNAL(triggered()), this,
     //          SLOT (cambiacuen()));

     //connect(ui.actionCambiar_cuenta, SIGNAL(triggered()), this,
     //          SLOT (cambiacuenpase()));

     connect(ui.actionEdita_pase, SIGNAL(triggered()), this,
               SLOT (edPase()));
    ui.actionEdita_pase->setEnabled(TRUE);
     connect(ui.actionEditar_concepto_y_documento, SIGNAL(triggered()), this,
               SLOT (edcondoc()));
	ui.actionEditar_concepto_y_documento->setEnabled(TRUE);
     connect(ui.actionCopia_seguridad, SIGNAL(triggered()), this,
               SLOT (seguridad()));

     connect(ui.actionRectificar_saldos, SIGNAL(triggered()), this,
               SLOT (actuSaldos()));
	ui.actionRectificar_saldos->setEnabled(TRUE);
     connect(ui.actionContenido, SIGNAL(triggered()), this,
               SLOT (ayuda()));

     connect(ui.actionInformacion_conexion, SIGNAL(triggered()), this,
               SLOT (infoconex()));

     connect(ui.actionAcerca_de, SIGNAL(triggered()), this,
               SLOT (cuadacercade()));

     connect(ui.actionAcuerdo_de_licencia, SIGNAL(triggered()), this,
               SLOT (acuerdolicencia()));
     connect(ui.actionAcuerdo_de_licencia_esp, SIGNAL(triggered()), this,
               SLOT (acuerdolicenciaesp()));

     //connect(ui.actionCargar_plan_nuevo, SIGNAL(triggered()), this,
     //          SLOT (carganuevoplan()));

     //connect(ui.actionBorrar_plan_nuevo, SIGNAL(triggered()), this,
     //          SLOT (borranuevoplan()));

     //connect(ui.actionEditar_plan_nuevo, SIGNAL(triggered()), this,
     //          SLOT (ednuevoplan()));

     connect(ui.actionEditar_equivalencias, SIGNAL(triggered()), this,
               SLOT (editarEquivalencias()));

     //connect(ui.actionMover_subcuentas_en_plan_nuevo, SIGNAL(triggered()), this,
     //          SLOT (susticuenta()));

     connect(ui.actionOrden_numero, SIGNAL(toggled(bool)), this,
               SLOT (qordendiario(bool)));
     connect(ui.actionNumero_cuenta, SIGNAL(toggled(bool)), this,
               SLOT (qordendiario(bool)));
     

     //connect(ui.actionExportar_asiento, SIGNAL(triggered()), this,
     //          SLOT (exportaasmodelo()));

     connect(ui.actionImportar_asiento, SIGNAL(triggered()), this,
               SLOT (importaLaCaixa()));
     ui.actionImportar_asiento->setEnabled(TRUE);

     connect(ui.actionTipos_diario, SIGNAL(triggered()), this,
               SLOT (tiposdiario()));

     //connect(ui.actionEditar_presupuesto, SIGNAL(triggered()), this,
     //          SLOT (presupuestos()));

     //connect(ui.actionEditar_pres_cuentas, SIGNAL(triggered()), this,
     //          SLOT (presupuestoscta()));

     //connect(ui.actionPrevisiones_realizaciones_subcuentas, SIGNAL(triggered()), this,
     //          SLOT (desv()));

     //connect(ui.actionPrevisiones_realizaciones_cuentas, SIGNAL(triggered()), this,
     //          SLOT (desvctas()));

     connect(ui.actionImportar_plan, SIGNAL(triggered()), this,
               SLOT (actualizaplan()));

}



bool Mrconta::oknosalir()
{
     bool bdabierta=false;
     bool hayfich=FALSE;
     // QString fichsplash = a.applicationDirPath ();
     QString fichsplash=fsplash();
     QSplashScreen *splash=NULL;
     if (QFile::exists(adapta(fichsplash)))
      {
       QPixmap pixmap( adapta(fichsplash) );
       splash = new QSplashScreen( pixmap );
       splash->show();
       hayfich=TRUE;
     }

     if (!cargapreferencias(&bdabierta) || !bdabierta )
      {
         if (hayfich)
          {
           splash->finish( this );
           delete splash;
           hayfich=FALSE;
          }
         // procesamos menú abrir bd, crear nueva, o salir
         inicio *i = new inicio;
         i->exec();
         i->~inicio();
         inicial *pinicial = new inicial;
         pinicial->exec();
         if (pinicial->salir())
           {
            pinicial->~inicial();
            return (false);
           }

       while (true)
        {
         if (pinicial->salir())
           {
            pinicial->~inicial();
            return false;
           }
         if (pinicial->abrir())
           {
            if (conexion0()) break;
           }
         if (pinicial->crear())
           {
            creaempresa *c = new creaempresa;
            int resultado = c->exec();
            if (resultado == QDialog::Accepted)
                {
                  if (c->creabd())
                     {
                      c->actufichconex(fichconexiones);
                      c->~creaempresa();
                      break;
                     }
                }
            c->~creaempresa();
           }
         pinicial->exec();
        }
       pinicial->~inicial();
      }
     QString title=APPNAME;
     title+=" - ";
     setWindowTitle(title+nombreempresa());
     calculaprimerosasientos();
     diario *eldiario = new diario;
     punterodiario=eldiario;
     setCentralWidget(eldiario);
     QString cadena;
     filtroactivo=condicionesfiltrodefecto();
     eldiario->pasafiltroedlin(filtro_a_lingu(filtroactivo));
     if (filtroactivo.length()>0) cadena=" WHERE "+filtroactivo+" ";
     //  falta pasar cadena a lineEdit del filtro
     cadena+=ordenarpor();
     eldiario->activaconfiltro(cadena,estilonumerico,sindecimales);
     eldiario->pasaanchos(anchocol);
     eldiario->muestratabla();
     if (hayfich)
        {
         splash->finish( this );
         delete splash;
      }
     return true;
}


void Mrconta::salir()
  {
      grabapreferencias();
      close();
  }

void Mrconta::qpreferencias()
  {
      int resultado;
      preferencias *prefer;
      preferencias *laprefer = new preferencias;
      prefer=laprefer;
      // pasamos variables al diálogo
      prefer->pasadirtrabajo(dirtrabajo);
      prefer->pasavisordvi(visordvi);
      prefer->pasaaplicimprimir(aplicacionimprimir);
      prefer->pasanavegador(navegador);
      prefer->pasafiltropor(filtrarpor);
      prefer->pasaordenarpor(ordendiario);
      prefer->pasaestilonumerico(estilonumerico);
      prefer->pasasindecimales(sindecimales);
      // prefer->pasanumeracion(numeracion);
      prefer->pasafiltrodiariopersonalizado(filtropersonalizado);
      prefer->pasafiltrartex(filtrartex);
      prefer->pasaidioma(idioma);

      resultado=prefer->exec();
      if (resultado==QDialog::Accepted)
         {
	     // pasar contenido a variables
             dirtrabajo=prefer->dirtrabajo();
             visordvi=prefer->visordvi();
             aplicacionimprimir=prefer->aplicimprimir();
             navegador=prefer->navegador();
             filtrarpor=prefer->filtropor();
             ordendiario=prefer->ordenarpor();
             ui.actionOrden_numero->disconnect(SIGNAL(toggled(bool)));
             if (ordendiario!=FECHA) ui.actionOrden_numero->setChecked(true);
                else ui.actionOrden_numero->setChecked(false);
             connect(ui.actionOrden_numero, SIGNAL(toggled(bool)), this,
                   SLOT (qordendiario(bool)));
             estilonumerico=prefer->estilonumerico();
             sindecimales=prefer->sindecimales();
             // numeracion=prefer->numeracion();
             filtropersonalizado=prefer->filtrodiariopersonalizado();
             filtrartex=prefer->esfiltrartex();
             idioma=prefer->qidioma();
         }
      prefer->~preferencias();
      grabapreferencias();

     QString cadena;
     filtroactivo=condicionesfiltrodefecto();
     punterodiario->pasafiltroedlin(filtroactivo);
     if (filtroactivo.length()>0) cadena=" WHERE "+filtroactivo+" ";
     //  falta pasar cadena a lineEdit del filtro
     cadena+=ordenarpor();
     punterodiario->pasafiltro(cadena,estilonumerico,sindecimales);
     // punterodiario->pasaanchos(anchocol);
     punterodiario->muestratabla();

  }

bool Mrconta::abrebasedatos(QString vpghost,QString vpgdbname,QString vpguser,
                            QString vpgpassword,QString vcontrolador,QString vpuerto)
{

   QSqlDatabase defaultDB = QSqlDatabase::addDatabase( vcontrolador );
   if ( defaultDB.isDriverAvailable (vcontrolador) ) {
                                if (!vpgdbname.isEmpty()) defaultDB.setDatabaseName( vpgdbname );
                                if (!vpguser.isEmpty()) defaultDB.setUserName( vpguser );
                                if (!vpgpassword.isEmpty()) defaultDB.setPassword( vpgpassword );
                                if (!vpghost.isEmpty()) defaultDB.setHostName( vpghost );
                                if (!vpuerto.isEmpty()) defaultDB.setPort(vpuerto.toInt());
                               if ( !defaultDB.open() ) return false;
                               // La base de datos se ha abierto, ya podemos executar comandos
       
                      }
                       else
                                {
                                  QMessageBox::warning( this, tr("Apertura de base de datos"),
                                  tr("IMPOSIBLE CARGAR BASE DE DATOS CON")+" "+vcontrolador);
		                  return false;
                                }
 
// comprobamos versión correcta
  if (versionbd()!=VERSION)
      {
        if (versionbd()!="0.7")
        {
           	QMessageBox::warning( this, tr("Apertura de base de datos"),
                     tr("ERROR: versión de tablas incorrecta"));
        defaultDB.close();
        return false;
        }
        else
           {
               if (QMessageBox::question(
               this,
               tr("ACTUALIZAR TABLAS"),
               tr("Las tablas pertenecen a la versión '%1' ¿ Desea actualizarlas ?").arg(versionbd() ),
               tr("&Sí"), tr("&No"),
               QString::null, 0, 1 ) ==0 )
                 {
                  if (versionbd()=="0.7") actualizade07();
                 }
                 else
                     {
                      defaultDB.close();
                      return false;
                     }
           }
      }
 return true;
}


bool Mrconta::cargapreferencias(bool *bdabierta)
{
  QString nombrefichcompleto=fichconfig;
  QString vpghost,vpgdbname,vpguser,vpgpassword,vcontrolador,vpuerto;
  QFile fichero(adapta(nombrefichcompleto));
  if (!fichero.exists()) 
     {
      *bdabierta=FALSE;
      return false;
     }

   if ( fichero.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &fichero );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable==QString("FILTRO")) contenido=linea.remove(QString("FILTRO="));
               if (variable.compare("PGHOST")==0) vpghost=contenido;
               if (variable.compare("DBNAME")==0) vpgdbname=contenido;
               if (variable.compare("PGUSER")==0) vpguser=contenido;
               //if (variable.compare("PASSWORD")==0) vpgpassword=desencriptarTexto(contenido);
               if (variable.compare("CONTROLADOR")==0) vcontrolador=contenido;
               if (variable.compare("PORT")==0) vpuerto=contenido;
	       
               if (variable.compare("COL0")==0) if (contenido.toInt()>10) anchocol[0]=contenido.toInt();
               if (variable.compare("COL1")==0) if (contenido.toInt()>10) anchocol[1]=contenido.toInt();
               if (variable.compare("COL2")==0) if (contenido.toInt()>10) anchocol[2]=contenido.toInt();
               if (variable.compare("COL3")==0) if (contenido.toInt()>10) anchocol[3]=contenido.toInt();
               if (variable.compare("COL4")==0) if (contenido.toInt()>10) anchocol[4]=contenido.toInt();
               if (variable.compare("COL5")==0) if (contenido.toInt()>10) anchocol[5]=contenido.toInt();
               if (variable.compare("COL6")==0) if (contenido.toInt()>10) anchocol[6]=contenido.toInt(); 
               if (variable.compare("COL7")==0) if (contenido.toInt()>10) anchocol[7]=contenido.toInt();
               if (variable.compare("COL8")==0) if (contenido.toInt()>10) anchocol[8]=contenido.toInt();
               if (variable.compare("COL9")==0) if (contenido.toInt()>10) anchocol[9]=contenido.toInt();
               if (variable.compare("COL10")==0) if (contenido.toInt()>10) anchocol[10]=contenido.toInt();
               // ---------------------------------------------------------------------------------------
               if (variable.compare("DIRECTORIO")==0) dirtrabajo=contenido;
               if (variable.compare("VISORDVI")==0) visordvi=contenido;
               if (variable.compare("IMPRIMIR")==0) aplicacionimprimir=contenido;
               if (variable.compare("NAVEGADOR")==0) navegador=contenido;
               if (variable.compare("FILTROPOR")==0) filtrarpor=contenido.toInt();
               if (variable.compare("ORDENARPOR")==0)
                  {
                   ordendiario=contenido.toInt();
                   ui.actionOrden_numero->disconnect(SIGNAL(toggled(bool)));
                   ui.actionNumero_cuenta->disconnect(SIGNAL(toggled(bool)));
                   if (ordendiario==ASIENTO || ordendiario==ASIENTO+CUENTA)
                   	 ui.actionOrden_numero->setChecked(true);
                   else ui.actionOrden_numero->setChecked(false);
                   if (ordendiario==CUENTA || ordendiario==ASIENTO+CUENTA)
                   	 ui.actionNumero_cuenta->setChecked(true);
                   else ui.actionNumero_cuenta->setChecked(false);
                   connect(ui.actionOrden_numero, SIGNAL(toggled(bool)), this,
                     SLOT (qordendiario(bool)));
                   connect(ui.actionNumero_cuenta, SIGNAL(toggled(bool)), this,
                     SLOT (qordendiario(bool)));
                   
                  }
               if (variable.compare("SINDECIMALES")==0) sindecimales=contenido.toInt();
               if (variable.compare("FILTRO")==0) filtropersonalizado=contenido;
               if (variable.compare("ESTILONUMERICO")==0) estilonumerico=contenido.toInt();
               if (variable.compare("FILTRARTEX")==0) filtrartex=contenido.toInt();
               if (variable.compare("IDIOMA")==0) idioma=contenido.toInt();
              }
            }
        fichero.close();
        }
   if (vpgdbname=="template1") 
      {
       *bdabierta=false;
       return true;
      }
   pidenombre *p = new pidenombre();
   p->asignanombreventana(tr("Conexión")+" "+tr("con")+" "+vpghost);
   p->asignaetiqueta(tr("BASE DE DATOS:")+" "+vpgdbname+"\n"+tr("USUARIO:")+" "+vpguser+"\n"+tr("CLAVE:"));
   p->password();
   int resultado = p->exec();
   vpgpassword = p->contenido();
   if (!resultado==QDialog::Accepted){
   		*bdabierta=false;
   		delete(p);
   		return false;
   }
   if (abrebasedatos(vpghost,vpgdbname,vpguser,
                      vpgpassword,vcontrolador,vpuerto))
       *bdabierta=true;
      else{
      		*bdabierta=false;
      		QMessageBox::critical(this, APPNAME,
                   tr("No se ha podido abrir la base de datos especificada.\n Clave incorrecta."));
     	}
 delete(p);
 return true;

}


void Mrconta::grabapreferencias()
{
  QString qfichero=fichconfig;
  QSqlDatabase bd = QSqlDatabase::database();
  QString anombredb=bd.databaseName();
  QString anombreusuario=bd.userName();
  QString aclave=bd.password();
  QString ahost=bd.hostName();
  QString cadvalor;
  QString acontrolador;
  acontrolador= bd.driverName();
  QString apuerto;
  apuerto.setNum(bd.port());

  QFile fichero(adapta(qfichero));
  if (! fichero.open( QIODevice::WriteOnly ) ) return;
  QTextStream stream( &fichero );
  stream.setCodec("UTF-8");

  stream << "DBNAME=" << anombredb << "\n";
  stream << "PGUSER=" << anombreusuario << "\n";
  //stream << "PASSWORD=" << encriptarTexto(aclave) << "\n";
  stream << "PGHOST=" << ahost << "\n";
  stream << "CONTROLADOR=" << acontrolador << "\n";
  stream << "PORT=" << apuerto << "\n";
  if (punterodiario!=NULL)
     {
    	stream << "COL0=";
  	cadvalor.setNum(punterodiario->anchocolumna(0));
  	stream << cadvalor << "\n";
  	stream << "COL1=";
  	cadvalor.setNum(punterodiario->anchocolumna(1));
  	stream << cadvalor << "\n";
  	stream << "COL2=";
  	cadvalor.setNum(punterodiario->anchocolumna(2));
  	stream << cadvalor << "\n";
  	stream << "COL3=";
  	cadvalor.setNum(punterodiario->anchocolumna(3));
  	stream << cadvalor << "\n";
	stream << "COL4=";
  	cadvalor.setNum(punterodiario->anchocolumna(4));
  	stream << cadvalor << "\n";
  	stream << "COL5=";
  	cadvalor.setNum(punterodiario->anchocolumna(5));
  	stream << cadvalor << "\n";
  	stream << "COL6=";
  	cadvalor.setNum(punterodiario->anchocolumna(6));
  	stream << cadvalor << "\n";
  	stream << "COL7=";
  	cadvalor.setNum(punterodiario->anchocolumna(7));
  	stream << cadvalor << "\n";
  	stream << "COL8=";
  	cadvalor.setNum(punterodiario->anchocolumna(8));
  	stream << cadvalor << "\n";
  	stream << "COL9=";
  	cadvalor.setNum(punterodiario->anchocolumna(9));
  	stream << cadvalor << "\n";
  	stream << "COL10=";
  	cadvalor.setNum(punterodiario->anchocolumna(10));
  	stream << cadvalor << "\n";
        stream << "DIRECTORIO=" << dirtrabajo << "\n";
        stream << "VISORDVI="  << visordvi << "\n";
        stream << "IMPRIMIR="  << aplicacionimprimir << "\n";
        stream << "NAVEGADOR=" << navegador << "\n";
        if (filtrarpor>0)
          {
           stream << "FILTROPOR=";
           cadvalor.setNum(filtrarpor);
           stream << cadvalor << "\n";
          }
        stream << "ORDENARPOR=";
        cadvalor.setNum(ordendiario);
        stream << cadvalor << "\n";
        stream << "ESTILONUMERICO=";
        cadvalor.setNum(estilonumerico);
        stream << cadvalor << "\n";
        stream << "SINDECIMALES=";
        cadvalor.setNum(sindecimales);
        stream << cadvalor << "\n";
        stream << "FILTRARTEX=";
        cadvalor.setNum(filtrartex);
        stream << cadvalor << "\n";
        stream << "IDIOMA=";
        cadvalor.setNum(idioma);
        stream << cadvalor << "\n";

        if (filtropersonalizado.length()>0) stream << "FILTRO=" << filtropersonalizado << "\n";

    }
  fichero.close();

}


QString Mrconta::condicionesfiltrodefecto(void)
{
 QString cadfiltro;
 QDate fechaactual=QDate::currentDate();
 QDate fecha;
    if (filtrarpor==1)
      {
         QString ejercicio=ejerciciodelafecha(fechaactual);
         if (ejercicio.length()>0)
            {
               cadfiltro="fecha>='";
               cadfiltro+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
               cadfiltro+="' and fecha<='";
               cadfiltro+=finejercicio(ejercicio).toString("yyyy.MM.dd");
               cadfiltro+="'";
            }
      }
   if (filtrarpor==2)
      {
        fecha=fechaactual.addDays(-30);
        cadfiltro="fecha>='";
        cadfiltro+=fecha.toString("yyyy.MM.dd");
        cadfiltro+="'";
     }
   if (filtrarpor==3)
     {
       cadfiltro="asiento>";
       cadfiltro+=ultimonumasiento("");
       cadfiltro+="-30";
     }
   if (filtropersonalizado.length()>0)
    {
        cadfiltro=filtropersonalizado;
    }

  return cadfiltro;
}

QString Mrconta::ordenarpor(void)
{
  QString cadena;
  if (ordendiario==ASIENTO) cadena=" ORDER BY asiento,fecha,pase";
  if (ordendiario==CUENTA) cadena=" ORDER BY descripcion,pase";
  if (ordendiario==FECHA) cadena=" ORDER BY fecha,pase";
  if (ordendiario==ASIENTO+CUENTA) cadena=" ORDER BY cuenta,asiento,pase";
  if (ordendiario==CUENTA+FECHA) cadena=" ORDER BY cuenta,fecha,pase";
  return cadena;
}

void Mrconta::filtrardiario()
{
 filtrodiario *f = new filtrodiario(estilonumerico);
 f->pasafiltro(filtro_a_lingu(filtroactivo));
 f->pasacondicionesfiltrodefecto(condicionesfiltrodefecto());
 int resultado = f->exec();
 if (resultado == QDialog::Accepted)
      {
       filtroactivo=lingu_a_filtro(f->filtro());
       punterodiario->~diario();
       diario *eldiario = new diario;
       punterodiario=eldiario;
       setCentralWidget(eldiario);
       eldiario->pasafiltroedlin(filtro_a_lingu(filtroactivo));
       QString cadena;
       if (filtroactivo.length()>0) cadena=" WHERE "+filtroactivo+" ";
       cadena+=ordenarpor();
       eldiario->activaconfiltro(cadena,estilonumerico,sindecimales);
       eldiario->pasaanchos(anchocol);
       eldiario->muestratabla();
      }
 f->~filtrodiario();
}

void Mrconta::conexionc()
{
  // primero nos quedamos con los parámetros de la anterior conexión
  // este es un slot para cambiar conexión no para partir desde cero

   QString anombredb;
   QString anombreusuario;
   QString aclave;
   QString ahost;
   QString acontrolador;
   QString apuerto;
  punterodiario->~diario();

  {
   QSqlDatabase bd = QSqlDatabase::database();
   anombredb=bd.databaseName();
   anombreusuario=bd.userName();
   aclave=bd.password();
   ahost=bd.hostName();
   acontrolador= bd.driverName();
   apuerto.setNum(bd.port());
   bd.close(); //linea nueva
   // bd.removeDatabase(anombredb);
  }
   QSqlDatabase::removeDatabase("qt_sql_default_connection");

  // destruimos diario antiguo
  // abría que quitarlo primero de centralwidget ??
  // setCentralWidget(NULL);
  // dialogo de conexión más conexión
  // QSqlDatabase::removeDatabase(anombredb);
  conexion *laconex = new conexion;
  laconex->pasaarchconex(fichconexiones);

  int resultado=laconex->exec();
  if (resultado==QDialog::Accepted)
    {
     if (!abrebasedatos(laconex->host(),
                     laconex->basedatos(),
                     laconex->usuario(),
                     laconex->clave(),
                     laconex->controlador(),
                     laconex->puerto()))
         {
          // Mensaje no se ha podido abrir; abrimos la antigua
          QMessageBox::warning(this, APPNAME,
                   tr("No se ha podido abrir la base de datos especificada"));
          abrebasedatos(ahost,anombredb,anombreusuario,aclave,acontrolador,apuerto);
         }
          else
                {
                 laconex->actulistaconex();
                 laconex->actufichconex();
                }
     }
      else abrebasedatos(ahost,anombredb,anombreusuario,aclave,acontrolador,apuerto);
  laconex->~conexion();
  QString title=APPNAME;
  title+=" - ";
  setWindowTitle(title+nombreempresa());
  calculaprimerosasientos();
  diario *eldiario = new diario;
  punterodiario=eldiario;
  setCentralWidget(eldiario);
  QString cadena;
  filtroactivo=condicionesfiltrodefecto();
  eldiario->pasafiltroedlin(filtro_a_lingu(filtroactivo));
  if (filtroactivo.length()>0) cadena=" WHERE "+filtroactivo+" ";
  cadena+=ordenarpor();
  eldiario->activaconfiltro(cadena,estilonumerico,sindecimales);
  eldiario->pasaanchos(anchocol);
  eldiario->muestratabla();

}



bool Mrconta::conexion0()
{

  conexion *laconex = new conexion;
  laconex->pasaarchconex(fichconexiones);

  int resultado=laconex->exec();
  if (resultado==QDialog::Rejected) return false;
  if (resultado==QDialog::Accepted)
    {
     if (!abrebasedatos(laconex->host(),
                     laconex->basedatos(),
                     laconex->usuario(),
                     laconex->clave(),
                     laconex->controlador(),
                     laconex->puerto()))
         {
          QMessageBox::warning(this, APPNAME,
                   tr("No se ha podido abrir la base de datos especificada"));
          laconex->~conexion();
          return false;
         }
          else
                {
                 laconex->actulistaconex();
                 laconex->actufichconex();
                }
     }
  laconex->~conexion();
  return true;
}

void Mrconta::nuevaempresa()
{
  // primero nos quedamos con los parámetros de la anterior conexión

   QString anombredb;
   QString anombreusuario;
   QString aclave;
   QString ahost;
   QString acontrolador;
   QString apuerto;

  punterodiario->~diario();

  {
   QSqlDatabase bd = QSqlDatabase::database();
   anombredb=bd.databaseName();
   anombreusuario=bd.userName();
   aclave=bd.password();
   ahost=bd.hostName();
   acontrolador= bd.driverName();
   apuerto.setNum(bd.port());
   bd.close(); //linea nueva
   // bd.removeDatabase(anombredb);
  }

  QSqlDatabase::removeDatabase("qt_sql_default_connection");
  creaempresa *c = new creaempresa;
  int resultado = c->exec();
  if (resultado == QDialog::Accepted)
      {
       if (c->creabd())
           {
            c->actufichconex(fichconexiones);
            // falta editar configuración
            editconfig *ed = new editconfig;
            ed->exec();
            ed->~editconfig();
           }
         else { 
                 abrebasedatos(ahost,anombredb,anombreusuario,aclave,acontrolador,apuerto);
                }
      }
      else abrebasedatos(ahost,anombredb,anombreusuario,aclave,acontrolador,apuerto);
  c->~creaempresa();
  QString title=APPNAME;
  title+=" - ";
  setWindowTitle(title+nombreempresa());
  calculaprimerosasientos();
  diario *eldiario = new diario;
  punterodiario=eldiario;
  setCentralWidget(eldiario);
  QString cadena;
  filtroactivo=condicionesfiltrodefecto();
  eldiario->pasafiltroedlin(filtro_a_lingu(filtroactivo));
  if (filtroactivo.length()>0) cadena=" WHERE "+filtroactivo+" ";
  cadena+=ordenarpor();
  //testigic();
  eldiario->activaconfiltro(cadena,estilonumerico,sindecimales);
  eldiario->pasaanchos(anchocol);
  eldiario->muestratabla();

}

void Mrconta::configuracion()
{
   editconfig *ed = new editconfig;
   ed->exec();
   ed->~editconfig();
   refrescardiario();
}


void Mrconta::refrescardiario()
{
  punterodiario->refresca();
  punterodiario->irfinal();
}



void Mrconta::ayuda()
{
  // contenido de la ayuda
   QString fichero=traynombrefichayuda();
   QString cadexec=navegador;

   QObject *parent=NULL;
   QProcess *myProcess = new QProcess(parent);
   QStringList arguments;

   arguments << adapta(fichero);

   myProcess->start(adapta(cadexec),arguments);
   if (!myProcess->waitForStarted ())
       {
        QMessageBox::warning( this, tr("AYUDA"),tr("ERROR: no se ha podido ejecutar"
                                                          " el navegador para mostrar ayuda"));
        myProcess->~QProcess();
        return;
       }
   myProcess->waitForFinished(-1);
   myProcess->~QProcess();

}


void Mrconta::infoconex()
{
   infobd *i = new infobd();
   i->exec();
   i->~infobd();
}


void Mrconta::cuadacercade()
{
   acercade *a = new acercade();
   a->exec();
   a->~acercade();
}


void Mrconta::acuerdolicencia()
{
   licencia *lic=new licencia();
   lic->exec();
   lic->~licencia();

}


void Mrconta::acuerdolicenciaesp()
{
   licencia *lic=new licencia();
   lic->lic_spanish();
   lic->exec();
   lic->~licencia();

}

void Mrconta::qordendiario(bool numero)
{
     if (!numero) ordendiario=FECHA;
     if (!ui.actionNumero_cuenta->isChecked() && ui.actionOrden_numero->isChecked())
     	ordendiario=ASIENTO;
     if (ui.actionNumero_cuenta->isChecked() && !ui.actionOrden_numero->isChecked())
     	ordendiario=CUENTA+FECHA;
     if (!ui.actionNumero_cuenta->isChecked() && !ui.actionOrden_numero->isChecked())
     	ordendiario=FECHA;
     if (ui.actionNumero_cuenta->isChecked() && ui.actionOrden_numero->isChecked())
     	ordendiario=ASIENTO+CUENTA;
     //if (!numero) ordendiario=FECHA;
     QString cadena;
     // filtroactivo=condicionesfiltrodefecto();
     punterodiario->pasafiltroedlin(filtroactivo);
     if (filtroactivo.length()>0) cadena=" WHERE "+filtroactivo+" ";
     //  falta pasar cadena a lineEdit del filtro
     cadena+=ordenarpor();
     punterodiario->pasafiltro(cadena,estilonumerico,sindecimales);
     // punterodiario->pasaanchos(anchocol);
     punterodiario->muestratabla();
}

void Mrconta::ejs()
{
  ejercicios *e = new ejercicios();
  e->exec();
  e->~ejercicios();
}

void Mrconta::edplan()
{
 editaplan *e = new editaplan();
 e->exec();
 e->~editaplan(); 
}

void Mrconta::edsubcuentas()
{
 subcuentas *s = new subcuentas();
 s->setWindowIcon(ui.actionSubcuentas->icon());
 s->exec();
 s->~subcuentas();
}

void Mrconta::edicionconceptos()
{
 conceptos *c = new conceptos();
 c->setWindowIcon(ui.actionConceptos->icon());
 c->exec();
 c->~conceptos();
}

void Mrconta::seguridad()
{
	copiaseg *s = new copiaseg();
	s->exec();
	s->~copiaseg();
}

void Mrconta::buscasubcuentas()
{
 buscasubcuenta *s = new buscasubcuenta("");
 s->setWindowIcon(ui.actionSubcuentas->icon());
 int resultado=s->exec();
 QString lista;
 if (resultado==QDialog::Accepted){
 	
       lista = s->seleccioncuenta();
       QMessageBox::information( this, tr("DIARIO"),tr("CUENTA"), lista);
    }
 s->~buscasubcuenta();
}

void Mrconta::buscarconcepto()
{
 buscaconcepto *b = new buscaconcepto("");
 b->setWindowIcon(ui.actionConceptos->icon());
 int resultado=b->exec();
 if (resultado==QDialog::Accepted)
       QMessageBox::information( this, tr("DIARIO"),b->seleccionconcepto());

 b->~buscaconcepto();
}

void Mrconta::nuevoasiento()
{
 entrada="";
 QString asiento;
 asiento=ultimonumasiento("1");
 introfecha *i = new introfecha();
 //i->fijarDiaMinimo(fechaMaxAsiento(asiento));
 //if(DEBUG) QMessageBox::warning(this, "Debug","ASIENTO: "+asiento);
 int resultado=i->exec();
 QDate fecha=i->fecha();
 //fecha=fecha.currentDate();
 int semana=fecha.weekNumber();
 QString eje = ejerciciodelafecha(fecha);
 if (semana == 1){
 	if (eje != ejerciciodelafecha(fecha.addDays(8)))
 		semana = 53;
	}
 asiento.setNum(semana);
 i->~introfecha();
 if (!resultado==QDialog::Accepted) return;
 if (existeAsientoEspera(asiento) && QMessageBox::question(
            this, tr("Asiento en espera"),
            tr("Existen datos en espera para la semana seleccionada.\n"
               "Si los ignora se perderán las entradas guardadas.\n"
               "¿ Desea cargar los datos de la semana < %1 > ?").arg( asiento ),
            tr("&Ignorar"), tr("&Ver"),
            QString::null, 0, 1 )){
 			entrada=asiento;
 			asientosEspera();
 			entrada="";

	}else{
		if (existeasiento(asiento,eje) && QMessageBox::question(
            this, tr("Semana en diario"),
            tr("Existen datos en el diario para la semana seleccionada.\n"
               "Si los ignora se perderán las entradas guardadas.\n"
               "¿ Desea cargar los datos de la semana < %1 > ?").arg( asiento ),
            tr("&Ignorar"), tr("&Cargar"),
            QString::null, 0, 1 )){
                funcEdAsiento(asiento,eje);
            	refrescardiario();
            	//return;
            	
     	}else{
     		if (existeasiento(asiento,eje))
     			QMessageBox::warning( this, tr("Nuevo asiento"),
    			tr("Si ignora las entradas ya guardadas para la semana %1, se borrarán automáticamente.\n").arg(asiento)
    			+tr("Si no quiere perder las entradas guardadas cancele la edición."));
            	
    		tabla_asientos *t = new tabla_asientos(estilonumerico,!sindecimales);
	 		//punterodiario->~diario();
	 		//setCentralWidget(t);
	 		t->pasaFechaInicial(fecha);
	 		t->pasanumasiento(asiento);
	 		t->exec();
	 		t->~tabla_asientos();
	 		refrescardiario();
 		}
	}
}

void Mrconta::nuevoAsientoAuto()
{
 tabla_asientos *t = new tabla_asientos(estilonumerico,!sindecimales);
 t->incorporaEdicion();
 t->exec();
 t->~tabla_asientos();
 refrescardiario();
}

void Mrconta::editaasiento()
{
    QString elasiento;
    qlonglong numasiento=punterodiario->asientoactual();
    if (numasiento!=0) elasiento.setNum(numasiento);
    if (elasiento=="")
       {
         QMessageBox::warning( this, tr("EDICIÓN DE ASIENTOS"),
         tr("Para editar asiento debe de seleccionar un pase del mismo en el diario"));
         return;
       }
    
      QDate fechapase;
      fechapase=punterodiario->fechapaseactual();
      QString ejercicio=ejerciciodelafecha(fechapase);
      if (ejerciciocerrado(ejercicio) || ejerciciocerrando(ejercicio))
       {
         QMessageBox::warning( this, tr("EDICIÓN DE ASIENTOS"),
			       tr("ERROR: El pase seleccionado corresponde a un ejercicio cerrado"));
         return;
       }

      funcEdAsiento(elasiento,ejercicio);
      refrescardiario();
}

void Mrconta::editaNumAsiento()
{
  pidenombre *numas=new pidenombre();
  numas->asignanombreventana(tr("DIARIO"));
  numas->asignaetiqueta(tr("Número de asiento:"));
  numas->exec();
  QString elasiento=numas->contenido();
  numas->~pidenombre();

  if (elasiento=="")
  {
     return;
  }

  //if (numeracionrelativa())
  // {
    pideejercicio *ej=new pideejercicio();
    ej->asignanombreventana(tr("DIARIO"));
    ej->asignaetiqueta(tr("Código de ejercicio:"));
    ej->exec();
    QString elejercicio=ej->contenido();
    //qlonglong absoluto=primerasiento(elejercicio)+elasiento.toLongLong()-1;
    //elasiento.setNum(absoluto);
  // } 
  
      
   if (!existeasiento(elasiento,elejercicio))
   {
      QMessageBox::warning( this, tr("EDICIÓN DE ASIENTOS"),
			       tr("ERROR: El número suministrado no existe en el diario"));
      return;
   }
      
   //QDate fechapase;
   //fechapase=fechaMaxAsiento(elasiento,elejercicio);
   //QString ejercicio=ejerciciodelafecha(fechapase);
   if (ejerciciocerrado(elejercicio) || ejerciciocerrando(elejercicio))
   {
         QMessageBox::warning( this, tr("EDICIÓN DE ASIENTOS"),
			       tr("ERROR: El asiento corresponde a un ejercicio cerrado"));
         return;
   }

   funcEdAsiento(elasiento,elejercicio);
   refrescardiario();
}

void Mrconta::borraasiento()
{
    QString elasiento;
    qlonglong numasiento=punterodiario->asientoactual();
    if (numasiento!=0) elasiento.setNum(numasiento);
    if (elasiento=="")
       {
         QMessageBox::warning( this, tr("EDICIÓN DE ASIENTOS"),
         tr("Para borrar un asiento debe de seleccionar un pase del mismo en el diario"));
         return;
       }
    
      QDate fechapase;
      fechapase=punterodiario->fechapaseactual();
      QString ejercicio=ejerciciodelafecha(fechapase);
      if (ejerciciocerrado(ejercicio) || ejerciciocerrando(ejercicio))
       {
         QMessageBox::warning( this, tr("BORRA ASIENTO"),
			       tr("ERROR: El pase seleccionado corresponde a un ejercicio cerrado"));
         return;
       }
  QString relas;
  if (numeracionrelativa())
      relas=numrelativa(elasiento);
    else relas=elasiento;
  if (!QMessageBox::question(
            this,
            tr("¿ Borrar asiento ?"),
            tr("¿ Desea borrar el asiento %1 ?").arg(relas ),
            tr("&Sí"), tr("&No"),
            QString::null, 1, 1 ) ==0 )
                          return;
   borraAsientoEjercicio(elasiento,ejercicio);
   refrescardiario();
}

void Mrconta::actualizaplan()
{
  if (QMessageBox::question(
            this, tr("Importar/actualizar plan contable"),
            tr("Este proceso actualiza el plan de cuentas a partir\n"
               "de un fichero de texto. No se efectúa ningún control\n"
               "sobre el contenido de la información. Sólo se dan\n"
               "de alta los códigos inexistentes;\n"
               "sería conveniente realizar una copia de seguridad\n"
               "antes de realizar la operación,\n"
               "¿ Desea proseguir ?"),
            tr("&Sí"), tr("&No"),
            QString::null, 0, 1 ) !=0 )
                          return;

  QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::ExistingFile);
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  dialogofich.setFilter("*.txt *.pln");
  dialogofich.setDirectory(adapta(dirtrabajo));
  dialogofich.setWindowTitle(tr("SELECCIÓN DE ARCHIVO PARA IMPORTAR CUENTAS PLAN"));
  // dialogofich.exec();
  //QString fileName = dialogofich.getOpenFileName(this, tr("Seleccionar archivo para importar asientos"),
  //                                              dirtrabajo,
  //                                              tr("Ficheros de texto (*.txt)"));
  QStringList fileNames;
  if (dialogofich.exec())
     {
      fileNames = dialogofich.selectedFiles();
      if (fileNames.at(0).length()>0)
          {
           // QString cadfich=cadfich.fromLocal8Bit(fileNames.at(0));
           QString cadfich=fileNames.at(0);
           if (importarfichplan(cadfich))
               {
                QMessageBox::information( this, tr("DIARIO"),
                             tr("El archivo seleccionado se ha importado correctamente"));
               }
          }
     }
}

bool Mrconta::importarfichplan(QString qfichero)
{
  QFile fichero(adapta(qfichero));
  if (!fichero.exists()) return false;

  if ( fichero.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &fichero );
        stream.setCodec("UTF-8");
        QString linea;
        while ( !stream.atEnd() )
          {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            QString codigo,descripcion;
            codigo=linea.section('\t',0,0);
            if (existecodigoplan(codigo,&descripcion)) continue;
            if (codigo.length()==0) continue;
            descripcion=linea.section('\t',1,1);
            QString cad1="insert into plancontable (codigo,descripcion) values ('";
            cad1+=codigo;
            cad1+="','";
            cad1+=descripcion;
            cad1+="');";
            QSqlQuery query(cad1);
         }
        fichero.close();
      } else return false;

  return true;

}
void Mrconta::exportplan()
{
  QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::AnyFile);
  dialogofich.setConfirmOverwrite ( false );
  dialogofich.setAcceptMode (QFileDialog::AcceptSave );
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  QStringList filtros;
  filtros << tr("Archivos de texto con plan (*.pln)");
  dialogofich.setFilters(filtros);
  dialogofich.setDirectory(adapta(dirtrabajo));
  dialogofich.setWindowTitle(tr("ARCHIVO PARA EXPORTAR PLAN DE CONTABILIDAD"));
  // dialogofich.exec();
  //QString fileName = dialogofich.getOpenFileName(this, tr("Seleccionar archivo para importar asientos"),
  //                                              dirtrabajo,
  //                                              tr("Ficheros de texto (*.txt)"));
  QStringList fileNames;
  if (dialogofich.exec())
     {
      fileNames = dialogofich.selectedFiles();
      if (fileNames.at(0).length()>0)
          {
           // QString nombre=nombre.fromLocal8Bit(fileNames.at(0));
           QString nombre=fileNames.at(0);
           if (nombre.right(4)!=".pln") nombre=nombre+".pln";
            QFile plan( adapta(nombre)  );
            if (plan.exists() && QMessageBox::question(this,
                tr("¿ Sobreescribir ? -- Exportar plan"),
                tr("'%1' ya existe."
                   "¿ Desea sobreescribirlo ?")
                  .arg( nombre ),
                tr("&Sí"), tr("&No"),
                QString::null, 0, 1 ) )
              return ;
            if (exportaplan(nombre,false))
               {
                QMessageBox::information( this, tr("EXPORTAR PLAN"),
                             tr("El archivo se ha generado correctamente"));
               }
          }
     }

}



bool Mrconta::exportaplan(QString fichero,bool subcuentas)
{

  QFile plan( adapta(fichero)  );

  if ( !plan.open( QIODevice::WriteOnly ) ) 
       {
        QMessageBox::warning( this, tr("Exportación de plan contable"),tr("Error: Imposible grabar fichero"));
        return false;
       }
  QTextStream planstream( &plan );
  planstream.setCodec("UTF-8");

  QString cadena="select codigo,descripcion from plancontable ";
  if (!subcuentas) 
     {
       cadena+="where char_length(codigo)<";
       QString cadnum;
       cadena+=cadnum.setNum(anchocuentas());
       cadena+=" ";
     }
  cadena+="order by codigo";

  QSqlQuery query(cadena);
   if ( query.isActive() )
       while (query.next())
          {
              planstream << query.value(0).toString() << "\t";
              planstream << query.value(1).toString() <<  "\n";
         }
  // planstream << "\\.";
  plan.close();
  return true;
}


void Mrconta::exportplansubcuentas()
{
  QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::AnyFile);
  dialogofich.setConfirmOverwrite ( false );
  dialogofich.setAcceptMode (QFileDialog::AcceptSave );
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  QStringList filtros;
  filtros << tr("Archivos de texto con plan (*.pln)");
  dialogofich.setFilters(filtros);
  dialogofich.setDirectory(adapta(dirtrabajo));
  dialogofich.setWindowTitle(tr("ARCHIVO EXPORTAR PLAN DE CONTABILIDAD CON SUBCUENTAS"));
  // dialogofich.exec();
  //QString fileName = dialogofich.getOpenFileName(this, tr("Seleccionar archivo para importar asientos"),
  //                                              dirtrabajo,
  //                                              tr("Ficheros de texto (*.txt)"));
  QStringList fileNames;
  if (dialogofich.exec())
     {
      fileNames = dialogofich.selectedFiles();
      if (fileNames.at(0).length()>0)
          {
           // QString nombre=nombre.fromLocal8Bit(fileNames.at(0));
           QString nombre=fileNames.at(0);
           if (nombre.right(4)!=".pln") nombre=nombre+".pln";
            QFile plan( adapta(nombre)  );
            if (plan.exists() && QMessageBox::question(this,
                tr("¿ Sobreescribir ? -- Exportar plan"),
                tr("'%1' ya existe."
                   "¿ Desea sobreescribirlo ?")
                  .arg( nombre ),
                tr("&Sí"), tr("&No"),
                QString::null, 0, 1 ) )
              return ;
            if (exportaplan(nombre,true))
               {
                QMessageBox::information( this, tr("EXPORTAR PLAN"),
                             tr("El archivo se ha generado correctamente"));
               }
          }
     }

}

void Mrconta::ImprimeDiario()
{
   imprimediario *laimpri=new imprimediario();
   laimpri->pasafiltro( filtroactivo );
   laimpri->setWindowIcon(ui.actionImprimir_diario->icon());
   laimpri->exec();
   laimpri->~imprimediario();
}

void Mrconta::generarpdf()
{
  QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::ExistingFiles);
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  QStringList filtros;
  filtros << tr("Archivos tex (*.tex)");
  dialogofich.setFilters(filtros);
  dialogofich.setDirectory(adapta(dirtrabajo));
  dialogofich.setWindowTitle(tr("GENERAR PDF"));
  // dialogofich.exec();
  //QString fileName = dialogofich.getOpenFileName(this, tr("Seleccionar archivo para importar asientos"),
  //                                              dirtrabajo,
  //                                              tr("Ficheros de texto (*.txt)"));
  QStringList fileNames;
  if (dialogofich.exec())
     {
      fileNames = dialogofich.selectedFiles();
      for (int veces=0;veces<fileNames.count();veces++)
        if (fileNames.at(veces).length()>0)
          {
           // QString cadfich=cadfich.fromLocal8Bit(fileNames.at(veces));
           QString cadfich=fileNames.at(veces);
           int valor=generapdffichabs(cadfich);
           if (valor==1)
             QMessageBox::warning( this, tr("Generar PDF"),tr("PROBLEMAS al llamar a Latex"));
           if (valor==2)
             QMessageBox::warning( this, tr("Generar PDF"),
                             tr("PROBLEMAS al llamar a ")+"dvipdf");
           if (valor==0)
             QMessageBox::information( this, tr("Generar PDF"),
                             tr("Se ha generado el archivo PDF"));
          }
     }

}

void Mrconta::actuSaldos()
{
  actualizasaldos();
  QMessageBox::information( this, tr("ACTUALIZACIÓN DE SALDOS"),
  tr("Operación realizada correctamente"));
}

void Mrconta::asientosEspera()
{
  cargaespera *lacargaespera=new cargaespera(entrada);
  lacargaespera->setWindowIcon(ui.actionCargar_asiento_en_espera->icon());
  int resultado=lacargaespera->exec();
  if (resultado==QDialog::Accepted)
  {
    // procesamos asiento en espera actual  en cargaespera
    qlonglong AstoEspera=lacargaespera->asientoactual();
    if (AstoEspera>0)
    {
       tabla_asientos *tablaasiento=new tabla_asientos(estilonumerico,!sindecimales);
       QString consulta="SELECT cuenta,concepto,debe,haber,documento,ctabaseiva,baseiva,";
       consulta+="claveiva,tipoiva,tipore,cuotaiva,cuentafra,diafra,mesfra,anyofra,soportado,ci ";
       consulta+="FROM borrador where asiento=";
       QString cadasiento; cadasiento.setNum(AstoEspera);
       consulta+=cadasiento;
       consulta+=" ORDER BY mesfra,diafra,cuenta;";
       int fila=0;
       //QString dia,mes,anyo;
       QSqlQuery query( consulta );
            if ( query.isActive() ) {
                while ( query.next() ) {
		    tablaasiento->pasadatos(fila,query.value(0).toString() ,
                                                          query.value(1).toString(),
                                                          query.value(2).toString(),
                                                          query.value(3).toString(),
                                                          query.value(4).toString(),
                                                          query.value(5).toString(),
                                                          query.value(6).toString(),
                                                          query.value(7).toString(),
                                                          query.value(8).toString(),
                                                          query.value(9).toString(),
                                                          query.value(10).toString(),
                                                          query.value(11).toString(),
                                                          query.value(12).toString(),
                                                          query.value(13).toString(),
                                                          query.value(14).toString(),
                                                          query.value(15).toString(),
                                                          query.value(16).toString() );
		    //dia=query.value(12).toString();
		    //mes=query.value(13).toString();
		    //anyo=query.value(14).toString();
		    fila++;
		}
	    }
        lacargaespera->elimasientoactual();
        tablaasiento->chequeatotales();
        tablaasiento->pasanumasiento(cadasiento);
        //QDate date;
        //date.setYMD(anyo.toInt(),mes.toInt(),dia.toInt());
        //tablaasiento->pasafechaasiento(date);
        tablaasiento->exec();
        tablaasiento->~tabla_asientos();
        refrescardiario();
       }
  }
lacargaespera->~cargaespera();
}

void Mrconta::genbss()
{
 bss *b = new bss();
 b->exec();
 delete(b);
}

void Mrconta::imprimemayor()
{
 cuadimprimayor *c = new cuadimprimayor(estilonumerico,!sindecimales);
 c->exec();
 delete(c);
}

void Mrconta::procvencimientos()
{
  listavenci *l = new listavenci();
  l->exec();
  l->~listavenci();
  actualizasaldos();
  refrescardiario();
}

void Mrconta::vtosSemana()
{
	int sem = punterodiario->asientoactual();
	if (!sem){
		QMessageBox::warning( this, tr("VENCIMIENTOS"),
		tr("Para cambiar datos de la semana debe seleccionar un pase en el diario"));
		return;
	}
	listavenci *l = new listavenci();
	l->pasaSemana(QString("%1").arg(sem),ejerciciodelafecha(punterodiario->fechapaseactual()));
	l->exec();
	l->~listavenci();
	actualizasaldos();
	refrescardiario();
}

void Mrconta::vtosCuenta()
{
	QString cuenta=punterodiario->subcuentaactual();
	if (cuenta.length()==0){
		QMessageBox::warning( this, tr("VENCIMIENTOS"),
		tr("Para cambiar datos de la subcuenta debe seleccionar un pase en el diario"));
		return;
	}
	listavenci *l = new listavenci();
	l->pasaCuenta(cuenta);
	l->exec();
	l->~listavenci();
	actualizasaldos();
	refrescardiario();
}

void Mrconta::qtiposiva()
{
  tiposiva *t = new tiposiva();
  t->exec();
  delete(t);
}

void Mrconta::edPase()
{
  qlonglong pase=punterodiario->paseactual();
  QString qapunte;
  if (pase>0) qapunte.setNum(pase);
  if (qapunte=="")
       {
         QMessageBox::warning( this, tr("EDITAR PASE"),
         tr("Para cambiar datos debe de seleccionar un pase en el diario"));
         return;
       }
  QDate qfecha=punterodiario->fechapaseactual();
  editapaseconci *ep = new editapaseconci();
  ep->pasadatos(qapunte,qfecha,punterodiario->conceptoactual(),formateanumero(punterodiario->debe(),estilonumerico,!sindecimales)
  				,formateanumero(punterodiario->haber(),estilonumerico,!sindecimales));
  ep->exec();
  delete(ep);
  refrescardiario();
}

void Mrconta::edcondoc()
{
  qlonglong pase=punterodiario->paseactual();
  QString qapunte;
  if (pase>0) qapunte.setNum(pase);
  if (qapunte=="")
       {
         QMessageBox::warning( this, tr("EDITAR CONCEPTO / DOCUMENTO"),
         tr("Para cambiar datos debe de seleccionar un pase en el diario"));
         return;
       }
  QDate qfecha=punterodiario->fechapaseactual();

  edit_conc_doc *e = new edit_conc_doc();
  e->pasadatos( qapunte, qfecha, punterodiario->conceptoactual(), punterodiario->documentoactual() );
  /*QString deb,hab;
  e->pasaEtiqueta(punterodiario->subcuentaactual()+"\t"+deb.setNum(punterodiario->debe())+
  						"\t"+hab.setNum(punterodiario->haber()));
  */
  e->exec();
  delete(e);
  refrescardiario();
}

void Mrconta::librosagr()
{
  libros *l = new libros();
  l->exec();
  delete(l);
}

void Mrconta::libroFactRec()
{
	libroiva *iv = new libroiva();
	iv->exec();
	delete(iv);
}

void Mrconta::acummes()
{
  acumuladosmes *a = new acumuladosmes();
  a->pasacodigocuenta(punterodiario->subcuentaactual(),punterodiario->fechapaseactual());
  a->exec();
  delete(a);
}

void Mrconta::consultaplan()
{
  consplan *c = new consplan();
  c->exec();
  delete(c);
}

void Mrconta::consultamayor()
{
 consmayor *c = new consmayor(estilonumerico,!sindecimales);
 c->pasadatos( punterodiario->subcuentaactual(), punterodiario->fechapaseactual() );
 c->exec();
 delete(c);
}

void Mrconta::importaLaCaixa()
{
 lacaixa *lc = new lacaixa(estilonumerico,!sindecimales);
 lc->exec();
 delete(lc);
 refrescardiario();
}

void Mrconta::consultatex()
{
  QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::ExistingFile);
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  QStringList filtros;
  filtros << tr("Archivos tex (*.tex)");
  dialogofich.setFilters(filtros);
  dialogofich.setDirectory(adapta(dirtrabajo));
  dialogofich.setWindowTitle(tr("VISUALIZAR ARCHIVO TEX"));
  // dialogofich.exec();
  //QString fileName = dialogofich.getOpenFileName(this, tr("Seleccionar archivo para importar asientos"),
  //                                              dirtrabajo,
  //                                              tr("Ficheros de texto (*.txt)"));
  QStringList fileNames;
  if (dialogofich.exec())
     {
      fileNames = dialogofich.selectedFiles();
      if (fileNames.at(0).length()>0)
          {
           // QString cadfich=cadfich.fromLocal8Bit(fileNames.at(0));
           QString cadfich=fileNames.at(0);
           int valor=consultalatex2fichabs(cadfich);
           if (valor==1)
             QMessageBox::warning( this, tr("Visualizar TEX"),tr("PROBLEMAS al llamar a Latex"));
           if (valor==2)
             QMessageBox::warning( this, tr("Visualizar TEX"),
                             tr("PROBLEMAS al llamar a ")+visordvi);
          }
     }

}

void Mrconta::grafOper()
{
	pideejercicio *ej=new pideejercicio();
	ej->asignanombreventana(tr("DIARIO"));
	ej->asignaetiqueta(tr("Código de ejercicio:"));
	ej->exec();
	QString elejercicio=ej->contenido();
	delete(ej);
	QString filtro="(fecha>='";
	filtro+=inicioejercicio(elejercicio).toString("yyyy.MM.dd");
	filtro+="' AND fecha<='";
	filtro+=finejercicio(elejercicio).toString("yyyy.MM.dd");
	filtro+="')";
	QString sem,cad;
	double total = 0.0;
	QList<double> valores1;
	QList<double> valores2;
	int minSem = 0, maxSem = 0;
	cad="SELECT min(asiento),max(asiento) from diario WHERE ";
	cad+=filtro;
	QSqlQuery query = ejecutarSQL(cad);
	if ( (query.isActive()) && (query.first()) )
	{
		minSem = query.value(0).toInt();
		maxSem = query.value(1).toInt();
	}
	if (minSem == 0 || maxSem == 0 || minSem == maxSem) return;
	//Comenzar en coordenadas (minSem,0)
	//valores1 << minSem-1;
	//valores2 << 0.0;
	for(int i=minSem ; i<=maxSem; i++)
	{
		sem.setNum(i);
		valores1 << sem.toDouble();
		cad="SELECT sum(debe) from diario where position('";
		cad+=grupoGastos();
		cad+="' in cuenta)=1 AND asiento='";
		cad+=sem;
		cad+="' AND ";
		cad+=filtro;
		query = ejecutarSQL(cad);
		if ( (query.isActive()) && (query.first()) )
		{
			valores2 << query.value(0).toDouble();
			total += query.value(0).toDouble();
		}
		else
			valores2 << 0.0;
	}
	//Acabar en coordenadas (maxSem,0)
	//valores1 << maxSem+1;
	//valores2 << 0.0;
        //grafico *gr = new grafico(tr("Ejercicio ")+elejercicio,tr("Semanas"),tr("Euros"),
        //					estilonumerico,!sindecimales);
	pastel *p=new pastel();
	
	//QColor null;
	
        //gr->addCurva(Qt::darkBlue,tr("Gastos"),valores1,valores2);
	p->addPorcion(Qt::darkBlue,tr("Gastos"),total);
	valores2.clear();
	total = 0.0;
	//valores2 << 0.0;//Comenzar en zero
	for(int i=minSem ; i<=maxSem; i++)
	{
		sem.setNum(i);
		cad="SELECT sum(haber) from diario where position('";
		cad+=grupoIngresos();
		cad+="' in cuenta)=1 AND asiento='";
		cad+=sem;
		cad+="' AND ";
		cad+=filtro;
		query = ejecutarSQL(cad);
		if ( (query.isActive()) && (query.first()) )
		{
			valores2 << query.value(0).toDouble();
			total += query.value(0).toDouble();
		}
		else
			valores2 << 0.0;
	}
	//valores2 << 0.0;//Acabar en zero
        //gr->addCurva(Qt::darkRed,tr("Ingresos"),valores1,valores2);
	p->addPorcion(Qt::darkRed,tr("Ingresos"),total);
	QTabWidget *tab = new QTabWidget();
        //tab->addTab(gr,tr("Temporal"));
	tab->addTab(p,tr("Total"));
	QGridLayout *l = new QGridLayout();
	l->addWidget(tab);
	l->setSpacing(4);
	l->setMargin(4);
	QDialog *d = new QDialog(this);
	d->setLayout(l);
	d->setWindowTitle(ui.actionOperaciones->text());
	d->setWindowIcon(ui.actionOperaciones->icon());
	d->resize(650,450);
	d->exec();
        //gr->~grafico();
	delete(p);
	delete(tab);
	//setCentralWidget(gr);
}

void Mrconta::marcarcerrado()
{
  pideejercicio *p = new pideejercicio();
  p->asignanombreventana(tr("Marcar ejercicio como cerrado"));
  int resultado=p->exec();
  if (resultado==QDialog::Accepted)
  {
  	cierres *cer = new cierres(p->contenido());
  	if(cer->marcarCerrado())
  		QMessageBox::information( this, tr("Marcar como cerrado"),
	              tr("El ejercicio seleccionado se ha marcado como cerrado"));
	delete(cer);
  	 
  }
  delete(p);
}

void Mrconta::suprimircierre()
{
  pideejercicio *p = new pideejercicio();
  p->asignanombreventana(tr("Suprimir cierre ejercicio"));
  int resultado=p->exec();
  if (resultado==QDialog::Accepted)
  {
  	cierres *cer = new cierres(p->contenido());
  	if(cer->suprimeCierre())
  		QMessageBox::information( this, tr("Deshacer cierre"),
	              tr("Se ha eliminado el cierre para el ejercicio seleccionado"));
	delete(cer);
  	 
  }
  delete(p);
}

void Mrconta::editarEquivalencias()
{
 equivalencias *e = new equivalencias();
 e->setWindowIcon(ui.actionEditar_equivalencias->icon());
 e->exec();
 e->~equivalencias();
}

void Mrconta::importasientos()
{
 importaSemanas *i = new importaSemanas(dirtrabajo);
 i->exec();
 delete(i);
 refrescardiario();
}

void Mrconta::copiar()
{
	punterodiario->copiar();
}

void Mrconta::tiposdiario()
{
 diarios *d = new diarios();
 d->exec();
 delete(d);
}

void Mrconta::asignardiario()
{
 QItemSelectionModel *seleccion;
 CustomSqlModel *model=punterodiario->modelo();
 seleccion=punterodiario->tabladiario()->selectionModel();
 if (seleccion->hasSelection())
 {
 	QList<QModelIndex> lista;
 	lista = seleccion->selectedRows (9);
 	asignadiario *a = new asignadiario();
 	for (int i = 0; i < lista.size(); ++i)
 		a->pasaPase(model->data(lista.at(i),Qt::DisplayRole).toString());
 	a->exec();
 	delete(a);
 	refrescardiario();
 	return;
 }else{
         QMessageBox::warning( this, tr("ASIGNAR DIARIO"),
         tr("Para asignar un diario debe de seleccionar un pase, como mínimo, del mismo en el diario"));
         return;
       }
}

void Mrconta::actualizade07()
{
  QSqlDatabase bd=QSqlDatabase::database ();
  QString acontrolador= bd.driverName();
  bool cmysql=(acontrolador.contains("MYSQL")) ;

           QMessageBox::information( this, tr("Apertura de base de datos"),
		     tr("Se van a actualizar las tablas para la versión 0.8"));
           
           //ejecutarSQL("update configuracion set version='0.8';");

           /*ejecutarSQL("alter table libroiva add column prorrata numeric(5,2) default 1;");

           ejecutarSQL("alter table libroiva add column rectificativa bool default false,"
                      " add column autofactura bool default false;");
		   ejecutarSQL("CREATE TABLE dif_conciliacion ("
                       "codigo        varchar(40),"
                       "descripcion   varchar(80) default '',"
                       "PRIMARY KEY (codigo) );");*/
          if (cmysql)
            {
             //ejecutarSQL("alter table diario change ci ci date default NULL;");
            }
            else
                {
                 //ejecutarSQL("alter table diario alter column ci type date default NULL;");
                }

           //ejecutarSQL("alter table amortcontable add primary key (ejercicio);");

           QMessageBox::information( this, tr("Actualización de base de datos"),
		     tr("La operación se ha realizado"));

}

