/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

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

#include <QApplication>
#include <QDebug>
#include "principal.h"
#include "inicial.h"
#include "funciones.h"
#include <qtextcodec.h>


int main(int argc, char *argv[])
{
        // Q_INIT_RESOURCE(application);

  QApplication app(argc, argv);
  QTextCodec::setCodecForTr( QTextCodec::codecForName("utf8") );

  int idioma=idiomaconfig();
  QString fich_idioma;
  QTranslator translator;
  QString locale = QLocale::system().name();
  locale.remove("\"");
  qDebug() << locale;

  if (idioma>0 && idioma<3)
     {
      if (idioma==1) fich_idioma = fich_ingles();
      if (idioma==2) fich_idioma = fich_catalan();
      translator.load(fich_idioma);
      app.installTranslator(&translator);
      
      qDebug() << "TR:" << fich_idioma;
      //qDebug() << app.arguments().at(1);
     }

  Mrconta mainWin;
  if (mainWin.oknosalir()) 
       {
        mainWin.show();
       } else { return (0); }
  return app.exec();
 }

