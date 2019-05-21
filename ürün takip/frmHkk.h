#ifndef frmHkk_H
#define frmHkk_H

#include <QDialog>

namespace Ui {
class frmHkk;
}

class frmHkk : public QDialog
{
    Q_OBJECT

public:
    explicit frmHkk(QWidget *parent = 0);
    ~frmHkk();

private slots:
    void on_btnOK_clicked();
    void on_btnOK_2_clicked();

private:
    Ui::frmHkk *ui;
};

#endif // frmHkk_H
