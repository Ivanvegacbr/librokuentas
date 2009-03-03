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

#include "copiaseg.h"
#include <QProcess>
#include <QSqlDatabase>
#include "funciones.h"
#include <QProgressDialog>


copiaseg::copiaseg() : QDialog() {
    ui.setupUi(this);
    QSqlDatabase bd;
    bd=QSqlDatabase::database ();
    nombre=bd.databaseName();
    usuario=bd.userName();
    host=bd.hostName();
    clave=bd.password();
    controlador=bd.driverName();
    nombrefichero=tr("libroKuentas-")+nombre;
    QDate fecha;
    nombrefichero+="-";
    nombrefichero+=fecha.currentDate().toString("dd.MM.yyyy");
    nombrefichero+=".sql";
    ui.textLabel2->setText(nombrefichero);

   connect(ui.aceptarpushButton,SIGNAL(clicked()),this,SLOT(procesar()));

}


void copiaseg::procesar()
{
 ui.progressBar->setEnabled(TRUE);
 //QProgressDialog progreso("Generando copia de seguridad ...", 0, 0, 100);
 //progreso.setWindowModality(Qt::WindowModal);
 //progreso.setMaximum(0);
 //progreso.setValue(1);
  QString cadena;
  if (controlador=="QPSQL7" || controlador=="QPSQL")
    {
     if (clave.length()>0)
       {
         QMessageBox::warning( this, tr("Copia de seguridad"),
		tr("No se puede realizar la copia cuando la base de datos se accede\n"
		   "mediante clave; utilice el programa 'PG_DUMP' en su lugar."));
        return;
       }

     QObject *parent=NULL;

     QString cadexec="pg_dump";
     QProcess *myProcess = new QProcess(parent);
     QStringList arguments;
     QString cadarg;
     if (host.length()>0)
        {
         arguments << "-h";
         arguments << host;
        }
     if (usuario.length()>0)
       {
         cadarg="-U ";
         cadarg+=usuario;
         arguments << cadarg;
       }

     cadarg=nombre;
     arguments << nombre;
     arguments << "-f";
     cadarg=dirtrabajo();
     cadarg.append(QDir::separator());
     cadarg+=nombrefichero;
     arguments << cadarg;
     // arguments << "&";

     myProcess-> setWorkingDirectory(dirtrabajo());
	 ui.textLabel2->setText("Generando copia de seguridad ...");
	 ui.progressBar->setMaximum(0);
 	 ui.progressBar->setValue(1);
 
     myProcess->start(cadexec,arguments);

     if (!myProcess->waitForStarted ())
       {
         QMessageBox::warning( this, tr("COPIA DE SEGURIDAD"),tr("ERROR: no se ha podido ejecutar"
                                                                  " el programa externo pg_dump"));
         myProcess->~QProcess();
         return;
       }
     if (!myProcess->waitForFinished (60000 ))
       {
         QMessageBox::warning( this, tr("COPIA DE SEGURIDAD"),tr("ERROR: no se ha podido ejecutar"
                                                                  " el programa externo pg_dump"));
         myProcess->~QProcess();
         return;
       }
     myProcess->~QProcess();
    }
  else
          {
             // mysql
           QObject *parent=NULL;
           QString cadexec;
           QProcess *myProcess = new QProcess(parent);
           QStringList arguments;
           QString cadarg;
           cadexec="mysqldump";
           //if (eswindows()) cadexec+=".exe";
           if (host.length()>0)
              {
                cadarg="--host=";
                cadarg+=host;
                arguments << cadarg;
               }
           if (usuario.length()>0)
             {
              cadarg="--user=";
              cadarg+=usuario;
              arguments << cadarg;
             }
          if (clave.length()>0)
            {
               cadarg="--password=";
               cadarg+=clave;
               arguments << cadarg;
            }
          cadarg=nombre;
          arguments << cadarg;
          cadarg="-r";
          cadarg+=dirtrabajo();
          cadarg.append(QDir::separator());
          cadarg+=nombrefichero;
          arguments << cadarg;
          // cadarg=" &";
          // arguments << cadarg;
          myProcess-> setWorkingDirectory(dirtrabajo());
	 ui.textLabel2->setText("Generando copia de seguridad ...");
	 ui.progressBar->setMaximum(0);
 	 ui.progressBar->setValue(1);

          myProcess->start(cadexec,arguments);
          if (!myProcess->waitForStarted ())
             {
               QMessageBox::warning( this, tr("COPIA DE SEGURIDAD"),tr("ERROR: no se ha podido ejecutar"
                                                                  " el programa externo mysqldump"));
               myProcess->~QProcess();
               return;
             }
          // myProcess->~QProcess();
          if (!myProcess->waitForFinished (60000))
           {
            QMessageBox::warning( this, tr("COPIA DE SEGURIDAD"),tr("ERROR: no se ha podido ejecutar"
                                                                  " el programa externo pg_dump"));
            myProcess->~QProcess();
            return;
           }
          myProcess->~QProcess();
         }
     
     QObject *parent=NULL;
     QProcess *myProcess = new QProcess(parent);
     QString cadexec="gzip "+nombrefichero;
     myProcess->setWorkingDirectory(dirtrabajo());
	 myProcess->start(cadexec);     
     myProcess->waitForFinished (-1);
     myProcess->~QProcess();
     QMessageBox::information( this, tr("Copia de seguridad"),
		tr("La copia de seguridad se ha realizado"));
     accept();
 }
