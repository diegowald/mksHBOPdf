#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "documentparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void defineTags();
    void llenarArbol(DocumentParser &doc);
    void llenarPolizas();

private slots:
    void on_btnSeleccionarPDF_clicked();

    void on_btnProcesar_released();

    void on_btnPolizas_released();

private:
    Ui::MainWindow *ui;
    QString _filename;
    QString _fileContents;
};

#endif // MAINWINDOW_H
