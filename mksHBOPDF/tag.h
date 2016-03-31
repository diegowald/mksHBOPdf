#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include "tagvalue.h"
#include <QEnableSharedFromThis>
#include <functional>

class Tag;

typedef QSharedPointer<Tag> TagPtr;

typedef std::function<QString ()> Calculation;

class Tag : public QObject, public QEnableSharedFromThis<Tag>
{
    Q_OBJECT
public:
    explicit Tag(const QString &tagName, bool isMultiple, const QString &leftDelimiter, const QString &rightDelimiter, bool removeLeft, bool removeRight, QObject *parent = 0);
    explicit Tag(const QString &tagName, bool isMultiple, int rowcount);
    explicit Tag(const QString &tagName, Calculation calculation, QObject *parent = 0);

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
    bool _isConstant;
    Calculation _calculation;
};



#endif // TAG_H
