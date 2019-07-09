#include "mlzm.h"

hC_MLZM::hC_MLZM(QWidget *parent) : QWidget(parent)
{
    //************************************************************
    //*****************  M A L Z E M E  **************************
    qDebug() << "Mlzm Cnstrctr   ";


    qDebug() << "  mlzm_setup";


    int* tB_fcnt = new int(13);

    // Create
    QVector< QVector < QString > >
            fields (*tB_fcnt, QVector < QString > (4));

    fields [0] = {"mlzm_kod"     ,"INTEGER", "MalzemeID", nullptr};
    fields [1] = {"mlzm_barkod"  ,"TEXT"   , "Barkod"   , "lE_barkod" };
    fields [2] = {"mlzm_malzeme" ,"TEXT"   , "Malzeme"  , "lE_malzeme" };
    fields [3] = {"mlzm_aciklama","TEXT"   , "Açıklama" , "lE_aciklama"  };
    fields [4] = {"mlzm_marka"   ,"TEXT"   , "Marka"    , "lE_marka" };
    fields [5] = {"mlzm_model"   ,"TEXT"   , "Model"    , "lE_model" };
    fields [6] = {"mlzm_cins"    ,"TEXT"   , "Cins"     , "lE_cins" };
    fields [7] = {"mlzm_birim"   ,"TEXT"   , "Birim"    , "cbx_birim" };
    fields [8] = {"mlzm_giris"   ,"TEXT"   , "Giriş Toplamı" , "lE_giris" };
    fields [9] = {"mlzm_cikis"   ,"TEXT"   , "Çıkış Toplamı" , "lE_cikis" };
    fields [10] = {"mlzm_mevcut"  ,"TEXT"   , "Ambar Mevcudu", "lE_mevcut" };
    fields [11] = {"mlzm_makina"  ,"TEXT"   , "Makina"   , nullptr };
    fields [12] = {"mlzm_resim"   ,"BLOB"   , "Resim"    , "winRsm" }     ;



    edits = new QVector<QWidget*> ;
    edits->append ( nullptr ) ;
    edits->append ( lE_barkod ) ;
    edits->append ( lE_malzeme ) ;
    edits->append ( lE_aciklama ) ;
    edits->append ( lE_marka ) ;
    edits->append ( lE_model ) ;
    edits->append ( lE_cins ) ;
    edits->append ( cbx_birim ) ;
    edits->append ( lE_giris ) ;
    edits->append ( lE_cikis ) ;
    edits->append ( lE_mevcut ) ;
    edits->append ( nullptr ) ;
    edits->append ( winRsm ) ;



    tB_fieldList = new QStringList ;
    tB_fieldList->append("Kod");
    tB_fieldList->append("Barkod");
    tB_fieldList->append("Malzeme");
    tB_fieldList->append("Açıklama");
    tB_fieldList->append("Marka");
    tB_fieldList->append("Model");
    tB_fieldList->append("Cins");
    tB_fieldList->append("Birim");
    tB_fieldList->append("Giriş");
    tB_fieldList->append("Çıkış");
    tB_fieldList->append("Mevcut");
    tB_fieldList->append("Makina");
    tB_fieldList->append("Resim");

    winLabel = new QLabel("AMBAR MALZEME");
    tB_name = new QString ("mlzm__dbtb") ;
    tB_ndex = new QString ("mlzm_malzeme");
    tB_modl = new QSqlRelationalTableModel;



    ////////////////////////////////////////////////////////
    /// Malzeme create
    ///

    QString ct, mesaj ="  OK - Malzeme";
    QSqlQuery q;

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( *tB_name ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *tB_name +
                " ( ";

        qDebug ()<< " dosya yokkkk " << tB_fieldList->length ();

        for (int i=0 ; i < tB_fieldList->length () ; i++)
        {
            if ( i == 0 )
            {
                ct = ct + tB_fieldList->at (i) + " "+
                        tB_fieldList-> at (i) +" PRIMARY KEY, ";
            }
            else if ( i > 0  &&
                      i < tB_fieldList->length () -1 )
            {
                ct = ct + tB_fieldList-> at (i) + " "+
                        tB_fieldList-> at (i) + ", ";
            }
            else if ( i == tB_fieldList->length () - 1 )
            {
                ct = ct + tB_fieldList-> at (i) + " "+
                        tB_fieldList->at (i) + " ) ";
            }

            qDebug ()<< " ct = " << i <<" - "<<tB_fieldList->at (i);
            qDebug ()<< "-------------------------- " ;
            qDebug ()<< " ct = " << ct;
        }



        if (!q.exec( ct ))
        {
            mesaj="<br>HATA - Malzeme Dosyası Oluşturulamadı"
                  "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else /// dosya oluşturuldu
        {
            mesaj= "OK - Malzeme Dosyası YENİ Oluşturuldu ";
            if (
                    q.exec("INSERT INTO " + *tB_name +
                           "( mlzm_barkod,mlzm_malzeme )"
                           " values( '1111','KOD 1 ve 1111 barkodlu malzeme' )"  ))
            {
                mesaj= mesaj+"<br>İLK kayıt Eklendi";
            }
            else
            {
                mesaj= mesaj+"<br>İLK Malzeme kaydı eklenemdi "
                             "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }

        }
    }

    else /// dosya var
    {
         qDebug ()<< " dosya varr mlzm " ;
    }
    qDebug() << mesaj;
    ////////////////////////////////////////////////////////////


}


void hC_MLZM::mlzm_setup()
{



    //mlzm_VTd   () ;

    hC_Rm hC_Rm (tB_name,
                 tB_modl,
                 tB_ndex ,
                 tB_fieldList) ;

    //    mlzm_model () ;
    mlzm_wdgt  () ;
    mlzm_map   () ;
    mlzm_ui    () ;
    mlzm_view  () ;
    mlzm_kntrl () ;
}


void hC_MLZM::mlzm_ui()
{
    qDebug() << "  Mlzm_ui";

    setWindowTitle (winLabel->text());
    MLZMtview = new hC_Tv (tB_modl, MLZMmapper, winWdgt);

    ////////////////////////////////////////////// layout
    auto *mlzmGrid = new QGridLayout(this);  // 100150
    mlzmGrid->addWidget (MLZMtview       , 0, 0, 1, 5);
    mlzmGrid->addWidget (winWdgt        , 0, 5, 1, 5);
}


void hC_MLZM::mlzm_wdgt()
{
    qDebug () << "  mlzm_wdgt";

    auto *lB_barkod = new QLabel(tr("&Barkod"));
    lE_barkod = new QLineEdit();
    lB_barkod->setBuddy(lE_barkod);

    auto lB_brkd = new QLabel();
    lB_brkd->setFont (QFont ("code128",30));
    lB_brkd->setText (lE_barkod->text ());

    auto *lB_malzeme = new QLabel(tr("&Malzeme"));
    lE_malzeme = new QLineEdit();
    lB_malzeme->setBuddy(lE_malzeme);

    auto *lB_aciklama = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_marka = new QLabel(tr("Ma&rka"));
    lE_marka = new QLineEdit();
    lB_marka->setBuddy(lE_marka);

    auto *lB_model = new QLabel(tr("Mo&del"));
    lE_model = new QLineEdit();
    lB_model->setBuddy(lE_model);

    auto *lB_cins = new QLabel(tr("&Cins"));
    lE_cins = new QLineEdit();
    lB_cins->setBuddy(lE_cins);

    auto *lB_birim = new QLabel(tr("&Birim"));
    cbx_birim = new QComboBox;

    QStringList br = {"adet",
                      "takım",
                      "ton",
                      "kg",
                      "gr",
                      "torba"};
    cbx_birim->insertItems (0,  br );
    lB_birim->setBuddy(cbx_birim);

    auto *lB_g = new QLabel(tr("Toplam Giriş"));
    lE_giris = new QLineEdit();
    lE_giris->setAlignment (Qt::AlignRight);
    lE_giris->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_giris)) ;
    lB_g->setBuddy(lE_giris);

    auto *lB_c = new QLabel(tr("Toplam Çıkış"));
    lE_cikis = new QLineEdit();
    lE_cikis->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_cikis)) ;
    lE_cikis->setAlignment (Qt::AlignRight);
    lB_c->setBuddy(lE_cikis);

    auto *lB_m = new QLabel(tr("Ambar Mevcudu"));
    lE_mevcut = new QLineEdit();
    lE_mevcut->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0, 2, lE_mevcut)) ;
    lE_mevcut->setAlignment (Qt::AlignRight);
    lB_m->setBuddy(lE_mevcut);

    winRsm = new QLabel;
    hC_Rs resim(winRsm);

    ///////////////////////////////////////
    winWdgt = new QWidget;
    winWdgt->setGeometry (0,0,800,300);
    auto mlzmGrid = new QGridLayout();
    winWdgt->setLayout(mlzmGrid);

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
    mlzmGrid ->addWidget (winRsm, str-3, 4, 4, 6);

}


void hC_MLZM::mlzm_view()
{
    qDebug() << "  mlzm_view";

    //////////////////////////////////////////////////////////
    MLZMtview->table->setModel(tB_modl);
    MLZMslctnMdl =   MLZMtview->table->selectionModel ();

    //////////////////////////////////////////////////////////
    /// kullanıcı bu alanları görmesin
    MLZMtview->table->setColumnHidden(tB_modl->fieldIndex("mlzm_kod"), true);
    //    MLZMtview->table->setColumnHidden(tB_modl->fieldIndex("mlzm_giris"), true);
    //    MLZMtview->table->setColumnHidden(tB_modl->fieldIndex("mlzm_cikis"), true);
    //    MLZMtview->table->setColumnHidden(tB_modl->fieldIndex("mlzm_mevcut"), true);
    MLZMtview->table->setColumnHidden(tB_modl->fieldIndex("mlzm_resim"), true);
    MLZMtview->table->setColumnHidden(tB_modl->fieldIndex("mlzm_makina"), true);
    //////////////////////////////////////////////////////////
    // with blue rect
    MLZMtview->table->setCurrentIndex(
                tB_modl->index(1, 1) );
    MLZMtview->table->setFocus();
}


void hC_MLZM::mlzm_map()
{
    qDebug() << "  mlzm_map";

    MLZMmapper = new QDataWidgetMapper(this);
    MLZMmapper->setModel(tB_modl);

    /*
for (int i=0 ;  i < fields->length () ; i++ )
{
   MLZMmapper->addMapping( edits->value(i), i);
}
*/
    MLZMmapper->addMapping( lE_barkod, tB_modl->fieldIndex( "mlzm_barkod"));
    MLZMmapper->addMapping(lE_malzeme, tB_modl->fieldIndex("mlzm_malzeme"));
    MLZMmapper->addMapping(lE_aciklama, tB_modl->fieldIndex("mlzm_aciklama"));
    MLZMmapper->addMapping(lE_marka, tB_modl->fieldIndex("mlzm_marka"));
    MLZMmapper->addMapping(lE_model, tB_modl->fieldIndex("mlzm_model"));
    MLZMmapper->addMapping(lE_cins, tB_modl->fieldIndex("mlzm_cins"));
    MLZMmapper->addMapping( cbx_birim, tB_modl->fieldIndex( "mlzm_birim" ));
    MLZMmapper->addMapping( lE_giris, tB_modl->fieldIndex("mlzm_giris"));
    MLZMmapper->addMapping( lE_cikis, tB_modl->fieldIndex("mlzm_cikis"));
    MLZMmapper->addMapping( lE_mevcut, tB_modl->fieldIndex("mlzm_mevcut"));
    //MLZMmapper->addMapping( cX_mkn, tB_modl->fieldIndex("makina"));


    hC_MLZM::MLZMmapper->toFirst() ;
}



void hC_MLZM::mlzm_kntrl()
{
    qDebug() << "  mlzm_kntrl";


    // /// yeni malzeme ekle
    connect(MLZMtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QString IEtableName{"mlzm__dbtb"};
        QSqlQuery q;
        QString qry, mesaj("");
        /// yeni barkod numarasını bul
        /// barkod nosu mlzm__dbtb de
        /// mlzm_barkod alanındaki en büyük sayı
        qry = "SELECT max(mlzm_kod) FROM " + IEtableName  ;
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
                " ( mlzm_barkod) values( ' ' )" ;

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
        hC_Nr (MLZMtview, mlzmno, 0);
        ////////////////////////////////////////////////
        MLZMtview->table->setFocus ();
        // mlzm  ekle


    });

    /// // malzeme resmi ekle
    connect(MLZMtview->pB_eklersm, &QPushButton::clicked,
            [this] ()
    {
        hC_Rs resim (winRsm, MLZMtview, tB_modl, MLZMslctnMdl,
                     "mlzm_resim","ekle");

    });

    connect(MLZMtview->pB_sil, &QPushButton::clicked,
            [this] ()
    {
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex mlzmIndex =   MLZMtview->table->currentIndex();
        if( mlzmIndex.row() >= 0 )
        {
            QSqlRecord rec = tB_modl->record(mlzmIndex.row ());
            int Mlzm_no = rec.value ("mlzm_kod").toInt();
            QString val = rec.value("mlzm_barkod").toString();
            QString val2= rec.value("mlzm_malzeme").toString() ;


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

            int Mlzmdet_count = 10000000; // = MLZMDETmodel->rowCount () ;
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
                s_qry = QString("DELETE FROM mlzmDet__dbtb where mlzmDet_mlzm_kod = %1").arg (Mlzm_no);
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
                s_qry = QString("DELETE FROM mlzm__dbtb where mlzm_kod = %1").arg (Mlzm_no);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<< "1 adet Mlzm Kaydı Silindi";

                    tB_modl->select ();

                    if (tB_modl->rowCount () == 1)
                    {
                        MLZMtview->table->selectRow (0);
                        MLZMtview->table->setCurrentIndex (tB_modl->index(0,1));
                    }
                    if (tB_modl->rowCount () > 1)
                    {
                        if (mlzmIndex.row () == 0)
                        {
                            MLZMtview->table->selectRow (0);
                            MLZMtview->table->setCurrentIndex (tB_modl->index(0,1));
                        }
                        else if (mlzmIndex.row () > 0)
                        {
                            MLZMtview->table->selectRow (mlzmIndex.row()-1);
                            MLZMtview->table->setCurrentIndex (tB_modl->index(mlzmIndex.row ()-1,1));
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
    connect(MLZMtview->pB_ilk, &QPushButton::clicked ,
            [this] ()
    {
     MLZMtview->hC_TvPb ("ilk", tB_modl, MLZMmapper);
    });


    connect(MLZMtview->pB_ncki, &QPushButton::clicked,
            [this] ()
    {
        MLZMtview->hC_TvPb ("ncki", tB_modl, MLZMmapper);
    });

    //             &hC_MLZM::slt_Mlzm_toPrevious )) ;
    connect(MLZMtview->pB_snrki, &QPushButton::clicked,
            [this] ()
    {
        MLZMtview->hC_TvPb ("snrki", tB_modl, MLZMmapper);
    });

    //             &hC_MLZM::slt_Mlzm_toNext )) ;
    connect(MLZMtview->pB_son, &QPushButton::clicked,
            [this] ()
    {
        MLZMtview->hC_TvPb ("son", tB_modl, MLZMmapper);
    });

    /// mlzm nav tuslari kontrol
    connect(MLZMmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        MLZMtview->hC_TvPb ("yenile", tB_modl, MLZMmapper);
    });
*/
    /// Mlzm da kolon değiştiğinde indexte değişsin
    connect(  MLZMslctnMdl, &QItemSelectionModel::currentColumnChanged,
              MLZMmapper, &QDataWidgetMapper::setCurrentModelIndex);

    /// Mlzm da row değiştiğinde indexte değişsin
    connect(  MLZMslctnMdl , &QItemSelectionModel::currentRowChanged,
              MLZMmapper, &QDataWidgetMapper::setCurrentModelIndex);

    // malzemede row değiştiğnde 3 şeyi değiştirelim
    // 1 map indexi
    // 2 malzeme kodunu ve ismini yayalım
    // 3 resim
    connect( MLZMslctnMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index)
    {


        // 1 map indexi değiştirelim
        MLZMmapper->setCurrentModelIndex(Index);

        // 2 malzeme kod - barkod - isim ve birim yayalım
        ////////////////////////////////////////////////////////////////
        auto kd = new QString;
        *kd = MLZMtview->table->model()->index( Index.row() ,
                                                tB_modl->fieldIndex ("mlzm_kod") ).data().toString();

        auto brkd = new QString;
        *brkd = MLZMtview->table->model()->index( Index.row() ,
                                                  tB_modl->fieldIndex ("mlzm_barkod") ).data().toString();

        auto mlzm = new QString;
        *mlzm = MLZMtview->table->model()->index( Index.row() ,
                                                  tB_modl->fieldIndex ("mlzm_malzeme") ).data().toString();

        auto brm = new QString;
        *brm =  MLZMtview->table->model()->index( Index.row() ,
                                                  tB_modl->fieldIndex ("mlzm_birim") ).data().toString();
        ////////////////////////////////////////////////////////////////
        emit hC_MLZM::sgnMalzeme( kd, brkd, mlzm, brm);
        ////////////////////////////////////////////////////////////////
        // 3 resimi değiştirelim
        hC_Rs resim ( winRsm, MLZMtview, tB_modl, MLZMslctnMdl,
                      "mlzm_resim", "değiştir" ) ;


    });


    /// Mlzmdet miktar değiştiğinde Mlzm envanter hesabı
    //   connect (lE_d_miktar, &QLineEdit::editingFinished,
    //          this, &hC_MLZM::slt_Mlzm_hesap);

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın

    connect(MLZMslctnMdl, &QItemSelectionModel::currentRowChanged,
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
                             fieldIndex("mlzm_kod"))).toInt () ;
        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT SUM(mlzmdet_miktar) "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmDet_mlzm_kod = %1 AND "
                         "mlzmDet_gc = 'Faturalı Giriş'").arg(id);
        q_qry.exec (s_qry);


        double grs=0,cks=0;

        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            tB_modl->setData(tB_modl->index(Mlzm_row, tB_modl->
                                            fieldIndex ("mlzm_giris")), grs);
        }
        else
        {
            qDebug() << "qury not active"<<endl<<
                        q_qry.lastError ().text()<<endl;
        }
        s_qry = QString ("SELECT SUM(mlzmdet_miktar) "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmDet_mlzm_kod = %1 AND "
                         "mlzmDet_gc = 'Çıkış'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {

            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            tB_modl->setData(tB_modl->
                             index(Mlzm_row, tB_modl->
                                   fieldIndex ("mlzm_cikis")), cks);
        }
        else
        {
            qDebug() << "qury not active 2  " <<endl<<
                        q_qry.lastError ().text()<<endl;
        }

        tB_modl->setData(tB_modl->
                         index(Mlzm_row, tB_modl->
                               fieldIndex ("mlzm_mevcut")), grs-cks);
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










///
/// \brief DBase::VTd_Mlzm
/// \return
///
QString hC_MLZM::mlzm_VTd ()
{


    /// Malzeme create
    ///

    QString ct, mesaj ="  OK - Malzeme";
    QSqlQuery q;

    qDebug() << " tableee  name " << *tB_name;
    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( "mlzm_dbtb" ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + *tB_name +
                "("
                "mlzm_kod integer primary key, "
                "mlzm_barkod	TEXT, "
                "mlzm_malzeme  TEXT,"
                "mlzm_aciklama TEXT,"
                "mlzm_marka	TEXT, "
                "mlzm_model	TEXT, "
                "mlzm_cins	    TEXT,"
                "mlzm_birim	TEXT,"
                "mlzm_giris	TEXT, "
                "mlzm_cikis	TEXT, "
                "mlzm_mevcut   TEXT,"
                "mlzm_makina   TEXT,"
                "mlzm_resim	BLOB) "    ;

        if (!q.exec( ct ))
        {
            mesaj="<br>HATA - Malzeme Dosyası Oluşturulamadı"
                  "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else /// dosya oluşturuldu
        {
            mesaj= "OK - Malzeme Dosyası YENİ Oluşturuldu ";
            if (
                    q.exec("INSERT INTO " + *tB_name +
                           "( mlzm_barkod,mlzm_malzeme )"
                           " values( '1111','KOD 1 ve 1111 barkodlu malzeme' )"  ))
            {
                mesaj= mesaj+"<br>İLK kayıt Eklendi";
            }
            else
            {
                mesaj= mesaj+"<br>İLK Malzeme kaydı eklenemdi "
                             "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }

        }
    }
    else /// dosya var
    {
        //        mdlMlzm = new QSqlRelationalTableModel;
        //      mdlMlzm = modelMalzeme();
    }
    qDebug() << mesaj;
    return mesaj;

}


