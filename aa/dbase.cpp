#include "dbase.h"
#include "ui_dbase.h"

DBase::DBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBase)
{
    ui->setupUi(this);
}

DBase::~DBase()
{
    delete ui;
}

bool DBase::setupDBase()
{

    qDebug()<<"WD Login dbcontrol";
    //durum = new QTextEdit(this);
    /// veritabanini kontrol et yoksa olustur
    VTKontrolEt::instance()->SetupDB();

    /// veritabanina baglanilabilir mi
    if(VTKontrolEt::instance()->Connect())
    {
        /// baglanti var /// uygulama yoluna devam etsin
        //        emit DBase::gologin();


        /// bağlandı - olmayan dosyaları oluştur

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

    yaz(DBase::VTd_CLSN ());
    yaz(DBase::VTd_MSLK ());
    yaz(DBase::VTd_FRMA ());
    yaz(DBase::VTd_FTRA ());
    yaz(DBase::VTd_Mlzm ());
    yaz(DBase::VTd_MlzmDETAY ());


    yaz(DBase::VTd_mkn ());
    yaz(DBase::VTd_CINS ());
    yaz(DBase::VTd_MARKA ());
    yaz(DBase::VTd_MODEL ());


    DBase::VTd_ISEMRI ();
    DBase::VTd_ISEMRIDETAY ();
    DBase::VTd_IEDTAMIRYERI ();
    DBase::VTd_IEDTYDETAY ();
    DBase::VTd_ISCILIK ();
    DBase::VTd_TASINIR () ;
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


}


QString DBase::VTd_CLSN()
{
    QSqlQuery   q;
    QString     ct, mesaj = "OK - Çalışan";
    QStringList inserts;
    CLSNtableName = new QString( "clsn_dbtb");
    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( *CLSNtableName ))
    {

        ct = "CREATE TABLE IF NOT EXISTS " + *CLSNtableName +
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
            mesaj = "<br>HATA - Çalışan Dosyası Oluşturulamadı  "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - Çalışan Dosyası YENİ Oluşturuldu ";
            inserts << "INSERT INTO " + *CLSNtableName +
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
                    << "INSERT INTO " + *CLSNtableName +
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
                    mesaj = mesaj + "<br>İLK Çalışan Eklenemdi"+
                            "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else
                {
                    mesaj = mesaj + "<br>İLK Çalışan eklendi.";
                }
            } // foreach
        }
    }
    qDebug ()<< mesaj;
    return mesaj ;


}


///
/// \brief DBase::VTd_MSLK
/// \return
///
QString DBase::VTd_MSLK ()
{
    QString mesaj = "OK - Meslek";
    QSqlQuery query;
    MSLKtableName = new QString( "clsnmslk__dbtb");

    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( *MSLKtableName ))
    {
        if (! query.exec("create table if not exists " + *MSLKtableName +
                         " (id int, meslek TEXT)"))
        {
            mesaj = "<br>HATA - Meslek Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    query.lastError().text ()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - Meslek Dosyası YENİ Oluşturuldu - ";
            if ( !query.exec("insert into " + *MSLKtableName + " values(101, 'Makina Mühendisi')"))
            {
                mesaj = mesaj + "<br>İLK meslek kaydı eklenemedi "
                                "<br>------------------------------------<br>"+
                        query.lastError().text() +
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "<br>İLK Meslek kaydı eklendi.";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;
}



QString DBase::VTd_FRMA()
{
    QSqlQuery   q;
    QString     ct, mesaj ="OK - Firma";
    QStringList inserts;
    FRMtableName = new QString( "frm__dbtb");

    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( *FRMtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *FRMtableName +
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
            mesaj = "<br>HATA - Firma Dosyası Oluşturulamadı - "
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - FİRMA Dosyası YENİ Oluşturuldu ";
            inserts << "INSERT INTO " + *FRMtableName +
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
                    mesaj = mesaj + "<br>İLK Firma Kaydı Eklenemedi "
                                    "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else{
                    mesaj = mesaj + "<br>İLK Firma Eklendi ";
                }
            } // foreach
        }
    }
    qDebug()  << mesaj ;
    return mesaj ;
}   /// FİRMA



void DBase::modelFirma(QSqlRelationalTableModel *model)
{
    qDebug() << " mdlfrm";
    QString indexField = "frm_unvan";
    FRMtableName = new QString("frm__dbtb");

    QStringList *tableFieldList = new QStringList ;
    tableFieldList->append("Firma Kod");
    tableFieldList->append("Firma Unvanı");
    tableFieldList->append("Adres");
    tableFieldList->append("Şehir");
    tableFieldList->append("Vergi Dairesi");
    tableFieldList->append("VD No");
    tableFieldList->append("Telefon");
    tableFieldList->append("e-posta");
    tableFieldList->append("Yetkili İsim");
    tableFieldList->append("Yetkili Soyad");
    tableFieldList->append("Yetkili Telefon");
    // tableFieldList->append("resim");


     hC_Rm hC_Rm (FRMtableName,
                  model,
                  &indexField ,
                  tableFieldList) ;

      //FRMmodel = new QSqlRelationalTableModel;
     //    mdlfrm->setTable( "frm_dbtb" );
//    mdlfrm->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
//    mdlfrm->setSort(mdlfrm->fieldIndex ( indexField ),Qt::AscendingOrder );

//    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
//    {
//        mdlfrm->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
//    }

//    // Populate the model_mkstok
//    if (!mdlfrm->select())
//    {
//        qDebug () <<  " HATA - Model firma select "
//                   <<mdlfrm->lastError();
//    }


}///FİRMA






QString DBase::VTd_FTRA ()
{
    QSqlQuery   q;
    QString     ct, mesaj = "OK - Fatura" ;
    QStringList inserts;
    FTRtableName = new QString( "ftr__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains(*FTRtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *FTRtableName +
             "("
             "  ftr_kod    INTEGER PRIMARY KEY  , "
             "  ftr_no  	TEXT ,"
             "  ftr_firma	TEXT ,"
             "  ftr_tarih	TEXT ,"
             "  ftr_aciklama TEXT ,"
             "  ftr_resim    BLOB  )" ;

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - FATURA Dosyası Oluşturulamadı - "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = " OK - Fatuura Dosyası YENİ Oluşturuldu - ";
            inserts << "INSERT INTO " + *FTRtableName +
                       "( "
                       "ftr_no , ftr_firma "
                       ") "
                       "VALUES "
                       "("
                       "'1', 'İlk Firma -' "
                       " )" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {
                    mesaj = "<br>İLK Fatura Eklenemedi"
                            "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else
                {
                    mesaj = mesaj + "<br>İLK Fatura Eklendi";
                }
            } // foreach
        }
    }
    else /// dosya var
    {
        // mdlFtr = new QSqlRelationalTableModel;
        // mdlFtr = modelFatura();
    }

    qDebug()<< mesaj ;
    return mesaj;
}

void DBase::modelFatura(QSqlRelationalTableModel *model)
{
    qDebug() << " mdlftr";
    QString indexField = "ftr_tarih";
    QString *tableName = new QString("ftr__dbtb");
    QStringList *tableFieldList = new QStringList ;
    tableFieldList->append("Fatura Kod");
    tableFieldList->append("Fatura No");
    tableFieldList->append("Firma Unvanı");
    tableFieldList->append("Fatura Tarihi");
    tableFieldList->append("Açıklama");
    tableFieldList->append("Resim");

    hC_Rm hC_Rm (tableName,
                 model,
                 &indexField ,
                 tableFieldList) ;
    /*
    auto *mdlFtr = new QSqlRelationalTableModel;
    mdlFtr->setTable( "ftr__dbtb" );
    mdlFtr->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlFtr->setSort(mdlFtr->fieldIndex ( indexField ),Qt::AscendingOrder );

    //qDebug() << "  tablename " << *tableName <<"  indexfield "<< *indexField ;
    // qDebug() << " view column count = i "<< FTRmodel->columnCount();

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlFtr->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlFtr->select())
    {
        qDebug () <<  " HATA - Model fatura select "
                   <<mdlFtr->lastError();
    }

    return mdlFtr ;*/
}///FATURA



///
/// \brief DBase::VTd_Mlzm
/// \return
///
QString DBase::VTd_Mlzm()
{
    /// Malzeme create
    ///

    QString ct, mesaj ="OK - Malzeme";
    QSqlQuery q;
    MLZMtableName = new QString( "mlzm__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( "mlzm__dbtb"))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *MLZMtableName +
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
            mesaj="<br>HATA - Malzeme Dosyası Oluşturulamadı"
                  "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else /// dosya oluşturuldu
        {
            mesaj= "OK - Malzeme Dosyası YENİ Oluşturuldu ";
            if (
                    q.exec("INSERT INTO " + *MLZMtableName +
                           "( mlzm_barkod,mlzm_malzeme )"
                           " values( '1111','KOD 1 ve 1111 barkodlu malzeme' )"  ))
            {
                mesaj= mesaj+"<br>İLK kayıt Eklendi";
            }
            else
            {
                mesaj= mesaj+"<br>İLK Malzeme kaydı eklenemdi "
                             "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }

        }
    }
    else /// dosya var
    {
        //        mdlMlzm = new QSqlRelationalTableModel;
        //      mdlMlzm = modelMalzeme();
    }
    qDebug() << mesaj;
    return mesaj;
}



void DBase::modelMalzeme(QSqlRelationalTableModel *model)
{
    qDebug() << " mdlmlzm";
    QString *tableName = new QString("mlzm__dbtb");
    QString indexField = "mlzm_malzeme";
    QStringList *tableFieldList = new QStringList ;
    tableFieldList->append("Kod");
    tableFieldList->append("Barkod");
    tableFieldList->append("Malzeme");
    tableFieldList->append("Açıklama");
    tableFieldList->append("Marka");
    tableFieldList->append("Model");
    tableFieldList->append("Cins");
    tableFieldList->append("Birim");
    tableFieldList->append("Giriş");
    tableFieldList->append("Çıkış");
    tableFieldList->append("Mevcut");
    tableFieldList->append("Makina");
    tableFieldList->append("Resim");
    hC_Rm hC_Rm (tableName,
                 model,
                 &indexField ,
                 tableFieldList) ;
/*
    auto *mdlMlzm = new QSqlRelationalTableModel;
    mdlMlzm->setTable( "mlzm__dbtb" );
    mdlMlzm->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlMlzm->setSort(mdlMlzm->fieldIndex ( indexField ),Qt::AscendingOrder );

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlMlzm->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlMlzm->select())
    {
        qDebug () <<  " HATA - Model fatura select "
                   <<mdlMlzm->lastError();

    }
    qDebug () <<  " MŞZMmodel orj mw main"<<mdlMlzm;
    return mdlMlzm ;*/
}///Malzeme Model






///
/// \brief DBase::VTd_MlzmDETAY
/// \return
///
QString DBase::VTd_MlzmDETAY()
{
    QString ct, mesaj = "OK - Malzeme Detay";
    QSqlQuery q;
    MLZDETtableName = new QString( "mlzmdet__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().
         tables().contains( *MLZDETtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *MLZDETtableName +
             "("
             "mlzmDet_kod integer primary key, "
             "mlzmDet_mlzm_kod	INTEGER, "
             "mlzmDet_barkod	TEXT , "
             "mlzmDet_malzeme	TEXT , "
             "mlzmDet_tarih	    TEXT , "
             "mlzmDet_gc        TEXT , "    // faturalı giriş vs.
                "mlzmDet_gcno      TEXT , "    // fatura no  vs.
                "mlzmDet_miktar    TEXT , "
                "mlzmDet_birim     TEXT , "
                "mlzmDet_fiyat     TEXT , "
                "mlzmDet_kdv       TEXT , "
                "mlzmDet_aciklama  TEXT ,  "
                "mlzmDet_resim  BLOB  "
                ")";

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Malzeme Detay Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Malzeme Detay Dosyası YENİ Oluşturuldu";

            if (q.exec("INSERT INTO " + *MLZDETtableName +
                       "( mlzmdet_malzeme, mlzmDet_gc, mlzmDet_gcno )"
                       " values( '1 nolu ürüne ait detay','Faturalı Giriş','1' )"  ))
            {
                mesaj = mesaj + "<br>İLK kayıt eklendi";
            }
            else
            {
                mesaj = mesaj +"<br>İLK Kayıt EKLENEMEDİ "
                               "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;
}   /// malzeme detay


void DBase::modelMalzemeDetay(
        QSqlRelationalTableModel *model)
{
    /// NOTE Model 1 mw_main de modeli oluştur
    /// fatura detayında
    /// malzeme detay dosyası oluşturuluyor
    QString *tableName = new QString("mlzmdet__dbtb");
    QString indexField = "mlzmdet_gcno";

    QStringList *tableFieldList = new QStringList ;
    tableFieldList->append("Detay Kod");
    tableFieldList->append("Malzeme Kod");
    tableFieldList->append("Barkod");
    tableFieldList->append("Malzeme");
    tableFieldList->append("Tarih");
    tableFieldList->append("İşlem Türü");
    tableFieldList->append("İşlem No");
    tableFieldList->append("Miktar");
    tableFieldList->append("Birim");
    tableFieldList->append("Fiyat");
    tableFieldList->append("KDV");
    tableFieldList->append("Açıklama");
    tableFieldList->append("Resim");

    hC_Rm hC_Rm (tableName,
                 model,
                 &indexField ,
                 tableFieldList) ;

/*    auto *mdlMlzmDty = new QSqlRelationalTableModel;
    mdlMlzmDty->setTable( "mlzmdet__dbtb" );
    mdlMlzmDty->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlMlzmDty->setSort(mdlMlzmDty->fieldIndex ( indexField ),Qt::AscendingOrder );

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlMlzmDty->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlMlzmDty->select())
    {
        qDebug () <<  " HATA - Model fatura select "
                   <<mdlMlzmDty->lastError();

    }

    return mdlMlzmDty ;*/
}///fsturs detsy Model









///
/// \brief DBase::VTd_mkn
///
QString DBase::VTd_mkn()
{

    /// MKSTOK create
    ///
    QString ct, mesaj = "OK - Makina";
    QSqlQuery q;
    MKNtableName = new QString( "mkn__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( *MKNtableName ))
    {
        //mkn_kurumNo key used every table's relation

        ct =  "CREATE TABLE IF NOT EXISTS  " + *MKNtableName +
              "("
              "id_mkn integer primary key, "
              "mkn_kurumno       TEXT, "
              "mkn_plaka         TEXT, "
              "mkn_cinsi         TEXT, "
              "mkn_Marka         TEXT,"
              "mkn_modeli        TEXT,"
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
            mesaj = "<br>HATA - Makina Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Malzeme Detay Dosyası YENİ Oluşturuldu";

            if ( q.exec("INSERT INTO "+*MKNtableName+" ( mkn_kurumNo,mkn_cinsi,"
                        "mkn_marka, mkn_modeli, mkn_surucu )"
                        " values( '100001', 1 , 1 , 1 , 1 )"  ))
            {
                mesaj = mesaj + "<br>İLK kayıt eklendi";
            }
            else
            {
                mesaj = mesaj +"<br>İLK Kayıt EKLENEMEDİ "
                               "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;



}       /// VTdMKSTOK



void DBase::modelMakina(QSqlRelationalTableModel *model)
{
    qDebug() << " modelmkn";
    QString indexField = "mkn_kurumno";
    MKNtableName = new QString("mkn__dbtb");


    QStringList *tableFieldList = new QStringList ;
    tableFieldList->append("Makina Kod");
    tableFieldList->append("Kurum No");
    tableFieldList->append("Plaka");
    tableFieldList->append("Cinsi");
    tableFieldList->append("Markası");
    tableFieldList->append("Modeli");
    tableFieldList->append("Model Yılı");
    tableFieldList->append("Şase No");
    tableFieldList->append("Motor No");
    tableFieldList->append("Motor Tipi");
    tableFieldList->append("Yakıt Türü");
    tableFieldList->append("Sürücü Adı");
    tableFieldList->append("İşe Başlama Tarihi");
    tableFieldList->append("Birimi");
    tableFieldList->append("Açıklama");
    tableFieldList->append("Bulunduğu Yer");
    tableFieldList->append("Resim");
    tableFieldList->append("Rating");
    // tableFieldList->append("resim");
    hC_Rm hC_Rm (MKNtableName,
                 model,
                 &indexField ,
                 tableFieldList) ;
/*
    auto *mdlmkn = new QSqlRelationalTableModel;
    mdlmkn->setTable( "mkn__dbtb" );
    mdlmkn->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlmkn->setSort(mdlmkn->fieldIndex ( indexField ),Qt::AscendingOrder );
    mdlmkn->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlmkn->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlmkn->select())
    {
        qDebug () <<  " HATA - Model fatura select "
                   <<mdlmkn->lastError();
    }

    return mdlmkn ;*/
}///MKN





///// CINS
///
///
QString DBase::VTd_CINS()
{
    qDebug() << "db Cinsi CREATE  ";
    QString ct, mesaj = "OK - Cinsi";
    QSqlQuery q;
    CNStableName = new QString( "mkcins__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( *CNStableName ))
    {
        ct = "CREATE TABLE " + *CNStableName +
             "("
             "cinsi TEXT, "
             "resim BLOB, "
             "id_mkcins INTEGER PRIMARY key "
             ") " ;


        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Cinsi Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Cinsi Dosyası YENİ Oluşturuldu";

            QStringList inserts;
            inserts << "INSERT INTO "+ *CNStableName +" ( cinsi ) values(' - ')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Otomobil')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Arazi Aracı')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Pickup')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Kamyon')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Çekici 2x2')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Çekici 4x2')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Çekici 4x4')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Forklift')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Loader')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Backhoe')"
                    << "INSERT INTO "+ *CNStableName +" ( cinsi ) values('Excavator')" ;
            int x{},y{};
            foreach (QString qry , inserts)
            {
                if ( q.exec(qry) )
                {
                    x++;
                }
                else
                {
                    y++;

                }
            }
            if (x>0)
            {
                mesaj = mesaj + QString::number (x) +
                        "<br>kayıt eklendi";
            }
            if (y>0)
            {
                mesaj = mesaj + QString::number (y) +
                        "<br>Kayıt EKLENEMEDİ "
                        "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;

}

void DBase::modelCinsi(QSqlRelationalTableModel *model)
{
    qDebug() << " db model cns";
    CNStableName = new QString("mkcins__dbtb");
    QString indexField = "cinsi";
    QStringList *tableFieldList = new QStringList ;

    tableFieldList->append("Cinsi");
    tableFieldList->append("Resim");
    tableFieldList->append("Cinsi Kodu");
    hC_Rm hC_Rm (CNStableName,
                 model,
                 &indexField ,
                 tableFieldList) ;
    /*
    auto *mdlcnsi = new QSqlRelationalTableModel;
    mdlcnsi->setTable( "mkcins__dbtb" );
    mdlcnsi->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlcnsi->setSort(mdlcnsi->fieldIndex ( indexField ),Qt::AscendingOrder );
    mdlcnsi->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlcnsi->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlcnsi->select())
    {
        qDebug () <<  " HATA - Model Cinsi select "
                   <<mdlcnsi->lastError();
    }

    return mdlcnsi ;*/
}///CNS




///// MARKA
///
///
QString DBase::VTd_MARKA()
{
    qDebug() << " db Marka CREATE  ";
    QString ct, mesaj = "OK - Marka";
    QSqlQuery q;
    MRKtableName = new QString( "mkmark__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( *MRKtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *MRKtableName +
             "("
             "marka TEXT, "
             "resim BLOB, "
             "mkcins_no INTEGER,"
             "id_mkmark INTEGER PRIMARY key )"  ;



        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Marka Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Marka Dosyası YENİ Oluşturuldu";


            QStringList inserts;
            inserts << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' - ',1)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' FORD '  ,2)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' RENAULT',2)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' OPEL '  ,2)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' VW'     ,2)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' JEEP '  ,3)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' TOYOTA' ,3)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' NISSAN ',4)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' ISUZU'  ,4)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',5)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',6)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',7)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',8)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' BAOLI'        ,9)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' ÇUKUROVA'     ,9)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' CATERPILLAR'  ,10)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' JVC'          ,11)"
                    << "INSERT INTO "+ *MRKtableName +" ( marka,mkcins_no ) values(' HITACHI'      ,12)";
            int x{},y{};
            foreach (QString qry , inserts)
            {
                if ( q.exec(qry) )
                {
                    x++;
                }
                else
                {
                    y++;

                }
            }
            if (x>0)
            {
                mesaj = mesaj + QString::number (x) +
                        "<br>kayıt eklendi";
            }
            if (y>0)
            {
                mesaj = mesaj + QString::number (y) +
                        "<br>Kayıt EKLENEMEDİ "
                        "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;

}


void DBase::modelMarka(QSqlRelationalTableModel *model)
{
    qDebug() << " db modelmarka";
    MRKtableName = new QString("mkmark__dbtb");
    QString indexField = "marka";
    QStringList *tableFieldList = new QStringList ;

    tableFieldList->append("Marka");
    tableFieldList->append("Resim");
    tableFieldList->append("Cinsi Nosu");
    tableFieldList->append("Marka kodu");

    hC_Rm hC_Rm (MRKtableName,
                 model,
                 &indexField ,
                 tableFieldList) ;
    /*
    auto *mdlmrk = new QSqlRelationalTableModel;
    mdlmrk->setTable( "mkmark__dbtb" );
    mdlmrk->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlmrk->setSort(mdlmrk->fieldIndex ( indexField ),Qt::AscendingOrder );
    mdlmrk->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlmrk->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlmrk->select())
    {
        qDebug () <<  " HATA - Model Marka select "
                   <<mdlmrk->lastError();
    }

    return mdlmrk ;*/
}///MRK




///// MODEL
///
///
QString DBase::VTd_MODEL()
{
    qDebug() << " db Modeli CREATE  ";
    QString ct, mesaj = "OK - Model";
    QSqlQuery q;
    MDLtableName = new QString( "mkmodl__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( *MDLtableName ))
    {
        ct =  "CREATE TABLE IF NOT EXISTS " + *MDLtableName +
              "("
              "modeli TEXT, "
              "resim BLOB, "
              "mkmark_no INTEGER,"
              "id_mkmodl INTEGER PRIMARY key )"  ;


        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Modeli Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Modeli Dosyası YENİ Oluşturuldu";


            QStringList inserts;
            inserts << "INSERT INTO "+ *MDLtableName +" ( modeli, mkmark_no ) values(' - '       ,1)"
                    << "INSERT INTO "+ *MDLtableName +" ( modeli, mkmark_no ) values('Fiesta 1.4',2)"
                    << "INSERT INTO "+ *MDLtableName +" ( modeli, mkmark_no ) values('Focus 1.6' ,2)"
                    << "INSERT INTO "+ *MDLtableName +" ( modeli, mkmark_no ) values('Mondeo 2.0',2)"
                    << "INSERT INTO "+ *MDLtableName +" ( modeli, mkmark_no ) values('Clio'      ,3)"
                    << "INSERT INTO "+ *MDLtableName +" ( modeli, mkmark_no ) values('Laguna'    ,3)" ;
            int x{},y{};
            foreach (QString qry , inserts)
            {
                if ( q.exec(qry) )
                {
                    x++;
                }
                else
                {
                    y++;

                }
            }
            if (x>0)
            {
                mesaj = mesaj + QString::number (x) +
                        "<br>kayıt eklendi";
            }
            if (y>0)
            {
                mesaj = mesaj + QString::number (y) +
                        "<br>Kayıt EKLENEMEDİ "
                        "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;

}



void DBase::modelModeli(QSqlRelationalTableModel *model)
{
    qDebug() << " db modeldlmodeli";
    MDLtableName = new QString("mkmodl__dbtb");
    QString indexField = "modeli";
    QStringList *tableFieldList = new QStringList ;


    tableFieldList->append("Model");
    tableFieldList->append("Resim");
    tableFieldList->append("Marka Nosu");
    tableFieldList->append("Model kodu");
    hC_Rm hC_Rm ( MDLtableName,
                 model,
                 &indexField ,
                 tableFieldList) ;

/*
    auto *mdlmdli = new QSqlRelationalTableModel;
    mdlmdli->setTable( "mkmodl__dbtb" );
    mdlmdli->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mdlmdli->setSort(mdlmdli->fieldIndex ( indexField ),Qt::AscendingOrder );
    mdlmdli->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    for(int i = 0, j = 0; i < tableFieldList.size (); i++, j++)
    {
        mdlmdli->setHeaderData(i,Qt::Horizontal,tableFieldList.value (j));
    }

    // Populate the model_mkstok
    if (!mdlmdli->select())
    {
        qDebug () <<  " HATA - Model Marka select "
                   <<mdlmdli->lastError();
    }

    return mdlmdli ; */
}///MDLİ






void DBase::VTd_ISEMRI ()
{
    ///  ISEMRI create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_IE"))
    {
        /// mkstok_no joins Mlzm with işemri
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


void DBase::VTd_ISEMRIDETAY ()
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




void DBase::VTd_ISCILIK ()
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



void DBase::VTd_TASINIR ()
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



/*
void DBase::VTd_DPTLP()
{
    /// Malzeme talep create
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
            qDebug() << "Malzeme TALEP Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << "Malzeme TALEP Dosyası YENİ Oluşturuldu - ";
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











///////////////////////////////////////////////////////// DBASE




void DBase::yaz(const QString& z)
{
    QString x,y;
    x = z.left(z.indexOf("-"));
    y = z.right(z.length() - z.indexOf("-"));
    qDebug()<<"x= "<< x <<"   y= "<<y;
    if (x.contains("OK"))
    {
        ui->durum->append("<span style='color:green;font-size:15px' > "
                          + x +" < /span> "
                               "<span style='color:darkblue;font-size:15px' > "
                          + y +" < /span> ");
    }
    else if  (x.contains("HATA"))
    {
        ui->durum->append("<span style='color:red;font-size:15px' > "
                          + x +" < /span> "
                               "<span style='color:darkblue;font-size:15px' > "
                          + y +" < /span> ");
    }
    else
        ui->durum->append("<span style='color:darkyellow;font-size:15px' > "
                          + x +" < /span> "
                               "<span style='color:darkyellow;font-size:15px' > "
                          + y +" < /span> ");

}

