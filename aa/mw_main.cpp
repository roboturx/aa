#include "mw_main.h" // main
#include "cw_per.h"  // stack per
#include "cw_fr.h"   // stack fr
#include "cw_mkn.h"  // stack mkn
#include "cw_grs.h"  // stack giris
#include "cw_ambar.h"// stack ambar
#include "cw_hkk.h"  // hakk1nda
#include "login.h"

#include "globals.h"
#include "form.h"




MW_main::MW_main( )
{

}

void MW_main::login()
{
    MW_main::showMaximized ();
    //    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint );

    //    setStyleSheet("background:transparent;");
    //  this->setStyleSheet("background-color: rgba(0, 0, 0, 192)");
    //this->setAttribute(Qt::WA_TranslucentBackground);
    /*  QPalette pal = palette();
    pal.setBrush(QPalette::Window, QColor(0, 0, 0, 128) );
    setPalette(pal);*/
    //setAutoFillBackground(true);



    /// ana ekran
    /////////////////////////////////////////////////////
    // qDebug() << "main log";
    wd_log = new QWidget(this);
    this->setCentralWidget (wd_log);
    durum = new QTextEdit;
    durum->setReadOnly (true);
    yaz("---", QDate::currentDate ().toString());

    QGridLayout *lg = new QGridLayout(wd_log);
    lg->addWidget(durum  ,1,0,1,6);



    fade(true);

    /// veritabanı kontrol
    qDebug() << "db control";
    if (! dbcontrol ())
    {
        /// hata ne /// baglanti yok
        yaz("HATA -","Veri Tabanı Bağlantısı Yapılamadı");
return;
    }
    else
    {
        /// baglanti var /// uygulama yoluna devam etsin

        yaz("OK","Veri Tabanı Bağlantısı Yapıldı");
        qDebug() << "Connected ...";

    }

    /// login için esc-enter kullanımı
    /////////////////////////////////////

    // logger= new Login;

    cr_Actions ();

    /*   connect(logger, &Login::logok, this, &MW_main::yetkiler);
    connect(this, &MW_main::cikis, logger, &Login::logex );

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
    QString x =" --- Kullanıcı ( "+user +" ) - ( "+ yetki +" ) yetkileri ile bağlandı";
    yaz(QDateTime::currentDateTime ().toString(),x);

}



void MW_main::logouted()
{
    GLB_yetki = "İlk";
    QString x =" --- ( "+logger->lE_user->text ()+" ) kullanıcısı ile yapılan bağlantı sona erdi...";
    yaz(QDateTime::currentDateTime ().toString(),x);
    logger->lE_user->setFocus ();
    logger->lE_user->setText ("");
    logger->lE_pass->setText ("");
    logger->show ();

}





void MW_main::cr_Actions()
{




    ///
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
    act_main = new QAction(QIcon(":/rsm/home.png"),
                           tr("&Giriş..."), this);
    act_main->setStatusTip("Ana Pencere" );
    act_main->setWhatsThis("Program Giriş Sayfas1");
    act_main->setShortcut(QKeySequence(tr("Ctrl+G")));
    act_main->setShortcutContext(Qt::ApplicationShortcut);
    act_main->setStatusTip(tr("Ana Ekran"));
    mn_main->addAction(act_main);
    tb_main->addAction(act_main);


    connect( act_main , &QAction::triggered,
             this, &MW_main::cw_main );   /// main central

    /// mkn
    QAction *act_mkn = new QAction(QIcon(":/rsm/ex.png"),
                                   tr("&Makina..."), this);
    act_mkn->setStatusTip(tr("Demirbaş Ambar"));
    act_mkn->setShortcut(QKeySequence(tr("Ctrl+M")));
    mn_main->addAction(act_mkn);
    tb_main->addAction(act_mkn);
    connect( act_mkn , &QAction::triggered,
             this, &MW_main::cw_mkn );   /// mkn central

    /// personel
    QAction *act_per = new QAction(QIcon(":/rsm/worker.jpeg"),
                                   tr("&Personel..."), this);
    act_per->setShortcut(QKeySequence(tr("Ctrl+P")));
    act_per->setStatusTip(tr("Personel"));
    mn_main->addAction(act_per);
    tb_main->addAction(act_per);
    connect( act_per , &QAction::triggered,
             this, &MW_main::cw_per );   /// personel central


    menuBar()->addSeparator();
    tb_main->addSeparator ();

    /// dpo    ambar kontrol
    QAction *act_dpo = new QAction(QIcon(":/rsm/plt.png"),
                                   tr("&Ambar..."), this);
    act_dpo->setShortcut(QKeySequence(tr("Ctrl+S")));
    act_dpo->setShortcutContext(Qt::ApplicationShortcut);
    act_dpo->setStatusTip(tr("Ambar Kontrol "));
    mn_main->addAction(act_dpo);
    tb_main->addAction(act_dpo);
    connect( act_dpo , &QAction::triggered,
             this, &MW_main::cw_dpo );   /// stok central





    /// firma
    QAction *act_fr = new QAction(QIcon(""),
                                  tr("&Firma..."), this);
    act_fr->setShortcut(QKeySequence(tr("Ctrl+f")));
    act_fr->setStatusTip(tr("Firma"));
    mn_main->addAction(act_fr);
    tb_main->addAction(act_fr);
    connect( act_fr , &QAction::triggered,
             this, &MW_main::cw_fr );   /// firma central

    /// fatura
    QAction *act_ftr = new QAction(QIcon(""),
                                   tr("&Fatura..."), this);
    act_ftr->setShortcut(QKeySequence(tr("Ctrl+t")));
    act_ftr->setStatusTip(tr("Fatura"));
    mn_main->addAction(act_ftr);
    tb_main->addAction(act_ftr);
    connect( act_ftr , &QAction::triggered,
             this, &MW_main::cw_ftr );   /// firma central



    menuBar()->addSeparator();


    tb_main->addSeparator ();
    /// Çıkış
    QAction *act_Quit = mn_main->addAction(tr("&Çıkış"),
                                           this, &QWidget::close);
    //QAction *act_Quit = new QAction(QIcon(":/rsm/out.ico"),
    //                             tr("&Çıkış..."), this);
    act_Quit->setIcon (QIcon(":/rsm/out.ico"));

    act_Quit->setShortcuts(QKeySequence::Quit);
    act_Quit->setStatusTip(tr("Programdan Çıkış "));
    mn_main->addAction(act_Quit);
    tb_main->addAction(act_Quit);
    connect(act_Quit , &QAction::triggered,
            this, &MW_main::quitApp );


    ///////////////////////
    /// \brief mn_yrdm
    ///
    QMenu *mn_yrdm = menuBar()->addMenu(tr("&Yardım"));


    /// hakkında
    QAction *act_hkk = new QAction(QIcon(":/rsm/worker.jpeg"),
                                   tr("&Uygulama Hakkında"), this);
    act_hkk->setShortcut(QKeySequence(tr("Ctrl+U")));
    act_hkk->setStatusTip(tr("Hakkında"));
    mn_yrdm->addAction(act_hkk);
    //  tb_main->addAction(act_hkk);
    connect( act_hkk , &QAction::triggered,
             this, &MW_main::hkk );   /// personel central




    /////////////////////////////////////


}




void MW_main::cw_main()               // giriş
{
    mw_mkk = new Form();

    statusBar()->showMessage( "Giriş" );

    mw_mkk->setWindowTitle ( GLB_yetki );
    mw_mkk->resize(qApp->screens()[0]->size()*.6);
    mw_mkk ->show ();
}


void MW_main::cw_per()               // Çal1şan
{
    mw_per = new Cw_per();

    statusBar()->showMessage(tr("Çalışan Bilgileri"));
    mw_per->setWindowTitle ("ÇALIŞAN");
    mw_per->resize(qApp->screens()[0]->size()*.8);
    mw_per->show ();
}


void MW_main::cw_fr()               // firma
{
    mw_fr = new Cw_fr();

    statusBar()->showMessage(tr("Firma Bilgileri"));
    mw_fr->setWindowTitle ("FİRMA");
    mw_fr->resize(qApp->screens()[0]->size()*.8);
    mw_fr->show ();
}


void MW_main::cw_ftr()               // fatura
{
    mw_ftr = new Cw_ftr();

    statusBar()->showMessage(tr("Ambar Faturalı Mal Girişi"));
    mw_ftr->setWindowTitle ("FATURA");
    mw_ftr->resize(qApp->screens()[0]->size()*.8);
    mw_ftr->setup_fatura ();
    mw_ftr->show ();
}

void MW_main::quitApp()
{
    emit cikis("Ana Menu act");
}

void MW_main::cw_dpo()   //new stokekle
{
    statusBar()->showMessage(tr("Ambar "));
    Cw_Ambar *mw_ambar = new Cw_Ambar();
    //mw_ambar ->setWindowFlags ( Qt:: Dialog );
    //anbar ->setWindowModality(Qt::WindowModal);
    mw_ambar->setWindowTitle ("AMBAR");
    mw_ambar->resize(qApp->screens()[0]->size()*.8);
    mw_ambar ->show ();

}
void MW_main::cw_mkn()   // makina centralwidget
{
    statusBar()->showMessage(tr("Demirbaş Ambar"));

    Cw_mkn *mw_mkn = new Cw_mkn ();
    //mw_mkn ->setWindowFlags ( Qt:: Dialog );
    //ambar ->setWindowModality(Qt::WindowModal);
    mw_mkn->setWindowTitle ("MAKİNA");
    //    mw_mkn->resize(qApp->screens()[0]->size()*.7);
    mw_mkn ->showMaximized();
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

void MW_main::hkk()
{

    CW_hkk *m_cw_hkk = new CW_hkk;
    m_cw_hkk->show ();
}

void MW_main::closeEvent (QCloseEvent *event)
{
    QMessageBox msgBox;
    QPushButton *bt_evet = msgBox.addButton(tr("&Sonlandır"), QMessageBox::YesRole);
    QPushButton *bt_hyr  = msgBox.addButton(tr("&Vazgeç"), QMessageBox::NoRole);

    msgBox.setWindowTitle ("GİRİŞ KONTROL");
    msgBox.setText(tr("\n    Uygulama sona erdirilsin mi ?    \n"));
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
    //  delete mw_Ambar;
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



////////////////////////////////////////////////////////
/// \brief MW_main::dbcontrol
/// \return
///
///
///
///
///
///
bool MW_main::dbcontrol()
{
    qDebug()<<"WD Login dbcontrol";

    /// veritabanini kontrol et yoksa olustur
    VTKontrolEt::instance()->SetupDB();

    /// veritabanina baglanilabilir mi
    if(VTKontrolEt::instance()->Connect())
    {
        /// baglanti var /// uygulama yoluna devam etsin
        //        emit MW_main::gologin();


        /// bağlandı - olmayan dosyaları oluştur

        MW_main::VTDosyaKontrol ();
        return true;
    }
    else
    {
        /// hata ne /// baglanti yok
        QString x = "Hata 002 - Code::Database NOT Connected !!! \n"+
                VTKontrolEt::instance ()->GetError ()   ;
        yaz("- ? - ",x);


        return false;
    }
}








void MW_main::VTDosyaKontrol()
{

    if (!MW_main::VTd_CLSN ())
        yaz( "HATA - ","Çalışan ");
    else yaz( "OK - ","Çalışan ");

    if (!MW_main::VTd_MSLK ())
        yaz( "HATA - ","Meslekler ");
    else yaz( "OK - ","Meslekler ");

    if (!MW_main::VTd_FRMA ())
        yaz( "HATA - ","Firma ");
    else yaz( "OK - ","Firma ");

    if (!MW_main::VTd_FTRA ())
        yaz( "HATA - ","Fatura ");
    else yaz( "OK - ","Fatura ");

    if (!MW_main::VTd_FTDT ())
        yaz( "HATA - ","Fatura Detay ");
    else yaz( "OK - ","Fatura Detay ");


    MW_main::VTd_mkn ();
    MW_main::VTd_Ambar ();
    MW_main::VTd_AmbarDETAY ();
    MW_main::VTd_CINS ();
    MW_main::VTd_MARKA ();
    MW_main::VTd_MODEL ();
    MW_main::VTd_ISEMRI ();
    MW_main::VTd_ISEMRIDETAY ();
    MW_main::VTd_IEDTAMIRYERI ();
    MW_main::VTd_IEDTYDETAY ();
    MW_main::VTd_ISCILIK ();
    MW_main::VTd_TASINIR () ;
    MW_main::VTd_MKYAG ();
    MW_main::VTd_MKFILTRE ();
    MW_main::VTd_MKAKU ();
    MW_main::VTd_MKLASTIK ();
    MW_main::VTd_MKMUAYENE ();
    MW_main::VTd_MKSIGORTA ();
    MW_main::VTd_MKYAKIT();
    MW_main::VTd_MKANTIFIRIZ();
    MW_main::VTd_MKZINCIR ();
    MW_main::VTd_MKHGS ();


}


bool MW_main::VTd_CLSN ()
{
    QSqlQuery   q;
    QString     ct;
    QStringList inserts;


    //// Veritabanında dosya varmý yoksa oluþtur ve ilk kaydÄ± ekle


    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( "dbtb_clsn"))
    {
        /// calişan create
        ///
        ///
        ///

        ct = "CREATE TABLE IF NOT EXISTS dbtb_clsn"
             "("
             "  kod_pr	    INTEGER PRIMARY KEY  , "
             "  isim		TEXT ,"
             "  soyad	    TEXT ,"
             "  tckimlik    TEXT ,"
             "  dogumyeri   TEXT ,"
             "  dogumtarihi DATE ,"
             "  babaadi     TEXT ,"
             "  bolum	    TEXT ,"
             "  meslek      int ,"
             "  gorev	    TEXT ,"
             "  adres		TEXT ,"
             "  sehir       TEXT ,"
             "  tel_cep	    TEXT ,"
             "  tel_ev	    TEXT ,"
             "  eposta      TEXT ,"
             "  username	TEXT ,"
             "  password	TEXT ,"
             "  yetki		TEXT ,"
             "  resim       BLOB  )" ;

        if (!q.exec( ct ))
        {
            qDebug() << "Çalışan Dosyası Oluşturulamadı - "
                     << q.lastError() ;
            return false;
        }
        else
        {
            yaz("+++", "Çalışan Dosyası YENİ Oluşturuldu - ");
            inserts << "INSERT INTO dbtb_clsn "
                       "( "
                       "isim, soyad, "
                       "bolum, meslek, gorev, "
                       "adres, sehir, "
                       "tel_cep, tel_ev, eposta,"
                       " username, password, yetki"
                       ") "
                       "VALUES "
                       "("
                       "'-', '-', "
                       "'', '', '', "
                       "'', '', "
                       "'', '', '', "
                       "'','', ''"
                       " )"
                    << "INSERT INTO dbtb_clsn "
                       "( "
                       "isim, soyad, "
                       "bolum, meslek, gorev, "
                       "adres, sehir, "
                       "tel_cep, tel_ev, eposta,"
                       " username, password, yetki"
                       ") "
                       "VALUES "
                       "("
                       "'Murat', 'BALCI', "
                       "'bilgi işlem', 'CASE', 'Developer', "
                       "'KSS', 'Tokat', "
                       "'505 320 22 40', '356 232 91 01', 'roboturx@gmail.com', "
                       "'a','a', 'a'"
                       " )" ;


            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {

                    durum->append(QString(" HATA - İlk ÇALIŞAN Eklenemedi - "
                                          + q.lastError().text ()));
                    qDebug()  << " HATA - ÇALIŞAN Eklenemedi - "
                              << q.lastError() ;
                    return false;
                }
                else{
                    yaz("+++", " İlk ÇALIŞAN Eklendi - ");
                    qDebug()  << "ÇALIŞAN Eklendi - ";

                }
            } // foreach


        }
    }
    return true;


}


///
/// \brief MW_main::VTd_MSLK
/// \return
///
///
///
///
bool MW_main::VTd_MSLK ()
{
    /// meslekler dosyası
    ///
    ///
    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( "dbtb_mslk"))
    {
        QSqlQuery query;
        if (! query.exec("create table if not exists "
                         "dbtb_mslk (id int, meslek TEXT)"))
        {
            durum->append (QString("MESLEK Dosyası Oluşturulamadı - "
                                   + query.lastError().text ()));
            qDebug() << "MESLEK Dosyası Oluşturulamadı - "
                     << query.lastError() ;
            return false;
        }
        else
        {
            yaz("+++", "MESLEK Dosyası YENİ Oluşturuldu - ");
            qDebug() << "MESLEK Çalışan Dosyası YENİ Oluşturuldu - ";
            if ( !query.exec("insert into dbtb_mslk values(101, 'Makina Mühendisi')"))
            {
                durum->append (QString("MESLEK Dosyasına İLK kayıt eklenemedi "
                                       + query.lastError().text() ));
                qDebug() << "MESLEK Dosyasına İLK kayıt eklenemedi "
                         << query.lastError() ;

                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return true;
}



bool MW_main::VTd_FRMA ()
{
    QSqlQuery   q;
    QString     ct;
    QStringList inserts;


    //// Veritabanında dosya varmý yoksa oluþtur ve ilk kaydÄ± ekle


    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( "frm__dbtb"))
    {
        /// calişan create
        ///
        ///
        ///

        ct = "CREATE TABLE IF NOT EXISTS frm__dbtb"
             "("
             "  frm_kod    INTEGER PRIMARY KEY  , "
             "  frm_unvan	TEXT ,"
             "  frm_adres	TEXT ,"
             "  frm_sehir    TEXT ,"
             "  frm_vd       TEXT ,"
             "  frm_vdno     TEXT ,"
             "  frm_tel 	    TEXT ,"
             "  frm_eposta   TEXT ,"
             "  frm_yisim	TEXT ,"
             "  frm_ysoyad	TEXT ,"
             "  frm_ytel 	TEXT ,"
             "  frm_resim    BLOB  )" ;

        if (!q.exec( ct ))
        {
            qDebug() << "FİRMA Dosyası Oluşturulamadı - "
                     << q.lastError() ;
            return false;
        }
        else
        {
            yaz("+++", "FİRMA Dosyası YENİ Oluşturuldu - ");
            inserts << "INSERT INTO frm__dbtb "
                       "( "
                       "frm_unvan , frm_adres, frm_sehir , "
                       "frm_vd    , frm_vdno , frm_tel   , "
                       "frm_eposta, frm_yisim, frm_ysoyad, "
                       "frm_ytel  , frm_resim  "
                       ") "
                       "VALUES "
                       "("
                       "'-', '-', ' ', "
                       "' ', ' ', ' ', "
                       "' ', ' ', ' ', "
                       "' ', ' ' "
                       " )" ;


            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {

                    durum->append(QString(" HATA - FİRMA Eklenemedi - "
                                          + q.lastError().text ()));
                    qDebug()  << " HATA - FİRMA Eklenemedi - "
                              << q.lastError() ;
                    return false;
                }
                else{
                    durum->append("FİRMA Eklendi - ");
                    qDebug()  << "FIRMA Eklendi - ";

                }
            } // foreach
        }
    }
    return true;
}    ///FİRMA



bool MW_main::VTd_FTRA ()
{
    QSqlQuery   q;
    QString     ct;
    QStringList inserts;


    //// Veritabanında dosya varmý yoksa oluþtur ve ilk kaydÄ± ekle


    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( "ftr__dbtb"))
    {
        /// calişan create
        ///
        ///
        ///

        ct = "CREATE TABLE IF NOT EXISTS ftr__dbtb"
             "("
             "  ftr_kod    INTEGER PRIMARY KEY  , "
             "  ftr_no  	TEXT ,"
             "  ftr_firma	TEXT ,"
             "  ftr_tarih	TEXT ,"
             "  ftr_resim    BLOB  )" ;

        if (!q.exec( ct ))
        {
            qDebug() << "FATURA Dosyası Oluşturulamadı - "
                     << q.lastError() ;
            return false;
        }
        else
        {
            yaz("+++", "FATURA Dosyası YENİ Oluşturuldu - ");
            inserts << "INSERT INTO ftr__dbtb "
                       "( "
                       "ftr_no , ftr_firma "
                       ") "
                       "VALUES "
                       "("
                       "'-', '-' "
                       " )" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {

                    durum->append(QString(" HATA - FATURA Eklenemedi - "
                                          + q.lastError().text ()));
                    qDebug()  << " HATA - FATURA Eklenemedi - "
                              << q.lastError() ;
                    return false;
                }
                else{
                    durum->append("FATURA Eklendi - ");
                    qDebug()  << "FATURA Eklendi - ";

                }
            } // foreach
        }
    }
    else
    {
        mdlFtr = new QSqlRelationalTableModel;
        mdlFtr = modelFatura();

        durum->append("FATURA dosyası var        ------------- - ");
    }
    return true;
}

QSqlRelationalTableModel* MW_main::modelFatura()
{

    QString *tableName  = new QString("ftr__dbtb");
    QString *indexField = new QString("ftr_tarih");

    QStringList *fieldList = new QStringList;
    fieldList->append("Fatura Kod");
    fieldList->append("Fatura No");
    fieldList->append("Firma Unvanı");
    fieldList->append("Fatura Tarihi");
    fieldList->append("Resim");


    QSqlRelationalTableModel *FTRmodel = new QSqlRelationalTableModel;
    FTRmodel->setTable( *tableName);
    qDebug() << "  tablename " << *tableName <<"  indexfield "<< *indexField ;
    FTRmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    FTRmodel->setSort(FTRmodel->fieldIndex (*indexField),Qt::AscendingOrder );

    qDebug() << " view column count = i "<< FTRmodel->columnCount();
    for(int i = 0, j = 0; i < fieldList->size (); i++, j++)
    {

        qDebug() << "  header data i önce = "<< i << "," <<
                    FTRmodel->headerData (i,Qt::Horizontal);

        FTRmodel->setHeaderData(i,Qt::Horizontal,fieldList->value (j));

        qDebug() << "  header data i = "<< i << "," <<
                    FTRmodel->headerData (i,Qt::Horizontal);
        qDebug() << "  setup_modelFtr i,j = "<< i << "," << j;
        qDebug() << "  field list j "<< fieldList->value (j);
    }

    // Populate the model_mkstok
    if (!FTRmodel->select())
    {
        qDebug () <<  " HATA - Model fatura select "
                   <<FTRmodel->lastError();

    }
    return FTRmodel ;
}///FATURA











bool MW_main::VTd_FTDT ()
{
    QSqlQuery   q;
    QString     ct;
    QStringList inserts;


    //// Veritabanında dosya varmý yoksa oluþtur ve ilk kaydÄ± ekle


    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( "ftd__dbtb"))
    {
        /// calişan create
        ///
        ///
        ///

        ct = "CREATE TABLE IF NOT EXISTS ftd__dbtb"
             "("
             "  ftd_kod    INTEGER PRIMARY KEY  , "
             "  ftd_ftno  	TEXT ,"
             "  ftd_malzeme	TEXT ,"
             "  ftd_aciklama TEXT ,"
             "  ftd_grs_cks	TEXT ,"
             "  ftd_miktar	TEXT ,"
             "  ftd_birim	TEXT ,"
             "  ftd_brfiyat	TEXT ,"
             "  ftd_kdv     TEXT ,"
             "  ftd_resim    BLOB  )" ;

        if (!q.exec( ct ))
        {
            qDebug() << "FATURA DETAY Dosyası Oluşturulamadı - "
                     << q.lastError() ;
            return false;
        }
        else
        {
            yaz("+++", "FATURA DETAY Dosyası YENİ Oluşturuldu - ");
            inserts << "INSERT INTO ftd__dbtb "
                       "( "
                       "ftd_ftno , ftd_malzeme, ftd_miktar,  "
                       "ftd_birim, ftd_brfiyat, ftd_kdv"
                       ") "
                       "VALUES "
                       "("
                       "'-', '-', '', '', '', '' "
                       " )" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {

                    durum->append(QString(" HATA - FATURA DETAY Eklenemedi - "
                                          + q.lastError().text ()));
                    qDebug()  << " HATA - FATURA DETAY Eklenemedi - "
                              << q.lastError() ;
                    return false;
                }
                else{
                    durum->append("FATURA DETAY Eklendi - ");
                    qDebug()  << "FATURA DETAY Eklendi - ";

                }
            } // foreach
        }
    }
    return true;
}///FATURA DETAY











////////////////////////////////////////// DBASE

void MW_main::VTd_mkn()
{

    /// MKSTOK create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkn"))
    {
        //mkn_kurumNo key used every table's relation

        ct =  "CREATE TABLE IF NOT EXISTS dbtb_mkn "
              "("
              "id_mkn integer primary key, "
              "mkn_kurumno        TEXT, "
              "mkn_plaka         TEXT, "
              "mkn_cinsi         integer, "
              "mkn_Marka         integer,"
              "mkn_modeli        integer,"
              "mkn_Yil           INTEGER, "
              "mkn_Saseno        TEXT, "
              "mkn_Motorno       TEXT, "
              "mkn_Motortip      TEXT, "
              "mkn_yakit         TEXT, "
              "mkn_surucu        integer, "
              "mkn_surucutar     DATE, "
              "mkn_Birim         TEXT, "
              "mkn_aciklama      TEXT, "
              "mkn_Byer          TEXT, "
              "mkn_resim         BLOB, "
              "mkn_rating        INTEGER)" ;

        if (!q.exec( ct ))
        {
            qDebug() << "DEMİRBAŞ AMBAR Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "DEMİRBAŞ AMBAR Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkn ( mkn_kurumNo,mkn_cinsi,"
                   "mkn_marka, mkn_modeli, mkn_surucu )"
                   " values( '100001', 1 , 1 , 1 , 1 )"  );

        }
    }
    else
    {
        qDebug() << "1- DEMİRBAŞ AMBAR Dosyası - OK ";
    }
}       /// VTdMKSTOK

void MW_main::VTd_ISEMRI ()
{
    ///  ISEMRI create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_IE"))
    {
        /// mkstok_no joins ambar with işemri
        /// db_mkn <- dbtb_IE
        ///
        /// ie_no = mknstk_n0 + id_IE
        ///
        /// ie_no used iedetay relation

        ct ="CREATE TABLE IF NOT EXISTS dbtb_IE "
            "("
            "ie_mkn_id        TEXT, "
            "ie_ie_no         TEXT, "
            "ie_tarih         TEXT, "
            "ie_bolum         TEXT, "
            "ie_durum         TEXT, "
            "ie_girtar        TEXT, "
            "ie_ciktar        TEXT, "
            "ie_yetkili1      TEXT, "
            "ie_yetkili2      TEXT, "
            "ie_resim         BLOB, "
            "id_IE integer primary key  )"  ;



        if (!q.exec( ct ))
        {
            qDebug() << " ISEMRI Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " ISEMRI Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_IE ( ie_mkn_id )"
                   " values( 1 )"  );

        }
    }
    else
    {
        qDebug() << "2- İŞ EMRİ Dosyası - OK ";
    }

}


void MW_main::VTd_ISEMRIDETAY ()
{
    ///  ISEMRI DETAY create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_IEdet"))
    {

        /// ie_no joins işemri with işemridetay
        /// dbtb_IE <- dbtb_IEdet
        ///
        /// iedet_no = ie_no + iedet_no
        ///
        /// iedet_no used tasinir and iscilik relation



        ct = "CREATE TABLE IF NOT EXISTS dbtb_IEdet "
             "("
             "iedet_ie_id	    TEXT, "
             "iedet_iedet_no	TEXT, "
             "iedet_aciklama	TEXT, "
             "iedet_tamiryeri	TEXT, "
             "ie_kurumicdis    TEXT, "
             "iedet_durum     TEXT, "
             "iedet_girtar    TEXT, "
             "iedet_ciktar    TEXT, "
             "iedet_resim     BLOB, "
             "id_IEdet integer primary key  )"  ;


        if (!q.exec( ct ))
        {
            qDebug() << " ISEMRI DETAY Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " ISEMRI DETAY Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_IEdet ( iedet_ie_id )"
                   " values( 1 )"  );
        }
    }
    else
    {
        qDebug() << "3- İŞ EMRİ DETAY Dosyası - OK ";
    }

}



void MW_main::VTd_IEDTAMIRYERI ()
{
    ///  ISEMRI DETAY TAMIRYERI create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().
         tables().contains( "dbtb_IEdtamiryeri"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_IEdtamiryeri "
             "("
             "tamiryeri	TEXT, "
             "aciklama	TEXT, "
             "resim     BLOB, "
             "id_IEdtamiryeri integer primary key  )"  ;


        if (!q.exec( ct ))
        {
            qDebug() << " ISEMRI DETAY TAMİRYERİ Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " ISEMRI DETAY TAMİRYERİ Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_IEdtamiryeri ( tamiryeri )"
                   " values( 'Atölye' )"  );
            q.exec("INSERT INTO dbtb_IEdtamiryeri ( tamiryeri )"
                   " values( 'Arazi' )"  );
            q.exec("INSERT INTO dbtb_IEdtamiryeri ( tamiryeri )"
                   " values( 'Serbest Piyasa' )"  );
            q.exec("INSERT INTO dbtb_IEdtamiryeri ( tamiryeri )"
                   " values( 'Yetkili Servis' )"  );
        }
    }
    else
    {
        qDebug() << "4- İŞ EMRİ DETAY TAMİRYERİ Dosyası - OK ";
    }


}



void MW_main::VTd_IEDTYDETAY ()
{
    ///  ISEMRI DETAY TAMIRYERI DETAY create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().
         tables().contains( "dbtb_IEdtydetay"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_IEdtydetay "
             "("
             "tamiryeri	TEXT, "
             "sorumlu	TEXT, "
             "aciklama	TEXT, "
             "resim     BLOB, "
             "id_IEdtydetay integer primary key  )"  ;


        if (!q.exec( ct ))
        {
            qDebug() << " ISEMRI DETAY TAMİRYERİ DETAY Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " ISEMRI DETAY TAMİRYERİ DETAY Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_IEdtydetay ( tamiryeri )"
                   " values( 'Motorhane' )"  );
            q.exec("INSERT INTO dbtb_IEdtydetay ( tamiryeri )"
                   " values( 'Elektrikhane' )"  );
            q.exec("INSERT INTO dbtb_IEdtyydetay ( tamiryeri )"
                   " values( 'Ağır Şase' )"  );
            q.exec("INSERT INTO dbtb_IEdtyydetay ( tamiryeri )"
                   " values( 'Hafif Şase' )"  );
            q.exec("INSERT INTO dbtb_IEdtyydetay ( tamiryeri )"
                   " values( 'Tornahane' )"  );
            q.exec("INSERT INTO dbtb_IEdtyydetay ( tamiryeri )"
                   " values( 'Boyahane' )"  );
            q.exec("INSERT INTO dbtb_IEdtyydetay ( tamiryeri )"
                   " values( 'Kaynakhane' )"  );

        }
    }
    else
    {
        qDebug() << "5- İŞEMRİ DETAY TAMİRYERİ DETAY Dosyası - OK ";
    }


}




void MW_main::VTd_ISCILIK ()
{
    ///  ISCILIK create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_iscilik"))
    {
        ct ="CREATE TABLE IF NOT EXISTS dbtb_iscilik "
            "("
            "sc_iedet_id   INTEGER, "
            "sc_no         TEXT, "
            "sc_tarih      TEXT, "
            "sc_Birim      TEXT, "
            "sc_usta       TEXT, "
            "sc_saat       TEXT, "
            "sc_ucret      TEXT, "
            "sc_ucrettip   TEXT,"
            "sc_aciklama   TEXT,"
            "sc_resim         BLOB, "
            "id_sc integer primary key  )"  ;



        if (!q.exec( ct ))
        {
            qDebug() << " ISCİLİK Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " İSÇİLİK Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_iscilik ( mknstk_no,iedet_no,is_no )"
                   " values( 1,1,1 )"  );

        }
    }
    else
    {
        qDebug() << "6- İŞÇİLİK Dosyası - OK ";
    }


} //ISCILIK



void MW_main::VTd_TASINIR ()
{
    ///  TASINIR create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_tasinir"))
    {
        ct ="CREATE TABLE IF NOT EXISTS dbtb_tasinir "
            "("
            "ts_iedet_id   TEXT, "
            "ts_no   TEXT, "
            "ts_tarih      TEXT, "
            "ts_malzeme    INTEGER, "
            "ts_miktar       TEXT, "
            "ts_Birim       TEXT, "
            "ts_bfiyat     TEXT, "
            "ts_durum      TEXT, "
            "ts_aciklama   TEXT, "
            "ts_resim      BLOB, "
            "id_tasinir integer primary key  )"  ;



        if (!q.exec( ct ))
        {
            qDebug() << " TAŞINIR Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " TAŞINIR Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_tasinir ( ts_iedet_id )"
                   " values( 1 )"  );

        }
    }
    else
    {
        qDebug() << "9- TAŞINIR Dosyası - OK ";
    }


} //TAŞINIR


void MW_main::VTd_MKYAG ()
{
    ///  MKYAG create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkyag"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkyag "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT, "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_yag integer primary key) "  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKYAG Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKYAG Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkyag ( mknstk_no )"
                   " values( 1 )"  );
        }
    }

}
void MW_main::VTd_MKFILTRE ()
{
    ///  MKFILTRE create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkfiltre"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkfiltre "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT, "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_filtre integer primary key )"  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKFILTRE Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKFILTRE Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkfiltre ( mknstk_no )"
                   " values( 1 )"  );
        }
    }

}
void MW_main::VTd_MKAKU ()
{
    ///  MKAKU create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkaku"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkaku "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT, "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_aku integer primary key) "  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKAKU Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKAKU Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkaku ( mknstk_no )"
                   " values( 1 )"  );
        }
    }

}
void MW_main::VTd_MKLASTIK ()
{
    ///  create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mklastik"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mklastik "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT, "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_lastik integer primary key) "  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKLASTIK Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKLASTIK Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mklastik ( mknstk_no )"
                   " values( 1 )"  );
        }
    }

}

void MW_main::VTd_MKMUAYENE()
{
    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkmuayene"))
    {
        ct =  "CREATE TABLE IF NOT EXISTS dbtb_mkmuayene "
              "("
              "mknstk_no     INTEGER, "
              "tarih         DATE, "
              "aciklama      TEXT, "
              "miktar     	INTEGER, "
              "resim         BLOB, "
              "id_muayene integer primary key) "  ;

        if (!q.exec( ct ))
        {
            qDebug() << " MKMUAYENE Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKMUAYENE Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkmuayene ( mknstk_no )"
                   " values( 1 )"  );
        }
    }




}       /// VTd_MKMUAYENE







void MW_main::VTd_MKSIGORTA()
{

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mksigorta"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mksigorta "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT, "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_sigorta integer primary key) "  ;

        if (!q.exec( ct ))
        {
            qDebug() << " MKSIGORTA Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKSIGORTA Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mksigorta ( mknstk_no )"
                   " values( 1 )"  );
        }
    }
}       /// VTd_MKSIGORTA



void MW_main::VTd_MKYAKIT()
{
    ///  create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkyakit"))
    {
        ct =  "CREATE TABLE IF NOT EXISTS dbtb_mkyakit "
              "("
              "mknstk_no     INTEGER, "
              "tarih         TEXT, "
              "aciklama      TEXT, "
              "miktar     	INTEGER, "
              "resim         BLOB, "
              "id_yakit integer primary key) "  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKYAKIT Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKYAKIT Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkyakit ( mknstk_no )"
                   " values( 1 )"  );
        }
    }

}
void MW_main::VTd_MKANTIFIRIZ()
{
    ///  create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkantifiriz"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkantifiriz "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT, "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_antifiriz integer primary key) "  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKANTIFIRIZ Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKANTIFIRIZ Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkantifiriz ( mknstk_no )"
                   " values( 1 )"  );
        }
    }

}
void MW_main::VTd_MKZINCIR ()
{
    ///  create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkzincir"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkzincir "
             "("
             "mknstk_no     INTEGER, "
             "tarih         TEXT,  "
             "aciklama      TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_zincir integer primary key) "  ;



        if (!q.exec( ct ))
        {
            qDebug() << " MKZINCIR Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKZINCIR Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkzincir ( mknstk_no )"
                   " values( 1 )"  );

        }
    }

}
void MW_main::VTd_MKHGS ()
{  ///  create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkhgs"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkhgs "
             "("
             "mknstk_no     INTEGER, "
             "hgs_kgs       TEXT, "
             "tarih         TEXT, "
             "miktar     	INTEGER, "
             "resim         BLOB, "
             "id_hgs integer primary key) "  ;


        if (!q.exec( ct ))
        {
            qDebug() << " MKHGS Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " MKHGS Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_mkhgs ( mknstk_no )"
                   " values( 1 )"  );

        }
    }
}



/*
void MW_main::VTd_DPTLP()
{
    /// depo talep create
    /// tasinir istek

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_dptlp"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_dptlp "
             "("
             "id_dp integer primary key, "
             "barkod	TEXT, "
             "malzeme TEXT,"
             "aciklama TEXT,"
             "marka	TEXT, "
             "model	TEXT, "
             "cins	TEXT,"
             "birim	TEXT,"
             "giris	REAL, "
             "cikis	REAL, "
             "mevcut REAL,"
             "makina TEXT,"
             "resim	BLOB) "    ;

        if (!q.exec( ct ))
        {
            qDebug() << "DEPO TALEP Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "DEPO TALEP Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_dptlp ( barkod,malzeme )"
                   " values( '','' )"  );

        }
    }
}

*/


///************************************************************
///****************            D  E  P  O          ************
///*******                   D  B  A  S  E         ************
///
///









/// DBASE ///




//////////////////////////////////////
///
/// DEPO
///
/// veritabanı


void MW_main::VTd_Ambar()
{
    /// depo create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "mlzm__dbtb"))
    {
        ct = "CREATE TABLE IF NOT EXISTS mlzm__dbtb "
             "("
             "mlzm_kod integer primary key, "
             "mlzm_barkod	TEXT, "
             "mlzm_malzeme  TEXT,"
             "mlzm_aciklama TEXT,"
             "mlzm_marka	TEXT, "
             "mlzm_model	TEXT, "
             "mlzm_cins	    TEXT,"
             "mlzm_birim	TEXT,"
             "mlzm_giris	TEXT, "
             "mlzm_cikis	TEXT, "
             "mlzm_mevcut   TEXT,"
             "mlzm_makina   TEXT,"
             "mlzm_resim	BLOB) "    ;

        if (!q.exec( ct ))
        {
            qDebug() << "DEPO Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "DEPO Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_Ambar ( barkod,malzeme )"
                   " values( '-','-' )"  );

        }
    }
}

/////DEPO DETAY
///
///
void MW_main::VTd_AmbarDETAY()
{
    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "ambardet__dbtb"))
    {
        ct = "CREATE TABLE IF NOT EXISTS mlzmDet__dbtb "
             "("
             "mlzmDet_kod integer primary key, "
             "mlzmDet_mlzm_kod	INTEGER, "
             "mlzmDet_barkod	TEXT , "
             "mlzmDet_malzeme	TEXT , "
             "mlzmDet_tarih	    TEXT , "
             "mlzmDet_gc        TEXT , "
             "mlzmDet_gcno      TEXT , "
             "mlzmDet_miktar    TEXT , "
             "mlzmDet_birim     TEXT , "
             "mlzmDet_fiyat     TEXT , "
             "mlzmDet_kdv       TEXT , "
             "mlzmDet_aciklama  TEXT   "
             ")";

        if (!q.exec( ct ))
        {
            qDebug() << "MALZEME - DETAY Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "MALZEME - DETAY Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO mlzmdet__dbtb ( mlzmdet_mlzm_kod )"
                   " values( 1 )"  );

        }
    }
    qDebug() << "DEPO-DETAY Dosyası OK - "
             << q.lastError() ;
}

///// CINS
///
///
void MW_main::VTd_CINS()
{
    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkcins"))
    {
        ct = "CREATE TABLE dbtb_mkcins "
             "("
             "cinsi TEXT, "
             "id_mkcins INTEGER PRIMARY key "
             ") " ;


        if (!q.exec( ct ))
        {
            qDebug() << "MAKİNA CİNSİ Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "MAKİNA CİNSİ Dosyası YENİ Oluşturuldu - ";
            QStringList inserts;
            inserts << "INSERT INTO dbtb_mkcins ( cinsi ) values(' - ')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Otomobil')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Arazi Aracı')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Pickup')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Kamyon')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Çekici 2x2')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Çekici 4x2')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Çekici 4x4')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Forklift')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Loader')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Backhoe')"
                    << "INSERT INTO dbtb_mkcins ( cinsi ) values('Excavator')" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                    qDebug()  << " HATA - CİNS Kaydı Eklenemedi - "
                              << q.lastError() ;
                else
                    qDebug()  << " CİNS Kaydı Eklendi - ";

            }
        }
    }
}

///// MARKA
///
///
void MW_main::VTd_MARKA()
{
    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkmark"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_mkmark "
             "("
             "marka TEXT, "
             "mkcins_no INTEGER,"
             "id_mkmark INTEGER PRIMARY key )"  ;

        if (!q.exec( ct ))
        {
            qDebug() << "MARKA Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "MARKA Dosyası YENİ Oluşturuldu - ";
            QStringList inserts;
            inserts << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' - ',1)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' FORD '  ,2)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' RENAULT',2)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' OPEL '  ,2)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' VW'     ,2)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' JEEP '  ,3)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' TOYOTA' ,3)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' NISSAN ',4)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' ISUZU'  ,4)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' MERCEDES-BENZ',5)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' MERCEDES-BENZ',6)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' MERCEDES-BENZ',7)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' MERCEDES-BENZ',8)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' BAOLI'        ,9)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' ÇUKUROVA'     ,9)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' CATERPILLAR'  ,10)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' JVC'          ,11)"
                    << "INSERT INTO dbtb_mkmark ( marka,mkcins_no ) values(' HITACHI'      ,12)";

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                    qDebug()  << " HATA - MARKA Kaydı Eklenemedi - "
                              << q.lastError() ;
                else
                    qDebug()  << " MARKA Kaydı Eklendi - ";

            }
        }
    }
}

///// MODEL
///
///
void MW_main::VTd_MODEL()
{
    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_mkmodl"))
    {
        ct =  "CREATE TABLE IF NOT EXISTS dbtb_mkmodl "
              "("
              "modeli TEXT, "
              "mkmark_no INTEGER,"
              "id_mkmodl INTEGER PRIMARY key )"  ;

        if (!q.exec( ct ))
        {
            qDebug() << "MODEL Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "MODEL Dosyası YENİ Oluşturuldu - ";

            QStringList inserts;
            inserts << "INSERT INTO dbtb_mkmodl ( modeli, mkmark_no ) values(' - '       ,1)"
                    << "INSERT INTO dbtb_mkmodl ( modeli, mkmark_no ) values('Fiesta 1.4',2)"
                    << "INSERT INTO dbtb_mkmodl ( modeli, mkmark_no ) values('Focus 1.6' ,2)"
                    << "INSERT INTO dbtb_mkmodl ( modeli, mkmark_no ) values('Mondeo 2.0',2)"
                    << "INSERT INTO dbtb_mkmodl ( modeli, mkmark_no ) values('Clio'      ,3)"
                    << "INSERT INTO dbtb_mkmodl ( modeli, mkmark_no ) values('Laguna'    ,3)" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                    qDebug()  << " HATA - MODEL Kaydı Eklenemedi - "
                              << q.lastError() ;
                else
                    qDebug()  << " MODEL Kaydı Eklendi - ";

            }
        }
    }
}









///////////////////////////////////////////////////////// DBASE





void MW_main::yaz(QString x, QString y)
{
    if (x=="OK")
    {
        durum->append("<span style='color:green;font-size:15px' > "+ x +" < /span> "
                                                                        "<span style='color:lightblue;font-size:15px' > "+ y +" < /span> ");
    }
    else if  (x=="HATA")
    {
        durum->append("<span style='color:red;font-size:15px' > "+ x +" < /span> "
                                                                      "<span style='color:lightblue;font-size:15px' > "+ y +" < /span> ");
    }
    else
        durum->append("<span style='color:yellow;font-size:15px' > "+ x +" < /span> "
                                                                         "<span style='color:yellow;font-size:15px' > "+ y +" < /span> ");

}
