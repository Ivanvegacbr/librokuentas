#ifndef CIERRES_H
#define CIERRES_H
//
#include <QString>
//
class cierres
{

public:
	cierres( QString ejercicio );
	bool marcarCerrado();
	bool suprimeCierre();
	
private:
	QString ejer;
	
};
#endif
