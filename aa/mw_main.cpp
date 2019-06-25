#include "mw_main.h" // main
#include "clsn.h"  // stack per
#include "frm.h"   // stack fr
#include "mkn.h"  // stack mkn
#include "cw_grs.h"  // stack giris
#include "mlzm.h"// stack Mlzm
#include "cw_hkk.h"  // hakk1nda
#include "login.h"

#include "globals.h"
#include "form.h"
#include <sortingbox.h>



MW_main::MW_main( )
= default;

void MW_main::login()
{
    cr_Actions ();
    //    this->setWindowFlags(Qt::Window |
    //                         Qt::FramelessWindowHint );

    /// ana ekran
    /////////////////////////////////////////////////////
    // qDebug() << "main log";
    this->setWindowTitle ("Makina İkmal Atölye Yönetim Uygulaması");
    this->setGeometry (200,200,600,100);
    MW_main::showMaximized ();

    wd_log = new QWidget(this);
    this->setCentralWidget (wd_log);

    auto *lg = new QGridLayout(wd_log);
    wd_log->setLayout(lg);

    //  durum = new QTextEdit(wd_log);
    //durum->setReadOnly (true);


    auto * sortingBox = new SortingBox;
    // lg->addWidget(durum  ,0,0,2,1);
    lg->addWidget(  sortingBox  ,2,0,9,1);


    //  mwyaz(QDate::currentDate ().toString());


    // fade(true);


    /// veritabanı kontrol
    qDebug() << "db control";
    dbase =new DBase();
    dbase->setGeometry (600,300,300,480);
    dbase->setWindowTitle("Veri Tabanı Kontrol");
    //dbase->yaz("dbase mw_main show");
    dbase->show();
    if (! dbase->setupDBase ())
    {
        /// hata ne /// baglanti yok
        dbase->yaz("----------------------------------------");
        dbase->yaz("HATA - Veri Tabanı Bağlantısı Yapılamadı");
        return;
    }
    
    
    /// baglanti var /// uygulama yoluna devam etsin

    dbase->yaz("----------------------------------------");
    dbase->yaz("OK - Veri Tabanı Bağlantısı Yapıldı");
    qDebug() << "OK - Veri Tabanı Bağlantısı Yapıldı";

    



    /// login için esc-enter kullanımı
    /////////////////////////////////////
    /*
     logger= new Login;

WARNING  şifre için burayı kullan

       connect(logger, &Login::logok, this, &MW_main::yetkiler);
    connect(this, &MW_main::cikis, logger, &Login::logex );
    //connect(this, &MW_main::cikis, qApp , &QApplication::quit );

    //qDebug() << "main keys set ESC";
    QShortcut * sc_ESC = new QShortcut(
                QKeySequence(Qt::Key_Escape),this,
                SLOT(logouted() ));
    sc_ESC->setAutoRepeat(false);
*/
    /// all things okey
    /// wait for a key for connect
}

void MW_main::yetkiler(const QString& yetki, const QString& user)
{
    //    this->setFocus ();
    qDebug() << "yetkiler ="<<yetki;
    QString x ="++++ Kullanıcı ( "+user +" ) - ( "+ yetki +
            " ) yetkileri ile bağlandı";
    dbase->yaz(QDateTime::currentDateTime ().toString() + x);

}



void MW_main::logouted()
{
    GLB_yetki = "İlk";
    QString x =" +++ ( "+logger->lE_user->text ()+
            " ) kullanıcısı ile yapılan bağlantı sona erdi...";
    dbase->yaz(QDateTime::currentDateTime ().toString() + x);
    logger->lE_user->setFocus ();
    logger->lE_user->setText ("");
    logger->lE_pass->setText ("");
    logger->show ();

}





void MW_main::cr_Actions()
{
    /////////////////// ana menü
    qDebug() << "main menu ";

    ////////////////////////////////////////////////////////////////
    /// main
    ///
    ///

    QMenu *mn_main  = menuBar()->addMenu(tr("&Giriş"));
    QToolBar *tb_main = addToolBar(tr("Makina İkmal"));
    tb_main->setMaximumHeight (50);
    tb_main->setMaximumWidth (650);
    tb_main->setMinimumWidth (450);
    tb_main->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb_main->setAllowedAreas(Qt::LeftToolBarArea);

    auto *act_main = new QAction(QIcon(":/rsm/home.png"),
                          tr("&Kontrol Merkezi..."), this);
    act_main->setStatusTip("Ana Pencere" );
    act_main->setWhatsThis("Program Giriş Sayfas1");
    act_main->setShortcut(QKeySequence(tr("Ctrl+K")));
    act_main->setShortcutContext(Qt::ApplicationShortcut);
    act_main->setStatusTip(tr("Ana Ekran"));
    mn_main->addAction(act_main);
    tb_main->addAction(act_main);

    //////// G İ R İ Ş
    connect( act_main , &QAction::triggered,

             [this]()
    {
        mw_mkk = new Form();
        statusBar()->showMessage( "Kontrol Merkezi" );
        mw_mkk->setWindowTitle ( GLB_yetki );
        mw_mkk->resize(qApp->screens()[0]->size()*.6);
        mw_mkk ->show ();
    });



    menuBar()->addSeparator();
    tb_main->addSeparator ();


    QMenu *mn_atlye = menuBar()->addMenu(tr("&Atölye"));
    /// mkn
    auto *act_mkn = new QAction(QIcon(":/rsm/ex.png"),
                                tr("&Makina..."), this);
    act_mkn->setStatusTip(tr("Demirbaş Mlzm"));
    act_mkn->setShortcut(QKeySequence(tr("Ctrl+M")));
    mn_atlye->addAction(act_mkn);
    //tb_main->addAction(act_mkn);
    connect( act_mkn , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Demirbaş Mlzm"));
        auto *mw_mkn = new hC_MKN;
        mw_mkn->mkn_setup ();

    });


    QMenu *mn_mkn = mn_atlye->addMenu(tr("&Mkcins"));
    /// mkn
    auto *act_mkc = new QAction(QIcon(":/rsm/ex.png"),
                                tr("&Makina..."), this);
    act_mkc->setStatusTip(tr("Demirbaş Mlzm"));
    //act_mkc->setShortcut(QKeycequence(tr("Ctrl+M")));
    mn_mkn->addAction(act_mkc);
    //tb_main->addAction(act_mkn);
    connect( act_mkn , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Demirbaş Mlzm"));
        auto *mw_mkn = new hC_MKN;
        mw_mkn->mkn_setup ();

    });



    /// personel
    auto *act_per = new QAction(QIcon(":/rsm/worker.jpeg"),
                                tr("&Personel..."), this);
    act_per->setShortcut(QKeySequence(tr("Ctrl+P")));
    act_per->setStatusTip(tr("Personel"));
    mn_atlye->addAction(act_per);
    // tb_main->addAction(act_per);
    connect( act_per , &QAction::triggered,
             [this]()
    {
        mw_per = new hC_CLSN ;
        mw_per->clsn_setup ();
        //statusBar()->showMessage(tr("Çalışan Bilgileri"));
        //mw_per->setWindowTitle ("ÇALIŞAN");
        //mw_per->resize(qApp->screens()[0]->size()*.8);
        mw_per->show ();
    });



    QMenu *mn_mbar  = menuBar()->addMenu(tr("&Ambar"));
    /// dpo    Mlzm kontrol
    auto *act_dpo = new QAction(QIcon(":/rsm/plt.png"),
                                tr("&Mlzm..."), this);
    act_dpo->setShortcut(QKeySequence(tr("Ctrl+S")));
    act_dpo->setShortcutContext(Qt::ApplicationShortcut);
    act_dpo->setStatusTip(tr("Mlzm Kontrol "));
    mn_mbar->addAction(act_dpo);
    // tb_main->addAction(act_dpo);
    connect( act_dpo , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Mlzm "));
        mwMLZM = new hC_MLZM;
        mwMLZM->setup_mlzm ();
        mwMLZM->show ();
    });


    QMenu *mn_stnlm = menuBar()->addMenu(tr("&Satın Alma"));


    /// fatura
    auto *act_ftr = new QAction(QIcon(""),
                                tr("&Fatura..."), this);
    act_ftr->setShortcut(QKeySequence(tr("Ctrl+t")));
    act_ftr->setStatusTip(tr("Fatura"));
    mn_stnlm->addAction(act_ftr);
    // tb_main->addAction(act_ftr);
    connect( act_ftr , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Mlzm Faturalı Mal Girişi"));
        mw_ftr = new hC_FTR;
        mw_ftr->ftr_setup ();
        mw_ftr->show ();
    });
    /// firma
    auto *act_fr = new QAction(QIcon(""),
                               tr("&Firma..."), this);
    act_fr->setShortcut(QKeySequence(tr("Ctrl+f")));
    act_fr->setStatusTip(tr("Firma"));
    mn_stnlm->addAction(act_fr);
    //tb_main->addAction(act_fr);
    connect( act_fr , &QAction::triggered,
             [this]()
    {
        mw_fr = new hC_FRM;
        mw_fr->frm_setup ();
        statusBar()->showMessage(tr("Firma Bilgileri"));
        mw_fr->show ();
    });



    menuBar()->addSeparator();

    tb_main->addSeparator ();
    /// Çıkış
    auto *act_Quit = mn_main->addAction(tr("&Çıkış"),
                                        this, &QWidget::close);
    //QAction *act_Quit = new QAction(QIcon(":/rsm/out.ico"),
    //                             tr("&Çıkış..."), this);
    act_Quit->setIcon (QIcon(":/rsm/out.ico"));

    act_Quit->setShortcuts(QKeySequence::Quit);
    act_Quit->setStatusTip(tr("Programdan Çıkış "));
    mn_main->addAction(act_Quit);
    tb_main->addAction(act_Quit);
    connect(act_Quit , &QAction::triggered,
            [this]()
    {
        emit cikis("Ana Menu act");
    });

    ////////////////////////////////////////////////////////////////
    ///////////////////////
    /// \brief mn_yrdm
    ///
    QMenu *mn_yrdm = menuBar()->addMenu(tr("&Yardım"));


    /// hakkında
    auto *act_hkk = new QAction(QIcon(":/rsm/worker.jpeg"),
                                tr("&Uygulama Hakkında"), this);
    act_hkk->setShortcut(QKeySequence(tr("Ctrl+U")));
    act_hkk->setStatusTip(tr("Hakkında"));
    mn_yrdm->addAction(act_hkk);
    //  tb_main->addAction(act_hkk);
    connect( act_hkk , &QAction::triggered,
             []()
    {
        auto *m_cw_hkk = new CW_hkk;
        m_cw_hkk->show ();
    });

}

void MW_main::cr_StatusBar()
{   statusBar()->showMessage(tr("Status Ready")); }

void MW_main::cr_about()
{   statusBar()->showMessage(tr("About Ready")); }



void MW_main::cik()
{
    emit cikis("Ana Menu");
    //qApp->quit();
}

void MW_main::closeEvent (QCloseEvent *event)
{
    QMessageBox msgBox;
    QPushButton *bt_evet = msgBox.addButton(tr("&Sonlandır"), QMessageBox::YesRole);
    QPushButton *bt_hyr  = msgBox.addButton(tr("&Vazgeç"), QMessageBox::NoRole);

    msgBox.setWindowTitle ("GİRİŞ KONTROL");
    msgBox.setText(tr("<br>    Uygulama sona erdirilsin mi ?    <br>"));
    msgBox.exec();

    if (msgBox.clickedButton() == bt_hyr)
    {
        event->ignore();
    }
    else if (msgBox.clickedButton() == bt_evet)
    {
        qApp->closeAllWindows();
        event->accept();
        //quitApp();
        emit cikis("Close Event");
    }
}



MW_main::~MW_main()
{
    delete stw;
    delete act_main;
    delete mw_per;
    delete mw_mkk;
    delete mw_mkn;
    //  delete mw_Mlzm;
}


void MW_main::fade(bool ne)
{

    if (!ne)
    {
        for (double i=1;i>0;i=i-0.001)
        {
            this->setWindowOpacity(i);
#ifdef WINDOWS
            Sleep(1);
#endif
#ifdef LINUX
            usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif

        }
        this->setWindowOpacity(0);
    }
    else
    {
        for (double i=0;i>1;i=i+0.0001)
        {
            this->setWindowOpacity(i);
#ifdef WINDOWS
            Sleep(1);
#endif
#ifdef LINUX
            usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif


            //            mySleep(1);
        }
        // this->setWindowOpacity(1);
    }

}



