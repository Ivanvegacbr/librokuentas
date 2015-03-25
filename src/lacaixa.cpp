#include <QtGui>
#include "lacaixa.h"
#include "basedatos.h"
#include "funciones.h"
#include "buscasubcuenta.h"
//
lacaixa::lacaixa( bool comadecimal, bool decimales ) 
	: QDialog()
{
  ui.setupUi(this);
  setWindowTitle(tr("Importar pases - La Caixa"));
  if(importarFichPases(abrirFichero())) ui.status->setText(tr("Fichero cargado..."));
  else ui.status->setText(tr("No se ha cargado ningún fichero"));
  stream.seek(0);
  fila=0;
  t = new tabla_asientos(comadecimal,decimales);
  connect(ui.sensibilidad,SIGNAL(valueChanged(int)),SLOT(sensibilidadCambiada(int)));
  connect(ui.buscapushButton,SIGNAL(clicked()),SLOT(botonsubcuentapulsado()));
  connect(ui.incorporarButton,SIGNAL(clicked()),this,SLOT(incorporar()));
  connect(ui.ignorarButton,SIGNAL(clicked()),this,SLOT(ignorar()));
  connect(ui.siguienteButton,SIGNAL(clicked()),this,SLOT(siguiente()));
  
}

void lacaixa::botonsubcuentapulsado()
{
    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.lineCuenta->text());
    int cod=labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();
    if (cod==QDialog::Accepted && existesubcuenta(cadena2))
      ui.lineCuenta->setText(cadena2);
       else ui.lineCuenta->setText("");
    delete labusqueda;

}

void lacaixa::sensibilidadCambiada(int sens)
{
	ui.linePatron->setText(ui.lineFound->text().left(ui.lineFound->text().length()
					*sens/ui.sensibilidad->maximum()));
}

bool lacaixa::importarFichPases(QString qfichero)
{
  fichero.setFileName(adapta(qfichero));
  if (!fichero.exists()) return false;
  if ( fichero.open( QIODevice::ReadOnly ) ) {
        stream.setDevice( &fichero );
        stream.setCodec("UTF-8");
        pos=0;
        while ( !stream.atEnd() )
        {
        	stream.readLine();
        	pos++;
       	}
       	//if(DEBUG) QMessageBox::warning(this, "Debug","Lineas: "+QString("%1").arg(pos));
       	ui.progressBar->setMaximum(pos);
       	ui.progressBar->setValue(0);
       	pos=0;
      } else return false;

  return true;

}

QString lacaixa::abrirFichero()
{
	QString dirtrabajo(dirtrabajodefecto());
  
  QFileDialog dialogofich(this);
  dialogofich.setFileMode(QFileDialog::ExistingFile);
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

  dialogofich.setFilter("*.txt");
  dialogofich.setDirectory(adapta(dirtrabajo));
  dialogofich.setWindowTitle(tr("SELECCIÓN DE ARCHIVO PARA IMPORTAR PASES AUTOMÁTICOS"));
  QStringList fileNames;
  if (dialogofich.exec())
     {
      fileNames = dialogofich.selectedFiles();
      if (fileNames.at(0).length()>0)
          {
           // QString cadfich=cadfich.fromLocal8Bit(fileNames.at(0));
           QString cadfich=fileNames.at(0);
           return cadfich;
          }
     }
  return "";
}

void lacaixa::pasaTabla()
{
	//if(DEBUG) QMessageBox::warning(this, "Debug","Fila: "+QString("%1").arg(fila));
	if(ui.lineImporte->text().contains("+") && ui.checkIngresos->isChecked())
	{
		t->pasadatos1(fila,ui.lineCuenta->text(),
    			ui.lineRemitente->text(),"",ui.lineImporte->text().replace("+",""),
    			"",ui.dateEdit->date(),"",ui.dateEdit->date().toString("yyyy-MM-dd"));
    	fila++;
   	}
    if(ui.lineImporte->text().contains("-") && ui.checkGastos->isChecked())
    {
    	t->pasadatos1(fila,ui.lineCuenta->text(),
       			ui.lineRemitente->text(),ui.lineImporte->text().replace("-",""),"",
       			"",ui.dateEdit->date(),"",ui.dateEdit->date().toString("yyyy-MM-dd"));
    	fila++;
   	}
}

void lacaixa::incorporar()
{
	if (ui.lineFound->text().length()>0 && ui.lineCuenta->text().length()>0
		&& ui.lineCuenta->text().length()==anchocuentas())
	{
		QString cuenta;
		bool in;
		if (!existeEquivalencia(ui.linePatron->text(),&cuenta,&in))
	     {
	      QString cadquery;
	      cadquery="INSERT INTO equivalenciasplan (cod,equiv,incorporar) VALUES ('";
	      cadquery+=ui.lineFound->text();
	      cadquery+="','";
	      cadquery+=ui.lineCuenta->text();
	      cadquery+="','1');";
	      ejecutarSQL(cadquery);
	     }
	    pasaTabla();
	    siguiente();
	}
}

void lacaixa::ignorar()
{
	if (ui.lineFound->text().length()>0)
	{
		QString cuenta;
		bool in;
		if (!existeEquivalencia(ui.linePatron->text(),&cuenta,&in))
	     {
	      QString cadquery;
	      cadquery="INSERT INTO equivalenciasplan (cod,equiv,incorporar) VALUES ('";
	      cadquery+=ui.lineFound->text();
	      cadquery+="','";
	      cadquery+=ui.lineCuenta->text();
	      cadquery+="','0');";
	      ejecutarSQL(cadquery);
	     }
	    siguiente();
	}
}

void lacaixa::siguiente()
{
	QString cuenta,linea,codigo,valor;
	bool incorporar = false;
	QDate fecha;
	t->incorporaEdicion();
	if (pos < ui.progressBar->maximum()){
	  	
		linea = stream.readLine(); // linea de texto excluyendo '\n'
        pos++;
        codigo=linea.section('\t',0,0);
        //if (codigo.length()==0) continue;
        ui.lineFound->setText(codigo);
        
        ui.linePatron->setText(codigo.left(codigo.length()*ui.sensibilidad->value()/ui.sensibilidad->maximum()));
        //qDebug() << linea.section('\t',2,2);
        fecha= QDate::fromString(linea.section('\t',2,2).replace(" ",""),"dd/MM/yyyy");
        //descripcion=linea.section('\t',1,1);
        ui.dateEdit->setDate(fecha);
        ui.lineRemitente->setText(linea.section('\t',3,3));
        valor = linea.section('\t',4,4).trimmed();
        valor.replace(" ","");
        //Parche para los miles
        valor.remove(".");
        ui.lineImporte->setText(valor);
        ui.progressBar->setValue(pos);
        ui.siguienteButton->setToolTip(tr("Siguiente"));
        ui.status->setText(tr("Procesando datos..."));
        if (existeEquivalencia(ui.linePatron->text(),&cuenta,&incorporar))
        {
        	ui.lineCuenta->setText(cuenta);
        	if (incorporar) pasaTabla();
			siguiente();
       	}
        else{
        	ui.status->setText(tr("Esperando respuesta..."));
        	ui.lineCuenta->setText("");
       	}
        
    }else{
    	ui.status->setText(tr("Fichero leído"));
    	fichero.close();
    	ui.siguienteButton->setEnabled(false);
    	ui.incorporarButton->setEnabled(false);
    	ui.ignorarButton->setEnabled(false);
    	QMessageBox::information( this, tr("DIARIO"),
                   tr("El archivo seleccionado se ha importado correctamente"));
        t->exec();
        t->~tabla_asientos();
   	}
}
//
