#ifndef EQUIVALENCIAS_H
#define EQUIVALENCIAS_H

#include <QSqlTableModel>

#include <QtGui>
#include "ui_equivalencias.h"

class equivalencias : public QDialog
{
Q_OBJECT
public:
	equivalencias();
	~equivalencias();
	
private:
	Ui::equivalencias ui;
	QSqlTableModel *modeloEquiv;
	void ctaexpandepunto();
	
private slots :
	void botonsubcuentapulsado();
	void subcuentacambiada();
	void finedicsubcuenta();
	void botonguardarpulsado();
	void botoncancelarpulsado();
	void botoneliminarpulsado();
	void tablapulsada();
	void incorporarCambiado(int incorp);

};
#endif
