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

#include "periodos.h"
#include "basedatos.h"
#include "funciones.h"

periodos::periodos(QString qejercicio) : QDialog() {
    ui.setupUi(this);
 ejercicio=qejercicio;
 QString cadena=tr("PERÍODOS EJERCICIO ");
 cadena+=ejercicio;
 ui.label->setText(cadena);
 QStringList columnas;
 columnas << tr("NOMBRE") << tr("INICIO") << tr("FIN");
 ui.tableWidget->setHorizontalHeaderLabels(columnas);
 //ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
 //ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);


// cargamos datos de la tabla
cadena="select codigo,inicio,fin from periodos where ejercicio='";
cadena+=ejercicio;
cadena+="' order by inicio desc";

 QSqlQuery query(cadena);
 int veces=0;
 while ( query.next() )
    {
     ui.tableWidget->insertRow(veces);
     QTableWidgetItem *newItem = new QTableWidgetItem(query.value(0).toString());
     ui.tableWidget->setItem(veces,0,newItem);
     QDateTimeEdit  *fecha = new QDateTimeEdit();
     fecha->setDisplayFormat("dd.MM.yyyy");
     fecha->setDate(query.value(1).toDate());
     fecha->setCalendarPopup(TRUE);
     ui.tableWidget->setCellWidget(veces,1,fecha);
     QDateTimeEdit  *fecha2 = new QDateTimeEdit();
     fecha2->setDisplayFormat("dd.MM.yyyy");
     fecha2->setDate(query.value(2).toDate());
     fecha2->setCalendarPopup(TRUE);
     ui.tableWidget->setCellWidget(veces,2,fecha2);
     //connect((QDateTimeEdit*)ui.tableWidget->cellWidget(veces,2),
     //    SIGNAL(dateChanged(QDate)),this,SLOT(itemCambiado(QDate)));
    }

 connect(ui.mesespushButton,SIGNAL(clicked()),this,SLOT(asignameses()));
 connect(ui.aceptarpushButton,SIGNAL(clicked()),this,SLOT(grabar()));
 connect(ui.borratodopushButton,SIGNAL(clicked()),this,SLOT(borrartodo()));
 connect(ui.insertapushButton,SIGNAL(clicked()),this,SLOT(insertafila()));
 connect(ui.borrafilapushButton,SIGNAL(clicked()),this,SLOT(borrafila()));
 //connect(ui.tableWidget,SIGNAL( itemChanged (QTableWidgetItem *) ), this,
 //	SLOT(itemCambiado( QTableWidgetItem *)));
}

void periodos::itemCambiado( QDate fecha ){
	int fil = ui.tableWidget->currentRow();
	if (fil<0) return;
	int col = ui.tableWidget->currentColumn();
	if (col == 2){
		//fecha = QDate::fromString(cel->text(), "dd.MM.yyyy");
		if (fecha.isValid())
			((QDateTimeEdit*)ui.tableWidget->cellWidget(fil+1,1))->setDate(fecha.addDays(1));
	}
	//if (DEBUG) QMessageBox::warning(this, tr("Debug"), "Fecha: "+fecha.toString("dd.MM.yyyy"));
	return;	
}

void periodos::asignameses()
{
  
  QDate fechaini=inicioejercicio(ejercicio);
  for (int veces=0;veces<12;veces++)
     {
      ui.tableWidget->insertRow(veces);
      QTableWidgetItem *newItem = new QTableWidgetItem(cadmes(veces+1));
      ui.tableWidget->setItem(veces,0,newItem);
      QDateEdit  *fecha = new QDateEdit();
      fecha->setDisplayFormat("dd.MM.yyyy");
      fecha->setDate(fechaini.addMonths(veces));
      fecha->setCalendarPopup(TRUE);
      ui.tableWidget->setCellWidget(veces,1,fecha);
      QDateEdit  *fecha2 = new QDateEdit();
      fecha2->setDisplayFormat("dd.MM.yyyy");
      QDate fechafinmes=fechaini.addMonths(veces+1);
      fechafinmes=fechafinmes.addDays(-1);
      fecha2->setCalendarPopup(TRUE);
      fecha2->setDate(fechafinmes);
      ui.tableWidget->setCellWidget(veces,2,fecha2);
     }
}

void periodos::grabar()
{
 QString cadena="delete from periodos where ejercicio='";
 cadena+=ejercicio;
 cadena+="'";
 QSqlQuery query(cadena);

 for (int veces=0;veces<ui.tableWidget->rowCount(); veces++)
     {
      cadena="INSERT INTO periodos (ejercicio,codigo,inicio,fin) VALUES('";
      cadena+=ejercicio;
      cadena+="','";
      QString codigo;
      if (ui.tableWidget->item(veces,0)==NULL) continue;
      if (ui.tableWidget->item(veces,0)->text().length()==0) continue;
      codigo=ui.tableWidget->item(veces,0)->text();
      cadena+=codigo;
      cadena+="','";
      QDateEdit *fechaini=(QDateEdit*)ui.tableWidget->cellWidget(veces,1);
      QDateEdit *fechafin=(QDateEdit*)ui.tableWidget->cellWidget(veces,2);
      cadena+=fechaini->date().toString("yyyy.MM.dd");
      cadena+="','";
      cadena+=fechafin->date().toString("yyyy.MM.dd");
      cadena+="');";
      query.exec(cadena);
     }
 accept();
}

void periodos::borrartodo()
{
 ui.tableWidget->clearContents();
 ui.tableWidget->setRowCount(0);
}

void periodos::insertafila()
{
  if (ui.tableWidget->rowCount()>=15)
     {
      QMessageBox::warning( this, tr("Períodos"),
           tr("No se puede exceder el número de 15 períodos"));
     }
  int fila=ui.tableWidget->currentRow();
  ui.tableWidget->insertRow(fila);
  QTableWidgetItem *newItem = new QTableWidgetItem("");
  ui.tableWidget->setItem(fila,0,newItem);
  QDateEdit  *fecha = new QDateEdit();
  fecha->setDisplayFormat("dd.MM.yyyy");
  fecha->setDate(QDate::currentDate ());
  fecha->setCalendarPopup(TRUE);
  ui.tableWidget->setCellWidget(fila,1,fecha);
  QDateEdit  *fecha2 = new QDateEdit();
  fecha2->setDisplayFormat("dd.MM.yyyy");
  fecha2->setDate(QDate::currentDate ());
  fecha2->setCalendarPopup(TRUE);
  ui.tableWidget->setCellWidget(fila,2,fecha2);
}

void periodos::borrafila()
{
 int fila=ui.tableWidget->currentRow();
 if (fila>=0 && ui.tableWidget->rowCount()>fila)
    ui.tableWidget->removeRow(fila);
}
