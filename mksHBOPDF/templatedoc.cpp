#include "templatedoc.h"
#include <QFileInfo>

TemplateDoc::TemplateDoc(const QString filePath) : QObject()
{
    _filePath = filePath;
    QFileInfo fileInfo(_filePath);
    _filename = fileInfo.fileName();
}

QString TemplateDoc::filename() const
{
    return _filename;
}

QString TemplateDoc::filePath() const
{
    return _filePath;
}
