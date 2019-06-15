#include "mkn_marka.h"
#include "cw_mkcins.h"
#include "ftr_frmekle.h"
#include "globals.h"
#include "dbase.h"

Mkn_Marka::Mkn_Marka(QDialog *parent) : QDialog(parent)
{

    qDebug ()  <<"CİNS MARKA MODEL YIL ";
    set_uiMRK();

    set_modelMRK ();
    set_viewMRK ();
    set_mapMRK ();
    set_kntrlMRK ();
}


void Mkn_Marka::set_uiMRK()
{
    qDebug() << "  setup_uimrk";

    this->setWindowTitle ("Marka Giriş");
    this->setGeometry(500,50,300,600);
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);

    lB_rsm = new QLabel ("Resim");
    lB_rsm->setMinimumSize(60,100);
    hC_Rs resim (lB_rsm);

    MRKtview = new hC_Tv;

    auto *gL = new QGridLayout();

    gL->addWidget( lB_rsm     , 0,   0 , 1, 1);
    gL->addWidget( MRKtview   , 1,   0 , 4, 1);
    this->setLayout(gL);
}


void Mkn_Marka::set_modelMRK()
{

    MRKmodel = new QSqlRelationalTableModel ;
    MRKmodel = dbase->modelMarka() ;


}

void Mkn_Marka::set_viewMRK()
{

    // Set the model and hide the ID column
    MRKtview-> table-> setModel(MRKmodel);
    MRKtview-> table-> setSelectionMode(QAbstractItemView::SingleSelection);
    MRKtview-> table-> setSelectionBehavior(QAbstractItemView::SelectItems);
    MRKselectionMdl = MRKtview-> table-> selectionModel();

    MRKtview-> table-> setColumnHidden(MRKmodel->fieldIndex("id_mkmark"), true);
    MRKtview-> table-> setColumnHidden(MRKmodel->fieldIndex("resim"), true);
    MRKtview-> table-> setColumnHidden(MRKmodel->fieldIndex("mkcins_no"), true);

    MRKtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    MRKtview->table->horizontalHeader()->setStretchLastSection(true);
    MRKtview->table->horizontalHeader()->resizeContentsPrecision();
    MRKtview->table->resizeRowsToContents ();
    MRKtview->table->resizeColumnsToContents();

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    MRKtview->table->setCurrentIndex(
                MRKmodel->index(0, 0)
                );
    // with blue rect
    MRKtview->table->setFocus();
    //   QTimer::singleShot(0, CNStview->table, SLOT(setFocus()));


}

void Mkn_Marka::set_mapMRK()
{

    qDebug()<<"setup mapcns";
    MRKmapper = new QDataWidgetMapper(this);
    MRKmapper->setModel(MRKmodel);

    //CNSmapper->addMapping(lE_unvan , MRKmodel->fieldIndex("frm_unvan"));

    MRKmapper->toFirst ();
}

void Mkn_Marka::set_kntrlMRK()
{

    // pB 001 yeni ekle
    connect(MRKtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        // ekle marka

        // markaya yeni kayıt eklemek için cins kodunu üğrenelim
/*        int id =-1;
        QModelIndex index = CNStview->table->currentIndex();
        if (index.isValid())
        {
            QSqlRecord record = CNSmodel->record(index.row());
            id = record.value("id_mkcins").toInt();
        }
*/
        QSqlQuery *q = new QSqlQuery;
        if (q->exec("INSERT INTO mkmark__dbtb ( mkcins_no )"
                    " values(" + QString::number( 1 ) +   ")"   ))
            qDebug () <<"Yeni Kayıt - "<< 1 << " -   Eklendi";
        else
            qDebug () << "Yeni Kayıt Eklenemedi - " << q->lastError() ;

        MRKmodel->submitAll();
        MRKtview->setFocus();
        MRKmodel->select();

    });

    // pB 002 yeni resim ekle
    connect(MRKtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim ( lB_rsm, MRKtview, MRKmodel, MRKselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MRKselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, MRKtview, MRKmodel, MRKselectionMdl,
                           "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(MRKtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   MRKtview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = MRKmodel->record();
            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val+
                                        "\n Marka kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                MRKmodel->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                MRKmodel->select();
            }
        }
    });

    // pB 006 ilk
    connect(MRKtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        MRKmapper->toFirst ();
        int map_row = MRKmapper->currentIndex ();
        MRKtview->pB_ilk->setEnabled (map_row>0);
        MRKtview->table->setCurrentIndex(MRKmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(MRKtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        MRKmapper->toPrevious ();
        int map_row = MRKmapper->currentIndex ();
        MRKtview->pB_ncki->setEnabled(map_row > 0);
        MRKtview->table->setCurrentIndex(MRKmodel->index( map_row  ,0));
    });

    // pB 008 sonraki
    connect(MRKtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        MRKmapper->toNext ();
        int map_row = MRKmapper->currentIndex ();
        MRKtview->pB_snrki->setEnabled(map_row < MRKmodel->rowCount() - 1);
        MRKtview->table->setCurrentIndex(MRKmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(MRKtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        MRKmapper->toLast ();
        int map_row = MRKmapper->currentIndex ();
        MRKtview->pB_son->setEnabled(map_row < MRKmodel->rowCount() - 1);
        MRKtview->table->setCurrentIndex(MRKmodel->index( MRKmodel->rowCount() - 1  ,0));
    });



    ///// tableview kontrol connectleri
    ///
    ///


    // pB 010 nav tuslari kontrol
    connect(MRKmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //FTRmapper->currentIndex ();
        MRKtview->pB_ilk->setEnabled (row>0);
        MRKtview->pB_ncki->setEnabled(row > 0);
        MRKtview->pB_snrki->setEnabled(row < MRKmodel->rowCount() - 1);
        MRKtview->pB_son->setEnabled(row < MRKmodel->rowCount() - 1);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  MRKselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        if (Index.isValid())
        {
            // 011-01 mapper indexi ayarla
            MRKmapper->setCurrentModelIndex(Index);


          //  QSqlRecord record = MRKmodel->record(Index.row());
        //    int id = record.value("id_mkmark").toInt();

            // 011-02 filter
//            MDLmodel->setFilter(QString("mkmark_no = %1").arg(id));
  //          MDLmodel->select();

            // 011-03 marka row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index = MRKtview->table->currentIndex ();

            sgnText = MRKtview->table->model()->index( Index.row() ,
                                                     MRKmodel->fieldIndex
                                                     ("marka") ).data().toString();

            emit Mkn_Marka::sgnCmmy (sgnText);
        }
        else
        {
    //        MRKmodel->setFilter("id_mkmark = -1");
        }
        MRKtview->table->setFocus();

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  MRKselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        MRKmapper->setCurrentModelIndex(Index);
    });


}

Mkn_Marka::~Mkn_Marka()
= default;


