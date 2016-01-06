#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include "tagvalue.h"

class Tag;

typedef QSharedPointer<Tag> TagPtr;

class Tag : public QObject
{
    Q_OBJECT
public:
    explicit Tag(const QString &tagName, bool isMultiple, const QString &leftDelimiter, const QString &rightDelimiter, bool removeLeft, bool removeRight, QObject *parent = 0);
    explicit Tag(const QString &tagName, bool isMultiple, int rowcount);

    QString tagName() const;
    QString leftDelimiter() const;
    QString rightDelimiter() const;
    QMap<QString, TagPtr> subtags() const;

    void addSubTag(TagPtr tag);

    QList<TagValuePtr> extractValue(const QString &source);

    bool isComplex() const;
    bool isMultiple() const;


private:
    QPair<QString, int> extractValueUsingDelimiters(const QString &source, int startPosition);
    QPair<QString, int> extractValueUsingRows(const QString &source, int startPosition);

signals:

public slots:

private:
    QString _tagName;
    QString _leftDelimiter;
    QString _rightDelimiter;
    bool _isMultiple;
    int _rowCount;
    QMap<QString, TagPtr> _subtags;
    bool _removeLeft;
    bool _removeRight;
};



#endif // TAG_H
