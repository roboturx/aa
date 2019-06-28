#include "ie.h"




hC_IE::hC_IE(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İş Emri Constructor";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IE::ie_setup()
{
    qDebug() << "ie setup ";
    ie_VTd();
    ie_ui();
    iedet_ui();

    IEmodel = new QSqlRelationalTableModel;
    ie_model( IEmodel ) ;

    ie_view();
    ie_map();
    ie_kntrl ();

}


void hC_IE::ie_ui()
{


    qDebug() << "ie_ui";
    lB_ie  = new QLabel ("İŞ EMRİ");
    hC_IE::setWindowTitle (lB_ie->text());
    hC_IE::showMaximized ();


    // ///////////////////////////////////////////////////////

    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);

    // ///////////////////////////////////////////////////////
    // views
    IEtview = new hC_Tv();

    /////*******************************************////////

    auto* lB_mk = new QLabel("Araç");
    lE_mkn = new hC_Le;
    auto* lB_ie = new QLabel("İş Emri No");
    lE_ieno = new  QLineEdit;
    auto* lB_tr = new QLabel("Geliş Tarihi");
    lE_geltar = new QLineEdit;


    auto *lB_dr = new QLabel("Bakım Yeri");
    QStringList lst{ "Sıra Bekliyor",
                     "Bakıma Alındı",
                     "Tamamlandı"};
    cbX_durum = new QComboBox;
    cbX_durum->insertItems(0,lst);

    auto lB_gt = new QLabel("Atölye Giriş Tarihi");
    lE_girtar = new QLineEdit;
    auto lB_ck = new QLabel("Atölye Çıkış Tarihi");
    lE_ciktar = new QLineEdit;
    auto lB_y1 = new QLabel("Yetkili - I ");
    lE_yetkili1 = new hC_Le;
    auto lB_y2 = new QLabel("Yetkili - II");
    lE_yetkili2 = new hC_Le;

    auto IEwdlay = new QGridLayout;
    IEwdlay->addWidget (lB_mk   , 0, 0, 1, 4);
    IEwdlay->addWidget (lE_mkn  , 0, 4, 1, 6);
    IEwdlay->addWidget (lB_ie   , 1, 0, 1, 4);
    IEwdlay->addWidget (lE_ieno , 1, 4, 1, 6);
    IEwdlay->addWidget (lB_tr     , 2, 0, 1, 4);
    IEwdlay->addWidget (lE_geltar , 2, 4, 1, 6);
    IEwdlay->addWidget (lB_dr     , 3, 0, 1, 4);
    IEwdlay->addWidget (cbX_durum , 3, 4, 1, 6);
    IEwdlay->addWidget (lB_gt     , 4, 0, 1, 4);
    IEwdlay->addWidget (lE_girtar , 4, 4, 1, 6);
    IEwdlay->addWidget (lB_ck     , 5, 0, 1, 4);
    IEwdlay->addWidget (lE_ciktar , 5, 4, 1, 6);
    IEwdlay->addWidget (lB_y1       , 6, 0, 1, 4);
    IEwdlay->addWidget (lE_yetkili1 , 6, 4, 1, 6);
    IEwdlay->addWidget (lB_y2       , 7, 0, 1, 4);
    IEwdlay->addWidget (lE_yetkili2 , 7, 4, 1, 6);
    IEwdlay->addWidget (lB_rsm      , 8, 4, 1, 6);




    auto IEwdmap = new QWidget;
    IEwdmap->setLayout (IEwdlay);

    auto *IEmainLay = new QGridLayout(this);
    IEmainLay->addWidget ( IEtview ,  0, 0, 1, 1 );
    IEmainLay->addWidget ( IEwdmap  ,  0, 1, 1, 1 );

}

void hC_IE::iedet_ui()
{
    hC_IEDET* iedet = new hC_IEDET;
    iedet->iedet_setup();
}

void hC_IE::ie_view()
{
    qDebug()<<"ie view ";
    IEtview->table->setModel(IEmodel);
    IEselectionMdl = IEtview->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    IEtview->table->setColumnHidden(IEmodel->fieldIndex("ie_mknstk_no"), true);
    IEtview->table->setColumnHidden(IEmodel->fieldIndex("id_IE"), true);
    IEtview->table->setColumnHidden(IEmodel->fieldIndex("ie_resim"), true);

    IEtview->table->setCurrentIndex(
                IEmodel->index(0, 1)
                );
    // with blue rect
    IEtview->table->setFocus();
}


void hC_IE::ie_map()
{
    /// mapper IE
    IEmapper = new QDataWidgetMapper(this);
    IEmapper->setModel(IEmodel);
    //IEmapper->addMapping (lE_isim , IEmodel->fieldIndex("ie_isim"));
    IEmodel->select();

}



void hC_IE::ie_kntrl()
{


    // pB 001 yeni ekle
    connect(IEtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = IEmodel->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        //  dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! IEmodel->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        IEmodel->select();

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
            QString ino = IEmodel->data
                    (IEmodel->index
                     (ie_indx.row (),
                      IEmodel->fieldIndex ("id_IE"))).toString ();

            s_qry = QString("DELETE FROM dbtb_IE "
                            "WHERE id_IE = %1").arg( ino );

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
        QSqlRecord record = IEmodel->record(Index.row ());
        QString ie_mkn_no = record.value("ie_ie_no").toString ();
        /// iş emri no her yılbaşında birden başlar

        iedet->IEDETmodel->setFilter(
                    QString("iedet_ie_id = %1").arg(ie_mkn_no) );

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



}








hC_IE::~hC_IE()
= default;


QString hC_IE::ie_VTd ()
{
    QSqlQuery q;
    QString ct, mesaj = "OK - İş Emri";
    QString IEtableName ("ie__dbtb");
    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( IEtableName))
    {
        ct ="CREATE TABLE IF NOT EXISTS "+ IEtableName +
                "("
                "ie_mkn_id        TEXT, "
                "ie_ie_no         TEXT, "
                "ie_tarih         TEXT, "
                "ie_durum         TEXT, "
                "ie_girtar        TEXT, "
                "ie_ciktar        TEXT, "
                "ie_yetkili1      TEXT, "
                "ie_yetkili2      TEXT, "
                "ie_resim         BLOB, "
                "id_IE integer primary key  )"  ;




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
    qDebug() << "ie mdl";
    QString IEtableName = "ie__dbtb";
    QString indexField = "ie_----------soyad";
    auto *fieldList = new QStringList;

    fieldList->append("İş Emri No");
    fieldList->append("İş Emri Tarihi");
    fieldList->append("Bölüm");
    fieldList->append("Durum");
    fieldList->append("Araç Giriş Tarihi");
    fieldList->append("Araç Çıkış Tarihi");
    fieldList->append("Yetkili");
    fieldList->append("Yetkili");
    hC_Rm hC_Rm ( &IEtableName,
                  model,
                  &indexField ,
                  fieldList) ;

} /// İŞ EMRİ
