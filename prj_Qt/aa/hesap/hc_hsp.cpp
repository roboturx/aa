#include "hc_hsp.h"

hC_HSP::hC_HSP() : hC_tBcreator ()
{
    qDebug ()<<"Constructor HESAP ********************************";
    //************************************************************
    //*****************  H E S A P  ******************************

    win_Label->setText ( "HESAP KAYITLARI");
    *tb_name   = "hsp_dbtb" ;
    *tb_ndex  = "hsp_ad";

    tb_flds = new hC_ArrD (12, 4);
    tb_flds->setValue ( 0, "hsp_ID"      , "INTEGER", "HesapID", "0" ) ;
    tb_flds->setValue ( 1, "hsp_ad"      , "TEXT"   , "Hesap Adı" );
    tb_flds->setValue ( 2, "hsp_tarih"   , "TEXT"   , "Açılış Tarihi" );
    tb_flds->setValue ( 3, "hsp_aciklama", "TEXT"   , "Açıklama");
    tb_flds->setValue ( 4, "hsp_parabrm" , "TEXT"   , "Birim");
    tb_flds->setValue ( 5, "hsp_not"     , "TEXT"   , "Not");
    tb_flds->setValue ( 6, "hsp_gizli"   , "TEXT"   , "Gizli");
    tb_flds->setValue ( 7, "hsp_toplu"   , "TEXT"   , "Toplu");
    tb_flds->setValue ( 8, "hsp_turu"    , "TEXT"   , "Türü");
    tb_flds->setValue ( 9, "hsp_lft"     , "TEXT"   , "LEFT");
    tb_flds->setValue (10, "hsp_rgt"     , "TEXT"   , "RIGHT");
    tb_flds->setValue (11, "hsp_resim"   , "BLOB"   , "Resim");

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( lE_ad  = new QLineEdit   ) ;
    tb_wdgts->append ( dE_tarih = new QDateEdit   ) ;
    tb_wdgts->append ( lE_aciklama = new QLineEdit  ) ;
    tb_wdgts->append ( cB_parabrm = new QComboBox ) ;
    tb_wdgts->append ( lE_not = new QLineEdit  ) ;
    tb_wdgts->append ( lE_gizli = new QLineEdit  ) ;
    tb_wdgts->append ( lE_toplu = new QLineEdit  ) ;
    tb_wdgts->append ( cB_turu = new QComboBox   ) ;
    tb_wdgts->append ( lE_lft = new QLineEdit ) ;
    tb_wdgts->append ( lE_rgt = new QLineEdit ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_HSP::tbsetup()
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


void hC_HSP::tbui()
{

    qDebug() << "   ui";

    hC_HSP::setWindowTitle (win_Label->text ());
    this->setGeometry (20,20,600,400);
    auto *win_grid = new QGridLayout(this);
    win_grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_grid->addWidget (win_Wdgt   , 0, 1, 1, 1);

}
void hC_HSP::tbwdgt()
{
    qDebug() << "   wdgt";

    auto *lB_ad = new QLabel("Hesap Adı"       );
    lB_ad->setBuddy(lE_ad);

    auto *lB_tarih  = new QLabel("Açılış Tarihi"        );
  //  dE_tarih->setPlaceholderText ("Tarih");
    lB_tarih->setBuddy(dE_tarih);
    dE_tarih->setSpecialValueText ("  ");
    dE_tarih->setLocale (QLocale::Turkish);
    dE_tarih->setMinimumDate(QDate::currentDate().addYears (-25));
    dE_tarih->setMaximumDate(QDate::currentDate().addYears(25));
    dE_tarih->setDisplayFormat ("dd-MM-yyyy");
    dE_tarih->setCalendarPopup (true);
    lB_tarih->setBuddy(dE_tarih);

    auto *lB_aciklama    = new QLabel("Açıklama" );
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_parabrm = new QLabel("Para Birimi"       );

    auto *lB_not = new QLabel("Not "  );
    lB_not->setBuddy(lE_not);

    auto *lB_gizli = new QLabel("Gizli ");
    lB_gizli->setBuddy(lE_gizli);

    auto *lB_toplu  = new QLabel("Toplu "  );
    lB_toplu->setBuddy(lE_toplu);

    auto *lB_turu = new QLabel("Hesap Türü" );
    auto *lB_lft   = new QLabel("LEFT" );
    auto *lB_rgt   = new QLabel("RIGHT" );

    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////

    win_Wdgt->adjustSize ();
    auto win_Grid = new QGridLayout();
    win_Wdgt->setLayout(win_Grid);

    ///////////////////////////////////////

    //tb_view->table->setMinimumWidth (200);
 //   lB_ad->setMinimumSize (100,25);
  //  lE_ad->setMinimumSize (100,25);
    lB_aciklama->setMinimumSize (200,25);
   // lB_alacak->setMinimumSize (150,25);


    win_Grid->addWidget(lB_ad      , 0, 0, 1, 1);
    win_Grid->addWidget(lE_ad      , 0, 1, 1, 2);
    win_Grid->addWidget(lB_tarih     , 1, 0, 1, 1);
    win_Grid->addWidget(dE_tarih     , 1, 1, 1, 2);
    win_Grid->addWidget(lB_aciklama        , 2, 0, 1, 1);
    win_Grid->addWidget(lE_aciklama        , 2, 1, 1, 2);
    win_Grid->addWidget(lB_parabrm     , 3, 0, 1, 1);
    win_Grid->addWidget(cB_parabrm     , 3, 1, 1, 2);
    win_Grid->addWidget(lB_not     , 4, 0, 1, 1);
    win_Grid->addWidget(lE_not     , 4, 1, 1, 2);
    win_Grid->addWidget(lB_gizli      , 5, 0, 1, 1);
    win_Grid->addWidget(lE_gizli      , 5, 1, 1, 2);
    win_Grid->addWidget(lB_toplu    , 6, 0, 1, 1);
    win_Grid->addWidget(lE_toplu    , 6, 1, 1, 2);
    win_Grid->addWidget(lB_turu     , 7, 0, 1, 1);
    win_Grid->addWidget(cB_turu     , 7, 1, 1, 2);
    win_Grid->addWidget(lB_lft     , 8, 0, 1, 1);
    win_Grid->addWidget(lE_lft     , 8, 1, 1, 2);
    win_Grid->addWidget(lB_rgt     , 9, 0, 1, 1);
    win_Grid->addWidget(lE_rgt     , 9, 1, 1, 2);

    win_Grid->addWidget(win_Rsm       , 7, 4, 3, 2);

}

void hC_HSP::tbkntrl()
{

    qDebug() << "  hsp KNTRL";


    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id = maxID.hC_NrMax ( tb_name, tb_flds->value (0,0));
        ////////////////////////////////////////////////

        // table daki mevcut row detaylarını alalım

        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex indx = tb_view->table->currentIndex ();
        QString ino = tb_model->data
                (tb_model->index
                 (indx.row (),
                  tb_model->fieldIndex ("hsp_ad"))).toString ();
        QString lft = tb_model->data
                (tb_model->index
                (indx.row (),
                tb_model->fieldIndex ("hsp_lft"))).toString ();

        //s_qry = QString("DELETE FROM dbtb_mkn "
          //              "WHERE id_mkn = %1").arg( ino );

        //q_qry.exec (s_qry);

        qDebug()<< "hesap adı :" << ino << "left : " <<lft;

        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///

        lE_lft->setText( "1");
        lE_rgt->setText("2");

/*        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Hesap kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Hesap Kaydı eklendi ";
        rec.setValue ("hsp_lft"  , lE_lft->text ());
        rec.setValue ("hsp_rgt"  , lE_rgt->text ());
        tb_model->submitAll ();

        ////////////////////////////////////////////////
        /// son eklenen kayda git
        maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
        ////////////////////////////////////////////////
   */
        // yeni kaydı ekle
//#include <QDate>
        QSqlQuery q;
        QString qry, mesaj("");
        qry = "INSERT INTO " + *tb_name +
                " ( hsp_lft, hsp_rgt )"
                " values ( '1' ,'2' )";
                    //,"+ QDate(QDate::currentDate()).toString()   +" )" ;

        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "Hesap kaydı Eklenemedi xxxx"+
                    "<br>------------------------------------<br>"+
                    q.lastError().text ()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = mesaj + "Hesap kaydı eklendi.";

            ////////////////////////////////////////////////
            /// son eklenen kayda git
            maxID.hC_NrGo (tb_view, tb_model, *max_id , 0);
            ////////////////////////////////////////////////

            lE_lft -> setText ("");
            lE_rgt ->setText ("");
        }
        qDebug()<<mesaj;
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
            qDebug()<< "Silinecek row no: "<<sample.row();

            //         tb_view->table->selectionModel()->setCurrentIndex
            //             (sample,QItemSelectionModel::NoUpdate);

            QSqlRecord rec = tb_model->record();
            QString val = rec.value(rec.indexOf("hsp_ad")).toString();
            int lft = rec.value(rec.indexOf("hsp_lft")).toInt();

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
        if (!Index.isValid())
        {
            qDebug() <<"index is invalid - tb mappper setCureentModelIndex";
        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_HSP::sgn(tb_view->table->model()->index( Index.row() ,
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


void hC_HSP::showEvent(QShowEvent *)
{
    qDebug() << "Hesap dosyası açılıyor";
}


hC_HSP::~hC_HSP()
{
    qDebug() << "*********** destructor Hesap";
    //delete
}

