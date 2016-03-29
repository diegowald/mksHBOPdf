#include "templateprocessor.h"

TemplateProcessor::TemplateProcessor(const QString &filename, QObject *parent) : QObject(parent)
{
    _filename = filename;
}

TemplateProcessor::~TemplateProcessor()
{
}

QString TemplateProcessor::filename() const
{
    return _filename;
}
