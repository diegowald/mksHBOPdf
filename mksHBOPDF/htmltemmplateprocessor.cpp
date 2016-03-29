#include "htmltemmplateprocessor.h"
#include <QTextStream>

HTMLTemmplateProcessor::HTMLTemmplateProcessor(const QString &filename, QObject *parent) : TemplateProcessor(filename, parent)
{
    _result = "";
}

HTMLTemmplateProcessor::~HTMLTemmplateProcessor()
{
    if (_file.isOpen())
        _file.close();
}


QString HTMLTemmplateProcessor::text()
{
    QTextStream s(&_file);
    QString txt(s.readAll());
    return txt;
}

void HTMLTemmplateProcessor::open()
{
    _file.setFileName(filename());
    _file.open(QIODevice::ReadOnly);
}

void HTMLTemmplateProcessor::applyResult(const QString &result)
{
    _result = result;
}

void HTMLTemmplateProcessor::save(const QString &filename)
{
    QFile file2(filename);
    file2.open(QIODevice::WriteOnly);
    QTextStream s2(&file2);
    s2 << _result;
    file2.close();
}
