#include "kira.h"

hC_KIRA::hC_KIRA() : hC_tBcreator ()
{
    qDebug ()<<"Constructor KİRA *******************************";
    //************************************************************
    //*****************     K İ R A     **************************
    win_Label->setText ( "KİRA KAYITLARI");
    *tb_name   = "kira_dbtb" ;
    *tb_ndex  = "kira_duztar";

    int f_no=0;
    tb_flds = new hC_ArrD (14, 4);
    tb_flds->setValue (f_no++, "f_kr_ID"             , "INTEGER", "KiraID", "0" ) ;
    tb_flds->setValue (f_no++, "f_kr_duzenleme_tarih", "TEXT"   , "Düzenleme Tarihi" );
    tb_flds->setValue (f_no++, "f_kr_duzenleme_No"   , "TEXT"   , "Düzenleme No" );
    tb_flds->setValue (f_no++, "f_kr_kveren_tc"      , "INTEGER", "Kiraya Veren TC" );
    tb_flds->setValue (f_no++, "f_kr_kirac_tc"       , "INTEGER", "Kiracı TC");
    tb_flds->setValue (f_no++, "f_kr_krlnn_adres_kod", "TEXT"   , "Kiralanan Adres Kodu");
    tb_flds->setValue (f_no++, "f_kr_bas_tarihi"     , "TEXT"   , "Kira Başlangıç Tarihi");
    tb_flds->setValue (f_no++, "f_kr_bit_tarihi"     , "TEXT"   , "Kira Bitiş Tarihi");
    tb_flds->setValue (f_no++, "f_kr_sure"           , "TEXT"   , "Süre");
    tb_flds->setValue (f_no++, "f_kr_bedel"          , "INTEGER", "Kira Bedeli");
    tb_flds->setValue (f_no++, "f_kr_teminat"        , "INTEGER", "Teminat Bedeli");
    tb_flds->setValue (f_no++, "f_kr_odeme_sekil"    , "TEXT"   , "Ödeme Şekli");
    tb_flds->setValue (f_no++, "f_kr_hesap_no"       , "TEXT"   , "HesapNo");
    tb_flds->setValue (f_no++, "f_kr_resim"          , "BLOB"   , "Resim");



    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( dE_duztar  = new QDateEdit   ) ;
    tb_wdgts->append ( lE_duzno = new QLineEdit   ) ;
    tb_wdgts->append ( lE_kvtc = new QLineEdit      ) ;
    tb_wdgts->append ( lE_kctc = new QLineEdit  ) ;
    tb_wdgts->append ( lE_adkod = new QLineEdit  ) ;
    tb_wdgts->append ( dE_kbastar = new QDateEdit  ) ;
    tb_wdgts->append ( dE_kbttar = new QDateEdit  ) ;
    tb_wdgts->append ( lE_sure = new QLineEdit   ) ;
    tb_wdgts->append ( lE_bedel = new QLineEdit ) ;
    tb_wdgts->append ( lE_teminat = new QLineEdit   ) ;
    tb_wdgts->append ( lE_osekli = new QLineEdit    ) ;
    tb_wdgts->append ( lE_hesno  = new QLineEdit   ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_KIRA::tbsetup()
{
    qDebug() << "   kira setup ";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_KIRA::tbui()
{

    qDebug() << "   ui";

    hC_KIRA::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,600,400);
    auto *win_grid = new QGridLayout(this);
    win_grid->addWidget (tb_view  , 0, 0, 1, 1);
    //win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);

}
void hC_KIRA::tbwdgt()
{
    qDebug() << "   wdgt";

    auto *lB_duztar = new QLabel("Düzenleme Tarihi ");
    //QDate::currentDate ());
    dE_duztar->setSpecialValueText ("  ");
    dE_duztar->setLocale (QLocale::Turkish);
    dE_duztar->setMinimumDate(QDate::currentDate().addYears (-65));
    dE_duztar->setMaximumDate(QDate::currentDate().addDays(365));
    dE_duztar->setDisplayFormat ("dd-MM-yyyy");
    dE_duztar->setCalendarPopup (true);
    lB_duztar->setBuddy(dE_duztar);



    auto *lB_duzno  = new QLabel("Düzenleme No"        );
    lE_duzno->setPlaceholderText ("Düzenleme No");
    lB_duzno->setBuddy(lE_duzno);

    auto *lB_kvtc = new QLabel("Kiraya Veren TC"       );
    lB_kvtc->setBuddy(lE_kvtc);

    auto *lB_kctc    = new QLabel("Kiracı TC" );
    lB_kctc->setBuddy(lE_kctc);

    auto *lB_adkod = new QLabel("Kiralanan Adres Kod"  );
    lB_adkod->setBuddy(lE_adkod);

    auto *lB_kbastar = new QLabel("Kira Başlangıç Tarihi ");
    //QDate::currentDate ());
    dE_kbastar->setSpecialValueText ("  ");
    dE_kbastar->setLocale (QLocale::Turkish);
    dE_kbastar->setMinimumDate(QDate::currentDate().addYears (-65));
    dE_kbastar->setMaximumDate(QDate::currentDate().addDays(365));
    dE_kbastar->setDisplayFormat ("dd-MM-yyyy");
    dE_kbastar->setCalendarPopup (true);
    lB_kbastar->setBuddy(dE_kbastar);

    auto *lB_kbttar = new QLabel("Kira Bitiş Tarihi ");
    //QDate::currentDate ());
    dE_kbttar->setSpecialValueText ("  ");
    dE_kbttar->setLocale (QLocale::Turkish);
    dE_kbttar->setMinimumDate(QDate::currentDate().addYears (-65));
    dE_kbttar->setMaximumDate(QDate::currentDate().addDays(365));
    dE_kbttar->setDisplayFormat ("dd-MM-yyyy");
    dE_kbttar->setCalendarPopup (true);
    lB_kbttar->setBuddy(dE_kbttar);

    auto *lB_sure  = new QLabel("Kira Süresi"  );
    lE_sure = new QLineEdit();
    lB_sure->setBuddy(lE_sure);

    auto *lB_bedel = new QLabel("Kira Bedeli"       );
    lE_bedel = new QLineEdit();
    lB_bedel->setBuddy(lE_bedel);

    auto *lB_tm   = new QLabel("Teminat" );
    lE_teminat = new QLineEdit;
    lB_tm->setBuddy(lE_teminat);

    auto *lB_osekli = new QLabel("Ödeme Şekli"  );
    lE_osekli = new QLineEdit();
    lB_osekli->setBuddy(lE_osekli);

    auto *lB_hesno  = new QLabel("Banka Hesap No"  );
    lE_hesno = new QLineEdit();
    lB_hesno->setBuddy(lE_hesno);

    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////

    win_Wdgt->adjustSize ();
    auto win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);

    ///////////////////////////////////////

    //tb_view->table->setMinimumWidth (200);
    lB_duzno->setMinimumSize (200,25);
    lE_duzno->setMinimumSize (100,25);


    win_Grid->addWidget(lB_duztar    , 0, 0, 1, 1);
    win_Grid->addWidget(dE_duztar    , 0, 1, 1, 2);
    win_Grid->addWidget(lB_duzno     , 1, 0, 1, 1);
    win_Grid->addWidget(lE_duzno     , 1, 1, 1, 2);
    win_Grid->addWidget(lB_kvtc      , 2, 0, 1, 1);
    win_Grid->addWidget(lE_kvtc      , 2, 1, 1, 2);
    win_Grid->addWidget(lB_kctc      , 3, 0, 1, 1);
    win_Grid->addWidget(lE_kctc      , 3, 1, 1, 2);
    win_Grid->addWidget(lB_adkod     , 4, 0, 1, 1);
    win_Grid->addWidget(lE_adkod     , 4, 1, 1, 2);
    win_Grid->addWidget(lB_kbastar   , 5, 0, 1, 1);
    win_Grid->addWidget(dE_kbastar   , 5, 1, 1, 2);
    win_Grid->addWidget(lB_kbttar    , 6, 0, 1, 1);
    win_Grid->addWidget(dE_kbttar    , 6, 1, 1, 2);
    win_Grid->addWidget(lB_sure      , 7, 0, 1, 1);
    win_Grid->addWidget(lE_sure      , 7, 1, 1, 2);
    win_Grid->addWidget(lB_bedel     , 8, 0, 1, 1);
    win_Grid->addWidget(lE_bedel     , 8, 1, 1, 2);
    win_Grid->addWidget(lB_tm        , 9, 0, 1, 1);
    win_Grid->addWidget(lE_teminat   , 9, 1, 1, 2);
    win_Grid->addWidget(lB_osekli    ,10, 0, 1, 1);
    win_Grid->addWidget(lE_osekli    ,10, 1, 1, 2);
    win_Grid->addWidget(lB_hesno     ,11, 0, 1, 1);
    win_Grid->addWidget(lE_hesno     ,11, 1, 1, 2);
    win_Grid->addWidget(win_Rsm      , 7, 4, 3, 2);

}

void hC_KIRA::tbkntrl()
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
        dE_duztar->setDate( QDate::fromString( "01/01/2022", "dd/MM/yyyy" ) );


        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Kira kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Kira Kaydı eklendi ";
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


void hC_KIRA::showEvent(QShowEvent *)
{
    qDebug() << "Kira dosyası açılıyor";
}


hC_KIRA::~hC_KIRA()
{
    qDebug() << "*********** destructor KİRA";
}




