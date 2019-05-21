#include "cw_isemri.h"
#include "globals.h"

/////////////////////////////////////////////////
///
/// iş emri
///




Cw_IsEmri::Cw_IsEmri(QWidget *parent) : QWidget (parent)
{
    //qDebug ()  <<" 'İş Emri   ' - İş Emri Başlatıldı ";
    setup_ui();
 //   setup_uidet();

    model_IE();
    view_IE();

    model_IEDET();
    view_IEDET();

    model_TASINIR();
    view_TASINIR();

    model_ISCILIK();
    view_ISCILIK();

    kontrolIE();
}

void Cw_IsEmri::kontrolIE()
{
    /// iş emri ekran kontrolleri
    ///


    qDebug()<<"kontrolie";

    connect(IEtview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_IE(QModelIndex)));

    ///
    connect(IEDETtview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_IEDET(QModelIndex)));

    /// ie column değiştiğinde modelindex de değişsin
       connect(IEtview->selectionModel(),
            SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
            IEmapper, SLOT(setCurrentModelIndex(QModelIndex)));

    /// ie row değiştiğinde modelindex de değişsin
    connect(IEtview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            IEmapper, SLOT(setCurrentModelIndex(QModelIndex)));

/*    // ie - iedet set filter
    connect(TStview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_TASINIR(QModelIndex)));

    // ie - iedet set filter
    connect(SCtview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_ISCILIK (QModelIndex)));

*/
    qDebug()<<"kontrolie sonu";
}



//////////////////////////////////
///
/// İŞ EMRİ
///
///
/// MODEL
/// VIEW


void Cw_IsEmri::model_IE()
{

    QString tableName = "dbtb_ie";
    QStringList fieldList;

    fieldList.append("İş Emri No");
    fieldList.append("İş Emri Tarihi");
    fieldList.append("Bölüm");
    fieldList.append("Durum");
    fieldList.append("Araç Giriş Tarihi");
    fieldList.append("Araç Çıkış Tarihi");
    fieldList.append("Yetkili");
    fieldList.append("Yetkili");


    IEmodel = new QSqlRelationalTableModel();
    IEmodel->setTable(tableName);
    IEmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    IEmodel->setSort(IEmodel->fieldIndex ("ie_tarih"),Qt::DescendingOrder );

    ////  kolon başlıkları

    for(int i = 1, j = 0; i < IEmodel->columnCount()-2; i++, j++)
    {
        IEmodel->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }


    // Populate the model_mkstok
    if (!IEmodel->select())
    {
        qDebug () << IEmodel->lastError();
    }
}

void Cw_IsEmri::view_IE()
{
    IEtview->setModel(IEmodel);
    IEtview->resizeColumnsToContents();
    IEtview->resizeRowsToContents();

    /// tV için selection model  oluştur
    /// bu view de seçileni belirlemede kullanılır
    /// selection ve current index ayrı şeyler
    ///
    IEtV_selectionMdl = new QItemSelectionModel(IEmodel);
    IEtview->setSelectionModel (IEtV_selectionMdl);

    IEtview->setSelectionMode(QAbstractItemView::SingleSelection);
    IEtview->setSelectionBehavior(QAbstractItemView::SelectItems);
    //IEtview->setCurrentIndex(IEmodel->index(0,0));

    //// kullanıcı bu alanları görmesin
    IEtview->setColumnHidden(IEmodel->fieldIndex("ie_mknstk_no"), true);
    IEtview->setColumnHidden(IEmodel->fieldIndex("id_IE"), true);
    IEtview->setColumnHidden(IEmodel->fieldIndex("ie_resim"), true);

    IEtview->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    IEtview->horizontalHeader()->setStretchLastSection(true);
    IEtview->horizontalHeader()->resizeContentsPrecision();

    ///// tableview kontrol connectleri
    ///
    ///
    ///
/*    (connect(IEtview->pB_ekle, &QPushButton::clicked ,this ,
                     &Cw_Ambar::slt_dp_pB_EKLE_clicked  )) ;
    (connect(IEtview->pB_eklersm, &QPushButton::clicked,this ,
                     &Cw_Ambar::slt_dp_pB_Eklersm_clicked  )) ;

    (connect(IEtview->pB_sil, &QPushButton::clicked,this ,
                     &Cw_Ambar::slt_dp_pB_SIL_clicked )) ;
    (connect(IEtview->pB_ilk, &QPushButton::clicked ,this ,
                     &Cw_Ambar::slt_dp_toFirst )) ;
    (connect(IEtview->pB_ncki, &QPushButton::clicked,this ,
                     &Cw_Ambar::slt_dp_toPrevious )) ;
    (connect(IEtview->pB_snrki, &QPushButton::clicked,this ,
                     &Cw_Ambar::slt_dp_toNext )) ;
    (connect(IEtview->pB_son, &QPushButton::clicked,this ,
                     &Cw_Ambar::slt_dp_toLast )) ;

    IEtview->pB_grscks->setVisible (false);
    (connect(IEtview->pB_grscks, &QPushButton::clicked,this ,
                     &Cw_IE::slt_dp_cX_grs_clicked  )) ;
  */

    /// mapper IE
    IEmapper = new QDataWidgetMapper(this);
    IEmapper->setModel(IEmodel);
    // mppMKN->setItemDelegate(new IEDelegate(this));
    IEmodel->select();
    IEtview->setContextMenuPolicy(Qt::CustomContextMenu);

    /// ie sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim

    bool sccs (true);
    sccs = connect(IEtview, &QTableView::customContextMenuRequested,this,
                   &Cw_IsEmri::rightMenu_IE);
    if (! sccs)
    {
        qDebug()<<"HATA - IE Right Menu Connection";
    }
    else
    {
        qDebug()<<"IE Right Menu Connected";
    }

}



//////////////////////////////////
///
/// İŞ EMRİ DETAY
///
///
/// MODEL
/// VIEW


void Cw_IsEmri::model_IEDET()
{
    IEDETmodel = new QSqlRelationalTableModel();
    IEDETmodel->setTable("dbtb_iedet");
    IEDETmodel->setEditStrategy(QSqlTableModel::OnFieldChange);

    ////  kolon başlıkları
    IEDETmodel->setHeaderData(
                IEDETmodel->fieldIndex("iedet_ie_no"),
                Qt::Horizontal, tr("İş Emri No"));
    IEDETmodel->setHeaderData(
                IEDETmodel->fieldIndex("iedet_aciklama"),
                Qt::Horizontal, tr("Yapılan İşin Cinsi"));
    IEDETmodel->setHeaderData(
                IEDETmodel->fieldIndex("iedet_tamiryeri"),
                Qt::Horizontal, tr("Tamirhane"));

    // Populate the model_mkstok
    if (!IEDETmodel->select())
    {
        qDebug () << IEDETmodel->lastError();
    }
}

void Cw_IsEmri::view_IEDET()
{
    IEDETtview->setModel(IEDETmodel);
    IEDETtview->setSelectionMode(QAbstractItemView::SingleSelection);
    IEDETtview->setSelectionBehavior(QAbstractItemView::SelectItems);
    IEDETtview->resizeColumnsToContents();
    IEDETtview->resizeRowsToContents();
    IEDETtview->setCurrentIndex(IEDETmodel->index(0,0));

    /// mapper IEdet
    IEDETmapper = new QDataWidgetMapper(this);
    IEDETmapper->setModel(IEDETmodel);
   // mpp->setItemDelegate(new IEDelegate(this));

    //// kullanıcı bu alanları görmesin
    IEDETtview->setColumnHidden(
                IEDETmodel->fieldIndex("iedet_resim"), true);
    //IEDETtview->setColumnHidden(
      //          IEDETmodel->fieldIndex("iedet_iedet_no"), true);
    IEDETtview->setColumnHidden(
                IEDETmodel->fieldIndex("id_IEdet"), true);

    IEDETmodel->select();
    IEDETtview->setContextMenuPolicy(Qt::CustomContextMenu);
    // ie - iedet set filter

    /// ie sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim



    bool sccs (true);
    sccs = connect(IEDETtview, &QTableView::customContextMenuRequested,this,
                   &Cw_IsEmri::rightMenu_IEDET);
    if (! sccs)
    {
        qDebug()<<"HATA - iedet Right Menu Connection";
    }
    else
    {
        qDebug()<<"iedet Right Menu Connected";
    }

}


//////////////////////////////////
///
///
///
/// TAŞINIR
///
///
/// MODEL
/// VIEW

void Cw_IsEmri::model_TASINIR()
{
    TSmodel = new QSqlRelationalTableModel();
    TSmodel->setTable("dbtb_tasinir");
    TSmodel->setEditStrategy(QSqlTableModel::OnFieldChange);

    TSmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);





    QSqlRelation relTS("dbtb_ambar", "id_dp", "malzeme");
    TSmodel->setRelation(TSmodel->fieldIndex("ts_malzeme"),relTS);
    cbx_TSmlzm = new QComboBox;
    cbxTSmlzmModel = new QSqlTableModel ;
    cbxTSmlzmModel = TSmodel->relationModel(
                TSmodel->fieldIndex("ts_malzeme"));
    cbx_TSmlzm ->setModel(cbxTSmlzmModel);
    cbx_TSmlzm->setModelColumn(cbxTSmlzmModel->fieldIndex("malzeme"));



    ////  kolon başlıkları
    TSmodel->setHeaderData(
                TSmodel->fieldIndex("ts_tarihi"),
                Qt::Horizontal, tr("Tarih"));
    TSmodel->setHeaderData(
                TSmodel->fieldIndex("ts_malzeme"),
                Qt::Horizontal, tr("Malzeme"));
    TSmodel->setHeaderData(
                TSmodel->fieldIndex("ts_adet"),
                Qt::Horizontal, tr("Adet"));
    TSmodel->setHeaderData(
                TSmodel->fieldIndex("ts_bfiyat"),
                Qt::Horizontal, tr("Birim Fiyat"));
    TSmodel->setHeaderData(
                TSmodel->fieldIndex("ts_durum"),
                Qt::Horizontal, tr("Temin Durumu"));

    // Populate the model_mkstok
    if (!TSmodel->select())
    {
        qDebug () << TSmodel->lastError();
    }


}

void Cw_IsEmri::view_TASINIR()
{
    TStview->setModel(TSmodel);

    TStview->setSelectionMode(QAbstractItemView::SingleSelection);
    TStview->setSelectionBehavior(QAbstractItemView::SelectItems);
    TStview->resizeColumnsToContents();
    TStview->resizeRowsToContents();
    TStview->setCurrentIndex(TSmodel->index(0,0));
TStview ->setItemDelegate(new QSqlRelationalDelegate(this));
    /// mapper tasinir
    TSmapper = new QDataWidgetMapper(this);
    TSmapper->setModel(TSmodel);
    TSmapper->setItemDelegate(new QSqlRelationalDelegate(this));




    //// kullanıcı bu alanları görmesin
    //TStview->setColumnHidden(
    //          TSmodel->fieldIndex("iedet_no"), true);
    TStview->setColumnHidden(
                TSmodel->fieldIndex("id_tasinir"), true);
    TStview->setColumnHidden(
                TSmodel->fieldIndex("resim"), true);

    TSmodel->select();
    TStview->setContextMenuPolicy(Qt::CustomContextMenu);

    /// tasinir sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim

    bool sccs (true);
    sccs = connect(TStview, &QTableView::customContextMenuRequested,this,
                   &Cw_IsEmri::rightMenu_TASINIR);
    if (! sccs)
    {
        qDebug()<<"HATA - TAŞINIR Right Menu Connection";
    }
    else
    {
        qDebug()<<"TAŞINIR Right Menu Connected";
    }

    /*    // tasinir - tasinirdet set filter
    connect(TStview->selectionModel(),
        SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
        this, SLOT(rowChanged_TASINIR(QModelIndex)));
*/
}



//////////////////////////////////
///
///
///
/// İŞÇİLİK
///
///
/// MODEL
/// VIEW



void Cw_IsEmri::model_ISCILIK()
{
    qDebug()<<"iscilik 1";
    SCmodel = new QSqlRelationalTableModel();
    SCmodel->setTable("dbtb_iscilik");
    SCmodel->setEditStrategy(QSqlTableModel::OnFieldChange);

    ////  kolon başlıkları
    SCmodel->setHeaderData(
                SCmodel->fieldIndex("ts_tarihi"),
                Qt::Horizontal, tr("Tarih"));
    SCmodel->setHeaderData(
                SCmodel->fieldIndex("ts_malzeme"),
                Qt::Horizontal, tr("Malzeme"));
    SCmodel->setHeaderData(
                SCmodel->fieldIndex("ts_adet"),
                Qt::Horizontal, tr("Adet"));
    SCmodel->setHeaderData(
                SCmodel->fieldIndex("ts_bfiyat"),
                Qt::Horizontal, tr("Birim Fiyat"));
    SCmodel->setHeaderData(
                SCmodel->fieldIndex("ts_durum"),
                Qt::Horizontal, tr("Temin Durumu"));



    // Populate the model_mkstok
    if (!SCmodel->select())
    {
        qDebug () << SCmodel->lastError();
    }


}

void Cw_IsEmri::view_ISCILIK()
{

    SCtview->setModel(SCmodel);

    SCtview->setSelectionMode(QAbstractItemView::SingleSelection);
    SCtview->setSelectionBehavior(QAbstractItemView::SelectItems);
    SCtview->resizeColumnsToContents();
    SCtview->resizeRowsToContents();
    SCtview->setCurrentIndex(SCmodel->index(0,0));

    /// mapper iscilik
    SCmapper = new QDataWidgetMapper(this);
    SCmapper->setModel(SCmodel);
   // mpp->setItemDelegate(new IEDelegate(this));

    //// kullanıcı bu alanları görmesin
    //    SCtview->setColumnHidden(
    //              SCmodel->fieldIndex("iedet_no"), true);
    SCtview->setColumnHidden(
                SCmodel->fieldIndex("id_iscilik"), true);
    SCtview->setColumnHidden(
                SCmodel->fieldIndex("resim"), true);


    SCmodel->select();
    SCtview->setContextMenuPolicy(Qt::CustomContextMenu);

    /// ie sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim

    bool sccs (true);
    sccs = connect(SCtview, &QTableView::customContextMenuRequested,this,
                   &Cw_IsEmri::rightMenu_ISCILIK);
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



///// SETUP UIS
///
/// IE IEDET TS SC
///
///
///


void Cw_IsEmri::setup_ui()
{

        QGridLayout *gLl = new QGridLayout(this);

    lbl_mkn = new QLabel("İş Emri ");
    lbl_IE = new QLabel("İş Emri Detay");

    IEtview = new QTableView(this);
    IEDETtview = new QTableView;
    TStview = new QTableView;
    SCtview = new QTableView;

//     pB1 = new QPushButton("İş Emri");
//     pB2 = new QPushButton("İş Emri Detay ");
//     hL1 = new QHBoxLayout();
//     hL1->addWidget(lbl_mkn);
//     hL1->addStretch(2);
//     hL1->addWidget(pB1);
//     hL1->addWidget(pB2);


//     hL2 = new QHBoxLayout();
//     hL2->addWidget(lbl_IE);
//     pB3 = new QPushButton("Taşınır İstek Listesi");
//     hL2->addStretch(2);
//     hL2->addWidget(pB3);





//    gL->addLayout(hL1,        5, 0, 1, 4 );
    gLl->addWidget(IEtview,      0, 0, 1, 1 );
    gLl->addWidget(IEDETtview,   0, 1, 1, 1 );
 //   gL->addLayout(hL2,        2, 0, 1, 4 );
 //   gLl->addWidget(TStview, 0, 0 );
   // gLl->addWidget(SCtview, 1, 1 );
    // x->show();
    /*    connect( pB1, &QPushButton::clicked,
             this, &Cw_IsEmri::ekle_IEDET );
    connect( pB2, &QPushButton::clicked,
             this, &Cw_IsEmri::sil_IE );
    //connect( pB3, &QPushButton::clicked,
    //       this, &Cw_IsEmri::ieYaz );
    //connect( pB4, &QPushButton::clicked,
    //       this, &Cw_IsEmri::ieEkleDDD );
    //   connect( pB5, &QPushButton::clicked,
    //          this, &Cw_IsEmri::iedetEkle );
    connect( pB6, &QPushButton::clicked,
             this, &Cw_IsEmri::sil_IEDET );
    //connect( pB7, &QPushButton::clicked,
    //       this, &Cw_IsEmri::iedetayEkleDDD );
*/

}



///// SLOTS
///
///
///
///
/// ROWCHANGED

void Cw_IsEmri::rowChanged_IE(QModelIndex IEindex)
{

    if (IEindex.isValid())
    {
        QSqlRecord record = IEmodel->record(IEindex.row());
        QString ieno = record.value("id_ie").toString() ;
        //qDebug() <<"selected ie no : "<< ieno;
        IEDETmodel->setFilter (QString("iedet_ie_id = '%1'" ).arg(ieno));

        IEDETtview->setCurrentIndex(IEDETmodel->index(0,0));
        QModelIndex iedetindx = IEDETtview->currentIndex();
        Cw_IsEmri::rowChanged_IEDET(iedetindx);
        IEDETtview->setFocus ();
    }
    else
    {
        IEDETmodel->setFilter("ie_no = -1");
        TSmodel->setFilter("id_tasinir = -1");
        SCmodel->setFilter("id_iscilik = -1");

    }

    // IEtview->setFocus(); // detaya geç
    /*   IEDETmodel->select();
    IEDETtview->setFocus();    // iş emrine geri dön
*/
    IEtview->setFocus ();
}




void Cw_IsEmri::rowChanged_IEDET(QModelIndex IEDETindex)
{

    //QModelIndex index = IEDETtview->currentIndex();
    if (IEDETindex.isValid())
    {
        QSqlRecord record = IEDETmodel->record(IEDETindex.row());
        QString ieno = record.value("id_iedet").toString() ;
        ///setfiltr to tasinir and iscilik
        TSmodel->setFilter (QString("ts_iedet_id = '%1'" ).arg(ieno));
        TSmodel->select();
         TStview->setFocus();
        SCmodel->setFilter (QString("sc_iedet_id = '%1'" ).arg(ieno));
        SCmodel->select();
SCtview->setFocus();

        /*lbl_IE->
                setText((record.value("mknstk_no").toString()+
                         " - " +
                         record.value("ie_no").toString() ));*/
    } else
    {
//        TSmodel->setFilter("id_tasinir = -1");
  //      SCmodel->setFilter("id_iscilik = -1");
    }

 /*   // qDebug () <<"iedet row changggggedd 2";
    //IEDETmodel->select();
    TStview->setFocus();
    SCtview->setFocus();
    IEDETmodel->select();


    //qDebug () <<"iedet row changggggedd 3";
*/
     IEDETtview->setFocus();
}



void Cw_IsEmri::rowChanged_TASINIR(QModelIndex)
{

}

void Cw_IsEmri::rowChanged_ISCILIK(QModelIndex)
{

}




///// SLOTS
///
///
///
///
/// RIGHTMENU



/////////////////////////////////////////////   ie view sağ tuş menusu
void Cw_IsEmri::rightMenu_IE(QPoint pos)

{
    //qDebug ()  <<"  cw işemri view sağ tuş 001";
    QMenu *menuie = new QMenu(this);

    // yeni iş emri detay kaydı ekle
    const QIcon ekleIc_IEdet = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_IEdet = new QAction(ekleIc_IEdet, tr("İş Emri Detay Ekle..."), this);
    ekleAct_IEdet->setShortcuts (QKeySequence::New);
    ekleAct_IEdet->setStatusTip ("İş Emri Detay Kaydı Ekle");
    connect (ekleAct_IEdet, &QAction::triggered, this,
             &Cw_IsEmri::onmnIE_IEDETekle );
    menuie->addAction(ekleAct_IEdet);

    //  iş emri detay sil
    const QIcon silIc_IE = QIcon(":/rsm/Add.ico");
    QAction* silAct_IE = new QAction(silIc_IE, tr("İş Emri Sil..."), this);
    silAct_IE->setShortcuts (QKeySequence::New);
    silAct_IE->setStatusTip ("İş Emri Sil");
    connect (silAct_IE, &QAction::triggered, this,
             &Cw_IsEmri::sil_IE );
    menuie->addAction(silAct_IE);

    menuie->popup(IEtview->viewport()->mapToGlobal(pos));
}


/////////////////////////////////////////////   iedet view sağ tuş menusu
void Cw_IsEmri::rightMenu_IEDET(QPoint pos)

{
    //qDebug ()  <<"  cw işemri view sağ tuş 001";
    QMenu *menuiedet = new QMenu(this);

    // taşınır kaydı ekle
    const QIcon ekleIc_IEdet = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_IEdet = new QAction(ekleIc_IEdet, "Taşınır Kaydı Ekle...", this);
    ekleAct_IEdet->setShortcuts (QKeySequence::New);
    ekleAct_IEdet->setStatusTip ("Taşınır Kaydı Ekle");
    connect (ekleAct_IEdet, &QAction::triggered, this,
             &Cw_IsEmri::onmnIEDET_TSekle );
    menuiedet->addAction(ekleAct_IEdet);

    // işbilik kaydı ekle
    const QIcon ekleIc_is = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_is = new QAction(ekleIc_is, tr("İşçilik Kaydı Ekle..."), this);
    ekleAct_is->setShortcuts (QKeySequence::New);
    ekleAct_is->setStatusTip ("İşçilik Kaydı Ekle");
    connect (ekleAct_is, &QAction::triggered, this,
             &Cw_IsEmri::onmnIEDET_SCekle );
    menuiedet->addAction(ekleAct_is);


    //  iş emri detaysil
    const QIcon silIc_IEdet = QIcon(":/rsm/Add.ico");
    QAction* silAct_IEdet = new QAction(silIc_IEdet, tr("İş Emri Detay Sil..."), this);
    silAct_IEdet->setShortcuts (QKeySequence::New);
    silAct_IEdet->setStatusTip ("İş Emri Detay Sil");
    connect (silAct_IEdet, &QAction::triggered, this,
             &Cw_IsEmri::sil_IEDET );
    menuiedet->addAction(silAct_IEdet);

    menuiedet->popup(IEDETtview->viewport()->mapToGlobal(pos));
} // rightMenu IEDET


/////////////////////////////////////////////   tasinir view sağ tuş menusu
void Cw_IsEmri::rightMenu_TASINIR(QPoint pos)

{
    //qDebug ()  <<"  cw tasinir view sağ tuş 001";
    QMenu *menuts = new QMenu(this);

    // tasinir kaydı ekle
    const QIcon ekleIc_ts = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_ts = new QAction(ekleIc_ts, tr("Taşınır Ekle..."), this);
    ekleAct_ts->setShortcuts (QKeySequence::New);
    ekleAct_ts->setStatusTip ("Taşınır Kaydı Ekle");
    connect (ekleAct_ts, &QAction::triggered, this,
             &Cw_IsEmri::TSekle );
    menuts->addAction(ekleAct_ts);

    //  tasinir sil
    const QIcon silIc_ts = QIcon(":/rsm/Add.ico");
    QAction* silAct_ts = new QAction(silIc_ts, tr("Taşınır Sil..."), this);
    silAct_ts->setShortcuts (QKeySequence::New);
    silAct_ts->setStatusTip ("Taşınır Sil");
    connect (silAct_ts, &QAction::triggered, this,
             &Cw_IsEmri::sil_TASINIR );
    menuts->addAction(silAct_ts);

    menuts->popup(TStview->viewport()->mapToGlobal(pos));
}

void Cw_IsEmri::rightMenu_ISCILIK(QPoint pos)
{
    //qDebug ()  <<"  cw iscilik view sağ tuş 001";
    QMenu *menuis = new QMenu(this);

    // iscilik ayar ekle
    const QIcon ekleIc_is = QIcon(":/rsm/Add.ico");
    QAction* ekleAct_is = new QAction(ekleIc_is, tr("İşçilik Ücretleri..."), this);
    ekleAct_is->setShortcuts (QKeySequence::New);
    ekleAct_is->setStatusTip ("İşçilik Ücretleri");
    connect (ekleAct_is, &QAction::triggered, this,
             &Cw_IsEmri::ayar_ISCILIK );
    menuis->addAction(ekleAct_is);

    //  iscilik sil
    const QIcon silIc_ts = QIcon(":/rsm/Add.ico");
    QAction* silAct_ts = new QAction(silIc_ts, tr("Taşınır Sil..."), this);
    silAct_ts->setShortcuts (QKeySequence::New);
    silAct_ts->setStatusTip ("Taşınır Sil");
    connect (silAct_ts, &QAction::triggered, this,
             &Cw_IsEmri::sil_ISCILIK );
    menuis->addAction(silAct_ts);

    menuis->popup(SCtview->viewport()->mapToGlobal(pos));
}






///// SLOTS
///
///
///
///
/// EKLE




////////////////////////////////////////////
///
///
///
//// EKLE_IEdet
///
///
///
///
///


//////////////////////////////////////////////////////////
///
///
///
///
///     İş Emri DETAY Ekle
///
///
///
///




void Cw_IsEmri::onmnIE_IEDETekle()
{
    IEno = new QString;
    IE_idno = new QString;
    QSqlQuery q;
    QVariant ino = " " ;
    QModelIndex index = IEtview->currentIndex();
    if (index.isValid())
    {
        // tv index i ile model de recordu bulduk
        QSqlRecord record = IEmodel->record(index.row());
        *IEno = record.value("ie_ie_no").toString();
        *IE_idno = record.value("id_IE").toString();

    }
    else
    {
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
        msgBox.setWindowTitle("İŞ EMRİ DETAY KAYIT EKLEME HATASI                               -");
        msgBox.setText("İş Emri Detay kaydı \n"
                       "Kayıt Eklenemedi ...");
        msgBox.setInformativeText("tV_ie index is invalid");        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {
            return;
        }
    }


    // IEdet_no yu oluşturalım
    // ioi_no + hangi yıl + yılın kaçıncı günündeyiz
    QString IEdet = *IEno;
    IEdet.append(":");
    IEdetno = new QString;
    *IEdetno = IEdet ;
    int IEdetcount = 1;

           qDebug ()<< "1 iedetcount :" << IEdetcount ;

    // how mny-- records?
    QSqlQuery query;
    query.prepare("SELECT * FROM dbtb_iedet ");
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
            lttl= query.value("iedet_iedet_no").toString();
            lttl.chop(3) ;
           qDebug ()<< "iecount :" << IEdetcount ;
            if (lttl == *IEno)
            {
                IEdetcount++;
                qDebug ()<< "iecount ---:" << IEdetcount ;
            }
        }
    }
    ///// yeni iedetno son hali
    *IEdetno += "0"+QString::number(IEdetcount);
    QWidget *wdgt_TSekle = new QWidget;
    wdgt_TSekle->setWindowTitle("İş Emri Detay Yeni Kayıt");
    wdgt_TSekle->setVisible(false);
    wdgt_TSekle->show();

    QGridLayout *TsL = new QGridLayout;
    wdgt_TSekle->setLayout(TsL);


    QLabel *lB_IEdetno = new QLabel("İş Emri Detay No ");
    TsL->addWidget(lB_IEdetno        ,0,0,1,1,nullptr);
    lE_IEdetno = new QLineEdit;
    lE_IEdetno->setText (*IEdetno);
    lE_IEdetno->setReadOnly (true);
    TsL->addWidget(lE_IEdetno   ,0,1,1,3,nullptr);
    lB_IEdetno->setBuddy(lE_IEdetno);

    QLabel *lB_acklm = new QLabel("Yapılacak İş");
    TsL->addWidget(lB_acklm        ,1,0,1,1,nullptr);
    lE_IEdetaciklama = new QLineEdit;
    TsL->addWidget(lE_IEdetaciklama   ,1,1,1,3,nullptr);
    lB_acklm->setBuddy(lE_IEdetaciklama);


    QLabel *lB_ust = new QLabel("Tamir Yeri");
    TsL->addWidget(lB_ust        ,3,0,1,1,nullptr);
    cbx_IEdetkurumicdis = new QComboBox;                    //dbtb_clsn
    QStringList tylist {"Atolye","Arazi","Yetkili Servis","Dış Servis"};
    cbx_IEdetkurumicdis->addItems(tylist);
    TsL->addWidget(cbx_IEdetkurumicdis   ,3,1,1,3,nullptr);
    lB_ust->setBuddy(cbx_IEdetkurumicdis);

    QLabel *lB_tm = new QLabel("Atolye Bolüm");
    TsL->addWidget(lB_tm        ,2,0,1,1,nullptr);
    cbx_IEdettamiryeri = new QComboBox;
    QStringList ablist {"Boya","Kaporta","Motor","Torna","Mekanik"};
    cbx_IEdettamiryeri->addItems(ablist);
    TsL->addWidget(cbx_IEdettamiryeri  ,2,1,1,3,nullptr);
    lB_tm->setBuddy(cbx_IEdettamiryeri );

    QLabel *lB_dr = new QLabel("İş Emri Detay Durum");
    TsL->addWidget(lB_dr        ,4,0,1,1,nullptr);
    cbx_IEdetdurum = new QComboBox;                    // dbtb_durum
    QStringList drlist { "-","Parça Bekliyor","Usta Bekliyor","Tamamlandı"};
    cbx_IEdetdurum->addItems(drlist);
    TsL->addWidget(cbx_IEdetdurum   ,4,1,1,3,nullptr);
    lB_dr->setBuddy(cbx_IEdetdurum);
//    QPushButton *pb_durum = new QPushButton("+");
//    TsL->addWidget(pb_durum   ,4,4,1,1,nullptr);
//    connect(pb_durum, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetdurum);

    QLabel *lB_gt = new QLabel("Araç Giriş Tarihi");
    TsL->addWidget(lB_gt        ,7,0,1,1,nullptr);
    dE_IEdetgirtarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEdetgirtarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEdetgirtarihi->setMinimumDate(QDate(01, 01, 1900));
    dE_IEdetgirtarihi->setMaximumDate(QDate(valiDDate));
    dE_IEdetgirtarihi->setCalendarPopup(true);
    TsL->addWidget(dE_IEdetgirtarihi   ,7,1,1,3,nullptr);
    lB_gt->setBuddy(dE_IEdetgirtarihi);

    QLabel *lB_ct = new QLabel("Araç Çıkış Tarihi");
    TsL->addWidget(lB_ct        ,8,0,1,1,nullptr);
    dE_IEdetciktarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEdetciktarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEdetciktarihi->setMinimumDate(QDate (01, 01, 1900));
    dE_IEdetciktarihi->setMaximumDate(QDate ( valiDDate ));
    dE_IEdetciktarihi->setCalendarPopup(true);
    TsL->addWidget(dE_IEdetciktarihi   ,8,1,1,3,nullptr);
    lB_ct->setBuddy(dE_IEdetciktarihi);

    //QLabel *lB_rsm = new QLabel("Resim");


    QPushButton *pb_kaydet = new QPushButton("Yeni Ekle");
    connect (pb_kaydet, &QPushButton::clicked,
             this, & Cw_IsEmri::clk_IEDETbosh );
    TsL->addWidget(pb_kaydet        ,10,5,1,1,nullptr);

    QPushButton *TStview = new QPushButton("Vazgeç");
    connect (TStview, &QPushButton::clicked, wdgt_TSekle, &QWidget::close );
    TsL->addWidget(TStview        ,10,3,1,1,nullptr);




    //IEmapper->addMapping(IEmapper, mdl_mkn->fieldIndex("ie_mknstk_no"));
    IEDETmapper->addMapping(lE_IEdetno, IEDETmodel->fieldIndex("iedet_iedet_no"));
    IEDETmapper->addMapping(lE_IEdetaciklama , IEDETmodel->fieldIndex("iedet_aciklama"));
    IEDETmapper->addMapping(cbx_IEdettamiryeri , IEDETmodel->fieldIndex("iedet_tamiryeri"));
    IEDETmapper->addMapping(cbx_IEdetkurumicdis, IEDETmodel->fieldIndex("iedet_kurumicdis"));
    IEDETmapper->addMapping(cbx_IEdetdurum, IEDETmodel->fieldIndex("iedet_yap"));
    IEDETmapper->addMapping(dE_IEdetgirtarihi , IEDETmodel->fieldIndex("ie_gir_tar"));
    IEDETmapper->addMapping(dE_IEdetciktarihi , IEDETmodel->fieldIndex("ie_cik_tar"));
qDebug ()<< "::::: 5" ;
//        IEmapper->addMapping(cbx_ykt, mdl_mkn->fieldIndex("ie_resim"));


    QPushButton *pb_ilk = new QPushButton("İlk");
    connect( pb_ilk, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toFirst );
    TsL->addWidget( pb_ilk   ,10,1,1,1,nullptr);

    QPushButton *pb_pr = new QPushButton("Önceki");
    connect( pb_pr, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toPrevious );
    TsL->addWidget( pb_pr   ,10,2,1,1,nullptr);

    QPushButton *pb_lr = new QPushButton("Sonraki");
    connect( pb_lr, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toNext );
    TsL->addWidget( pb_lr   ,10,3,1,1,nullptr);

    QPushButton *pb_ls = new QPushButton("Son");
    connect( pb_ls, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toLast );
    TsL->addWidget( pb_ls   ,10,4,1,1,nullptr);


}


void Cw_IsEmri::clk_IEDETbosh()
{
    /// yeni IE iş emri detay kaydı için
    /// sahaları boşaltalım


    lE_IEdetno->setText( *IEdetno) ;
    lE_IEdetaciklama->setText ("");
    cbx_IEdettamiryeri->setCurrentText ("");
    cbx_IEdetkurumicdis->setCurrentText ("");
    cbx_IEdetdurum->setCurrentText ("");
    dE_IEdetgirtarihi->setDate(QDate::currentDate());
    dE_IEdetciktarihi->setDate(QDate::currentDate());


    Cw_IsEmri::IEDETekle();

}




void Cw_IsEmri::IEDETekle()
{

    ////////////////////////////////
    QSqlQuery q;
    QString q_s;
    q_s="INSERT INTO dbtb_IEdet ( "
        "iedet_ie_id, iedet_iedet_no   , iedet_aciklama, iedet_tamiryeri, "
        "iedet_durum, iedet_girtar , iedet_ciktar "
        " )"
        " values( ?, ?, ?, ?, ?, ?, ? )";
    q.prepare(q_s);

    q.bindValue(0, *IE_idno  );   //*IEno
    q.bindValue(1, *IEdetno );
    q.bindValue(2, lE_IEdetaciklama->text ());
    q.bindValue(3, cbx_IEdettamiryeri->currentText ());
    q.bindValue(4, cbx_IEdetkurumicdis->currentText ());

    q.bindValue(5, cbx_IEdetdurum->currentText ());
    q.bindValue(6, dE_IEdetgirtarihi->text());
    q.bindValue(7, dE_IEdetciktarihi->text());

    q.exec();

    if (q.isActive())
    {
        qDebug () <<"İş Emri Detay Yeni Kayıt Eklendi - "<< lE_IEdetno->text() << " -   Eklendi";
    }
    else
    {
        qDebug () << "İş Emri Detay Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
    }




    IEDETmodel->select();
    IEDETtview->setFocus();

    // iş emri detay ekle
    ///////////////////////////////////////////////////



}






void Cw_IsEmri::clk_IEdetdurum()
{}

void Cw_IsEmri::clk_IEdetyyer()
{}

void Cw_IsEmri::clk_IEdetclsn()
{}


///////////////////////////////////////////////////////////////////
///
///
///
////*





//////////////////////////////////////////////////////////
///
///
///
///      TS
///     Taşınır Ekle
///
///
///
///




void Cw_IsEmri::onmnIEDET_TSekle()
{
    qDebug ()<<"ts 1";
    TSno = new QString;
    TSdet_idno = new QString;
    *TSdet_idno="-1";
    QSqlQuery q;
    QVariant ino = " " ;
    QModelIndex index = IEDETtview->currentIndex();
    if (index.isValid())
    {
        // tv index i ile model de recordu bulduk
        QSqlRecord record = IEDETmodel->record(index.row());
        *TSno = record.value("ie_iedet_no").toString();
        *TSdet_idno = record.value("id_IEdet").toString();
qDebug ()<<"ts 12 ---- tsdfetidno --- "<< * TSdet_idno;
    }
    else
    {
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
        msgBox.setWindowTitle("TAŞINIR İSTEK KAYIT EKLEME HATASI                               -");
        msgBox.setText("Taşınır kaydı \n"
                       "Kayıt Eklenemedi ...");
        msgBox.setInformativeText("TStview index is invalid");        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {
            return;
        }
    }


    // IEdet_no yu oluşturalım
    // ioi_no + hangi yıl + yılın kaçıncı günündeyiz
    QString TSdet = *TSno;
    TSdet.append(":");
    TSdetno = new QString;
    *TSdetno = TSdet ;
    int IEcount = 1;

           qDebug ()<< "iecount :" << IEcount ;

    // how mny-- records?
    QSqlQuery query;
    query.prepare("SELECT * FROM dbtb_tasinir ");
    if (!query.exec())
    {
        qDebug() << "SQL error: "<< query.lastError().text() << endl;
    }
    else
    {
        qDebug ()<<"ts 13";
        QString lttl ="" ;
        query.first();
        while (query.next())
        {
            lttl= query.value("ts_no").toString();
            lttl.chop(3) ;
           qDebug ()<< "iecount :" << IEcount ;
            if (lttl == *TSno)
            {
                IEcount++;
                qDebug ()<< "iecount --- :" << IEcount ;
            }
        }
    }
    ///// yeni ts iedetno son hali
    *TSdetno += "0"+QString::number(IEcount);
    QWidget *wdgt_TSekle = new QWidget;
    wdgt_TSekle->setWindowTitle("Taşınır Yeni Kayıt");
    wdgt_TSekle->setVisible(false);
    wdgt_TSekle->show();

    QGridLayout *TsL = new QGridLayout;
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
    cbx_TSmalzeme = new QComboBox;                    //dbtb_clsn
    TsL->addWidget(cbx_TSmalzeme   ,2,1,1,3,nullptr);
    lB_us->setBuddy(cbx_TSmalzeme);
    QPushButton *pb_clsn = new QPushButton("+");
    TsL->addWidget(pb_clsn   ,2,4,1,1,nullptr);
    connect (pb_clsn, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetclsn);





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
    cbx_TSbirim = new QComboBox;                    //dbtb_clsn
    TsL->addWidget(cbx_TSbirim   ,4,1,1,3,nullptr);
    lB_usb->setBuddy(cbx_TSbirim);
    QPushButton *pb_clsn2 = new QPushButton("+");
    TsL->addWidget(pb_clsn2   ,4,4,1,1,nullptr);
    connect (pb_clsn2, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetclsn);
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
    connect(pb_durum, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetdurum);

    QLabel *lB_acklm = new QLabel("Açıklama");
    TsL->addWidget(lB_acklm        ,7,0,1,1,nullptr);
    lE_TSaciklama = new QLineEdit;
    TsL->addWidget(lE_TSaciklama   ,7,1,1,3,nullptr);
    lB_acklm->setBuddy(lE_TSaciklama);

qDebug ()<<"ts 145";

    //QLabel *lB_rsm = new QLabel("Resim");


    QPushButton *pb_kaydet = new QPushButton("Yeni Ekle");
    connect (pb_kaydet, &QPushButton::clicked,
             this, & Cw_IsEmri::clk_TSbosh );
    TsL->addWidget(pb_kaydet        ,10,5,1,1,nullptr);

    QPushButton *TStview = new QPushButton("Vazgeç");
    connect (TStview, &QPushButton::clicked, wdgt_TSekle, &QWidget::close );
    TsL->addWidget(TStview        ,10,3,1,1,nullptr);



qDebug ()<<"ts 146";
    //IEmapper->addMapping(IEmapper, mdl_mkn->fieldIndex("ie_mknstk_no"));
    IEDETmapper->addMapping(lE_TSno, TSmodel->fieldIndex("ts_no"));
    IEDETmapper->addMapping(dE_TStarih , TSmodel->fieldIndex("ts_tarih"));
    IEDETmapper->addMapping(cbx_TSmalzeme , TSmodel->fieldIndex("ts_malzeme"));
    IEDETmapper->addMapping(lE_TSmiktar, TSmodel->fieldIndex("ts_miktar"));
    IEDETmapper->addMapping(cbx_TSbirim , TSmodel->fieldIndex("ts_birim"));
    IEDETmapper->addMapping(lE_TSbfiyat, TSmodel->fieldIndex("ts_bfiyat"));
    IEDETmapper->addMapping(cbx_TSdurum, TSmodel->fieldIndex("ts_durum"));
    IEDETmapper->addMapping(lE_TSaciklama , TSmodel->fieldIndex("ts_aciklama"));

qDebug ()<<"ts 15";
//        IEmapper->addMapping(cbx_ykt, mdl_mkn->fieldIndex("ie_resim"));


    QPushButton *pb_ilk = new QPushButton("İlk");
    connect( pb_ilk, &QPushButton::clicked,
             TSmapper, &QDataWidgetMapper::toFirst );
    TsL->addWidget( pb_ilk   ,10,1,1,1,nullptr);

    QPushButton *pb_pr = new QPushButton("Önceki");
    connect( pb_pr, &QPushButton::clicked,
             TSmapper, &QDataWidgetMapper::toPrevious );
    TsL->addWidget( pb_pr   ,10,2,1,1,nullptr);

    QPushButton *pb_lr = new QPushButton("Sonraki");
    connect( pb_lr, &QPushButton::clicked,
             TSmapper, &QDataWidgetMapper::toNext );
    TsL->addWidget( pb_lr   ,10,3,1,1,nullptr);

    QPushButton *pb_ls = new QPushButton("Son");
    connect( pb_ls, &QPushButton::clicked,
             TSmapper, &QDataWidgetMapper::toLast );
    TsL->addWidget( pb_ls   ,10,4,1,1,nullptr);


}


void Cw_IsEmri::clk_TSbosh()
{
    /// yeni IE iş emri detay kaydı için
    /// sahaları boşaltalım

qDebug ()<<"ts 16";
    lE_TSno->setText( *TSdetno) ;
    dE_TStarih->setDate(QDate::currentDate());
    cbx_TSmalzeme->setCurrentIndex (0);
    lE_TSmiktar->setText ("");
    cbx_TSbirim->setCurrentText ("");
    lE_TSbfiyat->setText ("");
    cbx_TSdurum->setCurrentText ("");
    lE_TSaciklama->setText ("");


    Cw_IsEmri::TSekle();

}




void Cw_IsEmri::TSekle()
{
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
        "ts_iedet_id, ts_no    , ts_tarih, ts_malzeme , ts_miktar, "
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
    TStview->setFocus();

    // tasinir ekle
    ///////////////////////////////////////////////////

qDebug ()<<"ts 19";

}








//////////////////////////////////////////////////////////
///
///
///
///      SC
///     işçilik Ekle
///
///
///
///




void Cw_IsEmri::onmnIEDET_SCekle()
{
    qDebug ()<<"SC 1";
    SCno = new QString;
    SCdet_idno = new QString;
    *SCdet_idno="-1";
    QSqlQuery q;
    QVariant ino = " " ;
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

    QGridLayout *SCL = new QGridLayout;
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
    connect (pb_clsn2, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetclsn);

    QLabel *lB_usb = new QLabel("Usta");
    SCL->addWidget(lB_usb        ,4,0,1,1,nullptr);
    cbx_SCusta = new QComboBox;                    //dbtb_clsn
    SCL->addWidget(cbx_SCusta   ,4,1,1,3,nullptr);
    lB_usb->setBuddy(cbx_SCusta);
    QPushButton *pb_cl2 = new QPushButton("+");
    SCL->addWidget(pb_cl2   ,4,4,1,1,nullptr);
    connect (pb_cl2, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetclsn);










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
    connect(pb_utip, &QPushButton::clicked, this, &Cw_IsEmri::clk_IEdetdurum);

    QLabel *lB_acklm = new QLabel("Açıklama");
    SCL->addWidget(lB_acklm        ,7,0,1,1,nullptr);
    lE_SCaciklama = new QLineEdit;
    SCL->addWidget(lE_SCaciklama   ,7,1,1,3,nullptr);
    lB_acklm->setBuddy(lE_SCaciklama);

qDebug ()<<"SC 145";

    //QLabel *lB_rsm = new QLabel("Resim");


    QPushButton *pb_kaydet = new QPushButton("Yeni Ekle");
    connect (pb_kaydet, &QPushButton::clicked,
             this, & Cw_IsEmri::clk_SCbosh );
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


void Cw_IsEmri::clk_SCbosh()
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


    Cw_IsEmri::SCekle();

}




void Cw_IsEmri::SCekle()
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




Cw_IsEmri::~Cw_IsEmri()
{
}

/*

void Cw_IsEmri::TSekle()
{
    QString ieno = "";
    QModelIndex index = IEDETtview->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = IEDETmodel->record(index.row());
        ieno = record.value("id_iedet").toString();

    }


    // taşınır ekle
    QSqlQuery q;
    q.prepare ("INSERT INTO dbtb_tasinir ( iedet_no ) values ( :a ) ") ;
    q.bindValue (":a",ieno);

    if (q.exec())
        qDebug () << "Taşınır İstek Yeni Kayıt - "<< ieno << " -   Eklendi";
    else
        qDebug () << "Taşınır İstek Yeni Kayıt Eklenemedi - " << q.lastError() ;

    // IEDETmodel->submit();
    //TStview->setFocus();
    TSmodel->select();
}  // ekle tasinir


void Cw_IsEmri::SCekle()
{
    QString ieno = "";
    QModelIndex index = IEDETtview->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = IEDETmodel->record(index.row());
        ieno = record.value("id_iedet").toString();

    }


    // isclik  ekle
    QSqlQuery q;
    q.prepare ("INSERT INTO dbtb_iscilik ( iedet_no )"
               " values( :a )");
    q.bindValue (":a",ieno);
    if (q.exec(  ))
        qDebug () <<"İşçilik Yeni Kayıt - "<< ieno << " -   Eklendi";
    else
        qDebug () << "İşçilik Yeni Kayıt Eklenemedi - " << q.lastError() ;

    //IEDETmodel->submit();
    ///V_iscilik->setFocus();
    SCmodel->select();

}


*/



///// SLOTS
///
///
///
///
/// SİL



void Cw_IsEmri::sil_IE()
{
    // ie  kayıt sil
    QMessageBox msgBox;
    QPushButton *pb_tmm = msgBox.addButton(tr("İŞ EMRİNİ SİL"), QMessageBox::ActionRole);
    QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


    msgBox.setIcon(QMessageBox::Critical );
    msgBox.setWindowTitle("!! DİKKAT !!");
    msgBox.setText("!! DİKKAT !!\n"
                   "İş emrini silerseniz;\n"
                   "bu İş Emri bağlı (iş emri detay, taşınır ve işçilik)\n "
                   "tüm kayıtlarda silinir\n "
                   "\n"
                   "Silmek istediğinizden eminmisiniz ?");
    msgBox.exec();



    if (msgBox.clickedButton() == pb_tmm)
    {
        /// önce bu iş emrine bağlı
        /// iedet
        /// iedet kayıtlarına bağlı
        /// taşınır
        /// işçilik kayıtlarını silelim



        // şimdi iş emrini silelim
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex ie_indx = IEtview->currentIndex ();
        QString ino = IEmodel->data
                (IEmodel->index
                 (ie_indx.row (),
                  IEmodel->fieldIndex ("id_IE"))).toString ();

        s_qry = QString("DELETE FROM dbtb_IE "
                        "WHERE id_IE = %1").arg( ino );

        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            qDebug()<< " İş Emri Kaydı Silindi ";
            IEmodel->submitAll ();
            IEmodel->select ();
        }
        else
        {

            qDebug()<< " HATA - İş Emri Kaydı Silinemedi "
                    << q_qry.lastError ().text ();

        }
    }
    else if (msgBox.clickedButton() == pb_vzg)
    {
        msgBox.close(); // abort
    }

}       ///      ie_sil








void Cw_IsEmri::sil_IEDET()
{
    // iedet  kayıt sil
    QMessageBox msgBox;
    QPushButton *pb_tmm = msgBox.addButton(tr("BU İŞ EMRİ DETAYINA AİT TÜM KAYITLARI SİL"), QMessageBox::ActionRole);
    QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


    msgBox.setIcon(QMessageBox::Critical );
    msgBox.setWindowTitle("!! DİKKAT !!");
    msgBox.setText("!! DİKKAT !!\n"
                   "İş Emri Detay Kaydını silerseniz;\n"
                   "bu İş Emri Detayına bağlı (taşınır ve işçilik)\n "
                   "tüm kayıtlarda silinir\n "
                   "\n"
                   "Silmek istediğinizden eminmisiniz ?");
    msgBox.exec();



    if (msgBox.clickedButton() == pb_tmm)
    {
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex iedet_indx = IEDETtview->currentIndex ();
        QString ino = IEDETmodel->data
                (IEDETmodel->index
                 (iedet_indx.row (),
                  IEDETmodel->fieldIndex ("id_iedet"))).toString ();

        s_qry = QString("DELETE FROM dbtb_iedet "
                        "WHERE id_iedet = %1").arg( ino );

        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            qDebug()<< " İş Rmri Detay Kaydı Silindi ";
            //   mdl_mkn->submitAll ();
            IEDETmodel->select ();
        }
        else
        {

            qDebug()<< " HATA - İş Emri Detay Kaydı Silinemedi "
                    << q_qry.lastError ().text ();

        }
    }
    else if (msgBox.clickedButton() == pb_vzg)
    {
        msgBox.close(); // abort
    }

}       /// iedet_sil






void Cw_IsEmri::sil_TASINIR()
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
        QModelIndex tasinir_indx = TStview->currentIndex ();
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

}





void Cw_IsEmri::sil_ISCILIK()
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



void Cw_IsEmri::ayar_ISCILIK()
{

}       ///      AYAR işçilik


