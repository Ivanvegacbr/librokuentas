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
 connect(ui.ivaSelect,SIGNAL(ivaActivado(QString)),this,SLOT(recalcularIvas()));

}


void editapaseconci::pasadatos(QString numpase,QDate fecha,QString descripcion, QString debe, QString haber)
{
 ui.haberlineEdit->disconnect(SIGNAL(textChanged(QString)));
 ui.debelineEdit->disconnect(SIGNAL(textChanged(QString)));
 ui.ivaSelect->disconnect(SIGNAL(ivaActivado(QString)));
//ui.fechadateEdit->setDateRange(inicioejercicio(ejerciciodelafecha(fecha)),finejercicio(ejerciciodelafecha(fecha)));
 pase = numpase;

 if (debe.toDouble()>0.001 || debe.toDouble()<-0.001) ui.debelineEdit->setText(debe);
 if (haber.toDouble()>0.001 || haber.toDouble()<-0.001) ui.haberlineEdit->setText(haber);
 double val;
 val=debe.toDouble()+haber.toDouble();
 claveiva = claveIva(pase);
 if (claveiva.length() > 0){
    ui.ivaSelect->setIndice(claveiva);

    QString cons = "SELECT base_iva,cuota_iva from libroiva where pase=";
    cons+=pase;
    cons+=";";
    QSqlQuery q = ejecutarSQL(cons);
    if(q.isActive() && q.next())
    {
        base = q.value(0).toDouble();
        civa = q.value(1).toDouble();
    }
    //ui.ivaSelect->calcularIvas(ui.ivaSelect->texto(),&val,&bas,&civa,false);

    ui.ivaLabel->setText(QString::number(civa,'f',2));
    cre=val-base-civa;
    ui.reLabel->setText(QString::number(cre,'f',2));
 }else{
    ui.ivaSelect->setIndice(diario_no_asignado());
    ui.ivaLabel->setText("0.00");
    ui.reLabel->setText("0.00");
 }

ui.fechadateEdit->setDate(fecha);
ui.descripcionlineEdit->setText(descripcion);
correcto = true;
 connect(ui.debelineEdit,SIGNAL(textChanged(QString)),this,SLOT(debecambiado()));
 connect(ui.haberlineEdit,SIGNAL(textChanged(QString)),this,SLOT(habercambiado()));
 connect(ui.ivaSelect,SIGNAL(ivaActivado(QString)),this,SLOT(recalcularIvas()));

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
 correcto = recalcularIvas();
 ui.haberlineEdit->disconnect(SIGNAL(textChanged(QString)));
 ui.haberlineEdit->clear();
 connect(ui.haberlineEdit,SIGNAL(textChanged(QString)),this,SLOT(habercambiado()));
 
}


void editapaseconci::habercambiado()
{
 if (comadecimal)
  if (ui.haberlineEdit->text().contains('.'))
     ui.haberlineEdit->setText(ui.haberlineEdit->text().replace('.',','));
 correcto = recalcularIvas();
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
 
 //int correcto = recalcularIvas();
 
 if (correcto){
     QString cad;
     updateDiarioFDHwP(ui.fechadateEdit->date(),ui.debelineEdit->text(),ui.haberlineEdit->text(),pase);

    if(paseLibroiva(pase)){

        if(ui.ivaSelect->texto() != diario_no_asignado()){
            updateLibroivaFBCwP(ui.fechadateEdit->date(),QString::number(base,'f',2), ui.ivaLabel->text(),pase);
        }else{
            cad = "delete from libroiva where pase ='";
            cad+=pase;
            cad+="';";
            ejecutarSQL(cad);
        }
    }else{

        if(ui.ivaSelect->texto() != diario_no_asignado()){
            cad="INSERT INTO libroiva (pase,cta_base_iva,base_iva,clave_iva,tipo_iva,tipo_re,";
            cad+="cuota_iva,cuenta_fra,fecha_fra,soportado,aib,eib) VALUES(";
            cad+=pase;
            cad+=",'";
            cad+="',";
            cad+=QString::number(base,'f',2); // base_iva
            cad+=",'";
            cad+=claveiva; // clave_iva
            cad+="',";
            double tiva = tipoivanore(claveiva) * 100;
            double tre = tipoivaefectivo(claveiva) * 100 - tiva;
            cad+=QString::number(tiva,'f',2); // tipo_iva
            cad+=",";
            cad+=QString::number(tre,'f',2); // tipo_re
            cad+=",";
            cad+=ui.ivaLabel->text(); // cuota_iva
            cad+=",'";
            cad+=ui.descripcionlineEdit->text(); // cuenta_fra
            cad+="','";
            cad+=ui.fechadateEdit->date().toString("yyyy/MM/dd");
            cad+="',";
            cad+="TRUE";
            cad+=",";
            cad+="FALSE,";
            cad+="FALSE);";
            ejecutarSQL(cad);
        }
    }
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
    double tiva = tipoivanore(claveiva) * 100;
    double tre = tipoivaefectivo(claveiva) * 100 - tiva;
    if (tre<0.001) tre = 0.00;
    QString cadena = "update libroiva set fecha_fra='";
    cadena += fecha.toString("yyyy-MM-dd");
    cadena += "', clave_iva='";
    cadena += claveiva.left(-1).replace("'","''");
    cadena += "', tipo_iva='";
    cadena += QString::number(tiva,'f',2);
    cadena += "', tipo_re='";
    cadena += QString::number(tre,'f',2);
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
        double bruto;
	bruto = ui.haberlineEdit->text().toDouble() + ui.debelineEdit->text().toDouble();
        if (ui.ivaSelect->texto() != diario_no_asignado())
	{

            correcto = ui.ivaSelect->calcularIvas(&claveiva,&bruto,&base,&civa,false);
            ui.ivaLabel->setText(QString::number(civa,'f',2));
            cre=bruto-base-civa;
            ui.reLabel->setText(QString::number(cre,'f',2));
            return 1;

	}else{
            base = bruto;
            ui.ivaLabel->setText("0.00");
            ui.reLabel->setText("0.00");
            return 1;
	}
        return 0;
}
