#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include "documentparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
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
}

void MainWindow::defineTags()
{

}

void MainWindow::llenarArbol(DocumentParser &doc)
{
    doc.llenarArbol(ui->treeWidget);
}
