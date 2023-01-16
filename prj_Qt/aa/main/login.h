#ifndef LOGIN_H
#define LOGIN_H

#include "libs/globals.h"
#include "VTKontTekkere.h"
#include "VTKontrol.h"
#include "VTTekton.h"

#include "main/dw_hesap.h"

namespace nSLogin {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QLineEdit *lE_user;
    QLineEdit *lE_pass;

private:
    QShortcut *keyESC;
    //dW_HESAP dw;

private slots:


    void logined();

public slots:
    void logout();
    void logex(const QString& nereden);
signals:
    void logok(QString, QString);

};

#endif // LOGIN_H
