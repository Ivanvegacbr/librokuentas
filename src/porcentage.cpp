
#include "porcentage.h"
#include <QtGui>
//
porcentage::porcentage(QWidget *parent) : QWidget(parent)
{
	setupUi(this);
	// TODO
}
//
void porcentage::pasaValores(double genero, double debe, double haber, bool decimales)
{
	int ndecimales=2;
	if (!decimales) ndecimales=0;
	QString cadena=QString( "%1" ).arg(debe, 0, 'f',ndecimales ) ;
	LCDSumadebe->display(cadena);
	cadena=QString( "%1" ).arg(haber, 0, 'f',ndecimales ) ;
	LCDSumahaber->display(cadena);
	cadena=QString( "%1" ).arg(haber-debe, 0, 'f',ndecimales ) ;
	if (haber-debe>-0.0001)
      descuadreVerde();
	else
      descuadreRojo();
	LCDDescuadre->display(cadena);
	double xciento=0;
	//LCD Neto (con todos los gastos)
	if (haber != 0) xciento=(haber-debe)/haber*100;
	cadena=QString( "%1" ).arg(xciento, 0, 'f',ndecimales ) ;
	LCDNeto->display(cadena);
	//LCD Bruto (solo el género sin el resto de gastos)
	if (haber != 0) xciento=(haber-genero)/haber*100;
	cadena=QString( "%1" ).arg(xciento, 0, 'f',ndecimales ) ;
	LCDBruto->display(cadena);
	
}

double porcentage::valorBruto()
{
	return LCDBruto->value();
}

double porcentage::valorNeto()
{
	return LCDNeto->value();
}

double porcentage::valorBeneficio()
{
	return LCDDescuadre->value();
}

void porcentage::descuadreVerde()
{
    QPalette palette3;
    QBrush brush9(QColor(255, 255, 255, 255));
    brush9.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Active, QPalette::Base, brush9);
    QBrush brush10(QColor(170, 255, 127, 255));
    brush10.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Active, QPalette::Window, brush10);
    QBrush brush11(QColor(255, 255, 255, 255));
    brush11.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Inactive, QPalette::Base, brush11);
    QBrush brush12(QColor(170, 255, 127, 255));
    brush12.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Inactive, QPalette::Window, brush12);
    QBrush brush13(QColor(170, 255, 127, 255));
    brush13.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Disabled, QPalette::Base, brush13);
    QBrush brush14(QColor(170, 255, 127, 255));
    brush14.setStyle(Qt::SolidPattern);
    palette3.setBrush(QPalette::Disabled, QPalette::Window, brush14);
    LCDDescuadre->setPalette(palette3);

}

void porcentage::descuadreRojo()
{
    QPalette palette4;
    QBrush brush15(QColor(255, 255, 255, 255));
    brush15.setStyle(Qt::SolidPattern);
    palette4.setBrush(QPalette::Active, QPalette::Base, brush15);
    QBrush brush16(QColor(255, 85, 0, 255));
    brush16.setStyle(Qt::SolidPattern);
    palette4.setBrush(QPalette::Active, QPalette::Window, brush16);
    QBrush brush17(QColor(255, 255, 255, 255));
    brush17.setStyle(Qt::SolidPattern);
    palette4.setBrush(QPalette::Inactive, QPalette::Base, brush17);
    QBrush brush18(QColor(255, 85, 0, 255));
    brush18.setStyle(Qt::SolidPattern);
    palette4.setBrush(QPalette::Inactive, QPalette::Window, brush18);
    QBrush brush19(QColor(255, 85, 0, 255));
    brush19.setStyle(Qt::SolidPattern);
    palette4.setBrush(QPalette::Disabled, QPalette::Base, brush19);
    QBrush brush20(QColor(255, 85, 0, 255));
    brush20.setStyle(Qt::SolidPattern);
    palette4.setBrush(QPalette::Disabled, QPalette::Window, brush20);
    LCDDescuadre->setPalette(palette4);

}

void porcentage::reset()
{
	descuadreVerde();
	LCDSumadebe->display("0");
	LCDSumahaber->display("0");
	LCDDescuadre->display("0");
	LCDBruto->display("0");
	LCDNeto->display("0");
}

