
#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QObject>
#include "tag.h"
#include <QTreeWidget>
#include "poliza.h"

class DocumentParser : public QObject
{
    Q_OBJECT
public:
    explicit DocumentParser(PolizaPtr poliza, const QString &documentContents, QObject *parent = 0);
    bool parse();

    void llenarArbol(QTreeWidget *treeWidget);

    QString applyOnTemplate(const QString &templateTxt);

private:
    QString extract(const QString &textoIzquierda, const QString &textoDerecha, int position = 0);
    QString extract(const QString from, const QString &textoIzquierda, const QString &textoDerecha, int position = 0);

    void defineTagDefinitions();
    TagPtr createTagDefinition(const QString &tagName, bool isMultiple, const QString &left, const QString &right, bool removeLeft = true, bool removeRight = true);
    TagPtr createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, const QString &left, const QString &right, bool removeLeft = true, bool removeRight = true);
    TagPtr createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, int rowcount);
    TagPtr createTagDefinition(TagPtr parentTag, const QString &tagName, Calculation calculation);

    int nroSuplemento();
    int nroPoliza();
    QString tomador();
    QString objetoPoliza();
    double montoContingente();
    double montoPasajero();
    double sumaAsegurada();
signals:

public slots:
private:
    QString _source;

    QMap<QString, TagPtr> _tagDefinition;
    QMap<QString, QList<TagValuePtr>> _tagValues;

    PolizaPtr _poliza;
};

#endif // DOCUMENTPARSER_H
