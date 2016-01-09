#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include "asegurado.h"
#include "poliza.h"
#include <QSqlDatabase>

class dbHandler : public QObject
{
    Q_OBJECT
public:

    static void initialize();
    static void finalize();
    static dbHandler *instance();

    explicit dbHandler(QObject *parent = 0);
    virtual ~dbHandler();

    QList<PolizaPtr> getPolizas();
    PolizaPtr getPoliza(int id);
    bool savePoliza(PolizaPtr poliza);

    QList<AseguradoPtr> getAsegurados();
    AseguradoPtr getAsegurado(int id);
    bool saveAsegurado(AseguradoPtr asegurado);

private:
    bool connectToDatabase();
private:
    QString _filename;
    QSqlDatabase _database;

    static dbHandler *_instance;
};

#endif // DBHANDLER_H
