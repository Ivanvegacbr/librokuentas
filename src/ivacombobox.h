#ifndef IVACOMBOBOX_H
#define IVACOMBOBOX_H

#include <QString>
#include <ui_ivaComboBox.h>

class ivaComboBox : public QWidget
{
Q_OBJECT

public:
    ivaComboBox(QWidget *parent = 0);
    int calcularIvas(QString *claveiva, double *valor, double *base, double *iv, bool vbase = false);
    QString texto();

public slots:
    int setIndice(QString qdiario);

private:
    Ui::ivaComboBox ui;
    bool comadecimal,decimales;

private slots:
    void comboIvaCambiado();

signals:
    void ivaActivado(QString ivatext);
};

#endif // IVACOMBOBOX_H
