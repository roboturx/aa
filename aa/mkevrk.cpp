#include "mkevrk.h"
#include "mkn.h"
#include "globals.h"

_Evr::_Evr()

= default;

_Evr::~_Evr()
= default;
/////////////////////////////////////////////////////////////
/// \brief Evr_Sgrt::Evr_Sgrt
///
///     EVRAK - SİGORTA
///
 Evr_Sgrt:: Evr_Sgrt()

{
    cr_Evr_Sgrt_ui();
    cr_Evr_Sgrt_model();
    cr_Evr_Sgrt_view();
    cr_Evr_Sgrt_kontrol();
}


void Evr_Sgrt::cr_Evr_Sgrt_model()
{
    mdl_evr_sgrt = new QSqlRelationalTableModel();
    mdl_evr_sgrt->setTable("dbtb_mksigorta");
    mdl_evr_sgrt->setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!mdl_evr_sgrt->select())
    {
        qDebug () << mdl_evr_sgrt->lastError();
    }
}
void Evr_Sgrt::cr_Evr_Sgrt_view()
{
    tV_evr_sgrt->setModel(mdl_evr_sgrt);
    tV_evr_sgrt->setSelectionMode(QAbstractItemView::SingleSelection);
    tV_evr_sgrt->setSelectionBehavior(QAbstractItemView::SelectItems);
    tV_evr_sgrt->resizeColumnsToContents();
    tV_evr_sgrt->resizeRowsToContents();
    tV_evr_sgrt->setCurrentIndex(mdl_evr_sgrt->index(0,0));

    //// kullanıcı bu alanları görmesin
 //   tV_evr_sgrt->setColumnHidden(
 //         model_spre->fieldIndex("mknstk_no"), true);
 //   tV_evr_sgrt->setColumnHidden(
  //        model_spre->fieldIndex("id_spre"), true);
    mdl_evr_sgrt->select();
}


void Evr_Sgrt::cr_Evr_Sgrt_ui()
{


    //lbl_sg = new QLabel("Sigorta");


    pb_sgrt_ekle = new QPushButton("Ekle");
    pb_sgrt_sil = new QPushButton("Sil");
    pb_sgrt_yaz = new QPushButton("Yazdır");
    pb_sgrt_ekleDDD = new QPushButton("...");


    auto *hL1 = new QHBoxLayout();

    hL1->addWidget(pb_sgrt_ekle);
    hL1->addWidget(pb_sgrt_ekleDDD);
    hL1->addStretch(1);
    hL1->addWidget(pb_sgrt_sil);
    hL1->addWidget(pb_sgrt_yaz);
//hL1->addWidget(lbl_sg);

    tV_evr_sgrt = new QTableView();

    auto *gL = new QGridLayout(this);
    gL->addLayout(hL1,        0, 0, 1, 1);
    gL->addWidget(tV_evr_sgrt,    1, 0, 1, 1);

}

void Evr_Sgrt::cr_Evr_Sgrt_kontrol()
{
    /// sigorta
    connect(tV_evr_sgrt->selectionModel(),
        SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
        this, SLOT(ontV_Evr_Sgrt_row_changed(QModelIndex)));

    /// sigorta kaydı ekleyelim
    connect( pb_sgrt_ekle, &QPushButton::clicked,
             this, & Evr_Sgrt::onpb_Evr_Sgrt_Ekle);

    /// sigorta kaydı ekleyelim
    connect( pb_sgrt_ekleDDD, &QPushButton::clicked,
             this, & Evr_Sgrt::onpb_Evr_Sgrt_EkleDDD);

    /// sigorta kaydı silelim
    connect( pb_sgrt_sil, &QPushButton::clicked,
             this, & Evr_Sgrt::onpb_Evr_Sgrt_Sil );

    /// sigorta kaydı yazdıralım
    connect( pb_sgrt_yaz, &QPushButton::clicked,
             this, & Evr_Sgrt::onpb_Evr_Sgrt_Yaz );
}


void Evr_Sgrt::ontV_Evr_Sgrt_row_changed(QModelIndex)
{


}
void Evr_Sgrt::onpb_Evr_Sgrt_Ekle()
{
    /*
    int id=-1;
    QModelIndex index = tv_mkn->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = model_mkn->record(index.row());
        id = record.value("id_mkstok").toInt();
    }


    // sigorta  ekle
    QSqlQuery *q = new QSqlQuery;
    if (q->exec("INSERT INTO dbtb_mksigorta ( mknstk_no )"
                " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

    //Cwv_Grs->model_spre->submit();
    //Cwv_Grs->tV_spre->setFocus();
    //Cwv_Grs->model_spre->select();

*/
}

void Evr_Sgrt::onpb_Evr_Sgrt_Sil()
{}
void Evr_Sgrt::onpb_Evr_Sgrt_Yaz()
{}
void Evr_Sgrt::onpb_Evr_Sgrt_EkleDDD()
{}




 Evr_Sgrt::~Evr_Sgrt()
= default;
 //////////////////////////////////////////////////////
 /// \brief Evr_Mua::Evr_Mua
 ///
 ///
 ///    MAKİNA MUAYENE
 ///
Evr_Mua:: Evr_Mua()

{
    cr_Evr_Mua_ui();
    cr_Evr_Mua_model();
    cr_Evr_Mua_view();
    cr_Evr_Mua_kontrol();
}


void Evr_Mua::cr_Evr_Mua_model()
{
    mdl_evrk_mua = new QSqlRelationalTableModel();
    mdl_evrk_mua->setTable("dbtb_mkmuayene");
    mdl_evrk_mua->setEditStrategy(QSqlTableModel::OnFieldChange);
    if (!mdl_evrk_mua->select())
    {
        qDebug () << mdl_evrk_mua->lastError();
    }
}
void Evr_Mua::cr_Evr_Mua_view()
{
    tV_evrk_mua->setModel(mdl_evrk_mua);
    tV_evrk_mua->setSelectionMode(QAbstractItemView::SingleSelection);
    tV_evrk_mua->setSelectionBehavior(QAbstractItemView::SelectItems);
    tV_evrk_mua->resizeColumnsToContents();
    tV_evrk_mua->resizeRowsToContents();
    tV_evrk_mua->setCurrentIndex(mdl_evrk_mua->index(0,0));

    //// kullanıcı bu alanları görmesin
 //   tV_Evr_Mua->setColumnHidden(
 //         model_spre->fieldIndex("mknstk_no"), true);
 //   tV_Evr_Mua->setColumnHidden(
  //        model_spre->fieldIndex("id_spre"), true);
    mdl_evrk_mua->select();
}


void Evr_Mua::cr_Evr_Mua_ui()
{


    //lbl_sg = new QLabel("Sigorta");


    pb_mua_ekle = new QPushButton("Ekle");
    pb_mua_sil = new QPushButton("Sil");
    pb_mua_yaz = new QPushButton("Yazdır");
    pb_mua_ekleDDD = new QPushButton("...");


    auto *hL1 = new QHBoxLayout();

    hL1->addWidget(pb_mua_ekle);
    hL1->addWidget(pb_mua_ekleDDD);
    hL1->addStretch(1);
    hL1->addWidget(pb_mua_sil);
    hL1->addWidget(pb_mua_yaz);
    //hL1->addWidget(lbl_sg);

    tV_evrk_mua = new QTableView();

    auto *gL = new QGridLayout(this);
    gL->addLayout(hL1,        0, 0, 1, 1);
    gL->addWidget(tV_evrk_mua,    1, 0, 1, 1);

}

void Evr_Mua::cr_Evr_Mua_kontrol()
{
    /// sigorta
    connect(tV_evrk_mua->selectionModel(),
        SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
        this, SLOT(ontV_Evr_Mua_row_changed(QModelIndex)));

    /// sigorta kaydı ekleyelim
    connect( pb_mua_ekle, &QPushButton::clicked,
             this, & Evr_Mua::onpb_Evr_Mua_Ekle);

    /// sigorta kaydı ekleyelim
    connect( pb_mua_ekleDDD, &QPushButton::clicked,
             this, & Evr_Mua::onpb_Evr_Mua_EkleDDD);

    /// sigorta kaydı silelim
    connect( pb_mua_sil, &QPushButton::clicked,
             this, & Evr_Mua::onpb_Evr_Mua_Sil );

    /// sigorta kaydı yazdıralım
    connect( pb_mua_yaz, &QPushButton::clicked,
             this, & Evr_Mua::onpb_Evr_Mua_Yaz );
}


void Evr_Mua::ontV_Evr_Mua_row_changed(QModelIndex)
{


}
void Evr_Mua::onpb_Evr_Mua_Ekle()
{
    /*
    int id=-1;
    QModelIndex index = tv_mkn->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = model_mkn->record(index.row());
        id = record.value("id_mkstok").toInt();
    }


    // sigorta  ekle
    QSqlQuery *q = new QSqlQuery;
    if (q->exec("INSERT INTO dbtb_mksigorta ( mknstk_no )"
                " values("  + QString::number(id) +   ")"  ))
        qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

    //Cwv_Grs->model_spre->submit();
    //Cwv_Grs->tV_spre->setFocus();
    //Cwv_Grs->model_spre->select();

*/
}

void Evr_Mua::onpb_Evr_Mua_Sil()
{}
void Evr_Mua::onpb_Evr_Mua_Yaz()
{}
void Evr_Mua::onpb_Evr_Mua_EkleDDD()
{}




 Evr_Mua::~Evr_Mua()
= default;




