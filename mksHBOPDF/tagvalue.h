#ifndef TAGVALUE_H
#define TAGVALUE_H

#include <QObject>
#include <QSharedPointer>
#include <QMap>

class TagValue;

typedef QSharedPointer<TagValue> TagValuePtr;



class TagValue : public QObject
{
    Q_OBJECT
public:
    explicit TagValue(const QString &tagName, const QString &value, int position, QObject *parent = 0);

    QString tagName() const;
    QString value() const;
    int position() const;

    void addSubValue(TagValuePtr subValue);

signals:

public slots:

private:
    QString _tagName;
    QString _value;
    int _position;
    QMap<QString, TagValuePtr> _subValues;
};


#endif // TAGVALUE_H
