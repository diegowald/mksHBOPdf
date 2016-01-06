#include "tagvalue.h"

TagValue::TagValue(const QString &tagName, const QString &value, int position, QObject *parent) : QObject(parent)
{
    _tagName = tagName;
    _value = value;
    _position = position;
}

QString TagValue::tagName() const
{
    return _tagName;
}

QString TagValue::value() const
{
    return _value;
}

int TagValue::position() const
{
    return _position;
}

void TagValue::addSubValue(TagValuePtr subValue)
{
    _subValues[subValue->tagName()] = subValue;
}

QTreeWidgetItem *TagValue::assTreeItem()
{
    QStringList lst;
    lst.append(_tagName);
    lst.append(_subValues.count() > 1 ? QString("") : _value);

    QTreeWidgetItem *item = new QTreeWidgetItem(lst);
    if (_subValues.count() > 0)
    {
        foreach (TagValuePtr tv, _subValues)
        {
            QTreeWidgetItem *subItem = tv->assTreeItem();
            item->addChild(subItem);
        }
    }
    return item;
}


QString TagValue::applyOnTemplate(const QString templateText)
{
    QString resultado = templateText;
    if (_subValues.count() > 0)
    {
        foreach (QString key, _subValues.keys())
        {
            resultado = _subValues[key]->applyOnTemplate(resultado);
        }
    }
    else
        resultado = resultado.replace(QString("@@%1@@").arg(_tagName), _value);
    return resultado;
}
