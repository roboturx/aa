﻿#include "iedet.h"
//#include "ie.h"
#include "mw_main.h"

hC_IEDET::hC_IEDET(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İş Emri Detay Constructor";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IEDET::iedet_setup()
{

    qDebug() << " -iedet setup ";
    iedet_VTd();
    iedet_ui();

    IEDETmodel = new QSqlRelationalTableModel;
    iedet_model( IEDETmodel ) ;

    iedet_view();
    iedet_map();
    iedet_kntrl ();


    //  this->show ();

}








void hC_IEDET::iedet_ui()
{
    qDebug() << " -iedet_ui";
    lB_iedet  = new QLabel ("İŞ EMRİ DETAY");
    hC_IEDET::setWindowTitle (lB_iedet->text());
    hC_IEDET::setGeometry(610,310,600,300);
    //   hC_IEDET::showMaximized ();



    // ///////////////////////////////////////////////////////
    IEDETtview = new hC_Tv;

    // ///////////////////////////////////////////////////////
    QLabel *lB_ieno = new QLabel("İş Emri No");
    lE_IEno = new QLineEdit;
    lB_ieno->setBuddy(lE_IEno);

    QLabel *lB_acklm = new QLabel("Açıklama");
    lE_IEdetaciklama = new QLineEdit;
    lB_acklm->setBuddy(lE_IEdetaciklama);

    QLabel *lB_krm = new QLabel("Tamir Yeri");
    cbx_IEdettamiryeri = new QComboBox;
    QStringList tylist {"Atolye",
                        "Arazi",
                        "Yetkili Servis",
                        "Dış Servis"};
    cbx_IEdettamiryeri->addItems(tylist);
    lB_krm->setBuddy(cbx_IEdettamiryeri);

    QLabel *lB_tm = new QLabel("Atolye Bolüm");
    cbx_IEdettamirbolum = new QComboBox;
    QStringList ablist {" ",
                        "Boya",
                        "Kaporta",
                        "Motor",
                        "Torna",
                        "Mekanik"};
    cbx_IEdettamirbolum->addItems(ablist);
    lB_tm->setBuddy(cbx_IEdettamirbolum );

    QLabel *lB_dr = new QLabel("İş Durumu");
    cbx_IEdetdurum = new QComboBox;                    // dbtb_durum
    QStringList drlist { " ",
                         "Parça Bekliyor",
                         "Usta Bekliyor",
                         "Tamamlandı"};
    cbx_IEdetdurum->addItems(drlist);
    lB_dr->setBuddy(cbx_IEdetdurum);

    QLabel *lB_gt = new QLabel("Araç Giriş Tarihi");
    dE_IEdetgirtarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEdetgirtarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEdetgirtarihi->setMinimumDate(QDate(01, 01, 1900));
    dE_IEdetgirtarihi->setMaximumDate(QDate(valiDDate));
    dE_IEdetgirtarihi->setCalendarPopup(true);
    lB_gt->setBuddy(dE_IEdetgirtarihi);

    QLabel *lB_ct = new QLabel("Araç Çıkış Tarihi");
    dE_IEdetciktarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEdetciktarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEdetciktarihi->setMinimumDate(QDate (01, 01, 1900));
    dE_IEdetciktarihi->setMaximumDate(QDate ( valiDDate ));
    dE_IEdetciktarihi->setCalendarPopup(true);
    lB_ct->setBuddy(dE_IEdetciktarihi);
    // ///////////////////////////////////////////////////////
    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);


    auto IEDETwdlay = new QGridLayout;
    IEDETwdlay->addWidget(lB_acklm            ,1,0,1,1);
    IEDETwdlay->addWidget(lE_IEdetaciklama    ,1,1,1,3);
    IEDETwdlay->addWidget(lB_krm              ,2,0,1,1);
    IEDETwdlay->addWidget(cbx_IEdettamiryeri  ,2,1,1,3);
    IEDETwdlay->addWidget(lB_tm               ,3,0,1,1);
    IEDETwdlay->addWidget(cbx_IEdettamirbolum ,3,1,1,3);
    IEDETwdlay->addWidget(lB_dr               ,4,0,1,1);
    IEDETwdlay->addWidget(cbx_IEdetdurum      ,4,1,1,3);
    IEDETwdlay->addWidget(lB_gt               ,7,0,1,1);
    IEDETwdlay->addWidget(dE_IEdetgirtarihi   ,7,1,1,3);
    IEDETwdlay->addWidget(lB_ct        ,8,0,1,1);
    IEDETwdlay->addWidget(dE_IEdetciktarihi   ,8,1,1,3);

    IEDETwdlay->addWidget (new QLabel("Resim") , 9, 0, 1, 1);
    IEDETwdlay->addWidget (lB_rsm      , 9, 1, 1, 2);

    auto IEDETwdmap = new QWidget;
    IEDETwdmap->setLayout(IEDETwdlay);

    auto *IEDETmainLay = new QGridLayout(this);
    IEDETmainLay->addWidget ( IEDETtview ,  0, 0, 1, 1 );
    IEDETmainLay->addWidget ( IEDETwdmap  ,  0, 1, 1, 1 );


}



void hC_IEDET::iedet_view()
{
    qDebug()<<" -iedet view ";
    IEDETtview->table->setModel(IEDETmodel);
    IEDETselectionMdl = IEDETtview->table->selectionModel();
    //// kullanıcı bu alanları görmesin
    IEDETtview->table->setColumnHidden(
                IEDETmodel->fieldIndex("iedet_ie_id"), true);
    IEDETtview->table->setColumnHidden(
                IEDETmodel->fieldIndex("iedet_iedet_no"), true);

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
                IEDETmodel->index(0, 1)
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
    ienoo = new QString;
    ie->ie_setup();
    ie->show();
    // /// 12- set filter

    connect(ie, &hC_IE::sgn,
            [this ] (QString ie_ieno)
    {
        *ienoo = ie_ieno;
        IEDETmodel->setFilter(
                    QString("iedet_ie_id = %1").arg(ie_ieno) );
    });
    //////////////////////////////////////////////
qDebug () <<"iedet ienoooowwwww " << *ienoo  ;
    // pB 001 yeni ekle
    connect(IEDETtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

            qDebug () <<"ie mwwwwwwwww sgn :"<<*ienoo  ;


            QSqlQuery q;
            QString q_s;
            q_s="INSERT INTO iedet__dbtb ( "
                "iedet_ie_id, iedet_iedet_no, iedet_girtar "
                " )"
                " values( ?, ?, ? )";
            q.prepare(q_s);

            q.bindValue(0, *ienoo  );
            q.bindValue(1, "1" );
            q.bindValue(2, "2" ); //QDate(QDate::currentDate()).toString());
            // q.bindValue(3, dE_IEdetciktarihi->text());

            q.exec();

            if (q.isActive())
            {
                qDebug () <<"İş Emri Detay Yeni Kayıt Eklendi - ";
            }
            else
            {
                qDebug () << "İş Emri Detay Yeni Kayıt Eklenemedi - "
                          << q.lastError().text();
            }




            IEDETmodel->select();
            IEDETtview->table->setFocus();

            // iş emri detay ekle
            ///////////////////////////////////////////////////


    });
    // pB 002 yeni resim ekle
    connect(IEDETtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(lB_rsm, IEDETtview, IEDETmodel, IEDETselectionMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  IEDETselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, IEDETtview, IEDETmodel, IEDETselectionMdl,
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

            s_qry = QString("DELETE FROM dbtb_iedet "
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
    });

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

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  IEDETselectionMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  IEDETselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        IEDETmapper->setCurrentModelIndex(Index);
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

            mesaj = { "OK - VTd - İş Emri Detay" } ,
            IEDETtableName {"iedet__dbtb"};

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( IEDETtableName ))
    {



        ct = "CREATE TABLE IF NOT EXISTS " +IEDETtableName +
                "("
                "iedet_ie_id	    TEXT, "
                "iedet_iedet_no	TEXT, "
                "iedet_aciklama	TEXT, "
                "iedet_tamiryeri TEXT, "
                "iedet_tamirbölum TEXT, "
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




void hC_IEDET::iedet_model(QSqlRelationalTableModel* model)
{
    qDebug() << " -iedet mdl";
    QString indexField = "iedet_aciklama";
    QString tableName ("iedet__dbtb");
    QStringList *tB_FieldList = new QStringList ;

    tB_FieldList->append("İş Emri No");
    tB_FieldList->append("Detay no");
    tB_FieldList->append("Açıklama");
    tB_FieldList->append("Tamir Yeri");
    tB_FieldList->append("Tamir Bölüm");
    tB_FieldList->append("Durum");
    tB_FieldList->append("Giriş Tarihi");
    tB_FieldList->append("Çıkış Tarihi");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Detay ID");

    hC_Rm hC_Rm ( &tableName,
                  model,
                  &indexField ,
                  tB_FieldList) ;
    //    qDebug() <<"iedetmodel in içinde  " <<IEDETmodel;

}
