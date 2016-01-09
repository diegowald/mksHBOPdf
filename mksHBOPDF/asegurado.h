#ifndef ASEGURADO_H
#define ASEGURADO_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>
class Asegurado : public QObject
{
    Q_OBJECT
public:
    explicit Asegurado(QObject *parent = 0);
    explicit Asegurado(QSqlRecord record);
    int id() const;
    QString asegurado() const;
    double porcentaje() const;

    void setAsegurado(const QString &value);
    void setPorcentaje(double value);

    QSqlQuery* getQuery(QSqlDatabase &database);

signals:

public slots:
private:
    int _id;
    QString _asegurado;
    double _porcentaje;
};

typedef QSharedPointer<Asegurado> AseguradoPtr;

#endif // ASEGURADO_H
