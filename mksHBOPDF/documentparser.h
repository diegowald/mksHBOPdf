#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <QObject>

class DocumentParser : public QObject
{
    Q_OBJECT
public:
    explicit DocumentParser(const QString &documentContents, QObject *parent = 0);
    bool parse();

private:
    QString extract(const QString &textoIzquierda, const QString &textoDerecha, int position = 0);
    QString extract(const QString from, const QString &textoIzquierda, const QString &textoDerecha, int position = 0);
signals:

public slots:
private:
    QString _source;

    QString _contratoNro;
    QString _codigoSeguridad;
    QString _Lugar;
    QString _Fecha;

    QString _Representante;
};

#endif // DOCUMENTPARSER_H
