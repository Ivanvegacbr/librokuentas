
#include <QtGui>
#include "grafico.h"
#include "funciones.h"
#include <qapplication.h>
#include <QPrinter>
//#include <QPrintDialog>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>

//
grafico::grafico(QString titulo, QString nombreX, QString nombreY, bool concomadecimal,
					bool condecimales ) 
	: QDialog()
{
	ui.setupUi(this);
	comadecimal=concomadecimal;
	decimales=condecimales;
	//setWindowTitle(titulo);
	ui.GPlot->setTitle(titulo);
		ui.GPlot->setCanvasBackground(Qt::white);
		ui.GPlot->setAxisTitle(QwtPlot::xBottom,nombreX);
		ui.GPlot->setAxisTitle(QwtPlot::yLeft,nombreY);
		ui.GPlot->setAutoReplot(false);
		QwtLegend *legend = new QwtLegend;
		legend->setItemMode(QwtLegend::CheckableItem);
		ui.GPlot->insertLegend(legend, QwtPlot::RightLegend);
		ui.tablaDatos->setEditTriggers ( QAbstractItemView::NoEditTriggers );
		connect(ui.guardarButton, SIGNAL(clicked()), this, SLOT (guardarImagen()));
		connect(ui.imprimirButton, SIGNAL(clicked()), this, SLOT (print()));
		connect(ui.GPlot, SIGNAL(legendChecked(QwtPlotItem *, bool)),
        	SLOT(verCurva(QwtPlotItem *, bool)));
	id = 0;
	Xname = nombreX;

}

grafico::~grafico()
{
	ui.GPlot->~QwtPlot();
	ui.tablaDatos->~QTableWidget();
}

int grafico::addCurva(QColor color, QString nombre, QList<double> valoresX, QList<double> valoresY)
{
	if(id > CURVAS) return 1;//controlamos el máximo de curvas en el plot o pastel
	if(!color.isValid()) color = randomColor(false);
    int ndecimales=2;
    if (!decimales) ndecimales=0;
    QString valor;
	//double total = 0.0;
	
		double x[valoresX.size()]; 
		double y[valoresX.size()]; 
		//ui.tablaDatos->setRowCount(id+1);
		//ui.tablaDatos->setColumnCount(valoresX.size());
		//hFilas << nombre;
		ui.tablaDatos->setRowCount(valoresX.size());
		ui.tablaDatos->setColumnCount(id+1);
		hColums << nombre;
		QPen pen1(Qt::lightGray, 1, Qt::DotLine);
	    
	    for(int i=0; i<valoresX.size() ; i++){
	    	if (comadecimal)
	    		valor = convacoma(valor.setNum(valoresY.at(i),'f',ndecimales));
	    	else
	    		valor.setNum(valoresY.at(i),'f',ndecimales);
	    	
	    	QTableWidgetItem *newItem = new QTableWidgetItem(valor);
	    	newItem->setTextAlignment (Qt::AlignRight | Qt::AlignVCenter);
	    	//ui.tablaDatos->setItem(id, i, newItem);
	    	//hColums << Xname+" "+valor.setNum(valoresX.at(i));
	    	ui.tablaDatos->setItem(i, id, newItem);
	    	hFilas << valor.setNum(valoresX.at(i));
	    	QwtPlotMarker *mX = new QwtPlotMarker();
	    	mX->setLineStyle(QwtPlotMarker::VLine);
	    	mX->setLinePen(pen1);
	    	mX->setXValue(valoresX.at(i));
	    	mX->attach(ui.GPlot);
	   		x[i] = valoresX.at(i);
	    	y[i] = valoresY.at(i);
	   	}
	    QPen pen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin);
	    QwtPlotCurve *curva = new QwtPlotCurve (nombre);
	    curva->setPen(pen);
		curva->setRenderHint(QwtPlotItem::RenderAntialiased);
		curva->setStyle(QwtPlotCurve::Steps);
		//curva->setSymbol( QwtSymbol(QwtSymbol::Ellipse,Qt::transparent,color, QSize(5,5)));
		curva->setCurveAttribute(QwtPlotCurve::Inverted);
		curva->setData( x, y, valoresX.size() );
		curva->attach(ui.GPlot);
		data[id] = curva;
	 	ui.tablaDatos->setHorizontalHeaderLabels(hColums);
	 	ui.tablaDatos->setVerticalHeaderLabels(hFilas);
	 	ui.tablaDatos->resizeColumnsToContents();
	 	verCurva(data[id], true);
	
 	id++;
 	return 0;
}

void grafico::verCurva(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
    QWidget *w = ui.GPlot->legend()->find(item);
    if ( w && w->inherits("QwtLegendItem") )
        ((QwtLegendItem *)w)->setChecked(on);
    
    ui.GPlot->replot();
}

// Salva la imagen creada en un archivo
void grafico::guardarImagen() {
    // Selección del nombre del fichero
    QFileDialog dialogofich(this);
    dialogofich.setFileMode(QFileDialog::AnyFile);
    dialogofich.setAcceptMode (QFileDialog::AcceptOpen );
    dialogofich.setLabelText ( QFileDialog::LookIn, tr("Directorio:") );
    dialogofich.setLabelText ( QFileDialog::FileName, tr("Archivo:") );
    dialogofich.setLabelText ( QFileDialog::FileType, tr("Tipo de archivo:") );
    dialogofich.setLabelText ( QFileDialog::Accept, tr("Guardar") );
    dialogofich.setLabelText ( QFileDialog::Reject, tr("Cancelar") );

    QStringList filtros;
    filtros << tr("Archivos de imagen (*.png)");
    dialogofich.setFilters(filtros);
    dialogofich.setDirectory(adapta(dirtrabajo()));
    dialogofich.setWindowTitle(tr("GUARDAR GRÁFICO"));

    // Si se ha seleccionado guardar
    if (dialogofich.exec()) {

        // Ruta del archivo seleccionado        
        QStringList fileNames;
        fileNames = dialogofich.selectedFiles();
        QString ruta=fileNames.at(0);
        if (!ruta.endsWith(".png")) ruta += ".png";
		QSize tamano = ui.GPlot->sizeHint();
        // rectangulo de fondo
        QRect rectangulofondo(0, 0, tamano.width(), tamano.height());
        //rectangulofondo->setZValue(-1);
    
        // genera la imagen
        QImage *imagen = new QImage(tamano.width(),tamano.height(), QImage::Format_RGB32);
        QPainter *p = new QPainter(imagen);
        p->setRenderHint(QPainter::Antialiasing);
        //graphicsscene->render(p);
        p->fillRect(rectangulofondo,Qt::white);
        ui.GPlot->print(p,rectangulofondo);
        p->end();
    
        // guarda la imagen
        bool grabado = imagen->save(adapta(ruta), "PNG");

        // elimina los punteros
        delete imagen;
        delete p;
        //delete rectangulofondo;

        // mensaje de confirmación /rechazo de guardado
        if (grabado) { QMessageBox::information ( this , tr("Gráfico"), tr("Imagen guardada en \n%1").arg(ruta)); }
        else { QMessageBox::warning ( this , tr("Gráfico"), tr("Ha habido problemas al intentar guardar la imagen en \n%1").arg(ruta)); }
    }
}

void grafico::print()
{
     printer = new QPrinter;
     QPrintDialog printDialog(printer, this);
     if ( printDialog.exec() == QDialog::Accepted ) {
         QPainter pp(printer);
         ui.GPlot->render(&pp);
     }
}

