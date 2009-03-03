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

#include "buscasubcuenta.h"
#include "funciones.h"
#include "basedatos.h"
#include <QSqlDatabase>
#include <QSqlRecord>

buscasubcuenta::buscasubcuenta(QString tituloini) : QDialog() {
    ui.setupUi(this);
     QSqlTableModel *modelo = new QSqlTableModel;
     modelo->setTable("plancontable");
     QString cadena="char_length(codigo)=";
     QString cadnum;
     cadnum.setNum(anchocuentas());
     cadena+=cadnum;
     modelo->setFilter(cadena);
     if (tituloini.length()>0 && !cadnumvalido(tituloini))
         {
          ui.TituloLineEdit->setText(tituloini);
          cadena+=" and position(upper('";
          cadena+=ui.TituloLineEdit->text();
          cadena+="') in upper(descripcion))=1";
          modelo->setFilter(cadena);
         }
         else{
         	ui.SubcuentaLineEdit->setText(tituloini);
          	cadena+=" and position('";
          	cadena+=ui.SubcuentaLineEdit->text();
          	cadena+="' in codigo)=1";
          	modelo->setFilter(cadena);
         }
     modelo->setSort(0,Qt::AscendingOrder);
     modelo->select();
     modelo->setHeaderData(0, Qt::Horizontal, tr("CÓDIGO"));
     modelo->setHeaderData(1, Qt::Horizontal, tr("CUENTA"));
     modeloplan=modelo;
     ui.tableView->setModel(modelo);
     ui.tableView->setColumnWidth(0,100);
     ui.tableView->setColumnWidth(1,300);
     ui.tableView->setEditTriggers ( QAbstractItemView::NoEditTriggers );
     ui.tableView->hideColumn(2);
	 
     ui.tableView->show();
     //ui.TituloLineEdit->setText(modelo->filter());
    connect(ui.ComienceRadioButton,SIGNAL(toggled(bool)),this,SLOT(ComienceRadioBotoncambiado()));
    connect(ui.ContengaRadioButton,SIGNAL(toggled(bool)),this,SLOT(ContengaRadioBotoncambiado()));
    connect(ui.SubcuentaLineEdit,SIGNAL(textChanged(QString)),this,SLOT(codigosubcuentacambiado()));
    connect(ui.TituloLineEdit,SIGNAL(textChanged(QString)),this,SLOT(titulocuentacambiado()));
    connect(ui.SubcuentaLineEdit,SIGNAL(editingFinished ()),this,SLOT(fuerafocosubcuenta()));
    connect(ui.tableView,SIGNAL( clicked ( QModelIndex )),this,SLOT(accept()));


}


buscasubcuenta::~buscasubcuenta()
{
  ui.tableView->~QTableView ();
  modeloplan->~QSqlTableModel ();
}

void buscasubcuenta::ComienceRadioBotoncambiado()
{
 if (ui.SubcuentaLineEdit->text().length()>0) codigosubcuentacambiado();
 if (ui.TituloLineEdit->text().length()>0) titulocuentacambiado();
}


void buscasubcuenta::ContengaRadioBotoncambiado()
{
 if (ui.SubcuentaLineEdit->text().length()>0) codigosubcuentacambiado();
 if (ui.TituloLineEdit->text().length()>0) titulocuentacambiado();
}


void buscasubcuenta::codigosubcuentacambiado()
{
  if (ui.TituloLineEdit->text().length()>0) 
    {
      QString guardacadena=ui.SubcuentaLineEdit->text();
      ui.TituloLineEdit->setText("");
      ui.SubcuentaLineEdit->setText(guardacadena);
     }
  QString cadena="char_length(codigo)=";
  QString cadnum;
  cadnum.setNum(anchocuentas());
  cadena+=cadnum;
  // si vacio fijar filtro inicial 
  if (ui.SubcuentaLineEdit->text().length()==0)
     {
        modeloplan->setFilter(cadena);
        // PlanDataTable->refresh();
        return;
     }
  if (ui.ComienceRadioButton->isChecked())
      {
        cadena+=" and position('";
        cadena+=ui.SubcuentaLineEdit->text();
        cadena+="' in codigo)=1";
        modeloplan->setFilter(cadena);
        // PlanDataTable->refresh();
      }
    else
       {
         cadena+=" and position('";
         cadena+=ui.SubcuentaLineEdit->text();
         cadena+="' in codigo)>0";
         modeloplan->setFilter(cadena);
         // PlanDataTable->refresh();
     }
}



void buscasubcuenta::titulocuentacambiado()
{
    if (ui.SubcuentaLineEdit->text().length()>0)
       {
        QString guardacadena=ui.TituloLineEdit->text();
        ui.SubcuentaLineEdit->setText("");
        ui.TituloLineEdit->setText(guardacadena);
       }
  QString cadena="char_length(codigo)=";
  QString cadnum;
  cadnum.setNum(anchocuentas());
  cadena+=cadnum;
  // si vacio fijar filtro inicial 
  if (ui.TituloLineEdit->text().length()==0)
     {
        modeloplan->setFilter(cadena);
        // PlanDataTable->refresh();
        return;
     }
  if (ui.ComienceRadioButton->isChecked())
      {
        cadena+=" and position(upper('";
        cadena+=ui.TituloLineEdit->text();
        cadena+="') in upper(descripcion))=1";
        modeloplan->setFilter(cadena);
        // PlanDataTable->refresh();
      }
    else
       {
         cadena+=" and position(upper('";
         cadena+=ui.TituloLineEdit->text();
         cadena+="') in upper(descripcion))>0";
         modeloplan->setFilter(cadena);
         // PlanDataTable->refresh();
     }

}


QString buscasubcuenta::seleccioncuenta( void )
{
 if (ui.SubcuentaLineEdit->text().length()==anchocuentas())
    {
     if (existesubcuenta(ui.SubcuentaLineEdit->text()))
         return ui.SubcuentaLineEdit->text();
     else return "";
    }
// if (modeloplan->rowCount()>0)
//    {
     QModelIndex indiceactual=ui.tableView->currentIndex();
     if (indiceactual.isValid())
        return modeloplan->record(indiceactual.row()).value("codigo").toString();
      else if (modeloplan->rowCount()>0)
                return modeloplan->record(0).value("codigo").toString();
//    }
return "";
}



void buscasubcuenta::fuerafocosubcuenta()
{
  QString codigo=ui.SubcuentaLineEdit->text();
  codigo=expandepunto(codigo,anchocuentas());
  ui.SubcuentaLineEdit->setText(codigo);
}


void buscasubcuenta::cambiatitulo(QString titulo)
{
  setWindowTitle(titulo);
}
