﻿#include "mlzm.h"

hC_MLZM::hC_MLZM() : hC_tBcreator ()
{
    qDebug() << "  cnstrct mlzm **********************************";
    //************************************************************
    //*****************  M A L Z E M E  **************************

    win_Label->text ()= "AMBAR MALZEME";
    *tb_name = "mlzm_dbtb" ;

    tb_flds = new hC_ArrD (13, 4);
    tb_flds->setValue ( 0, "mlzm_ID"      , "INTEGER", "MalzemeID", "0" ) ;
    tb_flds->setValue ( 1, "mlzm_barkod"  , "TEXT"   , "Barkod" );
    tb_flds->setValue ( 2, "mlzm_malzeme" , "TEXT"   , "Malzeme" );
    tb_flds->setValue ( 3, "mlzm_aciklama", "TEXT"   , "Açıklama");
    tb_flds->setValue ( 4, "mlzm_marka"   , "TEXT"   , "Marka"   );
    tb_flds->setValue ( 5, "mlzm_model"   , "TEXT"   , "Model"   );
    tb_flds->setValue ( 6, "mlzm_cins"    , "TEXT"   , "Cins"    );
    tb_flds->setValue ( 7, "mlzm_birim"   , "TEXT"   , "Birim"   );
    tb_flds->setValue ( 8, "mlzm_giris"   , "TEXT"   , "Giriş Toplamı");
    tb_flds->setValue ( 9, "mlzm_cikis"   , "TEXT"   , "Çıkış Toplamı");
    tb_flds->setValue (10, "mlzm_mevcut"  , "TEXT"   , "Ambar Mevcudu");
    tb_flds->setValue (11, "mlzm_makina"  , "TEXT"   , "Makina", "0");
    tb_flds->setValue (12, "mlzm_resim"   , "BLOB"   , "Resim" , "0" );

    *tb_ndex     = "malzeme";
//    tb_model     = new QSqlRelationalTableModel;
//    tb_mapper   = new QDataWidgetMapper;
//    win_Wdgt    = new QWidget;
  //  tb_view     = new hC_Tv (tb_model, tb_mapper, win_Wdgt);

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_barkod = new QLineEdit  ) ;
    tb_wdgts->append ( lE_malzeme = new QLineEdit  ) ;
    tb_wdgts->append ( lE_aciklama = new QLineEdit ) ;
    tb_wdgts->append ( lE_marka = new QLineEdit    ) ;
    tb_wdgts->append ( lE_model = new QLineEdit    ) ;
    tb_wdgts->append ( lE_cins = new QLineEdit     ) ;
    tb_wdgts->append ( cbx_birim = new QComboBox   ) ;
    tb_wdgts->append ( lE_giris = new QLineEdit    ) ;
    tb_wdgts->append ( lE_cikis  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_mevcut  = new QLineEdit  ) ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;


}


void hC_MLZM::setup()
{

    create ( tb_flds );
    model  ( tb_flds, tb_wdgts );
    view   ( tb_flds, tb_wdgts );
    map    ( tb_flds, tb_wdgts );
    wdgt  () ;
    ui    () ;
    kntrl () ;
}


void hC_MLZM::ui()
{
    qDebug() << "  ui";

    setWindowTitle (win_Label->text());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget (tb_view       , 0, 0, 1, 5);
    win_Grid->addWidget (win_Wdgt        , 0, 5, 1, 5);
}


void hC_MLZM::wdgt()
{
    qDebug () << "  wdgt";

    auto *lB_barkod = new QLabel(tr("&Barkod"));
    lB_barkod->setBuddy(lE_barkod);

    auto lB_brkd = new QLabel();
    lB_brkd->setFont (QFont ("code128",30));
    lB_brkd->setText (lE_barkod->text ());

    auto *lB_malzeme = new QLabel(tr("&Malzeme"));
    lB_malzeme->setBuddy(lE_malzeme);

    auto *lB_aciklama = new QLabel(tr("&Açıklama"));
    lB_aciklama->setBuddy(lE_aciklama);

    auto *lB_marka = new QLabel(tr("Ma&rka"));
    lB_marka->setBuddy(lE_marka);

    auto *lB_model = new QLabel(tr("Mo&del"));
    lB_model->setBuddy(lE_model);

    auto *lB_cins = new QLabel(tr("&Cins"));
    lB_cins->setBuddy(lE_cins);

    auto *lB_birim = new QLabel(tr("&Birim"));
    QStringList br = {"adet",
                      "takım",
                      "ton",
                      "kg",
                      "gr",
                      "torba"};
    cbx_birim->insertItems (0,  br );
    lB_birim->setBuddy(cbx_birim);

    auto *lB_g = new QLabel(tr("Toplam Giriş"));
    lE_giris->setAlignment (Qt::AlignRight);
/*    lE_giris->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0,
                                     2, lE_giris)) ;*/
    lB_g->setBuddy(lE_giris);

    auto *lB_c = new QLabel(tr("Toplam Çıkış"));
  /*  lE_cikis->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0,
 2, lE_cikis)) ;*/
    lB_c->setBuddy(lE_cikis);

    auto *lB_m = new QLabel(tr("Ambar Mevcudu"));
 /*   lE_mevcut->setValidator (
                new QDoubleValidator(-999.0,999'999'999.0,
                                     2, lE_mevcut)) ;*/
    lB_m->setBuddy(lE_mevcut);

    hC_Rs resim(win_Rsm);

    ///////////////////////////////////////
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_malzeme->setMinimumSize (200,25);

    int str = 0;
    wdgtGrid ->addWidget(lB_barkod  , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_barkod  ,   str, 1, 1, 5);
    wdgtGrid ->addWidget(lB_brkd    ,   str, 5, 1, 5);
    wdgtGrid ->addWidget(lB_malzeme , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_malzeme ,   str, 1, 1, 9);

    wdgtGrid ->addWidget(lB_marka   , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_marka   ,   str, 1, 1, 9);

    wdgtGrid ->addWidget(lB_aciklama, ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_aciklama,   str, 1, 1, 9);
    wdgtGrid ->addWidget(lB_model   , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_model   ,   str, 1, 1, 9);

    wdgtGrid ->addWidget (lB_cins   , ++str, 0, 1, 1);
    wdgtGrid ->addWidget (lE_cins   ,   str, 1, 1, 9);

    wdgtGrid ->addWidget (lB_birim  , ++str, 0, 1, 1);
    wdgtGrid ->addWidget (cbx_birim ,   str, 1, 1, 3);
    wdgtGrid ->addWidget (lB_g      , ++str, 0, 1, 1);
    wdgtGrid ->addWidget (lE_giris  ,   str, 1, 1, 3);
    wdgtGrid ->addWidget (lB_c      , ++str, 0, 1, 1);
    wdgtGrid ->addWidget (lE_cikis  ,   str, 1, 1, 3);
    wdgtGrid ->addWidget (lB_m      , ++str, 0, 1, 1);
    wdgtGrid ->addWidget (lE_mevcut ,   str, 1, 1, 3);
    wdgtGrid ->addWidget (win_Rsm, str-3, 4, 4, 6);

}


void hC_MLZM::kntrl()
{
    qDebug() << "  kntrl";

    tb_slctnMdl = tb_view->table->selectionModel();
    qDebug () <<"  "<< *tb_name << "Selected: " <<  tb_slctnMdl <<".";
    // /// yeni malzeme ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QString IEtableName{"mlzm_dbtb"};
        QSqlQuery q;
        QString qry, mesaj("");
        /// yeni barkod numarasını bul
        /// barkod nosu _dbtb de
        /// barkod alanındaki en büyük sayı
        qry = "SELECT max(mlzm_id) FROM " + IEtableName  ;
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
        tb_model->select();
        ////////////////////////////////////////////////
        hC_Nr (tb_view, mlzmno, 0);
        ////////////////////////////////////////////////
        tb_view->table->setFocus ();
        // mlzm  ekle


    });

    /// // malzeme resmi ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this] ()
    {
        hC_Rs resim (win_Rsm, tb_view, tb_model, tb_slctnMdl,
                     "resim","ekle");

    });

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this] ()
    {
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex mlzmIndex =   tb_view->table->currentIndex();
        if( mlzmIndex.row() >= 0 )
        {
            QSqlRecord rec = tb_model->record(mlzmIndex.row ());
            int Mlzm_no = rec.value ("mlzm_id").toInt();
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
                s_qry = QString("DELETE FROM mzgc__dbtb where mzgc_kod = %1").arg (Mlzm_no);
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
                s_qry = QString("DELETE FROM mzgc_dbtb where kod = %1").arg (Mlzm_no);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<< "1 adet Mlzm Kaydı Silindi";

                    tb_model->select ();

                    if (tb_model->rowCount () == 1)
                    {
                        tb_view->table->selectRow (0);
                        tb_view->table->setCurrentIndex (tb_model->index(0,1));
                    }
                    if (tb_model->rowCount () > 1)
                    {
                        if (mlzmIndex.row () == 0)
                        {
                            tb_view->table->selectRow (0);
                            tb_view->table->setCurrentIndex (tb_model->index(0,1));
                        }
                        else if (mlzmIndex.row () > 0)
                        {
                            tb_view->table->selectRow (mlzmIndex.row()-1);
                            tb_view->table->setCurrentIndex (tb_model->index(mlzmIndex.row ()-1,1));
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


    /// Mlzm da kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl, &QItemSelectionModel::currentColumnChanged,
              tb_mapper, &QDataWidgetMapper::setCurrentModelIndex);

    // malzemede row değiştiğnde 3 şeyi değiştirelim
    // 1 map indexi
    // 2 malzeme kodunu ve ismini yayalım
    // 3 resim
     qDebug() << " tb_slctnmdl connect 421 "<< tb_slctnMdl;
    connect( tb_slctnMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index)
    {


        // 1 map indexi değiştirelim
        tb_mapper->setCurrentModelIndex(Index);
        qDebug() << "  tb map index changed";

        // 2 malzeme kod - barkod - isim ve birim yayalım
        ////////////////////////////////////////////////////////////////
        auto kd = new QString;
        *kd = tb_view->table->model()->index( Index.row() ,
                                                tb_model->fieldIndex ("kod") ).data().toString();

        auto brkd = new QString;
        *brkd = tb_view->table->model()->index( Index.row() ,
                                                  tb_model->fieldIndex ("barkod") ).data().toString();

        auto mlzm = new QString;
        *mlzm = tb_view->table->model()->index( Index.row() ,
                                                  tb_model->fieldIndex ("malzeme") ).data().toString();

        auto brm = new QString;
        *brm =  tb_view->table->model()->index( Index.row() ,
                                                  tb_model->fieldIndex ("birim") ).data().toString();
        ////////////////////////////////////////////////////////////////
        emit hC_MLZM::sgnMalzeme( kd, brkd, mlzm, brm);
        ////////////////////////////////////////////////////////////////
        // 3 resimi değiştirelim
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                      "resim", "değiştir" ) ;


    });


    /// Mlzmdet miktar değiştiğinde Mlzm envanter hesabı
    //   connect (lE_d_miktar, &QLineEdit::editingFinished,
    //          this, &hC_MLZM::slt_Mlzm_hesap);

    //tableviewde miktar ve grs cks değştiğinde hsap yapılsın

     qDebug() << "  kntrl 4";
    connect(tb_slctnMdl, &QItemSelectionModel::currentRowChanged,
            this, &hC_MLZM::slt_Mlzm_hesap);

 qDebug() << "  kntrl son";
}


void hC_MLZM::slt_Mlzm_hesap(QModelIndex Index)
{
    if ( Index.row () >= 0 )
    {
        int Mlzm_row = Index.row ();
        int id = tb_model->
                data ( tb_model->
                       index(Mlzm_row,tb_model->
                             fieldIndex("kod"))).toInt () ;
        QSqlQuery q_qry;
        QString s_qry;
        s_qry = QString ("SELECT SUM(mzgc_miktar) "
                         "FROM mzgc__dbtb "
                         "WHERE mzgc_kod = %1 AND "
                         "mzgc_gc = 'Faturalı Giriş'").arg(id);
        q_qry.exec (s_qry);


        double grs=0,cks=0;

        if (q_qry.isActive ())
        {
            q_qry.next ();
            grs = q_qry.value(0).toDouble ();
            tb_model->setData(tb_model->index(Mlzm_row, tb_model->
                                            fieldIndex ("giris")), grs);
        }
        else
        {
            qDebug() << "qury not active"<<endl<<
                        q_qry.lastError ().text()<<endl;
        }
        s_qry = QString ("SELECT SUM(mzgc_miktar) "
                         "FROM mzgc__dbtb "
                         "WHERE mzgc_kod = %1 AND "
                         "mzgc_gc = 'Çıkış'").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {

            q_qry.next ();
            cks = q_qry.value(0).toDouble ();
            tb_model->setData(tb_model->
                             index(Mlzm_row, tb_model->
                                   fieldIndex ("cikis")), cks);
        }
        else
        {
            qDebug() << "qury not active 2  " <<endl<<
                        q_qry.lastError ().text()<<endl;
        }

        tb_model->setData(tb_model->
                         index(Mlzm_row, tb_model->
                               fieldIndex ("mevcut")), grs-cks);
        tb_model->submitAll ();
        qDebug()<<"toplam mevcut    "<<grs-cks;
    }
    else
    {
        qDebug() << "index invalid"<<endl          ;
    }


}



void hC_MLZM::showEvent(QShowEvent *)
{

    qDebug() << "   Show event - - - Mlzm dosyası açılıyor";
}

hC_MLZM::~hC_MLZM()
{
    qDebug() << "   destructor";
    delete tb_view     ;
    delete tb_model     ;
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
    delete cbx_grs_tipi;
    delete lE_barkod   ;
    delete lE_malzeme  ;
    delete lE_aciklama ;
    delete lE_marka    ;
    delete lE_model    ;
    delete lE_cins     ;
    delete cbx_birim   ;
    delete lE_giris    ;
    delete lE_cikis    ;
    delete lE_mevcut   ;

}
