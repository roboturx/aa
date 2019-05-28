#include "mw_main.h" // main
#include "cw_per.h"  // stack per
#include "cw_fr.h"   // stack fr
#include "cw_mkn.h"  // stack mkn
#include "cw_grs.h"  // stack giris
#include "cw_mlzm.h"// stack Mlzm
#include "cw_hkk.h"  // hakk1nda
#include "login.h"

#include "globals.h"
#include "form.h"
#include "dbase.h"




MW_main::MW_main( )
{

}
void MW_main::login()
{
    cr_Actions ();
    //    this->setWindowFlags(Qt::Window |
    //                         Qt::FramelessWindowHint );

    /// ana ekran
    /////////////////////////////////////////////////////
    // qDebug() << "main log";
    MW_main::showMaximized ();
    wd_log = new QWidget(this);
    this->setCentralWidget (wd_log);

    QGridLayout *lg = new QGridLayout(wd_log);
    wd_log->setLayout(lg);

    durum = new QTextEdit(wd_log);
    durum->setReadOnly (true);

    lg->addWidget(durum  ,1,0,1,6);






    mwyaz(QDate::currentDate ().toString());







    // fade(true);


    /// veritabanı kontrol
    qDebug() << "db control";

    DBase dbase;
    if (! dbase.setupDBase ())
    {
        /// hata ne /// baglanti yok
        mwyaz("----------------------------------------");
        mwyaz("HATA - Veri Tabanı Bağlantısı Yapılamadı");
        return;
    }
    else
    {
        /// baglanti var /// uygulama yoluna devam etsin

        mwyaz("----------------------------------------");
        mwyaz("OK - Veri Tabanı Bağlantısı Yapıldı");
        qDebug() << "OK - Veri Tabanı Bağlantısı Yapıldı";

    }



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

void MW_main::yetkiler(QString yetki, QString user)
{
    //    this->setFocus ();
    qDebug() << "yetkiler ="<<yetki;
    QString x ="++++ Kullanıcı ( "+user +" ) - ( "+ yetki +
            " ) yetkileri ile bağlandı";
    mwyaz(QDateTime::currentDateTime ().toString() + x);

}



void MW_main::logouted()
{
    GLB_yetki = "İlk";
    QString x =" +++ ( "+logger->lE_user->text ()+
            " ) kullanıcısı ile yapılan bağlantı sona erdi...";
    mwyaz(QDateTime::currentDateTime ().toString() + x);
    logger->lE_user->setFocus ();
    logger->lE_user->setText ("");
    logger->lE_pass->setText ("");
    logger->show ();

}





void MW_main::cr_Actions()
{
    /////////////////// ana menü
    qDebug() << "main menu ";
    QMenu *mn_main = menuBar()->addMenu(tr("&Giriş"));

    QToolBar *tb_main = addToolBar(tr("Makina İkmal"));
    tb_main->setMaximumHeight (50);
    tb_main->setMaximumWidth (650);
    tb_main->setMinimumWidth (450);
    tb_main->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb_main->setAllowedAreas(Qt::LeftToolBarArea);


    /// main
    auto *act_main = new QAction(QIcon(":/rsm/home.png"),
                                 tr("&Giriş..."), this);
    act_main->setStatusTip("Ana Pencere" );
    act_main->setWhatsThis("Program Giriş Sayfas1");
    act_main->setShortcut(QKeySequence(tr("Ctrl+G")));
    act_main->setShortcutContext(Qt::ApplicationShortcut);
    act_main->setStatusTip(tr("Ana Ekran"));
    mn_main->addAction(act_main);
    tb_main->addAction(act_main);


    connect( act_main , &QAction::triggered,

             [this]()
    {
        mw_mkk = new Form();
        statusBar()->showMessage( "Giriş" );
        mw_mkk->setWindowTitle ( GLB_yetki );
        mw_mkk->resize(qApp->screens()[0]->size()*.6);
        mw_mkk ->show ();
    });

    /// mkn
    auto *act_mkn = new QAction(QIcon(":/rsm/ex.png"),
                                tr("&Makina..."), this);
    act_mkn->setStatusTip(tr("Demirbaş Mlzm"));
    act_mkn->setShortcut(QKeySequence(tr("Ctrl+M")));
    mn_main->addAction(act_mkn);
    tb_main->addAction(act_mkn);
    connect( act_mkn , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Demirbaş Mlzm"));
        auto *mw_mkn = new Cw_mkn ();
        mw_mkn->setWindowTitle ("MAKİNA");
        mw_mkn ->showMaximized();
    });

    /// personel
    auto *act_per = new QAction(QIcon(":/rsm/worker.jpeg"),
                                tr("&Personel..."), this);
    act_per->setShortcut(QKeySequence(tr("Ctrl+P")));
    act_per->setStatusTip(tr("Personel"));
    mn_main->addAction(act_per);
    tb_main->addAction(act_per);
    connect( act_per , &QAction::triggered,
             [this]()
    {
        mw_per = new Cw_per();
        statusBar()->showMessage(tr("Çalışan Bilgileri"));
        mw_per->setWindowTitle ("ÇALIŞAN");
        mw_per->resize(qApp->screens()[0]->size()*.8);
        mw_per->show ();
    });

    menuBar()->addSeparator();
    tb_main->addSeparator ();

    /// dpo    Mlzm kontrol
    auto *act_dpo = new QAction(QIcon(":/rsm/plt.png"),
                                tr("&Mlzm..."), this);
    act_dpo->setShortcut(QKeySequence(tr("Ctrl+S")));
    act_dpo->setShortcutContext(Qt::ApplicationShortcut);
    act_dpo->setStatusTip(tr("Mlzm Kontrol "));
    mn_main->addAction(act_dpo);
    tb_main->addAction(act_dpo);
    connect( act_dpo , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Mlzm "));
        mwMLZM = new Cw_Mlzm;
        mwMLZM->setup_mlzm ();
        mwMLZM->show ();
    });

    /// firma
    auto *act_fr = new QAction(QIcon(""),
                               tr("&Firma..."), this);
    act_fr->setShortcut(QKeySequence(tr("Ctrl+f")));
    act_fr->setStatusTip(tr("Firma"));
    mn_main->addAction(act_fr);
    tb_main->addAction(act_fr);
    connect( act_fr , &QAction::triggered,
             [this]()
    {
        mw_fr = new Cw_fr;
        statusBar()->showMessage(tr("Firma Bilgileri"));
        mw_fr->setWindowTitle ("FİRMA");
        mw_fr->resize(qApp->screens()[0]->size()*.8);
        mw_fr->show ();
    });

    /// fatura
    auto *act_ftr = new QAction(QIcon(""),
                                tr("&Fatura..."), this);
    act_ftr->setShortcut(QKeySequence(tr("Ctrl+t")));
    act_ftr->setStatusTip(tr("Fatura"));
    mn_main->addAction(act_ftr);
    tb_main->addAction(act_ftr);
    connect( act_ftr , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Mlzm Faturalı Mal Girişi"));
        mw_ftr = new Cw_ftr;
        mw_ftr->setup_fatura ();
        mw_ftr->show ();
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

    if (ne == false)
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




void MW_main::mwyaz(QString z)
{
    QString x,y;
    x = z.left(z.indexOf("-"));
    y = z.right(z.length() - z.indexOf("-"));
    qDebug()<<"x= "<< x <<"   y= "<<y;
    if (x.contains("OK"))
    {
        durum->append("<span style='color:green;font-size:15px' > "
                      + x +" < /span> "
                           "<span style='color:darkblue;font-size:15px' > "
                      + y +" < /span> ");
    }
    else if  (x.contains("HATA"))
    {
        durum->append("<span style='color:red;font-size:15px' > "
                      + x +" < /span> "
                           "<span style='color:darkblue;font-size:15px' > "
                      + y +" < /span> ");
    }
    else
        durum->append("<span style='color:darkyellow;font-size:15px' > "
                      + x +" < /span> "
                           "<span style='color:darkyellow;font-size:15px' > "
                      + y +" < /span> ");

}

