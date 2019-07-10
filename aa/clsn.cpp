#include "clsn.h"

hC_CLSN::hC_CLSN ( QWidget *parent) : QWidget(parent)
{
    qDebug ()<<"Çalışan Constructor";
    //************************************************************
    //*****************  Ç A L I Ş A N  **************************
}


void hC_CLSN::clsn_setup()
{
    qDebug() << "clsn setup ";

    clsn_VTd ();
    clsn_model() ;
    clsn_wdgt  ();
    clsn_map();
    clsn_ui();
    clsn_view();
    clsn_kntrl ();
}


void hC_CLSN::clsn_ui()
{

    qDebug() << "  clsn_ui";
    ////////////////////////////////////////// window
    winLabel = new QLabel("ÇALIŞAN BİLGİLERİ");
    hC_CLSN::setWindowTitle (winLabel->text ());


    // ///////////////////////////////////////////////////////
    // views
    CLSNtview = new hC_Tv(CLSNmodel, CLSNmapper, winWdgt);

    /////*******************************************////////
    auto *gridClsn = new QGridLayout(this);
    gridClsn->addWidget (CLSNtview  , 0, 0, 1, 1);
    gridClsn->addWidget (winWdgt   , 0, 1, 1, 1);
}
void hC_CLSN::clsn_wdgt()
{
    qDebug() << "  clsn_wdgt";

    auto *lB_isim  = new QLabel("İ&sim"        );
    lE_isim = new QLineEdit() ;
    lE_isim->setPlaceholderText ("Personel Adı");
    lB_isim->setBuddy(lE_isim);

    auto *lB_soyad = new QLabel("S&oyad"       );
    lE_soyad = new QLineEdit();
    lB_soyad->setBuddy(lE_soyad);

    qDebug()<<" height "<<lE_soyad->height ()
           <<" mm : "<<lE_soyad->heightMM ();
    qDebug()<<" widht  "<<lE_soyad->width ();

    auto *lB_tc    = new QLabel("TC Kimlik No" );
    lE_tc = new QLineEdit();
    lB_tc->setBuddy(lE_tc);

    auto *lB_doyer = new QLabel("Doğum Yeri "  );
    lE_doyer = new QLineEdit();
    lB_doyer->setBuddy(lE_doyer);

    auto *lB_dotar = new QLabel("Doğum Tarihi ");
    dT_dotar = new QDateEdit(); //QDate::currentDate ());
    dT_dotar->setSpecialValueText ("  ");
    dT_dotar->setLocale (QLocale::Turkish);
    dT_dotar->setMinimumDate(QDate::currentDate().addYears (-65));
    dT_dotar->setMaximumDate(QDate::currentDate().addDays(365));
    dT_dotar->setDisplayFormat ("dd-MM-yyyy");
    dT_dotar->setCalendarPopup (true);
    lB_dotar->setBuddy(dT_dotar);

    auto *lB_baba  = new QLabel("Baba Adı "  );
    lE_baba = new QLineEdit();
    lB_baba->setBuddy(lE_baba);

    auto *lB_bolum = new QLabel("Bölü&m"       );
    lE_bolum = new QLineEdit();
    lB_bolum->setBuddy(lE_bolum);

    auto *lB_meslek   = new QLabel("M&eslek" );
    lE_meslek = new QLineEdit;
    lB_meslek->setBuddy(lE_meslek);

    auto *lB_gorev    = new QLabel("Gö&rev"  );
    lE_gorev = new QLineEdit();
    lB_gorev->setBuddy(lE_gorev);

    auto *lB_adres    = new QLabel("Adre&s"  );
    lE_adres = new QLineEdit();
    lB_adres->setBuddy(lE_adres);

    auto *lB_sehir    = new QLabel("Şe&hir"  );
    lE_sehir = new QLineEdit();
    lB_sehir->setBuddy(lE_sehir);


    auto *lB_tel_cep  = new QLabel("Tel &1"  );
    lE_tel_cep = new QLineEdit();
    lB_tel_cep->setBuddy(lE_tel_cep);
    auto *lB_tel_ev   = new QLabel("Tel &2"  ); lE_tel_ev = new QLineEdit(); lB_tel_ev->setBuddy(lE_tel_ev);
    auto *lB_eposta   = new QLabel("E-&posta"); lE_eposta = new QLineEdit(); lB_eposta->setBuddy(lE_eposta);
    auto *lB_username = new QLabel("Kullanıcı A&dı"); lE_username = new QLineEdit(); lB_username->setBuddy(lE_username);
    auto *lB_password = new QLabel("Şi&fre"  ); lE_password = new QLineEdit(); lB_password->setBuddy(lE_password);
    auto *lB_yetki    = new QLabel("&Yetki"  ); lE_yetki = new QLineEdit(); lB_yetki->setBuddy(lE_yetki);

    winRsm = new QLabel ("Resim");
    hC_Rs resim(winRsm);


    ///////////////////////////////////////
    winWdgt = new QWidget;
    winWdgt->setGeometry (0,0,800,300);
    auto winGrid = new QGridLayout();
    winWdgt->setLayout(winGrid);

    ///////////////////////////////////////

    //CLSNtview->table->setMinimumWidth (200);
    lB_isim->setMinimumSize (100,25);
    lE_isim->setMinimumSize (100,25);
    lB_sehir->setMinimumSize (100,25);
    lE_sehir->setMinimumSize (150,25);


    winGrid->addWidget(lB_isim      , 0, 0, 1, 1);
    winGrid->addWidget(lE_isim      , 0, 1, 1, 2);
    winGrid->addWidget(lB_soyad     , 1, 0, 1, 1);
    winGrid->addWidget(lE_soyad     , 1, 1, 1, 2);
    winGrid->addWidget(lB_tc        , 2, 0, 1, 1);
    winGrid->addWidget(lE_tc        , 2, 1, 1, 2);
    winGrid->addWidget(lB_doyer     , 3, 0, 1, 1);
    winGrid->addWidget(lE_doyer     , 3, 1, 1, 2);
    winGrid->addWidget(lB_dotar     , 4, 0, 1, 1);
    winGrid->addWidget(dT_dotar     , 4, 1, 1, 2);
    winGrid->addWidget(lB_baba      , 5, 0, 1, 1);
    winGrid->addWidget(lE_baba      , 5, 1, 1, 2);
    winGrid->addWidget(lB_meslek    , 6, 0, 1, 1);
    winGrid->addWidget(lE_meslek    , 6, 1, 1, 2);
    winGrid->addWidget(lB_bolum     , 7, 0, 1, 1);
    winGrid->addWidget(lE_bolum     , 7, 1, 1, 2);
    winGrid->addWidget(lB_gorev     , 8, 0, 1, 1);
    winGrid->addWidget(lE_gorev     , 8, 1, 1, 2);
    winGrid->addWidget(lB_adres     , 9, 0, 1, 1);
    winGrid->addWidget(lE_adres     , 9, 1, 1, 2);
    winGrid->addWidget(lB_sehir     , 0, 3, 1, 1);
    winGrid->addWidget(lE_sehir     , 0, 4, 1, 2);
    winGrid->addWidget(lB_tel_cep   , 1, 3, 1, 1);
    winGrid->addWidget(lE_tel_cep   , 1, 4, 1, 2);
    winGrid->addWidget(lB_tel_ev    , 2, 3, 1, 1);
    winGrid->addWidget(lE_tel_ev    , 2, 4, 1, 2);
    winGrid->addWidget(lB_eposta    , 3, 3, 1, 1);
    winGrid->addWidget(lE_eposta    , 3, 4, 1, 2);
    winGrid->addWidget(lB_username  , 4, 3, 1, 1);
    winGrid->addWidget(lE_username  , 4, 4, 1, 2);
    winGrid->addWidget(lB_password  , 5, 3, 1, 1);
    winGrid->addWidget(lE_password  , 5, 4, 1, 2);
    winGrid->addWidget(lB_yetki     , 6, 3, 1, 1);
    winGrid->addWidget(lE_yetki     , 6, 4, 1, 2);
    winGrid->addWidget(winRsm       , 7, 4, 3, 2);

}
void hC_CLSN::clsn_view()
{
    qDebug()<<"clsn view ";
    CLSNtview->table->setModel(CLSNmodel);
    CLSNslctnMdl = CLSNtview->table->selectionModel();
    //////////////////////////////////////////////////////////
    //// kullanıcı bu alanları görmesin
    CLSNtview->table->setColumnHidden(CLSNmodel->fieldIndex("clsn_kod"), true);
    CLSNtview->table->setColumnHidden(CLSNmodel->fieldIndex("resim"), true);
    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    CLSNtview->table->setCurrentIndex(
                CLSNmodel->index(0, 1)
                );
    // with blue rect
    CLSNtview->table->setFocus();
    //   QTimer::singleShot(0, CLSNtview->table, SLOT(setFocus()));

}



/* user interface */
void hC_CLSN::clsn_map()
{
    qDebug()<<"clsn map ";
    CLSNmapper = new QDataWidgetMapper(this);
    CLSNmapper->setModel(CLSNmodel);

    CLSNmapper->addMapping (lE_isim , CLSNmodel->fieldIndex("clsn_isim"));
    CLSNmapper->addMapping (lE_soyad, CLSNmodel->fieldIndex("clsn_soyad"));
    CLSNmapper->addMapping (lE_tc, CLSNmodel->fieldIndex("clsn_tckimlik"));
    CLSNmapper->addMapping (lE_doyer, CLSNmodel->fieldIndex("clsn_dogumyeri"));
    CLSNmapper->addMapping (dT_dotar, CLSNmodel->fieldIndex("clsn_dogumtarihi"));
    CLSNmapper->addMapping (lE_baba, CLSNmodel->fieldIndex("clsn_babaadi"));

    CLSNmapper->addMapping (lE_bolum,    CLSNmodel->fieldIndex("clsn_bolum"));
    CLSNmapper->addMapping (lE_meslek,   CLSNmodel->fieldIndex("clsn_meslek"));
    CLSNmapper->addMapping (lE_gorev,    CLSNmodel->fieldIndex("clsn_gorev"));
    CLSNmapper->addMapping (lE_adres,    CLSNmodel->fieldIndex("clsn_adres"));
    CLSNmapper->addMapping (lE_sehir,    CLSNmodel->fieldIndex("clsn_sehir"));
    CLSNmapper->addMapping (lE_tel_cep,  CLSNmodel->fieldIndex("clsn_tel_cep"));
    CLSNmapper->addMapping (lE_tel_ev,   CLSNmodel->fieldIndex("clsn_tel_ev"));
    CLSNmapper->addMapping (lE_eposta,   CLSNmodel->fieldIndex("clsn_eposta"));
    CLSNmapper->addMapping (lE_username, CLSNmodel->fieldIndex("clsn_username"));
    CLSNmapper->addMapping (lE_password, CLSNmodel->fieldIndex("clsn_password"));
    CLSNmapper->addMapping (lE_yetki, CLSNmodel->fieldIndex("clsn_yetki"));
    //CLSNmapper->addMapping (winRsm, CLSNmodel->fieldIndex("resim"));
    qDebug()<<"clsn view son";
    CLSNmapper->toFirst ();
}


void hC_CLSN::clsn_kntrl()
{


    // pB 001 yeni ekle
    connect(CLSNtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = CLSNmodel->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! CLSNmodel->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        CLSNmodel->select();

    });

    // pB 002 yeni resim ekle
    connect(CLSNtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim( winRsm, CLSNtview, CLSNmodel, CLSNslctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  CLSNslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( winRsm, CLSNtview, CLSNmodel, CLSNslctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(CLSNtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   CLSNtview->table->currentIndex();
        if( sample.row() >= 0 )
        {

            //         CLSNtview->table->selectionModel()->setCurrentIndex
            //             (sample,QItemSelectionModel::NoUpdate);

            QSqlRecord rec = CLSNmodel->record();
            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                CLSNmodel->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                CLSNmodel->select();
            }
        }
    });
/*
    // pB 006 ilk
    connect(CLSNtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        CLSNtview->hC_TvPb ("ilk", CLSNmodel, CLSNmapper);
    });

    // pB 007 önceki
    connect(CLSNtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        CLSNtview->hC_TvPb ("ncki", CLSNmodel, CLSNmapper);
    });

    // pB 008 sonraki
    connect(CLSNtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
      CLSNtview->hC_TvPb ("snrki", CLSNmodel, CLSNmapper);
    });

    // pB 009 son
    connect(CLSNtview->pB_son, &QPushButton::clicked,
            [this]()
    {CLSNtview->hC_TvPb ("son", CLSNmodel, CLSNmapper);
    });



    // pB 010 nav tuslari kontrol
    connect(CLSNmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {CLSNtview->hC_TvPb ("yenile", CLSNmodel, CLSNmapper);

    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  CLSNslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        CLSNmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_CLSN::sgn(CLSNtview->table->model()->index( Index.row() ,
        //               CLSNmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  CLSNslctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        CLSNmapper->setCurrentModelIndex(Index);
    });



}






void hC_CLSN::showEvent(QShowEvent *)
{
    qDebug() << "Personel dosyası açılıyor";
}


hC_CLSN::~hC_CLSN()
= default;



QString hC_CLSN::clsn_VTd()
{
    QSqlQuery   q;
    QString     ct, mesaj = "  OK - Çalışan";
    QStringList inserts;
    QString CLSNtableName ( "clsn__dbtb");
    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( CLSNtableName ))
    {

        ct = "CREATE TABLE IF NOT EXISTS " + CLSNtableName +
             "("
             "  clsn_kod	    INTEGER PRIMARY KEY  , "
             "  clsn_isim		TEXT ,"
             "  clsn_soyad	    TEXT ,"
             "  clsn_tckimlik    TEXT ,"
             "  clsn_dogumyeri   TEXT ,"
             "  clsn_dogumtarihi DATE ,"
             "  clsn_babaadi     TEXT ,"
             "  clsn_bolum	    TEXT ,"
             "  clsn_meslek      int ,"
             "  clsn_gorev	    TEXT ,"
             "  clsn_adres		TEXT ,"
             "  clsn_sehir       TEXT ,"
             "  clsn_tel_cep	    TEXT ,"
             "  clsn_tel_ev	    TEXT ,"
             "  clsn_eposta      TEXT ,"
             "  clsn_username	TEXT ,"
             "  clsn_password	TEXT ,"
             "  clsn_yetki		TEXT ,"
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
            inserts << "INSERT INTO " + CLSNtableName +
                       "( "
                       "clsn_isim, clsn_soyad, "
                       "clsn_bolum, clsn_meslek, clsn_gorev, "
                       "clsn_adres, clsn_sehir, "
                       "clsn_tel_cep, clsn_tel_ev, clsn_eposta,"
                       " clsn_username, clsn_password, clsn_yetki"
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
                    mesaj = mesaj + "İLK Çalışan eklendi.";
                }
            } // foreach
        }
    }
    qDebug ()<< mesaj;
    return mesaj ;


}





void hC_CLSN::clsn_model()
{
    qDebug() << "  clsn mdl";
    QString indexField = "clsn_soyad";
    QString CLSNtableName ("clsn__dbtb");
    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Çalışan Kod");
    tB_FieldList->append("İsim");
    tB_FieldList->append("Soyad");
    tB_FieldList->append("TC Kimlik No");
    tB_FieldList->append("Doğum Yeri");
    tB_FieldList->append("Doğum Tarihi");
    tB_FieldList->append("Baba Adı");
    tB_FieldList->append("Bölüm");
    tB_FieldList->append("Meslek");
    tB_FieldList->append("Gorev");
    tB_FieldList->append("Adres");
    tB_FieldList->append("Şehir");
    tB_FieldList->append("Telefon Cep");
    tB_FieldList->append("Telefon Ev");
    tB_FieldList->append("E-Poata");
    tB_FieldList->append("Kullanıcı Adı");
    tB_FieldList->append("Şifre");
    tB_FieldList->append("Yetki");
    tB_FieldList->append("resim");

    CLSNmodel = new QSqlRelationalTableModel;
  /*  hC_Rm hC_Rm ( &CLSNtableName,
                 CLSNmodel,
                 &indexField ,
                 tB_FieldList) ;
*/
} /// ÇALIŞAN





//*/

/////
///// \brief DBase::VTd_MSLK
///// \return
/////
//QString DBase::VTd_MSLK ()
//{
//    QString mesaj = "OK - Meslek";
//    QSqlQuery query;
//    MSLKtableName = new QString( "clsnmslk__dbtb");

//    if ( ! VTKontrolEt::instance()->
//         GetDB().tables().contains( *MSLKtableName ))
//    {
//        if (! query.exec("create table if not exists " + *MSLKtableName +
//                         " (id int, meslek TEXT)"))
//        {
//            mesaj = "<br>HATA - Meslek Dosyası Oluşturulamadı"
//                    "<br>------------------------------------<br>"+
//                    query.lastError().text ()+
//                    "<br>------------------------------------<br>";
//        }
//        else
//        {
//            mesaj = "OK - Meslek Dosyası YENİ Oluşturuldu - ";
//            if ( !query.exec("insert into " + *MSLKtableName + " values(101, 'Makina Mühendisi')"))
//            {
//                mesaj = mesaj + "<br>İLK meslek kaydı eklenemedi "
//                                "<br>------------------------------------<br>"+
//                        query.lastError().text() +
//                        "<br>------------------------------------<br>";
//            }
//            else
//            {
//                mesaj = mesaj + "<br>İLK Meslek kaydı eklendi.";
//            }
//        }
//    }
//    qDebug()<< mesaj ;
//    return mesaj ;
//} /// meslek

