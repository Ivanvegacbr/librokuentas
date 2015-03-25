CODECFORTR = UTF-8
CONFIG += qt \
    release \
    warn_off
HEADERS = src/acercade.h \
    src/acumuladosmes.h \
    src/arbol.h \
    src/basedatos.h \
    src/bss.h \
    src/buscaconcepto.h \
    src/buscasubcuenta.h \
    src/cargaespera.h \
    src/cierres.h \
    src/conceptos.h \
    src/conexion.h \
    src/consmayor.h \
    src/consplan.h \
    src/copiaseg.h \
    src/creaempresa.h \
    src/cuadimprimayor.h \
    src/diario.h \
    src/edit_conc_doc.h \
    src/editafechacierre.h \
    src/editapaseconci.h \
    src/editaplan.h \
    src/editconfig.h \
    src/ejercicios.h \
    src/equivalencias.h \
    src/filtrodiario.h \
    src/funciones.h \
    src/imprimediario.h \
    src/infobd.h \
    src/inicial.h \
    src/inicio.h \
    src/interfechas.h \
    src/introfecha.h \
    src/lacaixa.h \
    src/libroiva.h \
    src/libros.h \
    src/licencia.h \
    src/listavenci.h \
    src/nuevoejercicio.h \
    src/pastel.h \
    src/periodos.h \
    src/pideejercicio.h \
    src/pidenombre.h \
    src/pieview.h \
    src/porcentage.h \
    src/preferencias.h \
    src/principal.h \
    src/subcuentas.h \
    src/tabla_asientos.h \
    src/tiposiva.h \
    src/importasemanas.h \
    src/diarios.h \
    src/asignadiario.h \
    src/editarasiento.h \
    src/ivacombobox.h
DESTDIR = bin
FORMS = ui/acercade.ui \
    ui/acumuladosmes.ui \
    ui/bss.ui \
    ui/buscaconcepto.ui \
    ui/buscasubcuenta.ui \
    ui/cargaespera.ui \
    ui/conceptos.ui \
    ui/conexion.ui \
    ui/consmayor.ui \
    ui/consplan.ui \
    ui/copiaseg.ui \
    ui/creaempresa.ui \
    ui/cuadimprimayor.ui \
    ui/diario.ui \
    ui/edit_conc_doc.ui \
    ui/editafechacierre.ui \
    ui/editapaseconci.ui \
    ui/editaplan.ui \
    ui/editconfig.ui \
    ui/ejercicios.ui \
    ui/equivalencias.ui \
    ui/filtrodiario.ui \
    ui/imprimediario.ui \
    ui/infobd.ui \
    ui/inicial.ui \
    ui/inicio.ui \
    ui/interFechas.ui \
    ui/introfecha.ui \
    ui/lacaixa.ui \
    ui/libroiva.ui \
    ui/libros.ui \
    ui/licencia.ui \
    ui/listavenci.ui \
    ui/nuevoejercicio.ui \
    ui/periodos.ui \
    ui/pideejercicio.ui \
    ui/pidenombre.ui \
    ui/porcentage.ui \
    ui/preferencias.ui \
    ui/principal.ui \
    ui/subcuentas.ui \
    ui/tabla_asientos.ui \
    ui/tiposiva.ui \
    ui/diarios.ui \
    ui/asignadiario.ui \
    ui/ivaComboBox.ui
SOURCES = src/acercade.cpp \
    src/acumuladosmes.cpp \
    src/arbol.cpp \
    src/basedatos.cpp \
    src/bss.cpp \
    src/buscaconcepto.cpp \
    src/buscasubcuenta.cpp \
    src/cargaespera.cpp \
    src/cierres.cpp \
    src/conceptos.cpp \
    src/conexion.cpp \
    src/consmayor.cpp \
    src/consplan.cpp \
    src/copiaseg.cpp \
    src/creaempresa.cpp \
    src/cuadimprimayor.cpp \
    src/diario.cpp \
    src/edit_conc_doc.cpp \
    src/editafechacierre.cpp \
    src/editapaseconci.cpp \
    src/editaplan.cpp \
    src/editconfig.cpp \
    src/ejercicios.cpp \
    src/equivalencias.cpp \
    src/filtrodiario.cpp \
    src/funciones.cpp \
    src/imprimediario.cpp \
    src/infobd.cpp \
    src/inicial.cpp \
    src/inicio.cpp \
    src/interfechas.cpp \
    src/introfecha.cpp \
    src/lacaixa.cpp \
    src/libroiva.cpp \
    src/libros.cpp \
    src/licencia.cpp \
    src/listavenci.cpp \
    src/main.cpp \
    src/nuevoejercicio.cpp \
    src/pastel.cpp \
    src/periodos.cpp \
    src/pideejercicio.cpp \
    src/pidenombre.cpp \
    src/pieview.cpp \
    src/porcentage.cpp \
    src/preferencias.cpp \
    src/principal.cpp \
    src/subcuentas.cpp \
    src/tabla_asientos.cpp \
    src/tiposiva.cpp \
    src/importasemanas.cpp \
    src/diarios.cpp \
    src/asignadiario.cpp \
    src/editarasiento.cpp \
    src/ivacombobox.cpp
MOC_DIR = compilar
OBJECTS_DIR = compilar
QT += sql
RESOURCES += ui/libroK.qrc
TEMPLATE = app
TRANSLATIONS += lang/librok_cat.ts \
    lang/librok_eng.ts
UI_DIR = compilar
win32:RC_FILE = icon.rc
TARGET = libroK_0.7.8

OTHER_FILES += \
    CHANGELOG.txt
