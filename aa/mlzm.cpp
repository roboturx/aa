#include "mlzm.h"

hC_MLZM::hC_MLZM(QWidget *parent) : QWidget(parent)
{
    qDebug() << "  cnstrct mlzm";
    //************************************************************
    //*****************  M A L Z E M E  **************************

    win_Label = new QLabel ("AMBAR MALZEME");

    tB_name = new QString ("mlzm_dbtb") ;


    tB_fields = new hC_ArrD (13, 4);
    tB_fields->setValue ( 0, "mlzm_ID"      , "INTEGER", "MalzemeID", "0" ) ;
    tB_fields->setValue ( 1, "mlzm_barkod"  , "TEXT"   , "Barkod" );
    tB_fields->setValue ( 2, "mlzm_malzeme" , "TEXT"   , "Malzeme" );
    tB_fields->setValue ( 3, "mlzm_aciklama", "TEXT"   , "Açıklama");
    tB_fields->setValue ( 4, "mlzm_marka"   , "TEXT"   , "Marka"   );
    tB_fields->setValue ( 5, "mlzm_model"   , "TEXT"   , "Model"   );
    tB_fields->setValue ( 6, "mlzm_cins"    , "TEXT"   , "Cins"    );
    tB_fields->setValue ( 7, "mlzm_birim"   , "TEXT"   , "Birim"   );
    tB_fields->setValue ( 8, "mlzm_giris"   , "TEXT"   , "Giriş Toplamı");
    tB_fields->setValue ( 9, "mlzm_cikis"   , "TEXT"   , "Çıkış Toplamı");
    tB_fields->setValue (10, "mlzm_mevcut"  , "TEXT"   , "Ambar Mevcudu");
    tB_fields->setValue (11, "mlzm_makina"  , "TEXT"   , "Makina", "0");
    tB_fields->setValue (12, "mlzm_resim"   , "BLOB"   , "Resim" , "0" );

    tB_ndex = new QString ("malzeme");

    tB_view = new hC_Tv;
    tB_modl = new QSqlRelationalTableModel;
    tB_map = new QDataWidgetMapper;

    tB_wdgts = new QList <QWidget*> ;
    tB_wdgts->append ( nullptr    ) ;
    tB_wdgts->append ( lE_barkod = new QLineEdit  ) ;
    tB_wdgts->append ( lE_malzeme = new QLineEdit  ) ;
    tB_wdgts->append ( lE_aciklama = new QLineEdit ) ;
    tB_wdgts->append ( lE_marka = new QLineEdit    ) ;
    tB_wdgts->append ( lE_model = new QLineEdit    ) ;
    tB_wdgts->append ( lE_cins = new QLineEdit     ) ;
    tB_wdgts->append ( cbx_birim = new QComboBox   ) ;
    tB_wdgts->append ( lE_giris = new QLineEdit    ) ;
    tB_wdgts->append ( lE_cikis  = new QLineEdit   ) ;
    tB_wdgts->append ( lE_mevcut  = new QLineEdit  ) ;
    tB_wdgts->append ( nullptr    ) ;
    tB_wdgts->append ( win_Rsm  = new QLabel    ) ;

  qDebug() << "  cnstrct mlzm son";
}


void hC_MLZM::setup()
{


    hC_tBcreator (tB_name,
                  tB_fields,
                  tB_ndex,
                  tB_view,
                  tB_modl,
                  tB_slctnMdl,
                  tB_map,
                  tB_wdgts) ;

    wdgt  () ;
    ui    () ;
    kntrl () ;
}



void hC_MLZM::ui()
{
    qDebug() << "  Mlzm_ui";

    setWindowTitle (win_Label->text());
    tB_view = new hC_Tv (tB_modl, tB_map, win_Wdgt);

    ////////////////////////////////////////////// layout
    auto *mlzmGrid = new QGridLayout(this);  // 100150
    mlzmGrid->addWidget (tB_view       , 0, 0, 1, 5);
    mlzmGrid->addWidget (win_Wdgt        , 0, 5, 1, 5);
}


void hC_MLZM::wdgt()
{
    qDebug () << "  wdgt";

    auto *lB_barkod = new QLabel(tr("&Barkod"));
   // lE_barkod = new QLineEdit();
    lB_barkod->setBuddy(lE_barkod);

    auto lB_brkd = new QLabel();
    lB_brkd->setFont (QFont ("code128",30));
    lB_brkd->setText (lE_barkod->text ());

    auto *lB_malzeme = new QLabel(tr("&Malzeme"));
   // lE_malzeme = new QLineEdit();
    lB_malzeme->setBuddy(lE_malzeme);

    auto *lB_aciklama = new QLabel(tr("&Açıklama"));
    //lE_aciklama = new QLineEdit();
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_marka = new QLabel(tr("Ma&rka"));
    //lE_marka = new QLineEdit();
    lB_marka->setBuddy(lE_marka);

    auto *lB_model = new QLabel(tr("Mo&del"));
    //lE_model = new QLineEdit();
    lB_model->setBuddy(lE_model);

    auto *lB_cins = new QLabel(tr("&Cins"));
    ///lE_cins = new QLineEdit();
    lB_cins->setBuddy(lE_cins);

    auto *lB_birim = new QLabel(tr("&Birim"));
    //cbx_birim = new QComboBox;

    QStringList br = {"adet",
                      "takım",
                      "ton",
                      "kg",
                      "gr",
                      "torba"};
    cbx_birim->insertItems (0,  br );
    lB_birim->setBuddy(cbx_birim);

    auto *lB_g = new QLabel(tr("Toplam Giriş"));
   // lE_giris = new QLineEdit();
    lE_giris->setAlignment (Qt::AlignRight);
    lE_giris->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_giris)) ;
    lB_g->setBuddy(lE_giris);

    auto *lB_c = new QLabel(tr("Toplam Çıkış"));
   // lE_cikis = new QLineEdit();
    lE_cikis->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_cikis)) ;
   // lE_cikis->setAlignment (Qt::AlignRight);
    lB_c->setBuddy(lE_cikis);

    auto *lB_m = new QLabel(tr("Ambar Mevcudu"));
   // lE_mevcut = new QLineEdit();
    lE_mevcut->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_mevcut)) ;
   // lE_mevcut->setAlignment (Qt::AlignRight);
    lB_m->setBuddy(lE_mevcut);

   // win_Rsm = new QLabel;
    hC_Rs resim(win_Rsm);

    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto mlzmGrid = new QGridLayout();
    win_Wdgt->setLayout(mlzmGrid);

    ///////////////////////////////////////
    lE_malzeme->setMinimumSize (200,25);

    int str = 0;
    mlzmGrid ->addWidget(lB_barkod  , ++str, 0, 1, 1);
    mlzmGrid ->addWidget(lE_barkod  ,   str, 1, 1, 5);
    mlzmGrid ->addWidget(lB_brkd    ,   str, 5, 1, 5);
    mlzmGrid ->addWidget(lB_malzeme , ++str, 0, 1, 1);
    mlzmGrid ->addWidget(lE_malzeme ,   str, 1, 1, 9);

    mlzmGrid ->addWidget(lB_marka   , ++str, 0, 1, 1);
    mlzmGrid ->addWidget(lE_marka   ,   str, 1, 1, 9);

    mlzmGrid ->addWidget(lB_aciklama, ++str, 0, 1, 1);
    mlzmGrid ->addWidget(lE_aciklama,   str, 1, 1, 9);
    mlzmGrid ->addWidget(lB_model   , ++str, 0, 1, 1);
    mlzmGrid ->addWidget(lE_model   ,   str, 1, 1, 9);

    mlzmGrid ->addWidget (lB_cins   , ++str, 0, 1, 1);
    mlzmGrid ->addWidget (lE_cins   ,   str, 1, 1, 9);

    mlzmGrid ->addWidget (lB_birim  , ++str, 0, 1, 1);
    mlzmGrid ->addWidget (cbx_birim ,   str, 1, 1, 3);
    mlzmGrid ->addWidget (lB_g      , ++str, 0, 1, 1);
    mlzmGrid ->addWidget (lE_giris  ,   str, 1, 1, 3);
    mlzmGrid ->addWidget (lB_c      , ++str, 0, 1, 1);
    mlzmGrid ->addWidget (lE_cikis  ,   str, 1, 1, 3);
    mlzmGrid ->addWidget (lB_m      , ++str, 0, 1, 1);
    mlzmGrid ->addWidget (lE_mevcut ,   str, 1, 1, 3);
    mlzmGrid ->addWidget (win_Rsm, str-3, 4, 4, 6);

}

/*
void hC_MLZM::view()
{
    qDebug() << "  view";

    //////////////////////////////////////////////////////////
    tB_view->table->setModel(tB_modl);
    tB_slctnMdl =   tB_view->table->selectionModel ();

    for (int i = 1 ; i < tB_fields->length () ; i++ )
    {
        if (tB_fields->value (i,3) == "1")
        {
            tB_view->table->setColumnHidden( i , true);
        }
        else if (tB_fields->value (i,3) == "0")
        {
            tB_view->table->setColumnHidden( i , false);

        }
        else
        {
            qDebug ()<< *tB_name << " view colon hidden ERROR";
        }
    }
    //////////////////////////////////////////////////////////
    /// kullanıcı bu alanları görmesin
    tB_view->table->setColumnHidden(tB_modl->fieldIndex("kod"), true);
    //    tB_view->table->setColumnHidden(tB_modl->fieldIndex("giris"), true);
    //    tB_view->table->setColumnHidden(tB_modl->fieldIndex("cikis"), true);
    //    tB_view->table->setColumnHidden(tB_modl->fieldIndex("mevcut"), true);
    tB_view->table->setColumnHidden(tB_modl->fieldIndex("resim"), true);
    tB_view->table->setColumnHidden(tB_modl->fieldIndex("makina"), true);
    //////////////////////////////////////////////////////////
    // with blue rect

    tB_view->table->setCurrentIndex(tB_modl->index(1, 1) );
    tB_view->table->setFocus();
}
*/

//void hC_MLZM::map()
//{
//    qDebug() << "  map";

//    tB_map = new QDataWidgetMapper(this);
//    tB_map->setModel(tB_modl);


//    for (int i=0 ;  i < tB_fields->length () ; i++ )
//    {
//        tB_map->addMapping( tB_wdgts->value(i), i);
//    }
///*
//    tB_map->addMapping( lE_barkod, tB_modl->fieldIndex( "barkod"));
//    tB_map->addMapping( lE_malzeme, tB_modl->fieldIndex("malzeme"));
//    tB_map->addMapping( lE_aciklama, tB_modl->fieldIndex("aciklama"));
//    tB_map->addMapping( lE_marka, tB_modl->fieldIndex("marka"));
//    tB_map->addMapping( lE_model, tB_modl->fieldIndex("model"));
//    tB_map->addMapping( lE_cins, tB_modl->fieldIndex("cins"));
//    tB_map->addMapping( cbx_birim, tB_modl->fieldIndex( "birim" ));
//    tB_map->addMapping( lE_giris, tB_modl->fieldIndex("giris"));
//    tB_map->addMapping( lE_cikis, tB_modl->fieldIndex("cikis"));
//    tB_map->addMapping( lE_mevcut, tB_modl->fieldIndex("mevcut"));
//    //tB_map->addMapping( cX_mkn, tB_modl->fieldIndex("makina"));

//*/

//    connect(map, &QDataWidgetMapper::currentIndexChanged,
//            [this, map, model]( )
//    {
//        int map_row = map->currentIndex ();
//        this->pB_ilk->setEnabled (map_row>0);
//        this->pB_ncki->setEnabled(map_row > 0);
//        this->pB_snrki->setEnabled(map_row < model->rowCount() - 1);
//        this->pB_son->setEnabled(map_row < model->rowCount() - 1);
//    });



//    hC_MLZM::tB_map->toFirst() ;
//}



void hC_MLZM::kntrl()
{
    qDebug() << "  kntrl";






    // /// yeni malzeme ekle
    connect(tB_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QString IEtableName{"_dbtb"};
        QSqlQuery q;
        QString qry, mesaj("");
        /// yeni barkod numarasını bul
        /// barkod nosu _dbtb de
        /// barkod alanındaki en büyük sayı
        qry = "SELECT max(kod) FROM " + IEtableName  ;
        int mlzmno;
        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "Malzeme No bulunamadı \n"+
                    "------------------------------------\n"+
                    q.lastError().text ()+
                    "------------------------------------\n";
            return;
        }
        else
        {
            q.next();
            mlzmno = q.value(0).toInt ();
            mesaj = mesaj + "MAX VAL = " + QString::number(mlzmno) ;
        }

        mlzmno = mlzmno + 1  ;

        // yeni kaydı ekle
        qry = "INSERT INTO " + IEtableName +
                " ( barkod) values( ' ' )" ;

        if ( !q.exec(qry) )
        {
            mesaj = mesaj + " Malzeme kaydı Eklenemedi"+
                    "<br>------------------------------------<br>"+
                    q.lastError().text ()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = mesaj + " Malzeme kaydı eklendi.";

            lE_barkod->setText ("");
            lE_malzeme->setText ("");
            lE_marka->setText ("");
            lE_aciklama ->setText ("");
            lE_model ->setText ("");
            lE_cins ->setText ("");
            cbx_birim ->setCurrentText (" ");
            lE_giris ->setText ("");
            lE_cikis ->setText ("");
            lE_mevcut ->setText ("");
        }
        qDebug()<<mesaj;
        tB_modl->select();
        ////////////////////////////////////////////////
        hC_Nr (tB_view, mlzmno, 0);
        ////////////////////////////////////////////////
        tB_view->table->setFocus ();
        // mlzm  ekle


    });

    /// // malzeme resmi ekle
    connect(tB_view->pB_eklersm, &QPushButton::clicked,
            [this] ()
    {
        hC_Rs resim (win_Rsm, tB_view, tB_modl, tB_slctnMdl,
                     "resim","ekle");

    });

    connect(tB_view->pB_sil, &QPushButton::clicked,
            [this] ()
    {
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex mlzmIndex =   tB_view->table->currentIndex();
        if( mlzmIndex.row() >= 0 )
        {
            QSqlRecord rec = tB_modl->record(mlzmIndex.row ());
            int Mlzm_no = rec.value ("kod").toInt();
            QString val = rec.value("barkod").toString();
            QString val2= rec.value("malzeme").toString() ;


            /// Mlzm detay kayıtlarını silelim
            /*      QSqlQuery q_qry;
            QString s_qry;
            /// silinecek kayıt sayısı
            s_qry = QString("SELECT count() FROM dbtb_Mlzmdet where Mlzm_no = %1").arg (Mlzm_no);
            q_qry.exec(s_qry);
            int xx = 0 ;

            if ( q_qry.isActive ())
            {
                xx = s_qry.size () ;
                qDebug()<< xx <<" adet kayıt silinecek ";
            }
    */

            QString mess="\n";
            mess +=val + "\n" +
                    val2 +
                    "\n\n  silinsin mi ?\n"+
                    "İşlemi onaylarsanız bu Mlzm kaydına ait\n " ;

            int Mlzmdet_count = 10000000; // = DETmodel->rowCount () ;
            if ( Mlzmdet_count > 0 )
            {
                mess +="\n"+ QString::number (Mlzmdet_count) + " adet DEPO GİRİŞ - ÇIKIŞ kaydı";
            }


            /// model makina kaydı var
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox
                    ::question(this,
                               "KAYIT SİL", mess,
                               QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                /// Mlzmya ait Mlzmdet giriş kayıtlarını sil
                s_qry = QString("DELETE FROM mlzmDet__dbtb where mlzmDet_kod = %1").arg (Mlzm_no);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<<" - "<< Mlzmdet_count << " - adet Mlzm Giriş_Çıkış Kaydı Silindi";
                }
                else
                {
                    qDebug()<< "HATA - Mlzm Giriş Kayıtları Silinemedi"
                            << q_qry.lastError() ;
                }

                /// Mlzm ya ait makina ikmal kayıtlarını silelim
                ///
                /// burada makina ikmal kaydı varsa
                /// makina ikmale bağlı sgrt, muayene vb
                /// tüm kayıtlarıda silmek gerekir
                //  int sil_makina_kayitlerini;


                /// Mlzm kayıtlarını silelim
                s_qry = QString("DELETE FROM _dbtb where kod = %1").arg (Mlzm_no);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<< "1 adet Mlzm Kaydı Silindi";

                    tB_modl->select ();

                    if (tB_modl->rowCount () == 1)
                    {
                        tB_view->table->selectRow (0);
                        tB_view->table->setCurrentIndex (tB_modl->index(0,1));
                    }
                    if (tB_modl->rowCount () > 1)
                    {
                        if (mlzmIndex.row () == 0)
                        {
                            tB_view->table->selectRow (0);
                            tB_view->table->setCurrentIndex (tB_modl->index(0,1));
                        }
                        else if (mlzmIndex.row () > 0)
                        {
                            tB_view->table->selectRow (mlzmIndex.row()-1);
                            tB_view->table->setCurrentIndex (tB_modl->index(mlzmIndex.row ()-1,1));
                        }


                    }
                    else
                    {
                        qDebug()<< "HATA - Mlzm Kaydı Silinemedi"
                                << q_qry.lastError() ;
                    }
                }
                else
                {
                    /// SİLME
                    /// Mlzmya ait Mlzmdet giriş kayıtlarını SİLinMEdi
                }
            }
        }
    });

    /*
    connect(tB_view->pB_ilk, &QPushButton::clicked ,
            [this] ()
    {
     tB_view->hC_MLZMTvPb ("ilk", tB_modl, tB_map);
    });


    connect(tB_view->pB_ncki, &QPushButton::clicked,
            [this] ()
    {
        tB_view->hC_MLZMTvPb ("ncki", tB_modl, tB_map);
    });

    //             &hC_MLZM::slt_Mlzm_toPrevious )) ;
    connect(tB_view->pB_snrki, &QPushButton::clicked,
            [this] ()
    {
        tB_view->hC_MLZMTvPb ("snrki", tB_modl, tB_map);
    });

    //             &hC_MLZM::slt_Mlzm_toNext )) ;
    connect(tB_view->pB_son, &QPushButton::clicked,
            [this] ()
    {
        tB_view->hC_MLZMTvPb ("son", tB_modl, tB_map);
    });

    /// mlzm nav tuslari kontrol
    connect(tB_map, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        tB_view->hC_MLZMTvPb ("yenile", tB_modl, tB_map);
    });
*/
    /// Mlzm da kolon değiştiğinde indexte değişsin
    connect(  tB_slctnMdl, &QItemSelectionModel::currentColumnChanged,
              tB_map, &QDataWidgetMapper::setCurrentModelIndex);

    /// Mlzm da row değiştiğinde indexte değişsin
    connect(  tB_slctnMdl , &QItemSelectionModel::currentRowChanged,
              tB_map, &QDataWidgetMapper::setCurrentModelIndex);

    // malzemede row değiştiğnde 3 şeyi değiştirelim
    // 1 map indexi
    // 2 malzeme kodunu ve ismini yayalım
    // 3 resim
    connect( tB_slctnMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index)
    {


        // 1 map indexi değiştirelim
        tB_map->setCurrentModelIndex(Index);

        // 2 malzeme kod - barkod - isim ve birim yayalım
        ////////////////////////////////////////////////////////////////
        auto kd = new QString;
        *kd = tB_view->table->model()->index( Index.row() ,
                                                tB_modl->fieldIndex ("kod") ).data().toString();

        auto brkd = new QString;
        *brkd = tB_view->table->model()->index( Index.row() ,
                                                  tB_modl->fieldIndex ("barkod") ).data().toString();

        auto mlzm = new QString;
        *mlzm = tB_view->table->model()->index( Index.row() ,
                                                  tB_modl->fieldIndex ("malzeme") ).data().toString();

        auto brm = new QString;
        *brm =  tB_view->table->model()->index( Index.row() ,
                                                  tB_modl->fieldIndex ("birim") ).data().toString();
        ////////////////////////////////////////////////////////////////
        emit hC_MLZM::sgnMalzeme( kd, brkd, mlzm, brm);
        ////////////////////////////////////////////////////////////////
        // 3 resimi değiştirelim
        hC_Rs resim ( win_Rsm, tB_view, tB_modl, tB_slctnMdl,
                      "resim", "değiştir" ) ;


    });


    /// Mlzmdet miktar değiştiğinde Mlzm envanter hesabı
    //   connect (lE_d_miktar, &QLineEdit::editingFinished,
    //          this, &hC_MLZM::slt_Mlzm_hesap);

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın

    connect(tB_slctnMdl, &QItemSelectionModel::currentRowChanged,
            this, &hC_MLZM::slt_Mlzm_hesap);


}









void hC_MLZM::slt_Mlzm_hesap(QModelIndex Index)
{
    if ( Index.row () >= 0 )
    {
        int Mlzm_row = Index.row ();
        int id = tB_modl->
                data ( tB_modl->
                       index(Mlzm_row,tB_modl->
                             fieldIndex("kod"))).toInt () ;
        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT SUM(mlzmdet_miktar) "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmDet_kod = %1 AND "
                         "mlzmDet_gc = 'Faturalı Giriş'").arg(id);
        q_qry.exec (s_qry);


        double grs=0,cks=0;

        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            tB_modl->setData(tB_modl->index(Mlzm_row, tB_modl->
                                            fieldIndex ("giris")), grs);
        }
        else
        {
            qDebug() << "qury not active"<<endl<<
                        q_qry.lastError ().text()<<endl;
        }
        s_qry = QString ("SELECT SUM(mlzmdet_miktar) "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmDet_kod = %1 AND "
                         "mlzmDet_gc = 'Çıkış'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {

            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            tB_modl->setData(tB_modl->
                             index(Mlzm_row, tB_modl->
                                   fieldIndex ("cikis")), cks);
        }
        else
        {
            qDebug() << "qury not active 2  " <<endl<<
                        q_qry.lastError ().text()<<endl;
        }

        tB_modl->setData(tB_modl->
                         index(Mlzm_row, tB_modl->
                               fieldIndex ("mevcut")), grs-cks);
        tB_modl->submitAll ();
        qDebug()<<"toplam mevcut    "<<grs-cks;
    }
    else
    {
        qDebug() << "index invalid"<<endl          ;
    }


}








hC_MLZM::~hC_MLZM()
{
    qDebug() << "   destructor";
}

void hC_MLZM::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";
}









