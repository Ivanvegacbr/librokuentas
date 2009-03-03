#include "cierres.h"
#include "basedatos.h"
#include <QSqlQuery>

cierres::cierres( QString ejercicio ) 
{
	ejer = ejercicio;
}

bool cierres::marcarCerrado()
{
   QString cadena;
   cadena="update ejercicios set cerrado=TRUE where codigo='";
   cadena+=ejer.left(-1).replace("'","''");
   cadena+="'";
   QSqlQuery query = ejecutarSQL(cadena);
   return !query.lastError().isValid();
}

bool cierres::suprimeCierre()
{
   QSqlQuery query;
   QString cadena;
   /*QDate inicioej; inicioej=inicioejercicio(ejer);
   QDate finej=finejercicio(ejer);
   QString cadinicioej=inicioej.toString("yyyy.MM.dd");
   QString cadfinej=finej.toString("yyyy.MM.dd");

   cadena="delete from diario where diario='";
   cadena+=diario_cierre().left(-1).replace("'","''");
   cadena+="' and fecha>='";
   cadena+=cadinicioej.left(-1).replace("'","''");
   cadena+="' and fecha<='";
   cadena+=cadfinej.left(-1).replace("'","''");
   cadena+="'";

   query = ejecutarSQL(cadena);*/

   cadena="update ejercicios set cerrado=FALSE where codigo='";
   cadena+=ejer.left(-1).replace("'","''");
   cadena+="'";

   query = ejecutarSQL(cadena);

   //actualizasaldos();

   return !query.lastError().isValid();

}

