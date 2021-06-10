#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtSql>
#include "database.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);


    void login();

    ~LoginDialog();

private slots:
    void on_pushButton_clicked();

private:
    bool checkLicence();
    void setupConnection();
    Ui::LoginDialog *ui;
    DataBase* dBase;
};

#endif // LOGINDIALOG_H
