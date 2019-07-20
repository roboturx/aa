#include "iedet.h"


hC_IEDET::hC_IEDET()  : hC_tBcreator ()
{
    qDebug ()<<"Constructor İŞ EMRİ DETAY ***************************";
    //************************************************************
    //*****************  İ Ş   E M R İ D E T A Y *****************


    win_Label->setText ( "İŞ EMRİ DETAY KAYITLARI");
    *tb_name  = "iedet_dbtb" ;
    *tb_ndex  = "iedet_ie_no";
    //*tb_id    = "iedet_id";

    tb_flds = new hC_ArrD (9, 4);
    tb_flds->setValue ( 0, "iedet_ID"       , "INTEGER", "IEdetayID", "0" ) ;
    tb_flds->setValue ( 1, "iedet_ie_no"    , "INTEGER", "Iş Emri No");
    tb_flds->setValue ( 2, "iedet_aciklama" , "TEXT"   , "Açıklama" );
    tb_flds->setValue ( 3, "iedet_tamiryeri", "TEXT"   , "Tamir Yeri");
    tb_flds->setValue ( 4, "iedet_tybolum"  ,"TEXT"    , "T.Y. Bölümü"   );
    tb_flds->setValue ( 5, "iedet_durum"    , "TEXT"   , "İşin Durumu"   );
    tb_flds->setValue ( 6, "iedet_girtar"   , "TEXT"   , "Araç Giriş Tarihi"    );
    tb_flds->setValue ( 7, "iedet_ciktar"   , "TEXT"   , "Araç Çıkış Tarihi"   );
    tb_flds->setValue ( 8, "iedet_resim"    , "BLOB"   , "Resim" , "0" );


    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_IEno = new QLineEdit  ) ;
    tb_wdgts->append ( lE_IEdetaciklama = new QLineEdit  ) ;
    tb_wdgts->append ( cbx_IEdettamiryeri = new QComboBox ) ;
    tb_wdgts->append ( cbx_IEdettamirbolum = new QComboBox    ) ;
    tb_wdgts->append ( cbx_IEdetdurum = new QComboBox ) ;
    tb_wdgts->append ( dE_IEdetgirtarihi = new QDateTimeEdit(QDate::currentDate ()) ) ;
    tb_wdgts->append ( dE_IEdetciktarihi = new QDateTimeEdit(QDate::currentDate ()) ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;

}

void hC_IEDET:: tbsetup()
{

    qDebug() << "   iedet setup ";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_IEDET:: tbui()
{
    qDebug() << "   ui";

    hC_IEDET::setWindowTitle (win_Label->text());
    hC_IEDET::setGeometry(10,
                          qApp->screens()[0]->size ().rwidth ()/2,
            600,300);

    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget ( tb_view ,  0, 0, 1, 1 );
    win_Grid->addWidget ( win_Wdgt  ,  0, 1, 1, 1 );
}

void hC_IEDET:: tbwdgt ()
{
    qDebug() << "   WDGT";
    auto *lB_ieno = new QLabel("İş Emri No");
    lB_ieno->setBuddy(lE_IEno);

    auto *lB_acklm = new QLabel("Açıklama");
    lB_acklm->setBuddy(lE_IEdetaciklama);

    auto *lB_krm = new QLabel("Tamir Yeri");
    QStringList tylist {" ",
                        "Atolye",
                        "Arazi",
                        "Yetkili Servis",
                        "Dış Servis"};
    cbx_IEdettamiryeri->addItems(tylist);
    lB_krm->setBuddy(cbx_IEdettamiryeri);

    auto *lB_tm = new QLabel("Atolye Bolüm");
    QStringList ablist {" ",
                        "Boya",
                        "Kaporta",
                        "Motor",
                        "Torna",
                        "Mekanik"};
    cbx_IEdettamirbolum->addItems(ablist);
    lB_tm->setBuddy(cbx_IEdettamirbolum );

    auto *lB_dr = new QLabel("İş Durumu");
    QStringList drlist { " ",
                         "Parça Bekliyor",
                         "Usta Bekliyor",
                         "Tamamlandı"};
    cbx_IEdetdurum->addItems(drlist);
    lB_dr->setBuddy(cbx_IEdetdurum);

    auto *lB_gt = new QLabel("Araç Giriş Tarihi");
    hC_Gz (dE_IEdetgirtarihi,"nulldate");
    lB_gt->setBuddy(dE_IEdetgirtarihi);

    auto *lB_ct = new QLabel("Araç Çıkış Tarihi");
    hC_Gz(dE_IEdetciktarihi,"nulldate");
    lB_ct->setBuddy(dE_IEdetciktarihi);
    // ///////////////////////////////////////////////////////
    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    
    win_Wdgt->adjustSize();
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_IEdetaciklama->setMinimumSize (200,25);

    wdgtGrid->addWidget(lB_acklm            ,1,0,1,1);
    wdgtGrid->addWidget(lE_IEdetaciklama    ,1,1,1,3);
    wdgtGrid->addWidget(lB_krm              ,2,0,1,1);
    wdgtGrid->addWidget(cbx_IEdettamiryeri  ,2,1,1,3);
    wdgtGrid->addWidget(lB_tm               ,3,0,1,1);
    wdgtGrid->addWidget(cbx_IEdettamirbolum ,3,1,1,3);
    wdgtGrid->addWidget(lB_dr               ,4,0,1,1);
    wdgtGrid->addWidget(cbx_IEdetdurum      ,4,1,1,3);
    wdgtGrid->addWidget(lB_gt               ,7,0,1,1);
    wdgtGrid->addWidget(dE_IEdetgirtarihi   ,7,1,1,3);
    wdgtGrid->addWidget(lB_ct        ,8,0,1,1);
    wdgtGrid->addWidget(dE_IEdetciktarihi   ,8,1,1,3);
    wdgtGrid->addWidget (win_Rsm      , 9, 1, 1, 2);

}

void hC_IEDET:: tbkntrl()
{


    qDebug()<<"   iedet kntrl ";

    /////////////////////////////////////////////////////
    ie = new hC_IE;
    ie->tbsetup();
    ie->show();
    // /// 12- set filter
    ienoo = new int;

    QModelIndex Index = ie->tb_view->table->currentIndex ();
    *ienoo = ie->tb_model->data (ie->tb_model->
                index (Index.row (), ie->tb_model->
                       fieldIndex ("ie_no") )).toInt ();


    connect(ie, &hC_IE::sgnIsEmri ,
            [this ] (int ie_ieno)
    {
        *ienoo = ie_ieno;
        tb_model->setFilter(
                    QString(" iedet_ie_no = %1").arg(*ienoo) );
    });
    //////////////////////////////////////////////

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        connect(ie, &hC_IE::sgnIsEmri ,
                [this ] (int ie_ieno)
        {
            *ienoo = ie_ieno;
            qDebug()<<"ienooooo"<<*ienoo;
        });

        ////////////////////////////////////////////////
        hC_Nr maxID;
        int* max_id = new int{};
        *max_id     = maxID.hC_NrMax ( tb_name,
                            tb_flds->value (0,0));
        ////////////////////////////////////////////////
        /// yeni iş emri detay numaasını bul
        /// iş emri detay nosu  _dbtb de
        ///   no alanındaki en büyük sayı
        //// yeni kaydı ekle


              qDebug()<<"ienooooo"<<*ienoo;
        QSqlQuery q;
        QString qry, mesaj("");
        //QSqlQuery q;
        qry="INSERT INTO  "+*tb_name+" ( "
            " iedet_ie_no    , "
            " iedet_aciklama , "
            " iedet_tamiryeri, "
            " iedet_tybolum  , "
            " iedet_durum    , "
            " iedet_girtar   , "
            " iedet_ciktar     "
            " )"
            " values( ?, ?, ?, ?, ?, ?, ? )";
        q.prepare(qry);

        q.bindValue(0, *ienoo  );
        q.bindValue(1, " " );
        q.bindValue(2, " " );
        q.bindValue(3, " " );
        q.bindValue(4, " " );
        q.bindValue(5, " " );
        q.bindValue(6, " " );


        q.exec();

        if (q.isActive())
        {
            qDebug () <<"İş Emri Detay Yeni Kayıt Eklendi - "+
                        q.lastInsertId ().toString ();


            //lE_IEno
            lE_IEdetaciklama->setText ("");
            cbx_IEdettamiryeri->setCurrentIndex (0);
            cbx_IEdettamirbolum ->setCurrentIndex (0);

            hC_Gz ( dE_IEdetgirtarihi, "nulldate");
            hC_Gz ( dE_IEdetciktarihi, "nulldate");
            cbx_IEdetdurum->setCurrentIndex (0);

            tb_model->select ();
            ////////////////////////////////////////////////
            maxID.hC_NrGo (tb_view, *max_id , 0);
            ////////////////////////////////////////////////




        }
        else
        {
            qDebug () << "İş Emri Detay Yeni Kayıt Eklenemedi - "
                      << q.lastError().text();
        }
      //  tb_view->table->setFocus ();
        // iş emri detay ekle
    });
    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
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
            QModelIndex  indx = tb_view->table->currentIndex ();
            QString ino = tb_model->data
                    (tb_model->index
                     ( indx.row (),
                      tb_model->fieldIndex ("id_iedet"))).toString ();

            s_qry = QString("DELETE FROM  _dbtb "
                            "WHERE id_iedet = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Rmri Detay Kaydı Silindi ";
                //   mdl_mkn->submitAll ();
                tb_model->select ();
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


        tb_model->select ();
        tb_view->table->setCurrentIndex(
                    tb_model->index(0
                                      , 2)
                    );


        //        tb_model->select();  //q.lastInsertId ().toInt ()
        /*     tbx_slctnMdl->setCurrentIndex (
                    tb_model->index (q.lastInsertId ().toInt () , 3 ) ,
                    QItemSelectionModel::ClearAndSelect
                    );
*/
        tb_view->table->setFocus ();

    });
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_IEDET::sgn(tb_view->table->model()->index( Index.row() ,
        //               tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });

    // --- 013-01 iş durumuna göre tarihleri gizle
    connect(  cbx_IEdetdurum , &QComboBox::currentTextChanged,
              [this]( QString text )
    {
        if (text == " ")
        {
            hC_Gz ( dE_IEdetgirtarihi, "0" );
            hC_Gz ( dE_IEdetciktarihi, "0" );
        }
        else if (text == "Parça Bekliyor")
        {
            hC_Gz ( dE_IEdetgirtarihi, "1" );
            hC_Gz ( dE_IEdetciktarihi, "0" );
        }
        else if (text == "Usta Bekliyor")
        {

            hC_Gz ( dE_IEdetgirtarihi, "1" );
            hC_Gz ( dE_IEdetciktarihi, "0" );
        }
        else if (text == "Tamamlandı")
        {
            hC_Gz ( dE_IEdetgirtarihi, "1" );
            hC_Gz ( dE_IEdetciktarihi, "1" );
        }
    });

}



hC_IEDET::~hC_IEDET()
{
    qDebug() << "*********** destructor İŞ EMRİ DETAY ";//    delete ui;
}


