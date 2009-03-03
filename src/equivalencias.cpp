#include "equivalencias.h"
#include <QSqlDatabase>
#include <QSqlRecord>

#include "basedatos.h"
#include "funciones.h"
#include "buscasubcuenta.h"

equivalencias::equivalencias(  ) 
	: QDialog()
{
	ui.setupUi(this);
    ui.cuentaLineEdit->setFocus();
     QSqlTableModel *modelo = new QSqlTableModel;
     modelo->setTable("equivalenciasplan");
     modelo->setSort(0,Qt::AscendingOrder);
     modelo->select();
     modelo->setHeaderData(0, Qt::Horizontal, tr("EQUIVALENCIA"));
     modelo->setHeaderData(1, Qt::Horizontal, tr("CUENTA"));
     modelo->setHeaderData(2, Qt::Horizontal, tr("INCORP."));
     modeloEquiv=modelo;
     ui.tabla->setModel(modelo);
     ui.tabla->setColumnWidth(0,200);
     ui.tabla->setColumnWidth(1,80);
     ui.tabla->setColumnWidth(2,60);
     ui.tabla->setEditTriggers ( QAbstractItemView::NoEditTriggers );

     ui.tabla->show();

     connect(ui.buscapushButton,SIGNAL(clicked()),SLOT(botonsubcuentapulsado()));
     connect(ui.cuentaLineEdit,SIGNAL(returnPressed()),this,SLOT(finedicsubcuenta()));
     connect(ui.cuentaLineEdit,SIGNAL(textChanged(QString)),this,SLOT(subcuentacambiada()));
     connect(ui.checkBox,SIGNAL(stateChanged(int)),this,SLOT(incorporarCambiado(int)));
     connect(ui.BotonGuardar,SIGNAL(clicked()),this,SLOT(botonguardarpulsado()));
     connect(ui.BotonCancelar,SIGNAL(clicked()),this,SLOT(botoncancelarpulsado()));
     connect(ui.BotonEliminar,SIGNAL(clicked()),this,SLOT(botoneliminarpulsado()));
     connect(ui.tabla,SIGNAL( clicked ( QModelIndex )),this,SLOT(tablapulsada()));
}

equivalencias::~equivalencias()
{
  ui.tabla->~QTableView ();
  modeloEquiv->~QSqlTableModel ();
}

void equivalencias::tablapulsada()
{
     ui.cuentaLineEdit->disconnect(SIGNAL(textChanged(QString)));
     ui.checkBox->disconnect(SIGNAL(stateChanged(int)));
     ui.BotonGuardar->setDisabled(TRUE);
     QModelIndex indiceactual=ui.tabla->currentIndex();
     if (indiceactual.isValid())
       {
        ui.cuentaLineEdit->setText(modeloEquiv->record(indiceactual.row()).value("equiv").toString());
        ui.DescripcionLineEdit->setText(modeloEquiv->record(indiceactual.row()).value("cod").toString());
        if (modeloEquiv->record(indiceactual.row()).value("incorporar").toInt())
        	ui.checkBox->setCheckState(Qt::Checked);
        else
        	ui.checkBox->setCheckState(Qt::Unchecked);
        ui.BotonCancelar->setEnabled(TRUE);
        ui.BotonEliminar->setEnabled(TRUE);
        ui.DescripcionLineEdit->setEnabled(TRUE);
        ui.DescripcionLineEdit->setFocus();
        //ui.CodigoLineEdit->setReadOnly(TRUE);
       }
    connect(ui.cuentaLineEdit,SIGNAL(textChanged(QString)),this,SLOT(subcuentacambiada()));
    connect(ui.checkBox,SIGNAL(stateChanged(int)),this,SLOT(incorporarCambiado(int)));
}

void equivalencias::botonsubcuentapulsado()
{
    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.cuentaLineEdit->text());
    int cod=labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();
    if (cod==QDialog::Accepted && existesubcuenta(cadena2))
      ui.cuentaLineEdit->setText(cadena2);
       else ui.cuentaLineEdit->setText("");
    delete labusqueda;

}

void equivalencias::botonguardarpulsado()
{
  QString cadCod;
  bool incorp,si;
  if (ui.checkBox->checkState() == Qt::Checked)
	si = true;
  else
	si = false;
  if  (existeEquivalencia(ui.DescripcionLineEdit->text(),&cadCod,&incorp))
	guardaEquivalencia(ui.DescripcionLineEdit->text(),ui.cuentaLineEdit->text(),si);
  else 
	insertaEquivalencia(ui.DescripcionLineEdit->text(),ui.cuentaLineEdit->text(),si);       
  ui.cuentaLineEdit->clear();
  ui.cuentaLineEdit->setReadOnly(FALSE);
  ui.cuentaLineEdit->setFocus();
  ui.DescripcionLineEdit->clear();
  ui.DescripcionLineEdit->setEnabled(TRUE);
  ui.BotonGuardar->setDisabled(TRUE);
  ui.BotonCancelar->setDisabled(TRUE);
  ui.BotonEliminar->setDisabled(TRUE);
  modeloEquiv->select();
}


void equivalencias::botoncancelarpulsado()
{
     ui.cuentaLineEdit->clear();
     ui.cuentaLineEdit->setReadOnly(FALSE);
     ui.cuentaLineEdit->setFocus();
     ui.DescripcionLineEdit->clear();
     ui.DescripcionLineEdit->setDisabled(TRUE);
     ui.BotonGuardar->setDisabled(TRUE);
     ui.BotonCancelar->setDisabled(TRUE);
     ui.BotonEliminar->setDisabled(TRUE);
}


void equivalencias::botoneliminarpulsado()
{
     eliminaEquivalencia(ui.DescripcionLineEdit->text());
     modeloEquiv->select();
     ui.cuentaLineEdit->clear();
     ui.cuentaLineEdit->setReadOnly(FALSE);
     ui.cuentaLineEdit->setFocus();
     ui.DescripcionLineEdit->clear();
     ui.DescripcionLineEdit->setDisabled(TRUE);
     ui.BotonGuardar->setDisabled(TRUE);
     ui.BotonCancelar->setDisabled(TRUE);
     ui.BotonEliminar->setDisabled(TRUE);
}

void equivalencias::ctaexpandepunto()
{
  ui.cuentaLineEdit->setText(expandepunto(ui.cuentaLineEdit->text(),anchocuentas()));
}

void equivalencias::finedicsubcuenta()
{
 ctaexpandepunto();
 if (ui.cuentaLineEdit->text().length()<anchocuentas()) botonsubcuentapulsado();
}

void equivalencias::subcuentacambiada()
{
  if (existesubcuenta(ui.cuentaLineEdit->text()))
      ui.BotonGuardar->setEnabled(TRUE);
      //modeloEquiv->select();
}

void equivalencias::incorporarCambiado(int incorp)
{
	if(incorp) ui.checkBox->setText(tr("Incorporar"));
	else ui.checkBox->setText(tr("Ignorar"));
	if(incorp && ui.cuentaLineEdit->text().length()<anchocuentas())
		finedicsubcuenta();
	if(!incorp)
		ui.cuentaLineEdit->clear();
	ui.BotonGuardar->setEnabled(TRUE);
}
//
