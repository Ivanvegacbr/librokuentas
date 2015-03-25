#include "ivacombobox.h"
#include "basedatos.h"
#include "funciones.h"
#include "pidenombre.h"

ivaComboBox::ivaComboBox(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    // Tenemos que cargar clave IVA por defecto y resto de IVA'S en el combo box
    comadecimal=haycomadecimal();
    decimales=haydecimales();
    QString pasalinea;
    QString Clavedefecto, laclave;
    double tipo;
    double re;
    QString qdescrip;
    QString convert;
    Clavedefecto=clave_iva_defecto();
    if (Clavedefecto.length()>0 && existeclavetipoiva(Clavedefecto,&tipo,&re,&qdescrip))
        {
                pasalinea=Clavedefecto;
                if (!conigic()) pasalinea+=tr(" // IVA:");
                    else pasalinea+=tr(" // IGIC:");
                convert.setNum(tipo,'f',2);
                if (comadecimal) pasalinea+=convacoma(convert);
                    else pasalinea+=convert;
                pasalinea+=tr(" RE:");
                convert.setNum(re,'f',2);
                if (comadecimal) pasalinea+=convacoma(convert);
                    else pasalinea+=convert;
                ui.ClaveivaComboBox->insertItem ( 0,pasalinea) ;
        }
    ui.ClaveivaComboBox->insertItem ( 1,diario_no_asignado() ) ;
    ui.ClaveivaComboBox->insertItem ( 2,iva_mixto() );
    // ahora cargamos el resto de los tipos de IVA

     QString cadquery;
     cadquery="SELECT clave,tipo,re from tiposiva where clave != '";
     cadquery+=Clavedefecto;
     cadquery+="';";

     QSqlQuery query = ejecutarSQL(cadquery);

     if ( query.isActive() )
        {
          while (query.next())
             {
              laclave=query.value(0).toString();
              tipo=query.value(1).toDouble();
              re=query.value(2).toDouble();
                   qdescrip=query.value(3).toString();
              pasalinea=laclave;
              pasalinea+=tr(" // IVA:");
              convert.setNum(tipo,'f',2);
              if (comadecimal) pasalinea+=convacoma(convert);
                  else pasalinea+=convert;
              pasalinea+=tr(" RE:");
              convert.setNum(re,'f',2);
              if (comadecimal) pasalinea+=convacoma(convert);
                  else pasalinea+=convert;
              ui.ClaveivaComboBox->insertItem ( -1,pasalinea) ;
                 }
        }

     connect(ui.ClaveivaComboBox,SIGNAL(activated(int)),this,SLOT(comboIvaCambiado()));

}

void ivaComboBox::comboIvaCambiado()
{
    emit ivaActivado(ui.ClaveivaComboBox->currentText());
}

QString ivaComboBox::texto()
{
    return ui.ClaveivaComboBox->currentText();
}

int ivaComboBox::calcularIvas(QString *claveiva, double *valor, double *base, double *bi, bool vbase)
{
    QString cadenaiva = ui.ClaveivaComboBox->currentText();

    if (cadenaiva == diario_no_asignado())	return 0;

        bool bien;
        QString cadena;
        double re;
        if (cadenaiva == iva_mixto()){
                pidenombre *iva = new pidenombre();
                iva->asignanombreventana(tr("Introducir valor"));
                iva->asignaetiqueta(tr("Cuota IVA:"));
                int resultado = iva->exec();
                *bi = calculaValor( iva->contenido() );
                if (!resultado==QDialog::Accepted) return 0;
                if (bi <= 0){
                        QMessageBox::critical(this,tr("Tabla de apuntes"),
                                                tr("ERROR: Debe introducir un valor u operación correctos"));
                        return 0;
                }
                iva->asignaetiqueta(tr("Cuota RE:"));
                iva->setContenido(cadena.setNum(*bi,'f',2));
                resultado = iva->exec();
                re = calculaValor( iva->contenido() );
                if (!resultado==QDialog::Accepted) return 0;
                if (re <= 0 || re == *bi){
                        QMessageBox::warning(this,tr("Tabla de apuntes"),
                                                tr("El valor del RE se establecerá en zero (0.00)"));
                        re = 0.0;
                }
                //if (ui.Tablaapuntes->item(fila,0)==0) rellenaLinea(fila,TRUE);
                if (vbase){
                    base = valor;
                    *valor = *base+*bi+re;
                }else{
                    *base = *valor-*bi-re;
                }
                return 1;
        }
        QString extracto=cadenaiva.section(':',1,1);
        QString recargo=cadenaiva.section(':',2,2);
        QString clave=cadenaiva.section("//",0,0);
        //if (ui.Tablaapuntes->item(fila,0)==0) rellenaLinea(fila,TRUE);
        clave.remove(' ');
        *claveiva = clave;
        extracto.remove(tr(" RE"));

        qDebug() << "Iva+re: " << extracto.remove(tr(" RE")) << "+" << recargo;

        double tipo = extracto.toDouble(& bien)/100;
        if (!bien) tipo=0;
        re = recargo.toDouble(& bien)/100;
        if (!bien) re=0;

        if (vbase){
            base = valor;
            *valor = *base*(tipo+re+1.00);
        }else{
            *base = *valor/(tipo+re+1.00);
        }
        *bi = *base*tipo;
        return 1;


}

int ivaComboBox::setIndice(QString qdiario)
{
 for (int veces=0; veces < ui.ClaveivaComboBox->count(); veces++)
     {
       if (ui.ClaveivaComboBox->itemText(veces).startsWith( qdiario )) ui.ClaveivaComboBox->setCurrentIndex(veces);
     }
 return ui.ClaveivaComboBox->currentIndex();
}
