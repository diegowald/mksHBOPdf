#include "docxtemplateprocessor.h"
#include <QDebug>
DOCXTemplateProcessor::DOCXTemplateProcessor(const QString &filename, QObject *parent) : TemplateProcessor(filename, parent)
{
    _zipFile = NULL;
}


QString DOCXTemplateProcessor::text()
{
    return _uncompressed["word/document.xml"];
}

void DOCXTemplateProcessor::open()
{
    openAndReadInMemory(filename());

/*    leer este articulo como base
            http://stackoverflow.com/questions/2598117/zipping-a-folder-file-using-qt*/
}

void DOCXTemplateProcessor::applyResult(const QString &result)
{
    _new = result;
}

void DOCXTemplateProcessor::save(const QString &filename)
{
    saveFromMemory(filename);
}

bool DOCXTemplateProcessor::extract(const QString &filePath, const QString &extDirPath, const QString &singleFileName)
{
    QuaZip zip(filePath);
    zip.setFileNameCodec("IBM866");

    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning("testRead(): zip.open(): %d", zip.getZipError());
        return false;
    }

    zip.setFileNameCodec("IBM866");

    qWarning("%d entries\n", zip.getEntriesCount());
    qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFileInfo info;

    QuaZipFile file(&zip);

    QFile out;
    QString name;
    char c;
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        if (!zip.getCurrentFileInfo(&info)) {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return false;
        }
        qDebug() << info.name;

        if (!singleFileName.isEmpty())
            if (!info.name.contains(singleFileName))
                continue;

        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return false;
        }

        name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

        //out.setFileName("out/" + name);
        out.setFileName(name);

        // this will fail if "name" contains subdirectories, but we don't mind that
        out.open(QIODevice::WriteOnly);
        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either.
        // The slowest thing here is out.putChar(c).
        while (file.getChar(&c)) out.putChar(c);

        out.close();

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

        if (!file.atEnd()) {
            qWarning("testRead(): read all but not EOF");
            return false;
        }

        file.close();

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return false;
        }
    }

    zip.close();

    if (zip.getZipError() != UNZ_OK) {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
        return false;
    }

    return true;
}


QByteArray DOCXTemplateProcessor::fileContents(const QString &filePath, const QString &singleFileName)
{
    QByteArray res;
    QuaZip zip(filePath);
    zip.setFileNameCodec("IBM866");

    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning("testRead(): zip.open(): %d", zip.getZipError());
        return res;
    }

    zip.setFileNameCodec("IBM866");

    qWarning("%d entries\n", zip.getEntriesCount());
    qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFileInfo info;

    QuaZipFile file(&zip);

    QByteArray contents;
    char c;
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        if (!zip.getCurrentFileInfo(&info)) {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return res;
        }
        qDebug() << info.name;

        if (!singleFileName.isEmpty())
            if (!info.name.contains(singleFileName))
                continue;

        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return res;
        }

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return res;
        }

        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either.
        // The slowest thing here is out.putChar(c).

        while (file.getChar(&c))
        {
            contents.append(c);
        }

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return res;
        }

        if (!file.atEnd()) {
            qWarning("testRead(): read all but not EOF");
            return res;
        }

        file.close();

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return res;
        }
    }

    zip.close();

    if (zip.getZipError() != UNZ_OK) {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
        return res;
    }

    return contents;
}


bool DOCXTemplateProcessor::openAndReadInMemory(const QString &filePath)
{
    _uncompressed.clear();
    QuaZip zip(filePath);
    zip.setFileNameCodec("IBM866");

    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning("testRead(): zip.open(): %d", zip.getZipError());
        return false;
    }

    zip.setFileNameCodec("IBM866");

    qWarning("%d entries\n", zip.getEntriesCount());
    qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFileInfo info;

    QuaZipFile file(&zip);

    char c;
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        QByteArray contents;

        if (!zip.getCurrentFileInfo(&info)) {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return false;
        }
        qDebug() << info.name;


        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return false;
        }

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either.
        // The slowest thing here is out.putChar(c).

        while (file.getChar(&c))
        {
            contents.append(c);
        }

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

        if (!file.atEnd()) {
            qWarning("testRead(): read all but not EOF");
            return false;
        }

        _uncompressed[info.name] = contents;

        file.close();

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return false;
        }
    }

    zip.close();

    if (zip.getZipError() != UNZ_OK) {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
        return false;
    }

    return true;
}


bool DOCXTemplateProcessor::saveFromMemory(const QString &filePath)
{
    QuaZip zip(filePath);
    zip.setFileNameCodec("IBM866");

    if (!zip.open(QuaZip::mdCreate))
    {
        qWarning("testCreate(): zip.open(): %d", zip.getZipError());
        return false;
    }

    QuaZipFile outFile(&zip);

    char c;
    foreach (QString fname, _uncompressed.keys())
    {
        if (!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fname, fname)))
        {
//            qWarning((QString("testCreate(): outFile.open(): %1").arg(outFile.getZipError())).toStdString());
            return false;
        }

        QByteArray contents = (fname != "word/document.xml") ? _uncompressed[fname] : _new.toUtf8();
        for (int i = 0; i < contents.length(); ++i)
        {
            outFile.putChar(contents.at(i));
        }

        if (outFile.getZipError() != UNZ_OK) {
//            myMessageOutput(true, QtDebugMsg, QString("testCreate(): outFile.putChar(): %1").arg(outFile.getZipError()));
            return false;
        }

        outFile.close();

        if (outFile.getZipError() != UNZ_OK) {
//            myMessageOutput(true, QtDebugMsg, QString("testCreate(): outFile.close(): %1").arg(outFile.getZipError()));
            return false;
        }

    }

/*    if (!comment.isEmpty())
        zip.setComment(comment);*/

    zip.close();

    if (zip.getZipError() != 0)
    {
    //    myMessageOutput(true, QtDebugMsg, QString("testCreate(): zip.close(): %1").arg(zip.getZipError()));
        return false;
    }

    return true;
}
