/* ----------------------------------------------------------------------------------
    KEME-Contabilidad 2; aplicación para llevar contabilidades

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

#include "imprimediario.h"
#include "basedatos.h"
#include "funciones.h"

imprimediario::imprimediario() : QDialog() {
    ui.setupUi(this);
    comadecimal=haycomadecimal();
    decimales=haydecimales();

  connect(ui.visualizarpushButton,SIGNAL(clicked()),SLOT(visualizar()));
  connect(ui.imprimepushButton,SIGNAL(clicked()),SLOT(imprimir()));

}


void imprimediario::generalatexdiario()
{
    int lineaspagina=43;
    if (ui.fechaactualcheckBox->isChecked()) lineaspagina-=3;
    if (ui.confiltrocheckBox->isChecked()) lineaspagina-=3;

   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero+=tr("diario");
   qfichero+=".tex";
   // QMessageBox::warning( this, tr("Estados Contables"),qfichero);
    QFile fichero(adapta(qfichero));
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

    QString cabecerapagina="";
    if (ui.fechaactualcheckBox->isChecked())
          {
           cabecerapagina+= "\\begin{flushleft}"; cabecerapagina+="\n";
           cabecerapagina+= "\\today"; cabecerapagina+= "\n";
           cabecerapagina+= "\\newline"; cabecerapagina+="\n";
           cabecerapagina+= "\\end{flushleft}"; cabecerapagina+="\n";
          }
    
    cabecerapagina+= "\\begin{center}"; cabecerapagina+= "\n";
    cabecerapagina+= "{\\huge \\textbf {";  
    if(tabla=="borrador") cabecerapagina+="TABLA APUNTES";
    else cabecerapagina+="LIBRO DIARIO";
             cabecerapagina+="}}"; cabecerapagina+="\n";
    cabecerapagina+= "\\end{center}"; cabecerapagina+= "\n";
    cabecerapagina+= "\n";
        
    cabecerapagina+= "\\begin{center}"; cabecerapagina+= "\n";
    cabecerapagina+= "{\\Large \\textbf {";  cabecerapagina+=filtracad(nombreempresa());
             cabecerapagina+="}}"; cabecerapagina+="\n";
    cabecerapagina+= "\\end{center}"; cabecerapagina+= "\n";
    cabecerapagina+= "\n";
    cabecerapagina+="\\begin{center}\n";
    cabecerapagina+= "\\begin{tabular}{|r|l|l|l|l|r|r|c|}\n";
    cabecerapagina+="\\hline\n";
    cabecerapagina+="{\\scriptsize ";
    cabecerapagina+=tr("ASTO");
    cabecerapagina+="} & {\\scriptsize ";
    cabecerapagina+=tr("FECHA");
    cabecerapagina+= "} & {\\scriptsize ";
    cabecerapagina+=tr("CUENTA");
    cabecerapagina+= "} & {\\scriptsize ";
    cabecerapagina+= tr("TITULO CUENTA");
    cabecerapagina+= "} & {\\scriptsize ";
    cabecerapagina+= tr("DESCRIPCIÓN");
    cabecerapagina+="} & {\\scriptsize ";
    cabecerapagina+= tr("DEBE");
    cabecerapagina+= "} & {\\scriptsize ";
    cabecerapagina+= tr("HABER");
    cabecerapagina+= "} & {\\scriptsize ";
    cabecerapagina+= tr("PAGO");
    cabecerapagina+= "} \\\\\n";
    cabecerapagina+="\\hline\n";
    QString piepagina="\\hline\n";
     piepagina+="\\end{tabular}\n";
     piepagina+="\\end{center}\n";
     if (ui.confiltrocheckBox->isChecked())
        {
	 piepagina+="{\\tiny ";
         piepagina+= tr("FILTRO: ");
	 QString filtrodef=filtracad(filtro);
	 piepagina+=filtrodef;
	 piepagina+="}\n";
        }
     piepagina+="\\newpage \n";
	if (tabla.length()==0) tabla="diario"; 
    QString cadena="select count(asiento) ";
    cadena+="from "+tabla+" ";
    if (filtro.length()>0) cadena+=" where ";
    cadena+=filtro;
    int totallineas=0;
    QSqlQuery query(cadena);
    if ( query.isActive() )  if (query.next())  totallineas=query.value(0).toInt();
    ui.progressBar->setMaximum(totallineas);
    if(tabla=="diario"){
    	cadena="SELECT d.asiento,d.fecha,d.cuenta,p.descripcion,d.concepto,d.debe,d.haber,d.ci ";
   	}
    if(tabla=="borrador"){
    	cadena="SELECT d.asiento,d.ci,d.cuenta,p.descripcion,d.concepto,";
    	cadena+="d.debe,d.haber,d.diafra,d.mesfra,d.anyofra ";
   	}
    
    cadena+="FROM "+tabla+" d,plancontable p WHERE ";
    cadena+="p.codigo=d.cuenta";
    if (filtro.length()>0) cadena+=" AND ";
    cadena+=filtro;
    if(tabla=="diario") cadena+=" ORDER BY d.fecha,d.asiento,d.cuenta";
    if(tabla=="borrador") cadena+=" ORDER BY d.mesfra,d.diafra,d.asiento,d.cuenta";
    cadena+=";";
    query = ejecutarSQL(cadena);
    if ( query.isActive() && query.size()>0)
      {
          int linea=0;
          int glinea=0;
          double sumadebe=0;
          double sumahaber=0;
          double sumagen=0;
          double sumapago=0;
          QString cadcort;
          QDate fecha;
          while (query.next())
	   {
	      if (linea==0) stream << cabecerapagina;
	      stream << "{\\tiny ";
	      if (numeracionrelativa())
	         {
		  QString cdnum;
		  cdnum.setNum(query.value(0).toLongLong()
			     -primasejerciciodelafecha(query.value(1).toDate())+1);
		  stream << cdnum;
	         }
	        else
	                stream << query.value(0).toString();  // asiento
	      stream << "} & ";
	      stream << "{\\tiny ";
	      if(tabla=="diario") fecha=query.value(1).toDate();
	      if(tabla=="borrador")
	      	fecha.setYMD(query.value(9).toInt()
     	 	,query.value(8).toInt()
     	 	,query.value(7).toInt());
	      
	      stream << fecha.toString("dd.MM.yyyy");
	      
	      stream << "} &";
	      stream << "{\\tiny ";
	      stream << query.value(2).toString();
	      stream << "} &";
	      stream << "{\\tiny ";
	      QString cadcons=filtracad(query.value(3).toString());
	      cadcort=mcortaa(cadcons,40);
	      if (cadcort!=cadcons) cadcort=cadcort+"\\#";
	      stream << filtracad(cadcort);
	      stream << "} &";
	      stream << "{\\tiny ";
	      cadcons=query.value(4).toString();
	      cadcort=mcortaa(cadcons,40);
	      if (cadcort!=cadcons) cadcort=cadcort+"\\#";
	      stream << filtracad(cadcort);
	      stream << "} &";
	      stream << "{\\tiny ";
              // aquí estamos **********************************************************
	      stream << formateanumerosep(query.value(5).toDouble(),comadecimal,decimales);
	      stream << "} &";
	      stream << "{\\tiny ";
	      stream << formateanumerosep(query.value(6).toDouble(),comadecimal,decimales);
	      stream << "} &";
	      stream << "{\\tiny ";
	      if(tabla=="diario") fecha=query.value(7).toDate();
	      if(tabla=="borrador") fecha=query.value(1).toDate();
	      stream << fecha.toString("dd.MM.yyyy");
	      stream << "}  \\\\ \n";
	      if(esCuentadeGenero(query.value(2).toString()))
	      		sumagen+=query.value(5).toDouble();
	      sumadebe+=query.value(5).toDouble();
	      if(escuentadeingreso(query.value(2).toString()))
	      		sumahaber+=query.value(6).toDouble();
	      if(fecha.isValid()) sumapago+=query.value(5).toDouble();
	      linea++;
	      glinea++;
	      if (linea>lineaspagina) 
	         {
	            if (glinea!=totallineas)
		  		{
			     // sumas y siguen
			     QString cadnum;
			     stream << "\\hline\n";
			     stream  << "\\multicolumn{4}{|r|}{\\scriptsize " << tr("Sumas y siguen ...") << "} & {\\tiny " 
						    << tr("Género") << ": " << formateanumerosep(sumagen,comadecimal,decimales) ;
				 stream << "} & {\\tiny " << formateanumerosep(sumadebe,comadecimal,decimales) ;
			     stream << "} & {\\tiny " << formateanumerosep(sumahaber,comadecimal,decimales);
				 stream << "} & {\\tiny " << formateanumerosep(sumapago,comadecimal,decimales)
				     << "}  \\\\";
		         stream << piepagina;
		  		}
	            linea=0;
	         }
	      ui.progressBar->setValue(glinea);
	    }
           QString cadnum;
           stream << "\\hline\n";
           stream  << "\\multicolumn{4}{|r|}{\\scriptsize " << tr("Sumas ...") << "} & {\\tiny "
	     			<< tr("Género") << ": " << formateanumerosep(sumagen,comadecimal,decimales) ;
           stream << "} & {\\tiny " << formateanumerosep(sumadebe,comadecimal,decimales) ;
		   stream << "} & {\\tiny " << formateanumerosep(sumahaber,comadecimal,decimales);
	       stream << "} & {\\tiny " << formateanumerosep(sumapago,comadecimal,decimales)
	     			<< "}  \\\\";
           stream << piepagina;
      }
    
    
    // imprimimos final del documento latex
    stream << "% FIN_CUERPO" << "\n";
    stream << "\\end{document}" << "\n";
	ui.progressBar->setValue(totallineas);
    fichero.close();

}


void imprimediario::pasafiltro( QString qfiltro )
{
  filtro=qfiltro;
}

void imprimediario::pasaTabla (QString qTabla){
	tabla=qTabla;
}

void imprimediario::visualizar()
{
    generalatexdiario();
   
   int valor=consultalatex2(tr("diario"));
   if (valor==1){
   	QMessageBox::warning( this, tr("VISTA PREVIA DIARIO"),
   		tr("PROBLEMAS al llamar a Latex"));
   		ui.progressBar->reset();
  	}
       
   if (valor==2){
   	QMessageBox::warning( this, tr("VISTA PREVIA DIARIO"),
    	tr("PROBLEMAS al llamar a ")+visordvi());
    	ui.progressBar->reset();
  	}
       

    ui.progressBar->setValue(ui.progressBar->maximum());
    //ui.progressBar->reset();
}


void imprimediario::imprimir()
{
    generalatexdiario();

   int valor=imprimelatex(tr("diario"));
   if (valor==1)
       QMessageBox::warning( this, tr("IMPRIMIR DIARIO"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("IMPRIMIR DIARIO"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
   if (valor==3)
       QMessageBox::warning( this, tr("IMPRIMIR DIARIO"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());

    ui.progressBar->setValue(ui.progressBar->maximum());
    if(valor!=0) ui.progressBar->reset();

}
