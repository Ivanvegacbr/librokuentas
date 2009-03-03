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

#include "preferencias.h"
#include "funciones.h"

preferencias::preferencias() : QDialog() {
    ui.setupUi(this);
    connect(ui.filtrargroupBox,SIGNAL(toggled(bool)),this,SLOT(filtrarporcambiado()));
    connect(ui.personalizadogroupBox,SIGNAL(toggled(bool)),this,SLOT(filtrarinicambiado()));
    connect(ui.dirButton,SIGNAL(clicked()),SLOT(dirTrabajoPulsado()));
    connect(ui.visorButton,SIGNAL(clicked()),SLOT(visorPulsado()));
    connect(ui.imprimirButton,SIGNAL(clicked()),SLOT(imprPulsado()));
    connect(ui.navegadorButton,SIGNAL(clicked()),SLOT(navegadorPulsado()));
}

void preferencias::dirTrabajoPulsado()
{
	ui.directoriolineEdit->setText(selectDir(true,ui.directoriolineEdit->text()));
}

void preferencias::visorPulsado()
{
	ui.visorlineEdit->setText(selectDir(false,ui.visorlineEdit->text()));
}

void preferencias::imprPulsado()
{
	ui.imprimirlineEdit->setText(selectDir(false,ui.imprimirlineEdit->text()));
}

void preferencias::navegadorPulsado()
{
	ui.navegadorlineEdit->setText(selectDir(false,ui.navegadorlineEdit->text()));
}

void preferencias::filtrarporcambiado()
{
    if (ui.filtrargroupBox->isChecked())
	ui.personalizadogroupBox->setChecked(false);
}

void preferencias::filtrarinicambiado()
{
    if (ui.personalizadogroupBox->isChecked())
	ui.filtrargroupBox->setChecked(false);
}


void preferencias::pasadirtrabajo(QString directorio)
{
    ui.directoriolineEdit->setText(directorio);
}

void preferencias::pasavisordvi(QString visor)
{
    ui.visorlineEdit->setText(visor);
}

void preferencias::pasaaplicimprimir(QString aplic)
{
    ui.imprimirlineEdit->setText(aplic);
}

void preferencias::pasanavegador(QString navegador)
{
    ui.navegadorlineEdit->setText(navegador);
}

void preferencias::pasafiltropor(int filtro)
{
    if (filtro<1 || filtro>3) 
    {
     ui.filtrargroupBox->setChecked(false);
     return;
    }
    ui.filtrargroupBox->setChecked(true);
    if (filtro==EJERCICIOACTUAL) ui.ejercicioradioButton->setChecked(true);
    if (filtro==ULTIMOS30DIAS) ui.u30diasradioButton->setChecked(true);
    if (filtro==ULTIMOS30ASIENTOS) ui.u30asientosradioButton->setChecked(true);
}

void preferencias::pasaordenarpor(int orden)
{
    if (orden==FECHA) ui.fecharadioButton->setChecked(true);
    else ui.numradioButton->setChecked(true);
}

void preferencias::pasaestilonumerico(int estilo)
{
    if (estilo==COMADECIMAL) ui.comaradioButton->setChecked(true);
    else ui.puntoradioButton->setChecked(true);
}

void preferencias::pasasindecimales(bool sindecimales)
{
 ui.sindecimalescheckBox->setChecked(sindecimales);
}


void preferencias::pasafiltrodiariopersonalizado(QString filtro)
{
    if (filtro.length()>0)
    {
	ui.personalizadogroupBox->setChecked(true);
      ui.personalizadolineEdit->setText(filtro);
    }
    else
        ui.personalizadogroupBox->setChecked(false);
}

void preferencias::pasafiltrartex(bool filtrartext)
{
 ui.filtratexcheckBox->setChecked(filtrartext);
}

void preferencias::pasaidioma(int qidioma)
{
 if (qidioma==0) ui.espradioButton->setChecked(true);
 if (qidioma==1) ui.ingradioButton->setChecked(true);
 if (qidioma==2) ui.catradioButton->setChecked(true);
}

QString preferencias::dirtrabajo()
{
    return ui.directoriolineEdit->text();
}

QString preferencias::visordvi()
{
    return ui.visorlineEdit->text();
}

QString preferencias::aplicimprimir()
{
    return ui.imprimirlineEdit->text();
}

QString preferencias::navegador()
{
    return ui.navegadorlineEdit->text();
}

int preferencias::filtropor()
{
    if (!ui.filtrargroupBox->isChecked()) return NADA;
    if (ui.ejercicioradioButton->isChecked()) return EJERCICIOACTUAL;
    if (ui.u30diasradioButton->isChecked()) return ULTIMOS30DIAS;
    if (ui.u30asientosradioButton->isChecked()) return ULTIMOS30ASIENTOS;
    return NADA;
}

int preferencias::ordenarpor()
{
    if (ui.fecharadioButton->isChecked()) return FECHA;
    return ASIENTO;
}

int preferencias::estilonumerico()
{
    if (ui.comaradioButton->isChecked()) return COMADECIMAL;
    return PUNTODECIMAL;
}

bool preferencias::sindecimales()
{
 if (ui.sindecimalescheckBox->isChecked()) return true; 
 return false;
}

QString preferencias::filtrodiariopersonalizado()
{
    if (ui.personalizadogroupBox->isChecked())
      return ui.personalizadolineEdit->text();
    return "";
}

bool preferencias::esfiltrartex()
{
  return ui.filtratexcheckBox->isChecked();
}

int preferencias::qidioma()
{
 if (ui.ingradioButton->isChecked()) return 1;
 if (ui.catradioButton->isChecked()) return 2;
 return 0;
}

QString preferencias::selectDir(bool dir, QString dirIni)
{
	QString dirtrabajo(dirIni);
  
  QFileDialog dialogofich(this);
  if (dir) dialogofich.setFileMode(QFileDialog::DirectoryOnly);
  else dialogofich.setFileMode(QFileDialog::ExistingFile);
  dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
  dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
  dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
  dialogofich.setLabelText ( QFileDialog::Accept, tr("Aceptar") );
  dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );
  if (dir) dialogofich.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  //else dialogofich.setFilter(QDir::Readable);
  dialogofich.setDirectory(adapta(dirtrabajo));
  if (dir) dialogofich.setWindowTitle(tr("SELECCIÓN DIRECTORIO DE TRABAJO"));
  else dialogofich.setWindowTitle(tr("SELECCIONAR APLICACIÓN"));
  QDir dirName;
  QStringList fileNames;
  if (dialogofich.exec())
     {
      if (dir){
      	dirName = dialogofich.directory();
      	if (dirName.isReadable())
          {
           // QString cadfich=cadfich.fromLocal8Bit(fileNames.at(0));
           return dirName.absolutePath();
          }
      }else{
      	fileNames = dialogofich.selectedFiles();
	      if (fileNames.at(0).length()>0)
          {
           // QString cadfich=cadfich.fromLocal8Bit(fileNames.at(0));
           return fileNames.at(0);
          }
     	}
     }
  return dirIni;
}
