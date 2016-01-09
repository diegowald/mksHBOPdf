#include "dlgeditasegurado.h"
#include "ui_dlgeditasegurado.h"
#include "dbhandler.h"



DlgEditAsegurado::DlgEditAsegurado(AseguradoPtr asegurado, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditAsegurado)
{
    ui->setupUi(this);
    _asegurado = asegurado;
    ui->spinPorcentaje->setMinimum(0.);
    ui->spinPorcentaje->setMaximum(100.);
    llenarControles();
}

DlgEditAsegurado::~DlgEditAsegurado()
{
    delete ui;
}

void DlgEditAsegurado::on_buttonBox_accepted()
{
    _asegurado->setAsegurado(ui->txtAsegurado->text());
    _asegurado->setPorcentaje(ui->spinPorcentaje->value());
    dbHandler::instance()->saveAsegurado(_asegurado);
    close();
}

void DlgEditAsegurado::llenarControles()
{
    ui->txtAsegurado->setText(_asegurado->asegurado());
    ui->spinPorcentaje->setValue(_asegurado->porcentaje());
}
