#include <QtGui>
#include "funciones.h"
#include "basedatos.h"
#include "importasemanas.h"
//
importaSemanas::importaSemanas( QString dirtrabajo = dirtrabajodefecto()  ) 
	: QDialog()
{
  ui.setupUi(this);
  dir = dirtrabajo;
  setWindowTitle(tr("Importar semanas"));
  ui.textLabel1->setText(tr("FICHERO A IMPORTAR:"));
  ui.textLabel2->setText("...");
  ui.aceptarpushButton->setText(tr("Abrir..."));
  ui.progressBar->setTextVisible(true);
  connect(ui.aceptarpushButton,SIGNAL(clicked()),SLOT(cargarFichero()));
}

void importaSemanas::cargarFichero()
{
	ui.aceptarpushButton->setEnabled(false);
	QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::ExistingFile);
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  QStringList filtros;
  filtros << tr("Archivos de texto (*.txt)");
  dialogofich.setFilters(filtros);
  dialogofich.setDirectory(adapta(dir));
  dialogofich.setWindowTitle(tr("SELECCIÓN DE ARCHIVO PARA IMPORTAR"));
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
           if (comprovarFichero(cadfich))
               {
                //refrescardiario();
				ui.aceptarpushButton->disconnect(SIGNAL(clicked()));
				ui.aceptarpushButton->setText(tr("Importar"));
				ui.aceptarpushButton->setToolTip(cadfich);
                QMessageBox::information( this, tr("Importar semanas"),
                             tr("El archivo seleccionado es correcto.\nPulse Importar para comenzar el proceso."));
                connect(ui.aceptarpushButton,SIGNAL(clicked()),SLOT(importarFichero()));
                //punterodiario->irfinal();
               }
          }
     }
     ui.aceptarpushButton->setEnabled(true);
}

bool importaSemanas::comprovarFichero(QString qfichero)
{
	QFile fichero(adapta(qfichero));
	if (!fichero.exists()) return false;
	int numlineas=0;
	// contamos número de líneas del fichero
	if ( fichero.open( QIODevice::ReadOnly ) ) {
		QTextStream stream( &fichero );
		stream.setCodec("UTF-8");
		while ( !stream.atEnd() ) {
			QString linea;
			linea = stream.readLine(); // linea de texto excluyendo '\n'
			numlineas++;
		}
		fichero.close();
	} else return false;
	
	ui.progressBar->setMaximum(numlineas);
	int lineaactu=0;
	
	// primero comprobamos que la información es correcta
	if ( fichero.open( QIODevice::ReadOnly ) ) {
		ui.textLabel2->setText(tr("Comprovando fichero %1 ...").arg(qfichero.section(QDir::separator(),-1)));
		QTextStream stream( &fichero );
		stream.setCodec("UTF-8");
		QString linea;
		long numasiento=0;
		long guardaasiento=-1;
		double sumadebe=0;
		double sumahaber=0;
		while ( !stream.atEnd() ) {
			linea = stream.readLine(); // linea de texto excluyendo '\n'
			lineaactu++;
			ui.progressBar->setValue(lineaactu);
			//numlineas++;
			// analizamos la linea de texto
			// asiento fecha concepto cuenta debe haber documento ----- separados por tabulador
			QString asiento,fecha,cuenta,concepto,debe,haber,fecha2;
			asiento=linea.section('\t',0,0);
			numasiento=asiento.toLong();
			if (guardaasiento==-1) guardaasiento=numasiento;
			fecha=linea.section('\t',1,1);
			// corregir orden en fecha
			QString dia=fecha.left(2);
			QString mes=fecha.mid(3,2);
			QString anyo=fecha.right(4);
			if (fecha.length()<9) anyo=fecha.right(2);
			fecha=anyo+".";
			fecha+=mes;
			fecha+=".";
			fecha+=dia;
			QDate lafecha;
			int valanyo=anyo.toInt();
			if (valanyo<100 && valanyo>50) valanyo+=1900;
			if (valanyo<100 && valanyo<=50) valanyo+=2000;
			lafecha.setDate(valanyo,mes.toInt(),dia.toInt());
			if (!fechacorrespondeaejercicio(lafecha) || fechadejerciciocerrado(lafecha))
			{
			   QMessageBox::warning( this, tr("Importar semanas"),
			tr("Error en linea %1, la fecha (%2) no es correcta\n"
			"El fichero contiene errores.").arg(QString("%1").arg(lineaactu),fecha));
				fichero.close();
			   return false; 
			}
			cuenta=linea.section('\t',2,2);
			concepto=linea.section('\t',3,3);
			debe=convapunto(linea.section('\t',4,4));
			haber=convapunto(linea.section('\t',5,5));
			if (!existesubcuenta(cuenta))
			{
			   QMessageBox::warning( this, tr("Importar semanas"),
			tr("Error en linea %1, código de cuenta inexistente o con varios resultados: %2\n"
			"El fichero contiene errores.").arg(QString("%1").arg(lineaactu),cuenta));
				fichero.close();
			   return false;
			}
			fecha2=linea.section('\t',7,7);
			if (fecha2.length() > 0){
				// corregir orden en fecha
				dia=fecha.left(2);
				mes=fecha.mid(3,2);
				anyo=fecha.right(4);
				if (fecha2.length()<9) anyo=fecha2.right(2);
				fecha2=anyo+".";
				fecha2+=mes;
				fecha2+=".";
				fecha2+=dia;
				QDate lafecha2;
				valanyo=anyo.toInt();
				if (valanyo<100 && valanyo>50) valanyo+=1900;
				if (valanyo<100 && valanyo<=50) valanyo+=2000;
				lafecha2.setDate(valanyo,mes.toInt(),dia.toInt());
				if (!fechacorrespondeaejercicio(lafecha2) || fechadejerciciocerrado(lafecha2))
				{
				   QMessageBox::warning( this, tr("Importar semanas"),
				tr("Error en linea %1, la fecha (%2) no corresponde.\n"
				"El fichero contiene errores.").arg(QString("%1").arg(lineaactu),fecha2));
					fichero.close();
				   return false; 
				}
			}
			/*    if (escuentadeivasoportado(cuenta) || escuentadeivarepercutido(cuenta))
			{
			   QMessageBox::warning( this, tr("Importar asientos"),
			tr("Error, no se pueden incorporar asientos con cuentas de IVA \n"
			"la operación no se ha realizado."));
			   return false;
			}
			*/    
			if ((debe.toDouble()>0.001 || debe.toDouble()<-0.001) 
			&& (haber.toDouble()>0.001 || haber.toDouble()<-0.001))
			{
			   QMessageBox::warning( this, tr("Importar semanas"),
			tr("Error en linea %1, importes incorrectos,\n"
			"El fichero contiene errores.").arg(QString("%1").arg(lineaactu)));
				fichero.close();
			   return false;
			}
			if (numasiento!=guardaasiento)
			{
				if ((sumadebe<0.001 && sumadebe>-0.001)
					|| (sumahaber<0.001 && sumahaber>-0.001))
				{
				   QString cd,cd1,cd2;
				   cd.setNum(guardaasiento);
				   cd1.setNum(sumadebe,'f',2);
				   cd2.setNum(sumahaber,'f',2);
				   QMessageBox::warning( this, tr("Importar semanas"),
				tr("Error en linea %1, semana %2 incompleta %3 %4,\n"
				"El fichero contiene errores.").arg(QString("%1").arg(lineaactu),cd,cd1,cd2));
					fichero.close();
				   return false;
				
				}
				guardaasiento=numasiento;
				sumadebe=0;
				sumahaber=0;
			}
			sumadebe+=debe.toDouble();
			sumahaber+=haber.toDouble();
		}
		
		
		if ((sumadebe<0.001 && sumadebe>-0.001)
			|| (sumahaber<0.001 && sumahaber>-0.001))
		{
		  QString cd,cd1,cd2;
		  cd.setNum(guardaasiento);
		  cd1.setNum(sumadebe,'f',2);
		  cd2.setNum(sumahaber,'f',2);
		  QMessageBox::warning( this, tr("Importar semanas"),
		tr("Error, semana %1 incompleta %2 %3,\n"
		"El fichero contiene errores.").arg(cd,cd1,cd2));
			fichero.close();
		  return false;
		}
		fichero.close();
	} else return false;
	
	return true;

}

void importaSemanas::importarFichero()
{
	QString qfichero = ui.aceptarpushButton->toolTip();
	QFile fichero(adapta(qfichero));
	if (!fichero.exists()){
		QMessageBox::warning( this, tr("Importar semanas"),tr("El fichero no existe."));
		return;
	}
	// volvemos a abrir el fichero para procesar el asiento
	// actualizar saldossubcuentas
	// ojo con la fecha, hay que invertir orden de formato dd/mm/aaaa pasar a aaaa/mm/dd
	// eliminar ' y " de cadenas
	// cambiar comadecimal por punto decimal
	ui.textLabel2->setText(tr("Importando fichero %1 ...").arg(qfichero.section(QDir::separator(),-1)));
	//QMessageBox::information( this, tr("Importar semanas"),QString("Fichero: %1").arg(qfichero));
	if ( fichero.open( QIODevice::ReadOnly ) ) {
	QTextStream stream( &fichero );
	stream.setCodec("UTF-8");
	QString linea;
	QString cadfecha,cadfecha2;
	long numasiento=0;
	long guardaasiento=-1;
	QSqlDatabase contabilidad=QSqlDatabase::database();
	QString cadnumasiento;
	cadnumasiento.setNum(numasiento); 
	contabilidad.transaction();
	bloqueaTablasAsientos();
	int lineaactu=0;
	while ( !stream.atEnd() ) {
		if (sobreescribeproxasiento() && numasiento==0)
		{
		   QMessageBox::warning( this, tr("Importar asientos"),
		tr("Error, no se pueden sobreescribir asientos\n"
		      "revise número de próximo asiento en configuración."));
		break;
		}
		lineaactu++;
		ui.progressBar->setValue(lineaactu);
		linea = stream.readLine(); // linea de texto excluyendo '\n'
		// analizamos la linea de texto
		//  asiento fecha concepto cuenta debe haber documento ----- separados por tabulador
		QString asiento,fecha,cuenta,concepto,debe,haber,fecha2;
		asiento=linea.section('\t',0,0);
		numasiento=asiento.toLong();
		// if (guardaasiento==-1) guardaasiento=numasiento;
		fecha=linea.section('\t',1,1);
		fecha=quitacomillas(fecha);
		// corregir orden en fecha
		QString dia=fecha.left(2);
		QString mes=fecha.mid(3,2);
		QString anyo;
		anyo=fecha.right(4);
		if (fecha.length()<9) 
		  {
		   int valanyo=fecha.right(2).toInt();
		   if (valanyo<50) valanyo+=2000;
		      else valanyo+=1900;
		   anyo.setNum(valanyo);
		  }
		fecha=anyo+"/";
		fecha+=mes;
		fecha+="/";
		fecha+=dia;
		if (cadfecha.length()==0) cadfecha=fecha;
		fecha2=linea.section('\t',7,7);
		fecha2=quitacomillas(fecha2);
		if (fecha2.length() > 0){// corregir orden en fecha
			dia=fecha2.left(2);
			mes=fecha2.mid(3,2);
			anyo=fecha2.right(4);
			if (fecha2.length()<9) 
			  {
			   int valanyo=fecha2.right(2).toInt();
			   if (valanyo<50) valanyo+=2000;
			      else valanyo+=1900;
			   anyo.setNum(valanyo);
			  }
			fecha2=anyo+"/";
			fecha2+=mes;
			fecha2+="/";
			fecha2+=dia;
			if (cadfecha2.length()==0) cadfecha2=fecha2;
		}
		cuenta=linea.section('\t',2,2);
		cuenta=quitacomillas(cuenta);
		QString codigo;
		if (!cadnumvalido(cuenta) && unicoCodigoSubcuenta(&codigo,cuenta))
			cuenta=codigo;
		concepto=linea.section('\t',3,3);
		concepto=quitacomillas(concepto);
		debe=linea.section('\t',4,4);
		debe=convapunto(debe);
		haber=linea.section('\t',5,5);
		haber=convapunto(haber);
		QString documento=linea.section('\t',6,6);
		if (numasiento!=guardaasiento)
		{
		  guardaasiento=numasiento;
		  cadnumasiento.setNum(guardaasiento); 
		
		  if (existeasiento(cadnumasiento,ejerciciodelafecha(QDate::currentDate())) && QMessageBox::question(
            this, tr("Importar asientos"),
            tr("Existen datos en el diario para la semana a importar.\n"
               "¿ Seleccione la acción a seguir con los datos de la semana < %1 > ?").arg( cadnumasiento ),
            tr("&Añadir"), tr("&Sobreescribir"),
            QString::null, 0, 1 ))
			{
				borraAsientoEjercicio(cadnumasiento,ejerciciodelafecha(QDate::currentDate()));
			}
		}
		// procesamos aquí adición de pase
		qlonglong vnum2=0;
		vnum2 = proximoPase();
		QString cadnumpase,cad1;
		qlonglong pase=vnum2;
		cadnumpase.setNum(pase);
		cadfecha=fecha;
		cadfecha2=fecha2;
		cad1="INSERT into diario (asiento,pase,fecha,cuenta,debe,haber,concepto,documento,diario,usuario,ci) VALUES(";
		cad1+=cadnumasiento;
		cad1+=",";
		cad1+=cadnumpase;
		cad1+=",'";
		cad1+=cadfecha.left(-1).replace("'","''");
		cad1+="','";
		cad1+=cuenta.left(-1).replace("'","''");
		cad1+="',";
		if (debe.length()==0) cad1+="0"; else cad1+=debe;
		cad1+=",";
		if (haber.length()==0) cad1+="0"; else cad1+=haber;
		cad1+=",'";
		cad1+=concepto.left(-1).replace("'","''");
		cad1+="','";
		cad1+=documento.left(-1).replace("'","''");
		cad1+="','',CURRENT_USER,'";
		cad1+=cadfecha2.left(-1).replace("'","''");
		cad1+="');";
		// QMessageBox::warning( this, tr("Importar asientos"),cad1);
		ejecutarSQL(cad1);
		// queda actu saldo y proxpase
		QString cadq2;
		//QSqlQuery query2;
		cadq2="update saldossubcuenta set saldo=saldo+";
		if (debe.length()==0) cadq2+="0";
		else cadq2+=debe;
		cadq2+="-";
		if (haber.length()==0) cadq2+="0";
		else cadq2+=haber;
		cadq2+=" where codigo='";
		cadq2+= cuenta.left(-1).replace("'","''");
		 cadq2+="';";
		 ejecutarSQL(cadq2);
		pase++;
		cadnumpase.setNum(pase);
		ejecutarSQL("update configuracion set prox_pase="+cadnumpase);
	// -------------------------------------------------------------------
	} // final del while
	desbloqueaTablas();
	fichero.close();
	calculaprimerosasientos();
	ui.textLabel2->setText(tr("Fichero importado."));
	ui.aceptarpushButton->setEnabled(false);
	QMessageBox::information( this, tr("Importar semanas"),
                             tr("El archivo se ha importado correctamente."));
	} else return;
	

}

//
