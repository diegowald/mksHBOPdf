#ifndef HTMLTEMMPLATEPROCESSOR_H
#define HTMLTEMMPLATEPROCESSOR_H

#include <QObject>
#include "templateprocessor.h"
#include <QFile>


class HTMLTemmplateProcessor : public TemplateProcessor
{
    Q_OBJECT
public:
    explicit HTMLTemmplateProcessor(const QString &filename, QObject *parent = 0);
    virtual ~HTMLTemmplateProcessor();

signals:

public slots:

    // TemplateProcessor interface
public:
    virtual QString text();
    virtual void open();
    virtual void applyResult(const QString &result);
    virtual void save(const QString &filename);

private:
    QFile _file;
    QString _result;
};

typedef QSharedPointer<HTMLTemmplateProcessor> HTMLTemmplateProcessorPtr;
#endif // HTMLTEMMPLATEPROCESSOR_H
