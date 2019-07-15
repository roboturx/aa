#include "ftr.h"
#include "mlzm.h"
#include "frm.h"


hC_FTR::hC_FTR(QWidget *parent) :  QWidget(parent)
{
    //************************************************************
    //*****************  F A T U R A  ****************************
    qDebug() << "Ftr Cnstrctr";
}



void hC_FTR::setup()
{
    qDebug() << "  ftr_setup ";

    wdgt  () ;

    ui    () ;

    kntrl () ;
    /*FTRDETmodel = new QSqlRelationalTableModel;
    ftrdet_model ( FTRDETmodel );

    setup_viewFtrDet () ;
    setup_mapFtrDet ()  ;
    setup_kntrlFtrDet ();
*/


}


void hC_FTR::ui()
{
    qDebug() << "  ftr_ui";

    ////////////////////////////////////////// window
    win_Label = new QLabel("FATURA BAŞLIK BİLGİ GİRİŞ");
    hC_FTR::setWindowTitle(win_Label->text ());
    //hC_FTR::setMinimumSize (800,400);
    //hC_FTR::showMaximized();

    ////////////////////////////////////////// widgets

    //wd_FTRdet();

    //////////////////////////////////// depo tableview
  //  tb_view = new hC_Tv ( ) ;
    //tb_view->setMinimumSize (160,60);

    /*/////////////////////////////////// depodet
    ///  aslında malzemedet tableview
    FTRDETtview = new hC_Tv;
    FTRDETtview->setMinimumSize (160,60);

    ////////////////////////////////////////////// layout

    auto  frame1 = new QFrame;
    frame1->setFrameStyle(QFrame::Box | QFrame::Raised);
    */
    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget (tb_view  , 0, 0, 1, 1);
    winGrid->addWidget (win_Wdgt   , 0, 1, 1, 1);

/*
    auto frame2 = new QFrame;
    auto *grid2 = new QGridLayout;
    frame2->setLayout (grid2);
    grid2->addWidget (FTRDETtview    , 1, 0 );
    grid2->addWidget (wdgt_mapFTR_dty, 1, 1 );

    ////////////////////////////////////////////// layout
    auto *wdgtGrid = new QGridLayout(this);
    wdgtGrid->addWidget (frame1 , 0, 0, 1, 1);
    wdgtGrid->addWidget (frame2 , 1, 0, 1, 1);
*/

}

void hC_FTR::wdgt()
{
    qDebug() << "  ftr_wdgt";

    auto *lB_faturano = new QLabel(tr("Fatura &No"));
    lE_faturano = new QLineEdit();
    lE_faturano->setReadOnly (true);
    //lE_faturano->setPlaceholderText ("Fatura No ");
    lB_faturano->setBuddy(lE_faturano);

    auto *lB_firma = new QLabel(tr("Firma Ünvanı "));
    lE_firma = new hC_Le ;
    lE_firma->lineEdit->setReadOnly(true);



    // firma ismini fatyraya ekle
    connect(lE_firma->pushButton , &QPushButton::clicked,
            [this]()
    {
        // firma seçebilmek için firma penceresi
        auto diafrm = new QDialog;
        diafrm->setModal (true);
        auto layout_diafr = new QGridLayout;
        diafrm->setLayout (layout_diafr);
        // diafr->setWindowTitle ("Fatura Bilgilerine Firma Unvanı Ekle ");
        diafrm->setGeometry (100,220,800,500);

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


        // firma class ımızı getirelim
        auto firma = new hC_FRM;
        firma->setup ();
        layout_diafr->addWidget (firma ,0 ,0 ,1, 1);
        //diafrm->show();


        /////////////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------
        // firma tableviewinde gezinirken firma adımız
        // signal ediliyor onu yakalayalım
        // seçim yapılan lineedit e aktaralım
        // ----------------------------------------------------


        connect (firma, &hC_FRM::sgnfirma,
                 [ this ] (QString secfirma )
        {
            this->lE_firma->lineEdit->setText (secfirma);
            this->lE_firma->lineEdit->setFocus();
        });
        diafrm->exec ();




    });

    auto *lB_tarih = new QLabel(tr("Fatura &Tarihi"));
    lE_tarih = new QLineEdit();
    lB_tarih->setBuddy(lE_tarih);

    auto *lB_ack = new QLabel(tr("&Açıklama"));
    lE_aciklama = new QLineEdit();
    lB_ack->setBuddy(lE_aciklama);

    auto *lB_ftrToplam = new QLabel(tr("Fatura Toplamı"));
    lE_ftrToplam = new QLineEdit();
    lB_ftrToplam->setBuddy(lE_ftrToplam);

    auto *lB_ftrKdv = new QLabel(tr("KDV"));
    lE_ftrKdv = new QLineEdit();
    lB_ftrKdv->setBuddy(lE_ftrKdv);

    auto *lB_ftrGenelToplam = new QLabel(tr("Genel Toplam"));
    lE_ftrGenelToplam = new QLineEdit();
    lB_ftrGenelToplam->setBuddy(lE_ftrGenelToplam);

    win_Rsm = new QLabel;
    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_faturano->setMinimumSize (200,25);

    int str{};

    wdgtGrid ->addWidget(lB_faturano, ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_faturano,   str, 1, 1, 4);
    wdgtGrid ->addWidget(lB_firma   , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_firma   ,   str, 1, 1, 4);
    wdgtGrid ->addWidget(lB_ack     , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_aciklama,   str, 1, 1, 4);
    wdgtGrid ->addWidget(lB_tarih   , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_tarih   ,   str, 1, 1, 4);
    wdgtGrid ->addWidget(lB_ftrToplam     , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_ftrToplam     ,   str, 1, 1, 2);
    wdgtGrid ->addWidget(lB_ftrKdv     , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_ftrKdv     ,   str, 1, 1, 2);
    wdgtGrid ->addWidget(lB_ftrGenelToplam     , ++str, 0, 1, 1);
    wdgtGrid ->addWidget(lE_ftrGenelToplam     ,   str, 1, 1, 2);
    wdgtGrid ->addWidget(win_Rsm  , str-2, 3, 3, 3);

}

/*
void hC_FTR::ftr_view()
{
    qDebug() << "  ftr_view";

    //////////////////////////////////////////////////////////
    tb_view->table->setModel ( tb_model );
    tb_slctnMdl = tb_view->table->selectionModel ();

    //////////////////////////////////////////////////////////
    //// kullanıcı bu alanları görmesin
    tb_view->table->setColumnHidden(tb_model->fieldIndex("ftr_kod"), true);
    tb_view->table->setColumnHidden(tb_model->fieldIndex("ftr_resim"), true);

    //////////////////////////////////////////////////////////
    // with blue rect
    tb_view->table->setCurrentIndex(
                tb_model->index(1, 1) );
    tb_view->table->setFocus();

}

void hC_FTR::ftr_map()
{
    qDebug() << "  ftr_map";

    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    tb_mapper->addMapping(lE_faturano , tb_model->fieldIndex("ftr_no"));
    tb_mapper->addMapping(lE_firma->lineEdit, tb_model->fieldIndex("ftr_firma"));
    tb_mapper->addMapping(lE_tarih, tb_model->fieldIndex("ftr_tarih"));
    tb_mapper->addMapping(lE_aciklama, tb_model->fieldIndex("ftr_aciklama"));
    /// fatura ilk kayıda
    ///

    hC_FTR::tb_mapper->toFirst ();
}
*/
void hC_FTR::kntrl()
{
    ///// tableview kontrol connectleri
    ///
    ///
    qDebug() << "  ftr_kntrl";

    // //////////////////////// yeni fatura ekle
    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this ]()
    {
        auto *dia_fno =new QDialog(this);
        dia_fno->setModal (true);
        dia_fno->setWindowTitle ("Fatura No Giriniz");
        auto *ly_diafno = new QHBoxLayout(dia_fno) ;

        auto *wdkod = new QWidget;
        ly_diafno->addWidget (wdkod);

        auto *wd_ly = new QHBoxLayout;
        wdkod->setLayout (wd_ly);

        auto *lE_fno = new QLineEdit{};
        //lE_fno->setPlaceholderText ("Fatura No Giriniz...");


        auto *pB_vz = new QPushButton("Vazgeç");
        connect(pB_vz, &QPushButton::clicked,
                [dia_fno] ()
        {

            dia_fno->close() ;
        });


        auto *pB_ok = new QPushButton("Kaydet");
        pB_ok->setDefault (true);



        auto *pb_ly = new QHBoxLayout;
        pb_ly->addWidget (pB_vz);
        pb_ly->addWidget (pB_ok);

        wd_ly->addWidget (lE_fno);
        wd_ly->addLayout (pb_ly);


        // fatura no önemli
        // boş geçmek olmaz

        // ///////////////// yeni fatura no ekle
        connect(pB_ok, &QPushButton::clicked ,
                [this,lE_fno, dia_fno ]()
        {

            //  qDebug()<<"fatura no boş geçilemez";
            if (lE_fno->text () == "")
            {
                lE_fno->setPlaceholderText ("fatura no boş geçilemez");
                return;
            }

            // kayıt oluşturalım

            QString ftrNo = lE_fno->text ();

            QString IEtableName{"ftr__dbtb"};
            QSqlQuery q;
            QString qry, mesaj("");

            /// yeni barkod numarasını bul
            /// barkod nosu mlzm__dbtb de
            /// mlzm_barkod alanındaki en büyük sayı
            qry = "SELECT max(ftr_kod) FROM " + IEtableName  ;
            int ftrkod{};
            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "Fatura Kod bulunamadı \n"+
                        "------------------------------------\n"+
                        q.lastError().text ()+
                        "------------------------------------\n";
                return;
            }
            else
            {
                q.next();
                ftrkod = q.value(0).toInt ();
                mesaj = mesaj + "MAX VAL =" +
                        QString::number(ftrkod) ;
            }

            ftrkod = ftrkod + 1  ; /// ftr_id

            // yeni kaydı ekle

            QString date(QDate::currentDate().
                         toString ( "dd-MM-yyyy" ));

            qry = "INSERT INTO " + IEtableName +
                    " ( ftr_no,ftr_tarih) "
                    " values ( '"+ftrNo+
                    "' , '"+date+
                    "' )" ;

            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "Fatura kaydı Eklenemedi xxxx"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "Fatura kaydı eklendi.";

                lE_firma ->lineEdit-> setText ("");
                lE_aciklama ->setText ("");
           }
            qDebug()<<mesaj;
            tb_model->select();
            ////////////////////////////////////////////////
            hC_Nr (tb_view, ftrkod, 0);
            ////////////////////////////////////////////////
            tb_view->table->setFocus ();
            /// ftr  ekle
            /// pb_ok sonu
            ///////////////////////////////////////
            dia_fno->close ();
        });

        dia_fno->exec ();
    });

    // ///////////////  resim ekle
    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {

        hC_Rs resim (win_Rsm, tb_view, tb_model, tb_slctnMdl,
                     "ftr_resim", "ekle");
    });

    // row değiştiğnde resmide değiştirelim
    // -- 003   row değiştiğinde resmide değiştirelim
    connect( tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
             [this ]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                      "ftr_resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle



    // fattura sil
    // pB 005 sil
    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "  slt_ftr_pB_SIL_clicked";
        //QSqlQuery q_qry;
        //QString s_qry;
        QModelIndex ftrindex = tb_view->table->currentIndex();
        if( ftrindex.row() >= 0 )
        {
            QSqlRecord ftrrec = tb_model->record(ftrindex.row ());

            int fatkod = ftrrec.value ("ftr_kod").toInt();
            QString fatno = ftrrec.value("ftr_no").toString();

            /// depo detay kayıtlarını soralım - silelim
            QSqlQuery q_qry;
            QString s_qry;
            /// silinecek kayıt sayısı   mlzmdet__dbtb
            s_qry = QString("SELECT count() FROM mlzmdet__dbtb"
                            "where mlzmdet_gcno = %1 and "
                            "mlzmdet_gc = 'Faturalı Giriş'").arg (fatno);
            q_qry.exec(s_qry);
            int xx = 0 ;

            if ( q_qry.isActive ())
            {
                xx = s_qry.size () ;
                qDebug()<< xx <<" adet kayıt silinecek ";
            }


            QString mess="\n";
            mess += fatno + " nolu fatura"
                            "\n  silinsin mi ?\n"+
                    "İşlemi onaylarsanız bu fatura kaydına ait\n " ;

          //  int mlzdet_count = FTRDETmodel->rowCount () ;
         /*   if ( mlzdet_count > 0 )
            {
                mess +=QString::number (mlzdet_count) +
                        " adet Ambar GİRİŞ kaydı da SİLİNECEK";
            }
          mess +="\n\nİŞLEMİ ONAYLIYORMUSUNUZ ?";
*/

            /// model makina kaydı var
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox
                    ::question(this,
                               "KAYIT SİL", mess,
                               QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                /// ambara ait mlzm_det giriş kayıtlarını sil
                s_qry = QString("DELETE FROM mlzmdet__dbtb "
                                "where mlzmdet_gcno = %1").arg (fatno);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<<" - "<<
                              " - adet Faturalı Giriş Kaydı Silindi";
                }
                else
                {
                    qDebug()<< "HATA - Faturalı Giriş Kayıtları Silinemedi"
                            << q_qry.lastError() ;
                }



                /// depo kayıtlarını silelim
                s_qry = QString("DELETE FROM ftr__dbtb "
                                "where ftr_kod = %1").arg (fatkod);
                q_qry.exec(s_qry);
                if (q_qry.isActive ())
                {
                    qDebug()<< "1 adet Fatura Kaydı Silindi";
                    tb_view->table->setFocus ();
                    tb_model->select ();



                    if (tb_model->rowCount () == 1)
                    {
                        tb_view->table->selectRow (0);
                        tb_view->table->setCurrentIndex (tb_model->index(0,0));
                    }
                    if (tb_model->rowCount () > 1)
                    {
                        if (ftrindex.row () == 0)
                        {
                            tb_view->table->selectRow (0);
                            tb_view->table->setCurrentIndex (tb_model->index(0,0));
                        }
                        else if (ftrindex.row () > 0)
                        {
                            tb_view->table->selectRow (ftrindex.row()-1);
                            tb_view->table->setCurrentIndex (tb_model->index(ftrindex.row ()-1,0));
                        }
                    }
                }
                else
                {
                    qDebug()<< "HATA - Fatura Kaydı Silinemedi"
                            << q_qry.lastError() ;
                }
            }
        }
    });

    // pB 006 ilk
 /*   connect(tb_view->pB_ilk, &QPushButton::clicked ,
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
    {
        tb_view->hC_TvPb ("son", tb_model, tb_mapper);
    });



    /// depo map nav tuslari kontrol
    // pB 010 nav tuslari kontrol
    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this]( )
    {
        tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);
    });
*/






    /// row değiştiğinde
    // --- 011
    connect (tb_slctnMdl, &QItemSelectionModel::currentRowChanged,
             [this] (QModelIndex Index )
    {

        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex (Index);
    });

    /// depo da kolon değiştiğinde mapper index te değişsin
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl, &QItemSelectionModel::currentColumnChanged,
              tb_mapper, &QDataWidgetMapper::setCurrentModelIndex);
}

///************************************************************
///****************  F A T U R A   S  L  O  T  S  ************





void hC_FTR::slt_ftr_hesap()
{
    qDebug() << "ftr_hesapp";

    QModelIndex ftr_indx = tb_view->table->currentIndex ();
    if ( ftr_indx.row () >= 0 )
    {
        int fatura_row = ftr_indx.row ();
        int id = tb_model->
                data ( tb_model->
                       index(fatura_row,tb_model->
                             fieldIndex("ftr_no"))).toInt () ;

        QSqlQuery q_qry;
        QString s_qry;
        // fstura toplamı
        s_qry = QString ("SELECT SUM"
                         "("
                         "(mlzmdet_fiyat) * mlzmdet_miktar"
                         ") "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmdet_gcno= %1").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            double tpl =  q_qry.value(0).toDouble() ;
            lE_ftrToplam->setAlignment(Qt::AlignRight );
            lE_ftrToplam->setText ( QString::number(qRound( tpl *100) / 100.0, 'f', 2) ) ;
        }
        else
        {
            qDebug() << " query inactive 1"<<endl<< q_qry.lastError ().text ();
        }
        // kdv
        s_qry = QString ("SELECT SUM"
                         "("
                         "((mlzmdet_fiyat*mlzmdet_kdv/100)) * mlzmdet_miktar"
                         ") "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmdet_gcno= %1").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            double kdv = q_qry.value(0).toDouble ();

            lE_ftrKdv ->setAlignment(Qt::AlignRight );
            lE_ftrKdv->setText ( QString::number(qRound( kdv *100) / 100.0, 'f', 2) ) ;
        }

        else
        {
            qDebug() << " query inactive 2"<<endl<< q_qry.lastError ().text ();
        }
        // Genel Toplam
        s_qry = QString ("SELECT SUM"
                         "("
                         "(mlzmdet_fiyat + (mlzmdet_fiyat*mlzmdet_kdv/100)) * mlzmdet_miktar"
                         ") "
                         "FROM mlzmdet__dbtb "
                         "WHERE mlzmdet_gcno= %1").arg(id);
        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            q_qry.next ();
            double GTop = q_qry.value(0).toDouble( );

            lE_ftrGenelToplam->setAlignment(Qt::AlignRight );
            lE_ftrGenelToplam->setText ( QString::number(qRound( GTop *100) / 100.0, 'f', 2) ) ;
        }

        else
        {
            qDebug() << " query inactive 3 "<<endl<< q_qry.lastError ().text ();
        }
    }
}  ///**************************************** fatura hesap


/*
 F A T U R A    D  E  T  A  Y  ************
///
///                  malzeme detay olarak işlem yapılıyor
///

void hC_FTR::wd_FTRdet()
{
    qDebug() << "  wd_FTRdet";
    lB_FTRdet = new QLabel("Malzeme Ftr Giriş - Çıkış İşlemleri");

    //  QLabel *lB_d_tarih = new QLabel(tr("&Tarih"));
    // lE_d_tarih = new QLineEdit();
    // lB_d_tarih->setBuddy(lE_d_tarih);

    QLabel *lB_mlzdetbarkod = new QLabel(tr("Barkod"));
    lE_mlzdetbarkod = new QLineEdit();
    lB_mlzdetbarkod->setBuddy(lE_mlzdetbarkod);

    /// malzeme adı değiştirlemez
    /// sadece yeni kayıt ile eklenir
    /// mlzm kod birim ve barkod isme bağlı
    QLabel *lB_mlzdetmlzm = new QLabel(tr("Malzeme Adı"));
    lE_mlzm = new QLineEdit;
    lE_mlzm->setReadOnly (true);


    QLabel *lB_mlzdettarih = new QLabel(tr("Tarih"));
    lE_mlzdettarih = new QLineEdit();
    lB_mlzdettarih->setBuddy(lE_mlzdettarih);

    QLabel *lB_mlzdetgc = new QLabel(tr("İşlem"));
    lE_mlzdetgc = new QLineEdit;
    lB_mlzdetgc->setBuddy(lE_mlzdetgc);

    QLabel *lB_mlzdetgcno = new QLabel(tr("Belge No"));
    lE_mlzdetgcno = new QLineEdit;
    lB_mlzdetgcno->setBuddy(lE_mlzdetgcno);


    QLabel *lB_mlzdetmiktar = new QLabel(tr("Miktar"));
    lE_mlzdetmiktar = new QLineEdit();
    lB_mlzdetmiktar->setBuddy(lE_mlzdetmiktar);


    QLabel *lB_mlzdetbirim = new QLabel(tr("Birim"));
    lE_mlzdetbirim = new QLineEdit();
    lB_mlzdetbirim->setBuddy(lE_mlzdetbirim);


    QLabel *lB_mlzdetfiyat = new QLabel(tr("Birim Fiyat"));
    lE_mlzdetfiyat = new QLineEdit();
    lB_mlzdetfiyat->setBuddy(lE_mlzdetfiyat);


    QLabel *lB_mlzdetkdv = new QLabel(tr("KDV %"));
    lE_mlzdetkdv = new QLineEdit();
    lB_mlzdetkdv->setBuddy(lE_mlzdetkdv);


    QLabel *lB_mlzdetaciklama = new QLabel(tr("Açıklama"));
    lE_mlzdetaciklama = new QLineEdit();
    lB_mlzdetaciklama->setBuddy(lE_mlzdetaciklama);

    auto *lYG_d_map = new QGridLayout();
    int str{};
    lYG_d_map->addWidget (new QLabel("<b>Fatura Detay Bilgileri</b>"),str,0);
    lYG_d_map->addWidget(lB_mlzdetbarkod  , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetbarkod  ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetmlzm    , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzm          ,   str, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetgc      , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetgc      ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetmiktar  , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetmiktar  ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetbirim   , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetbirim   ,   str, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetfiyat   , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetfiyat   ,   str, 1, 1, 1);
    lYG_d_map->addWidget(lB_mlzdetkdv     , ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetkdv     ,   str, 1, 1, 1);

    lYG_d_map->addWidget(lB_mlzdetaciklama, ++str, 0, 1, 1);
    lYG_d_map->addWidget(lE_mlzdetaciklama,   str, 1, 1, 1);

    wdgt_mapFTR_dty = new QWidget;
    wdgt_mapFTR_dty->setLayout(lYG_d_map);
}



void hC_FTR::setup_viewFtrDet()
{
    qDebug() << "  setup_viewFtrDet";

    FTRDETtview->table->setModel(FTRDETmodel);
    FTRDETtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    FTRDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FTRDETslctnMdl = FTRDETtview->table->selectionModel ();


    // Hide the column id Records
    //// kullanıcı bu alanları görmesin
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_kod"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_mlzm_kod"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_tarih"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_gc"), true);
    FTRDETtview->table->setColumnHidden(FTRDETmodel->fieldIndex("mlzmdet_gcno"), true);




    FTRDETtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

    FTRDETtview->table->horizontalHeader()->setStretchLastSection(true);
    FTRDETtview->table->horizontalHeader()->resizeContentsPrecision();
    FTRDETtview->table->resizeRowsToContents ();
    FTRDETtview->table->resizeColumnsToContents();

    tb_view->table->setCurrentIndex(
                tb_model->index(0,1)
                );
    tb_view->table->setFocus();


}


void hC_FTR::setup_mapFtrDet()
{
    qDebug() << "  setup_mapFtrDet";
    FTRDETmapper = new QDataWidgetMapper(this);
    FTRDETmapper->setModel(FTRDETmodel);

    //FTRDETmapper->addMapping(lE_d_faturano , FTRDETmodel->fieldIndex("faturano"));
    //FTRDETmapper->addMapping(lE_d_firma, FTRDETmodel->fieldIndex("firma"));
    FTRDETmapper->addMapping(lE_mlzdetbarkod, FTRDETmodel->fieldIndex("mlzmdet_barkod"));
    FTRDETmapper->addMapping(lE_mlzm, FTRDETmodel->fieldIndex("mlzmdet_malzeme"));
    FTRDETmapper->addMapping(lE_mlzdetmiktar, FTRDETmodel->fieldIndex("mlzmdet_miktar"));
    FTRDETmapper->addMapping(lE_mlzdetbirim, FTRDETmodel->fieldIndex("mlzmdet_birim"));
    FTRDETmapper->addMapping(lE_mlzdetfiyat, FTRDETmodel->fieldIndex("mlzmdet_fiyat"));
    FTRDETmapper->addMapping(lE_mlzdetkdv, FTRDETmodel->fieldIndex("mlzmdet_kdv"));
    FTRDETmapper->addMapping(lE_mlzdetaciklama, FTRDETmodel->fieldIndex("mlzmdet_aciklama"));


    /// depodetay varsa ilk kayda
    hC_FTR::FTRDETmapper->toFirst ();

}

void hC_FTR::setup_kntrlFtrDet()
{
    /////////////////
    ///
    /// CONNECT


    /// fatura detaya yeni bir kayıt ekleyelim
    /// bunu yaparken
    /// 1- faturadan fatura no, firma ve detay
    /// 2- Malzemeden fatura detaya eklenecek
    ///    mlz kod, barkod, isim ve birimi ekleyelim
    /// 3- diğer alanları mikttar fiyat vb
    ///    kullanıcıdan isteyelim

    // pB 001 yeni ekle
    connect(FTRDETtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        qDebug() << "  slt_mlz_pB_EKLE_clicked";

        // 001 faturaya malzeme detayı eklemek için dialog oluşturalım
        auto *dia_ftrmlzmekle = new QDialog(this);
        //dia_ftrmlzmekle->setModal (true);
        dia_ftrmlzmekle->setGeometry (50,50,300,300);
        dia_ftrmlzmekle->setWindowTitle ("Faturaya Malzeme Kaydı Ekle");


        // 002 fatura başlığından fatura no (malzemedetayda = gcno)
        //     ve tarihi alalım
        QModelIndex ftr_indx = tb_view->table->currentIndex () ;
        int ftr_row = ftr_indx.row ();

        QString ftrno = tb_model->
                data ( tb_model->
                       index(ftr_row,tb_model->
                             fieldIndex("ftr_no"))).toString() ;
        QString ftrfrm = tb_model->
                data ( tb_model->
                       index(ftr_row,tb_model->
                             fieldIndex("ftr_firma"))).toString() ;

        QString ftrtarih = tb_model->
                data ( tb_model->
                       index(ftr_row,tb_model->
                             fieldIndex("ftr_tarih"))).toString() ;



        // 003 dialoğumuzda fatura detayında olması gerekenleri ekleyelim

        ///  malzemeden malzeme adını almak için linedit ve ekleme pB
        auto *lB_mlzdetmlzm = new QLabel(tr("Malzeme Adı"));
        lE_mlzdetmlzm = new hC_Le;
        lE_mlzdetmlzm->lineEdit->setReadOnly (true);

        ///  malzemeden malzeme kod - barkod - birim
        // sgn ile gelen kod barkod ve birim için değişken
        auto *mlzmKod     = new QString{};
        auto *mlzmMalzeme = new QString{};
        auto *mlzmBarkod  = new QString{};
        auto *mlzmBirim   = new QString{};
        /////////////////////////////////////////////////////////////////
        /// malzeme adını almak için class devrede
        /// class ın içinden malzeme detay bilgilerine
        /// ulaşmak mümkün (mlz->malzeme->MLZMmodel
        /// ama sinyal yoluyla alıyoruz ve classın içeriği hakkında
        /// bişey bilmemiz gerekmiyor...
        ///
        auto *mlz = new hC_MLZM;
        mlz->hide();
        connect (lE_mlzdetmlzm->pushButton, &QPushButton::clicked,
                 [this, mlz, mlzmKod, mlzmMalzeme,
                 mlzmBarkod, mlzmBirim  ] () mutable
        {
            mlz->show();
            /// malzeme detay seçebilmek için pencere
            /// bu pencerenin açılması için
            /// malzeme adı linedeitinin yanındaki
            /// pushbuttonu tıklamak gerekir
            /// HC_LE classında lineedit + pushbutton var

            /////////////////////////////////////////////////////////////////////////////////
            /// ----------------------------------------------------
            /// malzeme tableviewinde gezinirken
            /// 1 - malzeme kodu
            /// 2 - malzeme barkodu
            /// 3 - malzeme adı
            /// 4 - birim
            /// signal ediliyor onu yakalayalım
            /// seçim yapılan lineedit e aktaralım
            /// ----------------------------------------------------

            connect (mlz, &hC_MLZM::sgnMalzeme,
                     [this, mlzmKod, mlzmMalzeme,
                            mlzmBarkod, mlzmBirim  ]
                     ( QString* secKod,
                       QString* secBarkod,
                       QString* secMalzeme,
                       QString* secBirim ) mutable
            {

                mlzmKod     = secKod;
                mlzmMalzeme = secMalzeme;
                mlzmBarkod  = secBarkod;
                mlzmBirim   = secBirim;
                this->lE_mlzdetbarkod->setText( *mlzmBarkod );
                this->lE_mlzdetmlzm->lineEdit->setText ( *secMalzeme );
                this->lE_mlzdetmlzm->lineEdit->setFocus();
                qDebug()<<"signal cathed = "<< secMalzeme ;
            });   /// signal
            //dia_ftrmlzmekle->exec ();
//            qDebug()<<"selected malzeme = "<< mlz->getMalzeme ();

        });  /// HC_LE pushbutton

        /// yeni kayıt ekleme içerisinde
        /// malzeme lineeditin pushbuttonu kontrol edildi
        /// pb na basıldığında malzeme penceresi açıldı
        /// malzeme ismi - kod - barkod - birim signalı alınmaya başlandı


        /// diğer alanlarıda elle dolduralım

        /// - FATURA BAŞLIĞI
        auto *lB_fno = new QLabel("Fatura No");
        auto lE_fno = new QLineEdit ;
        lE_fno->insert (ftrno);
        lE_fno->setReadOnly (true);
        auto *lB_ftr = new QLabel("Fatura Tarihi");
        auto lE_ftr = new QLineEdit ;
        lE_ftr->setText (ftrtarih);
        lE_ftr->setReadOnly (true);
        auto *lB_frm = new QLabel("Firma");
        auto lE_frm = new QLineEdit ;
        lE_frm->setText (ftrfrm);
        lE_frm->setReadOnly (true);

        /// - YENİ GİRİLMESİ GEREKEN ALANLAR
        auto *lB_miktar = new QLabel("Miktar");
        auto *lE_miktar = new QLineEdit;
        auto *lB_bfiyat = new QLabel("Birim Fiyatı");
        auto *lE_bfiyat = new QLineEdit;
        auto *lB_kdv = new QLabel("KDV oranı");
        auto *lE_kdv = new QLineEdit;
        lE_kdv->setText ("18");
        auto *lB_ckl = new QLabel("Açıklama");
        auto *lE_ckl = new QLineEdit;

        auto *lay_dia = new QGridLayout(dia_ftrmlzmekle);
        int str{};
        lay_dia->addWidget (lB_frm   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_frm   ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_fno   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_fno   ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_ftr   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_ftr   ,  str, 1, 1, 1);

        lay_dia->addWidget (lB_mlzdetmlzm   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_mlzdetmlzm ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_miktar,++str, 0, 1, 1);
        lay_dia->addWidget (lE_miktar,  str, 1, 1, 1);
        lay_dia->addWidget (lB_bfiyat,++str, 0, 1, 1);
        lay_dia->addWidget (lE_bfiyat,  str, 1, 1, 1);
        lay_dia->addWidget (lB_kdv   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_kdv   ,  str, 1, 1, 1);
        lay_dia->addWidget (lB_ckl   ,++str, 0, 1, 1);
        lay_dia->addWidget (lE_ckl   ,  str, 1, 1, 1);



        // yeni faturamızı ekleyelim
        QPushButton *pB_mlzekle = new QPushButton("Faturaya Malzeme Kaydı Ekle");
        QPushButton *pB_vzgc = new QPushButton("Kapat");
        lay_dia->addWidget (pB_vzgc       ,++str, 0, 1, 1 );
        lay_dia->addWidget (pB_mlzekle    ,  str, 1, 1, 2 );

        // ekle pencerelrini kapatalım
        connect (pB_vzgc, &QPushButton::clicked,
                 [dia_ftrmlzmekle, mlz ] ()
        {
            dia_ftrmlzmekle->close ();
            mlz->close ();
        });


        /// tüm bilgileri "Faturaya Malzeme Kaydı Ekle"
        /// tuşuna basılırsa fatura detaya eklelyelim
        connect (pB_mlzekle, &QPushButton::clicked,
                 [this, mlzmKod, mlzmBirim,mlzmBarkod,
                 lE_miktar, lE_bfiyat, lE_kdv, lE_ckl,
                 ftrno, ftrtarih
                 ]()
        {

            // malzeme bilgileri fatura detay için yeterli
            // boş geçilmeyecek bir alan yok

            // kayıt oluşturalım
            QSqlRecord rec = FTRDETmodel->record();

            rec.setValue ("mlzmdet_mlzm_kod" , *mlzmKod );    /// signal
            rec.setValue ("mlzmdet_barkod"   , *mlzmBarkod ); /// signal
            rec.setValue ("mlzmdet_malzeme"  , lE_mlzdetmlzm->lineEdit->text() ); /// signal
            rec.setValue ("mlzmdet_tarih"    , ftrtarih); /// faturadan
            rec.setValue ("mlzmdet_gc"       , "Faturalı Giriş");   // yeni girildi
            rec.setValue ("mlzmdet_gcno"     , ftrno);    /// faturadan
            rec.setValue ("mlzmdet_miktar"   , lE_miktar->text ()); // yeni girildi
            rec.setValue ("mlzmdet_birim"    , *mlzmBirim );   /// signal
            rec.setValue ("mlzmdet_fiyat"    , lE_bfiyat->text ()); // yeni girildi
            rec.setValue ("mlzmdet_kdv"      , lE_kdv->text ());    // yeni girildi
            rec.setValue ("mlzmdet_aciklama" , lE_ckl->text ());    // yeni girildi


            // insert a new record (-1)
            if ( ! FTRDETmodel->insertRecord(FTRDETmodel->rowCount (),rec))
            {
                qDebug() << " HATA - FATura Detaya kayıt eklenemedi ";
            }
            else
            {
                qDebug() << " - Kayıt FATURA Detaya eklendi ";
                FTRDETmodel->submitAll ();
                FTRDETmodel->select ();
                // kayıt eklendi yeni kayıt için hazırlık yap
                lE_mlzdetmlzm->lineEdit->setText("");
                lE_miktar->setText ("");
                lE_bfiyat->setText ("");
                lE_kdv->setText ("18");
                lE_ckl->setText ("");



                QModelIndex ftr_ndx= FTRDETmodel->
                        index (FTRDETmodel->rowCount ()-1,0);
                FTRDETtview->table->selectRow (ftr_ndx.row ());


            }

        }); /// kaydı dosyaya kaydet pb

        dia_ftrmlzmekle->show ();

        qDebug ()<<"mlzm un 4";



    });  /// FTRDETtview yeni kayıt pushbutton

    // pB 002 yeni resim ekle

    // -- 003  row değiştiğnde resmide değiştirelim

    // pB 004 yeni camera resim ekle

    // pB 005 sil
    connect(FTRDETtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   FTRDETtview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = FTRDETmodel->record();

            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;

            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n faturanoli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                FTRDETmodel->removeRow(sample.row());
                FTRDETmodel->submitAll ();
                //pmodel->endRemoveColumns();
                FTRDETmodel->select ();
            }
        }

    });



    // pB 006 ilk
    connect(FTRDETtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FTRDETmapper->toFirst ();
        FTRDETtview->pB_ilk->setEnabled (FTRDETmapper->currentIndex ()>0);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(FTRDETtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FTRDETmapper->toPrevious ();
        FTRDETtview->pB_ncki->setEnabled(FTRDETmapper->currentIndex () > 0);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( FTRDETmapper->currentIndex () ,0));
    });

    // pB 008 sonraki
    connect(FTRDETtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        FTRDETmapper->toNext ();
        int map_row = FTRDETmapper->currentIndex ();
        FTRDETtview->pB_snrki->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(FTRDETtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        tb_mapper->toLast ();
        int map_row = FTRDETmapper->currentIndex ();
        FTRDETtview->pB_son->setEnabled(map_row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->table->setCurrentIndex(FTRDETmodel->index( FTRDETmodel->rowCount() - 1  ,0));
    });

    qDebug()<<" 1 ";
    /// depodet map değiştiğinde nav tuşalrı ayarlansın
    // pB 010 nav tuslari kontrol
    connect(FTRDETmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //.row ();   //FTRDETmapper->currentIndex ();
        FTRDETtview->pB_ilk->setEnabled (row>0);
        FTRDETtview->pB_ncki->setEnabled(row > 0);
        FTRDETtview->pB_snrki->setEnabled(row < FTRDETmodel->rowCount() - 1);
        FTRDETtview->pB_son->setEnabled(row < FTRDETmodel->rowCount() - 1);

    });
    qDebug()<<" 2 ";
    // --- 011 FTRDET row değiştiğinde 2 şey olsun
    connect( FTRDETslctnMdl, &QItemSelectionModel::currentRowChanged,
             [this]( QModelIndex Index )
    {
        if (Index.isValid())
        {

            qDebug()<<" 3323 ";
            // 011-01 mapper indexi ayarla
            FTRDETmapper->setCurrentModelIndex(Index);

            qDebug()<<" 23 ";
            // 011-02 fatura hesabı yapılsın
            this->slt_ftr_hesap ();
        }
    });

    // --- 011 row FTR değiştiğinde
    connect( tb_slctnMdl, &QItemSelectionModel::currentRowChanged,
             [this]( QModelIndex Index )
    {
        if (Index.isValid())
        {
            // 011-02 filtrele
            QSqlRecord record = tb_model->record(Index.row ());
            QString fatura_no = record.value("ftr_no").toString ();
            FTRDETmodel->setFilter (QString("mlzmdet_gcno = %1").arg(fatura_no) );

        }
        else
        {
            FTRDETmodel->setFilter("mlzdet_gcno=-1");
            qDebug()<<" 32 ";
        }
        FTRDETmodel->select();

        qDebug()<<" 23 ";
        // 011-02 fatura hesabı yapılsın
        this->slt_ftr_hesap ();

    });
    qDebug()<<" 3 ";
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(FTRDETslctnMdl, &QItemSelectionModel::currentColumnChanged,
            [this]( QModelIndex Index )
    {
        FTRDETmapper->setCurrentModelIndex(Index);
    });

    qDebug()<<" 4 ";
    // --- 013 tableviewde miktar ve grs cks değştiğinde hsap yapılsın
    connect(FTRDETtview->table->model() ,
            &QSqlTableModel::dataChanged , this,
            &hC_FTR::slt_ftr_hesap);

    // --- 014 depodet miktar değiştiğinde depo envanter hesabı
    connect (lE_mlzdetmiktar, &QLineEdit::editingFinished, this,
             &hC_FTR::slt_ftr_hesap);
    qDebug()<<" 5 ";
}
*/
void hC_FTR::showEvent(QShowEvent *)
{
    qDebug() << "   Show event - - - Ftr dosyası açılıyor";
}

hC_FTR::~hC_FTR()
{
    //    delete ui;
}




/*



QString hC_FTR::ftr_VTd ()
{
    QSqlQuery   q;
    QString     ct, mesaj = "  OK - Fatura" ;
    QStringList inserts;
    QString FTRtableName( "ftr__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains(FTRtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + FTRtableName +
             "("
             "  ftr_kod    INTEGER PRIMARY KEY  , "
             "  ftr_no  	TEXT ,"
             "  ftr_firma	TEXT ,"
             "  ftr_tarih	TEXT ,"
             "  ftr_aciklama TEXT ,"
             "  ftr_resim    BLOB  )" ;

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - FATURA Dosyası Oluşturulamadı - "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = " OK - Fatuura Dosyası YENİ Oluşturuldu - ";
            inserts << "INSERT INTO " + FTRtableName +
                       "( "
                       "ftr_no , ftr_firma "
                       ") "
                       "VALUES "
                       "("
                       "'1', 'İlk Firma -' "
                       " )" ;

            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {
                    mesaj = "<br>İLK Fatura Eklenemedi"
                            "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else
                {
                    mesaj = mesaj + "<br>İLK Fatura Eklendi";
                }
            } // foreach
        }
    }
    else /// dosya var
    {
        // mdlFtr = new QSqlRelationalTableModel;
        // mdlFtr = modelFatura();
    }

    qDebug()<< mesaj ;
    return mesaj;
}

void hC_FTR::ftr_model()
{
    qDebug() << "  ftr_model";
    QString indexField = "ftr_tarih";
    QString tableName ("ftr__dbtb");
    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Fatura Kod");
    tB_FieldList->append("Fatura No");
    tB_FieldList->append("Firma Unvanı");
    tB_FieldList->append("Fatura Tarihi");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Resim");

    tb_model = new QSqlRelationalTableModel ;
   hC_Rm hC_Rm (&tableName,
                 tb_model,
                 &indexField ,
                 tB_FieldList) ;

}///FATURA

void hC_FTR::ftrdet_model (QSqlRelationalTableModel *model)
{
    /// NOTE Model 1 mw_main de modeli oluştur
    /// fatura detayında
    /// malzeme detay dosyası oluşturuluyor
    QString tableName ("mlzmdet__dbtb");
    QString indexField = "mlzmdet_gcno";

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

  hC_Rm hC_Rm (&tableName,
                 model,
                 &indexField ,
                 tB_FieldList) ;

}///fatura detasy Model





// ////////////////////////////////////////
// / \brief Ftr_FrmEkle::Ftr_FrmEkle
// / \param parent
// /
// / faturaya firma ekle

Ftr_FrmEkle::Ftr_FrmEkle(QDialog *parent) : QDialog(parent)
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


    // firma class ımızı getirelim
    firma = new hC_FRM;
    firma->frm_setup ();
    layout_diafr->addWidget (firma ,0 ,0 ,1, 1);
    //diafr->show();


    /////////////////////////////////////////////////////////////////////////////////
    // ----------------------------------------------------
    // firma tableviewinde gezinirken firma adımız
    // seçim yapılan lineedit e aktaralım
    // ----------------------------------------------------
    connect (firma->FRMslctnMdl,
             &QItemSelectionModel::currentChanged  ,
             [ this ] (QModelIndex Index )

    {

        //QModelIndex firmandx = firma->FRMtview->table->currentIndex ()  ;
        int fr_row = Index.row ();
        this->setFirma (firma->FRMmodel->data(
                            firma->FRMmodel->index
                            (fr_row,firma->FRMmodel->fieldIndex ("frm_unvan"))
                            ).toString () )  ;

    });

    this->show ();
}

void Ftr_FrmEkle::reject()
{
    qDebug()<<"rejected";

    QDialog::reject();
}



Ftr_FrmEkle::~Ftr_FrmEkle()
{
}

QString Ftr_FrmEkle::getFirma() const
{
    qDebug()<<"return from getfirma"<<m_firma;
    return m_firma;
}

void Ftr_FrmEkle::setFirma(const QString &value)
{
    m_firma = value;
}

*/
