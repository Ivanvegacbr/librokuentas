#ifndef GRAFICO_H
#define GRAFICO_H
//
#include <QtGui>
#include "ui_grafico.h"
#include <qwt_plot_curve.h>
#define CURVAS 100
//

class grafico : public QDialog
{
Q_OBJECT
public:
	grafico(QString titulo, QString nombreX, QString nombreY, bool concomadecimal,
					bool condecimales );
	virtual ~grafico();
	int addCurva(QColor color, QString nombre, QList<double> valoresX, QList<double> valoresY);
	
private:
	Ui::grafico ui;
	QwtPlotCurve *data[CURVAS];
	int id;
	bool comadecimal;
	bool decimales;
	QStringList hFilas,hColums;
	QString Xname;
	QPrinter *printer;

private slots:
	void verCurva(QwtPlotItem *item, bool on);
	void guardarImagen();
	void print();
};
#endif
