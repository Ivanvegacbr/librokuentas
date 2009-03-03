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

#include "editconfig.h"


editconfig::editconfig() : QDialog()
 {
    ui.setupUi(this);
    QString cadena="select empresa, nif, domicilio, poblacion, cpostal, provincia, email, web, "
                                 "anchocuentas, cuenta_iva_soportado, cuenta_iva_repercutido, "
                                 "cuenta_ret_irpf,"
                                 "cuentasapagar, cuentasacobrar, clave_iva_defecto, clave_gastos, "
		 "clave_ingresos, cuenta_pyg, prox_asiento, prox_pase,prox_vencimiento, "
		 "numrel, igic, analitica,id_registral "
                                 "from configuracion;";
  QSqlQuery query(cadena);
  
  if (query.next())
     {
       ui.empresalineEdit->setText(query.value(0).toString());
       ui.niflineEdit->setText(query.value(1).toString());
       ui.domiciliolineEdit->setText(query.value(2).toString());
       ui.poblacionlineEdit->setText(query.value(3).toString());
       ui.cplineEdit->setText(query.value(4).toString());
       ui.provincialineEdit->setText(query.value(5).toString());
       ui.emaillineEdit->setText(query.value(6).toString());
       ui.weblineEdit->setText(query.value(7).toString());
       ui.anchocuentaslineEdit->setText(query.value(8).toString());
       ui.ivasoplineEdit->setText(query.value(9).toString());
       ui.ivareplineEdit->setText(query.value(10).toString());
       ui.ctaretlineEdit->setText(query.value(11).toString());
       ui.pagarlineEdit->setText(query.value(12).toString());
       ui.cobrarlineEdit->setText(query.value(13).toString());
       ui.claveivalineEdit->setText(query.value(14).toString());
       ui.clavegastoslineEdit->setText(query.value(15).toString());
       ui.claveingresoslineEdit->setText(query.value(16).toString());
       ui.pyglineEdit->setText(query.value(17).toString());
       ui.proxasientolineEdit->setText(query.value(18).toString());
       ui.proxpaselineEdit->setText(query.value(19).toString());
       ui.proxvencilineEdit->setText(query.value(20).toString());
       ui.numeracioncheckBox->setChecked(query.value(21).toBool());
       ui.igiccheckBox->setChecked(query.value(22).toBool());
       ui.analiticacheckBox->setChecked(query.value(23).toBool());
       ui.idlineEdit->setText(query.value(24).toString());
     }
  connect(ui.aceptarpushButton,SIGNAL(clicked()),this,SLOT(aceptar()));
  connect(ui.igiccheckBox,SIGNAL(stateChanged(int)),SLOT(igiccambiado()));
  igiccambiado();
}

void editconfig::aceptar()
{
   QString cadena="update configuracion set ";
   cadena+="empresa='";
   cadena+=ui.empresalineEdit->text().replace("'","''");
   cadena+="',nif='";
   cadena+=ui.niflineEdit->text().replace("'","''");
   cadena+="',domicilio='";
   cadena+=ui.domiciliolineEdit->text().replace("'","''");
   cadena+="',poblacion='";
   cadena+=ui.poblacionlineEdit->text().replace("'","''");
   cadena+="',cpostal='";
   cadena+=ui.cplineEdit->text().replace("'","''");
   cadena+="',provincia='";
   cadena+=ui.provincialineEdit->text().replace("'","''");
   cadena+="',email='";
   cadena+=ui.emaillineEdit->text().replace("'","''");
   cadena+="',web='";
   cadena+=ui.weblineEdit->text().replace("'","''");
   cadena+="',cuenta_iva_soportado='";
   cadena+=ui.ivasoplineEdit->text().replace("'","''").trimmed();
   cadena+="',cuenta_iva_repercutido='";
   cadena+=ui.ivareplineEdit->text().replace("'","''").trimmed();
   cadena+="',cuenta_ret_irpf='";
   cadena+=ui.ctaretlineEdit->text().replace("'","''").trimmed();
   cadena+="',cuentasapagar='";
   cadena+=ui.pagarlineEdit->text().replace("'","''");
   cadena+="',cuentasacobrar='";
   cadena+=ui.cobrarlineEdit->text().replace("'","''");
   cadena+="',clave_iva_defecto='";
   cadena+=ui.claveivalineEdit->text().replace("'","''");
   cadena+="',clave_gastos='";
   cadena+=ui.clavegastoslineEdit->text().replace("'","''");
   cadena+="',clave_ingresos='";
   cadena+=ui.claveingresoslineEdit->text().replace("'","''");
   cadena+="',cuenta_pyg='";
   cadena+=ui.pyglineEdit->text().replace("'","''").trimmed();
   cadena+="',prox_asiento=";
   cadena+=ui.proxasientolineEdit->text().replace("'","''");
   cadena+=",prox_pase=";
   cadena+=ui.proxpaselineEdit->text().replace("'","''");
   cadena+=",prox_vencimiento=";
   cadena+=ui.proxvencilineEdit->text().replace("'","''");
   cadena+=",numrel=";
   if (ui.numeracioncheckBox->isChecked()) cadena+="TRUE"; else cadena+="FALSE";
   cadena+=",igic=";
   if (ui.igiccheckBox->isChecked()) cadena+="TRUE"; else cadena+="FALSE";
   cadena+=",analitica=";
   if (ui.analiticacheckBox->isChecked()) cadena+="TRUE"; else cadena+="FALSE";
   cadena+=",id_registral='";
   cadena+=ui.idlineEdit->text();
   cadena+="'";
   QSqlQuery query(cadena);
   accept();
}


void editconfig::igiccambiado()
{
  if (ui.igiccheckBox->isChecked())
    {
     ui.labelCuenta_iva_soportado->setText(tr("Cuenta IGIC soportado"));
     ui.labelCuenta_iva_repercutido->setText(tr("Cuenta IGIC repercutido"));
     ui.labelClave_iva_defecto->setText(tr("Clave IGIC defecto"));
    }
  else
           {
            ui.labelCuenta_iva_soportado->setText(tr("Cuenta IVA soportado"));
            ui.labelCuenta_iva_repercutido->setText(tr("Cuenta IVA repercutido"));
            ui.labelClave_iva_defecto->setText(tr("Clave IVA defecto"));
           }
}
