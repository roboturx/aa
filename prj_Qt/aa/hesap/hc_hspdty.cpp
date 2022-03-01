#include "hc_hspdty.h"

hC_HSPDTY::hC_HSPDTY() : hC_tBcreator ()

{


    qDebug ()<<"Constructor HESAP DETAY **************************";
    //************************************************************
    //*****************  H E S A P  D E T A Y ********************

    win_Label->setText ( "HESAP DETAY KAYITLARI");
    *tb_name   = "hspdty_dbtb" ;
    *tb_ndex  = "hspdty_ad";

    tb_flds = new hC_ArrD (11, 4);
    tb_flds->setValue ( 0, "hsp_ID"      , "INTEGER", "HesapID", "0" ) ;
    tb_flds->setValue ( 1, "hsp_ad"      , "TEXT"   , "Hesap Adı" );
    tb_flds->setValue ( 2, "hsp_tarih"   , "TEXT"   , "Tarih" );
    tb_flds->setValue ( 3, "hsp_no"      , "TEXT"   , "No");
    tb_flds->setValue ( 4, "hsp_aciklama", "TEXT"   , "Açıklama");
    tb_flds->setValue ( 5, "hsp_aktar"   , "TEXT"   , "Aktarılan Hesap");
    tb_flds->setValue ( 6, "hsp_ok"      , "TEXT"   , "Ok");
    tb_flds->setValue ( 7, "hsp_borc"    , "TEXT"   , "Borç");
    tb_flds->setValue ( 8, "hsp_alacak"  , "TEXT"   , "Alacak");
    tb_flds->setValue ( 9, "hsp_bakiye"  , "TEXT"   , "Bakiye");
    tb_flds->setValue (10, "hsp_resim"   , "BLOB"   , "Resim");

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( lE_ad  = new QLineEdit   ) ;
    tb_wdgts->append ( dE_tarih = new QDateEdit   ) ;
    tb_wdgts->append ( lE_no = new QLineEdit      ) ;
    tb_wdgts->append ( lE_aciklama = new QLineEdit  ) ;
    tb_wdgts->append ( cB_aktar = new QComboBox  ) ;
    tb_wdgts->append ( lE_ok = new QLineEdit  ) ;
    tb_wdgts->append ( lE_borc = new QLineEdit  ) ;
    tb_wdgts->append ( lE_alacak = new QLineEdit   ) ;
    tb_wdgts->append ( lE_bakiye = new QLineEdit ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_HSPDTY::tbsetup()
{
    qDebug() << "   hsp setup ";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_HSPDTY::tbui()
{

    qDebug() << "   ui";

    hC_HSPDTY::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,600,400);
    auto *win_grid = new QGridLayout(this);
   // win_grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);

}
void hC_HSPDTY::tbwdgt()
{
    qDebug() << "   wdgt";

    auto *lB_tarih  = new QLabel("T&arih"        );
  //  dE_tarih->setPlaceholderText ("Tarih");
    lB_tarih->setBuddy(dE_tarih);
    //QDate::currentDate ());
    dE_tarih->setSpecialValueText ("  ");
    dE_tarih->setLocale (QLocale::Turkish);
    dE_tarih->setMinimumDate(QDate::currentDate().addYears (-25));
 //   dE_tarih->setMaximumDate(QDate::currentDate().addYars(25));
    dE_tarih->setDisplayFormat ("dd-MM-yyyy");
    dE_tarih->setCalendarPopup (true);
    lB_tarih->setBuddy(dE_tarih);




    auto *lB_no = new QLabel("N&o"       );
    lB_no->setBuddy(lE_no);

    auto *lB_aciklama    = new QLabel("Açıklama" );
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_aktar = new QLabel("Aktarılan hesap "  );
    lB_aktar->setBuddy(cB_aktar);

    auto *lB_ok = new QLabel("Ok ");
    lB_ok->setBuddy(lE_ok);

    auto *lB_borc  = new QLabel("Borç "  );
    lE_borc = new QLineEdit();
    lB_borc->setBuddy(lE_borc);

    auto *lB_alacak = new QLabel("Alacak"       );
    lE_alacak = new QLineEdit();
    lB_alacak->setBuddy(lE_alacak);

    auto *lB_bakiye   = new QLabel("B&akiye" );
    lE_bakiye = new QLineEdit;
    lB_bakiye->setBuddy(lE_bakiye);

    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////

    win_Wdgt->adjustSize ();
    auto win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);

    ///////////////////////////////////////

    //tb_view->table->setMinimumWidth (200);
 //   lB_ad->setMinimumSize (100,25);
  //  lE_ad->setMinimumSize (100,25);
    lB_alacak->setMinimumSize (200,25);
   // lB_alacak->setMinimumSize (150,25);


  //  win_Grid->addWidget(lB_ad      , 0, 0, 1, 1);
  //  win_Grid->addWidget(lE_ad      , 0, 1, 1, 2);
    win_Grid->addWidget(lB_tarih     , 1, 0, 1, 1);
    win_Grid->addWidget(dE_tarih     , 1, 1, 1, 2);
    win_Grid->addWidget(lB_no        , 2, 0, 1, 1);
    win_Grid->addWidget(lE_no        , 2, 1, 1, 2);
    win_Grid->addWidget(lB_aciklama     , 3, 0, 1, 1);
    win_Grid->addWidget(lE_aciklama     , 3, 1, 1, 2);
    win_Grid->addWidget(lB_aktar     , 4, 0, 1, 1);
    win_Grid->addWidget(cB_aktar     , 4, 1, 1, 2);
    win_Grid->addWidget(lB_ok      , 5, 0, 1, 1);
    win_Grid->addWidget(lE_ok      , 5, 1, 1, 2);
    win_Grid->addWidget(lB_borc    , 6, 0, 1, 1);
    win_Grid->addWidget(lE_borc    , 6, 1, 1, 2);
    win_Grid->addWidget(lB_alacak     , 7, 0, 1, 1);
    win_Grid->addWidget(lE_alacak     , 7, 1, 1, 2);
    win_Grid->addWidget(lB_bakiye     , 8, 0, 1, 1);
    win_Grid->addWidget(lE_bakiye     , 8, 1, 1, 2);
    win_Grid->addWidget(win_Rsm       , 7, 4, 3, 2);

}

void hC_HSPDTY::tbkntrl()
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
        dE_tarih->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Hesap kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Hesap Kaydı eklendi ";
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
        //     emit hC_HSPDTY::sgn(tb_view->table->model()->index( Index.row() ,
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


void hC_HSPDTY::showEvent(QShowEvent *)
{
    qDebug() << "Hesap Detay dosyası açılıyor";
}


hC_HSPDTY::~hC_HSPDTY()
{
    qDebug() << "*********** destructor Hesap Detay";
}

