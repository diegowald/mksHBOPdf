#include "dlgpolizas.h"
#include "ui_dlgpolizas.h"
#include "dbhandler.h"
#include "poliza.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include "dlgeditpoliza.h"


DlgPolizas::DlgPolizas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPolizas)
{
    ui->setupUi(this);
    llenarPolizas();
}

DlgPolizas::~DlgPolizas()
{
    delete ui;
}


void DlgPolizas::llenarPolizas()
{
    ui->tblPolizas->setRowCount(0);
    QList<PolizaPtr> polizas = dbHandler::instance()->getPolizas();
    foreach (PolizaPtr poliza, polizas)
    {
        int row = ui->tblPolizas->rowCount();
        ui->tblPolizas->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(poliza->denominacionPoliza());
        item->setData(Qt::UserRole, poliza->id());
        ui->tblPolizas->setItem(row, 0, item);

        item = new QTableWidgetItem(poliza->vigenciaDesde().toString());
        item->setData(Qt::UserRole, poliza->id());
        ui->tblPolizas->setItem(row, 1, item);

        item = new QTableWidgetItem(poliza->vigenciaHasta().toString());
        item->setData(Qt::UserRole, poliza->id());
        ui->tblPolizas->setItem(row, 2, item);

        item = new QTableWidgetItem(QString::number(poliza->monto()));
        item->setData(Qt::UserRole, poliza->id());
        ui->tblPolizas->setItem(row, 3, item);
    }
}

void DlgPolizas::on_btnNuevo_released()
{
    PolizaPtr poliza = PolizaPtr::create();
    editarPoliza(poliza);
}

void DlgPolizas::on_tblPolizas_itemDoubleClicked(QTableWidgetItem *item)
{
    PolizaPtr poliza = dbHandler::instance()->getPoliza(item->data(Qt::UserRole).toInt());
    editarPoliza(poliza);
}


void DlgPolizas::editarPoliza(PolizaPtr poliza)
{
    DlgEditPoliza dlg(poliza, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        llenarPolizas();
    }
}
