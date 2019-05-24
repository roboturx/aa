#ifndef MW_main_H
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
#include "cw_ambar.h"
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
    QStackedWidget *stw;
    QAction *act_main;
    Cw_per *mw_per;
    Cw_fr *mw_fr;
    Cw_ftr *mw_ftr;
    Form *mw_mkk;
    Cw_mkn *mw_mkn;
    Cw_Ambar *mw_depo;


    QTextEdit *durum;
    QLineEdit *lE_user;
    QLineEdit *lE_pass;
    QWidget *wd_log;
    QWidget *wd_login;
    QToolBar *toolBar;

    void cik();
    void yaz(QString x, QString y);
    Login *logger;
    void login();


public:

    QSqlRelationalTableModel *modelFatura();

private:
    void cr_MainWindow();
    void cr_DockWindows();
    void cr_Actions();
    void cr_StatusBar();

    void fade(bool ne);

//    void dbcontrol();
    bool dbcontrol();      // veritabanı yoksa oluştur, bağlan
    void VTDosyaKontrol();

     bool VTd_CLSN();
     bool VTd_MSLK();
     bool VTd_FRMA();
     bool VTd_FTRA();
     QSqlRelationalTableModel *mdlFtr;

     bool VTd_FTDT();


    void VTd_mkn ();
    void VTd_Ambar ();
    void VTd_AmbarDETAY ();
    void VTd_CINS ();
    void VTd_MARKA ();
    void VTd_MODEL ();


    void VTd_ISEMRI ();
    void VTd_ISEMRIDETAY ();
    void VTd_IEDTAMIRYERI ();
    void VTd_IEDTYDETAY ();
    void VTd_ISCILIK ();
    void VTd_TASINIR () ;

    void VTd_MKYAG ();
    void VTd_MKFILTRE ();
    void VTd_MKAKU ();
    void VTd_MKLASTIK ();
    void VTd_MKMUAYENE ();
    void VTd_MKSIGORTA ();
    void VTd_MKYAKIT ();
    void VTd_MKANTIFIRIZ ();
    void VTd_MKZINCIR ();
    void VTd_MKHGS ();

    void closeEvent (QCloseEvent *event);
    void cr_about();

public slots:
    void logouted();
    void yetkiler(QString yetki, QString user);
    void cw_main ();
    void cw_mkn ();    /// mkn central widget
    void cw_dpo ();    /// depo central widget
    void cw_per ();    /// personel central widget
    void cw_fr ();     /// firma central widget
    void cw_ftr ();     /// fatura central widget
    void quitApp();
    void hkk();

signals:
    void cikis(QString);

};

#endif // MW_main_H
