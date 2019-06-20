#include "sclk.h"


hC_SCLK::hC_SCLK ( QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İşçilik Constructor";
    //************************************************************
    //*****************  İ Ş Ç İ L İ K  **************************
}

void hC_SCLK::sclk_setup()
{
    qDebug() << "sclk setup ";
    sclk_VTd();
    sclk_ui();

    SCLKmodel = new QSqlRelationalTableModel;
    sclk_model( SCLKmodel ) ;

    sclk_view();
    sclk_map();
    sclk_kntrl ();

}


void hC_SCLK::sclk_ui()
{
    qDebug() << "  sclk_ui";
    hC_SCLK::setWindowTitle ("İŞÇİLİK");
    hC_SCLK::showMaximized ();


    // ///////////////////////////////////////////////////////

    lB_sclk  = new QLabel ("İşçilik");
    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);

    // ///////////////////////////////////////////////////////
    // views
    SCLKtview = new hC_Tv();

    /////*******************************************////////


    auto *gLl = new QGridLayout(this);

    gLl->addWidget(SCLKtview->table,      0, 0, 1, 1 );
    gLl->addWidget(SCLKtview,   0, 1, 1, 1 );
}


void hC_SCLK::sclk_view()
{
    qDebug()<<"sclk view ";
    SCLKtview->table->setModel(SCLKmodel);
    SCLKselectionMdl = SCLKtview->table->selectionModel();
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
    //   QTimer::singleShot(0, CLSNtview->table, SLOT(setFocus()));

}


void hC_SCLK::sclk_map()
{
    qDebug()<<"sclk map ";


    /// mapper iscilik
    SCLKmapper = new QDataWidgetMapper(this);
    SCLKmapper->setModel(SCLKmodel);

    SCLKmapper->addMapping (lB_rsm, SCLKmodel->fieldIndex("resim"));
    qDebug()<<"clsn view son";
    SCLKmapper->toFirst ();
}

void hC_SCLK::sclk_kntrl()
{
    SCLKtview->setContextMenuPolicy(Qt::CustomContextMenu);

    /// ie sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim

    bool sccs (true);
    sccs = connect(SCLKtview, &QTableView::customContextMenuRequested,this,
                   &hC_SCLK::rightMenu_ISCILIK);
    if (! sccs)
    {
        qDebug()<<"HATA - IŞCİLİK Right Menu Connection";
    }
    else
    {
        qDebug()<<"IŞÇİLİK Right Menu Connected";
    }

    qDebug()<<"iscilik view sonu";
}








//////////////////////////////////////////////////////////////////
void hC_SCLK::rightMenu_ISCILIK(QPoint pos)
{
    //qDebug ()  <<"  cw iscilik view sağ tuş 001";
    auto *menuis = new QMenu(this);

    // iscilik ayar ekle
    const QIcon ekleIc_is = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_is = new QAction(ekleIc_is, tr("İşçilik Ücretleri..."), this);
    ekleAct_is->setShortcuts (QKeySequence::New);
    ekleAct_is->setStatusTip ("İşçilik Ücretleri");
    connect (ekleAct_is, &QAction::triggered, this,
             &hC_SCLK::ayar_ISCILIK );
    menuis->addAction(ekleAct_is);

    //  iscilik sil
    const QIcon silIc_ts = QIcon(":/rsm/Add.ico");
    QAction* silAct_ts = new QAction(silIc_ts, tr("Taşınır Sil..."), this);
    silAct_ts->setShortcuts (QKeySequence::New);
    silAct_ts->setStatusTip ("Taşınır Sil");
    connect (silAct_ts, &QAction::triggered, this,
             &hC_SCLK::sil_ISCILIK );
    menuis->addAction(silAct_ts);

    menuis->popup(SCLKtview->table->viewport()->mapToGlobal(pos));
}


void hC_SCLK::onmnIEDET_SCekle()
{
    qDebug ()<<"SC 1";
    SCno = new QString;
    SCdet_idno = new QString;
    *SCdet_idno="-1";
    //QSqlQuery q;
    //QVariant ino = " " ;
    QModelIndex index = IEDETtview->currentIndex();
    if (index.isValid())
    {
        // tv index i ile model de recordu bulduk
        QSqlRecord record = IEDETmodel->record(index.row());
        *SCno = record.value("ie_iedet_no").toString();
        *SCdet_idno = record.value("id_IEdet").toString();
        qDebug ()<<"SC 12 ---- SCdfetidno --- "<< * SCdet_idno;
    }
    else
    {
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
        msgBox.setWindowTitle("İŞÇİLİK KAYIT EKLEME HATASI                               -");
        msgBox.setText("İşçilik kaydı \n"
                       "Kayıt Eklenemedi ...");
        msgBox.setInformativeText("SCtview index is invalid");        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {
            return;
        }
    }


    // IEdet_no yu oluşturalım
    // ioi_no + hangi yıl + yılın kaçıncı günündeyiz
    QString SCdet = *SCno;
    SCdet.append(":");
    SCdetno = new QString;
    *SCdetno = SCdet ;
    int sccount = 1;

    qDebug ()<< "sccount :" << sccount ;

    // how mny-- records?
    QSqlQuery query;
    query.prepare("SELECT * FROM dbtb_iscilik ");
    if (!query.exec())
    {
        qDebug() << "SQL error: "<< query.lastError().text() << endl;
    }
    else
    {

        QString lttl ="" ;
        query.first();
        while (query.next())
        {
            lttl= query.value("SC_no").toString();
            lttl.chop(3) ;
            qDebug ()<< "sccount :" << sccount ;
            if (lttl == *SCno)
            {
                sccount++;
                qDebug ()<< "sccount --- :" << sccount ;
            }
        }
    }
    ///// yeni SC iedetno son hali
    *SCdetno += "0"+QString::number(sccount);
    QWidget *wdgt_SCekle = new QWidget;
    wdgt_SCekle->setWindowTitle("İşçilik Yeni Kayıt");
    wdgt_SCekle->setVisible(false);
    wdgt_SCekle->show();

    auto *SCL = new QGridLayout;
    wdgt_SCekle->setLayout(SCL);


    QLabel *lB_SCno = new QLabel("İşçilik No");
    SCL->addWidget(lB_SCno        ,0,0,1,1,nullptr);
    lE_SCno = new QLineEdit;
    lE_SCno->setText (*SCdetno);
    lE_SCno->setReadOnly (true);
    SCL->addWidget(lE_SCno   ,0,1,1,3,nullptr);
    lB_SCno->setBuddy(lE_SCno);

    qDebug ()<<"SC 142";
    QLabel *lB_gt = new QLabel("Tarih");
    SCL->addWidget(lB_gt        ,1,0,1,1,nullptr);
    dE_SCtarih = new QDateTimeEdit(QDate::currentDate());
    dE_SCtarih->setDisplayFormat("dd.MM.yyyy");
    dE_SCtarih->setMinimumDate(QDate(01, 01, 1900));
    dE_SCtarih->setMaximumDate(QDate(valiDDate));
    dE_SCtarih->setCalendarPopup(true);
    SCL->addWidget(dE_SCtarih   ,1,1,1,3,nullptr);
    lB_gt->setBuddy(dE_SCtarih);

    QLabel *lB_usb2 = new QLabel("Birim");
    SCL->addWidget(lB_usb2        ,4,0,1,1,nullptr);
    cbx_SCbirim = new QComboBox;                    //dbtb_clsn
    SCL->addWidget(cbx_SCbirim   ,4,1,1,3,nullptr);
    lB_usb2->setBuddy(cbx_SCbirim);
    QPushButton *pb_clsn2 = new QPushButton("+");
    SCL->addWidget(pb_clsn2   ,4,4,1,1,nullptr);
    connect (pb_clsn2, &QPushButton::clicked, this, &hC_IE::clk_IEdetclsn);

    QLabel *lB_usb = new QLabel("Usta");
    SCL->addWidget(lB_usb        ,4,0,1,1,nullptr);
    cbx_SCusta = new QComboBox;                    //dbtb_clsn
    SCL->addWidget(cbx_SCusta   ,4,1,1,3,nullptr);
    lB_usb->setBuddy(cbx_SCusta);
    QPushButton *pb_cl2 = new QPushButton("+");
    SCL->addWidget(pb_cl2   ,4,4,1,1,nullptr);
    connect (pb_cl2, &QPushButton::clicked, this, &hC_IE::clk_IEdetclsn);










    QLabel *lB_tm = new QLabel("Saat");
    SCL->addWidget(lB_tm        ,3,0,1,1,nullptr);
    lE_SCsaat = new QLineEdit;
    QPushButton *pb_SCmk= new QPushButton("+");
    SCL->addWidget(lE_SCsaat  ,3,1,1,3,nullptr);
    SCL->addWidget(pb_SCmk   ,3,4,1,1,nullptr);
    lB_tm->setBuddy(lE_SCsaat );

    QLabel *lB_bf = new QLabel("Ücret");
    SCL->addWidget(lB_bf        ,5,0,1,1,nullptr);
    lE_SCucret = new QLineEdit;
    SCL->addWidget(lE_SCucret   ,5,1,1,3,nullptr);
    lB_bf->setBuddy(lE_SCucret);


    qDebug ()<<"SC 144";
    QLabel *lB_dr = new QLabel("Ücret Tipi");
    SCL->addWidget(lB_dr        ,6,0,1,1,nullptr);
    cbx_SCucrettip = new QComboBox;                    // dbtb_durum
    cbx_SCucrettip->addItem ("-");
    cbx_SCucrettip->addItem ("ücret tip 1");
    cbx_SCucrettip->addItem ("ücret tip 2");
    cbx_SCucrettip->addItem ("ücret tip 3");
    SCL->addWidget(cbx_SCucrettip   ,6,1,1,3,nullptr);
    lB_dr->setBuddy(cbx_SCucrettip);
    QPushButton *pb_utip = new QPushButton("+");
    SCL->addWidget(pb_utip   ,6,4,1,1,nullptr);
    connect(pb_utip, &QPushButton::clicked, this, &hC_IE::clk_IEdetdurum);

    QLabel *lB_acklm = new QLabel("Açıklama");
    SCL->addWidget(lB_acklm        ,7,0,1,1,nullptr);
    lE_SCaciklama = new QLineEdit;
    SCL->addWidget(lE_SCaciklama   ,7,1,1,3,nullptr);
    lB_acklm->setBuddy(lE_SCaciklama);

    qDebug ()<<"SC 145";

    //QLabel *lB_rsm = new QLabel("Resim");


    QPushButton *pb_kaydet = new QPushButton("Yeni Ekle");
    connect (pb_kaydet, &QPushButton::clicked,
             this, & hC_IE::clk_SCbosh );
    SCL->addWidget(pb_kaydet        ,10,5,1,1,nullptr);

    QPushButton *SCtview = new QPushButton("Vazgeç");
    connect (SCtview, &QPushButton::clicked, wdgt_SCekle, &QWidget::close );
    SCL->addWidget(SCtview        ,10,3,1,1,nullptr);



    qDebug ()<<"SC 146";
    //IEmapper->addMapping(IEmapper, mdl_mkn->fieldIndex("ie_mknstk_no"));
    SCmapper->addMapping(lE_SCno, SCmodel->fieldIndex("SC_no"));
    qDebug ()<<"SC 146";
    SCmapper->addMapping(dE_SCtarih , SCmodel->fieldIndex("SC_tarih"));
    SCmapper->addMapping(cbx_SCbirim , SCmodel->fieldIndex("SC_birim"));
    SCmapper->addMapping(cbx_SCusta, SCmodel->fieldIndex("SC_usta"));

    SCmapper->addMapping(lE_SCsaat , SCmodel->fieldIndex("SC_saat"));
    qDebug ()<<"SC 1462";
    SCmapper->addMapping(lE_SCucret, SCmodel->fieldIndex("SC_ucret"));
    qDebug ()<<"SC 146";
    SCmapper->addMapping(cbx_SCucrettip, SCmodel->fieldIndex("SC_ucrettip"));
    SCmapper->addMapping(lE_SCaciklama , SCmodel->fieldIndex("SC_aciklama"));

    qDebug ()<<"SC 15";
    //        IEmapper->addMapping(cbx_ykt, mdl_mkn->fieldIndex("ie_resim"));


    QPushButton *pb_ilk = new QPushButton("İlk");
    connect( pb_ilk, &QPushButton::clicked,
             SCmapper, &QDataWidgetMapper::toFirst );
    SCL->addWidget( pb_ilk   ,10,1,1,1,nullptr);

    QPushButton *pb_pr = new QPushButton("Önceki");
    connect( pb_pr, &QPushButton::clicked,
             SCmapper, &QDataWidgetMapper::toPrevious );
    SCL->addWidget( pb_pr   ,10,2,1,1,nullptr);

    QPushButton *pb_lr = new QPushButton("Sonraki");
    connect( pb_lr, &QPushButton::clicked,
             SCmapper, &QDataWidgetMapper::toNext );
    SCL->addWidget( pb_lr   ,10,3,1,1,nullptr);

    QPushButton *pb_ls = new QPushButton("Son");
    connect( pb_ls, &QPushButton::clicked,
             SCmapper, &QDataWidgetMapper::toLast );
    SCL->addWidget( pb_ls   ,10,4,1,1,nullptr);


}


void hC_SCLK::clk_SCbosh()
{
    /// yeni IE iş emri detay kaydı için
    /// sahaları boşaltalım

    qDebug ()<<"SC 16";
    lE_SCno->setText( *SCdetno) ;
    dE_SCtarih->setDate(QDate::currentDate());
    cbx_SCbirim->setCurrentText ("");
    cbx_SCusta->setCurrentText ("");
    lE_SCsaat->setText ("");
    lE_SCucret->setText ("");
    cbx_SCucrettip->setCurrentText ("");
    lE_SCaciklama->setText ("");


    hC_IE::SCekle();

}




void hC_SCLK::SCekle()
{
    qDebug ()<<"SC 17";
    ////////////////////////////////
    QSqlQuery q;
    QString q_s;
    q_s="INSERT INTO dbtb_iscilik ( "
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
        qDebug () <<"Taşınır Yeni Kayıt Eklendi - "<< lE_SCno->text() << " -   Eklendi";
    }
    else
    {
        qDebug () << "Taşınır Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
    }



    SCmodel->select();
    SCtview->setFocus();

    // işçilik ekle
    ///////////////////////////////////////////////////

    qDebug ()<<"SC 19";

}




hC_SCLK::~hC_SCLK()
= default;




void hC_SCLK::sil_ISCILIK()
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
        QModelIndex iscilik_indx = SCtview->currentIndex ();
        QString ino = SCmodel->data
                (SCmodel->index
                 (iscilik_indx.row (),
                  TSmodel->fieldIndex ("id_iscilik"))).toString ();

        s_qry = QString("DELETE FROM dbtb_iscilik "
                        "WHERE id_iscilik = %1").arg( ino );

        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            qDebug()<< " İşçilik Kaydı Silindi ";
            //  TSmodel->submitAll ();
            TSmodel->select ();
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

}





///// SLOTS
///
///
///
///
/// AYAR



void hC_SCLK::ayar_ISCILIK()
{

}       ///      AYAR işçilik


