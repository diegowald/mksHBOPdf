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
