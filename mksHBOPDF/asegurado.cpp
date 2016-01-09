#include "asegurado.h"
#include <QVariant>

Asegurado::Asegurado(QObject *parent) : QObject(parent)
{
    _id = -1;
    _asegurado = "";
    _porcentaje = 100.0;
}

Asegurado::Asegurado(QSqlRecord record) : QObject()
{
    _id = record.value(record.indexOf("id")).toInt();
    _asegurado = record.value(record.indexOf("asegurado")).toString();
    _porcentaje = record.value(record.indexOf("porcentaje")).toDouble();
}

int Asegurado::id() const
{
    return _id;
}

QString Asegurado::asegurado() const
{
    return _asegurado;
}

double Asegurado::porcentaje() const
{
    return _porcentaje;
}

void Asegurado::setAsegurado(const QString &value)
{
    _asegurado = value;
}

void Asegurado::setPorcentaje(double value)
{
    _porcentaje = value;
}


QSqlQuery* Asegurado::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = new QSqlQuery(database);

    if (_id == -1)
    {
        query->prepare("INSERT INTO asegurados (asegurado, porcentaje) "
                       " VALUES (:asegurado, :porcentaje);");
    }
    else
    {
        query->prepare("UPDATE asegurados SET asegurado = :asegurado, porcentaje = :porcentaje "
                       " WHERE id = :id;");
        query->bindValue(":id", _id);
    }
    query->bindValue(":asegurado", _asegurado);
    query->bindValue(":porcentaje", _porcentaje);
    return query;
}
