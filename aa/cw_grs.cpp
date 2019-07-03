#include "cw_grs.h"
//#include "globals.h"

Cw_Grs::Cw_Grs(QWidget *parent) : QWidget(parent) //:
{
/*void ontV_spre_row_changed(QModelIndex);
    QMovie *movie = new QMovie(":/rsm/trb2.gif");
    QLabel *lbl_bayrak = new QLabel();
    lbl_bayrak->setMovie(movie);
lbl_bayrak->show ();
movie->start();*/

    /*QLabel *lb = new QLabel("Giriş Ekranı");
    QPushButton *pb = new QPushButton(" ");

    QHBoxLayout *hl= new QHBoxLayout;
    hl->addWidget(lb);
    hl->addWidget(pb);

    QGridLayout *gr= new QGridLayout;
    gr->addLayout(hl,0,0,1,4);


    this->setLayout(gr);*/

    Cw_Grs::setup_VTdGrs();
    cr_spre_ui();
    cr_spre_model();
    cr_spre_view();
    cr_spredet_model();
    cr_spredet_view();
    cr_spre_kontrol();

}

//////////////////////////////////////////////////////
/// \brief Cw_Grs::cr_spre_model
///
///     Sipariş Emri
///             model oluşturalım
///

void Cw_Grs::cr_spre_model()
{
    model_spre = new QSqlRelationalTableModel();
    model_spre->setTable("dbtb_spre");
    model_spre->setEditStrategy(QSqlTableModel::OnFieldChange);

    ////  kolon başlıkları
 /*   model_spre->setHeaderData(
                model_spre->fieldIndex("se_no"),
                Qt::Horizontal, tr("Sip.Emri No"));
    model_spre->setHeaderData(
                model_spre->fieldIndex("se_tarih"),
                Qt::Horizontal, tr("Tarihi"));
*/
    // Populate the model_mkstok
    if (!model_spre->select())
    {
        qDebug () << model_spre->lastError();
    }


}

//////////////////////////////////////////////////////
/// \brief Cw_Grs::cr_spre_view
///
///     Sipariş Emri
///        modeli view de gösterelim
///

void Cw_Grs::cr_spre_view()
{

    tV_spre->setModel(model_spre);
    tV_spre->setSelectionMode(QAbstractItemView::SingleSelection);
    tV_spre->setSelectionBehavior(QAbstractItemView::SelectRows);
    tV_spre->resizeColumnsToContents();
    tV_spre->resizeRowsToContents();
    tV_spre->setCurrentIndex(model_spre->index(0,0));

    //// kullanıcı bu alanları görmesin
 //   tV_spre->setColumnHidden(
 //         model_spre->fieldIndex("mknstk_no"), true);
 //   tV_spre->setColumnHidden(
  //        model_spre->fieldIndex("id_spre"), true);
    model_spre->select();

}

//////////////////////////////////////////////////////
/// \brief Cw_Grs::cr_spredet_model
///
///     Sipariş Emri detay
///         model oluşturalım
///



void Cw_Grs::cr_spredet_model()
{
    model_spreDet = new QSqlRelationalTableModel();
    model_spreDet->setTable("dbtb_spredet");
    model_spreDet->setEditStrategy(QSqlTableModel::OnFieldChange);

    // Populate the model_mkstok
    if (!model_spreDet->select())
    {
        qDebug () << model_spreDet->lastError();
    }


}
//////////////////////////////////////////////////////
/// \brief Cw_Grs::cr_spredet_view
///
///     Sipariş Emri detay
///         modeli view de gösterelim
///
void Cw_Grs::cr_spredet_view()
{
    tV_spredet->setModel(model_spreDet);
    tV_spredet->setSelectionMode(QAbstractItemView::SingleSelection);
    tV_spredet->setSelectionBehavior(QAbstractItemView::SelectItems);
    tV_spredet->resizeColumnsToContents();
    tV_spredet->resizeRowsToContents();
    tV_spredet->setCurrentIndex(model_spreDet->index(0,0));

    //// kullanıcı bu alanları görmesin
/*    tV_spredet->setColumnHidden(
          model_spreDet->fieldIndex("mknstk_no"), true);
    tV_spredet->setColumnHidden(
          model_spreDet->fieldIndex("id_spre"), true);
*/
    model_spreDet->select();

}


//////////////////////////////////////////////////////
/// \brief Cw_Grs::cr_spre_ui
///
///      ekranda bişeyler gösterelim
///


void Cw_Grs::cr_spre_ui()
{

    lbl_mkn = new QLabel("Makina İkmal");
    lbl_spre = new QLabel("Sipariş Emri");

    pb_ieo = new QPushButton("İş Emri Oluştur");
    pb_se_sil = new QPushButton("Sipariş Emri Sil");
    pb_se_yaz = new QPushButton("Sipariş Emri Yazdır");
    pb_se_ = new QPushButton("...");
    pb_sedet_ekle = new QPushButton("SE Detay Ekle");
    pb_sedet_sil = new QPushButton("SE Detay Sil");
    pb_sedet_ = new QPushButton("...");

//qDebug () << "hl1  ";
    auto *hL1 = new QHBoxLayout();
    hL1->addWidget(lbl_mkn);
    hL1->addStretch(2);
    hL1->addWidget(pb_ieo);

    hL1->addWidget(pb_sedet_ekle);
    hL1->addWidget(pb_se_);
    hL1->addWidget(pb_se_sil);
    hL1->addStretch(1);
    hL1->addWidget(pb_se_yaz);

//qDebug () << "hl2  ";
    auto *hL2 = new QHBoxLayout();
    hL2->addWidget(lbl_spre);
    hL2->addStretch(2);
    hL2->addWidget(pb_sedet_ekle);
    hL2->addWidget(pb_sedet_);
    hL2->addStretch(1);
    hL2->addWidget(pb_sedet_sil);
    hL2->addStretch(1);

    tV_spre = new QTableView();
    tV_spredet = new QTableView();
//qDebug () << "grid  ";
    auto *gL = new QGridLayout();
    gL->addLayout(hL1,        0, 0, 1, 1);
    gL->addWidget(tV_spre,    1, 0, 1, 1);
    gL->addLayout(hL2,        2, 0, 1, 1);
    gL->addWidget(tV_spredet, 3, 0, 1, 1);
this->setLayout (gL);
//qDebug () << "gridded ";
}



//////////////////////////////////////////////////////
/// \brief Cw_Grs::cr_spre_kontrol
///
///         Ekrandaki hareketleri kontrol edelim
///

void Cw_Grs::cr_spre_kontrol()
{

    /// sipariş emrine ait detayları filtreleyelim
    connect(tV_spre->selectionModel(),
        SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
        this, SLOT(ontV_spre_row_changed(QModelIndex)));

    /// Sipariş emrini iş emrine dönüştürelim
    connect( pb_ieo, &QPushButton::clicked,
             this, &Cw_Grs::onpb_is_emri_olustur );

    /// sipariş emri silelim
    connect( pb_se_sil, &QPushButton::clicked,
             this, &Cw_Grs::onpb_spreSil );

    /// sipariş emrini yazdıralım
    connect( pb_se_yaz, &QPushButton::clicked,
             this, &Cw_Grs::onpb_spreYaz );

    /// sipariş emrini mapper da gösterelim
    connect( pb_se_, &QPushButton::clicked,
             this, &Cw_Grs::onpb_spreEkleDDD );

    /// sipariş emrine detay ekleyelim
    connect( pb_sedet_ekle, &QPushButton::clicked,
             this, &Cw_Grs::onpb_spreDetayEkle );

    /// sipariş emri detayını silelim
    connect( pb_sedet_sil, &QPushButton::clicked,
             this, &Cw_Grs::onpb_spreDetaySil );

    /// sipariş emri detayını mapper da gösterelim
    connect( pb_sedet_, &QPushButton::clicked,
             this, &Cw_Grs::onpb_spreDetayEkleDDD );

}



////////////////////////// SLOTS

void Cw_Grs::ontV_spre_row_changed(QModelIndex)
{
    QModelIndex index = tV_spre->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = model_spre->record(index.row());
        int id = record.value("id_spre").toInt();

        QString xx = QString("spre_no = %1").arg(id);
        model_spreDet->setFilter(xx);


    }
    else
    {
        model_spreDet->setFilter("id_spreDet = -1");
    }
    model_spreDet->select();
    tV_spredet->setFocus();
    tV_spre->setFocus();
}






//void Cw_Grs::spreEkle()
//{

//}

void Cw_Grs::onpb_spreEkleDDD()
{
/*
    gridLayout = new QGridLayout(this);
    horizontalLayout = new QHBoxLayout();

    lbl_mkn =new QLabel;
    horizontalLayout->addWidget(lbl_mkn);
    pb_ieo = new QPushButton(this);
    pb_ieo->setText("Sipariş Emri Ekle");

    horizontalLayout->addWidget(pb_ieo);

    pb_se_sil = new QPushButton(this);
    pb_se_sil->setText("Sipariş Emri Sil");

    horizontalLayout->addWidget(pb_se_sil);
    horizontalLayout->addStretch(1);
    pb_se_yaz = new QPushButton(this);
    pb_se_yaz->setText("Sipariş Emri Yazdır");

    horizontalLayout->addWidget(pb_se_yaz);
    horizontalLayout->addStretch(3);
    gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);
*/
}

void Cw_Grs::onpb_spreDetayEkle()
{
    // sipariş emri kodunu alalım
    int id=-1;
    QModelIndex index = tV_spre->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = model_spre->record(index.row());
        id = record.value("id_spre").toInt();

    }
    // sipariş emri detay ekle
    QSqlQuery *q = new QSqlQuery;
    if (q->exec("INSERT INTO dbtb_spredet ( spre_no )"
                " values(" + QString::number( id) +   ")"   ))
        qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

    model_spreDet->submit();
    tV_spredet->setFocus();
    model_spreDet->select();





}

void Cw_Grs::onpb_spreDetayEkleDDD()
{

}

void Cw_Grs::onpb_is_emri_olustur()
{

}

void Cw_Grs::onpb_spreDetaySil()
{

}

void Cw_Grs::onpb_spreSil()
{

}

void Cw_Grs::onpb_spreYaz()
{

}
////////////////////////////////////////// DBASE

void Cw_Grs::setup_VTdGrs()
{

    if(VTKontrolEt::instance()->Connect())
    {
Cw_Grs::VTd_SIPARISEMRI ();
Cw_Grs::VTd_SIPARISEMRIDETAY ();

    }
    else
    {
        qDebug() << "VTd_mkn VT NOT Connected" ;
    }

}       /// setup_VTdGrs()


void Cw_Grs::VTd_SIPARISEMRI ()
{
    ///  SIPARISEMRI create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_spre"))
    {
        ct = "CREATE TABLE IF NOT EXISTS dbtb_spre "
             "("
             "mknstk_no     INTEGER, "
             "se_no         TEXT, "
             "se_tarih      TEXT, "
             "isemri_no     TEXT, "
             "se_aitoldyer	TEXT, "
             "se_sekli      TEXT, "
             "se_yetkili1   TEXT,"
             "se_yetkili2   TEXT,"
             "se_teslimtarihi    TEXT,"
             "se_eki        TEXT, "
             "byer          TEXT, "
             "resim         BLOB, "
             "id_spre integer primary key )"  ;


        if (!q.exec( ct ))
        {
            qDebug() << " SIPARISEMRI Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " SIPARISEMRI Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_spre ( mknstk_no )"
                   " values( 1 )"  );
        }
    }


}


void Cw_Grs::VTd_SIPARISEMRIDETAY ()
{
    ///  SIPARISEMRI DETAY create
    ///

    QString ct;
    QSqlQuery q;
    if ( ! VTKontrolEt::instance()->GetDB().tables().contains( "dbtb_spredet"))
    {
        ct ="CREATE TABLE IF NOT EXISTS dbtb_spredet "
            "("
            "spre_no	INTEGER, "
            "aciklama	TEXT, "
            "resim     BLOB, "
            "id_spredet integer primary key)"  ;

        if (!q.exec( ct ))
        {
            qDebug() << " SIPARISEMRI DETAY Dosyası Oluşturulamadı - "
                     << q.lastError() ;
        }
        else
        {
            qDebug() << " SIPARISEMRI DETAY Dosyası YENİ Oluşturuldu - ";
            q.exec("INSERT INTO dbtb_spredet ( spre_no )"
                   " values( 1 )"  );
        }
    }


}








Cw_Grs::~Cw_Grs()
{
   // delete ui;
}
