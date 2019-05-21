#ifndef frmGrs_H
#define frmGrs_H

#include <QDialog>

namespace Ui {
class frmGrs;
}

class frmGrs : public QDialog
{
    Q_OBJECT

public:
    explicit frmGrs(QWidget *parent = 0);
    ~frmGrs();

signals:
    void LoginOK(QString name);

private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    Ui::frmGrs *ui;

    void closeEvent (QCloseEvent *event);
};

#endif // frmGrs_H
