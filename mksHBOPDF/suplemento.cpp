#include "suplemento.h"
#include "poliza.h"
#include "dbhandler.h"
#include <QVariant>


Suplemento::Suplemento(PolizaPtr poliza) : QObject()
{
    _poliza = poliza;
    _id = -1;
    _nroSuplemento = poliza->nuevoNroSuplemento();
    _pdf = "";
    _templateDoc = "";
    _monto = 0.;
}

Suplemento::Suplemento(PolizaPtr poliza, QSqlRecord record)
{
    _id = record.value(record.indexOf("id")).toInt();
    _poliza = poliza;
    _pdf = record.value(record.indexOf("pdf")).toString();
    _templateDoc = record.value(record.indexOf("templateDoc")).toString();
    _monto = record.value(record.indexOf("monto")).toDouble();
    _nroSuplemento = record.value(record.indexOf("nroSuplemento")).toInt();
}


PolizaPtr Suplemento::poliza() const
{
    return _poliza;
}

int Suplemento::id() const
{
    return _id;
}

QString Suplemento::pdf() const
{
    return _pdf;
}

QString Suplemento::templateDoc() const
{
    return _templateDoc;
}

double Suplemento::monto() const
{
    return _monto;
}


void Suplemento::setPDF(const QString &value)
{
    _pdf = value;
}

void Suplemento::setTemplateDoc(const QString &value)
{
    _templateDoc = value;
}

void Suplemento::setMonto(double value)
{
    _monto = value;
}

QSqlQuery* Suplemento::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = new QSqlQuery(database);

    if (_id == -1)
    {
        query->prepare("INSERT INTO suplementos (idPoliza, pdf, templateDoc, monto, nroSuplemento) "
                       " VALUES (:idPoliza, :pdf, :templateDoc, :monto, :nroSuplemento);");
    }
    else
    {
        query->prepare("UPDATE suplementos SET idPoliza = :idPoliza, pdf = :pdf, templateDoc = :templateDoc, monto = :monto, nroSuplemento = :nroSuplemento "
                       " WHERE id = :id;");
        query->bindValue(":id", _id);
    }

    query->bindValue(":idPoliza", _poliza->id());
    query->bindValue(":pdf", _pdf);
    query->bindValue(":templateDoc", _templateDoc);
    query->bindValue(":monto", _monto);
    query->bindValue(":nroSuplemento", _nroSuplemento);
    return query;
}

int Suplemento::nroSuplemento() const
{
    return _nroSuplemento;
}
