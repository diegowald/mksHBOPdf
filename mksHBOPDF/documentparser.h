
#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QObject>
#include "tag.h"
#include <QTreeWidget>

class DocumentParser : public QObject
{
    Q_OBJECT
public:
    explicit DocumentParser(const QString &documentContents, QObject *parent = 0);
    bool parse();

    void llenarArbol(QTreeWidget *treeWidget);
private:
    QString extract(const QString &textoIzquierda, const QString &textoDerecha, int position = 0);
    QString extract(const QString from, const QString &textoIzquierda, const QString &textoDerecha, int position = 0);

    void defineTagDefinitions();
    TagPtr createTagDefinition(const QString &tagName, bool isMultiple, const QString &left, const QString &right);
    TagPtr createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, const QString &left, const QString &right);
    TagPtr createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, int rowcount);

signals:

public slots:
private:
    QString _source;

    QMap<QString, TagPtr> _tagDefinition;
    QMap<QString, QList<TagValuePtr>> _tagValues;
};

#endif // DOCUMENTPARSER_H
