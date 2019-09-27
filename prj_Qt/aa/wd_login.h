#ifndef WD_LOGIN_H
#define WD_LOGIN_H

#include "globals.h"

namespace Ui {
class WD_login;
}

class WD_login : public QWidget
{
    Q_OBJECT

public:
    explicit WD_login();
    ~WD_login();
    QLineEdit *lE_user;
    QLineEdit *lE_pass;
    //QLineEdit *durum;
    QGroupBox *gr;
    QTextEdit *durum;

signals:
    void unlocked();


protected:
 void showEvent(QShowEvent *);

private slots:
    void on_pb_ok_clicked();
    void on_pb_out_clicked();
    void reject(); // esc key çalışmaz

private:
    void unlock_prg();
    void VTDosyaKontrol();
    //void quitApp();
 void quitApp();
};

#endif // WD_LOGIN_H
