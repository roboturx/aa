﻿#ifndef MW_main_H
#define MW_main_H

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

#include "globals.h"
//#include "wd_login.h"
#include "cw_per.h"
#include "cw_fr.h"
#include "cw_ftr.h"
#include "cw_grs.h"
#include "cw_mkn.h"
#include "cw_mlzm.h"
#include "login.h"
#include "form.h"
namespace Ui {
class MW_main;
}

class MW_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit MW_main();
    ~MW_main();
    QStackedWidget *stw{};
    QAction *act_main{};
    Cw_per *mw_per{};
    Cw_fr *mw_fr{};
    Cw_ftr *mw_ftr{};

    Form *mw_mkk{};
    Cw_mkn *mw_mkn{};
    Cw_Mlzm *mwMLZM{};


    QTextEdit *durum{};
    QLineEdit *lE_user{};
    QLineEdit *lE_pass{};
    QWidget *wd_log{};
    QWidget *wd_login{};
    QToolBar *toolBar{};

    void cik();
    void mwyaz ( const QString& z );
    Login *logger{};
    void login();


public:
    //void mwmain();  // constructor


private:
    void cr_MainWindow();
    void cr_DockWindows();
    void cr_Actions();
    void cr_StatusBar();

    void fade(bool ne);

    void closeEvent (QCloseEvent *event);
    void cr_about();

public slots:
    void logouted();
    void yetkiler(const QString& yetki, const QString& user);

signals:
    void cikis(QString);

};

#endif // MW_main_H
