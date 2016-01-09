#ifndef POLIZA_H
#define POLIZA_H

#include <QObject>
#include "asegurado.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDate>

class Poliza : public QObject
{
    Q_OBJECT
public:
    explicit Poliza(QObject *parent = 0);
    explicit Poliza(QSqlRecord record);

    int id() const;
    QDate vigenciaDesde() const;
    QDate vigenciaHasta() const;
    QString denominacionPoliza() const;
    int nroPoliza() const;
    QString objeto() const;
    AseguradoPtr asegurado() const;
    double monto() const;

    void setVigenciaDesde (const QDate &value);
    void setVigenciaHasta (const QDate &value);
    void setDenominacionPoliza(const QString &value);
    void setNroPoliza(int value);
    void setObjeto (const QString &value);
    void setAsegurado(AseguradoPtr value);
    void setMonto(double value);

    QSqlQuery* getQuery(QSqlDatabase &database);

signals:

public slots:

private:
    int _id;
    QDate _vigenciaDesde;
    QDate _vigenciaHasta;
    QString _denominacionPoliza;
    int _nroPoliza;
    QString _objeto;
    AseguradoPtr _asegurado;
    double _monto;
};

typedef QSharedPointer<Poliza> PolizaPtr;

#endif // POLIZA_H
