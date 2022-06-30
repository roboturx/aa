#include "clsn.h"

hC_CLSN::hC_CLSN () : hC_tBcreator ()
{
    qDebug ()<<"Constructor ÇALIŞAN *******************************";
    //************************************************************
    //*****************  Ç A L I Ş A N  **************************

    win_Label->setText ( "ÇALIŞAN KAYITLARI");
    *tb_name   = "clsn_dbtb" ;
    *tb_ndex  = "clsn_soyad";

    tb_flds = new hC_ArrD (19, 4);
    tb_flds->setValue ( 0, "clsn_ID"      , "INTEGER", "ÇalışanID", "0" ) ;
    tb_flds->setValue ( 1, "clsn_isim"    , "TEXT"   , "İsim" );
    tb_flds->setValue ( 2, "clsn_soyad"   , "TEXT"   , "Soyad" );
    tb_flds->setValue ( 3, "clsn_tc"      , "TEXT"   , "TC No");
    tb_flds->setValue ( 4, "clsn_dyeri"   , "TEXT"   , "Doğum Yeri");
    tb_flds->setValue ( 5, "clsn_dtarihi" , "TEXT"   , "Doğum Tarihi");
    tb_flds->setValue ( 6, "clsn_baba"    , "TEXT"   , "Baba Adı");
    tb_flds->setValue ( 7, "clsn_bolum"   , "TEXT"   , "Çalıştığı Birim");
    tb_flds->setValue ( 8, "clsn_meslek"  , "TEXT"   , "Meslek");
    tb_flds->setValue ( 9, "clsn_gorev"   , "TEXT"   , "Görev");
    tb_flds->setValue (10, "clsn_adres"   , "TEXT"   , "Adres");
    tb_flds->setValue (11, "clsn_sehir"   , "TEXT"   , "Şehir");
    tb_flds->setValue (12, "clsn_tel_cep" , "TEXT"   , "Cep Tel");
    tb_flds->setValue (13, "clsn_tel_ev"  , "TEXT"   , "Ev Tel");
    tb_flds->setValue (14, "clsn_eposta"  , "TEXT"   , "E-posta");
    tb_flds->setValue (15, "clsn_username", "TEXT"   , "Kullanıcı Adı");
    tb_flds->setValue (16, "clsn_password", "TEXT"   , "Kullanıcı Şifre");
    tb_flds->setValue (17, "clsn_yetki"   , "TEXT"   , "Kullanıcı Yetki");
    tb_flds->setValue (18, "clsn_resim"   , "BLOB"   , "Resim");

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( lE_isim  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_soyad = new QLineEdit   ) ;
    tb_wdgts->append ( lE_tc = new QLineEdit      ) ;
    tb_wdgts->append ( lE_doyer = new QLineEdit  ) ;
    tb_wdgts->append ( dT_dotar = new QDateEdit  ) ;
    tb_wdgts->append ( lE_baba = new QLineEdit  ) ;
    tb_wdgts->append ( lE_bolum = new QLineEdit  ) ;
    tb_wdgts->append ( lE_meslek = new QLineEdit   ) ;
    tb_wdgts->append ( lE_gorev = new QLineEdit ) ;
    tb_wdgts->append ( lE_adres = new QLineEdit   ) ;
    tb_wdgts->append ( lE_sehir = new QLineEdit    ) ;
    tb_wdgts->append ( lE_tel_cep  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_tel_ev  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_eposta = new QLineEdit   ) ;
    tb_wdgts->append ( lE_username  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_password  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_yetki  = new QLineEdit   ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_CLSN::tbsetup()
{
    qDebug() << "   clsn setup ";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_CLSN::tbui()
{

    qDebug() << "   ui";

    hC_CLSN::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,600,400);
    auto *win_grid = new QGridLayout(this);
   // win_grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);

}
void hC_CLSN::tbwdgt()
{
    qDebug() << "   wdgt";

    auto *lB_isim  = new QLabel("İ&sim"        );
    lE_isim->setPlaceholderText ("Personel Adı");
    lB_isim->setBuddy(lE_isim);

    auto *lB_soyad = new QLabel("S&oyad"       );
    lB_soyad->setBuddy(lE_soyad);

    auto *lB_tc    = new QLabel("TC Kimlik No" );
    lB_tc->setBuddy(lE_tc);

    auto *lB_doyer = new QLabel("Doğum Yeri "  );
    lB_doyer->setBuddy(lE_doyer);

    auto *lB_dotar = new QLabel("Doğum Tarihi ");
    //QDate::currentDate ());
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

    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////

    win_Wdgt->adjustSize ();
    auto win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);

    ///////////////////////////////////////

    //tb_view->table->setMinimumWidth (200);
    lB_isim->setMinimumSize (100,25);
    lE_isim->setMinimumSize (100,25);
    lB_sehir->setMinimumSize (100,25);
    lE_sehir->setMinimumSize (150,25);


    win_Grid->addWidget(lB_isim      , 0, 0, 1, 1);
    win_Grid->addWidget(lE_isim      , 0, 1, 1, 2);
    win_Grid->addWidget(lB_soyad     , 1, 0, 1, 1);
    win_Grid->addWidget(lE_soyad     , 1, 1, 1, 2);
    win_Grid->addWidget(lB_tc        , 2, 0, 1, 1);
    win_Grid->addWidget(lE_tc        , 2, 1, 1, 2);
    win_Grid->addWidget(lB_doyer     , 3, 0, 1, 1);
    win_Grid->addWidget(lE_doyer     , 3, 1, 1, 2);
    win_Grid->addWidget(lB_dotar     , 4, 0, 1, 1);
    win_Grid->addWidget(dT_dotar     , 4, 1, 1, 2);
    win_Grid->addWidget(lB_baba      , 5, 0, 1, 1);
    win_Grid->addWidget(lE_baba      , 5, 1, 1, 2);
    win_Grid->addWidget(lB_meslek    , 6, 0, 1, 1);
    win_Grid->addWidget(lE_meslek    , 6, 1, 1, 2);
    win_Grid->addWidget(lB_bolum     , 7, 0, 1, 1);
    win_Grid->addWidget(lE_bolum     , 7, 1, 1, 2);
    win_Grid->addWidget(lB_gorev     , 8, 0, 1, 1);
    win_Grid->addWidget(lE_gorev     , 8, 1, 1, 2);
    win_Grid->addWidget(lB_adres     , 9, 0, 1, 1);
    win_Grid->addWidget(lE_adres     , 9, 1, 1, 2);
    win_Grid->addWidget(lB_sehir     , 0, 3, 1, 1);
    win_Grid->addWidget(lE_sehir     , 0, 4, 1, 2);
    win_Grid->addWidget(lB_tel_cep   , 1, 3, 1, 1);
    win_Grid->addWidget(lE_tel_cep   , 1, 4, 1, 2);
    win_Grid->addWidget(lB_tel_ev    , 2, 3, 1, 1);
    win_Grid->addWidget(lE_tel_ev    , 2, 4, 1, 2);
    win_Grid->addWidget(lB_eposta    , 3, 3, 1, 1);
    win_Grid->addWidget(lE_eposta    , 3, 4, 1, 2);
    win_Grid->addWidget(lB_username  , 4, 3, 1, 1);
    win_Grid->addWidget(lE_username  , 4, 4, 1, 2);
    win_Grid->addWidget(lB_password  , 5, 3, 1, 1);
    win_Grid->addWidget(lE_password  , 5, 4, 1, 2);
    win_Grid->addWidget(lB_yetki     , 6, 3, 1, 1);
    win_Grid->addWidget(lE_yetki     , 6, 4, 1, 2);
    win_Grid->addWidget(win_Rsm       , 7, 4, 3, 2);

}

void hC_CLSN::tbkntrl()
{

    qDebug() << "   KNTRL";


    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
        ////////////////////////////////////////////////

        QSqlRecord rec = tb_model->record();

        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        tb_model->submitAll ();

        ////////////////////////////////////////////////
        /// son eklenen kayda git
        maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
        ////////////////////////////////////////////////
    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                     "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   tb_view->table->currentIndex();
        if( sample.row() >= 0 )
        {

            //         tb_view->table->selectionModel()->setCurrentIndex
            //             (sample,QItemSelectionModel::NoUpdate);

            QSqlRecord rec = tb_model->record();
            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                tb_model->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                tb_model->select();
            }
        }
    });
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_CLSN::sgn(tb_view->table->model()->index( Index.row() ,
        //               tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });



}


void hC_CLSN::showEvent(QShowEvent *)
{
    qDebug() << "Personel dosyası açılıyor";
}


hC_CLSN::~hC_CLSN()
{
    qDebug() << "*********** destructor ÇALIŞAN";
}

