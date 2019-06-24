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
#include "clsn.h"
#include "frm.h"
#include "ftr.h"
#include "cw_grs.h"
#include "mkn.h"
#include "mlzm.h"
#include "login.h"
#include "form.h"
#include "dbase.h"
namespace Ui {
class MW_main;
}

class MW_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit MW_main();
    ~MW_main();
    DBase* dbase;
    QStackedWidget *stw{};
    QAction *act_main{};
    hC_CLSN *mw_per{};
    hC_FRM *mw_fr{};
    hC_FTR *mw_ftr{};

    Form *mw_mkk{};
    hC_MKN *mw_mkn{};
    hC_MLZM *mwMLZM{};


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
