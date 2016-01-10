#ifndef DOCUMENTTEMPLATE_H
#define DOCUMENTTEMPLATE_H

#include <QObject>

class DocumentTemplate : public QObject
{
    Q_OBJECT
public:
    explicit DocumentTemplate(QObject *parent = 0);

signals:

public slots:
};

#endif // DOCUMENTTEMPLATE_H