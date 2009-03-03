#ifndef PORCENTAGE_H
#define PORCENTAGE_H
//
#include "ui_porcentage.h"

//
class porcentage : public QWidget, private Ui::porcentage
{
Q_OBJECT
public:
	porcentage(QWidget *parent = 0);
	void pasaValores(double genero, double debe, double haber, bool decimales);
	double valorBruto();
	double valorNeto();
	double valorBeneficio();
	void reset();
	
private:
	//Ui::porcentage ui;
	void descuadreVerde();
	void descuadreRojo();
};
#endif
