#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include "documentparser.h"
#include "dbhandler.h"
#include "dlgpolizas.h"
#include "htmltemmplateprocessor.h"
#include "docxtemplateprocessor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbHandler::initialize();
    llenarPolizas();
    llenarTemplates();
}

MainWindow::~MainWindow()
{
    dbHandler::finalize();
    delete ui;
}

void MainWindow::on_btnSeleccionarPDF_clicked()
{
    _filename = QFileDialog::getOpenFileName(this, "Abrir PDF", "./", "pdf (*.pdf)");
    QProcess *process = new QProcess(this);
    QString program = "/usr/bin/pdftotext";
    process->start(program, QStringList() << _filename << "-");
    process->waitForFinished(30000);
    _fileContents = QString(process->readAllStandardOutput());
    ui->textBrowser->setText(_fileContents);
}

void MainWindow::on_btnProcesar_released()
{
    DocumentParser doc(_fileContents, this);
    doc.parse();
    doc.addDatosPoliza();
    llenarArbol(doc);

    QString fileResult = "./result.docx";

    TemplateProcessorPtr templateProc = crearTemplateProcessor(ui->cboTemplate->currentData().toString());
    templateProc->open();
    QString txt = templateProc->text();
    QString result = doc.applyOnTemplate(txt);
    templateProc->applyResult(result);
    templateProc->save(fileResult);

    ui->textBrowser_2->setHtml(result);
}

void MainWindow::defineTags()
{

}

void MainWindow::llenarArbol(DocumentParser &doc)
{
    doc.llenarArbol(ui->treeWidget);
}


void MainWindow::llenarPolizas()
{
    ui->cboPolizas->clear();
    QList<PolizaPtr> polizas = dbHandler::instance()->getPolizas();
    foreach (PolizaPtr poliza, polizas)
    {
        ui->cboPolizas->addItem(poliza->denominacionPoliza(), poliza->id());
    }
}

void MainWindow::on_btnPolizas_released()
{
    DlgPolizas dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        llenarPolizas();
    }
}


void MainWindow::llenarTemplates()
{
    ui->cboTemplate->clear();
    QList<TemplateDocPtr> templates = dbHandler::instance()->getTemplates();
    foreach (TemplateDocPtr temp, templates)
    {
        ui->cboTemplate->addItem(temp->filename(), temp->filePath());
    }
}

TemplateProcessorPtr MainWindow::crearTemplateProcessor(const QString &filename)
{
    QString upperFilename = filename.toUpper();
    if (upperFilename.endsWith(".HTML"))
    {
        return HTMLTemmplateProcessorPtr::create(filename);
    }
    else if (upperFilename.endsWith(".DOCX"))
    {
        return DOCXTemplateProcessorPtr::create(filename);
    }
    return TemplateProcessorPtr();
}
