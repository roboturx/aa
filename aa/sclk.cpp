#include "sclk.h"


hC_SCLK::hC_SCLK ( QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"cnstrctr İşçilik ";
    //************************************************************
    //*****************  İ Ş Ç İ L İ K  **************************
}

void hC_SCLK::sclk_setup()
{
    qDebug() << "sclk setup ";
    sclk_VTd();
    sclk_model() ;
    sclk_wdgt();
    sclk_map();
    sclk_ui();
    sclk_view();
    sclk_kntrl ();
}


void hC_SCLK::sclk_ui()
{
    qDebug() << "  sclk_ui";
    winLabel = new QLabel("İŞÇİLİK");
    hC_SCLK::setWindowTitle (winLabel->text ());
    //hC_SCLK::showMaximized ();


    // ///////////////////////////////////////////////////////

    // ///////////////////////////////////////////////////////
    // views
    SCLKtview = new hC_Tv (SCLKmodel, SCLKmapper, winWdgt );

    /////*******************************************////////


    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget (SCLKtview  , 0, 0, 1, 1);
    winGrid->addWidget (winWdgt   , 0, 1, 1, 1);


}

void hC_SCLK::sclk_wdgt()
{

    auto *lB_SCno = new QLabel("İşçilik No");

    lE_SCno = new QLineEdit;
    lE_SCno->setText (*SCdetno);
    lE_SCno->setReadOnly (true);
    lB_SCno->setBuddy(lE_SCno);

    qDebug ()<<"SC 142";
    auto *lB_gt = new QLabel("Tarih");
    dE_SCtarih = new QDateTimeEdit(QDate::currentDate());
    dE_SCtarih->setDisplayFormat("dd.MM.yyyy");
    dE_SCtarih->setMinimumDate(QDate(01, 01, 1900));
    dE_SCtarih->setMaximumDate(QDate(valiDDate));
    dE_SCtarih->setCalendarPopup(true);
    lB_gt->setBuddy(dE_SCtarih);

    auto *lB_usb2 = new QLabel("Birim");
    cbx_SCbirim = new QComboBox;                    //dbtb_SCLK
    lB_usb2->setBuddy(cbx_SCbirim);

    auto *lB_usb = new QLabel("Usta");
    cbx_SCusta = new QComboBox;
    lB_usb->setBuddy(cbx_SCusta);

    auto *lB_tm = new QLabel("Saat");



    lE_SCsaat = new QLineEdit;
    QPushButton *pb_SCmk= new QPushButton("+");


    lB_tm->setBuddy(lE_SCsaat );

    auto *lB_bf = new QLabel("Ücret");

    lE_SCucret = new QLineEdit;
    lB_bf->setBuddy(lE_SCucret);

    auto *lB_dr = new QLabel("Ücret Tipi");

    cbx_SCucrettip = new QComboBox;                    // dbtb_durum
    cbx_SCucrettip->addItem ("-");
    cbx_SCucrettip->addItem ("ücret tip 1");
    cbx_SCucrettip->addItem ("ücret tip 2");
    cbx_SCucrettip->addItem ("ücret tip 3");
    lB_dr->setBuddy(cbx_SCucrettip);

    auto *lB_acklm = new QLabel("Açıklama");

    lE_SCaciklama = new QLineEdit;
    lB_acklm->setBuddy(lE_SCaciklama);


    winRsm = new QLabel ("Resim");
    hC_Rs resim(winRsm);


    ///////////////////////////////////////
    winWdgt = new QWidget;
    winWdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    winWdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_SCaciklama->setMinimumSize (200,25);



    wdgtGrid->addWidget(lB_SCno        ,0,0,1,1);
    wdgtGrid->addWidget(lE_SCno   ,0,1,1,3);
    wdgtGrid->addWidget(lB_gt        ,1,0,1,1);
    wdgtGrid->addWidget(dE_SCtarih   ,1,1,1,3);
    wdgtGrid->addWidget(lB_usb2        ,4,0,1,1);
    wdgtGrid->addWidget(cbx_SCbirim   ,4,1,1,3);
    wdgtGrid->addWidget(lB_usb        ,4,0,1,1);//dbtb_SCLK
    wdgtGrid->addWidget(cbx_SCusta   ,4,1,1,3);
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


void hC_SCLK::sclk_view()
{
    qDebug()<<"sclk view ";
    SCLKtview->table->setModel(SCLKmodel);
    SCLKslctnMdl = SCLKtview->table->selectionModel();
    SCLKtview->table->setColumnHidden(
                SCLKmodel->fieldIndex("id_iscilik"), true);
    SCLKtview->table->setColumnHidden(
                SCLKmodel->fieldIndex("resim"), true);


    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    SCLKtview->table->setCurrentIndex(
                SCLKmodel->index(0, 1)
                );
    // with blue rect
    SCLKtview->table->setFocus();
    //   QTimer::singleShot(0, SCLKtview->table, SLOT(setFocus()));

}


void hC_SCLK::sclk_map()
{
    qDebug()<<"sclk map ";


    /// mapper iscilik
    SCLKmapper = new QDataWidgetMapper(this);
    SCLKmapper->setModel(SCLKmodel);


    SCLKmapper->addMapping(lE_SCno, SCLKmodel->fieldIndex("SC_no"));
    SCLKmapper->addMapping(dE_SCtarih , SCLKmodel->fieldIndex("SC_tarih"));
    SCLKmapper->addMapping(cbx_SCbirim , SCLKmodel->fieldIndex("SC_birim"));
    SCLKmapper->addMapping(cbx_SCusta, SCLKmodel->fieldIndex("SC_usta"));

    SCLKmapper->addMapping(lE_SCsaat , SCLKmodel->fieldIndex("SC_saat"));
    SCLKmapper->addMapping(lE_SCucret, SCLKmodel->fieldIndex("SC_ucret"));
    SCLKmapper->addMapping(cbx_SCucrettip, SCLKmodel->fieldIndex("SC_ucrettip"));
    SCLKmapper->addMapping(lE_SCaciklama , SCLKmodel->fieldIndex("SC_aciklama"));

    SCLKmapper->toFirst ();
}


void hC_SCLK::sclk_kntrl()
{


    // pB 001 yeni ekle
    connect(SCLKtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = SCLKmodel->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        //dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! SCLKmodel->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        SCLKmodel->select();


        qDebug ()<<"SC 17";
        ////////////////////////////////
        QSqlQuery q;
        QString q_s;
        q_s="INSERT INTO sclk__dbtb ( "
            "SC_iedet_id, SC_no    , SC_tarih, SC_birim , SC_usta, "
            "SC_saat   , SC_ucret, SC_ucrettip, SC_aciklama  "
            " )"
            " values(?, ?, ?, ?, ?, ?, ?, ?, ? )";
        q.prepare(q_s);


        qDebug ()<<"SC 17***** " <<  *SCdet_idno  << " *****" << q.lastError();
        q.bindValue(0, *SCdet_idno  );
        q.bindValue(1, lE_SCno->text() );
        q.bindValue(2, dE_SCtarih->text ());
        q.bindValue(3, cbx_SCbirim->currentText ());
        q.bindValue(4, cbx_SCusta->currentText() );
        q.bindValue(5, lE_SCsaat->text ());
        q.bindValue(6, lE_SCucret->text() );
        q.bindValue(7, cbx_SCucrettip->currentText ());
        q.bindValue(8, lE_SCaciklama->text() );

        q.exec();
        qDebug ()<<"SC 18";
        if (q.isActive())
        {
            qDebug () <<"İşçilik Yeni Kayıt Eklendi - "<< lE_SCno->text() << " -   Eklendi";
        }
        else
        {
            qDebug () << "İşçilik Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
        }



        SCLKmodel->select();
        SCLKtview->table->setFocus();

        // işçilik ekle
        ///////////////////////////////////////////////////

        qDebug ()<<"SC 19";


    });

    // pB 002 yeni resim ekle
    connect(SCLKtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(winRsm, SCLKtview, SCLKmodel, SCLKslctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  SCLKslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( winRsm, SCLKtview, SCLKmodel, SCLKslctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(SCLKtview->pB_sil, &QPushButton::clicked,
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
            QModelIndex iscilik_indx = SCLKtview->table->currentIndex ();
            QString ino = SCLKmodel->data (SCLKmodel->index
                                           (iscilik_indx.row (), SCLKmodel->fieldIndex
                                            ("id_iscilik"))).toString ();

            s_qry = QString("DELETE FROM sclk__dbtb "
                            "WHERE id_iscilik = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İşçilik Kaydı Silindi ";
                //  TSmodel->submitAll ();
                SCLKmodel->select ();
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
    /*
    // pB 006 ilk
    connect(SCLKtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        SCLKtview->hC_TvPb ("ilk", SCLKmodel, SCLKmapper);
    });

    // pB 007 önceki
    connect(SCLKtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        SCLKtview->hC_TvPb ("ncki", SCLKmodel, SCLKmapper);
    });

    // pB 008 sonraki
    connect(SCLKtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
      SCLKtview->hC_TvPb ("snrki", SCLKmodel, SCLKmapper);
    });

    // pB 009 son
    connect(SCLKtview->pB_son, &QPushButton::clicked,
            [this]()
    {SCLKtview->hC_TvPb ("son", SCLKmodel, SCLKmapper);
    });



    // pB 010 nav tuslari kontrol
    connect(SCLKmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {SCLKtview->hC_TvPb ("yenile", SCLKmodel, SCLKmapper);

    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  SCLKslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        SCLKmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_SCLK::sgn(SCLKtview->table->model()->index( Index.row() ,
        //               SCLKmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  SCLKslctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        SCLKmapper->setCurrentModelIndex(Index);
    });




    SCLKtview->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(SCLKtview, &QTableView::customContextMenuRequested,
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

        menuis->popup(SCLKtview->table->viewport()->mapToGlobal(pos()));


    });
}



hC_SCLK::~hC_SCLK()
= default;


QString hC_SCLK::sclk_VTd ()
{
    QString ct,
            mesaj = "OK - İŞÇİLİK" ,
            tName = "sclk__dbtb";
    QStringList inserts;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( tName ))
    {
        ct ="CREATE TABLE IF NOT EXISTS " + tName +
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
            mesaj = "<br>HATA - İşçilik Dosyası Oluşturulamadı  "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - İşçilik Dosyası YENİ Oluşturuldu ";
            inserts << "INSERT INTO dbtb_iscilik ( mknstk_no,iedet_no,is_no )"
                       " values( 1,1,1 )" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {
                    mesaj = mesaj + "<br>İLK İşçilik Kaydı Eklenemdi"+
                            "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else
                {
                    mesaj = mesaj + "<br>İLK İşçilik kaydı eklendi.";
                }
            } // foreach
        }
    }
    qDebug ()<< mesaj;
    return mesaj ;


} //ISCILIK




void hC_SCLK::sclk_model()
{
    qDebug() << " sclk mdl";
    QString indexField = "sclk";
    QString tName ("sclk__dbtb");
    QStringList *tFieldList = new QStringList ;
    tFieldList->append("IEDET-SCLK ID ");
    tFieldList->append("İşçilik No");
    tFieldList->append("Tarih");
    tFieldList->append("Birim");
    tFieldList->append("Usta");
    tFieldList->append("Saat");
    tFieldList->append("Ücret");
    tFieldList->append("Ücret Tipi");
    tFieldList->append("Açıklama");
    tFieldList->append("Resim");
    tFieldList->append("İŞÇİLİK-ID");

    SCLKmodel = new QSqlRelationalTableModel;
    hC_Rm hC_Rm ( &tName,
                  SCLKmodel,
                  &indexField ,
                  tFieldList) ;

} /// İŞÇİLİK MODEL














//    qDebug ()<<"SC 1";
//    SCno = new QString;
//    SCdet_idno = new QString;
//    *SCdet_idno="-1";
//    //QSqlQuery q;
//    //QVariant ino = " " ;
//    QModelIndex index = IEDETtview->currentIndex();
//    if (index.isValid())
//    {
//        // tv index i ile model de recordu bulduk
//        QSqlRecord record = IEDETmodel->record(index.row());
//        *SCno = record.value("ie_iedet_no").toString();
//        *SCdet_idno = record.value("id_IEdet").toString();
//        qDebug ()<<"SC 12 ---- SCdfetidno --- "<< * SCdet_idno;
//    }
//    else
//    {
//        QMessageBox msgBox;
//        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
//        msgBox.setWindowTitle("İŞÇİLİK KAYIT EKLEME HATASI                               -");
//        msgBox.setText("İşçilik kaydı \n"
//                       "Kayıt Eklenemedi ...");
//        msgBox.setInformativeText("SCtview index is invalid");        msgBox.exec();
//        if (msgBox.clickedButton() == pb_tmm)
//        {
//            return;
//        }
//    }


//    // IEdet_no yu oluşturalım
//    // ioi_no + hangi yıl + yılın kaçıncı günündeyiz
//    QString SCdet = *SCno;
//    SCdet.append(":");
//    SCdetno = new QString;
//    *SCdetno = SCdet ;
//    int sccount = 1;

//    qDebug ()<< "sccount :" << sccount ;

//    // how mny-- records?
//    QSqlQuery query;
//    query.prepare("SELECT * FROM dbtb_iscilik ");
//    if (!query.exec())
//    {
//        qDebug() << "SQL error: "<< query.lastError().text() << endl;
//    }
//    else
//    {

//        QString lttl ="" ;
//        query.first();
//        while (query.next())
//        {
//            lttl= query.value("SC_no").toString();
//            lttl.chop(3) ;
//            qDebug ()<< "sccount :" << sccount ;
//            if (lttl == *SCno)
//            {
//                sccount++;
//                qDebug ()<< "sccount --- :" << sccount ;
//            }
//        }
//    }
//    ///// yeni SC iedetno son hali
//    *SCdetno += "0"+QString::number(sccount);
