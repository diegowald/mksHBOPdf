#ifndef DLGASEGURADOS_H
#define DLGASEGURADOS_H

#include <QDialog>
#include <QWidgetItem>
#include "asegurado.h"
#include <QTableWidgetItem>



namespace Ui {
class DlgAsegurados;
}

class DlgAsegurados : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAsegurados(QWidget *parent = 0);
    ~DlgAsegurados();

private:
    void llenarAsegurados();
    void editarAsegurado(AseguradoPtr asegurado);

private slots:
    void on_btnNuevo_released();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::DlgAsegurados *ui;
};

#endif // DLGASEGURADOS_H
