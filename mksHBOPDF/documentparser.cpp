#include "documentparser.h"
#include <QSharedPointer>

DocumentParser::DocumentParser(const QString &documentContents, QObject *parent) : QObject(parent)
{
    _source = documentContents;
    defineTagDefinitions();
}

bool DocumentParser::parse()
{
    _tagValues.clear();
    foreach (QString key, _tagDefinition.keys())
    {
        _tagValues[key] = _tagDefinition[key]->extractValue(_source);
    }

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

void DocumentParser::createTagDefinition(const QString &tagName, bool isMultiple, const QString &left, const QString &right)
{
    TagPtr tag = TagPtr::create(tagName, isMultiple, left, right);
    _tagDefinition[tag->tagName()] = tag;
}

void DocumentParser::createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, const QString &left, const QString &right)
{
    TagPtr tag = TagPtr::create(tagName, isMultiple, left, right);
    parentTag->addSubTag(tag);
}

void DocumentParser::createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, int rowcount)
{
    TagPtr tag = TagPtr::create(tagName, isMultiple, rowcount);
    parentTag->addSubTag(tag);
}

void DocumentParser::defineTagDefinitions()
{
    createTagDefinition("contrato", false, "CONTRATO DE PRESTACIÓN DE SERVICIOS TURISTICOS Nº ", "\n");
    createTagDefinition("codigoSeguridad", false, "CÓDIGO DE SEGURIDAD:", "\n");
    createTagDefinition("lugar", false, "Lugar:", "\n");
    createTagDefinition("fecha", false, "Fecha:", "\n");

    createTagDefinition("establecimiento", false, "Establecimiento Educativo: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "grado", false, "División/Grado: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "cantPasajeros", false, "Cant. estimada de pax: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "turno", false, "Turno: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "codPostal", false, "Cod. Post.: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "domicilio", false, "Domicilio: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "localidad", false, "Localidad: ", "\n");
    createTagDefinition(_tagDefinition["establecimiento"], "provincia", false, "Provincia: ", "\n");

    createTagDefinition("representantes", false, "Representantes del Contingente:", "Servicios a Prestar por la empresa:");
    createTagDefinition(_tagDefinition["representantes"], "nombre", false, "Apellido y Nombres:", "\n");
    createTagDefinition(_tagDefinition["representantes"], "dni", false, "DNI No: ", "\n");
    createTagDefinition(_tagDefinition["representantes"], "domicilio", false, "Domicilio: ", "\n");
    createTagDefinition(_tagDefinition["representantes"], "telefono", false, "Télefono: ", "\n");
    createTagDefinition(_tagDefinition["representantes"], "codPostal", false, "Cod. Postal: ", "\n");
    createTagDefinition(_tagDefinition["representantes"], "localidad", false, "Localidad: ", "\n");
    createTagDefinition(_tagDefinition["representantes"], "mail", false, "Mail: ", "\n");

    createTagDefinition("servicios", false, "Servicios a Prestar por la empresa:", "Hotelería:");
    createTagDefinition(_tagDefinition["servicios"], "destino", false, "Destino\n", "\n");
    createTagDefinition(_tagDefinition["servicios"], "dias", false, "Dias: ", "\n");
    createTagDefinition(_tagDefinition["servicios"], "noches", false, "Noches: ", "\n");
    createTagDefinition(_tagDefinition["servicios"], "quincena", false, "Quincena: ", "\n");
    createTagDefinition(_tagDefinition["servicios"], "mes", false, "Mes: ", "\n");
    createTagDefinition(_tagDefinition["servicios"], "anio", false, "Año: ", "\n");

    createTagDefinition("hoteleria", false, "Hotelería:", "Transporte de Larga Distancia:");
    /*
Hotel Domicilio Habitaciones Pensión
KOLCADOR SA - KOLCADOR VIAJES RAMBLA REP. DEL PERU CUADRUPLE MEDIA
1125
Página 1 de 12
Plazas
Contratadas
55
        Transporte de Larga Distancia:
    */

    createTagDefinition("transporteLargaDistancia", false, "Transporte de Larga Distancia:", "Transporte para traslados en el lugar de destino:");
    createTagDefinition("transporteTrasladosLugarDestino", false, "Transporte para traslados en el lugar de destino:", "Seguros y Asistencias Médica - Establecidos por la Ley No 25.599, modificada por la");


    createTagDefinition("seguros", false, "Seguros y Asistencias Médica - Establecidos por la Ley No 25.599, modificada por la\nley 26.208, reglamentados por Res.: 237/07", "Excursiones");
    createTagDefinition(_tagDefinition["seguros"], "polizaAccidentesPersonales", false, "Póliza de Accidentes Personales", "Póliza de Responsabilidad Civil");
    createTagDefinition(_tagDefinition["seguros"], "polizaResponsabilidadCivil", false, "Póliza de Responsabilidad Civil", "Asistencia Médica y Farmacéutica");
    createTagDefinition(_tagDefinition["seguros"], "asistenciaMedica", false, "Asistencia Médica y Farmacéutica ", "Asistencia al Viajero");
    createTagDefinition(_tagDefinition["seguros"], "asistenciaViajero", false, "Asistencia al Viajero", "Excursiones");

    createTagDefinition("precioPorContingente", false, "Precio por Contingente: $", "\n");
    createTagDefinition("precioPromedioPorPasajero", false, "Precio Promedio por Pasajero: $", "\n");

    createTagDefinition("contingente", false, "Listado de integrantes del contingente:\n", "@@END@@");
    //createTagDefinition(_tagDefinition["contingente"], "integrante", true, 13);
    createTagDefinition(_tagDefinition["contingente"], "integrante", true, "Apellidos y Nombres: ", "Apellidos y Nombres: ");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "nombre", false, "Apellidos y Nombres: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "dni", false, "D.N.I. Nº: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "domicilio", false, "Domicilio: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "codPostal", false, "Post.: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "telefono", false, "Teléfono: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "localidad", false, "Localidad: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "email", false, "Correo Electrónico: ", "\n");
    createTagDefinition(_tagDefinition["contingente"]->subtags()["integrante"], "representanteLegal", false, "Representante Legal: ", "\n");
}

void DocumentParser::llenarArbol(QTreeWidget *treeWidget)
{
    treeWidget->clear();
    foreach (QString key, _tagValues.keys())
    {
        QList<TagValuePtr> tags = _tagValues[key];
        foreach (TagValuePtr tv, tags)
        {
            QTreeWidgetItem *item = tv->assTreeItem();
            treeWidget->addTopLevelItem(item);
        }
    }
}
