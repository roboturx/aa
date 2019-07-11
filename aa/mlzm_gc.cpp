#include "mlzm_gc.h"

hC_MLZMGC::hC_MLZMGC(QWidget *parent) : QWidget(parent)
{
    //************************************************************
    //*****************  M A L Z E M E  **************************
    qDebug() << "Cnstrctr mlzmGc";
}


void hC_MLZMGC::mlzmGc_setup()
{
    qDebug() << "  mlzmGc_setup";

    mlzmGc_VTd   () ;
    mlzmGc_model () ;
    mlzmGc_wdgt  () ;
    mlzmGc_map   () ;
    mlzmGc_ui    () ;
    mlzmGc_view  () ;
    mlzmGc_kntrl () ;
}




void hC_MLZMGC::mlzmGc_ui()
{

    qDebug() << "  MlzmGc_ui";
    ////////////////////////////////////////// window
    winLabel = new QLabel("AMBAR MALZEME GİRİŞ-ÇIKIŞ KONTROL");
    hC_MLZMGC::setWindowTitle (winLabel->text ());
    //hC_MLZMGC::showMaximized ();

    //////////////////////////////////// mlzmGc tableview
    MLZMGCtview = new hC_Tv (MLZMGCmodel, MLZMGCmapper, winWdgt );

    ////////////////////////////////////////////// layout
    auto *mlzmGcGrid = new QGridLayout(this);  // 100150

    mlzmGcGrid->addWidget (MLZMGCtview , 0, 0, 1, 6);
    mlzmGcGrid->addWidget (mlzmGcWdgt  , 0, 6, 1, 4);
}



void hC_MLZMGC::mlzmGc_wdgt()
{
    qDebug() << "  mlzmGc_wdgt";

    auto *lB_tarih = new QLabel(tr("&Tarih"));
    lE_tarih = new QLineEdit();
    lB_tarih->setBuddy(lE_tarih);

    auto *lB_grs_cks = new QLabel(tr("Grş_Çkş"));
    cbx_grscks = new QComboBox;

    QStringList GC = {"Faturalı Giriş",
                      "Çıkış" };
    cbx_grscks->insertItems (0,  GC );
    lB_grs_cks->setBuddy(cbx_grscks);

    auto *lB_miktar = new QLabel(tr("&Miktar"));
    lE_miktar = new QLineEdit();
    lB_miktar->setBuddy(lE_miktar);

    auto *lB_fiyat = new QLabel(tr("&Fiyat"));
    lE_fiyat = new QLineEdit();
    lB_fiyat->setBuddy(lE_fiyat);

    auto *lB_aciklama = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_aciklama->setBuddy(lE_aciklama);

    winRsm  = new QLabel (tr("Resim"));
    hC_Rs resim(winRsm);

    ///////////////////////////////////////
    mlzmGcWdgt = new QWidget;
    mlzmGcWdgt->setGeometry (0,0,800,300);
    auto gridMlzm = new QGridLayout();
    mlzmGcWdgt->setLayout(gridMlzm);

    ///////////////////////////////////////
    lE_aciklama->setMinimumSize (200,25);

    gridMlzm->addWidget(lB_tarih   , 0, 0, 1, 1);
    gridMlzm->addWidget(lE_tarih   , 0, 1, 1, 1);
    gridMlzm->addWidget(lB_grs_cks , 1, 0, 1, 1);
    gridMlzm->addWidget(cbx_grscks , 1, 1, 1, 1);
    gridMlzm->addWidget(lB_miktar  , 2, 0, 1, 1);
    gridMlzm->addWidget(lE_miktar  , 2, 1, 1, 1);
    gridMlzm->addWidget(lB_fiyat   , 3, 0, 1, 1);
    gridMlzm->addWidget(lE_fiyat   , 3, 1, 1, 1);
    gridMlzm->addWidget(lB_aciklama, 4, 0, 1, 1);
    gridMlzm->addWidget(lE_aciklama, 4, 1, 1, 1);

}



void hC_MLZMGC::mlzmGc_view()
{
    qDebug() << "  mlzmGc_view";

    MLZMGCtview->table->setModel(MLZMGCmodel);
    MLZMGCslctnMdl = MLZMGCtview->table->selectionModel();

    //////////////////////////////////////////////////////////
    //// kullanıcı bu alanları görmesin
    MLZMGCtview->table->setColumnHidden(MLZMGCmodel->fieldIndex("mlzmGc_kod"), true);
    MLZMGCtview->table->setColumnHidden(MLZMGCmodel->fieldIndex("mlzmGc_mlzm_kod"), true);
    MLZMGCtview->table->setColumnHidden(MLZMGCmodel->fieldIndex("mlzmGc_barkod"), true);
    MLZMGCtview->table->setColumnHidden(MLZMGCmodel->fieldIndex("mlzmGc_malzeme"), true);
    MLZMGCtview->table->setColumnHidden(MLZMGCmodel->fieldIndex("mlzmGc_resim"), true);
    //////////////////////////////////////////////////////////
    // with blue rect
    MLZMGCtview->table->setCurrentIndex(
                MLZMGCmodel->index(1, 1) );

    MLZMGCtview->table->setFocus();
}

void hC_MLZMGC::mlzmGc_map()
{
    qDebug() << "  mlzmGc_map";
    MLZMGCmapper = new QDataWidgetMapper(this);
    MLZMGCmapper->setModel(MLZMGCmodel);

    //MLZMGCmapper->addMapping(lE_barkod , MLZMGCmodel->fieldIndex("barkod"));
    //MLZMGCmapper->addMapping(lE_malzeme, MLZMGCmodel->fieldIndex("malzeme"));
    MLZMGCmapper->addMapping(lE_tarih, MLZMGCmodel->fieldIndex("mlzmgc_tarih"));
    MLZMGCmapper->addMapping(cbx_grscks, MLZMGCmodel->fieldIndex("mlzmgc_gc"));
    MLZMGCmapper->addMapping(lE_miktar, MLZMGCmodel->fieldIndex("mlzmgc_miktar"));
    MLZMGCmapper->addMapping(lE_fiyat, MLZMGCmodel->fieldIndex("mlzmgc_fiyat"));
    MLZMGCmapper->addMapping(lE_aciklama, MLZMGCmodel->fieldIndex("mlzmgc_aciklama"));

    hC_MLZMGC::MLZMGCmapper->toFirst() ;
}



void hC_MLZMGC::mlzmGc_kntrl()
{
    qDebug() << "  mlzmGc_kntrl";

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
        MLZMGCmodel->setFilter(
                    QString("mlzmdet_mlzm_kod = %1")
                    .arg(*mlzmKod) );
    });


    /////////////////////////////////////////////////////

    /// MlzmGc table da koon değiştiğnde index değişsin
    connect(  MLZMGCslctnMdl, &QItemSelectionModel::currentRowChanged,
              MLZMGCmapper,       &QDataWidgetMapper::setCurrentModelIndex);



    connect(MLZMGCtview->pB_ekle, &QPushButton::clicked ,
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
            ftr->ftr_setup ();
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

    connect(MLZMGCtview->pB_sil, &QPushButton::clicked,
            [this] ()
    {
        QModelIndex mlzmGcIndex =   MLZMGCtview->table->currentIndex();
        if( mlzmGcIndex.row() >= 0 )
        {
            QSqlRecord rec = MLZMGCmodel->record();

            QString val = rec.value(1).toString();
            QMessageBox::StandardButton dlg;

            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n barkodli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                MLZMGCmodel->removeRow(mlzmGcIndex.row());
                //pmodel->endRemoveColumns();
                MLZMGCmodel->select ();
            }
        }
    });
/*
    connect(MLZMGCtview->pB_ilk, &QPushButton::clicked ,
            [this] ()
    {
        MLZMGCtview->hC_TvPb ("ilk", MLZMGCmodel, MLZMGCmapper);
    });


    connect(MLZMGCtview->pB_ncki, &QPushButton::clicked,
            [this] ()
    {
        MLZMGCtview->hC_TvPb ("ncki", MLZMGCmodel, MLZMGCmapper);
    });

    connect(MLZMGCtview->pB_snrki, &QPushButton::clicked,
            [this] ()
    {
        MLZMGCtview->hC_TvPb ("snrki", MLZMGCmodel, MLZMGCmapper);
    });


    connect(MLZMGCtview->pB_son, &QPushButton::clicked,
                  [this] ()
    {
        MLZMGCtview->hC_TvPb ("son", MLZMGCmodel,MLZMGCmapper);
    });


    connect(MLZMGCmapper, &QDataWidgetMapper::currentIndexChanged,
            [this ]()
    {
        MLZMGCtview->hC_TvPb ("yenile", MLZMGCmodel, MLZMGCmapper);
    });
*/

}



hC_MLZMGC::~hC_MLZMGC()
{
    qDebug() << "   destructor";
}

void hC_MLZMGC::showEvent(QShowEvent *)
{
    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";
}













///
/// \brief DBase::VTd_MlzmDETAY
/// \return
///
QString hC_MLZMGC::mlzmGc_VTd ()
{
    QString ct, mesaj = "  OK - Malzeme Detay";
    QSqlQuery q;
    QString MLZDETtableName ( "mlzmGc__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().
         tables().contains( MLZDETtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + MLZDETtableName +
             "("
             "mlzmgc_kod integer primary key, "
             "mlzmgc_mlzm_kod	INTEGER, "
             "mlzmgc_barkod	TEXT , "
             "mlzmgc_malzeme	TEXT , "
             "mlzmgc_tarih	    TEXT , "
             "mlzmgc_gc        TEXT , "    // faturalı giriş vs.
                "mlzmgc_gcno      TEXT , "    // fatura no  vs.
                "mlzmgc_miktar    TEXT , "
                "mlzmgc_birim     TEXT , "
                "mlzmgc_fiyat     TEXT , "
                "mlzmgc_kdv       TEXT , "
                "mlzmgc_aciklama  TEXT ,  "
                "mlzmgc_resim  BLOB  "
                ")";

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Malzeme Detay Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Malzeme Detay Dosyası YENİ Oluşturuldu";

            if (q.exec("INSERT INTO " + MLZDETtableName +
                       "( mlzmGc_malzeme, mlzmgc_gc, mlzmgc_gcno )"
                       " values( '1 nolu ürüne ait detay','Faturalı Giriş','1' )"  ))
            {
                mesaj = mesaj + "<br>İLK kayıt eklendi";
            }
            else
            {
                mesaj = mesaj +"<br>İLK Kayıt EKLENEMEDİ "
                               "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;
}   /// malzeme detay


void hC_MLZMGC::mlzmGc_model ()
{
    /// NOTE Model 1 mw_main de modeli oluştur
    /// fatura detayında
    /// malzeme detay dosyası oluşturuluyor
    QString tableName ("mlzmGc__dbtb");
    QString indexField = "mlzmGc_gcno";

    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Detay Kod");
    tB_FieldList->append("Malzeme Kod");
    tB_FieldList->append("Barkod");
    tB_FieldList->append("Malzeme");
    tB_FieldList->append("Tarih");
    tB_FieldList->append("İşlem Türü");
    tB_FieldList->append("İşlem No");
    tB_FieldList->append("Miktar");
    tB_FieldList->append("Birim");
    tB_FieldList->append("Fiyat");
    tB_FieldList->append("KDV");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Resim");

    MLZMGCmodel = new QSqlRelationalTableModel ;
  /*  hC_Rm hC_Rm (&tableName,
                 MLZMGCmodel,
                 &indexField ,
                 tB_FieldList) ;
*/
}///fsturs detsy Model






/*
// //////////////////////////////////////// Fatura Detaya malzeme ekle
// FtrDet_MlzEkle


FtrDet_MlzEkle::FtrDet_MlzEkle(QDialog *parent) : QDialog(parent)
{
    this->setModal (true);
    auto layout_diafr = new QGridLayout(this);
    this->setLayout (layout_diafr);
    // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
    this->setGeometry (100,220,800,500);

    this->setWhatsThis ("<br>"
                        "<br> Lütfen Girişi yapılan fatura bilgilerine "
                        "<br> Firma ünvanı girmek için seçim yapın "
                        "<br> "
                        "<br> Eğer aradığınız firma listede yoksa yeni  "
                        "<br> firma girişi yaparak işlemi tamamlayın"
                        "<br>");
    this->setToolTipDuration (5000);
    this->setToolTip ("<br>"
                      "<br> Lütfen Girişi yapılan fatura bilgilerine "
                      "<br> Firma ünvanı girmek için seçim yapın "
                      "<br> "
                      "<br> Eğer aradığınız firma listede yoksa yeni  "
                      "<br> firma girişi yaparak işlemi tamamlayın"
                      "<br>");


    // malzemefirma class ımızı getirelim
    malzeme = new hC_MLZM ;
    malzeme->mlzm_setup ();
    layout_diafr->addWidget (malzeme ,0 ,0 ,1, 1);
    //diafr->show();


    /////////////////////////////////////////////////////////////////////////////////
    // ----------------------------------------------------
    // firma tableviewinde gezinirken firma adımız
    // seçim yapılan lineedit e aktaralım
    // ----------------------------------------------------
    connect (malzeme->MLZMslctnMdl,
             &QItemSelectionModel::currentChanged  ,
             [ this ] (QModelIndex Index )

    {

        //QModelIndex firmandx = firma->FRMtview->table->currentIndex ()  ;
        int fr_row = Index.row ();
        this->setMalzeme (malzeme->MLZMmodel->data(
                              malzeme->MLZMmodel->index
                              (fr_row,malzeme->MLZMmodel->fieldIndex ("mlzm_malzeme"))
                              ).toString () )  ;

    });

    this->show ();
}

void FtrDet_MlzEkle::reject()
{
    QDialog::reject();
}


FtrDet_MlzEkle::~FtrDet_MlzEkle()
{
}

QString FtrDet_MlzEkle::getMalzeme() const
{
    return m_malzeme;
}

void FtrDet_MlzEkle::setMalzeme(const QString &value)
{
    m_malzeme = value;
}



*/
