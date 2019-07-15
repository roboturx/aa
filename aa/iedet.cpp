#include "iedet.h"


hC_IEDET::hC_IEDET(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"Cnstrctr İş Emri Detay";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IEDET:: setup()
{

    qDebug() << "  iedet setup ";

     wdgt  () ;

     ui    () ;

     kntrl () ;
}


void hC_IEDET:: ui()
{
    qDebug() << "   ui";
    win_Label  = new QLabel ("İŞ EMRİ DETAY");
    hC_IEDET::setWindowTitle (win_Label->text());
    hC_IEDET::setGeometry(10,
                          qApp->screens()[0]->size ().rwidth ()/2,
            600,300);
    //   hC_IEDET::showMaximized ();



    // ///////////////////////////////////////////////////////
    tb_view = new hC_Tv (tb_model, tb_mapper, win_Wdgt);

    // ///////////////////////////////////////////////////////

    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget ( tb_view ,  0, 0, 1, 1 );
    winGrid->addWidget ( win_Wdgt  ,  0, 1, 1, 1 );
}

void hC_IEDET:: wdgt ()
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
    win_Rsm = new QLabel ("Resim");
    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
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

    wdgtGrid->addWidget (new QLabel("Resim") , 9, 0, 1, 1);
    wdgtGrid->addWidget (win_Rsm      , 9, 1, 1, 2);

}


/*
void hC_IEDET:: view()
{
    qDebug()<<" -iedet view ";
    tb_view->table->setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel();
    //// kullanıcı bu alanları görmesin
    // tb_view->table->setColumnHidden(
    //           tb_model->fieldIndex(" ie_id"), true);
    // tb_view->table->setColumnHidden(
    //           tb_model->fieldIndex("  no"), true);

    tb_view->table->setColumnHidden(
                tb_model->fieldIndex(" resim"), true);

    //tb_view->table->setColumnHidden(
    //          tb_model->fieldIndex("  no"), true);
    tb_view->table->setColumnHidden(
                tb_model->fieldIndex("id_IEdet"), true);

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    tb_view->table->setCurrentIndex(
                tb_model->index(1, 2)
                );
    // with blue rect
    tb_view->table->setFocus();
    //   QTimer::singleShot(0, tb_view->table, SLOT(setFocus()));
}
void hC_IEDET:: map()
{
    qDebug()<<" -iedet map";
    /// mapper IEdet
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);


    tb_mapper->addMapping(lE_IEno , tb_model->
                            fieldIndex(" ie_id"));
    tb_mapper->addMapping(lE_IEdetaciklama , tb_model->
                            fieldIndex(" aciklama"));
    tb_mapper->addMapping(cbx_IEdettamiryeri , tb_model->
                            fieldIndex(" tamiryeri"));
    tb_mapper->addMapping(cbx_IEdettamirbolum , tb_model->
                            fieldIndex(" tamirbolum"));
    tb_mapper->addMapping(cbx_IEdetdurum, tb_model->
                            fieldIndex(" durum"));
    tb_mapper->addMapping(dE_IEdetgirtarihi , tb_model->
                            fieldIndex(" girtar"));
    tb_mapper->addMapping(dE_IEdetciktarihi , tb_model->
                            fieldIndex(" ciktar"));


    tb_mapper->toFirst ();
}

*/
void hC_IEDET:: kntrl()
{


    qDebug()<<" -iedet kntrl ";

    /////////////////////////////////////////////////////
    ie = new hC_IE;
    ienoo = new int;
    ie->setup();
    ie->show();
    // /// 12- set filter

    connect(ie, &hC_IE::sgnIsEmri ,
            [this ] (int ie_ieno)
    {
        *ienoo = ie_ieno;
        tb_model->setFilter(
                    QString(" ie_id = %1").arg(ie_ieno) );
    });
    //////////////////////////////////////////////

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QString IEtableName{" _dbtb"};
        QSqlQuery q;
        QString qry, mesaj("");

        /// yeni iş emri detay numaasını bul
        /// iş emri detay nosu  _dbtb de
        ///   no alanındaki en büyük sayı
        qry = "SELECT max(  no) FROM " + IEtableName  ;
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
        q_s="INSERT INTO  _dbtb ( "
            " ie_id     , "
            "  no  , "
            " tamiryeri , "
            " tamirbolum, "
            " durum     , "
            " girtar    , "
            " ciktar      "
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
        tb_model->select ();
        ////////////////////////////////////////////////
        hC_Nr (tb_view, iedetno, 1);
        ////////////////////////////////////////////////
        tb_view->table->setFocus ();
        // iş emri detay ekle
    });
    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tb_slctnMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
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
        /*     tb_slctnMdl->setCurrentIndex (
                    tb_model->index (q.lastInsertId ().toInt () , 3 ) ,
                    QItemSelectionModel::ClearAndSelect
                    );
*/
        tb_view->table->setFocus ();

    });
/*
    // pB 006 ilk
    connect(tb_view->pB_ilk, &win_Wdgt::clicked ,
            [this]()
    {
        tb_view->hC_TvPb ("ilk", tb_model, tb_mapper);
    });

    // pB 007 önceki
    connect(tb_view->pB_ncki, &win_Wdgt::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("ncki", tb_model, tb_mapper);
    });

    // pB 008 sonraki
    connect(tb_view->pB_snrki, &win_Wdgt::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("snrki", tb_model, tb_mapper);
    });

    // pB 009 son
    connect(tb_view->pB_son, &win_Wdgt::clicked,
            [this]()
    {tb_view->hC_TvPb ("son", tb_model, tb_mapper);
    });



    // pB 010 nav tuslari kontrol
    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);

    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  tb_slctnMdl ,
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



//void hC_IEDET::rowChanged_IEDET(QModelIndex IEDETindex)
//{

//    //QModelIndex index = tb_view->table->currentIndex();
//    if (IEDETindex.isValid())
//    {
//        QSqlRecord record = tb_model->record(IEDETindex.row());
//        QString ieno = record.value("id_iedet").toString() ;
//        ///setfiltr to tasinir and iscilik
//        TSmodel->setFilter (QString("ts_ id = '%1'" ).arg(ieno));
//        TSmodel->select();
//         TStview->setFocus();
//        SCmodel->setFilter (QString("sc_ id = '%1'" ).arg(ieno));
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
//    //tb_model->select();
//    TStview->setFocus();
//    SCtview->setFocus();
//    tb_model->select();


//    //qDebug () <<"iedet row changggggedd 3";
//*/
//     tb_view->table->setFocus();
//
//}




hC_IEDET::~hC_IEDET()
= default;

/*
QString hC_IEDET:: VTd ()
{
    QSqlQuery q;
    QString ct,

            mesaj = { "  OK - VTd - İş Emri Detay" } ,
            IEDETtableName {" _dbtb"};

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( IEDETtableName ))
    {



        ct = "CREATE TABLE IF NOT EXISTS " +IEDETtableName +
                "("
                " ie_id	    TEXT, "
                "  no	INTEGER, "
                " aciklama	TEXT, "
                " tamiryeri TEXT, "
                " tamirbolum TEXT, "
                " durum     TEXT, "
                " girtar    TEXT, "
                " ciktar    TEXT, "
                " resim     BLOB, "
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
                                                        " (  ie_id ) values( 1 )"  ;

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




void hC_IEDET:: model()
{
    qDebug() << "  iedet mdl";
    QString indexField = " aciklama";
    QString tableName (" _dbtb");
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

    tb_model = new QSqlRelationalTableModel;
    hC_Rm hC_Rm ( &tableName,
                  tb_model,
                  &indexField ,
                  tB_FieldList) ;

    //    qDebug() <<"tb_model in içinde  " <<tb_model;

}
*/
