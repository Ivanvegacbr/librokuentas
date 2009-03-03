/* ----------------------------------------------------------------------------------
    KEME-Contabilidad 2.1; aplicación para llevar contabilidades

    Copyright (C) 2007  José Manuel Díez Botella

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

#include "ejercicios.h"
#include "nuevoejercicio.h"
#include "basedatos.h"
//#include "funciones.h"
#include "editafechacierre.h"
#include "periodos.h"


CustomSqlModel3::CustomSqlModel3(QObject *parent)
        : QSqlQueryModel(parent)
    {
    }


QVariant CustomSqlModel3::datagen(const QModelIndex &index, int role) const
    {
        QVariant value = QSqlQueryModel::data(index, role);
        return value;
    }

QVariant CustomSqlModel3::data(const QModelIndex &index, int role) const
    {
        QString vacio;
        QVariant value = QSqlQueryModel::data(index, role);
        if (value.isValid() && role == Qt::DisplayRole) {
            if (index.column() == 1 || index.column() == 2)
               {
                return value.toDate().toString(Qt::SystemLocaleDate);
               }
            if (index.column() == 3 || index.column()==4)
               {
                if (value.toBool()) return value.fromValue(tr("SI"));
                   else return value.fromValue(tr("NO"));
               }
        }
        return value;
    }



ejercicios::ejercicios() : QDialog() {
    ui.setupUi(this);
    CustomSqlModel3 *elmodelo = new CustomSqlModel3;
    model = elmodelo;
    QString cadena;
    cadena="SELECT codigo,apertura,cierre,cerrado,cerrando,primerasiento "
            "from ejercicios order by apertura";

     model->setQuery(cadena);
     model->setHeaderData(0, Qt::Horizontal, tr("CÓDIGO"));
     model->setHeaderData(1, Qt::Horizontal, tr("APERTURA"));
     model->setHeaderData(2, Qt::Horizontal, tr("CIERRE"));
     model->setHeaderData(3, Qt::Horizontal, tr("CERRADO"));
     model->setHeaderData(4, Qt::Horizontal, tr("CERRANDO"));

     ui.ejerciciostableView->setModel(model);
     ui.ejerciciostableView->setAlternatingRowColors ( true);

     connect(ui.nuevopushButton,SIGNAL(clicked()),SLOT(nuevejercicio()));
     connect(ui.eliminarpushButton,SIGNAL(clicked()),SLOT(borraejercicio()));
     connect(ui.fcierrepushButton,SIGNAL(clicked()),SLOT(editacierre()));
     connect(ui.periodospushButton,SIGNAL(clicked()),SLOT(editaperiodos()));

}

ejercicios::~ejercicios()
{
  ui.ejerciciostableView->~QTableView();
  model->~CustomSqlModel3();
}


void ejercicios::refrescar()
{
 QSqlQuery p=model->query(); 
 p.exec();
 // model->clear();
 model->setQuery(p);
}

void ejercicios::nuevejercicio()
{
  nuevoejercicio *nejercicio = new nuevoejercicio();
  nejercicio->exec();
  nejercicio->~nuevoejercicio();
  refrescar();
}

void ejercicios::borraejercicio()
{
    QString elcodigo;
    elcodigo=ejercicioactual();
    if (elcodigo=="")
       {
         QMessageBox::warning( this, tr("Ejercicios"),
         tr("Para borrar un ejercicio debe de seleccionarlo en la lista"));
         return;
       }

    QString cadena;
    int fila=ui.ejerciciostableView->currentIndex().row();
    cadena="select asiento from diario where fecha>='";
    cadena+=model->datagen(model->index(fila,1),Qt::DisplayRole).toDate().toString("yyyy/MM/dd");
    cadena+="' and fecha<='";
    cadena+=model->datagen(model->index(fila,2),Qt::DisplayRole).toDate().toString("yyyy/MM/dd");
    cadena+="';";
    QSqlQuery query(cadena);
     if ( query.isActive() )
          {
              if (query.next())
                   {
                     QMessageBox::warning( this, tr("Borrar ejercicios"),
                     tr("ERROR: El ejercicio seleccionado posee apuntes en el diario"));
                     return;
                   } 
          }
  // Bueno parece que se puede borrar el ejercicio
  cadena="delete from ejercicios where codigo='";
  cadena+=elcodigo;
  cadena+="';";
  query.exec(cadena);
  refrescar();
}




QString ejercicios::ejercicioactual()
{

 if (!ui.ejerciciostableView->currentIndex().isValid()) return "";
 int fila=ui.ejerciciostableView->currentIndex().row();
 return model->data(model->index(fila,0),Qt::DisplayRole).toString();

}


void ejercicios::editacierre()
{
    QString elcodigo;
    elcodigo=ejercicioactual();
    if (elcodigo=="")
       {
         QMessageBox::warning( this, tr("Ejercicios"),
         tr("Para editar la fecha de cierre de un ejercicio debe de seleccionarlo de la lista"));
         return;
       }
 int fila=ui.ejerciciostableView->currentIndex().row();
 if (model->datagen(model->index(fila,3),Qt::DisplayRole).toBool() ||
      model->datagen(model->index(fila,4),Qt::DisplayRole).toBool())
    {
         QMessageBox::warning( this, tr("Ejercicios"),
         tr("No es posible editar la fecha de cierre de un ejercicio cerrado"));
         return;
    }

  editafechacierre *ef = new editafechacierre();
  ef->pasafecha(model->datagen(model->index(fila,2),Qt::DisplayRole).toDate());
  ef->pasaapertura(model->datagen(model->index(fila,1),Qt::DisplayRole).toDate());
  ef->pasaejercicio(model->datagen(model->index(fila,0),Qt::DisplayRole).toString());
  ef->exec();
  ef->~editafechacierre();
  refrescar();
}


void ejercicios::editaperiodos()
{
    QString elcodigo;
    elcodigo=ejercicioactual();
    if (elcodigo=="")
       {
         QMessageBox::warning( this, tr("Ejercicios"),
         tr("Para editar periodos de un ejercicio debe de seleccionarlo de la lista"));
         return;
       }

 periodos *p = new periodos(elcodigo);
 p->exec();
 p->~periodos();

}
