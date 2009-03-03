#ifndef PASTEL_H
#define PASTEL_H
//
#include <QtGui>
#define PORCIONES 100
//
class pastel : public QDialog
{
Q_OBJECT
public:
	pastel(int tamany = 350 , bool concomadecimal = true, bool condecimales = true );
	int addPorcion(QColor color, QString nombre, double valor);
	void limpiar();
	
private:
	int id;
	bool comadecimal;
	bool decimales;
	void setupModel();
	
	QAbstractItemModel *model;
	QAbstractItemView *pieChart;
	QItemSelectionModel *selectionModel;

};
#endif
