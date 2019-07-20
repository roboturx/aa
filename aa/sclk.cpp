#include "sclk.h"


hC_SCLK::hC_SCLK () :  hC_tBcreator  ()
{
    qDebug ()<<"Constructor İŞÇİLİK *********************************";
    //************************************************************
    //*****************  İ Ş Ç İ L İ K  **************************

    win_Label->setText ( "İŞÇİLİK KAYITLARI");
    *tb_name  = "sclk_dbtb" ;
    *tb_ndex  = "sclk_tarih";

    tb_flds = new hC_ArrD (10, 4);
    tb_flds->setValue ( 0, "sclk_ID"      , "INTEGER", "İşçilikID", "0" ) ;
    tb_flds->setValue ( 1, "sclk_iedet_id", "TEXT"   , "İEDetayID", "0" );
    tb_flds->setValue ( 2, "sclk_tarih"   , "TEXT"   , "Tarih" );
    tb_flds->setValue ( 3, "sclk_birim"   , "TEXT"   , "Birim");
    tb_flds->setValue ( 4, "sclk_usta"    , "TEXT"   , "Usta"   );
    tb_flds->setValue ( 5, "sclk_saat"    , "TEXT"   , "Saat"   );
    tb_flds->setValue ( 6, "sclk_ucret"   , "TEXT"   , "Ücret"    );
    tb_flds->setValue ( 7, "sclk_ucrettip", "TEXT"   , "Ücret Tipi"   );
    tb_flds->setValue ( 8, "sclk_aciklama", "TEXT"   , "Açıklama");
    tb_flds->setValue ( 9, "sclk_resim"   , "BLOB"   , "Resim");

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_SCno = new QLineEdit  ) ;
    tb_wdgts->append ( dE_SCtarih = new QDateTimeEdit( QDate::currentDate ()));
    tb_wdgts->append ( lE_SCbirim = new QLineEdit ) ;
    tb_wdgts->append ( lE_SCusta = new QLineEdit    ) ;
    tb_wdgts->append ( lE_SCsaat = new QLineEdit    ) ;
    tb_wdgts->append ( lE_SCucret = new QLineEdit     ) ;
    tb_wdgts->append ( cbx_SCucrettip = new QComboBox   ) ;
    tb_wdgts->append ( lE_SCaciklama = new QLineEdit    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;
}


void hC_SCLK::tbsetup()
{
    qDebug() << "   setup";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );
    tbwdgt  () ;
    tbui    () ;
    tbkntrl () ;



}



void hC_SCLK:: tbui()
{
    qDebug() << "   ui";
    hC_SCLK::setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_Grid->addWidget (win_Wdgt   , 0, 1, 1, 1);
}

void hC_SCLK:: tbwdgt()
{

    auto *lB_SCno = new QLabel("İşçilik No");

    lE_SCno->setText ("*iedetno");
    lE_SCno->setReadOnly (true);
    lB_SCno->setBuddy(lE_SCno);

    auto *lB_gt = new QLabel("Tarih");
    dE_SCtarih->setDisplayFormat("dd.MM.yyyy");
    dE_SCtarih->setMinimumDate(QDate(01, 01, 1900));
    dE_SCtarih->setMaximumDate(QDate(valiDDate));
    dE_SCtarih->setCalendarPopup(true);
    lB_gt->setBuddy(dE_SCtarih);

    auto *lB_usb2 = new QLabel("Birim");
    lB_usb2->setBuddy(lE_SCbirim);

    auto *lB_usb = new QLabel("Usta");
    lB_usb->setBuddy(lE_SCusta);

    auto *lB_tm = new QLabel("Saat");
    QPushButton *pb_SCmk= new QPushButton("+");
    lB_tm->setBuddy(lE_SCsaat );

    auto *lB_bf = new QLabel("Ücret");
    lB_bf->setBuddy(lE_SCucret);

    auto *lB_dr = new QLabel("Ücret Tipi");
    cbx_SCucrettip->addItem ("-");
    cbx_SCucrettip->addItem ("ücret tip 1");
    cbx_SCucrettip->addItem ("ücret tip 2");
    cbx_SCucrettip->addItem ("ücret tip 3");
    lB_dr->setBuddy(cbx_SCucrettip);

    auto *lB_acklm = new QLabel("Açıklama");
    lB_acklm->setBuddy(lE_SCaciklama);

    hC_Rs resim(win_Rsm);

    ///////////////////////////////////////
    
    win_Wdgt->adjustSize();
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_SCaciklama->setMinimumSize (200,25);



    wdgtGrid->addWidget(lB_SCno        ,0,0,1,1);
    wdgtGrid->addWidget(lE_SCno   ,0,1,1,3);
    wdgtGrid->addWidget(lB_gt        ,1,0,1,1);
    wdgtGrid->addWidget(dE_SCtarih   ,1,1,1,3);
    wdgtGrid->addWidget(lB_usb2        ,4,0,1,1);
    wdgtGrid->addWidget(lE_SCbirim   ,4,1,1,3);
    wdgtGrid->addWidget(lB_usb        ,4,0,1,1);//dbtb_SCLK
    wdgtGrid->addWidget(lE_SCusta   ,4,1,1,3);
    wdgtGrid->addWidget(lB_tm        ,3,0,1,1);
    wdgtGrid->addWidget(lE_SCsaat  ,3,1,1,3);
    wdgtGrid->addWidget(pb_SCmk   ,3,4,1,1);
    wdgtGrid->addWidget(lB_bf        ,5,0,1,1);
    wdgtGrid->addWidget(lE_SCucret   ,5,1,1,3);
    wdgtGrid->addWidget(lB_dr        ,6,0,1,1);
    wdgtGrid->addWidget(cbx_SCucrettip   ,6,1,1,3);
    wdgtGrid->addWidget(lB_acklm        ,7,0,1,1);
    wdgtGrid->addWidget(lE_SCaciklama   ,7,1,1,3);




}


void hC_SCLK:: tbkntrl()
{


    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id     = maxID.hC_NrMax ( tb_name,
                            tb_flds->value (0,0));
        ////////////////////////////////////////////////

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        //dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );

        QSqlQuery q;
        QString q_s;
        q_s="INSERT INTO  sclk_dbtb ( "
            "SC_iedet_id, SC_no    , SC_tarih, SC_birim , SC_usta, "
            "SC_saat   , SC_ucret, SC_ucrettip, SC_aciklama  "
            " )"
            " values(?, ?, ?, ?, ?, ?, ?, ?, ? )";
        q.prepare(q_s);


        q.bindValue(0, *max_id  );
        q.bindValue(1, lE_SCno->text() );
        q.bindValue(2, dE_SCtarih->text ());
        q.bindValue(3, lE_SCbirim->text ());
        q.bindValue(4, lE_SCusta->text() );
        q.bindValue(5, lE_SCsaat->text ());
        q.bindValue(6, lE_SCucret->text() );
        q.bindValue(7, cbx_SCucrettip->currentText ());
        q.bindValue(8, lE_SCaciklama->text() );

        q.exec();
        if (q.isActive())
        {
            qDebug () <<"İşçilik Yeni Kayıt Eklendi - "<< lE_SCno->text() << " -   Eklendi";

            ////////////////////////////////////////////////
            maxID.hC_NrGo (tb_view, *max_id , 0);
            ////////////////////////////////////////////////

        }
        else
        {
            qDebug () << "İşçilik Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
        }

        tb_model->select();
        tb_view->table->setFocus();
        // işçilik ekle
        ///////////////////////////////////////////////////
    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tbx_slctnMdl,
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
        // işçilik  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("İŞÇİİK KAYDI SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "İşçilik kaydı silinecek ;\n"
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            // şimdi işçilik silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex iscilik_indx = tb_view->table->currentIndex ();
            QString ino = tb_model->data (tb_model->index
                                           (iscilik_indx.row (), tb_model->fieldIndex
                                            ("id_iscilik"))).toString ();

            s_qry = QString("DELETE FROM  _dbtb "
                            "WHERE id_iscilik = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İşçilik Kaydı Silindi ";
                //  TSmodel->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - İşçilik Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
        }
        else if (msgBox.clickedButton() == pb_vzg)
        {
            msgBox.close(); // abort
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
        //     emit hC_SCLK::sgn(tb_view->table->model()->index( Index.row() ,
        //               tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });




    tb_view->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(tb_view, &QTableView::customContextMenuRequested,
            [this]()
    {

        //qDebug ()  <<"  cw iscilik view sağ tuş 001";
        auto *menuis = new QMenu(this);

        // iscilik ayar ekle
        const QIcon ekleIc_is = QIcon(":/rsm/Add.ico");
        QAction* ekleAct_is = new QAction(ekleIc_is, tr("İşçilik Ücretleri..."), this);
        ekleAct_is->setShortcuts (QKeySequence::New);
        ekleAct_is->setStatusTip ("İşçilik Ücretleri");
        connect (ekleAct_is, &QAction::triggered,
                 []()
        {
        });
        menuis->addAction(ekleAct_is);

        //            //  iscilik sil
        //            const QIcon silIc_ts = QIcon(":/rsm/Add.ico");
        //            QAction* silAct_ts = new QAction(silIc_ts, tr("Taşınır Sil..."), this);
        //            silAct_ts->setShortcuts (QKeySequence::New);
        //            silAct_ts->setStatusTip ("Taşınır Sil");
        //            connect (silAct_ts, &QAction::triggered, this,
        //                     &hC_SCLK::sil_ISCILIK );
        //            menuis->addAction(silAct_ts);
        menuis->popup(tb_view->table->viewport()->mapToGlobal(pos()));
    });
}


hC_SCLK::~hC_SCLK()
{
    qDebug() << "*********** destructor İŞÇİLİK";
}
