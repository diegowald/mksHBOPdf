#include "tagvalue.h"
#include "tag.h"


TagValue::TagValue(TagPtr tagDefinition, int index, const QString &value, int position, QObject *parent) : QObject(parent)
{
    _tagdefinition = tagDefinition;
    _value = value;
    _position = position;
    _index = index;
}

QString TagValue::tagName() const
{
    return _index == -1 ? _tagdefinition->tagName() : QString("%1:%2").arg(_tagdefinition->tagName()).arg(_index);
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
    lst.append(tagName());
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
            TagValuePtr subTag = _subValues[key];
            if (subTag->tagDefinition()->isMultiple())
            {
                QString
            }
            resultado = _subValues[key]->applyOnTemplate(resultado);
        }
    }
    else
        resultado = resultado.replace(QString("@@%1@@").arg(_tagdefinition->tagName()), _value);
    return resultado;
}
