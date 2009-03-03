/* ----------------------------------------------------------------------------------
    KEME-Contabilidad; aplicación para llevar contabilidades

    Copyright (C)

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

#include "libroiva.h"
//#include <QSqlQuery>
#include "basedatos.h"
#include "funciones.h"


libroiva::libroiva() : QDialog() {
    ui.setupUi(this);

  QSqlQuery query("select codigo from ejercicios order by codigo DESC;");
  QStringList ej1;

  if ( query.isActive() ) {
          while ( query.next() )
                ej1 << query.value(0).toString();
	  }
  ui.ejerciciocomboBox->addItems(ej1);

  soportado=true;
  aib=false;
  eib=false;
  soportadoprorrata=false;
  recibidas_autofactura=false;
  emitidas_autofactura=false;
  emitidas_rectificativa=false;
  comadecimal=haycomadecimal(); decimales=haydecimales();

  connect(ui.consultarpushButton,SIGNAL( clicked()),this,SLOT(consultatex()));
  connect(ui.imprimirpushButton,SIGNAL( clicked()),this,SLOT(imprime()));

}

void libroiva::generalatexsoportado()
{
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero+=nombrefichero();
   qfichero+=".tex";
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
    
    stream << "% CUERPO\n";

    stream << "\\begin{center}" << "\n";
    stream << "{\\Large \\textbf {";
    stream << filtracad(nombreempresa()) << "}}";
    stream << "\\end{center}";

    stream << "\\begin{center}" << "\n";
    stream << "\\begin{longtable}{|r|l|c|c|p{3cm}|l|r|r|r|r|r|}" << "\n";
    stream << "\\hline" << "\n";

   stream << "\\multicolumn{11}{|c|} {\\textbf{";
   QString cadena;
   if (soportado) cadena=tr("LIBRO DE FACTURAS RECIBIDAS");
   if (aib && soportado) cadena=tr("IVA SOPORTADO POR A.I.B.");
   if (recibidas_autofactura) cadena=tr("LIBRO DE AUTOFACTURAS REALIZADAS - FACTURAS RECIBIDAS");
   // --------------------------------------------------------------------------------------
   stream << cadena;
   stream <<  "}} \\\\";
   stream << "\\hline" << "\n";
    // -------------------------------------------------------------------------------------
    stream << "{\\tiny{" << tr("Orden") << "}} & ";
    stream << "{\\tiny{" << tr("Factura") << "}} & ";
    stream << "{\\tiny{" << tr("Fecha") << "}} & ";
    stream << "{\\tiny{" << tr("Cuenta") << "}} & ";
    stream << "{\\tiny{" << tr("Proveedor/acreedor") << "}} & ";
    stream << "{\\tiny{" << tr("CIF/NIF") << "}} & ";
    stream << "{\\tiny{" << tr("Asto.") << "}} & ";
    stream << "{\\tiny{" << tr("Base Imp.") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo") << "}} & ";
    stream << "{\\tiny{" << tr("Cuota") << "}} & ";
    stream << "{\\tiny{" << tr("Total") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endfirsthead";
    // ----------------------------------------------------------------------------------------
    stream << "\\hline" << "\n";
    // stream << tr(" \\\\") << "\n";
    stream << "{\\tiny{" << tr("Orden") << "}} & ";
    stream << "{\\tiny{" << tr("Factura") << "}} & ";
    stream << "{\\tiny{" << tr("Fecha") << "}} & ";
    stream << "{\\tiny{" << tr("Cuenta") << "}} & ";
    stream << "{\\tiny{" << tr("Proveedor/acreedor") << "}} & ";
    stream << "{\\tiny{" << tr("CIF/NIF") << "}} & ";
    stream << "{\\tiny{" << tr("Asto.") << "}} & ";
    stream << "{\\tiny{" << tr("Base Imp.") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo") << "}} & ";
    stream << "{\\tiny{" << tr("Cuota") << "}} & ";
    stream << "{\\tiny{" << tr("Total") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endhead" << "\n";
    // ---------------------------------------------------------------------------------------
    cadena="select count(libroiva.cuenta_fra) from libroiva,diario "
	     "where diario.pase=libroiva.pase and "
	     "diario.fecha>='";
    cadena+=inicioejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and diario.fecha<='";
    cadena+=finejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and soportado";
    if (aib) cadena+=" and aib"; else cadena+=" and not aib";
    if (recibidas_autofactura) cadena+=" and autofactura"; else cadena+=" and not autofactura";
    QSqlQuery query = ejecutarSQL(cadena);
    int registros=0;
    if ( query.isActive() ) {
          if ( query.next() )
              {
	        registros=query.value(0).toInt();
	      }
      }
    cadena="select d.documento,d.fecha,l.cuenta_fra,p.descripcion,d.asiento,"
	     "l.base_iva,l.tipo_iva,l.cuota_iva,l.base_iva+l.cuota_iva "
	     "from diario d, libroiva l, plancontable p "
	     "where d.pase=l.pase and d.fecha>='";
    cadena+=inicioejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and d.fecha<='";
    cadena+=finejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="'";
    if (aib) cadena+=" and aib"; else cadena+=" and not aib";
    if (recibidas_autofactura) cadena+=" and autofactura"; else cadena+=" and not autofactura";
    cadena+=" and p.codigo=l.cuenta_fra and soportado"
	       " order by d.fecha,d.asiento";
    query = ejecutarSQL(cadena);
    ui.progressBar->setMaximum(registros);
    int numorden=0;
    int numprog=1;
    QString cadnum,guardadoc,guardaprov;
    double base=0;
    double cuota=0;
    if ( query.isActive() ) {
          while ( query.next() )
              {
	        ui.progressBar->setValue(numprog);
                if (guardadoc!=query.value(0).toString() || query.value(0).toString().length()==0 
                    || numprog==1 || guardaprov!=query.value(2).toString()) numorden++; 
                guardadoc=query.value(0).toString();
                guardaprov=query.value(2).toString();
	        stream << "{\\tiny " << cadnum.setNum(numorden) << "} & {\\tiny "; 
	        stream << filtracad(query.value(0).toString()) << "} & {\\tiny "; // fra.
	        stream << query.value(1).toDate().toString("dd.MM.yyyy") << "} & {\\tiny "; // fecha
	        stream <<  query.value(2).toString() << "} & {\\tiny "; // cuenta
	        stream <<  filtracad(query.value(3).toString()) << "} & {\\tiny "; // proveedor
	        if (aib || eib) stream <<  nifcomunitariocta(query.value(2).toString()) << "} & {\\tiny "; // cif
		else stream <<  cifcta(query.value(2).toString()) << "} & {\\tiny "; // cif
	        // stream <<  cifcta(query.value(2).toString()) << "} & {\\tiny "; // cif
	        if (numeracionrelativa())
		   {
		    qlonglong primas=primasejerciciodelafecha(query.value(1).toDate());
		    qlonglong relativo=query.value(4).toLongLong()-primas+1;
		    QString cadas; cadas.setNum(relativo);
		    stream << cadas << "} & {\\tiny "; // asiento
		   }
                 else stream <<  query.value(4).toString() << "} & {\\tiny "; // asiento
	        stream <<  formateanumerosep(query.value(5).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // base iva
	        stream <<  formateanumerosep(query.value(6).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // tipo
	        stream <<  formateanumerosep(query.value(7).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // cuota
                stream <<  formateanumerosep(query.value(8).toDouble(),comadecimal,decimales) << "} \\\\ \n  " 
                       << "\\hline\n"; // total
	        numprog++;
	        base+=query.value(5).toDouble();
	        cuota+=query.value(7).toDouble();
	      }
      }

    stream << "\\multicolumn{7}{|r|} {\\textbf{";
   // --------------------------------------------------------------------------------------
    stream << tr("SUMAS TOTALES:") << "}} ";
    stream << " & {\\tiny " << formateanumerosep(base,comadecimal,decimales) << "} & & {\\tiny ";
    stream << formateanumerosep(cuota,comadecimal,decimales) << "} &  {\\tiny ";
    stream << formateanumerosep(base+cuota,comadecimal,decimales);
    stream <<  "} \\\\ \n";
    stream << "\\hline" << "\n";


    stream << "\\end{longtable}" << "\n";
    stream << "\\end{center}" << "\n";

    stream << "% FIN_CUERPO\n";
    stream << "\\end{document}" << "\n";
    
    fichero.close();

    ui.progressBar->reset();

}


void libroiva::generalatexrepercutido()
{
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero+=nombrefichero();
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
    
    stream << "% CUERPO\n";

    stream << "\\begin{center}" << "\n";
    stream << "{\\Large \\textbf {";
    stream << filtracad(nombreempresa()) << "}}";
    stream << "\\end{center}";

    stream << "\\begin{center}" << "\n";
    stream << "\\begin{longtable}{|r|l|c|p{3.5cm}|r|r|r|r|r|r|r|}" << "\n";
    stream << "\\hline" << "\n";

   stream << "\\multicolumn{11}{|c|} {\\textbf{";
   QString cadena;
   if (soportado) cadena=tr("LIBRO DE FACTURAS RECIBIDAS");
      else cadena=tr("LIBRO DE FACTURAS EMITIDAS");
   if (!soportado && aib) cadena=tr("IVA REPERCUTIDO POR AIB");
   if (eib) cadena=tr("ENTREGAS INTRACOMUNITARIAS DE BIENES");
   if (emitidas_autofactura) cadena=tr("AUTOFACTURAS - FACTURAS EMITIDAS");
   if (emitidas_rectificativa) cadena=tr("FACTURAS EMITIDAS RECTIFICATIVAS");
   // --------------------------------------------------------------------------------------
   stream << cadena;
   stream <<  "}} \\\\";
    stream << "\\hline" << "\n";
    // ---------------------------------------------------------------------------------------
    stream << "{\\tiny{" << tr("Orden") << "}} & ";
    stream << "{\\tiny{" << tr("Factura") << "}} & ";
    stream << "{\\tiny{" << tr("Fecha") << "}} & ";
    stream << "{\\tiny{" << tr("Cuenta, Proveedor/acreedor") << "}} & ";
    stream << "{\\tiny{" << tr("Asto.") << "}} & ";
    stream << "{\\tiny{" << tr("Base Imp.") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo") << "}} & ";
    stream << "{\\tiny{" << tr("Cuota") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo.RE") << "}} & ";
    stream << "{\\tiny{" << tr("R.E.") << "}} & ";
    stream << "{\\tiny{" << tr("Total") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endfirsthead";
    // --------------------------------------------------------------------------------------------------
    stream << "\\hline" << "\n";
    // stream << tr(" \\\\") << "\n";
    stream << "{\\tiny{" << tr("Orden") << "}} & ";
    stream << "{\\tiny{" << tr("Factura") << "}} & ";
    stream << "{\\tiny{" << tr("Fecha") << "}} & ";
    stream << "{\\tiny{" << tr("Cuenta, Proveedor/acreedor") << "}} & ";
    stream << "{\\tiny{" << tr("Asto.") << "}} & ";
    stream << "{\\tiny{" << tr("Base Imp.") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo") << "}} & ";
    stream << "{\\tiny{" << tr("Cuota") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo.RE") << "}} & ";
    stream << "{\\tiny{" << tr("R.E.") << "}} & ";
    stream << "{\\tiny{" << tr("Total") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endhead" << "\n";
    // -----------------------------------------------------------------------------------------------
    cadena="select count(libroiva.cuenta_fra) from libroiva,diario where diario.pase=libroiva.pase and "
	     "diario.fecha>='";
    cadena+=inicioejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and diario.fecha<='";
    cadena+=finejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and not soportado";
    if (eib) cadena+=" and eib"; else cadena+=" and not eib";
    if (aib) cadena+=" and aib"; else cadena+=" and not aib";
    if (emitidas_autofactura) cadena+=" and autofactura"; else cadena+=" and not autofactura";
    if (emitidas_rectificativa) cadena+=" and rectificativa"; else cadena+=" and not rectificativa";
    QSqlQuery query = ejecutarSQL(cadena);
    int registros=0;
    if ( query.isActive() ) {
          if ( query.next() )
              {
	        registros=query.value(0).toInt();
	      }
      }
    cadena="select d.documento,d.fecha,l.cuenta_fra,p.descripcion,d.asiento,"
	     "l.base_iva,l.tipo_iva,round(l.base_iva*l.tipo_iva/100,2),l.tipo_re,"
	     "round(l.tipo_re*l.base_iva/100,2),l.base_iva+l.cuota_iva "
	     "from diario d, libroiva l, plancontable p "
	     "where d.pase=l.pase and d.fecha>='";
    cadena+=inicioejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and d.fecha<='";
    cadena+=finejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="'";
    if (aib) cadena+=" and aib"; else cadena+=" and not aib";
    if (eib) cadena+=" and eib"; else cadena+=" and not eib";
    if (emitidas_autofactura) cadena+=" and autofactura"; else cadena+=" and not autofactura";
    if (emitidas_rectificativa) cadena+=" and rectificativa"; else cadena+=" and not rectificativa";
    cadena+=" and p.codigo=l.cuenta_fra and not soportado"
	       " order by d.fecha,d.asiento";
    query = ejecutarSQL(cadena);
    ui.progressBar->setMaximum(registros);
    int numorden=0;
    int numprog=1;
    QString cadnum,guardadoc,guardaprov;
    double base=0;
    double cuota=0;
    double re=0;
    if ( query.isActive() ) {
          while ( query.next() )
               {
	        ui.progressBar->setValue(numprog);
                if (guardadoc!=query.value(0).toString() || query.value(0).toString().length()==0 
                    || numprog==1 || guardaprov!=query.value(2).toString()) numorden++; 
                guardadoc=query.value(0).toString();
                guardaprov=query.value(2).toString();
	        stream << "{\\tiny " << cadnum.setNum(numorden) << "} & {\\tiny "; 
	        stream << filtracad(query.value(0).toString()) << "} & {\\tiny "; // fra.
	        stream << query.value(1).toDate().toString("dd.MM.yyyy") << "} & {\\tiny "; // fecha
	        stream <<  query.value(2).toString() << " "; // cuenta
	        stream <<  filtracad(query.value(3).toString()) << " "; // proveedor
	        if (aib || eib) stream <<  nifcomunitariocta(query.value(2).toString()) << "} & {\\tiny "; // cif
	             else stream <<  cifcta(query.value(2).toString()) << "} & {\\tiny "; // cif
		
	        if (numeracionrelativa())
		  {
		    qlonglong primas=primasejerciciodelafecha(query.value(1).toDate());
		    qlonglong relativo=query.value(4).toLongLong()-primas+1;
		    QString cadas; cadas.setNum(relativo);
		    stream << cadas << "} & {\\tiny "; // asiento
		  }
                 else stream <<  query.value(4).toString() << "} & {\\tiny "; // asiento

	        stream <<  formateanumerosep(query.value(5).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // base iva
	        stream <<  formateanumerosep(query.value(6).toDouble(),comadecimal,decimales) 
                       << "} & {\\tiny "; // tipo
	        stream <<  formateanumerosep(query.value(7).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // cuota
	        stream <<  formateanumerosep(query.value(8).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // tipo re
	        stream <<  formateanumerosep(query.value(9).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // re
                stream <<  formateanumerosep(query.value(10).toDouble(),comadecimal,decimales)
                       << "} \\\\ \n  " << "\\hline\n"; // total
	        numprog++;
	        base+=query.value(5).toDouble();
	        cuota+=query.value(7).toDouble();
	        re+=query.value(9).toDouble();
	      }
      }

    stream << "\\multicolumn{5}{|r|} {\\textbf{";
   // --------------------------------------------------------------------------------------
    stream << "SUMAS TOTALES:}} ";
    stream << " & {\\tiny " << formateanumerosep(base,comadecimal,decimales) << "} & & {\\tiny ";
    stream << formateanumerosep(cuota,comadecimal,decimales) << "} & & {\\tiny ";
    stream << formateanumerosep(re,comadecimal,decimales) << "} &  {\\tiny ";
    stream << formateanumerosep(base+cuota+re,comadecimal,decimales);
    stream <<  "} \\\\ \n";
    stream << "\\hline" << "\n";


   stream << "\\end{longtable}" << "\n";
   stream << "\\end{center}" << "\n";

    stream << "% FIN_CUERPO\n";
    stream << "\\end{document}" << "\n";
    
    fichero.close();

    ui.progressBar->reset();

}




void libroiva::consultatex()
{
    if (soportadoprorrata) generalatexsoportadoprorrata();
      else
        { if (soportado) generalatexsoportado(); else generalatexrepercutido(); }

   int valor=consultalatex2(nombrefichero());
   if (valor==1)
       QMessageBox::warning( this, tr("Libros de IVA"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("Libros de IVA"),
                             tr("PROBLEMAS al llamar a ")+visordvi());


}


void libroiva::imprime()
{
    if (soportadoprorrata) generalatexsoportadoprorrata();
      else
        { if (soportado) generalatexsoportado(); else generalatexrepercutido(); }

   int valor=imprimelatex(nombrefichero());
   if (valor==1)
       QMessageBox::warning( this, tr("Libros de IVA"),tr("PROBLEMAS al llamar a Latex"));
   if (valor==2)
       QMessageBox::warning( this, tr("Libros de IVA"),
                                tr("PROBLEMAS al llamar a 'dvips'"));
   if (valor==3)
       QMessageBox::warning( this, tr("Libros de IVA"),
                             tr("PROBLEMAS al llamar a ")+programa_imprimir());

}


void libroiva::hazaib()
{
  aib=true;
}


void libroiva::hazeib()
{
  eib=true;
}

void libroiva::hazrecibidas_autofactura()
{
  recibidas_autofactura=true;
}

void libroiva::hazemitidas_autofactura()
{
  emitidas_autofactura=true;
}

void libroiva::hazemitidas_rectificativa()
{
  emitidas_rectificativa=true;
}

void libroiva::hazsoportadoprorrata()
{
 soportadoprorrata=true;
}

QString libroiva::nombrefichero()
{
  QString cadena;
  if (soportadoprorrata) { cadena=tr("facturas_recibidas_prorrata"); return cadena; }
  if (soportado) cadena=tr("facturas_recibidas");
     else cadena=tr("facturas_emitidas");
  if (aib) cadena+=tr("_aib");
  if (eib) cadena+=tr("_eib");
  return cadena;
}

void libroiva::hazrepercutido()
{
  soportado=false;
  setWindowTitle(tr("Libro de IVA REPERCUTIDO"));
}


void libroiva::generalatexsoportadoprorrata()
{
   QString qfichero=dirtrabajo();
   qfichero.append(QDir::separator());
   qfichero+=nombrefichero();
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
    stream << "\\usepackage{lscape}" << "\n";
    stream << "\\addtolength{\\hoffset}{-2.8cm}" << "\n";
    stream << "\\addtolength{\\textwidth}{5.6cm}" << "\n";
    stream << "\\addtolength{\\voffset}{-1.5cm}" << "\n";
    stream << "\\addtolength{\\textheight}{3cm}" << "\n";
    stream << "\\begin{document}" << "\n";
    
    stream << "% CUERPO\n";

    stream << "\\begin{landscape}" << "\n";
    stream << "\\begin{center}" << "\n";
    stream << "{\\Large \\textbf {";
    stream << filtracad(nombreempresa()) << "}}";
    stream << "\\end{center}";

    stream << "\\begin{center}" << "\n";
    stream << "\\begin{longtable}{|r|l|c|c|p{4cm}|l|r|r|r|r|r|r|r|}" << "\n";
    stream << "\\hline" << "\n";

   stream << "\\multicolumn{13}{|c|} {\\textbf{";
   QString cadena;
   cadena=tr("LIBRO DE FACTURAS RECIBIDAS CON INFORMACIÓN SOBRE PRORRATA");
   // --------------------------------------------------------------------------------------
   stream << cadena;
   stream <<  "}} \\\\";
   stream << "\\hline" << "\n";
    // -------------------------------------------------------------------------------------
    stream << "{\\tiny{" << tr("Orden") << "}} & ";
    stream << "{\\tiny{" << tr("Factura") << "}} & ";
    stream << "{\\tiny{" << tr("Fecha") << "}} & ";
    stream << "{\\tiny{" << tr("Cuenta") << "}} & ";
    stream << "{\\tiny{" << tr("Proveedor/acreedor") << "}} & ";
    stream << "{\\tiny{" << tr("CIF/NIF") << "}} & ";
    stream << "{\\tiny{" << tr("Asto.") << "}} & ";
    stream << "{\\tiny{" << tr("Base Imp.") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo") << "}} & ";
    stream << "{\\tiny{" << tr("Cuota") << "}} & ";
    stream << "{\\tiny{" << tr("Total") << "}} &";
    stream << "{\\tiny{" << tr("Prorrata") << "}} &";
    stream << "{\\tiny{" << tr("Cuota ef.") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endfirsthead";
    // ----------------------------------------------------------------------------------------
    stream << "\\hline" << "\n";
    // stream << tr(" \\\\") << "\n";
    stream << "{\\tiny{" << tr("Orden") << "}} & ";
    stream << "{\\tiny{" << tr("Factura") << "}} & ";
    stream << "{\\tiny{" << tr("Fecha") << "}} & ";
    stream << "{\\tiny{" << tr("Cuenta") << "}} & ";
    stream << "{\\tiny{" << tr("Proveedor/acreedor") << "}} & ";
    stream << "{\\tiny{" << tr("CIF/NIF") << "}} & ";
    stream << "{\\tiny{" << tr("Asto.") << "}} & ";
    stream << "{\\tiny{" << tr("Base Imp.") << "}} & ";
    stream << "{\\tiny{" << tr("Tipo") << "}} & ";
    stream << "{\\tiny{" << tr("Cuota") << "}} & ";
    stream << "{\\tiny{" << tr("Total") << "}} &";
    stream << "{\\tiny{" << tr("Prorrata") << "}} &";
    stream << "{\\tiny{" << tr("Cuota ef.") << "}}";
    stream << " \\\\" << "\n";
    stream << "\\hline" << "\n";
    stream << "\\endhead" << "\n";
    // ---------------------------------------------------------------------------------------
    cadena="select count(libroiva.cuenta_fra) from libroiva,diario "
	     "where diario.pase=libroiva.pase and "
	     "diario.fecha>='";
    cadena+=inicioejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and diario.fecha<='";
    cadena+=finejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and soportado";
    if (aib) cadena+=" and aib"; else cadena+=" and not aib";
    QSqlQuery query = ejecutarSQL(cadena);
    int registros=0;
    if ( query.isActive() ) {
          if ( query.next() )
              {
	        registros=query.value(0).toInt();
	      }
      }
    cadena="select d.documento,d.fecha,l.cuenta_fra,p.descripcion,d.asiento,"
	     "l.base_iva,l.tipo_iva,l.cuota_iva,l.base_iva+l.cuota_iva, "
             "l.prorrata,l.cuota_iva*l.prorrata "
	     "from diario d, libroiva l, plancontable p "
	     "where d.pase=l.pase and d.fecha>='";
    cadena+=inicioejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="' and d.fecha<='";
    cadena+=finejercicio(ui.ejerciciocomboBox->currentText()).toString("yyyy/MM/dd");
    cadena+="'";
    if (aib) cadena+=" and aib"; else cadena+=" and not aib";
    cadena+=" and p.codigo=l.cuenta_fra and soportado"
	       " order by d.fecha,d.asiento,d.documento";
    query = ejecutarSQL(cadena);
    ui.progressBar->setMaximum(registros);
    int numorden=0;
    int numprog=1;
    QString cadnum;
    QString guardadoc,guardaprov;
    double base=0;
    double cuota=0;
    double cuotaefectiva=0;
    if ( query.isActive() ) {
          while ( query.next() )
              {
	        ui.progressBar->setValue(numprog);
                if (guardadoc!=query.value(0).toString() || query.value(0).toString().length()==0 
                    || numprog==1 || guardaprov!=query.value(2).toString()) numorden++; 
                guardadoc=query.value(0).toString();
                guardaprov=query.value(2).toString();
	        stream << "{\\tiny " << cadnum.setNum(numorden) << "} & {\\tiny "; 
	        stream << filtracad(query.value(0).toString()) << "} & {\\tiny "; // fra.
	        stream << query.value(1).toDate().toString("dd.MM.yyyy") << "} & {\\tiny "; // fecha
	        stream <<  query.value(2).toString() << "} & {\\tiny "; // cuenta
	        stream <<  filtracad(query.value(3).toString()) << "} & {\\tiny "; // proveedor
	        if (aib || eib) stream <<  nifcomunitariocta(query.value(2).toString()) << "} & {\\tiny "; // cif
		else stream <<  cifcta(query.value(2).toString()) << "} & {\\tiny "; // cif
	        // stream <<  cifcta(query.value(2).toString()) << "} & {\\tiny "; // cif
	        if (numeracionrelativa())
		   {
		    qlonglong primas=primasejerciciodelafecha(query.value(1).toDate());
		    qlonglong relativo=query.value(4).toLongLong()-primas+1;
		    QString cadas; cadas.setNum(relativo);
		    stream << cadas << "} & {\\tiny "; // asiento
		   }
                 else stream <<  query.value(4).toString() << "} & {\\tiny "; // asiento
	        stream <<  formateanumerosep(query.value(5).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // base iva
	        stream <<  formateanumerosep(query.value(6).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // tipo
	        stream <<  formateanumerosep(query.value(7).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // cuota
	        stream <<  formateanumerosep(query.value(8).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // total
	        stream <<  formateanumerosep(query.value(9).toDouble(),comadecimal,decimales)
                       << "} & {\\tiny "; // prorrata
                stream <<  formateanumerosep(query.value(10).toDouble(),comadecimal,decimales) << "} \\\\ \n  " 
                       << "\\hline\n"; // cuota corregida prorrata
	        numprog++;
	        base+=query.value(5).toDouble();
	        cuota+=query.value(7).toDouble();
                cuotaefectiva=query.value(8).toDouble();
	      }
      }

    stream << "\\multicolumn{7}{|r|} {\\textbf{";
   // --------------------------------------------------------------------------------------
    stream << tr("SUMAS TOTALES:") << "}} ";
    stream << " & {\\tiny " << formateanumerosep(base,comadecimal,decimales) << "} & & {\\tiny ";
    stream << formateanumerosep(cuota,comadecimal,decimales) << "} &  {\\tiny ";
    stream << formateanumerosep(base+cuota,comadecimal,decimales) << "} & & {\\tiny ";
    stream << formateanumerosep(cuotaefectiva,comadecimal,decimales);
    stream <<  "} \\\\ \n";
    stream << "\\hline" << "\n";


    stream << "\\end{longtable}" << "\n";
    stream << "\\end{center}" << "\n";
    stream << "\\end{landscape}\n";

    stream << "% FIN_CUERPO\n";
    stream << "\\end{document}" << "\n";
    
    fichero.close();

    ui.progressBar->reset();

}
