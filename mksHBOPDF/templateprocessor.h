#ifndef TEMPLATEPROCESSOR_H
#define TEMPLATEPROCESSOR_H

#include <QObject>

class TemplateProcessor : public QObject
{
    Q_OBJECT
public:
    explicit TemplateProcessor(const QString &filename, QObject *parent = 0);
    virtual ~TemplateProcessor();

    virtual QString text() = 0;
    virtual void open() = 0;
    virtual void applyResult(const QString &result) = 0;
    virtual void save(const QString &filename) = 0;

    QString filename() const;
signals:

public slots:
private:
    QString _filename;
};

typedef QSharedPointer<TemplateProcessor> TemplateProcessorPtr;

#endif // TEMPLATEPROCESSOR_H
