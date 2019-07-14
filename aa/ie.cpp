#include "ie.h"
#include "mkn.h"

hC_IE::hC_IE(QWidget *parent) : QWidget (parent)
{
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
    qDebug() << "Ie Cnstrctr   ";
}

void hC_IE::setup()
{
    qDebug() << "  ie setup ";

    wdgt  () ;

    ui    () ;

    kntrl () ;
}


void hC_IE::ui()
{
    qDebug() << "  ui";
    ////////////////////////////////////////// window
    win_Label  = new QLabel ("İŞ EMRİ");
    hC_IE::setWindowTitle (win_Label->text());
    hC_IE::setGeometry(20,20,
                       qApp->screens()[0]->size ().rwidth (),
            qApp->screens()[0]->size ().rheight ()/4);


    /////////////////////////////////////////// tview
    tb_view = new hC_Tv( this, tb_model, tb_mapper, win_Wdgt );

    ///////////////
    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget ( tb_view ,  0, 0, 1, 1 );
    winGrid->addWidget ( win_Wdgt  ,  0, 1, 1, 1 );

}

void hC_IE::wdgt ()
{
    qDebug () << "  wdgt";
    /////////////////////////////
    auto* lB_mk = new QLabel("Araç Kurum No");
    hClE_mkn = new hC_Le;
    hClE_mkn->lineEdit->setReadOnly (true);

    connect(hClE_mkn->pushButton2 , &QPushButton::clicked,
            [this ]()
    {
        hClE_mkn->lineEdit->clear () ;
    });
    connect(hClE_mkn->pushButton , &QPushButton::clicked,
            [this ]()
    {
        // mkn seçebilmek için pencere
        auto *dia = new QDialog();
        dia->setModal (true);
        dia->setGeometry ( 50, 400, 900, 200 );
        dia->setWindowTitle ( "Araç Seçimi" );

        auto *mkn = new hC_MKN ;
        mkn->setup ();
        // ----------------------------------------------------
        // tableviewinde gezinirken
        // mkn
        // signal ediliyor onu yakalayalım
        // seçim yapılan textedit e aktaralım
        // ----------------------------------------------------
        connect (mkn , &hC_MKN::sgnMkn ,
                 [ this ] ( QString sgnText )
        {
            hClE_mkn->lineEdit->setText ( sgnText );
            hClE_mkn->lineEdit->setFocus();
        });
        ////////////////////////////////////////////************
        auto *layout = new QGridLayout;
        dia->setLayout (layout);
        layout->addWidget (mkn  ,0 ,0 );
        dia->exec ();
    });



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

    win_Rsm = new QLabel ("Resim");
    hC_Rs resim(win_Rsm);

    //////////////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,100,300);
    auto wdgtGrid = new QGridLayout;
    win_Wdgt->setLayout (wdgtGrid);

    wdgtGrid->addWidget (lB_ie   , 0,  0, 1, 4);
    wdgtGrid->addWidget (lE_ieno , 0,  4, 1, 6);
    wdgtGrid->addWidget (lB_mk   , 0, 10, 1, 4);
    wdgtGrid->addWidget (hClE_mkn  , 0, 14, 1, 6);

    wdgtGrid->addWidget (lB_get    , 1, 0, 1, 4);
    wdgtGrid->addWidget (dE_geltar , 1, 4, 1, 6);
    wdgtGrid->addWidget (lB_dr     , 2, 0, 1, 4);
    wdgtGrid->addWidget (cbX_durum , 2, 4, 1, 6);
    wdgtGrid->addWidget (lB_git    , 3, 0, 1, 4);
    wdgtGrid->addWidget (dE_girtar , 3, 4, 1, 6);
    wdgtGrid->addWidget (lB_cit     , 4, 0, 1, 4);
    wdgtGrid->addWidget (dE_ciktar  , 4, 4, 1, 6);
    wdgtGrid->addWidget (lB_y1       , 1, 10, 1, 4);
    wdgtGrid->addWidget (hClE_yetkili1 , 1, 14, 1, 6);
    wdgtGrid->addWidget (lB_y2       , 2, 10, 1, 4);
    wdgtGrid->addWidget (hClE_yetkili2 , 2, 14, 1, 6);
    wdgtGrid->addWidget (new QLabel("Resim") , 3, 10, 1, 4);
    wdgtGrid->addWidget (win_Rsm      , 3, 14, 2, 6);


}
/*
void hC_IE::view()
{
    qDebug()<<"  ie view ";
    tb_view->table->setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel();

    //////////////////////////////////////////////////////////
    //// kullanıcı bu alanları görmesin
    tb_view->table->setColumnHidden(tb_model->
                                    fieldIndex("mkn_id"), true);
    //   tb_view->table->setColumnHidden(tb_model->
    //           fieldIndex("no"), true);
    tb_view->table->setColumnHidden(tb_model->
                                    fieldIndex("resim"), true);
    tb_view->table->setColumnHidden(tb_model->
                                    fieldIndex("id_ie"), true);
    //////////////////////////////////////////////////////////
    // with blue rect
    tb_view->table->setCurrentIndex(
                tb_model->index(1, 1) );
    tb_view->table->setFocus();
}


void hC_IE::map()
{

    qDebug()<<"  ie map ";

    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    tb_mapper->addMapping (hClE_mkn->lineEdit , tb_model->fieldIndex("mkn_id"));
    tb_mapper->addMapping (lE_ieno , tb_model->fieldIndex("no"));
    tb_mapper->addMapping (dE_geltar, tb_model->fieldIndex("tarih"));
    tb_mapper->addMapping (cbX_durum , tb_model->fieldIndex("durum"));
    tb_mapper->addMapping (dE_girtar , tb_model->fieldIndex("girtar"));
    tb_mapper->addMapping (dE_ciktar , tb_model->fieldIndex("ciktar"));
    tb_mapper->addMapping (hClE_yetkili1->lineEdit , tb_model->fieldIndex("yetkili1"));
    tb_mapper->addMapping (hClE_yetkili2->lineEdit , tb_model->fieldIndex("yetkili2"));
    //tb_mapper->addMapping (lE_    , tb_model->fieldIndex("resim"));

    tb_mapper->toFirst ();
}


*/
void hC_IE::kntrl()
{

    qDebug()<<"  ie kntrl";

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QString IEtableName{"_dbtb"};
        QSqlQuery q;
        QString qry, mesaj("");

        /// yeni iş emri numaasını bul
        /// iş emri nosu _dbtb de
        /// no alanındaki en büyük sayı
        qry = "SELECT max(no) FROM " + IEtableName  ;
        int ieieno;
        if ( !q.exec(qry) )
        {
            mesaj = mesaj + "İş Emri No bulunamadı \n"+
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

        qDebug()<< endl << "last inserted id  : "
                << q.lastInsertId ().toString ();
        //  tb_model->select();


        ieieno = ieieno + 1  ;
        // yeni kaydı ekle
        qry = "INSERT INTO " + IEtableName + " ( "
                                             "no, "
                                             "durum"
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
            cbX_durum->setCurrentText (" ");
            hClE_yetkili1->lineEdit->setText ("");
            hClE_yetkili2->lineEdit->setText ("");

            // QLineEdit f;



        }
        tb_model->select();
        ////////////////////////////////////////////////
        hC_Nr (tb_view, ieieno, 1);
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
            QModelIndex indx = tb_view->table->currentIndex ();

            // iedet sil
            QString ieieno = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("no"))).toString ();

            s_qry = QString("DELETE FROM iedet__dbtb "
                            "WHERE iedet_id = %1").arg( ieieno );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Detay Kaydı Silindi ";
                tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - İş Emri Detay Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
            // ie sil
            QString idie = tb_model->data
                    (tb_model->index
                     (indx.row (),
                      tb_model->fieldIndex ("id_IE"))).toString ();


            s_qry = QString("DELETE FROM _dbtb "
                            "WHERE id_IE = %1").arg( idie );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " İş Emri Kaydı Silindi ";
                tb_model->submitAll ();
                tb_model->select ();
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
/*
    // pB 006 ilk
    connect(tb_view->pB_ilk, &QPushButton::clicked ,
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
        // 011-02 setfilter
        // 011-02 filtrele

        /// iş emri no her yılbaşında birden başlar


        /*       int no = tb_model->data
                (tb_model->index
                 (Index.row (),
                  tb_model->fieldIndex ("no"))).toInt ();
*/
        // 011-03 ie de row değiştiğinde ie noyu ismini etrafa yayınlayalım
        emit hC_IE::sgnIsEmri ( tb_view->table->model()->
                          index( Index.row() ,
                                 tb_model->fieldIndex ("no")
                                 ).data().toInt() );

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
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
            hC_Gz ( dE_girtar, "0" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Bakıma Alındı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "0" );
        }
        else if (text == "Tamamlandı")
        {
            hC_Gz ( dE_geltar, "1" );
            hC_Gz ( dE_girtar, "1" );
            hC_Gz ( dE_ciktar, "1" );
        }
    });





    qDebug()<<"ie kontrol sonu ";
}








hC_IE::~hC_IE()
= default;

/*
QString hC_IE::VTd ()
{
    QSqlQuery q;
    QString ct, mesaj = "  OK - VTd - İş Emri";
    QString IEtableName ("_dbtb");
    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( IEtableName))
    {
        ct ="CREATE TABLE IF NOT EXISTS "+ IEtableName +
                "("
                "mkn_id        INTEGER, "
                "no         INTEGER, "
                "tarih         TEXT, "
                "durum         TEXT, "
                "girtar        TEXT, "
                "ciktar        TEXT, "
                "yetkili1      TEXT, "
                "yetkili2      TEXT, "
                "resim         BLOB, "
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
            qry = "INSERT INTO " + IEtableName + " ( mkn_id )"
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

void hC_IE::model()
{
    qDebug() << " -ie mdl";
    QString IEtableName = "_dbtb";
    QString indexField = "----------soyad";
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

    tb_model = new QSqlRelationalTableModel;
   hC_Rm hC_Rm ( &IEtableName,
                  tb_model,
                  &indexField ,
                  fieldList) ;

} /// İŞ EMRİ
*/
