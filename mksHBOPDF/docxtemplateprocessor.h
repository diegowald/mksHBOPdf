#ifndef DOCXTEMPLATEPROCESSORPTR_H
#define DOCXTEMPLATEPROCESSORPTR_H

#include <QObject>
#include "templateprocessor.h"
#include "../3rdParty/quazip-code/quazip/quazip/quazip.h"
#include "../3rdParty/quazip-code/quazip/quazip/quazipfile.h"
#include <QMap>

class DOCXTemplateProcessor : public TemplateProcessor
{
    Q_OBJECT
public:
    explicit DOCXTemplateProcessor(const QString &filename, QObject *parent = 0);

signals:

public slots:

    // TemplateProcessor interface
public:
    virtual QString text();
    virtual void open();
    virtual void applyResult(const QString &result);
    virtual void save(const QString &filename);
private:
    bool extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString(""));
    QByteArray fileContents(const QString & filePath, const QString &singleFileName);
    bool openAndReadInMemory(const QString &filePath);
    bool saveFromMemory(const QString &filePath);
private:
    QuaZip *_zipFile;
    QMap<QString, QByteArray> _uncompressed;
    QString _new;
};

typedef QSharedPointer<DOCXTemplateProcessor> DOCXTemplateProcessorPtr;
#endif // DOCXTEMPLATEPROCESSORPTR_H
