#ifndef DLGEDITASEGURADO_H
#define DLGEDITASEGURADO_H

#include <QDialog>
#include "asegurado.h"


namespace Ui {
class DlgEditAsegurado;
}

class DlgEditAsegurado : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditAsegurado(AseguradoPtr asegurado, QWidget *parent = 0);
    ~DlgEditAsegurado();

private slots:
    void on_buttonBox_accepted();

private:
    void llenarControles();
private:
    Ui::DlgEditAsegurado *ui;
    AseguradoPtr _asegurado;
};

#endif // DLGEDITASEGURADO_H
