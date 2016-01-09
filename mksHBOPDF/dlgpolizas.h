#ifndef DLGPOLIZAS_H
#define DLGPOLIZAS_H

#include <QDialog>
#include "poliza.h"
#include <QTableWidgetItem>


namespace Ui {
class DlgPolizas;
}

class DlgPolizas : public QDialog
{
    Q_OBJECT

public:
    explicit DlgPolizas(QWidget *parent = 0);
    ~DlgPolizas();

    void llenarPolizas();

private:
    void editarPoliza(PolizaPtr poliza);


private slots:
    void on_btnNuevo_released();

    void on_tblPolizas_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::DlgPolizas *ui;
};

#endif // DLGPOLIZAS_H
