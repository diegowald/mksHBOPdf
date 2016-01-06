#include "tag.h"
#include <QDebug>

Tag::Tag(const QString &tagName, bool isMultiple, const QString &leftDelimiter, const QString &rightDelimiter, bool removeLeft, bool removeRight, QObject *parent) : QObject(parent)
{
    _tagName = tagName;
    _leftDelimiter = leftDelimiter;
    _rightDelimiter = rightDelimiter;
    _isMultiple = isMultiple;
    _rowCount = 0;
    _removeLeft = removeLeft;
    _removeRight = removeRight;
}

Tag::Tag(const QString &tagName, bool isMultiple, int rowcount)
{
    _tagName = tagName;
    _isMultiple = isMultiple;
    _rowCount = rowcount;
}

QString Tag::tagName() const
{
    return _tagName;
}

QString Tag::leftDelimiter() const
{
    return _leftDelimiter;
}

QString Tag::rightDelimiter() const
{
    return _rightDelimiter;
}

QMap<QString, TagPtr> Tag::subtags() const
{
    return _subtags;
}


void Tag::addSubTag(TagPtr tag)
{
    _subtags[tag->tagName()] = tag;
}

QList<TagValuePtr> Tag::extractValue(const QString &source)
{
    qDebug() << "Tratando de obtener " << _tagName << ", isMultiple: " << (_isMultiple ? "SI" : "NO");
    QList<TagValuePtr> result;

    QPair<QString, int> valor;
    int fromPosition = 0;

    int currentIndex = 0;
    while (fromPosition != -1)
    {
        if (_rowCount == 0)
            valor = extractValueUsingDelimiters(source, fromPosition);
        else
            valor = extractValueUsingRows(source, fromPosition);

        qDebug() << _tagName << ": " << valor.first;
        TagValuePtr res = TagValuePtr::create(_isMultiple ? QString("%1:%2").arg(_tagName).arg(currentIndex) : _tagName, valor.first, valor.second);
        result.append(res);

        if ((valor.second > -1) && isComplex())
        {
            foreach (QString key, _subtags.keys())
            {
                TagPtr tag = _subtags[key];
                qDebug() << key << ", " << tag->tagName();
                QList<TagValuePtr> subValues = tag->extractValue(valor.first);

                foreach (TagValuePtr tv, subValues)
                {
                    res->addSubValue(tv);
                }
            }
        }
        fromPosition = _isMultiple ? valor.second + valor.first.length(): -1;
        if (_isMultiple)
            currentIndex++;
    }
    return result;
}

QPair<QString, int> Tag::extractValueUsingDelimiters(const QString &source, int startPosition)
{
    QPair<QString, int> result;
    result.first = "";
    result.second = -1;

    int desde = source.indexOf(_leftDelimiter, startPosition, Qt::CaseInsensitive);
    int hasta = -1;
    if (_rightDelimiter == "@@END@@")
    {
        hasta = source.length();
    }
    else
    {
        hasta = source.indexOf(_rightDelimiter, desde + _leftDelimiter.length(), Qt::CaseInsensitive);
    }

    if ((desde > -1) && (hasta > -1))
    {
        desde = desde + (_removeLeft ? _leftDelimiter.length() : 0);
        hasta = hasta + (_removeRight ? 0 : _rightDelimiter.length());
        QString valor = source.mid(desde, hasta - desde);
        qDebug() << valor;
        result.first = valor;
        result.second = desde;
    }
    return result;
}

QPair<QString, int> Tag::extractValueUsingRows(const QString &source, int startPosition)
{
    QPair<QString, int> result;
    result.first = "";
    result.second = -1;

    int hasta = startPosition;
    for (int i = 0; i < _rowCount; ++i)
    {
        hasta = source.indexOf("\n", hasta +1);
        if (hasta == -1)
            return result;
    }
    QString valor = source.mid(startPosition, hasta);
    result.first = valor;
    result.second = startPosition;
    return result;
}


bool Tag::isComplex() const
{
    return _subtags.count() > 0;
}

bool Tag::isMultiple() const
{
    return _isMultiple;
}
