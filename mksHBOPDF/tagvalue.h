#ifndef TAGVALUE_H
#define TAGVALUE_H

#include <QObject>
#include <QSharedPointer>
#include <QMap>
#include <QTreeWidgetItem>

class Tag;

typedef QSharedPointer<Tag> TagPtr;

class TagValue;

typedef QSharedPointer<TagValue> TagValuePtr;



class TagValue : public QObject
{
    Q_OBJECT
public:
    explicit TagValue(TagPtr tagDefinition, int index, const QString &value, int position, QObject *parent = 0);

    TagPtr tagDefinition() const;
    QString tagName() const;
    QString value() const;
    int position() const;

    void addSubValue(TagValuePtr subValue);
    QTreeWidgetItem * assTreeItem();

    QString applyOnTemplate(const QString templateText);

signals:

public slots:

private:
    TagPtr _tagdefinition;
    QString _value;
    int _position;
    QMap<QString, TagValuePtr> _subValues;
    int _index;
};


#endif // TAGVALUE_H

