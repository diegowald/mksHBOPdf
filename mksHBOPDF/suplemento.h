#ifndef SUPLEMENTO_H
#define SUPLEMENTO_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>


class Poliza;
typedef QSharedPointer<Poliza> PolizaPtr;

class Suplemento : public QObject
{
    Q_OBJECT
public:
    explicit Suplemento(PolizaPtr poliza);
    explicit Suplemento(PolizaPtr poliza, QSqlRecord record);

    PolizaPtr poliza() const;
    int id() const;
    int nroSuplemento() const;
    QString pdf() const;

    QString templateDoc() const;
    double monto() const;

    void setPDF(const QString &value);
    void setTemplateDoc(const QString &value);
    void setMonto(double value);



    QSqlQuery* getQuery(QSqlDatabase &database);

signals:

public slots:

private:
    PolizaPtr _poliza;
    int _id;
    int _nroSuplemento;
    QString _pdf;
    QString _templateDoc;
    double _monto;
};


typedef QSharedPointer<Suplemento> SuplementoPtr;
#endif // SUPLEMENTO_H
