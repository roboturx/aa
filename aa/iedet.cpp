#include "iedet.h"


hC_IEDET::hC_IEDET(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"Cnstrctr İş Emri Detay";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IEDET::iedet_setup()
{

    qDebug() << "  iedet setup ";
    iedet_VTd   () ;
    iedet_model () ;
    iedet_wdgt  () ;
    iedet_map   () ;
    iedet_ui    () ;
    iedet_view  () ;
    iedet_kntrl () ;
}


void hC_IEDET::iedet_ui()
{
    qDebug() << "  iedet_ui";
    iedetLb  = new QLabel ("İŞ EMRİ DETAY");
    hC_IEDET::setWindowTitle (iedetLb->text());
    hC_IEDET::setGeometry(10,
                          qApp->screens()[0]->size ().rwidth ()/2,
            600,300);
    //   hC_IEDET::showMaximized ();



    // ///////////////////////////////////////////////////////
    IEDETtview = new hC_Tv (IEDETmodel, IEDETmapper, iedetWdgt);

    // ///////////////////////////////////////////////////////

    auto *iedetGrid = new QGridLayout(this);
    iedetGrid->addWidget ( IEDETtview ,  0, 0, 1, 1 );
    iedetGrid->addWidget ( iedetWdgt  ,  0, 1, 1, 1 );
}

void hC_IEDET::iedet_wdgt ()
{
    auto *lB_ieno = new QLabel("İş Emri No");
    lE_IEno = new QLineEdit;
    lB_ieno->setBuddy(lE_IEno);

    auto *lB_acklm = new QLabel("Açıklama");
    lE_IEdetaciklama = new QLineEdit;
    lB_acklm->setBuddy(lE_IEdetaciklama);

    auto *lB_krm = new QLabel("Tamir Yeri");
    cbx_IEdettamiryeri = new QComboBox;
    QStringList tylist {" ",
                        "Atolye",
                        "Arazi",
                        "Yetkili Servis",
                        "Dış Servis"};
    cbx_IEdettamiryeri->addItems(tylist);
    lB_krm->setBuddy(cbx_IEdettamiryeri);

    auto *lB_tm = new QLabel("Atolye Bolüm");
    cbx_IEdettamirbolum = new QComboBox;
    QStringList ablist {" ",
                        "Boya",
                        "Kaporta",
                        "Motor",
                        "Torna",
                        "Mekanik"};
    cbx_IEdettamirbolum->addItems(ablist);
    lB_tm->setBuddy(cbx_IEdettamirbolum );

    auto *lB_dr = new QLabel("İş Durumu");
    cbx_IEdetdurum = new QComboBox;                    // dbtb_durum
    QStringList drlist { " ",
                         "Parça Bekliyor",
                         "Usta Bekliyor",
                         "Tamamlandı"};
    cbx_IEdetdurum->addItems(drlist);
    lB_dr->setBuddy(cbx_IEdetdurum);

    auto *lB_gt = new QLabel("Araç Giriş Tarihi");
    dE_IEdetgirtarihi = new QDateTimeEdit();
    hC_Gz (dE_IEdetgirtarihi,"nulldate");
    lB_gt->setBuddy(dE_IEdetgirtarihi);

    auto *lB_ct = new QLabel("Araç Çıkış Tarihi");
    dE_IEdetciktarihi = new QDateTimeEdit();
    hC_Gz(dE_IEdetciktarihi,"nulldate");
    lB_ct->setBuddy(dE_IEdetciktarihi);
    // ///////////////////////////////////////////////////////
    iedetRsm = new QLabel ("Resim");
    hC_Rs resim(iedetRsm);


    ///////////////////////////////////////
    iedetWdgt = new QWidget;
    iedetWdgt->setGeometry (0,0,800,300);
    auto iedetGrid = new QGridLayout();
    iedetWdgt->setLayout(iedetGrid);

    ///////////////////////////////////////
    lE_IEdetaciklama->setMinimumSize (200,25);

    iedetGrid->addWidget(lB_acklm            ,1,0,1,1);
    iedetGrid->addWidget(lE_IEdetaciklama    ,1,1,1,3);
    iedetGrid->addWidget(lB_krm              ,2,0,1,1);
    iedetGrid->addWidget(cbx_IEdettamiryeri  ,2,1,1,3);
    iedetGrid->addWidget(lB_tm               ,3,0,1,1);
    iedetGrid->addWidget(cbx_IEdettamirbolum ,3,1,1,3);
    iedetGrid->addWidget(lB_dr               ,4,0,1,1);
    iedetGrid->addWidget(cbx_IEdetdurum      ,4,1,1,3);
    iedetGrid->addWidget(lB_gt               ,7,0,1,1);
    iedetGrid->addWidget(dE_IEdetgirtarihi   ,7,1,1,3);
    iedetGrid->addWidget(lB_ct        ,8,0,1,1);
    iedetGrid->addWidget(dE_IEdetciktarihi   ,8,1,1,3);

    iedetGrid->addWidget (new QLabel("Resim") , 9, 0, 1, 1);
    iedetGrid->addWidget (iedetRsm      , 9, 1, 1, 2);

}



void hC_IEDET::iedet_view()
{
    qDebug()<<" -iedet view ";
    IEDETtview->table->setModel(IEDETmodel);
    IEDETslctnMdl = IEDETtview->table->selectionModel();
    //// kullanıcı bu alanları görmesin
    // IEDETtview->table->setColumnHidden(
    //           IEDETmodel->fieldIndex("iedet_ie_id"), true);
    // IEDETtview->table->setColumnHidden(
    //           IEDETmodel->fieldIndex("iedet_iedet_no"), true);

    IEDETtview->table->setColumnHidden(
                IEDETmodel->fieldIndex("iedet_resim"), true);

    //IEDETtview->table->setColumnHidden(
    //          IEDETmodel->fieldIndex("iedet_iedet_no"), true);
    IEDETtview->table->setColumnHidden(
                IEDETmodel->fieldIndex("id_IEdet"), true);

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    IEDETtview->table->setCurrentIndex(
                IEDETmodel->index(1, 2)
                );
    // with blue rect
    IEDETtview->table->setFocus();
    //   QTimer::singleShot(0, IEDETtview->table, SLOT(setFocus()));
}
void hC_IEDET::iedet_map()
{
    qDebug()<<" -iedet map";
    /// mapper IEdet
    IEDETmapper = new QDataWidgetMapper(this);
    IEDETmapper->setModel(IEDETmodel);


    IEDETmapper->addMapping(lE_IEno , IEDETmodel->
                            fieldIndex("iedet_ie_id"));
    IEDETmapper->addMapping(lE_IEdetaciklama , IEDETmodel->
                            fieldIndex("iedet_aciklama"));
    IEDETmapper->addMapping(cbx_IEdettamiryeri , IEDETmodel->
                            fieldIndex("iedet_tamiryeri"));
    IEDETmapper->addMapping(cbx_IEdettamirbolum , IEDETmodel->
                            fieldIndex("iedet_tamirbolum"));
    IEDETmapper->addMapping(cbx_IEdetdurum, IEDETmodel->
                            fieldIndex("iedet_durum"));
    IEDETmapper->addMapping(dE_IEdetgirtarihi , IEDETmodel->
                            fieldIndex("iedet_girtar"));
    IEDETmapper->addMapping(dE_IEdetciktarihi , IEDETmodel->
                            fieldIndex("iedet_ciktar"));


    IEDETmapper->toFirst ();
}


void hC_IEDET::iedet_kntrl()
{


    qDebug()<<" -iedet kntrl ";

    /////////////////////////////////////////////////////
    ie = new hC_IE;
    ienoo = new int;
    ie->ie_setup();
    ie->show();
    // /// 12- set filter

    connect(ie, &hC_IE::sgnIsEmri ,
            [this ] (int ie_ieno)
    {
        *ienoo = ie_ieno;
        IEDETmodel->setFilter(
                    QString("iedet_ie_id = %1").arg(ie_ieno) );
    });
    //////////////////////////////////////////////

    // pB 001 yeni ekle
    connect(IEDETtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QString IEtableName{"iedet__dbtb"};
        QSqlQuery q;
        QString qry, mesaj("");

        /// yeni iş emri detay numaasını bul
        /// iş emri detay nosu iedet__dbtb de
        /// iedet_iedet_no alanındaki en büyük sayı
        qry = "SELECT max(iedet_iedet_no) FROM " + IEtableName  ;
        int iedetno;
        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "İş Emri Detay No bulunamadı \n"+
                    "------------------------------------\n"+
                    q.lastError().text ()+
                    "------------------------------------\n";
            return;
        }
        else
        {
            q.next();
            iedetno = q.value(0).toInt();
            mesaj = mesaj + "MAX VAL =" + QString::number(iedetno) ;
        }

        qDebug()<< endl << "last inserted id  : "
                << q.lastInsertId ().toString ();
        //  IEmodel->select();

        qDebug()<< endl <<mesaj<<endl<< "iedetno    :"<< iedetno;
        iedetno= iedetno + 1 ;
        qDebug()<< endl << "iedetno +1 :"<< iedetno;
        //// yeni kaydı ekle
        //QSqlQuery q;
        QString q_s;
        q_s="INSERT INTO iedet__dbtb ( "
            "iedet_ie_id     , "
            "iedet_iedet_no  , "
            "iedet_tamiryeri , "
            "iedet_tamirbolum, "
            "iedet_durum     , "
            "iedet_girtar    , "
            "iedet_ciktar      "
            " )"
            " values( ?, ?, ?, ?, ?, ?, ? )";
        q.prepare(q_s);

        q.bindValue(0, *ienoo  );
        q.bindValue(1, iedetno );
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





        }
        else
        {
            qDebug () << "İş Emri Detay Yeni Kayıt Eklenemedi - "
                      << q.lastError().text();
        }
        IEDETmodel->select ();
        ////////////////////////////////////////////////
        hC_Nr (IEDETtview, iedetno, 1);
        ////////////////////////////////////////////////
        IEDETtview->table->setFocus ();
        // iş emri detay ekle
    });
    // pB 002 yeni resim ekle
    connect(IEDETtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(iedetRsm, IEDETtview, IEDETmodel, IEDETslctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  IEDETslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( iedetRsm, IEDETtview, IEDETmodel, IEDETslctnMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(IEDETtview->pB_sil, &QPushButton::clicked,
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
            QModelIndex iedet_indx = IEDETtview->table->currentIndex ();
            QString ino = IEDETmodel->data
                    (IEDETmodel->index
                     (iedet_indx.row (),
                      IEDETmodel->fieldIndex ("id_iedet"))).toString ();

            s_qry = QString("DELETE FROM iedet__dbtb "
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


        IEDETmodel->select ();
        IEDETtview->table->setCurrentIndex(
                    IEDETmodel->index(0
                                      , 2)
                    );


        //        IEDETmodel->select();  //q.lastInsertId ().toInt ()
        /*     IEDETslctnMdl->setCurrentIndex (
                    IEDETmodel->index (q.lastInsertId ().toInt () , 3 ) ,
                    QItemSelectionModel::ClearAndSelect
                    );
*/
        IEDETtview->table->setFocus ();

    });
/*
    // pB 006 ilk
    connect(IEDETtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        IEDETtview->hC_TvPb ("ilk", IEDETmodel, IEDETmapper);
    });

    // pB 007 önceki
    connect(IEDETtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        IEDETtview->hC_TvPb ("ncki", IEDETmodel, IEDETmapper);
    });

    // pB 008 sonraki
    connect(IEDETtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        IEDETtview->hC_TvPb ("snrki", IEDETmodel, IEDETmapper);
    });

    // pB 009 son
    connect(IEDETtview->pB_son, &QPushButton::clicked,
            [this]()
    {IEDETtview->hC_TvPb ("son", IEDETmodel, IEDETmapper);
    });



    // pB 010 nav tuslari kontrol
    connect(IEDETmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {IEDETtview->hC_TvPb ("yenile", IEDETmodel, IEDETmapper);

    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  IEDETslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        IEDETmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_IEDET::sgn(IEDETtview->table->model()->index( Index.row() ,
        //               IEDETmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  IEDETslctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        IEDETmapper->setCurrentModelIndex(Index);
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



//void hC_IEDET::rowChanged_IEDET(QModelIndex IEDETindex)
//{

//    //QModelIndex index = IEDETtview->table->currentIndex();
//    if (IEDETindex.isValid())
//    {
//        QSqlRecord record = IEDETmodel->record(IEDETindex.row());
//        QString ieno = record.value("id_iedet").toString() ;
//        ///setfiltr to tasinir and iscilik
//        TSmodel->setFilter (QString("ts_iedet_id = '%1'" ).arg(ieno));
//        TSmodel->select();
//         TStview->setFocus();
//        SCmodel->setFilter (QString("sc_iedet_id = '%1'" ).arg(ieno));
//        SCmodel->select();
//SCtview->setFocus();

//        /*lbl_IE->
//                setText((record.value("mknstk_no").toString()+
//                         " - " +
//                         record.value("ie_no").toString() ));*/
//    } else
//    {
////        TSmodel->setFilter("id_tasinir = -1");
//  //      SCmodel->setFilter("id_iscilik = -1");
//    }

// /*   // qDebug () <<"iedet row changggggedd 2";
//    //IEDETmodel->select();
//    TStview->setFocus();
//    SCtview->setFocus();
//    IEDETmodel->select();


//    //qDebug () <<"iedet row changggggedd 3";
//*/
//     IEDETtview->table->setFocus();
//
//}




hC_IEDET::~hC_IEDET()
= default;


QString hC_IEDET::iedet_VTd ()
{
    QSqlQuery q;
    QString ct,

            mesaj = { "  OK - VTd - İş Emri Detay" } ,
            IEDETtableName {"iedet__dbtb"};

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( IEDETtableName ))
    {



        ct = "CREATE TABLE IF NOT EXISTS " +IEDETtableName +
                "("
                "iedet_ie_id	    TEXT, "
                "iedet_iedet_no	INTEGER, "
                "iedet_aciklama	TEXT, "
                "iedet_tamiryeri TEXT, "
                "iedet_tamirbolum TEXT, "
                "iedet_durum     TEXT, "
                "iedet_girtar    TEXT, "
                "iedet_ciktar    TEXT, "
                "iedet_resim     BLOB, "
                "id_IEdet integer primary key  )"  ;


        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - İş Emri Detay Dosyası Oluşturulamadı  "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - İş Emri Detay Dosyası YENİ Oluşturuldu ";

            QString qry = "INSERT INTO "+IEDETtableName+""
                                                        " ( iedet_ie_id ) values( 1 )"  ;

            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "<br>İLK İş Emri Detay kaydı Eklenemedi"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "<br>İLK İş Emri Detay kaydı eklendi.";
            }
        }
    }
    qDebug ()<< mesaj;
    return mesaj ;

}




void hC_IEDET::iedet_model()
{
    qDebug() << "  iedet mdl";
    QString indexField = "iedet_aciklama";
    QString tableName ("iedet__dbtb");
    QStringList *tB_FieldList = new QStringList ;

    tB_FieldList->append("İENo");
    tB_FieldList->append("IEDETNo");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Tamir Yeri");
    tB_FieldList->append("Tamir Bölüm");
    tB_FieldList->append("Durum");
    tB_FieldList->append("Giriş Tarihi");
    tB_FieldList->append("Çıkış Tarihi");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Detay ID");

    IEDETmodel = new QSqlRelationalTableModel;
    hC_Rm hC_Rm ( &tableName,
                  IEDETmodel,
                  &indexField ,
                  tB_FieldList) ;
    //    qDebug() <<"iedetmodel in içinde  " <<IEDETmodel;

}
