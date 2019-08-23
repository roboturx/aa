#include "mlzm_gc.h"

hC_MLZMGC::hC_MLZMGC() : hC_tBcreator ()
{
    qDebug() << "Constructor MALZEME GİRİŞ ÇIKIŞ *********************************";
    //************************************************************
    //*****************  M A L Z E M E G C ***********************

    win_Label->setText ( "AMBAR MALZEME GİRİŞ-ÇIKIŞ KAYITLARI");
    *tb_name = "mlzmgc_dbtb" ;
    *tb_ndex = "mlzmgc_tarih";

    tb_flds = new hC_ArrD (13, 4);
    tb_flds->setValue ( 0, "mlzmgc_ID"      , "INTEGER", "MalzemeGcID", "0" ) ;
    tb_flds->setValue ( 1, "mlzmgc_mlzm_kod", "INTEGER", "Malzeme Kod", "0" );
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

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( lE_kod = new QLineEdit   ) ; // mlzm_kod
    tb_wdgts->append ( hClE_barkod = new hC_Le    ) ; // barkod
    tb_wdgts->append ( hClE_malzeme = new hC_Le   ) ; // malzeme
    tb_wdgts->append ( lE_tarih = new QLineEdit  ) ;
    tb_wdgts->append ( cbx_grscks = new QComboBox  ) ;
    tb_wdgts->append ( hCle_gcno = new hC_Le ) ; // gcno
    tb_wdgts->append ( lE_miktar = new QLineEdit  ) ;
    tb_wdgts->append ( cbx_birim = new QComboBox  ) ; // birim
    tb_wdgts->append ( lE_fiyat = new QLineEdit ) ;
    tb_wdgts->append ( spn_kdv = new QSpinBox  ) ; // kdv
    tb_wdgts->append ( lE_aciklama = new QLineEdit    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}


void hC_MLZMGC::tbsetup()
{
    qDebug() << "   mlzmGc_setup";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tb_mapper->addMapping (hClE_barkod->lineEdit ,
                           tb_model->fieldIndex ("mlzmgc_barkod"));
    tb_mapper->addMapping (hClE_malzeme->lineEdit ,
                           tb_model->fieldIndex ("mlzmgc_malzeme"));
    tb_mapper->addMapping (hCle_gcno->lineEdit ,
                           tb_model->fieldIndex ("mlzmgc_gcno"));
    //tb_mapper->addMapping (cbx_grscks,
      //                     tb_model->fieldIndex ("mlzmgc_barkod"));
    tbwdgt  ();
    tbui();
    tbkntrl ();
}




void hC_MLZMGC::tbwdgt()
{
    qDebug() << "   mlzmGc_wdgt";

    win_hC_MLZM = new hC_MLZM;
    win_hC_MLZM->tbsetup();
    /// malzeme penceresini açalım "Envanter Giriş" için
    win_hC_MLZM->setVisible (false);
    /// saklamıyoruz çünkü ilk önce
    /// envanter giriş modunda işlem yapacak

    win_hC_FTR = new hC_FTR;
    win_hC_FTR->tbsetup ();
    win_hC_FTR->setVisible (false);
    /// sakladık "faturalı giriş" modunda ortaya çıkacak


    auto *lB_kd = new QLabel("Malzeme Kodu");
    lB_kd->setBuddy(lE_kod);

    auto *lB_bk = new QLabel("Barkod");
    lB_bk->setBuddy(hClE_barkod);
    hClE_barkod->setWhatsThis ("Buradan barkod seçimi yapabilirsiniz.");
    hClE_malzeme ->setWhatsThis ("Buradan malzeme seçimi yapabilirsiniz.");


    // malzeme ismini fatyraya ekle
    connect(hClE_barkod->pushButton , &QPushButton::clicked,
            [this]()
    {
        // malzeme seçebilmek için malzeme penceresi
        auto diabarkod = new QDialog;
        diabarkod->setModal (true);
        auto barkodGrid = new QGridLayout;
        diabarkod->setLayout (barkodGrid);
        diabarkod->setWindowTitle ("MALZEME SEÇİM VE BİLGİ GİRİŞ");
        // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
        diabarkod->setGeometry (100,220,800,500);

        QString* mess = new QString( "<br>"
                                     "<br> Lütfen Girişi yapılan Malzeme bilgilerine "
                                     "<br> Barkod girmek için seçim yapın "
                                     "<br> "
                                     "<br> Eğer aradığınız Barkod listede yoksa yeni  "
                                     "<br> malzeme girişi yaparak işlemi tamamlayın"
                                     "<br>");

        this->setWhatsThis ( *mess);
        this->setToolTipDuration (5000);
        this->setToolTip (*mess);


        // malzeme class ımızı getirelim
        //auto malzeme = new hC_MLZM;
        //malzeme->tbsetup ();
        win_hC_MLZM->setVisible (true);
        barkodGrid->addWidget (win_hC_MLZM ,0 ,0 ,1, 1);
        //diabarkod->show();


        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // malzeme tableviewinde gezinirken malzeme adımız
        // signal ediliyor onu yakalayalım
        // seçim yapılan lineedit e aktaralım
        // ----------------------------------------------------


        connect (win_hC_MLZM, &hC_MLZM::sgnMalzeme,
                 [ this ] ( int* sgnKod,
                 QString* sgnBarkod,
                 QString* sgnMalzeme,
                 QString* sgnBirim)
        {

            *SGNEDmlzmKod     = *sgnKod ;
            *SGNEDmlzmBarkod  = *sgnBarkod ;
            *SGNEDmlzmMalzeme = *sgnMalzeme ;
            *SGNEDmlzmBirim   = *sgnBirim ;

            qDebug ()<< "SGNED barkod pb "
                     << *SGNEDmlzmKod
                     << *SGNEDmlzmBarkod
                     << *SGNEDmlzmMalzeme
                     << *SGNEDmlzmBirim;


            this->lE_kod->setText ( QString::number (*SGNEDmlzmKod) );
            this->hClE_malzeme->lineEdit->setText (*SGNEDmlzmBarkod);
            this->hClE_barkod->lineEdit->setText (*SGNEDmlzmMalzeme);
            this->cbx_birim->setCurrentText (*SGNEDmlzmBirim);
hCle_gcno->lineEdit->setText ("");
            this->hClE_malzeme->lineEdit->setFocus();
        });
        diabarkod->exec ();
    });


    auto *lB_ml = new QLabel("Malzeme");
    lB_ml->setBuddy(hClE_malzeme);
    connect(hClE_malzeme->pushButton , &QPushButton::clicked,
            [this]()
    {
        hClE_barkod->pushButton->clicked ();
        /// mlzm pushbuttonu ile aynı işe yarıyor
    });

    auto *lB_tarih = new QLabel(tr("&Tarih"));
    lE_tarih->setText (QDate::currentDate ().
                       toString ("dd/mm/yy"));
    lB_tarih->setBuddy(lE_tarih);

    auto *lB_grs_cks = new QLabel(tr("İşlem Türü"));
    QStringList GC = {"Envanter Girişi",
                      "Faturalı Giriş",
                      "Çıkış" };
    cbx_grscks->insertItems (0,  GC );
    lB_grs_cks->setBuddy(cbx_grscks);
    connect( cbx_grscks,  &QComboBox::currentIndexChanged,
              []()
    {

    }   );

    auto *lB_gcno = new QLabel(tr("İşlem No"));
    connect(hCle_gcno->pushButton, &QPushButton::clicked,
            [this]()
    {
        // fatura seçebilmek için fatura penceresi
        auto ftr_dia = new QDialog;
        ftr_dia->setModal (true);
        auto layout_diafr = new QGridLayout;
        ftr_dia->setLayout (layout_diafr);
        // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
        ftr_dia->setGeometry (100,220,800,500);
        ftr_dia->setWindowTitle ("FATURA SEÇİM VE BLGİ GİRİŞ");
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


        // fatura  class ımızı getirelim
        win_hC_FTR->setVisible (true);
        layout_diafr->addWidget (win_hC_FTR ,0 ,0 ,1, 1);
        //diafrm->show();


        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // fatura tableviewinde gezinirken fatura no muz
        // signal ediliyor onu yakalayalım
        // seçim yapılan lineedit e aktaralım
        // ----------------------------------------------------


        connect (win_hC_FTR, &hC_FTR::sgnFtr ,
                 [ this ] (QString* secfatura )
        {
            this->hCle_gcno->lineEdit->setText (*secfatura);
            this->hCle_gcno->lineEdit->setFocus();
        });
        ftr_dia->exec ();
    } );
    lB_gcno->setBuddy(hCle_gcno);

    auto *lB_miktar = new QLabel(tr("&Miktar"));
    lB_miktar->setBuddy(lE_miktar);

    auto *lB_birim = new QLabel(tr("&Birim"));
    lB_birim->setBuddy(cbx_birim);


    auto *lB_fiyat = new QLabel(tr("&Fiyat"));
    lB_fiyat->setBuddy(lE_fiyat);

    auto *lB_kdv = new QLabel(tr("&KDV"));
    lB_kdv->setBuddy(spn_kdv);

    auto *lB_aciklama = new QLabel(tr("&Açıklama"));
    lB_aciklama->setBuddy(lE_aciklama);


    hC_Rs resim(win_Rsm);

    ///////////////////////////////////////

    win_Wdgt->adjustSize();
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_aciklama->setMinimumSize (200,25);

    int str = 0;
    wdgtGrid->addWidget(lB_kd        , str, 0, 1, 1);
    wdgtGrid->addWidget(lE_kod       , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_bk        , ++str, 0, 1, 1);
    wdgtGrid->addWidget(hClE_barkod  , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_ml        , ++str, 0, 1, 1);
    wdgtGrid->addWidget(hClE_malzeme , str, 1, 1, 1);

    wdgtGrid->addWidget(lB_tarih   , ++str, 0, 1, 1);
    wdgtGrid->addWidget(lE_tarih   , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_grs_cks , ++str, 0, 1, 1);
    wdgtGrid->addWidget(cbx_grscks , str, 1, 1, 1);

    wdgtGrid->addWidget(lB_gcno    , ++str, 0, 1, 1);
    wdgtGrid->addWidget(hCle_gcno  , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_miktar  , ++str, 0, 1, 1);
    wdgtGrid->addWidget(lE_miktar  , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_birim   , ++str, 0, 1, 1);
    wdgtGrid->addWidget(cbx_birim  , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_fiyat   , ++str, 0, 1, 1);
    wdgtGrid->addWidget(lE_fiyat   , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_kdv     , ++str, 0, 1, 1);
    wdgtGrid->addWidget(spn_kdv    , str, 1, 1, 1);
    wdgtGrid->addWidget(lB_aciklama, ++str, 0, 1, 1);
    wdgtGrid->addWidget(lE_aciklama, str, 1, 1, 1);

}


void hC_MLZMGC::tbui()
{

    qDebug() << "   MlzmGc_ui";
    setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout(this);  // 100150
    win_Grid->addWidget (tb_view , 0, 0, 1, 6);
    win_Grid->addWidget (win_Wdgt  , 0, 6, 1, 4);



}



void hC_MLZMGC::tbkntrl()
{
    qDebug() << "   mlzmGc_kntrl";
this->setObjectName ("oMLZMGC");

    SGNEDmlzmKod = new int {};
    SGNEDmlzmBarkod = new QString {};
    SGNEDmlzmMalzeme = new QString {};
    SGNEDmlzmBirim = new QString {};

    SGNEDfaturaNo = new QString{};


    /// fatura penceresini açalım "Faturalı Giriş" için

    /// mlzm kod indexi nedir
    /// pencere ilk açıldığında gürüş öıkışta
    /// yeni kayıt eklenmek isterse
    QModelIndex Index = win_hC_MLZM-> tb_view->table->currentIndex ();

    *SGNEDmlzmKod = win_hC_MLZM->tb_view->table->model()->index( Index.row() ,
                     tb_model->fieldIndex ("mlzm_id") ).data().toInt();




    /// malzeme gc ilk açıldığında malzemedeki
    /// bilgileri ilk olarak aktaralım
    /// bu değişkenler sonrasında
    /// her mlzm row değiştiğinde signal ile değşştirilecek

    *SGNEDmlzmKod = win_hC_MLZM->tb_view->table->model()->
            index( Index.row(), win_hC_MLZM->tb_model->
                   fieldIndex ("mlzm_id") ).data().toInt();

    *SGNEDmlzmBarkod = win_hC_MLZM->tb_view->table->model()->
            index( Index.row(), win_hC_MLZM->tb_model->
                   fieldIndex ("mlzm_barkod") ).data().toString();

    *SGNEDmlzmMalzeme = win_hC_MLZM->tb_view->table->model()->
            index( Index.row(), win_hC_MLZM->tb_model->
                   fieldIndex ("mlzm_malzeme") ).data().toString();

    *SGNEDmlzmBirim =  win_hC_MLZM->tb_view->table->model()->
            index( Index.row(), win_hC_MLZM->tb_model->
                   fieldIndex ("mlzm_birim") ).data().toString();

    setWindowTitle (QString::number (*SGNEDmlzmKod)+" - "+
                                     *SGNEDmlzmBarkod+" - "+
                                     *SGNEDmlzmMalzeme+" - "+
                    "GİRİŞ ÇIKIŞ KAYITLARI");

       // /// 12- set filter

    connect( win_hC_MLZM, & hC_MLZM::sgnMalzeme ,
             [this]( int* sgnKod,
             QString* sgnBarkod,
             QString* sgnMalzeme,
             QString* sgnBirim )

    {
        /// malzemede row depiştiğinde bunlarda değişir
        *SGNEDmlzmKod = *sgnKod;
        *SGNEDmlzmBarkod = *sgnBarkod;
        *SGNEDmlzmMalzeme = *sgnMalzeme;
        *SGNEDmlzmBirim = *sgnBirim;

        setWindowTitle (QString::number (*SGNEDmlzmKod)+" - "+
                                         *SGNEDmlzmBarkod+" - "+
                                         *SGNEDmlzmMalzeme+" - "+
                        "GİRİŞ ÇIKIŞ KAYITLARI");

        // malzeme değiştiği için maşlzemeye göre filtrele
        tb_model->setFilter(
                    QString("mlzmgc_mlzm_kod = %1").arg (*sgnKod) );
    });
    connect( win_hC_FTR, & hC_FTR::sgnFtr ,
             [this]( QString* sgnGcno )

    {
        /// malzemede row depiştiğinde bunlarda değişir
        *SGNEDfaturaNo = *sgnGcno;

        setWindowTitle (*SGNEDfaturaNo+" - nolu faturaya ait "+
                        "GİRİŞ ÇIKIŞ KAYITLARI");


        tb_model->setFilter(
                    QString("mlzmgc_gcno = %1").arg (*SGNEDfaturaNo) );
    });

    /////////////////////////////////////////////////////


    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this] ()
    {
        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id     = maxID.hC_NrMax ( tb_name,
                            tb_flds->value (0,0));
        ////////////////////////////////////////////////

            QSqlQuery q;
            QString qry, mesaj("");
            // yeni kaydı ekle

            qry = QString("INSERT INTO " + *tb_name +
                          " ( mlzmgc_mlzm_kod, "
                          "   mlzmgc_barkod  , "
                          "   mlzmgc_malzeme , "
                          "   mlzmgc_tarih , "
                          "   mlzmgc_gc , "
                          "   mlzmgc_gcno , "
                          "   mlzmgc_birim    ) "
                          "values( %1, '%2', '%3', '%4', '%5', "
                          "      '%6', '%7' )")
                    .arg (*SGNEDmlzmKod )
                    .arg (*SGNEDmlzmBarkod)
                    .arg (*SGNEDmlzmMalzeme)
                    .arg (lE_tarih->text ())
                    .arg ("Envanter Girişi")
                    .arg (hCle_gcno->lineEdit->text ())
                    .arg (*SGNEDmlzmBirim);

            if ( !q.exec(qry) )
            {
                mesaj = mesaj + " Malzeme Giriş-Çıkış kaydı Eklenemedi"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + " Malzeme Giriş-Çıkış kaydı eklendi.";


                ////////////////////////////////////////////////
                /// son eklenen kayda git
                maxID.hC_NrGo (tb_view, tb_model, *max_id , 0,4);
                ////////////////////////////////////////////////

                //lE_kod->setText (QString::number (*SGNEDmlzmKod));
                //hClE_barkod->lineEdit->setText (*SGNEDmlzmBarkod );
                //hClE_malzeme->lineEdit->setText (*SGNEDmlzmMalzeme);
                //lE_tarih->setText (
                  //          QDate::currentDate ().toString ("dd-mm-yyyy"));
                //cbx_grscks->setCurrentText ("");
                //hCle_gcno->lineEdit->setText ("");
                lE_miktar ->setText ("");
                cbx_birim ->setCurrentText (*SGNEDmlzmBirim);
                lE_fiyat ->setText ("");
                spn_kdv ->setValue (18);
                lE_aciklama ->setText ("");
            }
            qDebug()<<mesaj;

            // mlzmGC  ekle


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
    qDebug() << "*********** destructor MALZEME GİRİŞ ÇIKIŞ ";//    delete ui;


    delete tb_flds     ;

    delete tb_wdgts    ;

    delete win_Wdgt  ;
    delete win_Label ;
    delete win_Rsm   ;
    /////////////////////////////////////////////////
    delete win_hC_MLZM        ;
    delete SGNEDmlzmKod      ;
    delete SGNEDmlzmBarkod   ;
    delete SGNEDmlzmMalzeme  ;
    delete SGNEDmlzmBirim    ;

    //   delete mlzmGcWdgt   ;

    //delete hClE_barkod   ;
    //  delete hClE_malzeme   ;
    //delete lE_tarih     ;
    //delete cbx_grscks   ;
    //delete lE_miktar    ;
    //  delete lE_fiyat     ;
    //delete lE_aciklama  ;


}

void hC_MLZMGC::showEvent(QShowEvent *)
{
    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";


}

