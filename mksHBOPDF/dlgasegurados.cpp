#include "dlgasegurados.h"
#include "ui_dlgasegurados.h"
#include "dbhandler.h"
#include "dlgeditasegurado.h"


DlgAsegurados::DlgAsegurados(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAsegurados)
{
    ui->setupUi(this);
    llenarAsegurados();
}

DlgAsegurados::~DlgAsegurados()
{
    delete ui;
}

void DlgAsegurados::on_btnNuevo_released()
{
    AseguradoPtr asegurado = AseguradoPtr::create();
    editarAsegurado(asegurado);
}

void DlgAsegurados::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    AseguradoPtr asegurado = dbHandler::instance()->getAsegurado(item->data(Qt::UserRole).toInt());
    editarAsegurado(asegurado);
}

void DlgAsegurados::llenarAsegurados()
{
    QList<AseguradoPtr> asegurados = dbHandler::instance()->getAsegurados();
    ui->tableWidget->setRowCount(0);
    foreach (AseguradoPtr asegurado, asegurados)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(asegurado->asegurado());
        item->setData(Qt::UserRole, asegurado->id());
        ui->tableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::number(asegurado->porcentaje()));
        item->setData(Qt::UserRole, asegurado->id());
        ui->tableWidget->setItem(row, 1, item);
    }
}

void DlgAsegurados::editarAsegurado(AseguradoPtr asegurado)
{
    DlgEditAsegurado dlg(asegurado, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        llenarAsegurados();
    }
}
