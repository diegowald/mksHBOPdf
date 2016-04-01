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
    _tomador = "";
    _suplementosLoaded = false;
}

Poliza::Poliza(QSqlRecord record) : QObject()
{
    _id = record.value(record.indexOf("id")).toInt();
    _vigenciaDesde = record.value(record.indexOf("vigenciaDesde")).toDate();
    _vigenciaHasta = record.value(record.indexOf("vigenciaHasta")).toDate();
    _denominacionPoliza = record.value(record.indexOf("denominacionPoliza")).toString();
    _nroPoliza = record.value(record.indexOf("nroPoliza")).toInt();
    _objeto = record.value(record.indexOf("objeto")).toString();
    _asegurado = dbHandler::instance()->getAsegurado(record.value(record.indexOf("asegurado")).toInt());
    _monto = record.value(record.indexOf("monto")).toDouble();
    _tomador = record.value(record.indexOf("tomador")).toString();
    _suplementosLoaded = false;
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

double Poliza::montoGastado()
{
    double gastado = 0.;
    QList<SuplementoPtr> supls = suplementos();
    foreach (SuplementoPtr s, supls)
    {
        gastado += s->monto();
    }
    return gastado;
}

double Poliza::montoDisponible()
{
    return _monto - montoGastado();
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
        query->prepare("INSERT INTO polizas (vigenciaDesde, vigenciaHasta, denominacionPoliza, nroPoliza, objeto, asegurado, monto, tomador) "
                       " VALUES (:vigenciaDesde, :vigenciaHasta, :denominacionPoliza, :nroPoliza, :objeto, :asegurado, :monto, :tomador);");
    }
    else
    {
        query->prepare("UPDATE polizas SET vigenciaDesde = :vigenciaDesde, vigenciaHasta = :vigenciaHasta, denominacionPoliza = :denominacionPoliza, "
                       " nroPoliza = :nroPoliza, objeto = :objeto, asegurado = :asegurado, monto = :monto, tomador = :tomador "
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
    query->bindValue(":tomador", _tomador);
    return query;
}

SuplementoPtr Poliza::crearSuplemento()
{
    SuplementoPtr s = SuplementoPtr::create(sharedFromThis());
    _suplementos.append(s);
    _suplementoNuevo = s;
    return s;
}

SuplementoPtr Poliza::suplementoNuevo() const
{
    return _suplementoNuevo;
}

int Poliza::nuevoNroSuplemento()
{
    int maxSupl = -1;
    foreach (SuplementoPtr s, suplementos())
    {
        maxSupl = s->nroSuplemento() > maxSupl ? s->nroSuplemento(): maxSupl;
    }
    return (maxSupl == -1) ? 1 : maxSupl +1;
}

QString Poliza::tomador() const
{
    return _tomador;
}

void Poliza::setTomador(const QString &value)
{
    _tomador = value;
}


QList<SuplementoPtr> Poliza::suplementos()
{
    if (!_suplementosLoaded)
    {
        _suplementos = dbHandler::instance()->getSuplementos(sharedFromThis());
        _suplementosLoaded = true;
    }
    return _suplementos;
}
