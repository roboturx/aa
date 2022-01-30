#include "mw_main.h"

MW_main::MW_main( )
{
    setAcceptDrops(true);
    this->setWindowTitle ("Çiftli Kayıt Sistemi ile Muhasebe Kontrol");
    this->setGeometry (20,20,800,500);
    this->setObjectName ("objMW_main");
    cr_Actions ();

}

void MW_main::login()
{

    // at the beginning first mainwindow is showed after login is executed

    // fade(true);

    /// veritabanı kontrol
    qDebug() << "db control";
    dbase = new DBase();
    dbase->setGeometry (800,300,300,480);
    dbase->setWindowTitle("Veri Tabanı Kontrol");
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


//    sbox = new SortingBox;
    //dbox = new DragWidget;


    this->setCentralWidget (dbase );

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

void MW_main::isemri()
{

//    QSqlQuery query("SELECT * FROM ie_dbtb WHERE ie_durum != 'Tamamlandı'");

//    if (query.isActive ())
//    {
//        qDebug()<< "active " ;
//    }
//    else {
//        qDebug()<< "not active "<< query.lastError ().text ();
//    }

//    while (query.next())
//    {

//        QPixmap outPixmap = QPixmap();
//        outPixmap.loadFromData( query.value (9).toByteArray () );

//        createNewSquar (squarePath,
//                        tr("Excavator < %1 >").arg(++count),
//                        randomItemPosition(),
//                        randomItemColor(),
//                        QString::number (count)+"---"+query.value(2).toString(),
//                        QPixmap( outPixmap ));

//    }
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
    QToolBar *tb_main = addToolBar("İşlemler");
    this->addToolBar(Qt::LeftToolBarArea, tb_main );
    //tb_main->setMaximumHeight (50);
   // tb_main->setMaximumWidth (650);
    tb_main->setMinimumWidth (450);
    tb_main->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb_main->setAllowedAreas(Qt::LeftToolBarArea );

    //////// G İ R İ Ş

    auto *act_main = new QAction(QIcon(":/rsm/home.png"),
                                 tr("&Kontrol Merkezi..."), this);
    act_main->setStatusTip("Ana Pencere" );
    act_main->setWhatsThis("Program Giriş Sayfas1");
    act_main->setShortcut(QKeySequence(tr("Ctrl+K")));
    act_main->setShortcutContext(Qt::ApplicationShortcut);
    act_main->setStatusTip(tr("Ana Ekran"));
    mn_main->addAction(act_main);
    tb_main->addAction(act_main);
    connect( act_main , &QAction::triggered,
             [this]()
    {
        // mwgr = new MW_graph;
        statusBar()->showMessage( "Kontrol Merkezi" );
        // mwgr->setWindowTitle ( GLB_yetki );
        // mwgr->adjustSize ();

        //delete sbox;

        //sbox = new SortingBox;

        this->setCentralWidget (dbase );

    });



    menuBar()->addSeparator();
    tb_main->addSeparator ();

    /////////////////////////////////////////////adres/
    /////// ADRES
///
/// Şahıs
/// Firma
///

    QMenu *mn_adres = menuBar()->addMenu(tr("&Adres"));



    /// personel
    auto *act_per = new QAction(QIcon(":/rsm/worker.jpeg"),
                                tr("&Şahıs ..."), this);
    act_per->setShortcut(QKeySequence(tr("Ctrl+Ş")));
    act_per->setStatusTip(tr("Şahıs Adres Bilgileri"));
    mn_adres->addAction(act_per);
     tb_main->addAction(act_per);
    connect( act_per , &QAction::triggered,
             [this]()
    {
        mw_per = new hC_CLSN ;
        mw_per->tbsetup ();
        //statusBar()->showMessage(tr("Çalışan Bilgileri"));
        //mw_per->setWindowTitle ("ÇALIŞAN");
        //mw_per->resize(qApp->screens()[0]->size()*.8);
       // mw_per->show ();
        this->setCentralWidget (mw_per );
    });

    /// firma
    auto *act_fr = new QAction(QIcon(""),
                               tr("&Firma..."), this);
    act_fr->setShortcut(QKeySequence(tr("Ctrl+f")));
    act_fr->setStatusTip(tr("Firma Bilgileri"));
    mn_adres->addAction(act_fr);
    tb_main->addAction(act_fr);
    connect( act_fr , &QAction::triggered,
             [this]()
    {
        mw_fr = new hC_FRM;
        mw_fr->tbsetup ();
        statusBar()->showMessage(tr("Firma Bilgileri"));
        this->setCentralWidget (mw_fr );
        //mw_fr->show ();
    });

/////////////////////////////////////////////adres/












    QMenu *mn_mkn = mn_adres->addMenu(tr("&Makina"));
    /// mkn
    auto *act_mkn = new QAction(QIcon(":/rsm/ex.png"),
                                tr("&Makina..."), this);
    act_mkn->setStatusTip(tr("Demirbaş Mlzm"));
    //act_mkc->setShortcut(QKeycequence(tr("Ctrl+M")));
    mn_mkn->addAction(act_mkn);
    tb_main->addAction(act_mkn);

    connect( act_mkn , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Demirbaş Mlzm"));
        auto *mw_mkn = new hC_MKN;
        mw_mkn->tbsetup ();
        this->setCentralWidget (mw_mkn );
       // mw_mkn->show ();

    });

    /// mkn cmm
    /*    auto *act_mkc = new QAction(QIcon(":/rsm/ex.png"),
                                tr("&Makina &Cinsi..."), this);
    act_mkc->setStatusTip(tr("Makina Cinsi"));
    act_mkc->setShortcut(QKeySequence(tr("Ctrl+C")));
    mn_mkn->addAction(act_mkc);
    //tb_main->addAction(act_mkn);
    connect( act_mkc , &QAction::triggered,
             []()
    {
        auto *dia = new QDialog();
        dia->setModal (true);
        dia->setGeometry ( 50, //lE_cins->pushButton->pos ().rx (),
                          400, //lE_cins->pushButton->pos ().ry (),
                          900,200);
        dia->setWindowTitle ("Cinsi - Marka ve Modeli ");

        auto *c = new hC_MKCINS ;
        c->mkcins_setup ();
        auto *cm = new hC_MKMARK ;
        cm->mkmark_setup ();
        auto *cmm = new hC_MKMODL ;
        cmm->mkmodl_setup ();

        auto *layout = new QGridLayout;
        dia->setLayout (layout);
        layout->addWidget (c  ,0 ,0 );
        layout->addWidget (cm ,0 ,1 );
        layout->addWidget (cmm,0 ,2 );

        dia->exec ();

    });
      */
    /*    /// iş emri
    auto *act_ie = new QAction(QIcon(":/rsm/worker.jpeg"),
                                tr("İş &Emri..."), this);
    act_ie->setShortcut(QKeySequence(tr("Ctrl+E")));
    act_ie->setStatusTip(tr("İş Emri"));
    mn_adres->addAction(act_ie);
    connect( act_ie , &QAction::triggered,
             [this]()
    {
        MW_main::mw_ie = new hC_IE;
        MW_main::mw_ie->ie_setup ();
        MW_main::mw_ie->show ();
    });

*/
    /// iş emri detay
    auto *act_iedet = new QAction(QIcon(":/rsm/worker.jpeg"),
                                  tr("&İş Emri"), this);
    act_iedet->setShortcut(QKeySequence(tr("Ctrl+P")));
    act_iedet->setStatusTip(tr("İş Emri Detay"));
    mn_adres->addAction(act_iedet);

    tb_main->addAction (act_iedet);
    tb_main->addAction(act_iedet);
    connect( act_iedet , &QAction::triggered,
             [this]()
    {
        mw_iedet = new hC_IEDET ;
        mw_iedet->tbsetup ();
        mw_iedet->show ();

    });/// iş emri detay

/*    /// Çıkış
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
  */








    //// Taşınır istek
    auto *act_tsnr = new QAction(QIcon(":/rsm/worker.jpeg"),
                                 tr("&Taşınır İsatek"), this);
    act_tsnr->setShortcut(QKeySequence(tr("Ctrl+T")));
    act_tsnr->setStatusTip(tr(""));
    mn_adres->addAction(act_tsnr);
    connect( act_tsnr , &QAction::triggered,
             [this]()
    {
        mw_tsnr = new hC_TSNR ;
        mw_tsnr->tbsetup ();
        mw_tsnr->show ();
    });/// taşınır istek

    //// işçilik
    auto *act_sclk = new QAction(QIcon(":/rsm/worker.jpeg"),
                                 tr("İşçi&lik"), this);
    act_sclk->setShortcut(QKeySequence(tr("Ctrl+L")));
    act_sclk->setStatusTip(tr("İşçilik"));
    mn_adres->addAction(act_sclk);
    connect( act_sclk , &QAction::triggered,
             [this]()
    {
        mw_sclk = new hC_SCLK ;
        mw_sclk->tbsetup();
        mw_sclk->show ();
    }); // işçilik



    QMenu *mn_mbar  = menuBar()->addMenu(tr("&Ambar"));
    /// dpo    Mlzm kontrol
    auto *act_dpo = new QAction(QIcon(":/rsm/plt.png"),
                                tr("&Mlzm..."), this);
    act_dpo->setShortcut(QKeySequence(tr("Ctrl+S")));
    act_dpo->setShortcutContext(Qt::ApplicationShortcut);
    act_dpo->setStatusTip(tr("Mlzm Kontrol "));
    mn_mbar->addAction(act_dpo);
     tb_main->addAction(act_dpo);
    connect( act_dpo , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Mlzm "));
        mw_mlzmGc = new hC_MLZMGC;
        mw_mlzmGc->tbsetup ();
        mw_mlzmGc->show ();
    });


    QMenu *mn_stnlm = menuBar()->addMenu(tr("&Satın Alma"));


    /// fatura
    auto *act_ftr = new QAction(QIcon(""),
                                tr("&Fatura..."), this);
    act_ftr->setShortcut(QKeySequence(tr("Ctrl+t")));
    act_ftr->setStatusTip(tr("Fatura"));
    mn_stnlm->addAction(act_ftr);
     tb_main->addAction(act_ftr);
    connect( act_ftr , &QAction::triggered,
             [this]()
    {
        statusBar()->showMessage(tr("Mlzm Faturalı Mal Girişi"));
        mw_ftr = new hC_FTR;
        mw_ftr->tbsetup ();
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
     tb_main->addAction(act_hkk);
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
    //    delete mw_mkk;
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



