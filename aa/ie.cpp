#include "ie.h"

hC_IE::hC_IE(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İş Emri Constructor";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IE::ie_setup()
{
    qDebug() << " -ie setup ";

  // iedet_show()  ;

    ie_VTd();
    ie_ui();

    IEmodel = new QSqlRelationalTableModel;
    ie_model( IEmodel ) ;

    ie_view();
    ie_map();
    ie_kntrl ();



}


void hC_IE::ie_ui()
{
    qDebug() << " -ie_ui";
    lB_ie  = new QLabel ("İŞ EMRİ");
    hC_IE::setWindowTitle (lB_ie->text());
    hC_IE::setGeometry(20,20,
            qApp->screens()[0]->size ().rwidth (),
            qApp->screens()[0]->size ().rheight ()/4);
    //    hC_IE::showMaximized ();

qApp->beep ();

    // ///////////////////////////////////////////////////////
    IEtview = new hC_Tv();

    // ///////////////////////////////////////////////////////
    auto* lB_mk = new QLabel("Araç Kurum No");
    hClE_mkn = new hC_Le;

    auto* lB_ie = new QLabel("İş Emri No");
    lE_ieno = new  QLineEdit;
    lE_ieno->setReadOnly (true);

    auto *lB_get = new QLabel("Araç Geliş Tarihi");
    dE_geltar = new QDateTimeEdit();
    hC_Gz(dE_geltar,"nulldate");
    lB_get->setBuddy(dE_geltar);

    auto *lB_dr = new QLabel("Araç Durumu ");
    QStringList lst{ " ",
                     "Sıra Bekliyor",
                     "Bakıma Alındı",
                     "Tamamlandı"};
    cbX_durum = new QComboBox;
    cbX_durum->insertItems(0,lst);

    auto lB_git = new QLabel("Atölye Giriş Tarihi");
    dE_girtar = new QDateTimeEdit();
    hC_Gz(dE_girtar,"nulldate");
    lB_git->setBuddy(dE_girtar);

    auto lB_cit = new QLabel("Atölye Çıkış Tarihi");
    dE_ciktar = new QDateTimeEdit();
    hC_Gz(dE_ciktar,"nulldate");

    auto lB_y1 = new QLabel("Yetkili - I ");
    hClE_yetkili1 = new hC_Le;

    auto lB_y2 = new QLabel("Yetkili - II");
    hClE_yetkili2 = new hC_Le;

    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);

    // ///////////////////////////////////////////////////////
    auto IEwdlay = new QGridLayout;
    IEwdlay->addWidget (lB_ie   , 0,  0, 1, 4);
    IEwdlay->addWidget (lE_ieno , 0,  4, 1, 6);
    IEwdlay->addWidget (lB_mk   , 0, 10, 1, 4);
    IEwdlay->addWidget (hClE_mkn  , 0, 14, 1, 6);

    IEwdlay->addWidget (lB_get    , 1, 0, 1, 4);
    IEwdlay->addWidget (dE_geltar , 1, 4, 1, 6);
    IEwdlay->addWidget (lB_dr     , 2, 0, 1, 4);
    IEwdlay->addWidget (cbX_durum , 2, 4, 1, 6);
    IEwdlay->addWidget (lB_git    , 3, 0, 1, 4);
    IEwdlay->addWidget (dE_girtar , 3, 4, 1, 6);
    IEwdlay->addWidget (lB_cit     , 4, 0, 1, 4);
    IEwdlay->addWidget (dE_ciktar  , 4, 4, 1, 6);
    IEwdlay->addWidget (lB_y1       , 1, 10, 1, 4);
    IEwdlay->addWidget (hClE_yetkili1 , 1, 14, 1, 6);
    IEwdlay->addWidget (lB_y2       , 2, 10, 1, 4);
    IEwdlay->addWidget (hClE_yetkili2 , 2, 14, 1, 6);
    IEwdlay->addWidget (new QLabel("Resim") , 3, 10, 1, 4);
    IEwdlay->addWidget (lB_rsm      , 3, 14, 2, 6);

    auto IEwdmap = new QWidget;
    IEwdmap->setLayout (IEwdlay);

    auto *IEmainLay = new QGridLayout(this);
    IEmainLay->addWidget ( IEtview ,  0, 0, 1, 1 );
    IEmainLay->addWidget ( IEwdmap  ,  0, 1, 1, 1 );

}
/*
void hC_IE::iedet_show()
{
    qDebug() << " * ie --> iedet_ui";
    iedet = new hC_IEDET;
    iedet->iedet_setup();
    iedet->show ();
}*/

void hC_IE::ie_view()
{
    qDebug()<<" -ie view ";
    IEtview->table->setModel(IEmodel);
    IEselectionMdl = IEtview->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    IEtview->table->setColumnHidden(IEmodel->
                                    fieldIndex("ie_mkn_id"), true);
    //   IEtview->table->setColumnHidden(IEmodel->
    //           fieldIndex("ie_ie_no"), true);
    qDebug()<<" -ietview "<< endl <<IEtview << endl;
    IEtview->table->setColumnHidden(IEmodel->
                                    fieldIndex("ie_resim"), true);
    IEtview->table->setColumnHidden(IEmodel->
                                    fieldIndex("id_ie"), true);

    IEtview->table->setCurrentIndex(
                IEmodel->index(1, 1)
                );
    // with blue rect
    IEtview->table->setFocus();
}


void hC_IE::ie_map()
{

    qDebug()<<" -ie map ";


    /// mapper IE
    IEmapper = new QDataWidgetMapper(this);
    IEmapper->setModel(IEmodel);

    IEmapper->addMapping (hClE_mkn->lineEdit , IEmodel->fieldIndex("ie_mkn_id"));
    IEmapper->addMapping (lE_ieno , IEmodel->fieldIndex("ie_ie_no"));
    IEmapper->addMapping (dE_geltar, IEmodel->fieldIndex("ie_tarih"));
    IEmapper->addMapping (cbX_durum , IEmodel->fieldIndex("ie_durum"));
    IEmapper->addMapping (dE_girtar , IEmodel->fieldIndex("ie_girtar"));
    IEmapper->addMapping (dE_ciktar , IEmodel->fieldIndex("ie_ciktar"));
    IEmapper->addMapping (hClE_yetkili1->lineEdit , IEmodel->fieldIndex("ie_yetkili1"));
    IEmapper->addMapping (hClE_yetkili2->lineEdit , IEmodel->fieldIndex("ie_yetkili2"));
    //IEmapper->addMapping (lE_    , IEmodel->fieldIndex("ie_resim"));
    IEmodel->select();

    IEmapper->toFirst ();
}



void hC_IE::ie_kntrl()
{

    qDebug()<<" -ie kntrl";

    // pB 001 yeni ekle
    connect(IEtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QString IEtableName{"ie__dbtb"};
        QSqlQuery q;
        QString qry, mesaj("İŞ EMRİ NO MAX VALUE -");

        /// yeni iş emri numaasını bul
        /// iş emri nosu ie__dbtb de
        /// ie_ie_no alanındaki en büyük sayı
        qry = "SELECT max(ie_ie_no) FROM " + IEtableName  ;
        int ieieno;
        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "İş Emri No bulunmadı \n"+
                    "------------------------------------\n"+
                    q.lastError().text ()+
                    "------------------------------------\n";
            return;
        }
        else
        {
            q.next();
            ieieno = q.value(0).toInt ();
            mesaj = mesaj + "MAX VAL =" + QString::number(ieieno) ;
        }

        qDebug()<< mesaj <<endl << endl << "last inserted id  : "
                << q.lastInsertId ().toString ();
          //  IEmodel->select();


        ieieno = ieieno + 1  ;
        // yeni kaydı ekle
        qry = "INSERT INTO " + IEtableName + " ( "
                    "ie_ie_no, "
                    "ie_durum"
                                             ")"

                    " values( "
                        "'"+QString::number(ieieno)+"' , "
                        "' '"
                                ")" ;

        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "<br>İLK İş Emri Eklenemedi"+
                    "<br>------------------------------------<br>"+
                    q.lastError().text ()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = mesaj + "<br>İLK İş Emri eklendi.";

            hClE_mkn->lineEdit->setText ("");
            hC_Gz (dE_geltar , "nulldate");
            hC_Gz (dE_girtar , "nulldate");
            hC_Gz (dE_ciktar , "nulldate");
            cbX_durum->setCurrentIndex (0);
            hClE_yetkili1->lineEdit->setText ("");
            hClE_yetkili2->lineEdit->setText ("");

       // QLineEdit f;



        }
        IEmodel->select();
        ////////////////////////////////////////////////
        hC_Nr (IEtview, ieieno, 0);
        ////////////////////////////////////////////////
        IEtview->table->setFocus ();
        // iş emri detay ekle

    });

    // pB 002 yeni resim ekle
    connect(IEtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(lB_rsm, IEtview, IEmodel, IEselectionMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  IEselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, IEtview, IEmodel, IEselectionMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(IEtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // ie  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("İŞ EMRİNİ SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "İş emrini silerseniz;\n"
                       "bu İş Emri bağlı (iş emri detay, taşınır ve işçilik)\n "
                       "tüm kayıtlarda silinir\n "
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            /// önce bu iş emrine bağlı
            /// iedet
            /// iedet kayıtlarına bağlı
            /// taşınır
            /// işçilik kayıtlarını silelim



            // şimdi iş emrini silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex ie_indx = IEtview->table->currentIndex ();

            // iedet sil
            QString ieieno = IEmodel->data
                    (IEmodel->index
                     (ie_indx.row (),
                      IEmodel->fieldIndex ("ie_ie_no"))).toString ();

            s_qry = QString("DELETE FROM iedet__dbtb "
                            "WHERE iedet_ie_id = %1").arg( ieieno );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Detay Kaydı Silindi ";
                IEmodel->submitAll ();
                IEmodel->select ();
            }
            else
            {

                qDebug()<< " HATA - İş Emri Detay Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
            // ie sil
            QString idie = IEmodel->data
                    (IEmodel->index
                     (ie_indx.row (),
                      IEmodel->fieldIndex ("id_IE"))).toString ();


            s_qry = QString("DELETE FROM ie__dbtb "
                            "WHERE id_IE = %1").arg( idie );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Kaydı Silindi ";
                IEmodel->submitAll ();
                IEmodel->select ();
            }
            else
            {

                qDebug()<< " HATA - İş Emri Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
        }
        else if (msgBox.clickedButton() == pb_vzg)
        {
            msgBox.close(); // abort
        }

    });

    // pB 006 ilk
    connect(IEtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        IEtview->hC_TvPb ("ilk", IEmodel, IEmapper);
    });

    // pB 007 önceki
    connect(IEtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        IEtview->hC_TvPb ("ncki", IEmodel, IEmapper);
    });

    // pB 008 sonraki
    connect(IEtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        IEtview->hC_TvPb ("snrki", IEmodel, IEmapper);
    });

    // pB 009 son
    connect(IEtview->pB_son, &QPushButton::clicked,
            [this]()
    {IEtview->hC_TvPb ("son", IEmodel, IEmapper);
    });



    // pB 010 nav tuslari kontrol
    connect(IEmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {IEtview->hC_TvPb ("yenile", IEmodel, IEmapper);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  IEselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        IEmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 setfilter
        // 011-02 filtrele

        /// iş emri no her yılbaşında birden başlar


        QString ie_ie_no = IEmodel->data
                (IEmodel->index
                 (Index.row (),
                  IEmodel->fieldIndex ("ie_ie_no"))).toString ();

        // 011-03 ie de row değiştiğinde ie noyu ismini etrafa yayınlayalım
        emit hC_IE::sgn ( IEtview->table->model()->
                          index( Index.row() ,
                                 IEmodel->fieldIndex ("ie_ie_no")
                                 ).data().toString() );

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  IEselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        IEmapper->setCurrentModelIndex(Index);
    });

    // --- 013-01 iş durumuna göre tarihleri gizle
    connect(  cbX_durum , &QComboBox::currentTextChanged,
                [this]( QString text )
    {
        if (text == " ")
        {
            hC_Gz ( dE_geltar, "0" );
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );



        }
        else if (text == "Sıra Bekliyor")
        {
            hC_Gz ( dE_geltar, "1" );
          //  dE_geltar->setFocusPolicy (Qt::StrongFocus);
          //  dE_geltar->setFocus () ;
            //cbX_durum->setFocus ();
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Bakıma Alındı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            //dE_girtar->setFocus () ;
          //  cbX_durum->setFocus ();
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Tamamlandı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "1" );
         //   dE_ciktar->setFocus () ;
           // cbX_durum->setFocus ();

        }
    });





    qDebug()<<"ie kontrol sonu ";
}








hC_IE::~hC_IE()
= default;


QString hC_IE::ie_VTd ()
{
    QSqlQuery q;
    QString ct, mesaj = "OK - VTd - İş Emri";
    QString IEtableName ("ie__dbtb");
    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( IEtableName))
    {
        ct ="CREATE TABLE IF NOT EXISTS "+ IEtableName +
                "("
                "ie_mkn_id        INTEGER, "
                "ie_ie_no         INTEGER, "
                "ie_tarih         TEXT, "
                "ie_durum         TEXT, "
                "ie_girtar        TEXT, "
                "ie_ciktar        TEXT, "
                "ie_yetkili1      TEXT, "
                "ie_yetkili2      TEXT, "
                "ie_resim         BLOB, "
                "id_IE INTEGER primary key  )"  ;




        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - İş Emri Dosyası Oluşturulamadı  "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - İşEmri Dosyası YENİ Oluşturuldu ";
            QString qry;
            qry = "INSERT INTO " + IEtableName + " ( ie_mkn_id )"
                                                 " values( 1 )"  ;

            if ( !q.exec(qry) )
            {
                mesaj = mesaj + "<br>İLK İş Emri Eklenemedi"+
                        "<br>------------------------------------<br>"+
                        q.lastError().text ()+
                        "<br>------------------------------------<br>";
            }
            else
            {
                mesaj = mesaj + "<br>İLK İş Emri eklendi.";
            }

        }
    }
    qDebug ()<< mesaj;
    return mesaj ;

}

void hC_IE::ie_model(QSqlRelationalTableModel *model)
{
    qDebug() << " -ie mdl";
    QString IEtableName = "ie__dbtb";
    QString indexField = "ie_----------soyad";
    auto *fieldList = new QStringList;

    fieldList->append("Mkn No");
    fieldList->append("İş Emri No");
    fieldList->append("Tarihi");
    fieldList->append("Durum");
    fieldList->append("Giriş Tarihi");
    fieldList->append("Çıkış Tarihi");
    fieldList->append("Yetkili");
    fieldList->append("Yetkili");
    fieldList->append("Resim");
    fieldList->append("ID_IE");


    hC_Rm hC_Rm ( &IEtableName,
                  model,
                  &indexField ,
                  fieldList) ;

} /// İŞ EMRİ
