#include "tagvalue.h"
#include "tag.h"
#include <QDebug>

TagValue::TagValue(TagPtr tagDefinition, int index, const QString &value, int position, QObject *parent) : QObject(parent)
{
    _tagdefinition = tagDefinition;
    _value = value;
    _position = position;
    _index = index;
    _useCalculation = false;
}


TagValue::TagValue(TagPtr tagDefinition, Calculation calculation, QObject *parent) : QObject(parent)
{
    _tagdefinition = tagDefinition;
    _calculation = calculation;
    _useCalculation = true;
}

QString TagValue::tagName() const
{
    return _index == -1 ? _tagdefinition->tagName() : QString("%1:%2").arg(_tagdefinition->tagName()).arg(_index);
}

QString TagValue::value()
{
    return _useCalculation ? _calculation() : _value;
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

QString TagValue::applyContingenteOnTemplate(const QString templateText)
{
    int from  = templateText.indexOf("@@contingente@@");
    int to = templateText.indexOf("@@/contingente@@");
    QString t = templateText.mid(from + 15, to - from - 15);
    qDebug() << t;
    QString resultadoAcumulado = "";
    foreach (QString key, _subValues.keys())
    {
        QString templ = t;
        TagValuePtr subTag = _subValues[key]; // integrante
        foreach (QString k, subTag->_subValues.keys())
        {
            TagValuePtr st = subTag->_subValues[k];
            templ = st->applyOnTemplate(templ);
        }
        resultadoAcumulado += templ;
    }
    QString result = templateText;
    result = result.replace(from, to - from, resultadoAcumulado);
    return result;
}

QString TagValue::applyOnTemplate(const QString templateText)
{
    if (_tagdefinition->tagName() == "contingente")
        return applyContingenteOnTemplate(templateText);

    QString resultado = templateText;
    if (_subValues.count() > 0)
    {
        foreach (QString key, _subValues.keys())
        {
            TagValuePtr subTag = _subValues[key];
            resultado = _subValues[key]->applyOnTemplate(resultado);
        }
    }
    else
        resultado = resultado.replace(QString("@@%1@@").arg(_tagdefinition->tagName()), value());
    return resultado;
}

TagValuePtr TagValue::subValue(const QString &key)
{
    return _subValues[key];
}
