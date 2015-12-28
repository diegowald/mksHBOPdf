#include "documentparser.h"

DocumentParser::DocumentParser(const QString &documentContents, QObject *parent) : QObject(parent)
{
    _source = documentContents;
}

bool DocumentParser::parse()
{
    _contratoNro = extract("CONTRATO DE PRESTACIÓN DE SERVICIOS TURISTICOS N", "\n");
    _codigoSeguridad = extract("CÓDIGO DE SEGURIDAD:", "\n");
    _Lugar = extract("Lugar:", "\n");
    _Fecha = extract("Fecha:", "\n");

    QString substr = extract("Representantes del Contingente:", "Servicios a Prestar por la empresa:");
    _Representante = extract(substr, "Apellido y Nombres:", "\n");

    return true;
}

QString DocumentParser::extract(const QString &textoIzquierda, const QString &textoDerecha, int position)
{
    return extract(_source, textoIzquierda, textoDerecha, position);
}

QString DocumentParser::extract(const QString from, const QString &textoIzquierda, const QString &textoDerecha, int position)
{
    int desde = from.indexOf(textoIzquierda, position, Qt::CaseInsensitive) + textoIzquierda.length();
    int hasta = from.indexOf(textoDerecha, desde, Qt::CaseInsensitive);
    return from.mid(desde, hasta - desde);
}
