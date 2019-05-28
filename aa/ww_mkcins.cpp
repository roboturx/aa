#include "ww_mkcins.h"

#include "globals.h"


WW_Mkcins::WW_Mkcins(QWidget *parent) : QWidget(parent)
{

    qDebug ()  <<"ww mkcins 001 ";
    cr_ui();
    cr_mdl_mkcins();
    cr_mdl_mkmark();
    cr_mdl_mkmodl();
    cr_kontrol();
}

WW_Mkcins::~WW_Mkcins()
= default;

void WW_Mkcins::cr_mdl_mkcins()
{
    // Create the data model for DBTB_MKCINS

    mdl_mkcins = new QSqlRelationalTableModel(tv_mkcins);
    mdl_mkcins->setEditStrategy(QSqlTableModel::OnFieldChange);
    mdl_mkcins->setTable("DBTB_MKCINS");
    mdl_mkcins->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    // Remember the indexes of the columns
    // combobox fields
    //idx_cins = mdl_mkcins->fieldIndex("cinsi");	//dbtb_mkcins

    // Set the localized header captions
    mdl_mkcins->setHeaderData(mdl_mkcins->fieldIndex("cinsi"),
                              Qt::Horizontal, tr("CİNSİ"));

    // Populate the model
    if (!mdl_mkcins->select())
    {
        qDebug () << " HATA - " << mdl_mkcins->lastError();
        return;
    }

    // Set the model and hide the ID column
    tv_mkcins->setModel(mdl_mkcins);
    tv_mkcins->setColumnHidden(mdl_mkcins->fieldIndex("id_mkcins"), true);
    tv_mkcins->setSelectionMode(QAbstractItemView::SingleSelection);

}


void WW_Mkcins::cr_mdl_mkmark()
{
    // Create the data model for DBTB_MKCINS

    mdl_mkmark = new QSqlRelationalTableModel(tv_mkmark);
    mdl_mkmark->setEditStrategy(QSqlTableModel::OnFieldChange);
    mdl_mkmark->setTable("dbtb_mkmark");
    mdl_mkmark->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    // Remember the indexes of the columns
    // combobox fields
    //idx_cins = mdl_mkcins->fieldIndex("cinsi");	//dbtb_mkcins

    // Set the localized header captions
    mdl_mkmark->setHeaderData(mdl_mkmark->fieldIndex("marka"),
                              Qt::Horizontal, tr("MARKA"));

    // Populate the model
    if (!mdl_mkmark->select())
    {
        qDebug () << " HATA - " << mdl_mkmark->lastError();
        return;
    }

    // Set the model and hide the ID column
    tv_mkmark->setModel(mdl_mkmark);
    tv_mkmark->setColumnHidden(mdl_mkmark->fieldIndex("id_mkmark"), true);
    tv_mkmark->setSelectionMode(QAbstractItemView::SingleSelection);

}
void WW_Mkcins::cr_mdl_mkmodl()
{
    // Create the data model for DBTB_MKmodl

    mdl_mkmodl = new QSqlTableModel(tv_mkmodl);
    mdl_mkmodl->setEditStrategy(QSqlTableModel::OnFieldChange);
    mdl_mkmodl->setTable("dbtb_mkmodl");

    // Set the localized header captions
    mdl_mkmodl->setHeaderData(mdl_mkmodl->fieldIndex("modeli"),
                              Qt::Horizontal, tr("MODELİ"));

    // Populate the model
    if (!mdl_mkmodl->select())
    {
        qDebug () << " HATA - " << mdl_mkmodl->lastError();
        return;
    }

    // Set the model and hide the ID column
    tv_mkmodl->setModel(mdl_mkmodl);
    tv_mkmodl->setColumnHidden(mdl_mkmodl->fieldIndex("id_mkmodl"), true);
    tv_mkmodl->setSelectionMode(QAbstractItemView::SingleSelection);

}

void WW_Mkcins::cr_ui()
{
    pnc = new QWidget(this);
    pnc->setGeometry(100,100,600,400);
    pnc->setWindowTitle("Cins - Marka _ Model Giriş");

    tv_mkcins = new QTableView();
    pb_eklE_cns = new QPushButton("Cins Ekle");
    pb_sil_cns = new QPushButton("Cins Sil");


    tv_mkmark = new QTableView();
    pb_eklE_mrk = new QPushButton("Marka Ekle");
    pb_sil_mrk = new QPushButton("Marka Sil");

    tv_mkmodl = new QTableView(pnc);
    pb_eklE_mdl = new QPushButton("Model Ekle");
    pb_sil_mdl = new QPushButton("Model Sil");

    pb_tmm = new QPushButton("Tamam");



    auto *gL = new QGridLayout(pnc);
    gL->addWidget(tv_mkcins   ,0,0,20,2);
    gL->addWidget(pb_eklE_cns ,21,0,1,1);
    gL->addWidget(pb_sil_cns  ,21,1,1,1);

    gL->addWidget(tv_mkmark   ,0,3,20,2);
    gL->addWidget(pb_eklE_mrk ,21,3,1,1);
    gL->addWidget(pb_sil_mrk  ,21,4,1,1);

    gL->addWidget(tv_mkmodl   ,0,5,20,2);
    gL->addWidget(pb_eklE_mdl ,21,5,1,1);
    gL->addWidget(pb_sil_mdl  ,21,6,1,1);
    gL->addWidget(pb_tmm     ,22,6,1,1);
    //pnc->setLayout(gL);
    pnc->show();



}


void WW_Mkcins::cr_kontrol()
{
    tv_mkcins->setCurrentIndex(mdl_mkcins->index(0, 0));
    tv_mkcins->setFocus();

    connect(tv_mkcins->selectionModel(),
            SIGNAL( currentRowChanged(QModelIndex,QModelIndex)),
            this,  SLOT( ontV_cins_filterSLOT(QModelIndex) ));

    connect(tv_mkmark->selectionModel(),
            SIGNAL( currentRowChanged(QModelIndex,QModelIndex)),
            this,  SLOT( ontV_mark_filterSLOT(QModelIndex) ));


    connect( pb_tmm,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_tmm_clicked);

    connect( pb_eklE_cns,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_eklE_cns_clicked);

    connect( pb_sil_cns,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_sil_cns_clicked);

    connect( pb_eklE_mrk,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_eklE_mrk_clicked);

    connect( pb_sil_mrk,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_sil_mrk_clicked);

    connect( pb_eklE_mdl,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_eklE_mdl_clicked);

    connect( pb_sil_mdl,&QPushButton::clicked,
             this, &WW_Mkcins::onpb_sil_mdl_clicked);
    connect( tv_mkcins , &QTableView::clicked ,
             this, &WW_Mkcins::ontv_cns_clicked);

    connect( tv_mkmark , &QTableView::clicked ,
             this, &WW_Mkcins::ontv_mrk_clicked);

    }

void WW_Mkcins::ontv_cns_clicked()
{
    //tv_mkmodl->hide();
   // tv_mkmodl->hide();
}


void WW_Mkcins::ontv_mrk_clicked()
{
    //tv_mkmodl->hide();
}



void WW_Mkcins::onpb_tmm_clicked()
{
    // tamam - close dialog
    mdl_mkcins->submitAll();
    pnc->close();


}


void WW_Mkcins::onpb_eklE_mrk_clicked()
{
    // ekle marka

    // markaya yeni kayıt eklemek için cins kodunu üğrenelim
    int id =-1;
    QModelIndex index = tv_mkcins->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = mdl_mkcins->record(index.row());
        id = record.value("id_mkcins").toInt();
    }

    QSqlQuery *q = new QSqlQuery;
    if (q->exec("INSERT INTO dbtb_mkmark ( mkcins_no )"
                " values(" + QString::number( id) +   ")"   ))
        qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

    mdl_mkmark->submit();
    tv_mkmark->setFocus();
    mdl_mkmark->select();

}
void WW_Mkcins::onpb_sil_mrk_clicked()
{}
void WW_Mkcins::onpb_eklE_mdl_clicked()
{
    // ekle model

    // modele yeni kayıt eklemek için marka kodunu üğrenelim
    int id =-1;
    QModelIndex index = tv_mkmark->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = mdl_mkmark->record(index.row());
        id = record.value("id_mkmark").toInt();
    }

    QSqlQuery *q = new QSqlQuery;
    if (q->exec("INSERT INTO dbtb_mkmodl ( mkmark_no )"
                " values(" + QString::number( id) +   ")"   ))
        qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
    else
        qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

    mdl_mkmodl->submit();
    tv_mkmodl->setFocus();
    mdl_mkmodl->select();


}
void WW_Mkcins::onpb_sil_mdl_clicked()
{}

void WW_Mkcins::ontV_cins_filterSLOT(QModelIndex)
{

    QModelIndex index = tv_mkcins->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = mdl_mkcins->record(index.row());
        int id = record.value("id_mkcins").toInt();

        mdl_mkmark->setFilter(QString("mkcins_no = %1").arg(id));
        mdl_mkmark->select();


    }
    else
    {
        mdl_mkmark->setFilter("id_mkcins = -1");
    }
    tv_mkmark->setFocus();

}


void WW_Mkcins::ontV_mark_filterSLOT(QModelIndex)
{

    QModelIndex index = tv_mkmark->currentIndex();
    if (index.isValid())
    {
        QSqlRecord record = mdl_mkmark->record(index.row());
        int id = record.value("id_mkmark").toInt();

        mdl_mkmodl->setFilter(QString("mkmark_no = %1").arg(id));
        mdl_mkmodl->select();


    }
    else
    {
        mdl_mkmodl->setFilter("id_mkmark = -1");
    }
    tv_mkmodl->setFocus();

}


void WW_Mkcins::onpb_eklE_cns_clicked()
{
    // ekle cins
    QSqlRecord  rec( mdl_mkcins->record() );

    // Insert at end of table
    mdl_mkcins->insertRecord( -1, rec );
    mdl_mkcins->submitAll();
    tv_mkcins->setCurrentIndex(mdl_mkcins->
                               index(0,mdl_mkcins->columnCount()));
    mdl_mkcins->submitAll();
    mdl_mkcins->select();
}

void WW_Mkcins::onpb_sil_cns_clicked()
{
    // sil currentrecord
    QModelIndex sample = tv_mkcins->currentIndex();
    if( sample.row() >= 0 )
    {
        tv_mkcins->selectionModel()->
                setCurrentIndex(sample,QItemSelectionModel::NoUpdate);

        QSqlRecord rec = mdl_mkcins->record();

        QString val = rec.value(1).toString();
        QMessageBox::StandardButton dlg;

        dlg = QMessageBox::question(this,
                                    "KAYIT SİL",  val ,
                                    QMessageBox::Yes | QMessageBox::No);


        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // model->beginRemoveColumn();
            mdl_mkcins->removeRow(sample.row());
            //model->endRemoveColumns();
            mdl_mkcins->submitAll();
            mdl_mkcins->select();
        }
    }
}
