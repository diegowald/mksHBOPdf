#include "dbhandler.h"
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QDirIterator>


dbHandler *dbHandler::_instance;


dbHandler::dbHandler(QObject *parent) : QObject(parent)
{
    _filename = "./polizas.db";
}

dbHandler::~dbHandler()
{
}

void dbHandler::initialize()
{
    _instance = new dbHandler();
}

void dbHandler::finalize()
{
    _instance->deleteLater();
}

dbHandler *dbHandler::instance()
{
    return _instance;
}

QList<PolizaPtr> dbHandler::getPolizas()
{
    QList<PolizaPtr> resultado;

    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = "select * from polizas;";

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        resultado.append(PolizaPtr::create(query.record()));
    }
    // cierro la base de datos
    _database.close();


    return resultado;
}

PolizaPtr dbHandler::getPoliza(int id)
{
    PolizaPtr resultado;

    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = QString("select * from polizas where id = %1;").arg(id);

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        resultado = PolizaPtr::create(query.record());
    }
    // cierro la base de datos
    _database.close();

    return resultado;
}

bool dbHandler::savePoliza(PolizaPtr poliza)
{
    // Abro la base de datos
    connectToDatabase();

    // Obtengo los queries de eliminacion;
    QSqlQuery* query = poliza->getQuery(_database);

    bool result = true;
    _database.transaction();
    if (!query->exec())
    {
        qDebug() << query->lastError().text();
        result = false;
    }
    if (result)
    {
        _database.commit();
    }
    else
    {
        _database.rollback();
    }

    delete query;
}


QList<AseguradoPtr> dbHandler::getAsegurados()
{
    QList<AseguradoPtr> resultado;

    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = "select * from asegurados;";

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        resultado.append(AseguradoPtr::create(query.record()));
    }
    // cierro la base de datos
    _database.close();

    return resultado;
}

AseguradoPtr dbHandler::getAsegurado(int id)
{
    AseguradoPtr resultado;

    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = QString("select * from asegurados where id = %1;").arg(id);

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        resultado = AseguradoPtr::create(query.record());
    }
    // cierro la base de datos
    _database.close();

    return resultado;
}

bool dbHandler::saveAsegurado(AseguradoPtr asegurado)
{
    // Abro la base de datos
    connectToDatabase();

    // Obtengo los queries de eliminacion;
    QSqlQuery* query = asegurado->getQuery(_database);

    bool result = true;
    _database.transaction();
    if (!query->exec())
    {
        qDebug() << query->lastError().text();
        result = false;
    }
    if (result)
    {
        _database.commit();
    }
    else
    {
        _database.rollback();
    }

    delete query;
}

QList<SuplementoPtr> dbHandler::getSuplementos(PolizaPtr poliza)
{
    QList<SuplementoPtr> resultado;

    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = QString("select * from suplementos where idPoliza = %1;").arg(poliza->id());

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        resultado.append(SuplementoPtr::create(poliza, query.record()));
    }
    // cierro la base de datos
    _database.close();

    return resultado;
}

SuplementoPtr dbHandler::getSuplemento(PolizaPtr poliza, int id)
{
    SuplementoPtr resultado;

    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = QString("select * from suplementos where id = %1;").arg(id);

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        resultado = SuplementoPtr::create(poliza, query.record());
    }
    // cierro la base de datos
    _database.close();

    return resultado;
}

bool dbHandler::saveSuplemento(SuplementoPtr suplemento)
{
    // Abro la base de datos
    connectToDatabase();

    // Obtengo los queries de eliminacion;
    QSqlQuery* query = suplemento->getQuery(_database);

    bool result = true;
    _database.transaction();
    if (!query->exec())
    {
        qDebug() << query->lastError().text();
        result = false;
    }
    if (result)
    {
        _database.commit();
    }
    else
    {
        _database.rollback();
    }

    delete query;
}

bool dbHandler::connectToDatabase()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    //_database.setDatabaseName(":memory:");
    _database.setDatabaseName(_filename);
    if (!_database.open()) {
        QMessageBox::critical(0, "Cannot open database",
                              "Unable to establish a database connection.\n"
                              "This example needs SQLite support. Please read "
                              "the Qt SQL driver documentation for information how "
                              "to build it.\n\n"
                              "Click Cancel to exit.", QMessageBox::Cancel);
        return false;
    }
    return true;
}


QList<TemplateDocPtr> dbHandler::getTemplates()
{
    QList<TemplateDocPtr> resultado;
    QDirIterator it("./templates/", QDirIterator::NoIteratorFlags);

    while (it.hasNext())
    {
        QString entry = it.next();
        if (!entry.endsWith("."))
        {
            qDebug() << entry;
            resultado.append(TemplateDocPtr::create(entry));
        }
    }
    return resultado;
}
