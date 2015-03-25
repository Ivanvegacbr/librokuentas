#include "funciones.h"
#include "tabla_asientos.h"
#include "basedatos.h"

void funcEdAsiento(QString elasiento, QString eje)
{
       tabla_asientos *t = new tabla_asientos(haycomadecimal(),haydecimales());
       t->activaparaedicion();
       QString consulta="SELECT cuenta,concepto,debe,haber,documento,asiento,fecha,pase,ci,diario ";
       consulta+="FROM diario where asiento='";
       consulta+=elasiento;
       consulta+="' and fecha>='";
          consulta+=inicioejercicio(eje).toString("yyyy.MM.dd");
          consulta+="' and fecha<='";
          consulta+=finejercicio(eje).toString("yyyy.MM.dd");
          consulta+="'";
       //bool esaib=false;
       //bool eseib=false;
       //if (asientoenaib(elasiento)) { t->preparaaib(); esaib=true; }
       //if (asientoeneib(elasiento)) { t->preparaeib(); eseib=true; }
       consulta+=" order by fecha,pase;";
       int fila=0;
       QString cadasiento;
       QString cadpase;
       QDate fechaasiento;
       QString caddebe;
       QString cadhaber;
       QString consulta2;
       QString qdiario;
       bool pasado=false;
       QSqlQuery query2;
       QSqlQuery query = ejecutarSQL( consulta );
            if ( query.isActive() ) {
                while ( query.next() ) {
                    if (!pasado)
                       {
                        qdiario=query.value(9).toString();
                        if (qdiario.length()==0) qdiario=diario_no_asignado();
                        t->pasadiario(qdiario);
                        pasado=true;
                       }
                    //if (esaib && (escuentadeivasoportado(query.value(0).toString())
                        //|| escuentadeivarepercutido(query.value(0).toString()))) continue;
                    if (query.value(2).toDouble()>-0.0001 && query.value(2).toDouble()<0.0001)
                        caddebe=""; else caddebe=query.value(2).toString();
                    if (query.value(3).toDouble()>-0.0001 && query.value(3).toDouble()<0.0001)
                        cadhaber=""; else cadhaber=query.value(3).toString();

                    fechaasiento=query.value(6).toDate();
                    cadpase=query.value(7).toString();

                    t->pasadatos1(fila, query.value(0).toString() , query.value(1).toString(),
                          caddebe, cadhaber, query.value(4).toString(),
                          fechaasiento, cadpase, query.value(8).toString());

                    cadasiento=query.value(5).toString();
                    t->pasanumasiento(cadasiento);
                    //t->pasafechaasiento(fechaasiento);
                    if (!paseLibroiva(cadpase)) { fila++; continue; }
                //QSqlDatabase bd;
                //bd=QSqlDatabase::database ();
                //QString acontrolador= bd.driverName();
            consulta2="SELECT cta_base_iva, base_iva, clave_iva, tipo_iva, ";
            consulta2+="tipo_re, cuota_iva, cuenta_fra, soportado ";
                      /*if (acontrolador=="QMYSQL3" || acontrolador=="QMYSQL")
                      {
                                    consulta2+="tipo_re, cuota_iva, cuenta_fra, DAY(fecha_fra), ";
                                    consulta2+="MONTH(fecha_fra), YEAR(fecha_fra),soportado ";
                      }
                       else
                         {
                            consulta2+="tipo_re, cuota_iva, cuenta_fra, date_part('day',fecha_fra), ";
                            consulta2+="date_part('month',fecha_fra), date_part('year',fecha_fra),soportado ";
                          }*/
            consulta2+="from libroiva where pase=";
                consulta2+=cadpase; consulta2+=";";

                    query2 = ejecutarSQL(consulta2);
                    if (query2.isActive())
                        if (query2.next()) {
                            QString cadsoportado;
                            if (query2.value(10).toBool()==true )
                                cadsoportado="1"; else cadsoportado="0";
                            t->pasadatos2(fila,query2.value(0).toString(),
                                                     query2.value(1).toString(),
                                                     query2.value(2).toString(),
                                                     query2.value(3).toString(),
                                                     query2.value(4).toString(),
                                                     query2.value(5).toString(),
                                                     query2.value(6).toString(),
                                                     cadpase);
                        }

                    fila++;
                }
            }
        t->pasaFechasAsiento(fechaMinAsiento(elasiento,eje),fechaMaxAsiento(elasiento,eje));
        t->chequeatotales();
        t->exec();
        t->~tabla_asientos();
}
