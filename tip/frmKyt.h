#ifndef frmKyt_H
#define frmKyt_H

#include <QDialog>

namespace Ui {
class frmKyt;
}

class frmKyt : public QDialog
{
    Q_OBJECT

private:
    void Clear();
    bool CheckInputs();

public:
    explicit frmKyt(QWidget *parent = 0);
    ~frmKyt();

private slots:
    void on_btnRegister_clicked();

private:
    Ui::frmKyt *ui;
};

#endif // frmKyt_H
