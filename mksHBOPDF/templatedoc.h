#ifndef TEMPLATEDOC_H
#define TEMPLATEDOC_H

#include <QObject>

class TemplateDoc : public QObject
{
    Q_OBJECT
public:
    explicit TemplateDoc(const QString filePath);

    QString filename() const;
    QString filePath() const;

signals:

public slots:

private:
    QString _filename;
    QString _filePath;
};

typedef QSharedPointer<TemplateDoc> TemplateDocPtr;

#endif // TEMPLATEDOC_H
