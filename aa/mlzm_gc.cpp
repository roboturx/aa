#include "mlzm_gc.h"

hC_MLZMGC::hC_MLZMGC() : hC_tBcreator ()
{
    //************************************************************
    //*****************  M A L Z E M E  **************************
    qDebug() << "Cnstrctr mlzmGc *********************************";

    win_Label->text ()= "AMBAR MALZEME GİRİŞ-ÇIKIŞ KAYITLARI";
    *tb_name   = "mlzmgc_dbtb" ;

    tb_flds = new hC_ArrD (13, 4);
    tb_flds->setValue ( 0, "mlzmgc_ID"      , "INTEGER", "MalzemeGcID", "0" ) ;
    tb_flds->setValue ( 1, "mlzmgc_mlzm_kod", "TEXT"   , "Malzeme Kod", "0" );
    tb_flds->setValue ( 2, "mlzmgc_barkod"  , "TEXT"   , "Barkod", "0" );
    tb_flds->setValue ( 3, "mlzmgc_malzeme" , "TEXT"   , "Malzeme", "0");
    tb_flds->setValue ( 4, "mlzmgc_tarih"   , "TEXT"   , "Tarih"   );
    tb_flds->setValue ( 5, "mlzmgc_gc"      , "TEXT"   , "İşlem Türü");
    tb_flds->setValue ( 6, "mlzmgc_gcno"    , "TEXT"   , "İşlem No"  );
    tb_flds->setValue ( 7, "mlzmgc_miktar"  , "TEXT"   , "Miktar"  );
    tb_flds->setValue ( 8, "mlzmgc_birim"   , "TEXT"   , "Birim");
    tb_flds->setValue ( 9, "mlzmgc_fiyat"   , "TEXT"   , "Fiyatı");
    tb_flds->setValue (10, "mlzmgc_kdv"     , "TEXT"   , "KDV %");
    tb_flds->setValue (11, "mlzmgc_aciklama", "TEXT"   , "Açıklama" );
    tb_flds->setValue (12, "mlzmgc_resim"   , "BLOB"   , "Resim" , "0" );

    *tb_ndex     = "mlzmgc_tarih";
//    tb_model    = new QSqlRelationalTableModel;
//    tb_mapper   = new QDataWidgetMapper;
//    win_Wdgt    = new QWidget;
//    tb_view     = new hC_Tv ();
//    tb_slctnMdl = new QItemSelectionModel;

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( nullptr    ) ; // mlzm_kod
    tb_wdgts->append ( nullptr    ) ; // barkod
    tb_wdgts->append ( nullptr    ) ; // malzeme
    tb_wdgts->append ( lE_tarih = new QLineEdit  ) ;
    tb_wdgts->append ( cbx_grscks = new QComboBox  ) ;
    tb_wdgts->append ( nullptr    ) ; // gcno
    tb_wdgts->append ( lE_miktar = new QLineEdit  ) ;
    tb_wdgts->append ( nullptr    ) ; // birim
    tb_wdgts->append ( lE_fiyat = new QLineEdit ) ;
    tb_wdgts->append ( nullptr    ) ; // kdv
    tb_wdgts->append ( lE_aciklama = new QLineEdit    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_MLZMGC::setup()
{
    qDebug() << "  mlzmGc_setup";

    create ( tb_flds );
    model  ( tb_flds, tb_wdgts );
    view   ( tb_flds, tb_wdgts );
    map    ( tb_flds, tb_wdgts );


    wdgt  () ;
    ui    () ;
    kntrl () ;
}




void hC_MLZMGC::ui()
{

    qDebug() << "  MlzmGc_ui";
    setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout(this);  // 100150
    win_Grid->addWidget (tb_view , 0, 0, 1, 6);
    win_Grid->addWidget (win_Wdgt  , 0, 6, 1, 4);
}



void hC_MLZMGC::wdgt()
{
    qDebug() << "  mlzmGc_wdgt";

    auto *lB_tarih = new QLabel(tr("&Tarih"));
    lB_tarih->setBuddy(lE_tarih);

    auto *lB_grs_cks = new QLabel(tr("İşlem Türü"));
    QStringList GC = {"Faturalı Giriş",
                      "Çıkış" };
    cbx_grscks->insertItems (0,  GC );
    lB_grs_cks->setBuddy(cbx_grscks);

    auto *lB_miktar = new QLabel(tr("&Miktar"));
    lB_miktar->setBuddy(lE_miktar);

    auto *lB_fiyat = new QLabel(tr("&Fiyat"));
    lB_fiyat->setBuddy(lE_fiyat);

    auto *lB_aciklama = new QLabel(tr("&Açıklama"));
    lB_aciklama->setBuddy(lE_aciklama);


    hC_Rs resim(win_Rsm);

    ///////////////////////////////////////

    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_aciklama->setMinimumSize (200,25);

    wdgtGrid->addWidget(lB_tarih   , 0, 0, 1, 1);
    wdgtGrid->addWidget(lE_tarih   , 0, 1, 1, 1);
    wdgtGrid->addWidget(lB_grs_cks , 1, 0, 1, 1);
    wdgtGrid->addWidget(cbx_grscks , 1, 1, 1, 1);
    wdgtGrid->addWidget(lB_miktar  , 2, 0, 1, 1);
    wdgtGrid->addWidget(lE_miktar  , 2, 1, 1, 1);
    wdgtGrid->addWidget(lB_fiyat   , 3, 0, 1, 1);
    wdgtGrid->addWidget(lE_fiyat   , 3, 1, 1, 1);
    wdgtGrid->addWidget(lB_aciklama, 4, 0, 1, 1);
    wdgtGrid->addWidget(lE_aciklama, 4, 1, 1, 1);

}


void hC_MLZMGC::kntrl()
{
    qDebug() << "  mlzmGc_kntrl";

    tb_slctnMdl = tb_view->table->selectionModel();
    qDebug () <<"  "<< *tb_name << "Selected: " <<  tb_slctnMdl <<".";
    /////////////////////////////////////////////////////
    /// mlzm göster

    mlzm = new hC_MLZM;
    mlzmBarkod = new QString;
    mlzm->setup();
    mlzm->show();
    // /// 12- set filter

    connect(mlzm, &hC_MLZM::sgnMalzeme ,
            [this ] (QString* sgnKod,
                     QString* sgnBarkod,
                     QString* sgnMalzeme,
                     QString* sgnBirim)
    {
        mlzmKod     = sgnKod ;
        mlzmBarkod  = sgnBarkod ;
        mlzmMalzeme = sgnMalzeme ;
        mlzmBirim   = sgnBirim ;
        // malzeme kod a göre filtrele
        tb_model->setFilter(
                    QString("mlzmdet_mlzm_kod = %1")
                    .arg(*mlzmKod) );
    });


    /////////////////////////////////////////////////////



    /// MlzmGc table da koon değiştiğnde index değişsin
    connect(  tb_slctnMdl, &QItemSelectionModel::currentRowChanged,
              tb_mapper,       &QDataWidgetMapper::setCurrentModelIndex);



    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            //this , &hC_MLZMGC::slt_Mlzmd_pB_EKLE_clicked  )) ;
            [] ()
    {

        QWidget *dia = new QWidget();
        auto *gg = new QGridLayout;
        dia->setLayout (gg);

        dia->setWindowTitle ("Giriş Tipi");
        dia->setMinimumSize (250,200);

        QPushButton* fat = new QPushButton("Faturalı Malzeme Girişi",dia);
        QPushButton* fat1 = new QPushButton("Hibe Giriş",dia);
        QPushButton* fat2 = new QPushButton("Envanter Giriş",dia);
        QPushButton* fat3 = new QPushButton("Malzeme Teslim Fişi ile Çıkış",dia);
        fat->setDefault (true) ;

        QGroupBox *ft = new QGroupBox("Mlzm Malzeme Giriş Tipi",dia);
        auto *ff = new QVBoxLayout();
        ff->addWidget (fat);
        ff->addWidget (fat1);
        ff->addWidget (fat2);
        ff->addWidget (fat3);
        ft->setLayout (ff);

        gg->addWidget (ft);
        /////////////////////////////////////////////
        /// Faturalı Giriş

        connect(fat, &QPushButton::clicked,
                [dia]()
        {
            auto *ftr = new hC_FTR;
            ftr->show ();
            ftr->setup ();
            dia->close ();
        });

        /////////////////////////////////////////////
        /// Hibe Giriş

        /////////////////////////////////////////////
        /// Envanter Giriş


        /////////////////////////////////////////////
        /// Malzeme Teslim Fişi ile Çıkış

        dia->show ();
    });

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this] ()
    {
        QModelIndex mlzmGcIndex =   tb_view->table->currentIndex();
        if( mlzmGcIndex.row() >= 0 )
        {
            QSqlRecord rec = tb_model->record();

            QString val = rec.value(1).toString();
            QMessageBox::StandardButton dlg;

            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n barkodli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                tb_model->removeRow(mlzmGcIndex.row());
                //pmodel->endRemoveColumns();
                tb_model->select ();
            }
        }
    });

}


hC_MLZMGC::~hC_MLZMGC()
{
    qDebug() << "   destructor";
    delete tb_view     ;
    delete tb_model    ;
    delete tb_slctnMdl ;
    delete tb_mapper   ;

    delete tb_name     ;
    delete tb_flds     ;
    delete tb_ndex     ;
    delete tb_wdgts    ;

    delete win_Wdgt  ;
    delete win_Label ;
    delete win_Rsm   ;
/////////////////////////////////////////////////
    delete mlzm         ;
    delete mlzmKod      ;
    delete mlzmBarkod   ;
    delete mlzmMalzeme  ;
    delete mlzmBirim    ;

    delete mlzmGcWdgt   ;

    delete lE_barkod    ;
    delete lE_malzeme   ;
    delete lE_tarih     ;
    delete cbx_grscks   ;
    delete lE_miktar    ;
    delete lE_fiyat     ;
    delete lE_aciklama  ;


}

void hC_MLZMGC::showEvent(QShowEvent *)
{
    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";


}

