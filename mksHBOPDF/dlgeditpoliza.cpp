#include "dlgeditpoliza.h"
#include "ui_dlgeditpoliza.h"
#include "dbhandler.h"
#include "dlgasegurados.h"

DlgEditPoliza::DlgEditPoliza(PolizaPtr poliza, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditPoliza)
{
    ui->setupUi(this);
    _poliza = poliza;
    llenarAsegurados();
    llenarControles();
}

DlgEditPoliza::~DlgEditPoliza()
{
    delete ui;
}

void DlgEditPoliza::on_buttonBox_accepted()
{
    //aca hay que hacer el save

    _poliza->setVigenciaDesde(ui->dateDesde->date());
    _poliza->setVigenciaHasta(ui->dateHasta->date());
    _poliza->setDenominacionPoliza(ui->txtDenominacion->text());
    _poliza->setNroPoliza(ui->txtnroPoliza->text().toInt());
    _poliza->setObjeto(ui->txtObjeto->toPlainText());
    _poliza->setAsegurado(dbHandler::instance()->getAsegurado(ui->cboAsegurado->currentData().toInt()));
    _poliza->setMonto(ui->txtMonto->text().toDouble());

    dbHandler::instance()->savePoliza(_poliza);

    close();
}

void DlgEditPoliza::llenarAsegurados()
{
    ui->cboAsegurado->clear();
    QList<AseguradoPtr> asegurados = dbHandler::instance()->getAsegurados();

    foreach (AseguradoPtr asegurado, asegurados)
    {
        ui->cboAsegurado->addItem(asegurado->asegurado(), asegurado->id());
    }
}

void DlgEditPoliza::llenarControles()
{
    ui->dateDesde->setDate(_poliza->vigenciaDesde());
    ui->dateHasta->setDate(_poliza->vigenciaHasta());
    ui->txtDenominacion->setText(_poliza->denominacionPoliza());
    ui->txtnroPoliza->setText(QString::number(_poliza->nroPoliza()));
    ui->txtObjeto->setText(_poliza->objeto());
    if (!_poliza->asegurado().isNull())
    {
        ui->cboAsegurado->setCurrentIndex(ui->cboAsegurado->findData(_poliza->asegurado()->id()));
    }
    ui->txtMonto->setText(QString::number(_poliza->monto()));
}

void DlgEditPoliza::on_toolButton_released()
{
    DlgAsegurados dlg(this);
    dlg.exec();
}
