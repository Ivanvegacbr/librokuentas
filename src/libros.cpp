/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

    Copyright (C)   José Manuel Díez Botella

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

#include "libros.h"
#include "funciones.h"


libros::libros() : QDialog() {
    ui.setupUi(this);
   ui.texlistWidget->clear();
   ui.seleclistWidget->clear();
   QDir directorio(dirtrabajo());
   QStringList filters;
   filters << "*.tex";
   directorio.setNameFilters(filters);
   directorio.setSorting(QDir::Name);
   ui.texlistWidget->setSortingEnabled(TRUE);
   ui.texlistWidget->addItems(directorio.entryList());

  connect(ui.adicionpushButton,SIGNAL( clicked()),this,SLOT(adicionitem()));
  connect(ui.quitarpushButton,SIGNAL( clicked()),this,SLOT(quitaritem()));
  connect(ui.arribapushButton,SIGNAL( clicked()),this,SLOT(subir()));
  connect(ui.abajopushButton,SIGNAL( clicked()),this,SLOT(bajar()));
  connect(ui.nombrelineEdit,SIGNAL( textChanged (QString)),this,SLOT(nombrecambiado()));
  connect(ui.guardarpushButton,SIGNAL( clicked()),this,SLOT(guardafichero()));

  connect(ui.texlistWidget,SIGNAL(itemDoubleClicked ( QListWidgetItem *)),this,SLOT(adicionitem()));
  connect(ui.seleclistWidget,SIGNAL(itemDoubleClicked ( QListWidgetItem *)),this,SLOT(quitaritem()));

}


void libros::adicionitem()
{
   if (ui.texlistWidget->currentItem()!=0)
    {
       ui.seleclistWidget->addItem(ui.texlistWidget->currentItem()->text());
       delete ui.texlistWidget->takeItem(ui.texlistWidget->currentRow());
    }
       else   QMessageBox::warning( this, tr("Libros contables"),
		       tr("Debe de seleccionar un elemento de la lista"));

}


void libros::quitaritem()
{
   if (ui.seleclistWidget->currentItem()!=0)
    {
       ui.texlistWidget->addItem(ui.seleclistWidget->currentItem()->text());
       delete ui.seleclistWidget->takeItem(ui.seleclistWidget->currentRow());
    }
       else   QMessageBox::warning( this, tr("Libros contables"),
		       tr("Debe de seleccionar un elemento de la lista"));
}


void libros::subir()
{
  if (ui.seleclistWidget->currentRow()>0)
    {
      QString cadena1=ui.seleclistWidget->currentItem()->text();
      int fila1=ui.seleclistWidget->currentRow();
      ui.seleclistWidget->setCurrentRow(fila1-1);
      QString cadena0=ui.seleclistWidget->currentItem()->text();
      ui.seleclistWidget->currentItem()->setText(cadena1);
      ui.seleclistWidget->setCurrentRow(fila1);
      ui.seleclistWidget->currentItem()->setText(cadena0);
      ui.seleclistWidget->setCurrentRow(fila1-1);
    }
}


void libros::bajar()
{
  if (ui.seleclistWidget->currentRow()<ui.seleclistWidget->count()-1)
    {
      QString cadena1=ui.seleclistWidget->currentItem()->text();
      int fila1=ui.seleclistWidget->currentRow();
      ui.seleclistWidget->setCurrentRow(fila1+1);
      QString cadena0=ui.seleclistWidget->currentItem()->text();
      ui.seleclistWidget->currentItem()->setText(cadena1);
      ui.seleclistWidget->setCurrentRow(fila1);
      ui.seleclistWidget->currentItem()->setText(cadena0);
      ui.seleclistWidget->setCurrentRow(fila1+1);

    }
}


void libros::nombrecambiado()
{
  if (ui.nombrelineEdit->text().contains(' ')>0)
    {
     QMessageBox::warning( this, tr("Libros contables"),tr("No se permiten espacios en el nombre de fichero"));
     ui.nombrelineEdit->setText(ui.nombrelineEdit->text().remove(' '));
    }
  if (ui.nombrelineEdit->text().contains("..")>0)
    {
     QMessageBox::warning( this, tr("Libros contables"),
        tr("No se permiten dos puntos seguidos en el nombre de fichero"));
     ui.nombrelineEdit->setText(ui.nombrelineEdit->text().remove(".."));
    }
  if (ui.nombrelineEdit->text().contains('/')>0)
    {
     QMessageBox::warning( this, tr("Libros contables"),
        tr("No se permite el caracter '/' en el nombre de fichero"));
     ui.nombrelineEdit->setText(ui.nombrelineEdit->text().remove('/'));
    }
  if (ui.nombrelineEdit->text().contains('\\')>0)
    {
     QMessageBox::warning( this, tr("Libros contables"),
        tr("No se permite el caracter '\' en el nombre de fichero"));
     ui.nombrelineEdit->setText(ui.nombrelineEdit->text().remove('\\'));
    }
  if (ui.nombrelineEdit->text().contains('*')>0)
    {
     QMessageBox::warning( this, tr("Libros contables"),
        tr("No se permite el caracter '*' en el nombre de fichero"));
     ui.nombrelineEdit->setText(ui.nombrelineEdit->text().remove('*'));
    }
  if (ui.nombrelineEdit->text().contains('?')>0)
    {
     QMessageBox::warning( this, tr("Libros contables"),
       tr("No se permite el caracter '?' en el nombre de fichero"));
     ui.nombrelineEdit->setText(ui.nombrelineEdit->text().remove('?'));
    }

}


void libros::guardafichero()
{
  if (ui.seleclistWidget->count()==0) 
    {
      QMessageBox::warning( this, tr("Libros contables"),tr("Error: No hay ficheros seleccionados"));
      return;
    }
  if (ui.nombrelineEdit->text().length()==0) 
    {
      QMessageBox::warning( this, tr("Libros contables"),
       tr("Error: No se ha especificado nombre a la selección"));
      return;
    }

  QString qfichero=dirtrabajo();
  qfichero.append(QDir::separator());
  qfichero=qfichero+ui.nombrelineEdit->text();
  if (ui.nombrelineEdit->text().right(4)!=".tex") qfichero=qfichero+".tex";

  QFile libro( adapta(qfichero)  );
  if ( !libro.open( QIODevice::WriteOnly  ) )
       {
        QMessageBox::warning( this, tr("Libros contables"),tr("Error: Imposible grabar fichero"));
        return;
       }
  QTextStream librostream( &libro );
  librostream.setCodec("UTF-8");

  QString cadfichtex=dirtrabajo();
  cadfichtex.append(QDir::separator());

  // --------------------------------------------------------------------------------------------------
  ui.seleclistWidget->setCurrentRow(0);
  cadfichtex+=ui.seleclistWidget->currentItem()->text();

  QFile primero(adapta(cadfichtex));
   if ( primero.open( QIODevice::ReadOnly ) )
      {
        QTextStream stream( &primero );
        stream.setCodec("UTF-8");
        QString linea;
         while ( ! stream.atEnd() )
	   {
	     linea = stream.readLine(); // linea de texto, excluye '\n'
	     if (linea.left(8)=="% CUERPO") break;
	     // librostream << linea << "\n";
           }
        // añadimos la cabecera manualmente con el paquete lscape
        librostream << "\\documentclass[11pt,a4paper]{article}" << "\n";
        librostream << "\\usepackage{ucs}" << "\n";
        librostream << "\\usepackage[utf8x]{inputenc}" << "\n";
        librostream << "\\usepackage[spanish]{babel}" << "\n";
        librostream << "\\usepackage{longtable}" << "\n";
        librostream << "\\usepackage{lscape}" << "\n";
        librostream << "\\addtolength{\\hoffset}{-2.8cm}" << "\n";
        librostream << "\\addtolength{\\textwidth}{5.6cm}" << "\n";
        librostream << "\\addtolength{\\voffset}{-1.5cm}" << "\n";
        librostream << "\\addtolength{\\textheight}{3cm}" << "\n";
        librostream << "\\begin{document}" << "\n";

        librostream << "% CUERPO" << "\n";
        primero.close();
       }
   
   for (int veces=0;veces<ui.seleclistWidget->count();veces++)
     {
       cadfichtex=dirtrabajo();
       cadfichtex.append(QDir::separator());
       ui.seleclistWidget->setCurrentRow(veces);
       cadfichtex+=ui.seleclistWidget->currentItem()->text();
       QFile cuerpofich(adapta(cadfichtex));
       if ( cuerpofich.open( QIODevice::ReadOnly ) )
          {
            QTextStream streamcuerpo(&cuerpofich);
            streamcuerpo.setCodec("UTF-8");
           // buscamos la marca del cuerpo
           QString linea;
           while (!streamcuerpo.atEnd())
             {
	      linea=streamcuerpo.readLine();
	      if (linea.left(8)=="% CUERPO") break;
             }
            // pasamos el resto del fichero al libro
           while (!streamcuerpo.atEnd())
            {
		     linea=streamcuerpo.readLine();
		     if (linea.left(12)=="% FIN_CUERPO") break;
             librostream << linea << "\n";
            }
           librostream << "\\newpage" << "\n";
           cuerpofich.close();
         }
     }
   // falta procesar el pie del último fichero

   QFile ultimo(adapta(cadfichtex));
   if ( ultimo.open( QIODevice::ReadOnly ) )
      {
        QTextStream stream( &ultimo );
        stream.setCodec("UTF-8");
        QString linea;
         while ( !stream.atEnd() )
	   {
	     linea = stream.readLine(); // linea de texto, excluye '\n'
	     if (linea.left(12)=="% FIN_CUERPO") break;
           }
        librostream << "% FIN_CUERPO" << "\n";
         while ( !stream.atEnd() )
	   {
	     linea = stream.readLine(); // linea de texto, excluye '\n'
                     librostream << linea << "\n";
           }
        ultimo.close();
       }

  libro.close();
 QMessageBox::information( this, tr("Libros contables"),
           tr("Los ficheros seleccionados se han agrupado en un libro"));
 accept();
}


