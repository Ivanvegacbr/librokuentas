#ifndef LACAIXA_H
#define LACAIXA_H
//
#include <QtGui>
#include "ui_lacaixa.h"
#include "tabla_asientos.h"
//
class lacaixa : public QDialog
{
Q_OBJECT
public:
	lacaixa( bool comadecimal, bool decimales );
	
private:
	Ui::lacaixa ui;
	tabla_asientos *t;
	int pos,fila;
	QFile fichero;
	QTextStream stream;
	bool importarFichPases(QString qfichero);
	QString abrirFichero();
	void pasaTabla();
private slots:
	void incorporar();
	void ignorar();
	void botonsubcuentapulsado();
	void sensibilidadCambiada(int sens);
	void siguiente();
};
#endif
