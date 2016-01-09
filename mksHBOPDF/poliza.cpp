#include "poliza.h"
#include <QVariant>
#include "dbhandler.h"

Poliza::Poliza(QObject *parent) : QObject(parent)
{
    _id = -1;
    _vigenciaDesde = QDate::currentDate();
    _vigenciaHasta = QDate::currentDate();
    _denominacionPoliza = "";
    _nroPoliza = -1;
    _objeto = "";
    _asegurado.clear();
    _monto = 0.;
}

Poliza::Poliza(QSqlRecord record) : QObject()
{
    _id = record.value(record.indexOf("id")).toInt();
    _vigenciaDesde = record.value(record.indexOf("vigenciaDesde")).toDate();
    _vigenciaHasta = record.value(record.indexOf("vigenciaHasta")).toDate();
    _denominacionPoliza = record.value(record.indexOf("denominacionPoliza")).toString();
    _nroPoliza = record.value(record.indexOf("nroPoliza")).toInt();
    _objeto = record.value(record.indexOf("objeto")).toString();
    _asegurado = dbHandler::instance()->getAsegurado(record.value(record.indexOf("idAsegurado")).toInt());
    _monto = record.value(record.indexOf("monto")).toDouble();
}

int Poliza::id() const
{
    return _id;
}

QDate Poliza::vigenciaDesde() const
{
    return _vigenciaDesde;
}

QDate Poliza::vigenciaHasta() const
{
    return _vigenciaHasta;
}

QString Poliza::denominacionPoliza() const
{
    return _denominacionPoliza;
}

int Poliza::nroPoliza() const
{
    return _nroPoliza;
}


QString Poliza::objeto() const
{
    return _objeto;
}

AseguradoPtr Poliza::asegurado() const
{
    return _asegurado;
}

double Poliza::monto() const
{
    return _monto;
}

void Poliza::setVigenciaDesde (const QDate &value)
{
    _vigenciaDesde = value;
}

void Poliza::setVigenciaHasta (const QDate &value)
{
    _vigenciaHasta = value;
}

void Poliza::setDenominacionPoliza(const QString &value)
{
    _denominacionPoliza = value;
}

void Poliza::setNroPoliza(int value)
{
    _nroPoliza = value;
}

void Poliza::setObjeto (const QString &value)
{
    _objeto = value;
}

void Poliza::setAsegurado(AseguradoPtr value)
{
    _asegurado = value;
}

void Poliza::setMonto(double value)
{
    _monto = value;
}

QSqlQuery* Poliza::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = new QSqlQuery(database);

    if (_id == -1)
    {
        query->prepare("INSERT INTO polizas (vigenciaDesde, vigenciaHasta, denominacionPoliza, nroPoliza, objeto, asegurado, monto) "
                       " VALUES (:vigenciaDesde, :vigenciaHasta, :denominacionPoliza, :nroPoliza, :objeto, :asegurado, :monto);");
    }
    else
    {
        query->prepare("UPDATE polizas SET vigenciaDesde = :vigenciaDesde, vigenciaHasta = :vigenciaHasta, denominacionPoliza = :denominacionPoliza, "
                       " nroPoliza = :nroPoliza, objeto = :objeto, asegurado = :asegurado, monto = :monto "
                       " WHERE id = :id;");
        query->bindValue(":id", _id);
    }
    query->bindValue(":vigenciaDesde", _vigenciaDesde);
    query->bindValue(":vigenciaHasta", _vigenciaHasta);
    query->bindValue(":denominacionPoliza", _denominacionPoliza);
    query->bindValue(":nroPoliza", _nroPoliza);
    query->bindValue(":objeto", _objeto);
    query->bindValue(":asegurado", _asegurado->id());
    query->bindValue(":monto", _monto);
    return query;
}
