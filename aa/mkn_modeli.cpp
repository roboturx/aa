#include "mkn_modeli.h"
#include "cw_mkcins.h"
#include "ftr_frmekle.h"
#include "globals.h"
#include "dbase.h"

Mkn_Modeli::Mkn_Modeli(QDialog *parent) : QDialog(parent)
{

    qDebug ()  <<"CİNS MARKA MODEL YIL ";
    set_uiMDL();

    set_modelMDL ();
    set_viewMDL ();
    set_mapMDL ();
    set_kntrlMDL ();
}


void Mkn_Modeli::set_uiMDL()
{
    qDebug() << "  setup_uicns";

    this->setWindowTitle ("Model Giriş");
    this->setGeometry(500,50,300,600);
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);

    lB_rsm = new QLabel ("Resim");
    lB_rsm->setMinimumSize(60,100);
    hC_Rs resim (lB_rsm);

    MDLtview = new hC_Tv;

    auto *gL = new QGridLayout();

    gL->addWidget( lB_rsm     , 0,   0 , 1, 1);
    gL->addWidget( MDLtview   , 1,   0 , 4, 1);

    this->setLayout(gL);

}

void Mkn_Modeli::set_modelMDL()
{
    MDLmodel = new QSqlRelationalTableModel ;
    dbase->modelModeli(MDLmodel) ;
}

void Mkn_Modeli::set_viewMDL()
{

    // Set the model and hide the ID column
    MDLtview-> table-> setModel(MDLmodel);
    MDLtview-> table-> setSelectionMode(QAbstractItemView::SingleSelection);
    MDLtview-> table-> setSelectionBehavior(QAbstractItemView::SelectItems);
    MDLselectionMdl = MDLtview-> table-> selectionModel();


    MDLtview-> table-> setColumnHidden(MDLmodel->fieldIndex("resim"), true);
    MDLtview-> table-> setColumnHidden(MDLmodel->fieldIndex("mkmark_no"), true);
    MDLtview-> table-> setColumnHidden(MDLmodel->fieldIndex("id_mkmodl"), true);

    MDLtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    MDLtview->table->horizontalHeader()->setStretchLastSection(true);
    MDLtview->table->horizontalHeader()->resizeContentsPrecision();
    MDLtview->table->resizeRowsToContents ();
    MDLtview->table->resizeColumnsToContents();

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    MDLtview->table->setCurrentIndex(
                MDLmodel->index(0, 0)
                );
    // with blue rect
    MDLtview->table->setFocus();
    //   QTimer::singleShot(0, CNStview->table, SLOT(setFocus()));


}

void Mkn_Modeli::set_mapMDL()
{

    qDebug()<<"setup mapmodeli";
    MDLmapper = new QDataWidgetMapper(this);
    MDLmapper->setModel(MDLmodel);

    //CNSmapper->addMapping(lE_unvan , MDLmodel->fieldIndex("frm_unvan"));

    MDLmapper->toFirst ();

}

void Mkn_Modeli::set_kntrlMDL()
{
qDebug()<<"kntrl mdl ";
    // pB 001 yeni ekle
    connect(MDLtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        // ekle model

        // modele yeni kayıt eklemek için marka kodunu üğrenelim
/*        int id =-1;
        QModelIndex index = MRKtview->table->currentIndex();
        if (index.isValid())
        {
            QSqlRecord record = MRKmodel->record(index.row());
            id = record.value("id_mkmark").toInt();
        }
*/
        QSqlQuery *q = new QSqlQuery;
        if (q->exec("INSERT INTO mkmodl__dbtb ( mkmark_no )"
                    " values(" + QString::number( 1 ) +   ")"   ))
            qDebug () <<"Yeni Kayıt - "<< 1 << " -   Eklendi";
        else
            qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

        MDLmodel->submitAll();
        MDLtview->setFocus();
        MDLmodel->select();


    });

    // pB 002 yeni resim ekle
    connect(MDLtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim ( lB_rsm, MDLtview, MDLmodel, MDLselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MDLselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        qDebug()<<"kntrl mdl11111 ";
        hC_Rs resim ( lB_rsm, MDLtview, MDLmodel, MDLselectionMdl,
                           "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(MDLtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   MDLtview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = MDLmodel->record();
            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question (this,
                                         "KAYIT SİL",  val +
                                         "\n Modeli kaydı silinsin mi? ?" ,
                                         QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                MDLmodel->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                MDLmodel->select();
            }
        }
    });

    // pB 006 ilk
    connect(MDLtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        MDLmapper->toFirst ();
        int map_row = MDLmapper->currentIndex ();
        MDLtview->pB_ilk->setEnabled (map_row>0);
        MDLtview->table->setCurrentIndex(MDLmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(MDLtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        MDLmapper->toPrevious ();
        int map_row = MDLmapper->currentIndex ();
        MDLtview->pB_ncki->setEnabled(map_row > 0);
        MDLtview->table->setCurrentIndex(MDLmodel->index( map_row  ,0));
    });

    // pB 008 sonraki
    connect(MDLtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        MDLmapper->toNext ();
        int map_row = MDLmapper->currentIndex ();
        MDLtview->pB_snrki->setEnabled(map_row < MDLmodel->rowCount() - 1);
        MDLtview->table->setCurrentIndex(MDLmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(MDLtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        MDLmapper->toLast ();
        int map_row = MDLmapper->currentIndex ();
        MDLtview->pB_son->setEnabled(map_row < MDLmodel->rowCount() - 1);
        MDLtview->table->setCurrentIndex(MDLmodel->index( MDLmodel->rowCount() - 1  ,0));
    });



    ///// tableview kontrol connectleri
    ///
    ///


    // pB 010 nav tuslari kontrol
    connect(MDLmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //FTRmapper->currentIndex ();
        MDLtview->pB_ilk->setEnabled (row>0);
        MDLtview->pB_ncki->setEnabled(row > 0);
        MDLtview->pB_snrki->setEnabled(row < MDLmodel->rowCount() - 1);
        MDLtview->pB_son->setEnabled(row < MDLmodel->rowCount() - 1);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  MDLselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        MDLmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

            // 011-02 marka row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index = MDLtview->table->currentIndex ();

            sgnText = MDLtview->table->model()->index( Index.row() ,
                                                     MDLmodel->fieldIndex
                                                     ("modeli") ).data().toString() ;



            emit Mkn_Modeli::sgnCmmy (sgnText);

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //  emit Cw_fr::sgnfirma(MDLtview->table->model()->index( Index.row() ,
        //                                                      MDLmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  MDLselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        MDLmapper->setCurrentModelIndex(Index);
    });

}






Mkn_Modeli::~Mkn_Modeli()
= default;


