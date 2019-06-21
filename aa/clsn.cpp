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
    clsn_ui();

    CLSNmodel = new QSqlRelationalTableModel;
    clsn_model( CLSNmodel ) ;
    // Set Sort Ascending steering column data
    CLSNmodel->setSort(2,Qt::AscendingOrder);

    clsn_view();
    clsn_map();
    clsn_kntrl ();



}


void hC_CLSN::clsn_ui()
{

    qDebug() << "  clsn_ui";
    hC_CLSN::setWindowTitle ("ÇALIŞAN");
    hC_CLSN::showMaximized ();


    // ///////////////////////////////////////////////////////

    lB_clsn  = new QLabel ("ÇALIŞAN");
    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);

    // ///////////////////////////////////////////////////////
    // views
    CLSNtview = new hC_Tv();

    /////*******************************************////////

    QLabel *lB_isim  = new QLabel("İ&sim"        );
    lE_isim = new QLineEdit() ;
    lE_isim->setPlaceholderText ("Personel Adı");
    lB_isim->setBuddy(lE_isim);

    QLabel *lB_soyad = new QLabel("S&oyad"       );
    lE_soyad = new QLineEdit();
    lB_soyad->setBuddy(lE_soyad);

    QLabel *lB_tc    = new QLabel("TC Kimlik No" );
    lE_tc = new QLineEdit();
    lB_tc->setBuddy(lE_tc);

    QLabel *lB_doyer = new QLabel("Doğum Yeri "  );
    lE_doyer = new QLineEdit();
    lB_doyer->setBuddy(lE_doyer);

    QLabel *lB_dotar = new QLabel("Doğum Tarihi ");
    dT_dotar = new QDateEdit(); //QDate::currentDate ());
    dT_dotar->setSpecialValueText ("  ");
    dT_dotar->setLocale (QLocale::Turkish);
    dT_dotar->setMinimumDate(QDate::currentDate().addYears (-65));
    dT_dotar->setMaximumDate(QDate::currentDate().addDays(365));
    dT_dotar->setDisplayFormat ("dd-MM-yyyy");
    dT_dotar->setCalendarPopup (true);
    lB_dotar->setBuddy(dT_dotar);

    QLabel *lB_baba  = new QLabel("Baba Adı "  );
    lE_baba = new QLineEdit();
    lB_baba->setBuddy(lE_baba);

    QLabel *lB_bolum = new QLabel("Bölü&m"       );
    lE_bolum = new QLineEdit();
    lB_bolum->setBuddy(lE_bolum);

    QLabel *lB_meslek   = new QLabel("M&eslek" );
    lE_meslek = new QLineEdit;
    lB_meslek->setBuddy(lE_meslek);

    QLabel *lB_gorev    = new QLabel("Gö&rev"  );
    lE_gorev = new QLineEdit();
    lB_gorev->setBuddy(lE_gorev);

    QLabel *lB_adres    = new QLabel("Adre&s"  );
    lE_adres = new QLineEdit();
    lB_adres->setBuddy(lE_adres);

    QLabel *lB_sehir    = new QLabel("Şe&hir"  );
    lE_sehir = new QLineEdit();
    lB_sehir->setBuddy(lE_sehir);

    QLabel *lB_tel_cep  = new QLabel("Tel &1"  );
    lE_tel_cep = new QLineEdit();
    lB_tel_cep->setBuddy(lE_tel_cep);
    QLabel *lB_tel_ev   = new QLabel("Tel &2"  ); lE_tel_ev = new QLineEdit(); lB_tel_ev->setBuddy(lE_tel_ev);
    QLabel *lB_eposta   = new QLabel("E-&posta"); lE_eposta = new QLineEdit(); lB_eposta->setBuddy(lE_eposta);
    QLabel *lB_username = new QLabel("Kullanıcı A&dı"); lE_username = new QLineEdit(); lB_username->setBuddy(lE_username);
    QLabel *lB_password = new QLabel("Şi&fre"  ); lE_password = new QLineEdit(); lB_password->setBuddy(lE_password);
    QLabel *lB_yetki    = new QLabel("&Yetki"  ); lE_yetki = new QLineEdit(); lB_yetki->setBuddy(lE_yetki);

    auto *clsn_mly = new QGridLayout();


    clsn_mly->addWidget(lB_isim      , 0, 0, 1, 1);
    clsn_mly->addWidget(lE_isim      , 0, 1, 1, 2);
    clsn_mly->addWidget(lB_soyad     , 1, 0, 1, 1);
    clsn_mly->addWidget(lE_soyad     , 1, 1, 1, 2);
    clsn_mly->addWidget(lB_tc        , 2, 0, 1, 1);
    clsn_mly->addWidget(lE_tc        , 2, 1, 1, 2);
    clsn_mly->addWidget(lB_doyer     , 3, 0, 1, 1);
    clsn_mly->addWidget(lE_doyer     , 3, 1, 1, 2);
    clsn_mly->addWidget(lB_dotar     , 4, 0, 1, 1);
    clsn_mly->addWidget(dT_dotar     , 4, 1, 1, 2);
    clsn_mly->addWidget(lB_baba      , 5, 0, 1, 1);
    clsn_mly->addWidget(lE_baba      , 5, 1, 1, 2);
    clsn_mly->addWidget(lB_meslek    , 6, 0, 1, 1);
    clsn_mly->addWidget(lE_meslek    , 6, 1, 1, 2);
    clsn_mly->addWidget(lB_bolum     , 7, 0, 1, 1);
    clsn_mly->addWidget(lE_bolum     , 7, 1, 1, 2);
    clsn_mly->addWidget(lB_gorev     , 8, 0, 1, 1);
    clsn_mly->addWidget(lE_gorev     , 8, 1, 1, 2);
    clsn_mly->addWidget(lB_adres     , 9, 0, 1, 1);
    clsn_mly->addWidget(lE_adres     , 9, 1, 1, 2);
    clsn_mly->addWidget(lB_sehir     , 0, 3, 1, 1);
    clsn_mly->addWidget(lE_sehir     , 0, 4, 1, 2);
    clsn_mly->addWidget(lB_tel_cep   , 1, 3, 1, 1);
    clsn_mly->addWidget(lE_tel_cep   , 1, 4, 1, 2);
    clsn_mly->addWidget(lB_tel_ev    , 2, 3, 1, 1);
    clsn_mly->addWidget(lE_tel_ev    , 2, 4, 1, 2);
    clsn_mly->addWidget(lB_eposta    , 3, 3, 1, 1);
    clsn_mly->addWidget(lE_eposta    , 3, 4, 1, 2);
    clsn_mly->addWidget(lB_username  , 4, 3, 1, 1);
    clsn_mly->addWidget(lE_username  , 4, 4, 1, 2);
    clsn_mly->addWidget(lB_password  , 5, 3, 1, 1);
    clsn_mly->addWidget(lE_password  , 5, 4, 1, 2);
    clsn_mly->addWidget(lB_yetki     , 6, 3, 1, 1);
    clsn_mly->addWidget(lE_yetki     , 6, 4, 1, 2);

    auto *clsn_mainlay = new QGridLayout(this);
    clsn_mainlay->addWidget (CLSNtview  , 0, 0, 9, 5);
    clsn_mainlay->addLayout (clsn_mly   , 0, 5, 9, 5);
    clsn_mainlay->addWidget (lB_rsm     , 6, 8, 3, 2);

}
void hC_CLSN::clsn_view()
{
    qDebug()<<"clsn view ";
    CLSNtview->table->setModel(CLSNmodel);
    CLSNselectionMdl = CLSNtview->table->selectionModel();
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
    CLSNmapper->addMapping (lB_rsm, CLSNmodel->fieldIndex("resim"));
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
        hC_Rs resim(lB_rsm, CLSNtview, CLSNmodel, CLSNselectionMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  CLSNselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, CLSNtview, CLSNmodel, CLSNselectionMdl,
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

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  CLSNselectionMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  CLSNselectionMdl ,
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
    QString     ct, mesaj = "OK - Çalışan";
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
                    mesaj = mesaj + "<br>İLK Çalışan eklendi.";
                }
            } // foreach
        }
    }
    qDebug ()<< mesaj;
    return mesaj ;


}





void hC_CLSN::clsn_model(QSqlRelationalTableModel *model)
{
    qDebug() << " clsn mdl";
    QString indexField = "clsn_soyad";
    QString CLSNtableName ("clsn__dbtb");
    QStringList *tableFieldList = new QStringList ;
    tableFieldList->append("Çalışan Kod");
    tableFieldList->append("İsim");
    tableFieldList->append("Soyad");
    tableFieldList->append("TC Kimlik No");
    tableFieldList->append("Doğum Yeri");
    tableFieldList->append("Doğum Tarihi");
    tableFieldList->append("Baba Adı");
    tableFieldList->append("Bölüm");
    tableFieldList->append("Meslek");
    tableFieldList->append("Gorev");
    tableFieldList->append("Adres");
    tableFieldList->append("Şehir");
    tableFieldList->append("Telefon Cep");
    tableFieldList->append("Telefon Ev");
    tableFieldList->append("E-Poata");
    tableFieldList->append("Kullanıcı Adı");
    tableFieldList->append("Şifre");
    tableFieldList->append("Yetki");
    tableFieldList->append("resim");

    hC_Rm hC_Rm ( &CLSNtableName,
                 model,
                 &indexField ,
                 tableFieldList) ;

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

