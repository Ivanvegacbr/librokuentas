#ifndef INTERFECHAS_H
#define INTERFECHAS_H
//
#include <ui_interFechas.h>
#include <QString>
#include <QDateTime>
//
class interFechas : public QWidget
{
Q_OBJECT

public:
	enum Fecha
	{
		inicial,
		final
	};
	interFechas(QWidget *parent = 0);
	QDate fecha(Fecha index);
	bool isChecked();
	QString ejercicio();
	QString semana();
	
public slots:
	void setFecha(Fecha index, QDate fecha);
	void setSemana(QString sem, QString qejercicio);
	void setEjercicio(QString qejercicio);
	void setCheckable(bool chk);

private:
	Ui::interFechas ui;
	QDate f_ini,f_fin;
	//QString ejercicio;
	
private slots:
	void comboSemanaCambiado(int index);
	void ejercicioCambiado();
	void initDate(QDate fe);
	void finalDate(QDate fe);

signals:
	void ejercicioActivado(QString eje);
	void fechaCambiada(Fecha index);
	void semanaCambiada(QString sem);

};
#endif
