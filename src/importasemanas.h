#ifndef IMPORTASEMANAS_H
#define IMPORTASEMANAS_H
//
#include <ui_copiaseg.h>
//
class importaSemanas : public QDialog
{
Q_OBJECT
public:
	importaSemanas(QString dirtrabajo);
private:
	Ui::copiaseg ui;
	QString dir;
	bool comprovarFichero(QString qfichero);
private slots:
	void cargarFichero();
	void importarFichero();
};
#endif
