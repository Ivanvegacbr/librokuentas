#include "basedatos.h"
#include <QMessageBox>
#include "funciones.h"

QString ejerciciodelafecha(QDate fecha)
{
  QString cadena="select codigo from ejercicios where apertura<='";
  cadena+=fecha.toString("yyyy.MM.dd");
  cadena+="' and cierre>='";
  cadena+=fecha.toString("yyyy.MM.dd");
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
      return query.value(0).toString();
     }
  return "";
}

void calculaprimerasientoejercicio(QString ejercicio)
{
    QString cadena="select apertura,cierre from ejercicios where codigo='";
    cadena+=ejercicio;
    cadena+="'";
    QSqlQuery query = ejecutarSQL(cadena);
    if (query.next())
       {
	   QString cad2="select min(asiento) from diario where fecha>='";
           cad2+=query.value(0).toDate().toString("yyyy.MM.dd");
           cad2+="' and fecha<='";
           cad2+=query.value(1).toDate().toString("yyyy.MM.dd");
           cad2+="'";
           QSqlQuery query2 = ejecutarSQL(cad2);
           QString cadnum;
           if (query2.next())
	      {
		  cadnum=query2.value(0).toString();
                  cad2="update ejercicios set primerasiento=";
                  cad2+=cadnum;
                  cad2+=" where codigo='";
                  cad2+=ejercicio;
                  cad2+="'";
                  ejecutarSQL(cad2);
	      }
       }
}

void calculaprimerosasientos()
{
    QSqlQuery query = ejecutarSQL("select codigo from ejercicios");
    while (query.next())
       {
	   calculaprimerasientoejercicio(query.value(0).toString());
       }
}

bool numeracionrelativa()
{
    QSqlQuery query = ejecutarSQL("select numrel from configuracion");
    if (query.next())
	return query.value(0).toBool();
    return false;
}

qlonglong primerasiento(QString ejercicio)
{
    QString cadena="select primerasiento from ejercicios where codigo='";
    cadena+=ejercicio;
    cadena+="'";
    QSqlQuery query = ejecutarSQL(cadena);

    if (query.next())
		return query.value(0).toLongLong();
    return 0;  
}

qlonglong primasejerciciodelafecha(QDate fecha)
{
  QString cadena="select primerasiento from ejercicios where apertura<='";
  cadena+=fecha.toString("yyyy.MM.dd");
  cadena+="' and cierre>='";
  cadena+=fecha.toString("yyyy.MM.dd");
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
      return query.value(0).toLongLong();
     }
  return 0;
}

QString numrelativa(QString numabsoluta)
{
    QString cadena="select fecha from diario where asiento=";
    cadena+=numabsoluta;
    QSqlQuery query = ejecutarSQL(cadena);
    query.next();
    QString ejercicio=ejerciciodelafecha(query.value(0).toDate());
    QString cadnum;
    qlonglong absoluta=numabsoluta.toLongLong();
    cadnum.setNum(absoluta-primerasiento(ejercicio)+1);
    return cadnum;
}

QDate inicioejercicio(QString ejercicio)
{
  QDate fecha;
  QString cadena="select apertura from ejercicios where codigo='";
  cadena+=ejercicio;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
      return query.value(0).toDate();
     }
  return fecha.currentDate();
}

QDate finejercicio(QString ejercicio)
{
  QDate fecha;
  QString cadena="select cierre from ejercicios where codigo='";
  cadena+=ejercicio;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
      return query.value(0).toDate();
     }
  return fecha.currentDate();
}

QString ultimonumasiento(QString filtro)
{
 QString cadquery;
 cadquery="SELECT max(asiento) from diario";
 if (filtro.length()>0)
   {
     cadquery+=" where ";
     cadquery+=filtro;
   }
 cadquery+=";";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
    }
 return "";
}

QString descripcioncuenta(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT descripcion from plancontable where codigo = '";
 cadquery+=qcodigo;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.next() )
    {
     return query.value(0).toString();
    }
 return QString("");
}

double saldocuentaendiarioejercicio(QString cuenta,QString ejercicio)
{
 QString cadquery="select sum(debe-haber) from diario where cuenta='";
 cadquery+=cuenta;
 cadquery+="' and fecha>='";
 cadquery+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
 cadquery+="' and fecha<='";
 cadquery+=finejercicio(ejercicio).toString("yyyy.MM.dd");
 cadquery+="' and char_length(ci)=0"; 
  QSqlQuery query = ejecutarSQL(cadquery);
  if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toDouble();
         }
    }
  return 0;
 
}

QString nombreempresa()
{
 QString cadquery;
 cadquery="SELECT empresa from configuracion ;";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
      }
 return "";
}

int anchocuentas()
{
 QString cadquery;
 cadquery="SELECT anchocuentas from configuracion ;";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toInt();
           }
      }
 return 0;
}

bool sobreescribeproxasiento()
{
    QSqlQuery query = ejecutarSQL("select prox_asiento from configuracion");

    if ( (query.isActive()) && (query.first()) ) {
        QString cadquery = "SELECT count(asiento) from diario where asiento=" + query.value(0).toString();
        query = ejecutarSQL(cadquery);
        if ( (query.isActive()) && (query.first()) )
        {
            if (query.value(0).toInt()>0) return true;
        }
    }
    return false;
}

qlonglong proximoAsiento ()
{
    QSqlQuery query = ejecutarSQL("select prox_asiento from configuracion");
    qlonglong vnum = 0;
    if ( (query.isActive()) && (query.first()) )
    {
        vnum = query.value(0).toLongLong();
        if (vnum == 0) vnum = 1;
    }
    else vnum = 1;

    return vnum;
}

qlonglong proximoPase ()
{
    QSqlQuery query = ejecutarSQL("select prox_pase from configuracion");
    qlonglong vnum = 0;
    if ( (query.isActive()) && (query.first()) )
    {
        vnum = query.value(0).toLongLong();
        if (vnum == 0) vnum = 1;
    }
    else vnum = 1;

    return vnum;
}

int existecodigoplan(QString cadena,QString *qdescrip)
{
 QString cadquery;
 cadquery="SELECT codigo,descripcion from plancontable where codigo = '";
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

int escuentadeivasoportado(const QString subcuenta)
{
 QString cadquery, qcuenta, qcompara;
 cadquery="SELECT cuenta_iva_soportado from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           qcuenta=query.value(0).toString();
	   if (qcuenta.length()==0) return 0;
           qcompara=subcuenta.left(qcuenta.length());
	   if (qcompara.compare(qcuenta)==0) return 1; else return 0;
           }
      }
 return 0;
}

int escuentadeivarepercutido(const QString subcuenta)
{
 QString cadquery, qcuenta, qcompara;
 cadquery="SELECT cuenta_iva_repercutido from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           qcuenta=query.value(0).toString();
	   if (qcuenta.length()==0) return 0;
           qcompara=subcuenta.left(qcuenta.length());
	   if (qcompara.compare(qcuenta)==0) return 1; else return 0;
           }
      }
 return 0;
}

int ejerciciocerrado(QString ejercicio)
{
  QString cadena="select cerrado from ejercicios where codigo='";
  cadena+=ejercicio;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
       if (query.value(0).toBool()) return 1;
     }
  return 0;
}

/*
void borraasientos(QString asientoinicial,QString asientofinal)
{
 // primero borramos y actualizamos registros de iva y vencimientos
 QSqlDatabase contabilidad=QSqlDatabase::database();
 contabilidad.transaction();

 QString cadena="select pase,debe,haber,cuenta from diario where asiento>=";
 cadena+=asientoinicial;
 cadena+=" and asiento<=";
 cadena+=asientofinal;
 QSqlQuery query = ejecutarSQL(cadena);
 while (query.next())
     {
      QString cad2="delete from libroiva where pase=";
      cad2+=query.value(0).toString();
      ejecutarSQL(cad2);
      
      cad2="delete from vencimientos where pase_diario_operacion=";
      cad2+=query.value(0).toString();
      ejecutarSQL(cad2);
      
      cad2="update vencimientos set pase_diario_vencimiento=0, pendiente=TRUE where pase_diario_vencimiento=";
      cad2+=query.value(0).toString();
      ejecutarSQL(cad2);
      
      cad2="update saldossubcuenta set saldo=saldo-(";
      cad2+=query.value(1).toString();
      cad2+=")+(";
      cad2+=query.value(2).toString();
      cad2+=") where codigo='";
      cad2+=query.value(3).toString();
      cad2+="'";
      ejecutarSQL(cad2);
     }
 cadena="delete from diario where asiento>=";
 cadena+=asientoinicial;
 cadena+=" and asiento<=";
 cadena+=asientofinal;
 ejecutarSQL(cadena);
 contabilidad.commit();
}
*/

bool paseenasiento(QString pase, QString asiento)
{
  QString cadena="select pase from diario where pase=";
  cadena+=pase;
  cadena+=" and asiento=";
  cadena+=asiento;
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           if (query.value(0).toString()==pase) return true;
           }
    }
  return false;

}


int subgrupocongrupo(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from plancontable where codigo = ";
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


int cuentaconsubgrupo(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from plancontable where codigo = ";
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


int codigoconcuenta3digitos(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from plancontable where codigo = ";
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

int unicoCodigoSubcuenta(QString *qcodigo,QString qdescrip)
{
	QString ancho;
	ancho.setNum(anchocuentas());
	QString cadquery;
 cadquery="SELECT codigo from plancontable where char_length(codigo) = ";
 cadquery+=ancho;
 cadquery+=" and position(upper('";
 cadquery+=qdescrip;
 cadquery+="') in upper(descripcion))=1;";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()==1)
         {
           query.first();
           *qcodigo=query.value(0).toString();
           //*qdescrip=query.value(1).toString();
           return 1;
           }
      }
 return 0;
}

void insertaenplan(QString codigo,QString descripcion)
{
 QString cadena;
 if (!existecodigoplan(codigo,&cadena))
     {
      QString cadquery;
      cadquery="INSERT INTO plancontable (codigo,descripcion) VALUES ('";
      cadquery+=codigo;
      cadquery+="','";
      cadquery+=descripcion;
      cadquery+="');";
      ejecutarSQL(cadquery);
     }
}

void guardacambiosplan(QString codigo,QString descripcion)
{
 QString cadquery;
 cadquery="UPDATE plancontable SET descripcion='";
 cadquery+=descripcion;
 cadquery+="' WHERE codigo='";
 cadquery+=codigo;
 cadquery+="';";
 ejecutarSQL(cadquery);

}

int itemplaneliminado(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT codigo from plancontable where char_length(codigo) > ";
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

cadquery="delete from plancontable where codigo = '";
cadquery+=qcodigo;
cadquery+="';";
ejecutarSQL(cadquery);
    
return 1;
}

void eliminasubcuenta(QString qcodigo)
{
 QString cadquery;
 cadquery="delete from datossubcuenta where cuenta = '";
 cadquery+=qcodigo;
 cadquery+="';";
 ejecutarSQL(cadquery);


 cadquery="delete from plancontable where codigo = '";
 cadquery+=qcodigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
 
 cadquery="delete from saldossubcuenta where codigo = '";
 cadquery+=qcodigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
 
 return;
}


int cuentaendiario(QString cadena)
{
 QString cadquery;
 cadquery="SELECT cuenta from diario where cuenta = '";
 cadquery+=cadena;
 cadquery+="';";
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

int existendatosaccesorios(QString cuenta, QString *razon, QString *ncomercial, QString *cif,
            QString *nifcomunitario, QString *domicilio, QString *poblacion,
            QString *codigopostal, QString *provincia, QString *pais,
            QString *tfno, QString *fax, QString *email, QString *observaciones,
            QString *ccc, QString *cuota)
{

 QString cadquery;
 cadquery="SELECT cuenta,razon,nombrecomercial,cif,nifcomunitario,domicilio,poblacion,";
 cadquery+="codigopostal,provincia,pais,tfno,fax,email,observaciones,ccc,cuota ";
 cadquery+=" from datossubcuenta where cuenta = '";
 cadquery+=cuenta;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           *razon=query.value(1).toString();
           *ncomercial=query.value(2).toString();
           *cif=query.value(3).toString();
           *nifcomunitario=query.value(4).toString();
           *domicilio=query.value(5).toString();
           *poblacion=query.value(6).toString();
           *codigopostal=query.value(7).toString();
           *provincia=query.value(8).toString();
           *pais=query.value(9).toString();
           *tfno=query.value(10).toString();
           *fax=query.value(11).toString();
           *email=query.value(12).toString();
           *observaciones=query.value(13).toString();
           *ccc=query.value(14).toString();
           *cuota=query.value(15).toString();
           return 1;
          }
      }
 return 0;

}

void guardadatosaccesorios(QString cuenta, QString razon, QString ncomercial,QString cif,
            QString nifcomunitario, QString domicilio, QString poblacion,
            QString codigopostal, QString provincia, QString pais,
            QString tfno, QString fax, QString email, QString observaciones,
            QString ccc, QString cuota)
{
 QString qdescrip;
 if (!existecodigoplan(cuenta,&qdescrip)) return;

 QString cadquery;
 cadquery="SELECT cuenta from datossubcuenta where cuenta = '";
 cadquery+=cuenta;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           cadquery="UPDATE datossubcuenta set razon ='";
           cadquery+=razon;
           cadquery+="', ";
           cadquery+="nombrecomercial ='";
           cadquery+=ncomercial;
           cadquery+="', ";
           cadquery+="cif ='";
           cadquery+=cif;
           cadquery+="', ";
           cadquery+="nifcomunitario ='";
           cadquery+=nifcomunitario;
           cadquery+="', ";
           cadquery+="domicilio ='";
           cadquery+=domicilio;
           cadquery+="', ";
           cadquery+="poblacion ='";
           cadquery+=poblacion;
           cadquery+="', ";
           cadquery+="codigopostal ='";
           cadquery+=codigopostal;
           cadquery+="', ";
           cadquery+="provincia ='";
           cadquery+=provincia;
           cadquery+="', ";
           cadquery+="pais ='";
           cadquery+=pais;
           cadquery+="', ";
           cadquery+="tfno ='";
           cadquery+=tfno;
           cadquery+="', ";
           cadquery+="fax ='";
           cadquery+=fax;
           cadquery+="', ";
           cadquery+="email ='";
           cadquery+=email;
           cadquery+="', ";
           cadquery+="observaciones ='";
           cadquery+=observaciones;
           cadquery+="', ";
           cadquery+="ccc ='";
           cadquery+=ccc;
           cadquery+="',";
           cadquery+="cuota='";
           cadquery+=cuota;
           cadquery+="' where cuenta ='";
           cadquery+=cuenta;
           cadquery+="';";
           ejecutarSQL(cadquery);
          }
       else
            {
              cadquery="insert into datossubcuenta (cuenta,razon,nombrecomercial,cif,";
              cadquery+="nifcomunitario,domicilio,poblacion,codigopostal,";
              cadquery+="provincia,pais,tfno,fax,email,observaciones,ccc,cuota) ";
              cadquery+="values('";
              cadquery+=cuenta;
              cadquery+="', '";
              cadquery+=razon;
              cadquery+="', '";
              cadquery+=ncomercial;
              cadquery+="', '";
              cadquery+=cif;
              cadquery+="', '";
              cadquery+=nifcomunitario;
              cadquery+="', '";
              cadquery+=domicilio;
              cadquery+="', '";
              cadquery+=poblacion;
              cadquery+="', '";
              cadquery+=codigopostal;
              cadquery+="', '";
              cadquery+=provincia;
              cadquery+="', '";
              cadquery+=pais;
              cadquery+="', '";
              cadquery+=tfno;
              cadquery+="', '";
              cadquery+=fax;
              cadquery+="', '";
              cadquery+=email;
              cadquery+="', '";
              cadquery+=observaciones;
              cadquery+="','";
              cadquery+=ccc;
              cadquery+="','";
              cadquery+=cuota;
              cadquery+="')";
              ejecutarSQL(cadquery);
            }
      }

}

void eliminadatosaccesorios(QString qcodigo)
{
 QString cadquery;
 cadquery="delete from datossubcuenta where cuenta = '";
 cadquery+=qcodigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

bool conanalitica(void)
{
    QSqlQuery query = ejecutarSQL("select analitica from configuracion");
    if (query.next())
		return query.value(0).toBool();
    return false;
}

bool conigic(void)
{
    QSqlQuery query = ejecutarSQL("select igic from configuracion");
    if (query.next())
		return query.value(0).toBool();
    return false;
}

int existecodigoconcepto(QString cadena,QString *qdescrip)
{
 QString cadquery;
 cadquery="SELECT clave,descripcion from conceptos where clave = '";
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

void guardacambiosconcepto(QString codigo,QString descripcion)
{
 QString cadquery;
 cadquery="UPDATE conceptos SET descripcion='";
 cadquery+=descripcion;
 cadquery+="' WHERE clave='";
 cadquery+=codigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

void insertaenconceptos(QString codigo,QString descripcion)
{
 QString cadquery;
 cadquery="INSERT INTO conceptos (clave,descripcion) VALUES ('";
 cadquery+=codigo;
 cadquery+="','";
 cadquery+=descripcion;
 cadquery+="');";
 ejecutarSQL(cadquery);
}

void eliminaconcepto(QString qcodigo)
{
 QString cadquery;
 cadquery="delete from conceptos where clave = '";
 cadquery+=qcodigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

int existeclavetipoiva(QString cadena,double *tipo,double *re,QString *qdescrip)
{
 QString cadquery;
 cadquery="SELECT clave,tipo,re,descripcion from tiposiva where clave = '";
 cadquery+=cadena;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           *qdescrip=query.value(3).toString();
	   *tipo=query.value(1).toDouble();
	   *re=query.value(2).toDouble();
           return 1;
           }
      }
 return 0;
}

QString clave_iva_defecto(void)
{
 QString cadquery, qclave="";
 cadquery="SELECT clave_iva_defecto from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           qclave=query.value(0).toString();
           }
      }
 return qclave;

}

int esCuentadeGenero(const QString subcuenta)
{
	QString cadquery, qcuentas, qcompara;
	cadquery="SELECT clave_gastos from configuracion";
	QSqlQuery query = ejecutarSQL(cadquery);
	if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           qcuentas=query.value(0).toString();
	   if (qcuentas.length()==0) return 0;

           int partes=qcuentas.count(',');
           for (int veces=0;veces<=partes;veces++)
             {
              QString selec=qcuentas.section(',',veces,veces).trimmed();
              qcompara=subcuenta.left(selec.length());
    	      if (qcompara.compare(selec)==0 && selec.length()==3) return 1;
             }
           }
    }
	return 0;
}

int escuentadegasto(const QString subcuenta)
{
 QString cadquery, qcuentas, qcompara;
 cadquery="SELECT clave_gastos from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           qcuentas=query.value(0).toString();
	   if (qcuentas.length()==0) return 0;

           int partes=qcuentas.count(',');
           for (int veces=0;veces<=partes;veces++)
             {
              QString selec=qcuentas.section(',',veces,veces).trimmed();
              qcompara=subcuenta.left(selec.length());
    	      if (qcompara.compare(selec)==0) return 1;
             }
           }
      }
 return 0;
}

int escuentadeingreso(const QString subcuenta)
{
 QString cadquery, qcuentas, qcompara;
 cadquery="SELECT clave_ingresos from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);

 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           qcuentas=query.value(0).toString();
	   if (qcuentas.length()==0) return 0;

           int partes=qcuentas.count(',');
           for (int veces=0;veces<=partes;veces++)
             {
              QString selec=qcuentas.section(',',veces,veces).trimmed();
              qcompara=subcuenta.left(selec.length());
    	      if (qcompara.compare(selec)==0) return 1;
             }
           }
      }
 return 0;
}

int existecodigosaldosubcuenta(QString cadena)
{
 QString cadquery;
 cadquery="SELECT codigo from saldossubcuenta where codigo = '";
 cadquery+=cadena;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return 1;
           }
      }
 return 0;
  }

void insertasaldosubcuenta(QString codigo)
{
 QString cadquery;
 cadquery="INSERT INTO saldossubcuenta (codigo,saldo,saldomedio1,saldomedio2) VALUES ('";
 cadquery+=codigo;
 cadquery+="',0,0,0);";
 ejecutarSQL(cadquery);
}

QString cuentadeivasoportado()
{
QString cadquery;
 cadquery="SELECT cuenta_iva_soportado from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
      }
 return "";
}

QString cuentadeivarepercutido()
{
 QString cadquery;
 cadquery="SELECT cuenta_iva_repercutido from configuracion";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
      }
 return "";

}

void borraAsientoEjercicio(QString asiento,QString ejercicio)
{
 // primero borramos y actualizamos registros de iva y vencimientos
 QSqlDatabase contabilidad=QSqlDatabase::database();
 contabilidad.transaction();
 QString cad2;
 QString cadena="select pase,debe,haber,cuenta from diario where asiento=";
 cadena+=asiento;
 cadena+=" and fecha>='";
 cadena+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
 cadena+="' and fecha<='";
 cadena+=finejercicio(ejercicio).toString("yyyy.MM.dd");
 cadena+="'";
 QSqlQuery query = ejecutarSQL(cadena);
 while (query.next())
     {
      cad2="delete from libroiva where pase=";
      cad2+=query.value(0).toString();
      ejecutarSQL(cad2);
      
      /*cad2="delete from vencimientos where pase_diario_operacion=";
      cad2+=query.value(0).toString();
      ejecutarSQL(cad2);
      
      cad2="update vencimientos set pase_diario_vencimiento=0, pendiente=TRUE where pase_diario_vencimiento=";
      cad2+=query.value(0).toString();
      ejecutarSQL(cad2);*/
      
      cad2="update saldossubcuenta set saldo=saldo-(";
      cad2+=query.value(1).toString();
      cad2+=")+(";
      cad2+=query.value(2).toString();
      cad2+=") where codigo='";
      cad2+=query.value(3).toString();
      cad2+="'";
      ejecutarSQL(cad2);
     }
 cadena="delete from diario where asiento=";
 cadena+=asiento;
 cadena+=" and fecha>='";
 cadena+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
 cadena+="' and fecha<='";
 cadena+=finejercicio(ejercicio).toString("yyyy.MM.dd");
 cadena+="'";
 ejecutarSQL(cadena);
 contabilidad.commit();
 
}

void guardaFechaPago(QString cuenta, QString pase, QDate fecha , QString fact)
{
	QString cadquery;
	cadquery="UPDATE diario SET ci='";
	cadquery+=fecha.toString("yyyy-MM-dd");
	cadquery+="'";
	if (fact.length()==0){
		cadquery+=" WHERE pase='";
		cadquery+=pase;
		cadquery+="'";
	}else{
		cadquery+=" WHERE documento='";
		cadquery+=fact;
		cadquery+="'";
	}
	cadquery+=" AND cuenta='";
	cadquery+=cuenta;
	cadquery+="';";
	ejecutarSQL(cadquery);
}

QString subcuentaanterior(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT max(codigo) from saldossubcuenta where codigo < '";
 cadquery+=qcodigo;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.next() )
    {
     return query.value(0).toString();
    }
 return "";
}


QString subcuentaposterior(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT min(codigo) from saldossubcuenta where codigo > '";
 cadquery+=qcodigo;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.next() )
    {
     return query.value(0).toString();
    }
 return "";
}

/*bool asientoenaib(QString asiento)
{
 QString cadena="select libroiva.aib from diario,libroiva where "
     "diario.asiento=";
 cadena+=asiento;
 cadena+=" and diario.pase=libroiva.pase";
 QSqlQuery query = ejecutarSQL(cadena);
  if ( query.isActive() )
    {
      while (query.next())
      {
	  if (query.value(0).toBool()) return true;
      }
    }
  return false;
}

bool asientoeneib(QString asiento)
{
 QString cadena="select libroiva.eib from diario,libroiva where "
     "diario.asiento=";
 cadena+=asiento;
 cadena+=" and diario.pase=libroiva.pase";
 QSqlQuery query = ejecutarSQL(cadena);
  if ( query.isActive() )
    {
      while (query.next())
      {
	  if (query.value(0).toBool()) return true;
      }
    }
  return false;
}*/

int ejerciciocerrando(QString ejercicio)
{
  QString cadena="select cerrando from ejercicios where codigo='";
  cadena+=ejercicio;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
       if (query.value(0).toBool()) return 1;
     }
  return 0;
}

QDate fechaMaxAsiento(QString qasiento, QString ejercicio)
{
  QString cadena="select max(fecha) from diario where asiento='";
  cadena+=qasiento;
  cadena+="' and fecha>='";
  cadena+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
  cadena+="' and fecha<='";
  cadena+=finejercicio(ejercicio).toString("yyyy.MM.dd");
  cadena+="'";
  //cadena+=" ORDER by fecha DESC";
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toDate();
           }
    }
  return QDate::QDate();
}

QDate fechaMinAsiento(QString qasiento, QString ejercicio)
{
  QString cadena="select min(fecha) from diario where asiento='";
  cadena+=qasiento;
  cadena+="' and fecha>='";
  cadena+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
  cadena+="' and fecha<='";
  cadena+=finejercicio(ejercicio).toString("yyyy.MM.dd");
  cadena+="'";
 //cadena+=" ORDER by fecha DESC";
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toDate();
           }
    }
  return QDate::QDate();
}

QString diariodeasiento(QString qasiento)
{
  QString cadena="select diario from diario where asiento=";
  cadena+=qasiento;
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
    }
  return "";
}

int existeasiento(QString asiento, QString ejercicio)
{
 QString cadquery;
 cadquery="SELECT asiento from diario where asiento='";
 cadquery+=asiento;
 cadquery+="' and fecha>='";
  cadquery+=inicioejercicio(ejercicio).toString("yyyy.MM.dd");
  cadquery+="' and fecha<='";
  cadquery+=finejercicio(ejercicio).toString("yyyy.MM.dd");
  cadquery+="'";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return 1;
           }
      }
 return 0;
}

int existeAsientoEspera(QString asiento)
{
 QString cadquery;
 cadquery="SELECT asiento from borrador where asiento='";
 cadquery+=asiento;
 cadquery+="'";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return 1;
           }
      }
 return 0;
}

void cadvalorestipoiva(QString cadena,QString *tipo,QString *re)
{
 QString cadquery;
 cadquery="SELECT tipo,re from tiposiva where clave = '";
 cadquery+=cadena;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 *tipo="";
 *re="";
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
	   *tipo=query.value(0).toString();
	   *re=query.value(1).toString();
           }
      }
 return;
}

QString claveIva (QString pase)
{
	QString cadquery;
	cadquery="SELECT clave_iva from libroiva where pase = '";
	cadquery+=pase;
	cadquery+="';";
	QSqlQuery query = ejecutarSQL(cadquery);
	if (query.isActive() && query.first())
		return query.value(0).toString();
	return "";
}

double tipoivaefectivo(QString clave)
{

 QString cadquery;
 double tipo=0,re=0;
 cadquery="SELECT tipo,re from tiposiva where clave = '";
 cadquery+=clave;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
	   tipo=query.value(0).toDouble();
	   re=query.value(1).toDouble();
           return (tipo+re)/100;
         }
      }
 return 0;
   
}

double tipoivanore(QString clave)
{
 QString cadquery;
 double tipo=0;
 cadquery="SELECT tipo from tiposiva where clave = '";
 cadquery+=clave;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
	   tipo=query.value(0).toDouble();
           return (tipo)/100;
         }
      }
 return 0;
}

void actualizasaldo(QString cuenta,QString importe,bool cargo)
{
 QString cadq2;
 //QSqlQuery query2;
 cadq2="update saldossubcuenta set saldo=saldo";
 if (cargo) cadq2+="+"; else cadq2+="-";
 cadq2+=importe;
 cadq2+=" where codigo='";
 cadq2+= cuenta;
 cadq2+="';";
 ejecutarSQL(cadq2);
}

double saldocuentaendiario(QString cuenta)
{
 QString cadquery="select sum(debe-haber) from diario where cuenta='";
 cadquery+=cuenta;
 cadquery+="' and char_length(ci)=0";
  QSqlQuery query = ejecutarSQL(cadquery);
  if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toDouble();
         }
    }
  return 0;
 
}

double deudaCuentaenDiario(QString cuenta, QDate fecha)
{
	QString cadena = "select sum(debe-haber) from diario where fecha<='";
    cadena += fecha.toString("yyyy/MM/dd");
    cadena += "' and cuenta='";
    cadena += cuenta;
    cadena += "' and (STR_TO_DATE(ci,'%Y-%m-%d')>'";
    cadena += fecha.toString("yyyy/MM/dd");
    cadena += "' OR char_length(ci)=0);";
//qDebug() << "deuda en Diario:" << cadena;
    QSqlQuery query = ejecutarSQL(cadena);
    if ( (query.isActive()) && (query.first()) )
    {
        return query.value(0).toDouble();
    }
	return 0;
}

QString ejercicio_igual_o_maxigual(QDate fecha)
{
  QString cadena="select max(cierre) from ejercicios where cierre<='";
  cadena+=fecha.toString("yyyy.MM.dd");
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
  if (query.next())
     {
      return ejerciciodelafecha(query.value(0).toDate());
     }
  return "";

}

QString numAsiento(QString pase)
{
  QString cadquery="SELECT asiento from diario where pase=";
  cadquery+=pase;
  QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
    }
 return "";
}

int existeclaveiva(QString cadena,QString *qtipo,QString *qre,QString *qdescrip)
{
 QString cadquery;
 cadquery="SELECT clave,tipo,re,descripcion from tiposiva where clave = '";
 cadquery+=cadena;
 cadquery+="';";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           *qtipo=query.value(1).toString();
           *qre=query.value(2).toString();
           *qdescrip=query.value(3).toString();
           return 1;
           }
      }
 return 0;
}

void guardacambiostiposiva(QString clave,QString tipo,QString re,QString descripcion)
{
 QString cadquery;
 if (re.length()==0) re="0";
 cadquery="UPDATE tiposiva SET tipo="; 
 cadquery+=tipo;
 cadquery+=", re=";
 cadquery+=re;
 cadquery+=", descripcion='";
 cadquery+=descripcion;
 cadquery+="' WHERE clave='";
 cadquery+=clave;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

void insertatipoiva(QString clave,QString tipo, QString re, QString descripcion)
{
 QString cadquery;
 if (re.length()==0) re="0";
 cadquery="INSERT INTO tiposiva (clave,tipo,re,descripcion) VALUES ('";
 cadquery+=clave;
 cadquery+="',";
 cadquery+=tipo;
 cadquery+=",";
 cadquery+=re;
 cadquery+=",'";
 cadquery+=descripcion;
 cadquery+="');";
 ejecutarSQL(cadquery);
}

void eliminatipoiva(QString qclave)
{
 QString cadquery;
 cadquery="delete from tiposiva where clave = '";
 cadquery+=qclave;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

QString nifcomunitariocta(QString codigo)
{
  QString cadquery="SELECT nifcomunitario from datossubcuenta where cuenta='";
  cadquery+=codigo;
  cadquery+="'";
  QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
    }
 return "";
}

QString cifcta(QString codigo)
{
  QString cadquery="SELECT cif from datossubcuenta where cuenta='";
  cadquery+=codigo;
  cadquery+="'";
  QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
    }
 return "";
}

void desbloqueasaldosmedios()
{
   QString cadena="update configuracion set bloqsaldosmedios=FALSE;";  
   ejecutarSQL(cadena);

}

bool int_asientos_ej_cerrado(QString asientoinicial,QString asientofinal)
{
 QString cadena="select fecha from diario where asiento>=";
 cadena+=asientoinicial;
 cadena+=" and asiento<=";
 cadena+=asientofinal;
 QSqlQuery query = ejecutarSQL(cadena);
 while (query.next())
     {
      if (fechadejerciciocerrado(query.value(0).toDate())) return true;
     }
 return false;
}

void pasasaldo(QString cuenta,QString importe,bool cargo)
{
 QString cadq2;
 //QSqlQuery query2;
 cadq2="update saldossubcuenta set saldo=";
 if (!cargo) cadq2+="-";
 cadq2+=importe;
 cadq2+=" where codigo='";
 cadq2+= cuenta;
 cadq2+="';";
 ejecutarSQL(cadq2);
}

bool cuentaenlibroiva(QString cuenta)
{
  QString cadena="select cuenta_fra from libroiva where cuenta_fra='";
  cadena+=cuenta;
  cadena+="'";
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.next())
         {
           return true;
         }
    }
  return false;  
}

bool paseapertura(QString pase)
{
  QString cadena="select diario from diario where pase=";
  cadena+=pase;
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           if (query.value(0).toString()==diario_apertura()) return true;
           }
    }
  return false;

}

bool paseenlibroivaeib(QString pase)
{
  QString cadena="select pase from libroiva where pase=";
  cadena+=pase;
  cadena+=" and eib";
  QSqlQuery query = ejecutarSQL(cadena);
   if ( query.isActive() )
    {
      if (query.next())
         {
           return true;
         }
    }
  return false;  
}

void actualizasaldos()
{
  QString cadquery="update saldossubcuenta set saldo=0";
  ejecutarSQL(cadquery);
  cadquery="select codigo from saldossubcuenta";
  QSqlQuery query = ejecutarSQL(cadquery);
  if ( query.isActive() )
    {
      while (query.next())
         {
          double saldo=saldocuentaendiario(query.value(0).toString());
		  QString cadnum;
		  cadnum.setNum(saldo,'f',2);
		  QString cadena2="update saldossubcuenta set saldo=";
		  cadena2+=cadnum;
		  cadena2+=" where codigo='";
		  cadena2+=query.value(0).toString();
		  cadena2+="'";
		  ejecutarSQL(cadena2);
         }
    }
}

QString versionbd()
{
QString cadquery;
 cadquery="SELECT version from configuracion ;";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString();
           }
      }
 return "";
}

bool codsubdivis(QString qcodigo)
{
 // evaluamos si el código suministrado posee subcódigos 
 // que no sean subcuentas
 QString cadquery="SELECT codigo from plancontable where char_length(codigo) > ";
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


//Revisar
void cambiacuentaconta(QString origen, QString destino)
{
 QString cadena;
 cadena="update amortfiscalycontable set cuenta_activo='";
 cadena+=destino;
 cadena+="' where cuenta_activo='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);
 cadena="update amortfiscalycontable set cuenta_am_acum='";
 cadena+=destino;
 cadena+="' where cuenta_am_acum='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);
 cadena="update amortfiscalycontable set cuenta_gasto='";
 cadena+=destino;
 cadena+="' where cuenta_gasto='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update borrador set cuenta='";
 cadena+=destino;
 cadena+="' where cuenta='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update datossubcuenta set cuenta='";
 cadena+=destino;
 cadena+="' where cuenta='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update diario set cuenta='";
 cadena+=destino;
 cadena+="' where cuenta='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update libroiva set cta_base_iva='";
 cadena+=destino;
 cadena+="' where cta_base_iva='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update libroiva set cuenta_fra='";
 cadena+=destino;
 cadena+="' where cuenta_fra='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);


 cadena="update planamortizaciones set cuenta_activo='";
 cadena+=destino;
 cadena+="' where cuenta_activo='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update planamortizaciones set cuenta_am_acum='";
 cadena+=destino;
 cadena+="' where cuenta_am_acum='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update planamortizaciones set cuenta_gasto='";
 cadena+=destino;
 cadena+="' where cuenta_gasto='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update amortpers set cuenta='";
 cadena+=destino;
 cadena+="' where cuenta='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update saldossubcuenta set codigo='";
 cadena+=destino;
 cadena+="' where codigo='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update vencimientos set cta_ordenante='";
 cadena+=destino;
 cadena+="' where cta_ordenate='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);

 cadena="update vencimientos set cta_tesoreria='";
 cadena+=destino;
 cadena+="' where cta_tesoreria='";
 cadena+=origen;
 cadena+="'";
 ejecutarSQL(cadena);
}

int existecodigodiario(QString cadena,QString *qdescrip)
{
 QString cadquery;
 cadquery="SELECT codigo,descripcion from diarios where codigo = '";
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

void guardacambiosdiario(QString codigo,QString descripcion)
{
 QString cadquery;
 cadquery="UPDATE diarios SET descripcion='";
 cadquery+=descripcion;
 cadquery+="' WHERE codigo='";
 cadquery+=codigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

void insertaendiarios(QString codigo,QString descripcion)
{
 QString cadquery;
 cadquery="INSERT INTO diarios (codigo,descripcion) VALUES ('";
 cadquery+=codigo;
 cadquery+="','";
 cadquery+=descripcion;
 cadquery+="');";
 ejecutarSQL(cadquery);
}

int eliminadiario(QString qcodigo)
{
 QString cadquery;
 cadquery="SELECT diario from diario where diario = '";
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


 cadquery="delete from diarios where codigo = '";
 cadquery+=qcodigo;
 cadquery+="';";
 ejecutarSQL(cadquery);
 return 1;
}

QString grupoGastos()
{
 QString cadquery;
 cadquery="SELECT clave_gastos from configuracion ;";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString().left(1);
           }
      }
 return "";
}

QString grupoIngresos()
{
 QString cadquery;
 cadquery="SELECT clave_ingresos from configuracion ;";
 QSqlQuery query = ejecutarSQL(cadquery);
 if ( query.isActive() )
    {
      if (query.size()>0)
         {
           query.first();
           return query.value(0).toString().left(1);
           }
      }
 return "";
}

QStringList listaOrdenadaSubcuentas(QString cuenta)
{
	QString cadena="select codigo from plancontable where position('";
    cadena+=cuenta;
    cadena+="' in codigo)=1 and char_length(codigo)=";
    QString cadnum;
    cadnum.setNum(anchocuentas());
    cadena+=cadnum;
    cadena+=" order by descripcion";
    QSqlQuery query = ejecutarSQL(cadena);
	QStringList lista;
	if ( query.isActive() ) {
	while ( query.next() )
		lista << query.value(0).toString();
	}
	return lista;
}

QStringList listaSubcuentas(QString cuenta)
{
	QString cadena="select codigo from plancontable where position('";
    cadena+=cuenta;
    cadena+="' in codigo)=1 and char_length(codigo)=";
    QString cadnum;
    cadnum.setNum(anchocuentas());
    cadena+=cadnum;
    cadena+=" order by codigo";
    QSqlQuery query = ejecutarSQL(cadena);
	QStringList lista;
	if ( query.isActive() ) {
	while ( query.next() )
		lista << query.value(0).toString();
	}
	return lista;
}

int existeEquivalencia(QString busqueda,QString *qcuenta,bool *incor)
{
  if(busqueda.length()>0)
  {
	 QString cadquery;
	 cadquery="SELECT cod,equiv,incorporar from equivalenciasplan where position('";
	 cadquery+=busqueda;
	 cadquery+="' in cod)=1;";
	 QSqlQuery query = ejecutarSQL(cadquery);
	 if ( query.isActive() )
	 {
      if (query.size()==1)
         {
           query.first();
           *qcuenta=query.value(1).toString();
           *incor=query.value(2).toBool();
           return 1;
         }
	 }
  }
 return 0;
}

void guardaEquivalencia(QString equiv,QString cuenta, bool incorpora)
{
 QString cadquery;
 cadquery="UPDATE equivalenciasplan SET equiv='";
 cadquery+=cuenta;
 cadquery+="',incorporar=";
 if(incorpora) cadquery+="TRUE";
 else cadquery+="FALSE";
 cadquery+=" WHERE cod='";
 cadquery+=equiv;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

void insertaEquivalencia(QString equiv,QString cuenta, bool incorpora)
{
 QString cadquery;
 cadquery="INSERT INTO equivalenciasplan (cod,equiv,incorporar) VALUES ('";
 cadquery+=equiv;
 cadquery+="','";
 cadquery+=cuenta;
 cadquery+="',";
 if(incorpora) cadquery+="TRUE";
 else cadquery+="FALSE";
 cadquery+=");";
 ejecutarSQL(cadquery);
}

void eliminaEquivalencia(QString equiv)
{
 QString cadquery;
 cadquery="delete from equivalenciasplan where cod = '";
 cadquery+=equiv;
 cadquery+="';";
 ejecutarSQL(cadquery);
}

int existePaseDiario(QString asiento,QDate fecha,QString cuenta,QString valor)
{
	QString cadquery;
	cadquery="SELECT * FROM diario WHERE asiento='";
	cadquery+=asiento;
	cadquery+="' AND fecha='";
	cadquery+=fecha.toString("yyyy.MM.dd");
	cadquery+="' AND cuenta='";
	cadquery+=cuenta;
	cadquery+="' AND debe+haber='";
	cadquery+=convapunto(valor);
	cadquery+="';";
	QSqlQuery query = ejecutarSQL(cadquery);
	if ( query.isActive() && query.size()>0 )
		return 1;
	return 0;
}


//MODIFICACIONES BASE DE DATOS

QSqlQuery ejecutarSQL (QString cadena)
{
    QSqlQuery query;
    if ( !query.exec(cadena) ) {
        QMessageBox::critical ( 0 , QObject::tr("Base de datos") , QObject::tr("Error al ejecutar la sentencia:\n") + cadena + "\n" + query.lastError().databaseText() +"\n"+ QObject::tr("Controlador: ") + QSqlDatabase::database().driverName() );
    }
    return query;
}

void bloqueaTabla (QString tabla)
{
 QString cad("LOCK TABLE ");
 cad+=tabla;
 //QSqlDatabase::database().transaction();
 if (QSqlDatabase::database().driverName() == "QMYSQL")
    {
     ejecutarSQL("SET AUTOCOMMIT=0;");
     ejecutarSQL(cad+" WRITE;");
    }
 if (QSqlDatabase::database().driverName() == "QPSQL")
    {
      ejecutarSQL(cad+" IN ACCESS EXCLUSIVE MODE;");
    }
}

void bloqueaTablasAsientos()
{
 //QSqlDatabase::database().transaction();
 if (QSqlDatabase::database().driverName() == "QMYSQL")
    {
     ejecutarSQL("SET AUTOCOMMIT=0;");
     ejecutarSQL("LOCK TABLE configuracion write, diario write, saldossubcuenta write, libroiva write,"
               "ejercicios write;");
    }
 if (QSqlDatabase::database().driverName() == "QPSQL")
    {
      ejecutarSQL("LOCK TABLE configuracion IN ACCESS EXCLUSIVE MODE;");
    }
}

void desbloqueaTablas()
{
 QSqlDatabase::database().commit();
 if (QSqlDatabase::database().driverName() == "QMYSQL")
    {
     ejecutarSQL("unlock tables;");
     ejecutarSQL("SET AUTOCOMMIT=1;");
    }
}

char cualControlador () {
    if ( QSqlDatabase::database().driverName().indexOf("QMYSQL") > -1 ) { return MYSQL; }
    else if ( QSqlDatabase::database().driverName().indexOf("QPSQL") > -1 ) { return POSTGRES; }
    else if ( QSqlDatabase::database().driverName().indexOf("QSQLITE") > -1 ) { return SQLITE; }
    else return NINGUNA;
}

// Devuelve el nombre del controlador
QString controlador () {
    return QSqlDatabase::database().driverName();
}

