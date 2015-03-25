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

#include "inicio.h"

inicio::inicio() : QDialog() {
    ui.setupUi(this);

   ui.textEdit->setText(tr(
        "Este programa es software libre; se  puede redistribuir y/o modificar "
        "bajo las condiciones de la Licencia GNU (GNU General Public License) "
        "en la forma en que la Free Software Foundation la ha publicado, ya "
        "sea bajo la versión 3 de la Licencia, o a su elección, bajo cualquier  "
        "otra versión más reciente.\n"
        "Libro-Kuentas se suministra sin ningún tipo de garantía, ya sea implícita o "
        "explícita. El usuario asume por completo cualquier tipo de riesgo o pérdida "
        "derivada de la calidad y posible mal funcionamiento del programa. Si el "
        "programa fuera o se probara que es defectuoso, el usuario asumiría por "
        "completo el coste de cualquier servicio de mantenimiento, reparación o "
        "corrección.\n\n"
        "Libro-Kuentas presupone, para su correcto funcionamiento, la existencia "
        "del siguiente software:\n\n"
        "Alguno de los dos  gestores de bases de datos POSTGRESQL ó MySQL "
        "correctamente instalados y en "
        "funcionamiento (el manual de usuario contiene información al "
        "respecto)\n\n"
        "El controlador QPSQL de las librerías QT para la conexión con "
        "POSTGRESQL, o bien el controlador QMYSQL para MySQL\n\n"
        "El paquete Latex, que será el encargado, entre otras cosas, de generar la "
        "salida impresa de la aplicación. En Ubuntu y derivados los paquetes <texlive-base> "
        "y <texlive-extra-utils>\n\n"));

}

/*IFORMACIÓN IMPORTANTE:


KEME-Contabilidad necesita para su ejecución del paquete Miktex: el archivo basic-miktex-2.7.2904 proporciona un instalador a partir de una versión reducida. Se puede obtener a través del proyecto en Sourceforge:

http://sourceforge.net/project/downloading.php?groupname=miktex&filename=basic-miktex-2.7.2904.exe

Una vez instalado, sería conveniente activar el soporte para unicode (utf8). Esto lo podemos conseguir a partir de la herramienta "MiKTeX Package Manager". Seleccionaremos en la lista el paquete "unicode" y lo instalaremos pulsando el botón '+'

La versión 2.2.1 de KEME-Contabilidad incorpora soporte SQLITE por lo que no es necesario la instalación de un gestor de bases de datos. Para cargar la empresa de ejemplo bastaría con suministrar la cadena de caracteres "ejemplo-sqlite" en el campo "base de datos" del diálogo de conexión.

El manual de la aplicación posee información sobre la utilización de KEME-Contabilidad conjuntamente con los gestores de bases de datos MySQL y PostgreSQL.*/

