/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

    Copyright (C) José Manuel Díez Botella

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

#include "editapaseconci.h"
#include "funciones.h"
#include "basedatos.h"
#include "pidenombre.h"

editapaseconci::editapaseconci() : QDialog() {
    ui.setupUi(this);
 comadecimal=haycomadecimal();
 connect(ui.debelineEdit,SIGNAL(textChanged(QString)),this,SLOT(debecambiado()));
 connect(ui.haberlineEdit,SIGNAL(textChanged(QString)),this,SLOT(habercambiado()));
 connect(ui.aceptarpushButton,SIGNAL(clicked()),this,SLOT(botonaceptar()));

}


void editapaseconci::pasadatos(QString numpase,QDate fecha,QString descripcion, QString debe, QString haber)
{
 ui.haberlineEdit->disconnect(SIGNAL(textChanged(QString)));
 ui.debelineEdit->disconnect(SIGNAL(textChanged(QString)));
//ui.fechadateEdit->setDateRange(inicioejercicio(ejerciciodelafecha(fecha)),finejercicio(ejerciciodelafecha(fecha)));
 pase = numpase;
 claveiva = claveIva(pase);
 if (claveiva.length() > 0){
 	ui.ivaCheck->setCheckState(Qt::Checked);
 	ui.ivaCheck->setText(tr("IVA %1 incluído").arg(claveiva));
 }else{
 	ui.ivaCheck->setCheckState(Qt::Unchecked);
 	ui.ivaCheck->setEnabled(false);
 	ui.ivaCheck->setText(tr("IVA NO incluído"));
 }
ui.fechadateEdit->setDate(fecha);
ui.descripcionlineEdit->setText(descripcion);
if (debe.toDouble()>0.001 || debe.toDouble()<-0.001) ui.debelineEdit->setText(debe);
if (haber.toDouble()>0.001 || haber.toDouble()<-0.001) ui.haberlineEdit->setText(haber);

 connect(ui.debelineEdit,SIGNAL(textChanged(QString)),this,SLOT(debecambiado()));
 connect(ui.haberlineEdit,SIGNAL(textChanged(QString)),this,SLOT(habercambiado()));

}

/*void editapaseconci::recuperadatos(QDate *fecha,QString *descripcion, QString *debe, QString *haber)
{
 *fecha=ui.fechadateEdit->date();
 *descripcion=ui.descripcionlineEdit->text();
 *debe=ui.debelineEdit->text();
 *haber=ui.haberlineEdit->text();
}
*/

void editapaseconci::debecambiado()
{
 if (comadecimal) 
   if (ui.debelineEdit->text().contains('.'))
      ui.debelineEdit->setText(ui.debelineEdit->text().replace('.',','));
 ui.haberlineEdit->disconnect(SIGNAL(textChanged(QString)));
 ui.haberlineEdit->clear();
 connect(ui.haberlineEdit,SIGNAL(textChanged(QString)),this,SLOT(habercambiado()));
 
}


void editapaseconci::habercambiado()
{
 if (comadecimal)
  if (ui.haberlineEdit->text().contains('.'))
     ui.haberlineEdit->setText(ui.haberlineEdit->text().replace('.',','));
 ui.debelineEdit->disconnect(SIGNAL(textChanged(QString)));
 ui.debelineEdit->clear();
 connect(ui.debelineEdit,SIGNAL(textChanged(QString)),this,SLOT(debecambiado()));
}

void editapaseconci::botonaceptar()
{
 if (fechadejerciciocerrado(ui.fechadateEdit->date()))
 {
 	QMessageBox::warning( this, tr("Editar apunte"),
 	tr("ERROR: La fecha %1 del pase %1 corresponde a un ejercicio cerrado").arg(ui.fechadateEdit->text(),pase));
 	return;
 }
 if (!fechacorrespondeaejercicio(ui.fechadateEdit->date()))
 {
 	QMessageBox::warning( this, tr("Editar apunte"),
 	tr("ERROR: La fecha %1 del pase %1 no corresponde a ningún ejercicio definido").arg(ui.fechadateEdit->text(),pase));
 	return;
 }
 
 int correcto = recalcularIvas();
 
 if (correcto){
 	updateDiarioFDHwP(ui.fechadateEdit->date(),ui.debelineEdit->text(),ui.haberlineEdit->text(),pase);
 	QMessageBox::information( this, tr("Editar apunte"),
		     tr("Operación realizada correctamente"));
	accept();
 }else{
 	QMessageBox::critical( this, tr("Editar apunte"),
		     tr("Se ha producido un error al calcular el IVA"));
  }
}

void editapaseconci::updateDiarioFDHwP (QDate fecha, QString debe, QString haber, QString pase)
{
	if (!cadnumvalido(pase)) return;
	QString cadena = "update diario set fecha='";
    cadena += fecha.toString("yyyy-MM-dd");
    cadena += "', debe='";
    cadena += convapunto(debe.left(-1).replace("'","''"));
    cadena += "', haber='";
    cadena += convapunto(haber.left(-1).replace("'","''"));
    cadena += "' where pase=";
    cadena += pase.left(-1).replace("'","''");
    ejecutarSQL(cadena);
}

void editapaseconci::updateLibroivaFBCwP (QDate fecha, QString base, QString cuota, QString pase)
{
	if (!cadnumvalido(pase)) return;
	QString cadena = "update libroiva set fecha_fra='";
    cadena += fecha.toString("yyyy-MM-dd");
    cadena += "', base_iva='";
    cadena += convapunto(base.left(-1).replace("'","''"));
    cadena += "', cuota_iva='";
    cadena += convapunto(cuota.left(-1).replace("'","''"));
    cadena += "' where pase=";
    cadena += pase.left(-1).replace("'","''");
    ejecutarSQL(cadena);
}

int editapaseconci::recalcularIvas()
{
	//QString clave = claveIva(pase);
	double ivaEfect, ivaNore, bruto, base;
	bruto = ui.haberlineEdit->text().toDouble() + ui.debelineEdit->text().toDouble();
	if (ui.ivaCheck->isChecked())
	{
		if (claveiva == iva_mixto()){
			pidenombre *iva = new pidenombre();
			iva->asignanombreventana(tr("Introducir valor"));
			iva->asignaetiqueta(tr("Cuota IVA:"));
			int resultado = iva->exec();
	   		civa = calculaValor( iva->contenido() );
	   		if (!resultado==QDialog::Accepted) return 0;
	   		if (civa <= 0){
	   			QMessageBox::critical(this,tr("Editar apunte"),
	   						tr("ERROR: Debe introducir un valor u operación correctos"));
	   			return 0;
	  		}
			iva->asignaetiqueta(tr("Cuota RE:"));
			resultado = iva->exec();
	   		cre = calculaValor( iva->contenido() );
	   		if (!resultado==QDialog::Accepted) return 0;
	   		if (cre <= 0 || cre == civa){
	   			QMessageBox::warning(this,tr("Editar apunte"),
	   						tr("El valor del RE se establecerá en zero (0.00)"));
	   			cre = 0.0;
	  		}
			//return;
		}else{
			ivaEfect = tipoivaefectivo(claveiva);
			ivaNore = tipoivanore(claveiva);
			cre = (ivaEfect - ivaNore)*(bruto/(ivaEfect+1.00));
			civa = (bruto/(ivaEfect+1.00))*ivaNore;
		}
	}else{
		if (claveiva.length() > 0)
		{
			QString cad = "delete from libroiva where pase ='";
			cad+=pase;
			cad+="';";
			ejecutarSQL(cad);
		}
		return 1;
	}
	if (bruto >= 0)
		base = bruto-civa-cre;
	else
		base = bruto+civa+cre;
	
	updateLibroivaFBCwP(ui.fechadateEdit->date(),QString("%1f2").arg(base),QString("%1f2").arg(civa),pase);
	return 1;
}
