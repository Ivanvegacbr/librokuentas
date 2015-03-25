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

#include "cuadimprimayor.h"
#include "funciones.h"
#include "basedatos.h"
#include "buscasubcuenta.h"
#include "pidenombre.h"
 
cuadimprimayor::cuadimprimayor(bool concomadecimal, bool condecimales) : QDialog() {
  ui.setupUi(this);
  comadecimal=concomadecimal;
  decimales=condecimales;
  //QDate fechaactual;
  QString cadfechaactual;
  cadfechaactual=fechaactual.currentDate().toString("yyyy.MM.dd");
  c = new consmayor(comadecimal,decimales);
  ui.inicialdateEdit->setDate( selectAperturaejerciciosaperturacierre( cadfechaactual, cadfechaactual ) );
  ui.finaldateEdit->setDate( selectCierreejerciciosaperturacierre( cadfechaactual, cadfechaactual ) );

  connect(ui.genfactura,SIGNAL(clicked()),SLOT(botonGenFactura()));
 connect(ui.subcuentalineEdit,SIGNAL(returnPressed()),SLOT(finedicsubcuenta()));
 connect(ui.subcuentapushButton,SIGNAL(clicked()),SLOT(botonsubcuentapulsado()));
 connect(ui.imprimepushButton,SIGNAL(clicked()),SLOT(botonimprimepulsado()));
 connect(ui.previsualizapushButton,SIGNAL(clicked()),SLOT(botonprevisualizapulsado()));
 connect(ui.subcuentalineEdit,SIGNAL(textChanged(QString)),SLOT(ctainicialcambiada()));
 connect(ui.finalpushButton,SIGNAL(clicked()),SLOT(botonctafinalpulsado()));
 connect(ui.finallineEdit,SIGNAL(returnPressed()),SLOT(finedicfinsubcuenta()));
 
}


void cuadimprimayor::ctaexpandepunto()
{
  ui.subcuentalineEdit->setText(expandepunto(ui.subcuentalineEdit->text(),anchocuentas()));
}


void cuadimprimayor::finedicsubcuenta()
{
 ctaexpandepunto();
 if (ui.subcuentalineEdit->text().length()<anchocuentas()) botonsubcuentapulsado();
}


void cuadimprimayor::botonsubcuentapulsado()
{

    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.subcuentalineEdit->text());
    labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();
    if (existesubcuenta(cadena2)) ui.subcuentalineEdit->setText(cadena2);
       else ui.subcuentalineEdit->setText("");
    delete labusqueda;

}


void cuadimprimayor::pasadatos( QString qsubcuenta, QDate qfecha )
{
   ui.subcuentalineEdit->setText(qsubcuenta);
   ui.finallineEdit->setText(qsubcuenta);
   QString ejercicio=ejerciciodelafecha(qfecha);
   QDate fechaini=inicioejercicio(ejercicio);
   QDate fechafin=finejercicio(ejercicio);
   ui.inicialdateEdit->setDate(fechaini);
   ui.finaldateEdit->setDate(fechafin);
}


void cuadimprimayor::fechasok()
{
   ctaexpandepunto();
    if (ejerciciodelafecha(ui.inicialdateEdit->date())!=ejerciciodelafecha(ui.finaldateEdit->date())
	&&(escuentadegasto(ui.subcuentalineEdit->text()) || 
	   escuentadeingreso(ui.subcuentalineEdit->text()) ))
	{
	       QMessageBox::warning( this, tr("Consultas de Mayor"),
				 tr("En consultas de cuentas de ingresos/gastos\n"
				      "las fechas han de pertenecer al mismo período"));
	   QString ejercicio=ejerciciodelafecha(ui.inicialdateEdit->date());
	   // QMessageBox::warning( this, tr("Consultas de Mayor"),ejercicio);
	   if (ejercicio.length()!=0) ui.finaldateEdit->setDate(finejercicio(ejercicio));
	      else ui.finaldateEdit->setDate(ui.inicialdateEdit->date());
        }
}



void cuadimprimayor::botonimprimepulsado()
{
  fechasok();
  generalatexmayor(ui.subcuentalineEdit->text(),
		   ui.finallineEdit->text(),
		   ui.inicialdateEdit->date(),ui.finaldateEdit->date());
    
   int valor=imprimelatex(tr("mayor"));
   if (valor==1)
       QMessageBox::warning( this, tr("IMPRIMIR MAYOR"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("IMPRIMIR MAYOR"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
   if (valor==3)
       QMessageBox::warning( this, tr("IMPRIMIR MAYOR"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());
}
void cuadimprimayor::botonGenFactura()
{

  fechasok();
  QString fact = generalatexfactura(ui.subcuentalineEdit->text(),
                   ui.finallineEdit->text(),
                   ui.inicialdateEdit->date(),ui.finaldateEdit->date());

  QString fich(tr("factura"));
  fich+=nombreempresa().replace(" ","_").prepend("_");
  fich+="_";
  fich+=fact;
  int valor=consultalatex2(fich);
   if (valor==1)
       QMessageBox::warning( this, tr("VISTA PREVIA FACTURA"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("VISTA PREVIA FACTURA"),
                             tr("PROBLEMAS al llamar a ")+visordvi());
   if (valor==0){
       QMessageBox::information( this, tr("VISTA PREVIA FACTURA"),tr("Se generará el documento PDF también."));
       QString cadexec="dvipdf";
       if (eswindows()) cadexec="dvipdfm";
       QStringList arguments;
       QObject *parent=this;
       QProcess *miProceso = new QProcess(parent);

       miProceso-> setWorkingDirectory(adapta(dirtrabajo()));

       QString cadarg=adapta(fich);
       cadarg+=".dvi";
       arguments << cadarg;
       // arguments << "&";

       miProceso->start(cadexec,arguments);

       if (!miProceso->waitForStarted ())
          {
            miProceso->~QProcess();
          }

       if (!miProceso->waitForFinished ())
          {
            miProceso->~QProcess();
          }

        miProceso->~QProcess();

    }
}


void cuadimprimayor::botonprevisualizapulsado()
{

  fechasok();
  generalatexmayor(ui.subcuentalineEdit->text(),
		   ui.finallineEdit->text(),
		   ui.inicialdateEdit->date(),ui.finaldateEdit->date());

   int valor=consultalatex2(tr("mayor"));
   if (valor==1)
       QMessageBox::warning( this, tr("VISTA PREVIA MAYOR"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("VISTA PREVIA MAYOR"),
                             tr("PROBLEMAS al llamar a ")+visordvi());

}


void cuadimprimayor::ctainicialcambiada()
{
  ui.finallineEdit->setText(ui.subcuentalineEdit->text());
}


void cuadimprimayor::botonctafinalpulsado()
{
    QString cadena2;
    buscasubcuenta *labusqueda=new buscasubcuenta(ui.subcuentalineEdit->text());
    labusqueda->exec();
    cadena2=labusqueda->seleccioncuenta();
    if (existesubcuenta(cadena2)) ui.finallineEdit->setText(cadena2);
       else ui.finallineEdit->setText("");
    delete labusqueda;
}


void cuadimprimayor::finedicfinsubcuenta()
{
 finalexpandepunto();
 if (ui.finallineEdit->text().length()<anchocuentas()) botonctafinalpulsado();
}



void cuadimprimayor::finalexpandepunto()
{
  ui.finallineEdit->setText(expandepunto(ui.finallineEdit->text(),anchocuentas()));
}


void cuadimprimayor::generalatexmayor( QString qsubcuentaini, QString qsubcuentafinal, QDate fechainicial, QDate fechafinal )
{

    // -----------------------------------------------------------------------------------
   if (QString::compare(qsubcuentaini,qsubcuentafinal)>0) return;
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero=qfichero+tr("mayor.tex");
   // QMessageBox::warning( this, tr("Estados Contables"),qfichero);
   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(qfichero);
       else pasa=qfichero;
   QFile fichero(pasa);
    if (! fichero.open( QIODevice::WriteOnly ) ) return;
    QTextStream stream( &fichero );
    stream.setCodec("UTF-8");
    stream << "\\documentclass[11pt,a4paper]{article}" << "\n";
    stream << "\\usepackage{ucs}" << "\n";
    stream << "\\usepackage[utf8x]{inputenc}" << "\n";
    stream << "\\usepackage[spanish]{babel}" << "\n";
    stream << "\\usepackage{longtable}" << "\n";
    stream << "\\addtolength{\\hoffset}{-2.8cm}" << "\n";
    stream << "\\addtolength{\\textwidth}{5.6cm}" << "\n";
    stream << "\\addtolength{\\voffset}{-1.5cm}" << "\n";
    stream << "\\addtolength{\\textheight}{3cm}" << "\n";
    stream << "\\begin{document}" << "\n";
    stream << "% CUERPO" << "\n";
            
    QString subctaactual=qsubcuentaini;
    int lineas=0;
    QString cadena;
    QSqlQuery query;
    while (subctaactual<=qsubcuentafinal)
      {
       while (1)
          {
           /*cambiado a partir de aquí*/
           // Imprimimos cabecera del listado con nombre de empresa
           // imprimimos codigo de subcuenta, fecha inicial, fecha final
           // imprimimos fecha actual

           stream << "\\begin{center}" << "\n";
           stream << "{\\Large \\textbf {" << filtracad(nombreempresa()) << "}}" << "\n";
           stream << "\\end{center}" << "\n";
           stream << "\n";
           // buscar descripción de la cuenta
           stream << "\\begin{center}" << "\n";
           stream << "{\\Large \\textbf {" << tr("MAYOR SUBCUENTA: ") << subctaactual <<  "}}" << "\n";
           stream << "\\end{center}" << "\n";
           
           stream << "\\begin{center}" << "\n";
           stream << "{\\Large \\textbf {" << filtracad(descripcioncuenta(subctaactual)) << "}}" << "\n";
           stream << "\\end{center}" << "\n";

           stream << "{\\textbf {" << tr("Extracto de ") << fechainicial.toString("dd.MM.yyyy") <<
	                         tr(" a ") << fechafinal.toString("dd.MM.yyyy") << "}}" << "\n";

           // cuerpo de listado (tablas)
           stream << "\\begin{center}\n";
           stream << "\\begin{tabular}{|l|r|p{7.5cm}|r|r|r|}\n";
           stream << "\\hline\n";
           stream << "{\\textbf {" << tr("FECHA") << "}} & {\\textbf {" << tr("ASTO.") << "}} & {\\textbf {" <<
             tr("CONCEPTO") << "}} & {\\textbf {" << tr("DEBE") << "}} & {\\textbf {" << tr("HABER") << 
             "}} & {\\textbf {" << tr("SALDO") << "}} \\\\\n";
           stream << "\\hline\n";

            qlonglong num = c->selectCountAsiento(fechainicial, fechafinal, subctaactual);

            if (num==0)
            {
                subctaactual=subcuentaposterior(subctaactual);
                lineas=0;
                if (subctaactual.length()==0) {
                    stream << "\\end{tabular}\n";
                    stream << "\\end{center}\n";
                    break;
                }
                else
                {
                    stream << "\\end{tabular}\n";
                    stream << "\\end{center}\n";
                    stream << "\\newpage\n";
                }
                continue;
            }
     
	   
           // calculamos saldo inicial
	   // calculamos acumulado de saldo inicial
           // primero observamos si el ejercicio anterior está cerrado
           QString ejercicio=ejerciciodelafecha(fechainicial);
           QDate fechainiejercicio=inicioejercicio(ejercicio);
           QDate fechaejercicioanterior=fechainiejercicio.addDays(-1);
           QString ejercicioanterior=ejerciciodelafecha(fechaejercicioanterior);
           if (ejerciciocerrado(ejercicioanterior) || escuentadegasto(subctaactual) || 
	     escuentadeingreso(subctaactual))		
            {
                query = c->selectSumasDiario(fechainiejercicio, fechainicial, subctaactual);
            }
           else query = c->selectSumasDiarioHasta(fechainicial, subctaactual);

           double saldoin=0;
           double sumadebe=0;
           double sumahaber=0;
           double sumadebeextracto=0;
           double sumahaberextracto=0;
	   double saldo=0;
	   QString cadsaldo="";
	   QString cadnum;
           if ( (query.isActive()) && (query.first()) )
              {
               saldoin=query.value(0).toDouble()-query.value(1).toDouble();
               sumadebe=query.value(0).toDouble();
               sumahaber=query.value(1).toDouble();
              }
	 
         query = select5Diariofechascuentaorderfechapase(fechainicial, fechafinal, subctaactual);
	     saldo=saldoin;
         QString concepto;
         if (query.isActive())
         while (query.next())
	     {
	      lineas++;
	      stream << query.value(0).toDate().toString("dd.MM.yyyy") << " & ";
	      // Asiento ------------------------------------------------------------------------------------------
	      if (!numeracionrelativa()) stream << query.value(1).toString() << " & ";
	      else
	      {
		     qlonglong asreal;
		     asreal=query.value(1).toLongLong();
		     qlonglong asrelativo=asreal-
				primasejerciciodelafecha(query.value(0).toDate())+1;
		     QString cadnum;
		     cadnum.setNum(asrelativo);
		     stream << cadnum << " & ";
		  }
	      // ---------------------------------------------------------------------------------------------------
	      concepto=query.value(2).toString();
	      concepto=filtracad(concepto);
	      QString cort=mcortaa(concepto,43);
	      if (cort!=concepto) concepto=cort+"\\#"; else concepto=cort;	      
	      stream << concepto << " & ";
	      double valdebe=query.value(3).toDouble();
	      if (valdebe>0.0001 || valdebe<-0.0001)
                 stream << formateanumerosep(query.value(3).toDouble(),comadecimal,decimales) << " & ";
                else stream << " & ";
	      double valhaber=query.value(4).toDouble();
	      if (valhaber>0.0001 || valhaber<-0.0001)
                   stream << formateanumerosep(query.value(4).toDouble(),comadecimal,decimales) << " & ";
	        else stream << " & ";
	      saldo+=query.value(3).toDouble()-query.value(4).toDouble();
	      sumadebe+=query.value(3).toDouble();
	      sumahaber+=query.value(4).toDouble();
	      sumadebeextracto+=query.value(3).toDouble();
	      sumahaberextracto+=query.value(4).toDouble();
	      cadsaldo=formateanumerosep(saldo,comadecimal,decimales);
	      stream << cadsaldo << " \\\\ \n ";
                      stream << "\\hline\n";
	      if (lineas==LINEASPAGINA)
                        {
	                  lineas=0;
                          stream  << "\\multicolumn{3}{|r|}{" << tr("Sumas y siguen ...") << "} & " <<
                               formateanumerosep(sumadebe,comadecimal,decimales);
	                  stream << " & " << formateanumerosep(sumahaber,comadecimal,decimales) << "& \\\\";
                          stream << "\\hline\n";
       	                  stream << "\\end{tabular}\n";
                          stream << "\\end{center}\n";
                          stream << "\\newpage\n";
		  
                         // stream << "\\begin{flushleft}" << "\n";
                         // stream << "\\today" << "\n";
                         // stream << "\\newline" << "\n";
                         // stream << "\\end{flushleft}" << "\n";
     
                         stream << "\\begin{center}" << "\n";
                         stream << "{\\Large \\textbf {" << filtracad(nombreempresa()) << "}}" << "\n";
                         stream << "\\end{center}" << "\n";
                         stream << "\n";
                         // buscar descripción de la cuenta
                        stream << "\\begin{center}" << "\n";
                        stream << "{\\Large \\textbf {" << tr("MAYOR SUBCUENTA: ") << subctaactual <<  "}}" << "\n";
                        stream << "\\end{center}" << "\n";
           
                        stream << "\\begin{center}" << "\n";
                        stream << "{\\Large \\textbf {" << filtracad(descripcioncuenta(subctaactual)) << "}}" << "\n";
                        stream << "\\end{center}" << "\n";

                        stream << "{\\textbf {" << tr("Extracto de ") << fechainicial.toString("dd.MM.yyyy") <<
	                         tr(" a ") << fechafinal.toString("dd.MM.yyyy") << "}}" << "\n";

                       // cuerpo de listado (tablas)
                       stream << "\\begin{center}\n";
                       stream << "\\begin{tabular}{|l|r|p{7.5cm}|r|r|r|}\n";
                       stream << "\\hline\n";
	               stream << "{\\textbf {" << tr("FECHA") << "}} & {\\textbf {" << tr("ASTO.") << 
                        "}} & {\\textbf {" << tr("CONCEPTO") << "}} & {\\textbf {" << tr("DEBE") << 
                        "}} & {\\textbf {" << tr("HABER") << "}} & {\\textbf {" << tr("SALDO") << "}} \\\\\n";
                       stream << "\\hline\n";
  	       }
	     }
           stream  << "\\multicolumn{3}{|r|}{" << tr("Sumas ...") << "} & " <<
              formateanumerosep(sumadebe,comadecimal,decimales);
           stream << " & " << formateanumerosep(sumahaber,comadecimal,decimales) << "& \\\\";
           stream << "\\hline\n";
           stream  << "\\multicolumn{3}{|r|}{" << tr("Sumas extracto...") << "} & " 
                   << formateanumerosep(sumadebeextracto,comadecimal,decimales);
           stream << " & " << formateanumerosep(sumahaberextracto,comadecimal,decimales) << "& \\\\";
           stream << "\\hline\n";
           // final de la tabla
           stream << "\\end{tabular}\n";
           stream << "\\end{center}\n";
           stream << "\\newpage\n";
           break;
          }
       if (subctaactual.length()==0) break;
       subctaactual=subcuentaposterior(subctaactual);
       lineas=0;
       if (subctaactual.length()==0) break;
       }
    
    // imprimimos final del documento latex
    stream << "% FIN_CUERPO" << "\n";
    stream << "\\end{document}" << "\n";

    fichero.close();

    if (filtrartexaxtivado()) filtratex(qfichero);
}

QString cuadimprimayor::generalatexfactura( QString qsubcuentaini, QString qsubcuentafinal, QDate fechainicial, QDate fechafinal )
{

    // -----------------------------------------------------------------------------------
   pidenombre *f = new pidenombre();
   f->asignanombreventana(tr("Factura"));
   f->asignaetiqueta(tr("Número factura:"));
   f->exec();
   QString numfactura=f->contenido();
   f->~pidenombre();

    if (QString::compare(qsubcuentaini,qsubcuentafinal)>0) return numfactura;
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero=qfichero+tr("factura");
   qfichero+=nombreempresa().replace(" ","_").prepend("_");
   qfichero+="_";
   qfichero+=numfactura;
   qfichero+=".tex";
   // QMessageBox::warning( this, tr("Estados Contables"),qfichero);
   QString pasa;
   if (eswindows()) pasa=QFile::encodeName(qfichero);
       else pasa=qfichero;
   QFile fichero(pasa);
    if (! fichero.open( QIODevice::WriteOnly ) ) return numfactura;
    QTextStream stream( &fichero );
    stream.setCodec("UTF-8");
    stream << "\\documentclass[a4paper]{article}" << "\n";
    stream << "\\usepackage[T1]{fontenc}" << "\n";
    stream << "\\usepackage[utf8x]{inputenc}" << "\n";
    stream << "\\usepackage[spanish]{babel}" << "\n";
    stream << "\\usepackage{amsmath}" << "\n";
    stream << "\\usepackage{color}" << "\n";
    stream << "\\usepackage{supertabular}" << "\n";
    stream << "\\usepackage{graphicx}" << "\n";
    stream << "\\usepackage{amssymb,amsfonts,textcomp}" << "\n";
    stream << "\\usepackage{array}" << "\n";
    stream << "\\usepackage{hhline}" << "\n";
    stream << "\\usepackage{hyperref}" << "\n";
    stream << "\\hypersetup{colorlinks=true, linkcolor=blue, citecolor=blue, filecolor=blue, urlcolor=blue}" << "\n";
     stream << "\\makeatletter" << "\n";
     stream << "\\newcommand\\arraybslash{\\let\\\\\\@arraycr}" << "\n";
     stream << "\\makeatother" << "\n";
    stream << "% Page layout (geometry)" << "\n";
     stream << "\\setlength\\voffset{-1in}" << "\n";
     stream << "\\setlength\\hoffset{-1in}" << "\n";
     stream << "\\setlength\\topmargin{2cm}" << "\n";
     stream << "\\setlength\\oddsidemargin{2cm}" << "\n";
     stream << "\\setlength\\textheight{27.279cm}" << "\n";
     stream << "\\setlength\\textwidth{16.999cm}" << "\n";
     stream << "\\setlength\\footskip{0.0cm}" << "\n";
     stream << "\\setlength\\headheight{0cm}" << "\n";
     stream << "\\setlength\\headsep{0cm}" << "\n";
     stream << "% Footnote rule" << "\n";
     stream << "\\setlength{\\skip\\footins}{0.119cm}" << "\n";
     stream << "\\renewcommand\\footnoterule{\\vspace*{-0.018cm}\\setlength\\leftskip{0pt}\\setlength\\rightskip{0pt plus 1fil}\\noindent\\textcolor{black}{\\rule{0.25\\columnwidth}{0.018cm}}\\vspace*{0.101cm}}" << "\n";
     stream << "% Pages styles" << "\n";
     stream << "\\makeatletter" << "\n";
     stream << "\\newcommand\\ps@Standard{" << "\n";
       stream << "\\renewcommand\\@oddhead{}" << "\n";
       stream << "\\renewcommand\\@evenhead{}" << "\n";
       stream << "\\renewcommand\\@oddfoot{}" << "\n";
       stream << "\\renewcommand\\@evenfoot{}" << "\n";
       stream << "\\renewcommand\\thepage{\\arabic{page}}" << "\n";
     stream << "}" << "\n";
     stream << "\\makeatother" << "\n";
     stream << "\\pagestyle{Standard}" << "\n";
     stream << "\\setlength\\tabcolsep{1mm}" << "\n";
     stream << "\\renewcommand\\arraystretch{1.3}" << "\n";
     stream << "\\title{factura_libroK}" << "\n";
     stream << "\\author{ivanvegacbr}" << "\n";
     stream << "\\date{" << fechaactual.currentDate().toString("yyyy-MM-dd") << "}\n";

    stream << "\\begin{document}" << "\n";
    stream << "% CUERPO" << "\n";

    QString subctaactual=qsubcuentaini;
    int lineas=0;
    QString cadena;
    QSqlQuery query;
    cadena="select empresa, nif, domicilio, poblacion, cpostal, provincia, email from configuracion;";
    query=ejecutarSQL(cadena);
    if ( query.isActive() ) query.next();
    QStringList direccion= query.value(2).toString().split("|");

    while (subctaactual<=qsubcuentafinal)
      {
       while (1)
          {
           /*cambiado a partir de aquí*/
           // Imprimimos cabecera del listado con nombre de empresa
           // imprimimos codigo de subcuenta, fecha inicial, fecha final
           // imprimimos fecha actual

           stream << "\\begin{center}" << "\n";
           stream << "\\tablehead{}" << "\n";
           stream << "\\begin{supertabular}{m{8.5cm}m{8.5cm}}" << "\n";
           stream << "{\\sffamily " << filtracad(nombreempresa()) << "}" << "\n\n";
           stream << "{\\sffamily NIF: " << filtracad(query.value(1).toString()) << "}" << "\n\n";
           stream << "{\\sffamily " << filtracad(direccion.at(1)) << "}" << "\n\n";
           stream << "{\\sffamily " << "Telf. 933021880" << "}" << "\n\n";
           stream << "{\\sffamily " << filtracad(direccion.at(0)) << "}" << "\n\n";
           stream << "{\\sffamily " << filtracad(query.value(4).toString()) << ", ";
           stream << filtracad(query.value(3).toString()) << "}" << "\n\n";
           stream << "{\\sffamily Email: " << filtracad(query.value(6).toString()) << "}";
           stream << "&\n";
           stream << "\\includegraphics[width=7.4cm,height=4.2cm]{logo_nuevo.eps}\\\\" << "\n";
           stream << "\\end{supertabular}" << "\n";
           stream << "\\end{center}" << "\n";
           stream << "\n";
           //stream << "\\bigskip" << "\n";
           stream << "\\begin{center}" << "\n";
           stream << "\\tablehead{}" << "\n";
           stream << "\\begin{supertabular}{m{8.5cm}m{8.5cm}}" << "\n";
           stream << "{\\sffamily\\itshape Cliente:}" << "\n";
           QString cliente,comercial,nif,cif,direccion2,pobl,codpostal,prov,pais,telef,fax,mail,obs,cc,cuot;
           int si = existendatosaccesorios(subctaactual,&cliente,&comercial,&nif,
                                           &cif,&direccion2,&pobl,&codpostal,
                                           &prov,&pais,&telef,&fax,&mail,
                                           &obs,&cc,&cuot);
           stream << "{\\sffamily " << filtracad(cliente) << "}" << "\n";
           stream << "\n";

           stream << "{\\sffamily " << nif << "}" << "\n";
           stream << "\n";

           stream << "{\\sffamily " << filtracad(direccion2) << "}" << "\n";
           stream << "\n";
           stream << "{\\sffamily " << codpostal << ", " << filtracad(pobl) << "}\n";
           stream << "\n";

           stream << "{\\sffamily Email: " << filtracad(mail) << "}&" << "\n";

           stream << "\\centering {\\sffamily\\bfseries FACTURA}\\par" << "\n";
           stream << "\n";

           stream << "\\centering {\\sffamily\\bfseries ";
           stream << numfactura << "}\\par" << "\n";
           stream << "\n";

           stream << "\\centering\\arraybslash \\sffamily\\bfseries ";
           stream << fechaactual.currentDate().toString("dd/MM/yy");
           stream << "\\\\" << "\n";
           stream << "\\end{supertabular}" << "\n";
           stream << "\\end{center}" << "\n";

           //stream << "\\bigskip" << "\n";
           stream << "\\begin{center}" << "\n";
           stream << "\\tablehead{}" << "\n";
           stream << "\\begin{supertabular}{m{8.5cm} c l r|r}" << "\n";
           stream << "\\sffamily\\bfseries\\color{black} Concepto &" << "\n";
           stream << "\\sffamily\\bfseries\\color{black} Cantidad &" << "\n";
           stream << "~" << "\n";
           stream << "&" << "\n";
           stream << "{\\sffamily\\bfseries\\color{black} Precio}" << "\n";
           stream << "\n";
           stream << "\\sffamily\\bfseries\\color{black} unidad/kg &" << "\n";
           stream << "\\sffamily\\bfseries\\color{black} Subtotal\\\\\\hline" << "\n";

           double bas,iva8,iva4,total;
           cadena="select d.fecha,l.base_iva,l.tipo_iva,l.cuota_iva,l.base_iva+l.cuota_iva "
                   "from diario d, libroiva l "
                   "where d.pase=l.pase and l.cuenta_fra='";

           cadena+=subctaactual;
           cadena += "' and d.fecha>='";
           cadena += fechainicial.toString("yyyy.MM.dd");
           cadena += "' and d.fecha<='";
           cadena += fechafinal.toString("yyyy.MM.dd");
           cadena+="' order by d.fecha,d.asiento;";
           query = ejecutarSQL(cadena);
           while( (query.next()) || (lineas<26) ){
               lineas++;
               if(query.value(1).toDouble() > 0.0){
                   stream << "\\sffamily\\bfseries\\color{black} ";
                   stream << query.value(0).toDate().toString("dd/MM/yy");
                   if ((query.value(2).toDouble()) > 4.00){
                       iva8 = iva8+query.value(3).toDouble();
                       stream << "  Jamon y embutido";
                   }else{
                       iva4 = iva4+query.value(3).toDouble();
                       stream << "  Quesos";
                   }

                   stream <<"&" << "\n";
                   stream << "\\sffamily\\color{black} 1 &" << "\n";
                   stream << "\\sffamily\\color{black} B. &" << "\n";
                   stream << "\\raggedleft \\sffamily\\color{black} ";
                   stream << formateanumerosep(query.value(1).toDouble(),comadecimal,decimales) << QChar(8364) << "&" << "\n";
                   stream << "\\sffamily\\color{black} ";
                   stream << formateanumerosep(query.value(1).toDouble(),comadecimal,decimales) << QChar(8364) << "\\\\" << "\n";
                   bas = bas+query.value(1).toDouble();
                   total = total+query.value(4).toDouble();

               }else{
                   stream << "~" << "\n";
                   stream << "&" << "\n";
                   stream << "~" << "\n";
                   stream << "&" << "\n";
                   stream << "~" << "\n";
                   stream << "&" << "\n";
                   stream << "~" << "\n";
                   stream << "&" << "\n";
                   stream << "\\\\" << "\n";
               }

           }
           stream << "~" << "\n";
            stream << "&" << "\n";
           stream << "\\multicolumn{3}{m{6.068cm}|}{\\sffamily\\color{black} Base} &" << "\n";
           stream << "\\raggedleft\\arraybslash \\sffamily ";
           stream << formateanumerosep(bas,comadecimal,decimales) << " " << QChar(8364) << "\\\\" << "\n";
           stream << "~" << "\n";
           stream << "&" << "\n";
           stream << "\\multicolumn{3}{m{6.068cm}|}{\\sffamily\\color{black} I.V.A. ( 8\\% )} &" << "\n";
           stream << "\\raggedleft\\arraybslash \\sffamily ";
           stream << formateanumerosep(iva8,comadecimal,decimales) << " " << QChar(8364) << "\\\\" << "\n";
           stream << "~" << "\n";
            stream << "&" << "\n";
           stream << "\\multicolumn{3}{m{6.068cm}|}{\\sffamily\\color{black} I.V.A. ( 4\\% )} &" << "\n";
           stream << "\\raggedleft\\arraybslash \\sffamily ";
           stream << formateanumerosep(iva4,comadecimal,decimales) << " " << QChar(8364) << "\\\\\\hline" << "\n";
           stream << "~" << "\n";
            stream << "&" << "\n";
           stream << "\\multicolumn{3}{m{6.068cm}|}{\\sffamily\\bfseries TOTAL} &" << "\n";
           stream << "\\raggedleft\\arraybslash \\sffamily\\bfseries\\itshape ";
           stream << formateanumerosep(total,comadecimal,decimales) << " " << QChar(8364) << "\\\\" << "\n";

           stream << "\\end{supertabular}" << "\n";
           stream << "\\end{center}" << "\n";

           break;
          }
       if (subctaactual.length()==0) break;
       subctaactual=subcuentaposterior(subctaactual);
       lineas=0;
       if (subctaactual.length()==0) break;
       }

    // imprimimos final del documento latex
    stream << "% FIN_CUERPO" << "\n";
    stream << "\\end{document}" << "\n";

    fichero.close();

    if (filtrartexaxtivado()) filtratex(qfichero);
    return numfactura;
}


QDate cuadimprimayor::selectAperturaejerciciosaperturacierre(QString ini, QString fin) {
    QString cadena = "select apertura from ejercicios where apertura<='";
    cadena += ini;
    cadena += "' and cierre>='";
    cadena += fin;
    cadena += "'";
    QSqlQuery query = ejecutarSQL(cadena);
    if ( (query.isActive()) &&(query.first()) )
    {
        return query.value(0).toDate();
    }
    else
    {
        return QDate::currentDate();
    }
}

// 

QDate cuadimprimayor::selectCierreejerciciosaperturacierre(QString ini, QString fin) {
    QString cadena = "select cierre from ejercicios where apertura<='";
    cadena += ini;
    cadena += "' and cierre>='";
    cadena += fin;
    cadena += "'";
    QSqlQuery query = ejecutarSQL(cadena);
    if ( (query.isActive()) &&(query.first()) )
    {
        return query.value(0).toDate();
    }
    else
    {
        return QDate::currentDate();
    }
}

QSqlQuery cuadimprimayor::select5Diariofechascuentaorderfechapase (QDate inicial, QDate final, QString cuenta) {
    QString cadena = "select fecha,asiento,concepto,debe,haber from diario where fecha>='";  
    cadena += inicial.toString("yyyy.MM.dd");
    cadena += "' and fecha<='";
    cadena += final.toString("yyyy.MM.dd");
    cadena += "' and cuenta='";
    cadena += cuenta.left(-1).replace("'","''");
    cadena += "' order by fecha,pase";
    return ejecutarSQL(cadena);
}

