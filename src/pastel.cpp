#include <QtGui>
#include "pastel.h"
#include "pieview.h"
#include "funciones.h"
//
pastel::pastel(int tamany , bool concomadecimal, bool condecimales ) 
	: QDialog()
{
	QGridLayout *gridLayout;
    gridLayout = new QGridLayout(this);
    comadecimal=concomadecimal;
	decimales=condecimales;
	id = 0;
	setupModel();
	QSplitter *splitter = new QSplitter;
    QTableView *table = new QTableView;
    pieChart = new PieView(this,tamany);
	splitter->addWidget(table);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    table->setModel(model);
    pieChart->setModel(model);

	QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
	table->setSelectionModel(selectionModel);
	pieChart->setSelectionModel(selectionModel);
	//QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	//pieChart->setSizePolicy(sizePolicy);
	gridLayout->addWidget(splitter);
	resize(tamany*2, tamany);
	
}
//
void pastel::setupModel()
{
     model = new QStandardItemModel(0, 2, this);
     model->setHeaderData(0, Qt::Horizontal, tr("Nombre"));
     model->setHeaderData(1, Qt::Horizontal, tr("Cantidad"));
}

int pastel::addPorcion( QColor color, QString nombre, double valor)
{
	//QMessageBox::warning(this,"ID",tr("%1").arg(id));
	if(id > PORCIONES) return 1;//controlamos el máximo de porciones
	if(!color.isValid()) color = randomColor(false);
    QString cant = formateanumero(valor,comadecimal,decimales);
    model->insertRows(id, 1, QModelIndex());
	model->setData(model->index(id, 0, QModelIndex()), nombre);
	model->setData(model->index(id, 1, QModelIndex()), cant);
	model->setData(model->index(id, 0, QModelIndex()), color, Qt::DecorationRole);
	model->submit();
	id++;
	return 0;
}

void pastel::limpiar()
{
	model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
	id = 0;
}
