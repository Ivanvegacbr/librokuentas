
#include "interfechas.h"
#include "basedatos.h"
#include "funciones.h"
//

interFechas::interFechas(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	
	QSqlQuery query = ejecutarSQL("select codigo from ejercicios order by codigo DESC;");
	QStringList ej1;
  	if ( query.isActive() ) {
	    while ( query.next() )
        ej1 << query.value(0).toString();
	}
  	ui.ejercicioComboBox->addItems(ej1);
  	ui.ejercicioComboBox->addItem(noejercicio());
  	//ejercicio=ui.ejercicioComboBox->currentText();
    ui.groupBox->setCheckable(false);
    ejercicioCambiado();

	connect(ui.ejercicioComboBox,SIGNAL(activated(int)),this,SLOT(ejercicioCambiado()));
	connect(ui.semanaComboBox,SIGNAL(activated(int)),this,SLOT(comboSemanaCambiado( int )));
	connect(ui.inicialdateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(initDate(QDate)));
	connect(ui.finaldateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(finalDate(QDate)));
}
//
void interFechas::ejercicioCambiado()
{
	QString ejercicio=ui.ejercicioComboBox->currentText();
	QString cad;
	QSqlQuery query;
    if (ejercicio != noejercicio())
    {
    	f_ini = inicioejercicio(ejercicio);
    	ui.inicialdateEdit->setDate(f_ini);
    	f_fin = finejercicio(ejercicio);
    	ui.finaldateEdit->setDate(f_fin);
    }
    else
    {
        cad = "SELECT min(apertura) FROM ejercicios;";
        query = ejecutarSQL(cad);
        if ( query.isActive() && query.next()){
        	f_ini = query.value(0).toDate();
        	ui.inicialdateEdit->setDate(f_ini);
       	}else{
       		f_ini = QDate::currentDate();
       		ui.inicialdateEdit->setDate(QDate::currentDate());
         }
        cad = "SELECT max(cierre) FROM ejercicios;";
        query = ejecutarSQL(cad);
        if ( query.isActive() && query.next()){
        	f_fin = query.value(0).toDate();
        	ui.finaldateEdit->setDate(f_fin);
       	}else{
       		f_fin = QDate::currentDate();
       		ui.finaldateEdit->setDate(QDate::currentDate());
         }
        //ejercicio = ejerciciodelafecha(QDate::currentDate());
        ui.semanaComboBox->clear();
        emit ejercicioActivado(ejercicio);
        return;
    }
    
    QString semana,asiento;
	cad = "SELECT asiento FROM diario WHERE fecha>='";
	cad+=f_ini.toString("yyyy.MM.dd");
	cad+="' AND fecha<='";
	cad+=f_fin.toString("yyyy.MM.dd");
	cad+="' ORDER BY asiento;";
	query = ejecutarSQL(cad);
	QStringList semanas;
	semanas << "";
	if ( query.isActive() )
	{
		while (query.next())
		{
				asiento=query.value(0).toString();
				if (asiento != semana) 
				{
					semana = asiento;
					semanas << semana ;
				}
		}
	}
	ui.semanaComboBox->clear();
	ui.semanaComboBox->addItems(semanas);
	
	emit ejercicioActivado(ejercicio);
}

void interFechas::comboSemanaCambiado( int index )
{
	QString ejercicio=ui.ejercicioComboBox->currentText();
    ui.semanaComboBox->setEditText(ui.semanaComboBox->itemText(index));
	if (existeasiento(ui.semanaComboBox->itemText(index),ejercicio))
	{
		ui.inicialdateEdit->setDate(fechaMinAsiento(ui.semanaComboBox->itemText(index),ejercicio));
		ui.finaldateEdit->setDate(fechaMaxAsiento(ui.semanaComboBox->itemText(index),ejercicio));
		}else{
		if (ejercicio=="") ejercicio=ejercicio_igual_o_maxigual(QDate::currentDate());
    	ui.inicialdateEdit->setDate(inicioejercicio(ejercicio));
    	ui.finaldateEdit->setDate(finejercicio(ejercicio));
	}
	f_ini = ui.inicialdateEdit->date();
	f_fin = ui.finaldateEdit->date();
	emit semanaCambiada(ui.semanaComboBox->itemText(index));
}

void interFechas::initDate(QDate fe)
{
	f_ini = fe;
	emit fechaCambiada(inicial);
}

void interFechas::finalDate(QDate fe)
{
	f_fin = fe;
	emit fechaCambiada(final);
}

QDate interFechas::fecha(Fecha index)
{
	if(index == inicial)	return ui.inicialdateEdit->date();
	if(index == final)	return ui.finaldateEdit->date();
	return QDate::currentDate();
}

/*QString interFechas::SFecha(Fecha index)
{
	if(index == inicial)	return ui.inicialdateEdit->text();
	if(index == final)	return ui.finaldateEdit->text();
	return QDate::currentDate().toString("yyyy.MM.dd");
}*/

void interFechas::setCheckable(bool chk)
{
	ui.groupBox->setCheckable(chk);
}

void interFechas::setFecha(Fecha index, QDate fecha)
{
	if(index == inicial){
		if(fecha != f_ini){
			f_ini = fecha;
			ui.inicialdateEdit->setDate(fecha);
			emit fechaCambiada(inicial);
		}
	}
	if(index == final){
		if(fecha != f_fin){
			f_fin = fecha;
			ui.finaldateEdit->setDate(fecha);
			emit fechaCambiada(final);
		}
	}
	for (int veces=0; veces < ui.ejercicioComboBox->count(); veces++)
     {
       if (ui.ejercicioComboBox->itemText(veces)==ejerciciodelafecha(fecha)){
	     if(veces != ui.ejercicioComboBox->currentIndex()){
	     	ui.ejercicioComboBox->setCurrentIndex(veces);
	       	ejercicioCambiado();
     	 }
	   }
     }
}

void interFechas::setSemana(QString sem, QString qejercicio)
{
	setEjercicio(qejercicio);
	for (int veces=0; veces < ui.semanaComboBox->count(); veces++)
     {
       if (ui.semanaComboBox->itemText(veces)==sem){
       	ui.semanaComboBox->setCurrentIndex(veces);
       	comboSemanaCambiado( veces );
	   }
     }
}

void interFechas::setEjercicio(QString qejercicio)
{
	for (int veces=0; veces < ui.ejercicioComboBox->count(); veces++)
     {
       if (ui.ejercicioComboBox->itemText(veces)==qejercicio){
       	ui.ejercicioComboBox->setCurrentIndex(veces);
       	ejercicioCambiado();
	   }
     }
}

bool interFechas::isChecked()
{
	return ui.groupBox->isChecked();
}

QString interFechas::ejercicio()
{
	return ui.ejercicioComboBox->currentText();
}

QString interFechas::semana()
{
	return ui.semanaComboBox->currentText();
}
