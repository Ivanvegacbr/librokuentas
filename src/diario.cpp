/* ----------------------------------------------------------------------------------
    KEME-Contabilidad ; aplicación para llevar contabilidades

    Copyright (C)  José Manuel Díez Botella

    Este programa es software libre: usted puede redistribuirlo y/o modificarlo 
    bajo los términos de la Licencia Pública General GNU publicada 
    por la Fundación para el Software Libre, ya sea la versión 3 
    de la Licencia, o (a su elección) cualquier versión posterior.

    Este programa se distribuye con la esperanza de que sea útil, pero 
    SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
    MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
    Consulte los detalles de la Licencia Pública General GNU para obtener 
    una información más detallada. 

    Debería haber recibido una copia de la Licencia Pública General GNU 
    junto a este programa. 
    En caso contrario, consulte <http://www.gnu.org/licenses/>.
  ----------------------------------------------------------------------------------*/

#include "diario.h" 
#include "basedatos.h"
#include "funciones.h"
#include <QSqlField>



CustomSqlModel::CustomSqlModel(QObject *parent)
        : QSqlQueryModel(parent)
    {
     primerasiento1=numeracionrelativa();
     comadecimal=true; sindecimales=false;
    }

void CustomSqlModel::pasainfo(bool qcomadecimal, bool qsindecimales)
{
 comadecimal=qcomadecimal;
 sindecimales=qsindecimales;
}

void CustomSqlModel::chknumeracion()
{
  primerasiento1=numeracionrelativa();
}

qlonglong primas=0;

void asignaprimas(qlonglong qprimas)
{
 primas=qprimas;
}

QVariant CustomSqlModel::datagen(const QModelIndex &index, int role) const
    {
        QVariant value = QSqlQueryModel::data(index, role);
        return value;
    }

QVariant CustomSqlModel::data(const QModelIndex &index, int role) const
    {
        QString vacio;
        QVariant value = QSqlQueryModel::data(index, role);
        if (value.isValid() && role == Qt::DisplayRole) {
            if (index.column() == 1)
            {
            	return value.fromValue(descripcioncuenta(value.toString()));
           	}
            
            if (index.column() == 3)
               {
                // número de asiento
                if (primerasiento1)
                    {
                      QString cad2;
                      cad2.setNum(value.toLongLong()-primas+1);
                      return cad2;
                    }
               }
            if (index.column() == 2)
               {
                if (primerasiento1) asignaprimas(primasejerciciodelafecha(value.toDate()));
                return value.toDate().toString(Qt::SystemLocaleDate);
               }
            if (index.column() == 5 || index.column()==6)
	        {
   	        	if (value.toDouble()<0.0001 && value.toDouble()>-0.0001)
                   return value.fromValue(vacio);
                else
                   return formateanumerosep(value.toDouble(),comadecimal,!sindecimales);
	       }
	       if (index.column() == 10)
           {
                return value.toDate().toString(Qt::SystemLocaleDate);
           }
        }
        if (role == Qt::TextAlignmentRole && 
             (index.column() == 5 || index.column()==6 ||
              index.column() == 3 ))
            return qVariantFromValue(int(Qt::AlignVCenter | Qt::AlignRight));
        if (role == Qt::TextAlignmentRole && (index.column()==2 || index.column()==10))
            return qVariantFromValue(int(Qt::AlignCenter));
        if (role == Qt::TextColorRole && index.column() == 5)
        	return qVariantFromValue(QColor(Qt::darkBlue));
        if (role == Qt::TextColorRole && index.column() == 6)
        	return qVariantFromValue(QColor(Qt::darkRed));
        return value;
    }



diario::diario() : QWidget() {
  ui.setupUi(this);
  ui.latabladiario->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui.latabladiario->setSelectionMode(QAbstractItemView::ContiguousSelection);
  comadecimal=TRUE; sindecimales=FALSE;
                        //objeto del que sale la señal
      connect(ui.latabladiario,SIGNAL(clicked(QModelIndex)),this,SLOT(infocuentapase(QModelIndex)));
      connect(ui.latabladiario,SIGNAL(activated(QModelIndex)),this,SLOT(infocuentapase(QModelIndex)));
      //connect(ui.latabladiario,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ordenarColumna(QModelIndex)));
      
}

void diario::activaconfiltro(QString filtro,bool qcomadecimal, bool qsindecimales)
{
        CustomSqlModel *elmodelo = new CustomSqlModel;
        comadecimal=qcomadecimal;
        sindecimales=qsindecimales;
        model = elmodelo;
        model->pasainfo(qcomadecimal, qsindecimales);
        QString cadena;
        //cadena="SELECT d.cuenta, p.descripcion, d.fecha, d.asiento, d.concepto, d.debe, "
        //       "d.haber, d.documento, d.diario, d.pase,d.ci "
        //       "FROM diario d, plancontable p ";
        cadena = "SELECT cuenta, cuenta, fecha, asiento, concepto, debe, "
        		"haber, documento, diario, pase, ci "
        		"FROM diario ";
        if (filtro.length()>0)
        {
        	//QString newFiltro;
        	//newFiltro=filtro.replace("WHERE","AND");
        	//cadena+="WHERE p.codigo = d.cuenta "+newFiltro;
        	cadena+=filtro;
		}	 
        //else cadena+="WHERE p.codigo = d.cuenta";
        //QMessageBox::warning(this, "Debug","QUERY: "+cadena);
        qDebug() << cadena;
        model->setQuery(cadena);
        model->setHeaderData(0, Qt::Horizontal, tr("cuenta"));
        model->setHeaderData(1, Qt::Horizontal, tr("subcuenta"));
        model->setHeaderData(2, Qt::Horizontal, tr("fecha"));
        model->setHeaderData(3, Qt::Horizontal, tr("sem."));
        model->setHeaderData(4, Qt::Horizontal, tr("concepto"));
        model->setHeaderData(5, Qt::Horizontal, tr("debe"));
        model->setHeaderData(6, Qt::Horizontal, tr("haber"));
        model->setHeaderData(7, Qt::Horizontal, tr("documento"));
        model->setHeaderData(8, Qt::Horizontal, tr("diario"));
        model->setHeaderData(9, Qt::Horizontal, tr("pase"));
        model->setHeaderData(10, Qt::Horizontal, tr("pagado"));

        ui.latabladiario->setModel(model);
        ui.latabladiario->setColumnHidden(0,true);
        if (!conanalitica()) ui.latabladiario->setColumnHidden(10,true);
           else ui.latabladiario->setColumnHidden(10,false);
        ui.latabladiario->setAlternatingRowColors ( true);
        // infocuentapase();

}

void diario::pasafiltro(QString filtro,bool qcomadecimal,bool qsindecimales)
{
 model->pasainfo(qcomadecimal,qsindecimales);
 sindecimales=qsindecimales;
 QString cadena="SELECT cuenta, cuenta, fecha, asiento, concepto, debe, "
               "haber, documento, diario, pase, ci "
               "FROM diario ";
 if (filtro.length()>0)
 {
 	/*QString newFiltro;
 	newFiltro=filtro.replace("WHERE","AND");
 	cadena+="WHERE p.codigo = d.cuenta "+newFiltro;*/
 	cadena+=filtro;
 }	 
 //else cadena+="WHERE p.codigo = d.cuenta";
 //QMessageBox::warning(this, "Debug","QUERY: "+cadena);
 qDebug() << "diario:" << cadena;
 model->setQuery(cadena);

}

void diario::refresca()
{
 if (!conanalitica()) ui.latabladiario->setColumnHidden(10,true);
     else ui.latabladiario->setColumnHidden(10,false);
 model->chknumeracion();
 QSqlQuery p=model->query(); 
 p.exec();
 // model->clear();
 model->setQuery(p);
}

void diario::irfinal()
{
 QModelIndex indice=ui.latabladiario->currentIndex ();
 ui.latabladiario->setCurrentIndex(modelo()->index(modelo()->rowCount()-1,0));
 ui.latabladiario->scrollToBottom();
 ui.latabladiario->setFocus();
}


int diario::anchocolumna(int col)
{
 return ui.latabladiario->columnWidth(col);
}

void diario::pasaanchocolumna(int columna,int ancho)
{
  ui.latabladiario->setColumnWidth(columna,ancho);
}

void diario::pasaanchos(int ancho[])
{
  for (int veces=0;veces<11;veces++) pasaanchocolumna(veces,ancho[veces]);
}

void diario::muestratabla(void)
{
 ui.latabladiario->show();
}


QModelIndex diario::indiceactual(void)
{
 return ui.latabladiario->currentIndex();
}

void diario::situate(QModelIndex indice)
{
 ui.latabladiario->setCurrentIndex (indice);
}

void diario::pasafiltroedlin(QString filtro)
{
  ui.filtrolineEdit->setText(filtro);
}

void diario::infocuentapase(QModelIndex primaryKeyIndex)
{
   int fila=primaryKeyIndex.row();
   QString cad = model->record(fila).value("cuenta").toString();
   ui.codigolineEdit->setText(cad);
   ui.descriplineEdit->setText(descripcioncuenta(cad));

   QString ejercicio=ejerciciodelafecha(model->record(fila).value("fecha").toDate());
   double saldo=saldocuentaendiarioejercicio(cad,ejercicio);
   QString cadnum;
   cadnum.setNum(saldo,'f',2);
   cadnum.remove('-');

   if (comadecimal) cadnum=puntuanumerocomadec(cadnum);
       else cadnum=puntuanumeropuntodec(cadnum);

   if (saldo<0.001) { ui.haberlineEdit->setText(cadnum+" "); ui.debelineEdit->setText(""); }
   if (saldo>0.001) { ui.debelineEdit->setText(cadnum+" "); ui.haberlineEdit->setText(""); }

}

void diario::ordenarColumna(QModelIndex headerIndex){
	int fila=headerIndex.column();
	QString cadena; cadena.setNum(fila);
	//if(DEBUG) QMessageBox::warning(this, "Debug","QUERY: "+cadena);
	QSqlQuery p = model->query();
	cadena=p.lastQuery();
	QString query = cadena.section(" ORDER BY ",0,0);
	QString order = cadena.section(" ORDER BY ",1,1);
	query += " ORDER BY ";
	if (fila == 1){
		order.remove("cuenta,");
		query += "cuenta,";
	} else
		order.remove("cuenta,");
	query += order;
	p.exec(query);
	//if(DEBUG) QMessageBox::warning(this, "Debug","QUERY: "+query);
	model->setQuery(p);
}

QString diario::subcuentaactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return "";
 int fila=ui.latabladiario->currentIndex().row();
 return model->data(model->index(fila,0),Qt::DisplayRole).toString();
}

qlonglong diario::asientoactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return 0;
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("asiento").toLongLong();
 // return model->record(fila).field(2).defaultValue().toLongLong();
 // return model->data(model->index(fila,2),Qt::DisplayRole).toLongLong();
}


QDate diario::ciactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return QDate::currentDate();
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("ci").toDate();
}


QDate diario::fechapaseactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return QDate::currentDate();
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("fecha").toDate();
}

qlonglong diario::paseactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return 0;
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("pase").toLongLong();
}

double diario::debe()
{
 if (!ui.latabladiario->currentIndex().isValid()) return 0;
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("debe").toDouble();
}

double diario::haber()
{
 if (!ui.latabladiario->currentIndex().isValid()) return 0;
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("haber").toDouble();
}

CustomSqlModel *diario::modelo()
{
  return model;
}


QTableView *diario::tabladiario()
{
 return ui.latabladiario;
}


QString diario::conceptoactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return "";
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("concepto").toString();
}


QString diario::documentoactual()
{
 if (!ui.latabladiario->currentIndex().isValid()) return "";
 int fila=ui.latabladiario->currentIndex().row();
 return model->record(fila).value("documento").toString();
}

void diario::copiar()
{
 QItemSelectionModel *seleccion;
 //CustomSqlModel *model=punterodiario->modelo();
 seleccion=ui.latabladiario->selectionModel();
 if (seleccion->hasSelection())
    {
      QList<QModelIndex> lista;
      /*QList<QModelIndex> listafechas;
      QList<QModelIndex> listacuentas;
      QList<QModelIndex> listaconceptos;
      QList<QModelIndex> listadebe;
      QList<QModelIndex> listahaber;
      QList<QModelIndex> listadocumentos;
      listaasientos= seleccion->selectedRows ( 3 );
      listafechas=seleccion->selectedRows (2);
      listacuentas=seleccion->selectedRows (0);
      listaconceptos=seleccion->selectedRows (4);
      listadebe=seleccion->selectedRows (5);
      listahaber=seleccion->selectedRows (6);*/
      lista=seleccion->selectedRows (2);
      QString valores;
      for (int i = 0; i < lista.size(); ++i)
           {
            valores+=model->record(lista.at(i).row()).value("asiento").toString();
            valores+="\t";
            valores+=model->data(lista.at(i),Qt::DisplayRole).toString();
            valores+="\t";
            valores+=model->record(lista.at(i).row()).value("cuenta").toString();
            valores+="\t";
            valores+=model->record(lista.at(i).row()).value("concepto").toString();
            valores+="\t";
            if (comadecimal)
                 valores+=convacoma(model->record(lista.at(i).row()).value("debe").toString());
            else
                 valores+=model->record(lista.at(i).row()).value("debe").toString();
            valores+="\t";
            if (comadecimal)
                valores+=convacoma(model->record(lista.at(i).row()).value("haber").toString());
            else
                valores+=model->record(lista.at(i).row()).value("haber").toString();
            valores+="\t";
            valores+=model->record(lista.at(i).row()).value("documento").toString();
            valores+="\t";
            valores+=model->record(lista.at(i).row()).value("ci").toDate().toString(Qt::SystemLocaleDate);
            valores+="\n";
           }
      QClipboard *clipboard = QApplication::clipboard();
      clipboard->setText(valores);
      QMessageBox::information( this, tr("DIARIO"),
                             tr("El contenido de la selección se ha pasado al portapapeles"));
    }
}

diario::~diario()
{
 model->~CustomSqlModel();
}

