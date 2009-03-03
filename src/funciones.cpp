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

#include "funciones.h"
#include "basedatos.h"
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QTextDocument>
#include <QProcess>
#include <QPrinter>
//#include "aritmetica.h"
#ifdef Q_WS_X11
	#define WINDOWS 0
#else
	#define WINDOWS 1
#endif

//#define BLOCK_SIZE 3

QString convacoma(QString cad)
{
  QString origen;
  // if (origen[origen.length()-3]=='.') origen[origen.length()-3]=',';
  origen=cad.replace('.',',');
  return origen;
}


QString puntuanumerocomadec(QString origen)
{
 QString origen1=convacoma(origen).remove(' ');
 QString entera=origen1.left(uint(origen1.indexOf(',')));
 QString signo;
 // if (entera[1]=='-') {signo="-"; entera=entera.right(entera.length()-1);}
 if (entera.length()<4) return origen1;
 QString decimal=origen1.right(origen1.length()-uint(origen1.indexOf(',')));
 QString enterapuntos;
 int pasados=0;
 for (int veces=entera.length()-1;veces>=0;veces--)
     {
       pasados++;
       enterapuntos=enterapuntos.insert(0,entera[veces]);
       if (pasados==3 || pasados==6 || pasados==9)
           enterapuntos=enterapuntos.insert(0,'.');
     }
 if (enterapuntos[0]=='.') enterapuntos=enterapuntos.remove(0,1);
 if (enterapuntos[0]=='-' && enterapuntos[1]=='.') enterapuntos=enterapuntos.remove(1,1);
 QString resultado;
 resultado=signo;
 resultado+=enterapuntos;
 resultado+=decimal;
 return resultado;
}

 
QString puntuanumeropuntodec(QString origen)
{
 QString origen1=origen.remove(' ');
 QString entera=origen1.left(uint(origen1.indexOf('.')));
 QString signo;
 // if (entera[1]=='-') {signo="-"; entera=entera.right(entera.length()-1);}
 if (entera.length()<4) return origen1;
 QString decimal=origen1.right(origen1.length()-uint(origen1.indexOf('.')));
 QString enterapuntos;
 int pasados=0;
 for (int veces=entera.length()-1;veces>=0;veces--)
     {
       pasados++;
       enterapuntos=enterapuntos.insert(0,entera[veces]);
       if (pasados==3 || pasados==6 || pasados==9)
           enterapuntos=enterapuntos.insert(0,',');
     }
 if (enterapuntos[0]==',') enterapuntos=enterapuntos.remove(0,1);
 if (enterapuntos[0]=='-' && enterapuntos[1]==',') enterapuntos=enterapuntos.remove(1,1);
 QString resultado;
 resultado=signo;
 resultado+=enterapuntos;
 resultado+=decimal;
 return resultado;
}

QString trad_fecha()
{
  return QObject::tr("fecha");
}

QString trad_usuario()
{
  return QObject::tr("usuario");
}

QString trad_asiento()
{
  return QObject::tr("asiento");
}

QString trad_cuenta()
{
  return QObject::tr("cuenta");
}

QString trad_concepto()
{
  return QObject::tr("concepto");
}

QString trad_documento()
{
  return QObject::tr("documento");
}

QString trad_debe()
{
  return QObject::tr("debe");
}

QString trad_haber()
{
  return QObject::tr("haber");
}

QString trad_diario()
{
  return QObject::tr("diario");
}

QString trad_pase()
{
  return QObject::tr("pase");
}

QString filtro_a_lingu(QString fuente)
{
  QString destino=fuente;
  destino.replace(QString("fecha"),trad_fecha());
  destino.replace(QString("usuario"),trad_usuario());
  destino.replace(QString("asiento"),trad_asiento());
  destino.replace(QString("cuenta"),trad_cuenta());
  destino.replace(QString("concepto"),trad_concepto());
  destino.replace(QString("documento"),trad_documento());
  destino.replace(QString("debe"),trad_debe());
  destino.replace(QString("haber"),trad_haber());
  destino.replace(QString("diario"),trad_diario());
  destino.replace(QString("pase"),trad_pase());
  return destino;
}


QString lingu_a_filtro(QString fuente)
{
  QString destino=fuente;
  destino.replace(trad_fecha(),QString("fecha"));
  destino.replace(trad_usuario(),QString("usuario"));
  destino.replace(trad_asiento(),QString("asiento"));
  destino.replace(trad_cuenta(),QString("cuenta"));
  destino.replace(trad_concepto(),QString("concepto"));
  destino.replace(trad_documento(),QString("documento"));
  destino.replace(trad_debe(),QString("debe"));
  destino.replace(trad_haber(),QString("haber"));
  destino.replace(trad_diario(),QString("diario"));
  destino.replace(trad_pase(),QString("pase"));
  return destino;
}

QString trayconfig(void)
{
    QString directorio;
    if (WINDOWS) directorio=directorio.fromLocal8Bit(getenv("USERPROFILE"));
      else directorio=getenv("HOME");
    QString nombredir="/.libroK";
     //nombredir += APPDIRNAME;
     nombredir[0]=QDir::separator();
     directorio+=nombredir;
     QString pasa;
     if (eswindows()) pasa=QFile::encodeName(directorio);
        else pasa=directorio;
     QDir d2(pasa);
     if (!d2.exists())
       {
        d2.mkdir(pasa);
        QString pasa2;
        if (eswindows()) pasa2=QFile::encodeName(traydoc());
           else pasa2=traydoc();
        QDir dirdoc(pasa2);
        QStringList filters;
        filters << "*.est" << "*.pln" << "*.qm";
        dirdoc.setNameFilters(filters);
        QStringList ficheros=dirdoc.entryList();
        for (int veces=0; veces<ficheros.count(); veces++)
            {
             QString cad=traydoc();
             cad.append(QDir::separator());
             // QString cfich=cfich.fromLocal8bit(ficheros.at(veces));
             QString cfich=ficheros.at(veces);
             cad+=cfich;
             QString destino=directorio;
             destino.append(QDir::separator());
             destino+=cfich;
             QString p;
             if (eswindows()) p=QFile::encodeName(cad);
                else p=cad;
             QFile fichero(p);
             if (eswindows()) fichero.copy(QFile::encodeName(destino));
                else fichero.copy(destino);
             // qWarning(destino.toAscii().constData());
             // QFile::copy ( cad, destino );
            }

        QObject *parent=NULL;
        QProcess *myProcess = new QProcess(parent);
        if (!WINDOWS)
         {
          QString cadexec="cp /usr/share/applications/Libro-Kuentas.desktop ";
          cadexec+=getenv("HOME");
          cadexec+="/Desktop";
          myProcess->start(cadexec);
          myProcess->waitForFinished ();
         }
        myProcess->~QProcess();

       }
     return directorio;
}

QString convapunto(QString cadena)
{
  return cadena.replace(',','.');
}


QString quitacomillas(QString cadena)
{
  QString resultado;
  resultado=cadena.remove(34); // comillas dobles
  resultado=resultado.remove(39); // comillas simples
  return resultado;
}

bool fechacorrespondeaejercicio(QDate fecha)
{
 if (ejerciciodelafecha(fecha).length()==0) return false;
 return true;
}

bool fechadejerciciocerrado(QDate fecha)
{
  QString ejercicio;
  ejercicio=ejerciciodelafecha(fecha);
  if (ejerciciocerrado(ejercicio)) return true;
  return false;
}

int existesubcuenta(QString codigo)
{
 QString ladescrip="";
 if (existecodigoplan(codigo,&ladescrip) && (int)codigo.length()==anchocuentas()
 	 && cadnumvalido(codigo)) return 1;
 if (unicoCodigoSubcuenta(&ladescrip,codigo) && !cadnumvalido(codigo)) return 1;
 else return 0;
}

QString encriptarTexto(QString texto)
{
	QString llave;
	QString host = getenv("USERNAME");
	QByteArray data,key;
	key=host.toAscii();
	data=texto.toAscii();
	for (int i=0,y=0;i<data.size();){
		llave[i]=data.at(i)+key.at(y);
		i++;
		y++;
		if (y == key.size())
			y=0;
	}
		
return llave;
}

QString desencriptarTexto(QString llave)
{
	QString texto;
	QString host = getenv("USERNAME");
	QByteArray data,key;
	key=host.toAscii();
	data.append(llave);
	for(int i=0,y=0; i<data.size();){
		data[i]=data.at(i)-key.at(y);
		i++;
		y++;
		if (y == key.size())
			y=0;
	}
		

return texto.fromAscii(data);
}

QString expandepunto(QString cadena,int anchocad)
{
  int indice=0,longitud=0,veces;
  if (!cadena.contains('.')) return cadena;
  while (cadena.contains('.'))
    {
     indice=cadena.indexOf('.');
     cadena.remove(indice,1);
    }
  longitud=cadena.length();
  for (veces=0;veces<anchocad-longitud;veces++)
       cadena.insert(indice,'0');
  return cadena;
}

QString formateanumero(double numero,bool comadecimal, bool decimales)
{

 int ndecimales=2;
 if (!decimales) ndecimales=0;
 QString cadena; 
 cadena.setNum(numero,'f',ndecimales);
 if (comadecimal)
     return convacoma(cadena);
 return cadena;

}

QString diario_apertura()
{
 return QObject::tr("APERTURA");
}

QString diario_general()
{
 return QObject::tr("GENERAL");
}

QString diario_no_asignado()
{
 return QObject::tr("SIN_ASIGNAR");
}

QString iva_mixto()
{
	return QObject::tr("MIXT");
}

QString diario_cierre()
{
 return QObject::tr("CIERRE");
}

QString previsiones()
{
 return QObject::tr("PREV");
}

QString diario_regularizacion()
{
 return QObject::tr("REGULARIZACION");
}


QString dirtrabajodefecto()
{
   QString directorio;
   if (WINDOWS) directorio=directorio.fromLocal8Bit(getenv("USERPROFILE"));
     else
       directorio=getenv("HOME");
   QString nombredir="/libroK";
   //nombredir += APPDIRNAME;
   nombredir[0]=QDir::separator();
   directorio+=nombredir;
   return directorio;
}


QString dirtrabajo(void)
 {
  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;
  if (eswindows()) nombrefichcompleto=QFile::encodeName(nombrefichcompleto);
  QFile ficheroini(nombrefichcompleto);
  QString qdirtrabajo;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("DIRECTORIO")==0) qdirtrabajo=contenido;
              }
            }
        ficheroini.close();
       }
  if (qdirtrabajo.length()==0) qdirtrabajo=dirtrabajodefecto();
  if (eswindows()) qdirtrabajo=QFile::encodeName(qdirtrabajo);
  QDir d(qdirtrabajo);
  if (!d.exists()) d.mkdir(qdirtrabajo);
  return qdirtrabajo;
}


int idiomaconfig(void)
 {
  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;
  if (eswindows()) nombrefichcompleto=QFile::encodeName(nombrefichcompleto);
  QFile ficheroini(nombrefichcompleto);
  int idioma=0;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("IDIOMA")==0) idioma=contenido.toInt();
              }
            }
        ficheroini.close();
       }
  return idioma;
}

QString fich_ingles()
{
 QString nombre=trayconfig();
 //if (DEBUG) nombre="../lang";
 nombre.append(QDir::separator());
 nombre+="librok_eng";
 if (eswindows()) nombre=QFile::encodeName(nombre);
 return nombre;
}


QString fich_catalan()
{
 QString nombre=trayconfig();
 //if (DEBUG) nombre="../lang";
 nombre.append(QDir::separator());
 nombre+="librok_cat";
 if (eswindows()) nombre=QFile::encodeName(nombre);
 return nombre;
}


QString filtracad(QString origen)
{
  QString destino;
  destino=origen;
  destino.replace(34,39); // covertimos a comillas simples
  destino.remove("\\");
  destino.remove("º");
  destino.remove("ª");
  destino.replace("#","\\#");
  destino.replace("$","\\$");
  destino.replace("%","\\%");
  destino.replace("^","\\^");
  destino.replace("&","\\&");
  destino.replace("{","\\{");
  destino.replace("}","\\}");
  destino.replace("~","\\~");
  destino.replace("_","\\_");
  destino.replace("<","\\flq");
  destino.replace(">","\\frq");
  return destino;
}


QString mcortaa(QString cadena, uint num)
{
    uint longitud=0;
    QString mays=cadena.toUpper();
    QString numeros="0123456789.,' ";
    float medias=0;
    for (int veces=0; veces<int(cadena.length()); veces++)
        {
	    longitud++;
	    if (cadena[veces]==mays[veces]
                && numeros.contains(cadena[veces])==0) 
	       {
		   medias=medias+0.5;
	       }
	    if (longitud+uint(medias)>=num)
	        {
    	         QString devuelve=cadena; devuelve.truncate(uint(veces));
                 return devuelve;
	        } 
	}
    return cadena;
}


QString programa_imprimir()
{

  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;
  
  if (eswindows()) nombrefichcompleto=QFile::encodeName(nombrefichcompleto);
  QFile ficheroini(nombrefichcompleto);
  QString qimprimir;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("IMPRIMIR")==0) qimprimir=contenido;
              }
            }
        ficheroini.close();
       }
  if (qimprimir.length()==0) qimprimir=programa_imprimir_defecto();
  return qimprimir;

}


QString programa_imprimir_defecto()
{
  return "kprinter";
}


QString visordvidefecto()
{
  if (WINDOWS) return "yap";
  return "kdvi";
}

QString visordvi()
{
  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;

  if (eswindows()) nombrefichcompleto=QFile::encodeName(nombrefichcompleto);
  QFile ficheroini(nombrefichcompleto);
  QString qvisor;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("VISORDVI")==0) qvisor=contenido;
              }
            }
        ficheroini.close();
       }
  if (qvisor.length()==0) qvisor=visordvidefecto();
  return qvisor;

}


bool filtrartexaxtivado()
{
  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;

  if (eswindows()) nombrefichcompleto=QFile::encodeName(nombrefichcompleto);
  QFile ficheroini(nombrefichcompleto);
  QString cnum;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("FILTRARTEX")==0) cnum=contenido;
              }
            }
        ficheroini.close();
       }
       // else { if ( WINDOWS ) return true; }
  if (cnum.length()==0) return false;

  return cnum.toInt();

}

QString adapta(QString cadena)
{
 if (eswindows()) return QFile::encodeName(cadena);
   else return cadena;
}

void filtratex(QString cadfich)
{

 QString qfichero=cadfich;
 QString fichmod=qfichero+"2";

 QFile escritura( adapta(fichmod) );

  if ( !escritura.open( QIODevice::WriteOnly ) ) return; 
  QTextStream streamescritura( &escritura );
  streamescritura.setCodec("UTF-8");


 QFile lectura( adapta(qfichero)  );
 
   if ( lectura.open(  QIODevice::ReadOnly  ) )
      {
        QTextStream streamlectura( &lectura );
        streamlectura.setCodec("UTF-8");
        QString linea;
         while ( !streamlectura.atEnd() )
	   {
	     linea = streamlectura.readLine(); // linea de texto, excluye '\n'
             if (linea.length()==0) continue;
             linea.replace(QObject::tr("á"),QString("\\'a"));
             linea.replace(QObject::tr("é"),QString("\\'e"));
             linea.replace(QObject::tr("í"),QString("\\'i"));
             linea.replace(QObject::tr("ó"),QString("\\'o"));
             linea.replace(QObject::tr("ú"),QString("\\'u"));
             linea.replace(QObject::tr("Á"),QString("\\'A"));
             linea.replace(QObject::tr("É"),QString("\\'E"));
             linea.replace(QObject::tr("Í"),QString("\\'I"));
             linea.replace(QObject::tr("Ó"),QString("\\'O"));
             linea.replace(QObject::tr("Ú"),QString("\\'U"));
             linea.replace(QObject::tr("ñ"),QString("\\~n"));
             linea.replace(QObject::tr("Ñ"),QString("\\~N"));
             linea.replace(QObject::tr("à"),QString("\\`a"));
             linea.replace(QObject::tr("è"),QString("\\`e"));
             linea.replace(QObject::tr("ì"),QString("\\`i"));
             linea.replace(QObject::tr("ò"),QString("\\`o"));
             linea.replace(QObject::tr("ù"),QString("\\`u"));
             linea.replace(QObject::tr("À"),QString("\\`A"));
             linea.replace(QObject::tr("È"),QString("\\`E"));
             linea.replace(QObject::tr("Ì"),QString("\\`I"));
             linea.replace(QObject::tr("Ò"),QString("\\`O"));
             linea.replace(QObject::tr("Ù"),QString("\\`U"));
             linea.replace(QObject::tr("ã"),QString("\\~a"));
             linea.replace(QObject::tr("ẽ"),QString("\\~e"));
             linea.replace(QObject::tr("ĩ"),QString("\\~i"));
             linea.replace(QObject::tr("õ"),QString("\\~o"));
             linea.replace(QObject::tr("ũ"),QString("\\~u"));
             linea.replace(QObject::tr("Ã"),QString("\\~A"));
             linea.replace(QObject::tr("Ẽ"),QString("\\~E"));
             linea.replace(QObject::tr("Ĩ"),QString("\\~I"));
             linea.replace(QObject::tr("Õ"),QString("\\~O"));
             linea.replace(QObject::tr("Ũ"),QString("\\~U"));
             linea.replace(QObject::tr("â"),QString("\\^a"));
             linea.replace(QObject::tr("ê"),QString("\\^e"));
             linea.replace(QObject::tr("î"),QString("\\^i"));
             linea.replace(QObject::tr("ô"),QString("\\^o"));
             linea.replace(QObject::tr("û"),QString("\\^u"));
             linea.replace(QObject::tr("Â"),QString("\\^A"));
             linea.replace(QObject::tr("Ê"),QString("\\^E"));
             linea.replace(QObject::tr("Î"),QString("\\^I"));
             linea.replace(QObject::tr("Ô"),QString("\\^O"));
             linea.replace(QObject::tr("Û"),QString("\\^U"));
             linea.replace(QObject::tr("ç"),QString("\\c c"));
             linea.replace(QObject::tr("Ç"),QString("\\c C"));
             streamescritura << linea << "\n";
           }
        lectura.close();
       } else return;
  escritura.close();

 //queda copiar escritura en lectura y borrar escritura
 QDir directorio(adapta(dirtrabajo()));
 directorio.remove(adapta(qfichero));
 directorio.rename(adapta(fichmod),adapta(qfichero));

}



bool haycomadecimal()
{
  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;

  QFile ficheroini(adapta(nombrefichcompleto));
  QString cnum;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("ESTILONUMERICO")==0) cnum=contenido;
              }
            }
        ficheroini.close();
       }
  if (cnum.length()==0) return true;

  return cnum.toInt();

}


bool haydecimales()
{
  QString nombrefichcompleto=trayconfig();
  QString nombre="/libroK.cfg";
  //nombre += APPDIRNAME;
  //nombre += ".cfg";
  nombre[0]=QDir::separator();
  nombrefichcompleto+=nombre;

  QFile ficheroini(adapta(nombrefichcompleto));
  QString cnum;

   if ( ficheroini.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &ficheroini );
        stream.setCodec("UTF-8");
        QString linea,variable,contenido;
        while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            // analizamos la linea de texto
            if (linea.contains('=')) {
               variable=linea.section('=',0,0);
               contenido=linea.section('=',1,1);
               if (variable.compare("SINDECIMALES")==0) cnum=contenido;
              }
            }
        ficheroini.close();
       }
  if (cnum.length()==0) return true;

  return !cnum.toInt();

}


QString formateanumerosep(double numero,bool comadecimal, bool decimales)
{
 QString cad; 
 cad.setNum(numero,'f',2);
 if (comadecimal) cad=convacoma(cad);

 if (comadecimal)
     {
       if (decimales)
           return puntuanumerocomadec(cad);
        else
             {
               QString cad2=puntuanumerocomadec(cad);
               cad2.truncate(cad2.length()-3);
               return cad2;
             }
     }
     else
        {
          if (decimales)
              return puntuanumeropuntodec(cad);
           else
                {
                  QString cad2=puntuanumeropuntodec(cad);
                  cad2.truncate(cad2.length()-3);
                  return cad2;
                }
        }

}

/*bool parentesisbalanceados(QString cadena)
{
  evaluadorparentesis evparentesis;
  evparentesis.inicializa(cadena);
  if (!evparentesis.okparentesis()) return 0;
  return 1;
}
*/
QString cadenamedia()
{
 return QObject::tr("MEDIA");
}

QString cadpositivo()
{
  return QObject::tr(";POSITIVO");
}


QString tipoNumerico()
{
  return QObject::tr("Numérico");
}

QString tipoFecha()
{
  return QObject::tr("Fecha");
}

QString tipoCaracteres()
{
  return QObject::tr("Caracteres");
}

QString tipoSubcuenta()
{
  return QObject::tr("Subcuenta");
}

QString tipoCI()
{
  return QObject::tr("CI");
}


QString tipoDEBE()
{
  return QObject::tr("DEBE");
}

QString tipoHABER()
{
  return QObject::tr("HABER");
}



bool chequeaformula(QString formula)
{
  if (formula.length()==0) return 1;
  //if (!parentesisbalanceados(formula)) return 0;
  if (formula.contains("(+")) return 0;
  if (formula.contains("(/")) return 0;
  if (formula.contains("(*")) return 0;
  if (formula.contains("/)")) return 0;
  if (formula.contains("*)")) return 0;
  if (formula.contains("+)")) return 0;
  if (formula.contains("-)")) return 0;
  if (formula.contains("()")) return 0;
  if (formula.contains(")(")) return 0;
  if (formula.contains("++")) return 0;
  if (formula.contains("+-")) return 0;
  if (formula.contains("+*")) return 0;
  if (formula.contains("+/")) return 0;
  if (formula.contains("--")) return 0;
  if (formula.contains("-+")) return 0;
  if (formula.contains("-*")) return 0;
  if (formula.contains("-/")) return 0;
  if (formula.contains("**")) return 0;
  if (formula.contains("*+")) return 0;
  if (formula.contains("*/")) return 0;
  if (formula.contains("//")) return 0;
  if (formula.contains("/+")) return 0;
  if (formula.contains("/*")) return 0;
  if (formula.endsWith("+")) return 0;
  if (formula.endsWith("-")) return 0;
  if (formula.endsWith("/")) return 0;
  if (formula.endsWith("*")) return 0;
  if (formula.endsWith("(")) return 0;
  
  if (formula.contains("][")) return 0;
  if (formula.contains("[[")) return 0;
  if (formula.contains("]]")) return 0;
  if (formula.contains("[]")) return 0;
    
  if (formula.indexOf(']',0)<formula.indexOf('[',0)) return 0;
  
  int indice=0;
  while (indice<formula.length() && formula.indexOf('[',indice)>=0)
    {
             int base=formula.indexOf('[',indice);
             if (formula.indexOf(']',indice)<0) return 0;
             if (base+1<formula.length() && formula.indexOf('[',base+1)>=0)
                  if (formula.indexOf('[',base+1)<formula.indexOf(']',base)) return 0; 
             indice=formula.indexOf(']',indice)+1;
             if (indice<formula.length() && formula.indexOf(']',indice)>=0 && 
             	 (formula.indexOf(']',indice)<formula.indexOf('[',indice) || formula.indexOf('[',indice)<0))
                 return 0;
    }

// hacer lo propio con las llaves  
  if (formula.contains("}{")) return 0;
  if (formula.contains("{{")) return 0;
  if (formula.contains("}}")) return 0;
  if (formula.contains("{}")) return 0;

  if (formula.indexOf('}',0)<formula.indexOf('{',0)) return 0;
  
  indice=0;
  while (indice<formula.length() && formula.indexOf('{',indice)>=0)
    {
      int base=formula.indexOf('{',indice);
      if (formula.indexOf('}',indice)<0) return 0;
      if (base+1<formula.length() &&formula.indexOf('{',base+1)>=0)
	  if (formula.indexOf('{',base+1)<formula.indexOf('}',base)) return 0; 
      indice=formula.indexOf('}',indice)+1;
      if (indice<formula.length() && formula.indexOf('}',indice)>=0 && 
	  (formula.indexOf('}',indice)<formula.indexOf('{',indice) || formula.indexOf('{',indice)<0)) return 0;
    }

// -------------------------------------------------------------  
  QString cadpru;
  cadpru=formula;
  int final;
  int inicio;
  indice=0;
  while (indice<cadpru.length())
      {
         if (cadpru[indice]=='[')
           {
              inicio=indice;
              final=inicio;
              while (final<cadpru.length() && cadpru[final]!=']') final++;
              cadpru.remove(inicio,final-inicio+1);
              continue;
           }
        if (cadpru[indice]=='{')
           {
              inicio=indice;
              final=inicio;
              while (final<cadpru.length() && cadpru[final]!='}') final++;
              cadpru.remove(inicio,final-inicio+1);
              continue;
           }
       indice++;
      }
    
  QString cadcods="()+-/*0123456789.";
  
  indice=0;
  cadpru.remove(' ');
  while (indice<cadpru.length())
      {
        if (!cadcods.contains(cadpru[indice])) return 0;
        indice++;
      }
 
  return 1;   

}

bool cadnumvalido(QString cadnum)
{
  QString num;
  num=cadnum.trimmed();
  if(num.length()==0) return FALSE;
  QString digitos="0123456789.";
  for (int veces=0;veces<num.length();veces++)
    {
      if (!digitos.contains(num[veces])) return FALSE;
    }
  if (num.count('.')>1) return FALSE;
  return TRUE;
}

bool cadfechavalida(QString cadfecha)
{
  // formato dd/mm/aaaa

  // 1 comprobamos longitud
  if (cadfecha.length()!=10) return FALSE;

  // comprobamos separadores
  if (cadfecha[2]!='/' && cadfecha[2]!='-' &&cadfecha[2]!='.') return FALSE;

  if (cadfecha[2]=='/' && cadfecha[5]!='/') return FALSE;
  if (cadfecha[2]=='-' && cadfecha[5]!='-') return FALSE;
  if (cadfecha[2]=='.' && cadfecha[5]!='.') return FALSE;

  // comprobaciones básicas
  // en las demás posiciones deben de haber números
  QString numeros="0123456789";
  if (!numeros.contains(cadfecha[0])) return FALSE;
  if (!numeros.contains(cadfecha[1])) return FALSE;
  if (!numeros.contains(cadfecha[3])) return FALSE;
  if (!numeros.contains(cadfecha[4])) return FALSE;
  if (!numeros.contains(cadfecha[6])) return FALSE;
  if (!numeros.contains(cadfecha[7])) return FALSE;
  if (!numeros.contains(cadfecha[8])) return FALSE;
  if (!numeros.contains(cadfecha[9])) return FALSE;

  // días, meses y años han de ser enteros positivos
  int dia,mes,anyo;
  QString cadextract;

  cadextract=cadfecha.mid(0,2);
  dia=cadextract.toInt();

  cadextract=cadfecha.mid(3,2);
  mes=cadextract.toInt();

  cadextract=cadfecha.mid(6,4);
  anyo=cadextract.toInt();
  
  if (QDate::isValid(anyo,mes,dia)) return TRUE;
    else return FALSE;

}

QString ciamort()
{
 return QObject::tr("AMR");
}

QString cadmes(int mes)
{
  switch (mes)
    {
      case 1 : return QObject::tr("ENERO");
         break;
      case 2 : return QObject::tr("FEBRERO");
         break;
      case 3 : return QObject::tr("MARZO");
         break;
      case 4 : return QObject::tr("ABRIL");
         break;
      case 5 : return QObject::tr("MAYO");
         break;
      case 6 : return QObject::tr("JUNIO");
         break;
      case 7 : return QObject::tr("JULIO");
         break;
      case 8 : return QObject::tr("AGOSTO");
         break;
      case 9 : return QObject::tr("SEPTIEMBRE");
         break;
      case 10 : return QObject::tr("OCTUBRE");
         break;
      case 11 : return QObject::tr("NOVIEMBRE");
         break;
      case 12 : return QObject::tr("DICIEMBRE");
         break;
    }
 return "";
}

int imprimelatex(QString qfichero)
{
    if (WINDOWS) return consultalatex2(qfichero);
    QString pasafich=dirtrabajo();
    pasafich.append(QDir::separator());
    pasafich.append(qfichero);
    pasafich.append(".tex");
    if (filtrartexaxtivado()) filtratex(pasafich);

    QString fichero=qfichero;

    QString cadexec="latex";
    QString cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;

    QObject *parent=NULL;

     QStringList arguments;
     arguments << adapta(cadarg);

     QProcess *myProcess = new QProcess(parent);

     myProcess-> setWorkingDirectory(adapta(dirtrabajo()));

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished (60000))
       {
         myProcess->~QProcess();
         return 1;
       }

    arguments.clear();
    cadexec="dvips";
    arguments << "-Pcmz";
    cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;
    cadarg+".dvi";
    arguments << adapta(cadarg);
    arguments << "-o";
    QString cadfich=qfichero; cadfich.append(".ps");
    arguments << cadfich;
    myProcess->start(cadexec,arguments);

    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 2;
       }
    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 2;
       }


    arguments.clear();
    cadexec=programa_imprimir();
    if (programa_imprimir()==programa_imprimir_defecto())
        {
         arguments << "--caption";
         arguments << "Libro-Kuentas";
         cadarg=dirtrabajo();
         cadarg.append(QDir::separator());
         cadarg+=fichero;
         cadarg+=".ps";
         arguments << adapta(cadarg);
         // arguments << "&";
         myProcess->start(cadexec,arguments);
        }
     else
        {
          cadexec+=" ";
          cadexec+=dirtrabajo();
          cadexec.append(QDir::separator());
          cadexec+=fichero;
          cadexec+=".ps";
          myProcess->start(adapta(cadexec));
        }
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 3;
       }

  myProcess->waitForFinished(-1);

  myProcess->~QProcess();

  return 0;
}


/*int imprimeLatexDialog(QString qfichero)
{
    if (WINDOWS) return consultalatex2(qfichero);
    QString pasafich=dirtrabajo();
    pasafich.append(QDir::separator());
    pasafich.append(qfichero);
    pasafich.append(".tex");
    if (filtrartexaxtivado()) filtratex(pasafich);

    QString fichero=qfichero;

    QString cadexec="latex";
    QString cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;

    QObject *parent=NULL;

     QStringList arguments;
     arguments << adapta(cadarg);

     QProcess *myProcess = new QProcess(parent);

     myProcess-> setWorkingDirectory(adapta(dirtrabajo()));

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished (60000))
       {
         myProcess->~QProcess();
         return 1;
       }

     //segunda pasada
     //myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished (60000))
       {
         myProcess->~QProcess();
         return 1;
       }


    arguments.clear();
    cadexec="dvips";
    arguments << "-Pcmz";
    cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;
    cadarg+".dvi";
    arguments << adapta(cadarg);
    arguments << "-o";
    QString cadfich=qfichero; cadfich.append(".ps");
    arguments << cadfich;
    myProcess->start(cadexec,arguments);

    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 2;
       }
    if (!myProcess->waitForFinished (60000))
       {
         myProcess->~QProcess();
         return 2;
       }


    arguments.clear();
    cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;
    cadarg+=".ps";
    QPrinter *printer = new QPrinter;
    QTextDocument text = new QTextDocument(cadarg);
     QPrintDialog printDialog(printer, parent);
     if ( printDialog.exec() == QDialog::Accepted ) {
         QPainter pp(printer);
         ui.GPlot->render(&pp);
     }
    
    
  myProcess->waitForFinished(-1);

  myProcess->~QProcess();
  return 0;
}*/

/*int consultalatex(QString qfichero)
{
    QString pasafich=dirtrabajo();
    pasafich.append(QDir::separator());
    pasafich.append(qfichero);
    pasafich.append(".tex");
    if (filtrartexaxtivado()) filtratex(pasafich);

    QString fichero=qfichero;

    QString cadexec="latex";
    QString cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;

    QObject *parent=NULL;

     QStringList arguments;
     arguments << adapta(cadarg);

     QProcess *myProcess = new QProcess(parent);

     myProcess-> setWorkingDirectory(adapta(dirtrabajo()));

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished (60000))
       {
         myProcess->~QProcess();
         return 1;
       }


    arguments.clear();
    cadexec=visordvi();

    cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;
    cadarg+=".dvi";
    arguments << adapta(cadarg);
    //arguments << "&";

    myProcess->start(cadexec,arguments);

    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 2;
       }

   myProcess->waitForFinished(-1);

   myProcess->~QProcess();

  return 0;
}*/


int consultalatex2(QString qfichero)
{
    QString pasafich=dirtrabajo();
    pasafich.append(QDir::separator());
    pasafich.append(qfichero);
    pasafich.append(".tex");
    if (filtrartexaxtivado()) filtratex(pasafich);

    QString fichero=qfichero;

    QString cadexec="latex";
    QString cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;

    QObject *parent=NULL;

     QStringList arguments;
     arguments << adapta(cadarg);

     QProcess *myProcess = new QProcess(parent);

     myProcess-> setWorkingDirectory(adapta(dirtrabajo()));

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished (60000))
       {
         myProcess->~QProcess();
         return 1;
       }

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 1;
       }


    arguments.clear();
    cadexec=visordvi();

    cadarg=dirtrabajo();
    cadarg.append(QDir::separator());
    cadarg+=fichero;
    cadarg+=".dvi";
    arguments << adapta(cadarg);
    
    myProcess->start(cadexec,arguments);

    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 2;
       }

   myProcess->disconnect();


  return 0;
}


int consultalatex2fichabs(QString qfichero)
{
    if (filtrartexaxtivado()) filtratex(qfichero);

    QString fichero=qfichero;
    fichero.truncate(qfichero.length()-4);
    QString cadarg=fichero;

    QObject *parent=NULL;

     QStringList arguments;
     arguments << adapta(cadarg);

     QString cadexec="latex";
     QProcess *myProcess = new QProcess(parent);

     myProcess-> setWorkingDirectory(adapta(dirtrabajo()));

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 1;
       }

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 1;
       }


    arguments.clear();
    cadexec=visordvi();

    cadarg=fichero;
    cadarg+=".dvi";
    arguments << adapta(cadarg);

    myProcess->start(cadexec,arguments);

    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 2;
       }

   //myProcess->waitForFinished(-1);

   //myProcess->~QProcess();
	myProcess->disconnect();
  return 0;
}

int generapdffichabs(QString qfichero)
{
    if (filtrartexaxtivado()) filtratex(qfichero);

    QString fichero=qfichero;
    fichero.truncate(qfichero.length()-4);
    QString cadarg=fichero;

    QObject *parent=NULL;

     QStringList arguments;
     arguments << adapta(cadarg);

     QString cadexec="latex";
     QProcess *myProcess = new QProcess(parent);

     myProcess-> setWorkingDirectory(adapta(dirtrabajo()));

     myProcess->start(cadexec,arguments);

    // system(cadexec);
     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }

    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 1;
       }

     myProcess->start(cadexec,arguments);

    // system(cadexec);
    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 1;
       }
    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 1;
       }


    arguments.clear();
    cadexec="dvipdf";
    if (eswindows()) cadexec="dvipdfm";

    cadarg=adapta(fichero);
    cadarg+=".dvi";
    arguments << cadarg;
    // arguments << "&";

    myProcess->start(cadexec,arguments);

    if (!myProcess->waitForStarted ())
       {
         myProcess->~QProcess();
         return 2;
       }

    if (!myProcess->waitForFinished ())
       {
         myProcess->~QProcess();
         return 2;
       }

  myProcess->~QProcess();
  return 0;
}

QString traydoc(void)
{
  // return trayconfig();
  QString cadena;
  if (!WINDOWS)
  {
  	cadena = "/usr/local/share/doc/libroK";
  	//cadena+= APPDIRNAME;
  	return cadena;
  }
   else
        {
         cadena=cadena.fromLocal8Bit(getenv("ProgramFiles"));
         cadena+="\\libroK\\doc";
         //cadena+=APPDIRNAME;
         //cadena+="\\doc";
         return cadena;
        }
}
 
QString traynombrefichayuda(void)
 {
     QString nombrefich;
     nombrefich=traydoc();
     if (WINDOWS) nombrefich+="\\manual\\index.html";
        else nombrefich+="/manual/index.html";
     return nombrefich;
 }


/*bool importanuevoplan(QString qfichero)
{
  QFile fichero(adapta(qfichero));
  if (!fichero.exists()) return false;
  //QSqlQuery query;
   if ( fichero.open( QIODevice::ReadOnly ) ) 
     {
        QTextStream stream( &fichero );
        stream.setCodec("UTF-8");
        QString linea;
         while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            QString codigo,descripcion;
            codigo=linea.section('\t',0,0);
            descripcion=linea.section('\t',1,1);
            QString cad1="insert into nuevoplan (codigo,descripcion) values ('";
            cad1+=codigo;
            cad1+="','";
            cad1+=descripcion;
            cad1+="');";
            ejecutarSQL(cad1);	    
           }
         fichero.close();
      } else return false;
   return true;
}

void borraplannuevo()
{
 QString cadquery;
 cadquery="delete from nuevoplan;";
 ejecutarSQL(cadquery);
}



int subgrupocongruponuevoplan(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from nuevoplan where codigo = ";
 cadquery+="substring('";
 cadquery+=cadena;
 cadquery+="' from 1 for 1);";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           return 1;
           }
      }
 return 0;
}


int cuentaconsubgruponuevoplan(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from nuevoplan where codigo = ";
 cadquery+="substring('";
 cadquery+=cadena;
 cadquery+="' from 1 for 2);";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           return 1;
           }
      }
 return 0;
}


int codigoconcuenta3digitosnuevoplan(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from nuevoplan where codigo = ";
 cadquery+="substring('";
 cadquery+=cadena;
 cadquery+="' from 1 for 3);";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           return 1;
           }
      }
 return 0;
}

void guardacambiosplannuevo(QString codigo,QString descripcion)
{
 QString cadquery;
 cadquery="UPDATE nuevoplan SET descripcion='";
 cadquery+=descripcion;
 cadquery+="' WHERE codigo='";
 cadquery+=codigo;
 cadquery+="';";
 ejecutarSQL(cadquery);

}

int existecodigoplannuevo(QString cadena,QString *qdescrip)
{
 QString cadquery;
 cadquery="SELECT codigo,descripcion from nuevoplan where codigo = '";
 cadquery+=cadena;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           *qdescrip=query.value(1).toString();
           return 1;
           }
      }
 return 0;
}


void insertaenplannuevo(QString codigo,QString descripcion)
{
 QString cadena;
 if (!existecodigoplannuevo(codigo,&cadena))
     {
      QString cadquery;
      cadquery="INSERT INTO nuevoplan (codigo,descripcion) VALUES ('";
      cadquery+=codigo;
      cadquery+="','";
      cadquery+=descripcion;
      cadquery+="');";
      ejecutarSQL(cadquery);
     }
}

int itemplaneliminadonuevo(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT codigo from nuevoplan where char_length(codigo) > ";
 cadquery+="char_length('";
 cadquery+=qcodigo;
 cadquery+="') and substring(codigo from 1 for char_length('";
 cadquery+=qcodigo;
 cadquery+="'))='";
 cadquery+=qcodigo;
 cadquery+="';";
 
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           return 0;
         }
    }

cadquery="delete from nuevoplan where codigo = '";
cadquery+=qcodigo;
cadquery+="';";
query.exec(cadquery);

return 1;
}


QString descripcioncuentanuevoplan(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT descripcion from nuevoplan where codigo = '";
 cadquery+=qcodigo;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.next() )
    {
     return query.value(0).toString();
    }
 return QString("");
}*/

/*bool codsubdivisplannuevo(QString qcodigo)
{
 // evaluamos si el código suministrado posee subcódigos 
 // que no sean subcuentas
 QString cadquery="SELECT codigo from nuevoplan where char_length(codigo) > ";
 cadquery+="char_length('";
 cadquery+=qcodigo;
 cadquery+="') and substring(codigo from 1 for char_length('";
 cadquery+=qcodigo;
 cadquery+="'))='";
 cadquery+=qcodigo;
 cadquery+="' and char_length(codigo)<";
 QString cadnum;
 cadnum.setNum(anchocuentas());
 cadquery+=cadnum;
 
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           return true;
         }
    }
 return false;
}
*/

QString fsplash()
{
    QString fichsplash;
    if (!WINDOWS)
     {
      fichsplash="/usr/local/share/libroK";
      //fichsplash+=APPDIRNAME;
      fichsplash+="/splash.png";
     }
      else 
           {
            fichsplash=fichsplash.fromLocal8Bit(getenv("ProgramFiles"));
            fichsplash+="\\libroK\\splash.png";
            //fichsplash+=APPDIRNAME;
            //fichsplash+="\\splash.png";
           }
    return fichsplash;
}

bool eswindows()
{
  return WINDOWS;
}

QString windirprogram()
{
 QString fichero=fichero.fromLocal8Bit(getenv("ProgramFiles"));
 return fichero;
}


/*bool exportarasmodelo(QString nombre,QString nfich)
{

  QFile fichero( adapta(nfich)  );

  if ( !fichero.open( QIODevice::WriteOnly ) ) return false;

  QTextStream stream( &fichero );
  stream.setCodec("UTF-8");

  QSqlDatabase bd=QSqlDatabase::database ();
  QString acontrolador;
  acontrolador= bd.driverName();

  QString cadena="select asientomodelo,fecha from cab_as_modelo where asientomodelo='";
  cadena+=nombre;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
       while (query.next())
          {
              stream << query.value(0).toString() << "\t";
              stream << query.value(1).toString() << "\n";
         }

// ------------------------------------------------------------------------------------------------------   
  // ahora vamos a por las variables del asiento modelo
  cadena="select variable,tipo,descripcion from var_as_modelo where asientomodelo='";
  cadena+=nombre;
  cadena+="'";
   query.exec(cadena);
   if ( query.isActive() )
       while (query.next())
          {
              stream << query.value(0).toString() << "\t";
              stream << query.value(1).toString() << "\t";
              stream << query.value(2).toString() << "\n";
         }

 stream << "#DETALLE#\n";

 cadena="select cuenta,concepto,expresion,d_h,ci,baseiva,cuentafra,cuentabaseiva,claveiva,documento ";
 cadena+="from det_as_modelo where asientomodelo='";
 cadena+=nombre;
 cadena+="'";
   query.exec(cadena);
   if ( query.isActive() )
       while (query.next())
          {
             stream << query.value(0).toString() << "\t";
             stream << query.value(1).toString() << "\t";
             stream << query.value(2).toString() << "\t";
             stream << query.value(3).toString() << "\t";
             stream << query.value(4).toString() << "\t";
             stream << query.value(5).toString() << "\t";
             stream << query.value(6).toString() << "\t";
             stream << query.value(7).toString() << "\t";
             stream << query.value(8).toString() << "\t";
             stream << query.value(9).toString() << "\n";
          }
   fichero.close();
  return true;
}


int importarasmodelo(QString nombre)
{
  QFile fichero(adapta(nombre));
  if (!fichero.exists()) return false;

  QString titulo;
  QTextStream stream( &fichero );
  stream.setCodec("UTF-8");
  QString linea;
  if ( fichero.open( QIODevice::ReadOnly ) )
     {
       linea = stream.readLine(); // linea de texto excluyendo '\n'
       titulo=linea.section('\t',0,0);
       fichero.close();
     }
   else return 0;

  // buscamos el nombre
  QString cadena="select asientomodelo from cab_as_modelo where asientomodelo='";
  cadena+=titulo;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return 2;
         }
    }
 

   if ( fichero.open( QIODevice::ReadOnly ) ) 
     {
        QTextStream stream( &fichero );
        stream.setCodec("UTF-8");
        QString linea;
            linea = stream.readLine(); // linea de texto excluyendo '\n'

            QString asientomodelo,fecha;
            asientomodelo=linea.section('\t',0,0);
            fecha=linea.section('\t',1,1);
            QString cad1="insert into cab_as_modelo (asientomodelo,fecha"
	                         ") values ('";
            cad1+=asientomodelo;
            cad1+="','";
            cad1+=fecha;
            cad1+="');";
            // QMessageBox::information( this, tr("Importar estado contable"),cad1);   
            ejecutarSQL(cad1);	    

   // importamos el resto de fichero

         while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            if (linea=="#DETALLE#") break;
            QString variable,tipo,descripcion;
            variable=linea.section('\t',0,0);
            tipo=linea.section('\t',1,1);
            descripcion=linea.section('\t',2,2);
            QString cad1="insert into var_as_modelo (asientomodelo,"
		       "variable,tipo,descripcion) values ('" ;
            cad1+=asientomodelo;
            cad1+="','";
            cad1+=variable;
            cad1+="','";
            cad1+=tipo;
            cad1+="','";
            cad1+=descripcion;
            cad1+="');";
            // QMessageBox::information( this, tr("Importar estado contable"),cad1);   
            ejecutarSQL(cad1);	    
           }

         while ( !stream.atEnd() ) {
            linea = stream.readLine(); // linea de texto excluyendo '\n'
            QString cuenta,concepto,expresion,d_h,ci,baseiva,cuentafra,cuentabaseiva,claveiva,documento;
            cuenta=linea.section('\t',0,0);
            concepto=linea.section('\t',1,1);
            expresion=linea.section('\t',2,2);
            d_h=linea.section('\t',3,3);
            ci=linea.section('\t',4,4);
            baseiva=linea.section('\t',5,5);
            cuentafra=linea.section('\t',6,6);
            cuentabaseiva=linea.section('\t',7,7);
            claveiva=linea.section('\t',8,8);
            documento=linea.section('\t',9,9);
            QString cad1="insert into det_as_modelo (asientomodelo,"
		       "cuenta,concepto,expresion,d_h,ci,baseiva,cuentafra,"
                       "cuentabaseiva,claveiva,documento) values ('" ;
            cad1+=asientomodelo;
            cad1+="','";
            cad1+=cuenta;
            cad1+="','";
            cad1+=concepto;
            cad1+="','";
            cad1+=expresion;
            cad1+="','";
            cad1+=d_h;
            cad1+="','";
            cad1+=ci;
            cad1+="','";
            cad1+=baseiva;
            cad1+="','";
            cad1+=cuentafra;
            cad1+="','";
            cad1+=cuentabaseiva;
            cad1+="','";
            cad1+=claveiva;
            cad1+="','";
            cad1+=documento;
            cad1+="');";
            // QMessageBox::information( this, tr("Importar estado contable"),cad1);   
            ejecutarSQL(cad1);	    
           }

         fichero.close();
      }

 return 1;
}*/



QString noejercicio()
{
 return "- -";
}

QString comandodescrip()
{
 return QObject::tr("DESCRIP");
}

double calculaValor( QString calculo )
{
   //calcula el valor de un string con sumas, restas y multiplicaciones
   double valor = 0;
   QString valores = convapunto(calculo);
   valores.replace('-',"+-");
   if (valores.contains('/') || valores.contains(':')){
	   return -1;
   }
   if (!valores.contains('+') && !valores.contains('*')){
	   return valores.toDouble();
	   
   }else{
   	QStringList val = valores.split('+',QString::SkipEmptyParts);
   	QStringList mas;
   	valor = 1;
    for (int i = 0; i < val.size(); ++i) {
     	mas = val.at(i).split('*',QString::SkipEmptyParts);
     	for (int j = 0; j < mas.size(); ++j){
     		if (mas.at(j) > 0){
     			valor*=mas.at(j).toDouble();
			} 
    	}
    	val[i]=valores.setNum(valor);
    	valor = 1;
    }
    valor = 0;
    for (int i = 0; i < val.size(); ++i){
    	if (val.at(i) > 0) valor+=val.at(i).toDouble();
   	}
   	return valor;
   }
   return 0;
}

QColor randomColor(bool trans)
{
     int red = int(0 + 255.0*qrand()/(RAND_MAX+1.0));
     int green = int(0 + 255.0*qrand()/(RAND_MAX+1.0));
     int blue = int(0 + 255.0*qrand()/(RAND_MAX+1.0));
     int alpha;
     if (trans){
     	alpha = int(91 + 100.0*qrand()/(RAND_MAX+1.0));
     }else{
     	alpha = 255;
      }
     return QColor(red, green, blue, alpha);
}


