#ifndef DLGEDITPOLIZA_H
#define DLGEDITPOLIZA_H

#include <QDialog>
#include "poliza.h"

namespace Ui {
class DlgEditPoliza;
}

class DlgEditPoliza : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditPoliza(PolizaPtr poliza, QWidget *parent = 0);
    ~DlgEditPoliza();

private slots:
    void on_buttonBox_accepted();

    void on_toolButton_released();

private:
    void llenarAsegurados();
    void llenarControles();
private:
    Ui::DlgEditPoliza *ui;
    PolizaPtr _poliza;
};

#endif // DLGEDITPOLIZA_H
