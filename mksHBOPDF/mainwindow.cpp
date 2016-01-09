#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include "documentparser.h"
#include "dbhandler.h"
#include "dlgpolizas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbHandler::initialize();
    llenarPolizas();
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
    llenarArbol(doc);
    QFile file("./template.html");
    file.open(QIODevice::ReadOnly);
    QTextStream s(&file);
    QString txt(s.readAll());
    QString result = doc.applyOnTemplate(txt);
    ui->textBrowser_2->setHtml(result);

    QFile file2("./resultado.html");
    file2.open(QIODevice::WriteOnly);
    QTextStream s2(&file2);
    s2 << result;
    file2.close();
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
    dlg.exec();
}
