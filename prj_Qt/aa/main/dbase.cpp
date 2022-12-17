
#ifdef MAIN
#include "libs/globals.h"
#include "libs/dbase.h"
#endif

#ifdef ADRS
#include "adrs/clsn.h"
#include "adrs/frm.h"
#include "adrs/ftr.h"


#endif

#include "ie/ie.h"
#include "ie/iedet.h"
#include "ie/sclk.h"
#include "ie/tsnr.h"


//#include "hsap/hc_hsp.h"
#include "hsap/hc_hspdetay.h"

#include "mchn/mkn.h"
#include "mchn/mkn_cinsi.h"
#include "mchn/mkn_marka.h"
#include "mchn/mkn_modeli.h"

#include "mlzm/mlzm.h"
#include "mlzm/mlzm_gc.h"

#include "ui_dbase.h"

DBase::DBase(QWidget* parent)
    : QWidget(parent)
{
    qDebug ()<<"Constructor DBase *******************************";
    //************************************************************
    //*******************  VERİ TABANI ***************************
    dbui();
    dbwdgt();
    dbkntrl();
    //   ui->setupUi(this);
    durum->append("Veri tabanı dosyaları kontrol ediliyor...");
}

void DBase::dbui()
{
    qDebug() << "   dbase ";

    DBase::setWindowTitle ("Veri Tabanı Kontrol");
    //this->setGeometry (20,20,600,400);

    durum = new QTextEdit;
    win_Wdgt = new QWidget;
    win_Wdgt->adjustSize ();

    auto win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);
    win_Grid->addWidget(durum      , 0, 0, 1, 1);

    auto *win_grid = new QGridLayout(this);
    win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);
    //win_grid->addWidget (durum  , 0, 0, 1, 1);
}

void DBase::dbwdgt()
{

}

void DBase::dbkntrl()
{

}

DBase::~DBase()
{
    //delete ui;
}
bool DBase::setupDBase()
{
    //qDebug()<<"setupDbase ";
    //durum = new QTextEdit(this);
    /// veritabanini kontrol et yoksa olustur
    VTKontrolEt::instance()->SetupDB();
    /// veritabanina baglanilabilir mi
    if(VTKontrolEt::instance()->Connect())
    {
        DBase::VTDosyaKontrol ();
        return true;
    }
    /// hata ne /// baglanti yok
    QString x = "Hata 002 - Code::Database NOT Connected !!! <br>"+
            VTKontrolEt::instance ()->GetError ()   ;
    yaz("/// ? - "+x);
    return false;
}

void DBase::VTDosyaKontrol()
{

#ifdef ADRS
    hC_CLSN* clsn = new hC_CLSN;
    yaz(clsn->tbCreate (clsn->tb_flds));
    delete clsn ;

    hC_FRM* frm = new hC_FRM;
    yaz(frm->tbCreate (frm->tb_flds));
    delete frm ;
#endif

#ifdef HSAP
    hC_HSPDTY* hspdty = new hC_HSPDTY;
    yaz(hspdty->tbCreate (hspdty->tb_flds));
    delete hspdty ;
#endif

#ifdef OTHR
    hC_FTR* ftr = new hC_FTR;
    yaz(ftr->tbCreate (ftr->tb_flds));
    delete ftr ;

    hC_IE* ie = new hC_IE;
    yaz(ie->tbCreate (ie->tb_flds));
    delete ie ;

    hC_IEDET* iedet = new hC_IEDET;
    yaz(iedet->tbCreate (iedet->tb_flds));
    delete iedet ;

    hC_MKN* mkn = new hC_MKN;
    yaz(mkn->tbCreate (mkn->tb_flds));
    delete mkn ;

    hC_MKCINS* mkcins = new hC_MKCINS;
    yaz(mkcins->tbCreate (mkcins->tb_flds));
    delete mkcins ;

    hC_MKMARK* mkmark = new hC_MKMARK;
    yaz(mkmark->tbCreate (mkmark->tb_flds));
    delete mkmark ;

    hC_MKMODL* mkmodl = new hC_MKMODL;
    yaz(mkmodl->tbCreate (mkmodl->tb_flds));
    delete mkmodl ;

    hC_MLZM* mlzm = new hC_MLZM;
    yaz(mlzm->tbCreate (mlzm->tb_flds)) ;
    delete mlzm ;

    hC_MLZMGC* mlzmgc = new hC_MLZMGC;
    yaz(mlzmgc->tbCreate (mlzmgc->tb_flds)) ;
    delete mlzmgc ;

    hC_SCLK* sclk = new hC_SCLK;
    yaz(sclk->tbCreate (sclk->tb_flds)) ;
    delete sclk ;

    hC_TSNR* tsnr = new hC_TSNR;
    yaz(tsnr->tbCreate (tsnr->tb_flds)) ;
    delete tsnr ;

    DBase::VTd_IEDTAMIRYERI ();
    DBase::VTd_IEDTYDETAY ();

    DBase::VTd_MKYAG ();
    DBase::VTd_MKFILTRE ();
    DBase::VTd_MKAKU ();
    DBase::VTd_MKLASTIK ();
    DBase::VTd_MKMUAYENE ();
    DBase::VTd_MKSIGORTA ();
    DBase::VTd_MKYAKIT();
    DBase::VTd_MKANTIFIRIZ();
    DBase::VTd_MKZINCIR ();
    DBase::VTd_MKHGS ();
#endif
}

void DBase::yaz(const QString& z)
{
    // qDebug ()<<"yaz - 1";
    QString x,y;
    x = z.left(z.indexOf("-"));
    y = z.right(z.length() - z.indexOf("-"));
    //    qDebug()<<"x= "<< x <<"   y= "<<y;
    if (x.contains("OK"))
    {
        // qDebug ()<<"yaz - 11";
        durum->append("<span style='color:green;font-size:15px' > "
                      + x +" < /span> "
                           "<span style='color:darkblue;font-size:15px' > "
                      + y +" < /span> ");
    }
    else if  (x.contains("HATA"))
    {
        //  qDebug ()<<"yaz - 12";
        durum->append("<span style='color:red;font-size:15px' > "
                      + x +" < /span> "
                           "<span style='color:darkblue;font-size:15px' > "
                      + y +" < /span> ");
    }
    else
    {
        //  qDebug ()<<"yaz - 13";
        durum->append("<span style='color:darkyellow;font-size:15px' > "
                      + x +" < /span> "
                           "<span style='color:darkyellow;font-size:15px' > "
                      + y +" < /span> ");
    }
}

void DBase::VTd_IEDTAMIRYERI ()
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



void DBase::VTd_IEDTYDETAY ()
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



void DBase::VTd_MKYAG ()
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
void DBase::VTd_MKFILTRE ()
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
void DBase::VTd_MKAKU ()
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
void DBase::VTd_MKLASTIK ()
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

void DBase::VTd_MKMUAYENE()
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


void DBase::VTd_MKSIGORTA()
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



void DBase::VTd_MKYAKIT()
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
void DBase::VTd_MKANTIFIRIZ()
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
void DBase::VTd_MKZINCIR ()
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
void DBase::VTd_MKHGS ()
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
///////////////////////////////////////////////////////// DBASE

