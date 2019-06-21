#include "tsnr.h"

hC_TSNR::hC_TSNR(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İş Emri Constructor";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_TSNR::tsnr_setup()
{
    qDebug() << "tsnr setup ";
    tsnr_VTd();
    tsnr_ui();

    TSNRmodel = new QSqlRelationalTableModel;
    tsnr_model( TSNRmodel ) ;

    tsnr_view();
    tsnr_map();
    tsnr_kntrl ();

}


void hC_TSNR::tsnr_ui()
{
    qDebug() << "  TSNR_ui";
    hC_TSNR::setWindowTitle ("TAŞINIR İSTEK");
    hC_TSNR::showMaximized ();
    auto *gLl = new QGridLayout(this);

    lB_rsm = new QLabel("Resim ");
    lB_tsnr = new QLabel("Taşınır İstek");

    // ///////////////////////////////////////////////////////
    // views
    TSNRtview = new hC_Tv;

    /////*******************************************////////

    QWidget *wdgt_TSekle = new QWidget;
    wdgt_TSekle->setWindowTitle("Taşınır Yeni Kayıt");
    wdgt_TSekle->setVisible(false);
    wdgt_TSekle->show();

    auto *TsL = new QGridLayout;
    wdgt_TSekle->setLayout(TsL);


    QLabel *lB_tsno = new QLabel("Taşınır No");
    TsL->addWidget(lB_tsno        ,0,0,1,1,nullptr);
    lE_TSno = new QLineEdit;
    lE_TSno->setText (*TSdetno);
    lE_TSno->setReadOnly (true);
    TsL->addWidget(lE_TSno   ,0,1,1,3,nullptr);
    lB_tsno->setBuddy(lE_TSno);

qDebug ()<<"ts 142";
    QLabel *lB_gt = new QLabel("Tarih");
    TsL->addWidget(lB_gt        ,1,0,1,1,nullptr);
    dE_TStarih = new QDateTimeEdit(QDate::currentDate());
    dE_TStarih->setDisplayFormat("dd.MM.yyyy");
    dE_TStarih->setMinimumDate(QDate(01, 01, 1900));
    dE_TStarih->setMaximumDate(QDate(valiDDate));
    dE_TStarih->setCalendarPopup(true);
    TsL->addWidget(dE_TStarih   ,1,1,1,3,nullptr);
    lB_gt->setBuddy(dE_TStarih);


    QLabel *lB_us = new QLabel("İstenen Malzeme Adı");
    TsL->addWidget(lB_us        ,2,0,1,1,nullptr);
    cbx_TSmalzeme = new QComboBox;                    //dbtb_TSNR
    TsL->addWidget(cbx_TSmalzeme   ,2,1,1,3,nullptr);
    lB_us->setBuddy(cbx_TSmalzeme);
    QPushButton *pb_TSNR = new QPushButton("+");
    TsL->addWidget(pb_TSNR   ,2,4,1,1,nullptr);
    connect (pb_TSNR, &QPushButton::clicked, this, &hC_TSNR::clk_tsnrdetTSNR);





qDebug ()<<"ts 143";


    QLabel *lB_tm = new QLabel("Miktar");
    TsL->addWidget(lB_tm        ,3,0,1,1,nullptr);
    lE_TSmiktar = new QLineEdit;
    QPushButton *pb_TSmk= new QPushButton("+");
    TsL->addWidget(lE_TSmiktar  ,3,1,1,3,nullptr);
    TsL->addWidget(pb_TSmk   ,3,4,1,1,nullptr);
    lB_tm->setBuddy(lE_TSmiktar );

qDebug ()<<"ts 143";
    QLabel *lB_usb = new QLabel("Birim");
    TsL->addWidget(lB_usb        ,4,0,1,1,nullptr);
    cbx_TSbirim = new QComboBox;                    //dbtb_TSNR
    TsL->addWidget(cbx_TSbirim   ,4,1,1,3,nullptr);
    lB_usb->setBuddy(cbx_TSbirim);
    QPushButton *pb_TSNR2 = new QPushButton("+");
    TsL->addWidget(pb_TSNR2   ,4,4,1,1,nullptr);
//    connect (pb_TSNR2, &QPushButton::clicked, this, &hC_TSNR::clk_tsnrdetTSNR);
qDebug ()<<"ts 143";
    QLabel *lB_bf = new QLabel("Birim Fiyat");
    TsL->addWidget(lB_bf        ,5,0,1,1,nullptr);
    lE_TSbfiyat = new QLineEdit;
    TsL->addWidget(lE_TSbfiyat   ,5,1,1,3,nullptr);
    lB_bf->setBuddy(lE_TSbfiyat);

qDebug ()<<"ts 144";
    QLabel *lB_dr = new QLabel("Durum");
    TsL->addWidget(lB_dr        ,6,0,1,1,nullptr);
    cbx_TSdurum = new QComboBox;                    // dbtb_durum
    cbx_TSdurum->addItem ("-");
    cbx_TSdurum->addItem ("Parça Bekliyor");
    cbx_TSdurum->addItem ("Usta Bekliyor");
    cbx_TSdurum->addItem ("Tamamlandı");
    TsL->addWidget(cbx_TSdurum   ,6,1,1,3,nullptr);
    lB_dr->setBuddy(cbx_TSdurum);
    QPushButton *pb_durum = new QPushButton("+");
    TsL->addWidget(pb_durum   ,6,4,1,1,nullptr);
  //  connect(pb_durum, &QPushButton::clicked, this, &hC_TSNR::clk_tsnrdetdurum);

    QLabel *lB_acklm = new QLabel("Açıklama");
    TsL->addWidget(lB_acklm        ,7,0,1,1,nullptr);
    lE_TSaciklama = new QLineEdit;
    TsL->addWidget(lE_TSaciklama   ,7,1,1,3,nullptr);
    lB_acklm->setBuddy(lE_TSaciklama);





    gLl->addWidget(TSNRtview->table,      0, 0, 1, 1 );
    gLl->addWidget(tsnrDETtvtsnrw,   0, 1, 1, 1 );
}

void hC_TSNR::tsnr_view()
{
    qDebug()<<"tsnr view ";
    TSNRtview->table->setModel(TSNRmodel);
    TSNRselectionMdl = TSNRtview->table->selectionModel();

    TSNRtview->table->setColumnHidden(TSNRmodel->fieldIndex("tsnr_mknstk_no"), true);
    TSNRtview->table->setColumnHidden(TSNRmodel->fieldIndex("id_tsnr"), true);
    TSNRtview->table->setColumnHidden(TSNRmodel->fieldIndex("tsnr_resim"), true);


    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    TSNRtview->table->setCurrentIndex(
                TSNRmodel->index(0, 1)
                );
    // with blue rect
    TSNRtview->table->setFocus();
    //   QTimer::singleShot(0, TSNRtview->table, SLOT(setFocus()));

}

/* user interface */
void hC_TSNR::tsnr_map()
{
    qDebug()<<"tsnr map ";
    TSNRmapper = new QDataWidgetMapper(this);
    TSNRmapper->setModel(TSNRmodel);

    //TSNRmodelapper->addMapping(TSNRmodelapper, mdl_mkn->fieldIndex("tsnr_mknstk_no"));
        TSNRmapper->addMapping(lE_TSno, TSNRmodel->fieldIndex("ts_no"));
        TSNRmapper->addMapping(dE_TStarih , TSNRmodel->fieldIndex("ts_tarih"));
        TSNRmapper->addMapping(cbx_TSmalzeme , TSNRmodel->fieldIndex("ts_malzeme"));
        TSNRmapper->addMapping(lE_TSmiktar, TSNRmodel->fieldIndex("ts_miktar"));
        TSNRmapper->addMapping(cbx_TSbirim , TSNRmodel->fieldIndex("ts_birim"));
        TSNRmapper->addMapping(lE_TSbfiyat, TSNRmodel->fieldIndex("ts_bfiyat"));
        TSNRmapper->addMapping(cbx_TSdurum, TSNRmodel->fieldIndex("ts_durum"));
        TSNRmapper->addMapping(lE_TSaciklama , TSmodel->fieldIndex("ts_aciklama"));


    qDebug()<<"TSNR view son";
    TSNRmapper->toFirst ();
}







void hC_TSNR::tsnr_kntrl()
{

    qDebug()<<"kontroltsnr ";

    // pB 001 yeni ekle
    connect(TSNRtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = TSNRmodel->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! TSNRmodel->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        TSNRmodel->select();
        qDebug ()<<"ts 17";
            ////////////////////////////////
        /*
        q.bindValue(0, *TSdet_idno  );
        q.bindValue(1, lE_TSno->text() );
        q.bindValue(2, dE_TStarih->text ());
        q.bindValue(3, cbx_TSmalzeme->currentText ());
        q.bindValue(4, lE_TSmiktar->text() );
        q.bindValue(5, cbx_TSbirim->currentText ());
        q.bindValue(6, lE_TSbfiyat->text() );
        q.bindValue(7, cbx_TSdurum->currentText ());
        q.bindValue(8, lE_TSaciklama->text() );
        */
        QSqlQuery q;
            QString q_s;
            q_s="INSERT INTO dbtb_tasinir ( "
                "ts_tsnrdet_id, ts_no    , ts_tarih, ts_malzeme , ts_miktar, "
                "ts_birim   , ts_bfiyat, ts_durum, ts_aciklama  "
                " )"
                " values(?, ?, ?, ?, ?, ?, ?, ?, ? )";
            q.prepare(q_s);


            qDebug ()<<"ts 17***** " <<  *TSdet_idno  << " *****" << q.lastError();


            q.bindValue(0, *TSdet_idno  );
            q.bindValue(1, lE_TSno->text() );
            q.bindValue(2, dE_TStarih->text ());
            q.bindValue(3, 0 );
            q.bindValue(4, 0 );
            q.bindValue(5, 0 );
            q.bindValue(6, 0 );
            q.bindValue(7, 0 );
            q.bindValue(8, "" );

            q.exec();
        qDebug ()<<"ts 18";
            if (q.isActive())
            {
                qDebug () <<"Taşınır Yeni Kayıt Eklendi - "<< lE_TSno->text() << " -   Eklendi";
            }
            else
            {
                qDebug () << "Taşınır Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
            }



            TSmodel->select();
            TStvtsnrw->setFocus();

            // tasinir ekle
            ///////////////////////////////////////////////////

        qDebug ()<<"ts 19";

    });

    // pB 002 yeni resim ekle
    connect(TSNRtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim(lB_rsm, TSNRtview, TSNRmodel, TSNRselectionMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  TSNRselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, TSNRtview, TSNRmodel, TSNRselectionMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(TSNRtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // tasinir  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("TAŞINIR KAYDI SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "Taşınır kaydı silinecek ;\n"
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            // şimdi taşınır silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex tasinir_indx = TStvtsnrw->currentIndex ();
            QString ino = TSmodel->data
                    (TSmodel->index
                     (tasinir_indx.row (),
                      TSmodel->fieldIndex ("id_tasinir"))).toString ();

            s_qry = QString("DELETE FROM dbtb_tasinir "
                            "WHERE id_tasinir = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " Taşınır Kaydı Silindi ";
                //  TSmodel->submitAll ();
                TSmodel->select ();
            }
            else
            {

                qDebug()<< " HATA - Taşınr Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
        }
        else if (msgBox.clickedButton() == pb_vzg)
        {
            msgBox.close(); // abort
        }
    });

    // pB 006 ilk
    connect(TSNRtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        TSNRtview->hC_TvPb ("ilk", TSNRmodel, TSNRmapper);
    });

    // pB 007 önceki
    connect(TSNRtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        TSNRtview->hC_TvPb ("ncki", TSNRmodel, TSNRmapper);
    });

    // pB 008 sonraki
    connect(TSNRtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
      TSNRtview->hC_TvPb ("snrki", TSNRmodel, TSNRmapper);
    });

    // pB 009 son
    connect(TSNRtview->pB_son, &QPushButton::clicked,
            [this]()
    {TSNRtview->hC_TvPb ("son", TSNRmodel, TSNRmapper);
    });



    // pB 010 nav tuslari kontrol
    connect(TSNRmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {TSNRtview->hC_TvPb ("yenile", TSNRmodel, TSNRmapper);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  TSNRselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        TSNRmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_TSNR::sgn(TSNRtview->table->model()->index( Index.row() ,
        //               TSNRmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  TSNRselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        TSNRmapper->setCurrentModelIndex(Index);
    });


}




void hC_TSNR::showEvent(QShowEvent *)
{
    qDebug() << "Personel dosyası açılıyor";
}


hC_TSNR::~hC_TSNR()
= default;



void hC_TSNR::tsnr_model()
{

    QString tableName = "tsnr__dbtb";
    QStringList ftsnrldList;

    ftsnrldList.append("İş Emri No");
    ftsnrldList.append("İş Emri Tarihi");
    ftsnrldList.append("Bölüm");
    ftsnrldList.append("Durum");
    ftsnrldList.append("Araç Giriş Tarihi");
    ftsnrldList.append("Araç Çıkış Tarihi");
    ftsnrldList.append("Yetkili");
    ftsnrldList.append("Yetkili");

}

