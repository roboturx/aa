#include "ftr.h"
#include "mlzm.h"
#include "frm.h"


hC_FTR::hC_FTR() : hC_tBcreator ()
{
    //************************************************************
    //*****************  F A T U R A  ****************************
    qDebug() << "Ftr Cnstrctr";

    win_Label->text ()= "FATURA BAŞLIK BİLGİ GİRİŞ";
    *tb_name  = "ftr_dbtb" ;
    *tb_ndex  = "ftr_tarih";

    tb_flds = new hC_ArrD ( 5, 4);
    tb_flds->setValue ( 0, "ftr_ID"      , "INTEGER", "FaturaID", "0" ) ;
    tb_flds->setValue ( 1, "ftr_no"      , "TEXT"   , "Fatura No" );
    tb_flds->setValue ( 2, "ftr_frm"     , "TEXT"   , "Firma Unvanı" );
    tb_flds->setValue ( 3, "ftr_tarih"   , "TEXT"   , "Fatura Tarihi");
    tb_flds->setValue ( 4, "ftr_aciklama", "TEXT"   , "Açıklama"   );
    tb_flds->setValue ( 5, "ftr_resim"   , "BLOB"   , "Resim" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_faturano = new QLineEdit  ) ;
    tb_wdgts->append ( lE_firma = new hC_Le  ) ;
    tb_wdgts->append ( lE_tarih = new QLineEdit ) ;
    tb_wdgts->append ( lE_aciklama = new QLineEdit    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;


}



void hC_FTR::tbsetup()
{
    qDebug() << "  ftr_setup ";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_FTR::tbui()
{
    qDebug() << "  ftr_ui";

    ////////////////////////////////////////// window

    hC_FTR::setWindowTitle(win_Label->text ());

    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget (tb_view  , 0, 0, 1, 1);
    win_Grid->addWidget (win_Wdgt   , 0, 1, 1, 1);

}

void hC_FTR::tbwdgt()
{
    qDebug() << "  ftr_wdgt";

    auto *lB_faturano = new QLabel("Fatura &No");
    lE_faturano->setReadOnly (true);
    //lE_faturano->setPlaceholderText ("Fatura No ");
    lB_faturano->setBuddy(lE_faturano);

    auto *lB_firma = new QLabel("Firma Ünvanı ");
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
        firma->tbsetup ();
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

    auto *lB_tarih = new QLabel("Fatura &Tarihi");
    lB_tarih->setBuddy(lE_tarih);

    auto *lB_ack = new QLabel("&Açıklama");
    lB_ack->setBuddy(lE_aciklama);

    auto *lB_ftrToplam = new QLabel("Fatura Toplamı");
    lE_ftrToplam = new QLineEdit();
    lB_ftrToplam->setBuddy(lE_ftrToplam);

    auto *lB_ftrKdv = new QLabel("KDV");
    lE_ftrKdv = new QLineEdit();
    lB_ftrKdv->setBuddy(lE_ftrKdv);

    auto *lB_ftrGenelToplam = new QLabel("Genel Toplam");
    lE_ftrGenelToplam = new QLineEdit();
    lB_ftrGenelToplam->setBuddy(lE_ftrGenelToplam);

    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->adjustSize();
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

void hC_FTR::tbkntrl()
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
            /// barkod nosu ftr__dbtb de
            /// ftr_barkod alanındaki en büyük sayı
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
                /// ambara ait ftr_det giriş kayıtlarını sil
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


void hC_FTR::showEvent(QShowEvent *)
{
    qDebug() << "   Show event - - - Ftr dosyası açılıyor";
}

hC_FTR::~hC_FTR()
{
    //    delete ui;
}

