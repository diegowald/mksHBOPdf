#include "documentparser.h"
#include <QSharedPointer>
#include "dbhandler.h"
#include "suplemento.h"
#include <QDebug>

DocumentParser::DocumentParser(PolizaPtr poliza, const QString &documentContents, QObject *parent) : QObject(parent)
{
    _source = documentContents;
    _poliza = poliza;
    defineTagDefinitions();
    poliza->crearSuplemento();
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

TagPtr DocumentParser::createTagDefinition(const QString &tagName, bool isMultiple, const QString &left, const QString &right, bool removeLeft, bool removeRight)
{
    TagPtr tag = TagPtr::create(tagName, isMultiple, left, right, removeLeft, removeRight);
    _tagDefinition[tag->tagName()] = tag;
    return tag;
}

TagPtr DocumentParser::createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, const QString &left, const QString &right, bool removeLeft, bool removeRight)
{
    TagPtr tag = TagPtr::create(tagName, isMultiple, left, right, removeLeft, removeRight);
    parentTag->addSubTag(tag);
    return tag;
}

TagPtr DocumentParser::createTagDefinition(TagPtr parentTag, const QString &tagName, bool isMultiple, int rowcount)
{
    TagPtr tag = TagPtr::create(tagName, isMultiple, rowcount);
    parentTag->addSubTag(tag);
    return tag;
}

TagPtr DocumentParser::createTagDefinition(TagPtr parentTag, const QString &tagName, Calculation calculation)
{
    TagPtr tag = TagPtr::create(tagName, calculation);
    parentTag->addSubTag(tag);
    return tag;
}

void DocumentParser::defineTagDefinitions()
{
    TagPtr root = createTagDefinition("definition", false, "", "@@END@@");
    createTagDefinition(root, "NroPoliza", [&] () -> QString
    {
                            return QString::number(nroPoliza());
                        });

    createTagDefinition(root, "NroSuplemento", [&] () -> QString
    {
                            return QString::number(nroSuplemento());
                        });

    createTagDefinition(root, "Tomador", [&] () -> QString
    {
                            return tomador();
                        });

    createTagDefinition(root, "ObjetoPoliza", [&] () -> QString
    {
                            return objetoPoliza();
                        });

    createTagDefinition(root, "MontoContingente", [&] () -> QString
    {
                            return QString::number(montoContingente());
                        });

    createTagDefinition(root, "MontoPasajero", [&] () -> QString
    {
                            return QString::number(montoPasajero());
                        });

    createTagDefinition(root, "SumaAsegurada", [&] () -> QString
    {
                            return QString::number(sumaAsegurada());
                        });

    createTagDefinition(root, "contrato", false, "CONTRATO DE PRESTACIÓN DE SERVICIOS TURISTICOS Nº ", "\n");
    createTagDefinition(root, "codigoSeguridad", false, "CÓDIGO DE SEGURIDAD:", "\n");
    createTagDefinition(root, "lugar", false, "Lugar:", "\n");
    createTagDefinition(root, "fecha", false, "Fecha:", "\n");

    TagPtr tag = createTagDefinition(root, "establecimiento", false, "Establecimiento Educativo: ", "\n");
    createTagDefinition(root, "grado", false, "División/Grado: ", "\n");
    createTagDefinition(root, "cantPasajeros", false, "Cant. estimada de pax: ", "\n");
    createTagDefinition(root, "turno", false, "Turno: ", "\n");
    createTagDefinition(root, "codPostal", false, "Cod. Post.: ", "\n");
    createTagDefinition(root, "domicilio", false, "Domicilio: ", "\n");
    createTagDefinition(root, "localidad", false, "Localidad: ", "\n");
    createTagDefinition(root, "provincia", false, "Provincia: ", "\n");

    tag = createTagDefinition(root, "representantes", false, "Representantes del Contingente:", "Servicios a Prestar por la empresa:");
    createTagDefinition(tag, "nombre", false, "Apellido y Nombres:", "\n");
    createTagDefinition(tag, "dni", false, "DNI No: ", "\n");
    createTagDefinition(tag, "domicilio", false, "Domicilio: ", "\n");
    createTagDefinition(tag, "telefono", false, "Télefono: ", "\n");
    createTagDefinition(tag, "codPostal", false, "Cod. Postal: ", "\n");
    createTagDefinition(tag, "localidad", false, "Localidad: ", "\n");
    createTagDefinition(tag, "mail", false, "Mail: ", "\n");

    tag = createTagDefinition(root, "servicios", false, "Servicios a Prestar por la empresa:", "Hotelería:");
    createTagDefinition(tag, "destino", false, "Destino\n", "\n");
    createTagDefinition(tag, "dias", false, "Dias: ", "\n");
    createTagDefinition(tag, "noches", false, "Noches: ", "\n");
    createTagDefinition(tag, "quincena", false, "Quincena: ", "\n");
    createTagDefinition(tag, "mes", false, "Mes: ", "\n");
    createTagDefinition(tag, "anio", false, "Año: ", "\n");

    createTagDefinition(root, "hoteleria", false, "Hotelería:", "Transporte de Larga Distancia:");
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

    createTagDefinition(root, "transporteLargaDistancia", false, "Transporte de Larga Distancia:", "Transporte para traslados en el lugar de destino:");
    createTagDefinition(root, "transporteTrasladosLugarDestino", false, "Transporte para traslados en el lugar de destino:", "Seguros y Asistencias Médica - Establecidos por la Ley No 25.599, modificada por la");


    tag = createTagDefinition(root, "seguros", false, "Seguros y Asistencias Médica - Establecidos por la Ley No 25.599, modificada por la\nley 26.208, reglamentados por Res.: 237/07", "Excursiones");
    createTagDefinition(tag, "polizaAccidentesPersonales", false, "Póliza de Accidentes Personales", "Póliza de Responsabilidad Civil");
    createTagDefinition(tag, "polizaResponsabilidadCivil", false, "Póliza de Responsabilidad Civil", "Asistencia Médica y Farmacéutica");
    createTagDefinition(tag, "asistenciaMedica", false, "Asistencia Médica y Farmacéutica ", "Asistencia al Viajero");
    createTagDefinition(tag, "asistenciaViajero", false, "Asistencia al Viajero", "Excursiones");

    createTagDefinition(root, "precioPorContingente", false, "Precio por Contingente: $", "\n");
    createTagDefinition(root, "precioPromedioPorPasajero", false, "Precio Promedio por Pasajero: $", "\n");

    tag = createTagDefinition(root, "contingente", false, "Listado de integrantes del contingente:\n", "@@END@@");
    //createTagDefinition(_tagDefinition["contingente"], "integrante", true, 13);
    tag = createTagDefinition(tag, "integrante", true, "Apellidos y Nombres: ", "Apellidos y Nombres: ", false);
    createTagDefinition(tag, "nombre", false, "Apellidos y Nombres: ", "\n");
    createTagDefinition(tag, "dni", false, "D.N.I. Nº: ", "\n");
    createTagDefinition(tag, "domicilio", false, "Domicilio: ", "\n");
    createTagDefinition(tag, "codPostal", false, "Post.: ", "\n");
    createTagDefinition(tag, "telefono", false, "Teléfono: ", "\n");
    createTagDefinition(tag, "localidad", false, "Localidad: ", "\n");
    createTagDefinition(tag, "email", false, "Correo Electrónico: ", "\n");
    createTagDefinition(tag, "representanteLegal", false, "Representante Legal: ", "\n");
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

QString DocumentParser::applyOnTemplate(const QString &templateTxt)
{
    QString resultado = templateTxt;
    foreach (QString key, _tagValues.keys())
    {
        if (_tagValues[key].count() > 0)
        {
            foreach (TagValuePtr tv, _tagValues[key])
            {
                resultado = tv->applyOnTemplate(resultado);
            }
        }
    }
    return resultado;
}


int DocumentParser::nroSuplemento()
{
    return _poliza->suplementoNuevo()->nroSuplemento();
}

int DocumentParser::nroPoliza()
{
    return _poliza->nroPoliza();
}

QString DocumentParser::tomador()
{
    return _poliza->tomador();
}

QString DocumentParser::objetoPoliza()
{
    return _poliza->objeto();
}

double DocumentParser::montoContingente()
{
    TagValuePtr tv = _tagValues["definition"].at(0)->subValue("precioPorContingente");
    QString v = tv->value();
    return v.toDouble();
}

double DocumentParser::montoPasajero()
{
    TagValuePtr tv = _tagValues["definition"].at(0)->subValue("precioPromedioPorPasajero");
    QString v = tv->value();
    return v.toDouble();
}

double DocumentParser::sumaAsegurada()
{
    double pct = _poliza->asegurado()->porcentaje();
    double valor = montoContingente() * pct / 100;
    _poliza->suplementoNuevo()->setMonto(valor);
    return valor;
}
