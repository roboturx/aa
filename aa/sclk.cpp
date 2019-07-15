#include "sclk.h"


hC_SCLK::hC_SCLK ( QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"cnstrctr İşçilik ";
    //************************************************************
    //*****************  İ Ş Ç İ L İ K  **************************
}

void hC_SCLK:: setup()
{
    qDebug() << "sclk setup ";

     wdgt();

     ui();

     kntrl ();
}


void hC_SCLK:: ui()
{
    qDebug() << "   ui";
    win_Label = new QLabel("İŞÇİLİK");
    hC_SCLK::setWindowTitle (win_Label->text ());
    //hC_SCLK::showMaximized ();


    // ///////////////////////////////////////////////////////

    // ///////////////////////////////////////////////////////
    // views
   // tb_view = new hC_Tv ( );

    /////*******************************************////////


    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget (tb_view  , 0, 0, 1, 1);
    winGrid->addWidget (win_Wdgt   , 0, 1, 1, 1);


}

void hC_SCLK:: wdgt()
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


    win_Rsm = new QLabel ("Resim");
    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

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

/*
void hC_SCLK:: view()
{
    qDebug()<<"sclk view ";
    tb_view->table->setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel();
    tb_view->table->setColumnHidden(
                tb_model->fieldIndex("id_iscilik"), true);
    tb_view->table->setColumnHidden(
                tb_model->fieldIndex("resim"), true);


    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    tb_view->table->setCurrentIndex(
                tb_model->index(0, 1)
                );
    // with blue rect
    tb_view->table->setFocus();
    //   QTimer::singleShot(0, tb_view->table, SLOT(setFocus()));

}


void hC_SCLK:: map()
{
    qDebug()<<"sclk map ";


    /// mapper iscilik
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);


    tb_mapper->addMapping(lE_SCno, tb_model->fieldIndex("SC_no"));
    tb_mapper->addMapping(dE_SCtarih , tb_model->fieldIndex("SC_tarih"));
    tb_mapper->addMapping(cbx_SCbirim , tb_model->fieldIndex("SC_birim"));
    tb_mapper->addMapping(cbx_SCusta, tb_model->fieldIndex("SC_usta"));

    tb_mapper->addMapping(lE_SCsaat , tb_model->fieldIndex("SC_saat"));
    tb_mapper->addMapping(lE_SCucret, tb_model->fieldIndex("SC_ucret"));
    tb_mapper->addMapping(cbx_SCucrettip, tb_model->fieldIndex("SC_ucrettip"));
    tb_mapper->addMapping(lE_SCaciklama , tb_model->fieldIndex("SC_aciklama"));

    tb_mapper->toFirst ();
}
*/

void hC_SCLK:: kntrl()
{


    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = tb_model->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        //dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        tb_model->select();


        qDebug ()<<"SC 17";
        ////////////////////////////////
        QSqlQuery q;
        QString q_s;
        q_s="INSERT INTO  _dbtb ( "
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



        tb_model->select();
        tb_view->table->setFocus();

        // işçilik ekle
        ///////////////////////////////////////////////////

        qDebug ()<<"SC 19";


    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tb_slctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
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
    /*
    // pB 006 ilk
    connect(tb_view->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        tb_view->hC_TvPb ("ilk", tb_model, tb_mapper);
    });

    // pB 007 önceki
    connect(tb_view->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("ncki", tb_model, tb_mapper);
    });

    // pB 008 sonraki
    connect(tb_view->pB_snrki, &QPushButton::clicked,
            [this]()
    {
      tb_view->hC_TvPb ("snrki", tb_model, tb_mapper);
    });

    // pB 009 son
    connect(tb_view->pB_son, &QPushButton::clicked,
            [this]()
    {tb_view->hC_TvPb ("son", tb_model, tb_mapper);
    });



    // pB 010 nav tuslari kontrol
    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);

    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  tb_slctnMdl ,
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
= default;

/*
QString hC_SCLK:: VTd ()
{
    QString ct,
            mesaj = "OK - İŞÇİLİK" ,
            tName = " _dbtb";
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




void hC_SCLK:: model()
{
    qDebug() << " sclk mdl";
    QString indexField = "sclk";
    QString tName (" _dbtb");
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

    tb_model = new QSqlRelationalTableModel;
  hC_Rm hC_Rm ( &tName,
                  tb_model,
                  &indexField ,
                  tFieldList) ;

} /// İŞÇİLİK MODEL
*/













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
