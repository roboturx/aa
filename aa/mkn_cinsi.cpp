#include "mkn_cinsi.h"
#include "ftr_frmekle.h"
#include "globals.h"
#include "dbase.h"

Mkn_Cinsi::Mkn_Cinsi(QDialog *parent) : QDialog(parent)
{

    qDebug ()  <<"CİNS MARKA MODEL YIL ";
    set_uiCNS();

    set_modelCNS ();
    set_viewCNS ();
    set_mapCNS ();
    set_kntrlCNS ();
}


void Mkn_Cinsi::set_uiCNS()
{
    qDebug() << "  setup_uicns";

    this->setWindowTitle ("Cinsi");
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);

    lB_rsm = new QLabel ("Resim");
    lB_rsm->setMinimumSize(60,100);
    Resim resim (lB_rsm);

    CNStview = new HC_TableView;

    auto *gL = new QGridLayout();

    gL->addWidget( CNStview   , 0,   0 , 4, 1);
    gL->addWidget( lB_rsm     , 4,   0 , 1, 1);
    this->setLayout(gL);

}

void Mkn_Cinsi::set_modelCNS()
{
    qDebug()<<"setup model cns";

    CNSmodel = new QSqlRelationalTableModel ;
    CNSmodel = dbase->modelCinsi() ;
    qDebug()<<"setup model cns son";
}
void Mkn_Cinsi::set_viewCNS()
{
    // Set the model and hide the ID column
    CNStview-> table-> setModel(CNSmodel);
    CNStview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    CNStview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    CNSselectionMdl = CNStview->table->selectionModel();

    CNStview-> table-> setColumnHidden(CNSmodel->fieldIndex("id_mkcins"), true);
    CNStview-> table-> setColumnHidden(CNSmodel->fieldIndex("resim"), true);

    CNStview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    CNStview->table->horizontalHeader()->setStretchLastSection(true);
    CNStview->table->horizontalHeader()->resizeContentsPrecision();
    CNStview->table->resizeRowsToContents ();
    CNStview->table->resizeColumnsToContents();

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    CNStview->table->setCurrentIndex(
                CNSmodel->index(0, 1)
                );
    // with blue rect
    CNStview->table->setFocus();
    //   QTimer::singleShot(0, CNStview->table, SLOT(setFocus()));



}

void Mkn_Cinsi::set_mapCNS()
{
    qDebug()<<"setup mapcns";
    CNSmapper = new QDataWidgetMapper(this);
    CNSmapper->setModel(CNSmodel);

    //CNSmapper->addMapping(lE_unvan , CNSmodel->fieldIndex("frm_unvan"));

    CNSmapper->toFirst ();
}


void Mkn_Cinsi::set_kntrlCNS()
{
    // pB 001 yeni ekle
    connect(CNStview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QSqlRecord rec = CNSmodel->record();
        // insert a new record (-1) with null date
        if ( ! CNSmodel->insertRecord(-1,rec))
        {
            qDebug() << "HATA - Cinsi kaydı eklenemedi ";
        }
        else
        {
            qDebug() << "Cinsi Kaydı eklendi ";
        }
        CNSmodel->submitAll();
        CNSmodel->select();
        CNStview->table->setCurrentIndex(CNSmodel->
                                         index(0,CNSmodel->columnCount()));

    });

    // pB 002 yeni resim ekle
    connect(CNStview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        Resim resim;
        resim.resimUpdate (lB_rsm, CNStview, CNSmodel, CNSselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  CNSselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        Resim resim;
        resim.resimUpdate (lB_rsm, CNStview, CNSmodel, CNSselectionMdl,
                           "resim");
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(CNStview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // sil currentrecord
        QModelIndex sample = CNStview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            CNSselectionMdl->
                    setCurrentIndex(sample,QItemSelectionModel::NoUpdate);

            QSqlRecord rec = CNSmodel->record();

            QString val = rec.value(1).toString();
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question ( this,
                                          "KAYIT SİL",  val ,
                                          QMessageBox::Yes |
                                          QMessageBox::No);


            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // model->beginRemoveColumn();
                CNSmodel->removeRow(sample.row());
                //model->endRemoveColumns();
                CNSmodel->submitAll();
                CNSmodel->select();
            }
        }
    });

    // pB 006 ilk
    connect(CNStview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        CNSmapper->toFirst ();
        int map_row = CNSmapper->currentIndex ();
        CNStview->pB_ilk->setEnabled (map_row>0);
        CNStview->table->setCurrentIndex(CNSmodel->index( 0  ,0));
    });

    // pB 007 önceki
    connect(CNStview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        CNSmapper->toPrevious ();
        int map_row = CNSmapper->currentIndex ();
        CNStview->pB_ncki->setEnabled(map_row > 0);
        CNStview->table->setCurrentIndex(CNSmodel->index( map_row  ,0));
    });

    // pB 008 sonraki
    connect(CNStview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        CNSmapper->toNext ();
        int map_row = CNSmapper->currentIndex ();
        CNStview->pB_snrki->setEnabled(map_row < CNSmodel->rowCount() - 1);
        CNStview->table->setCurrentIndex(CNSmodel->index( map_row  ,0));
    });

    // pB 009 son
    connect(CNStview->pB_son, &QPushButton::clicked,
            [this]()
    {
        CNSmapper->toLast ();
        int map_row = CNSmapper->currentIndex ();
        CNStview->pB_son->setEnabled(map_row < CNSmodel->rowCount() - 1);
        CNStview->table->setCurrentIndex(CNSmodel->index( CNSmodel->rowCount() - 1  ,0));
    });



    ///// tableview kontrol connectleri
    ///
    ///
    // pB 010 nav tuslari kontrol
    connect(CNSmapper, &QDataWidgetMapper::currentIndexChanged,
            [this](int Index )
    {
        int row = Index; //FTRmapper->currentIndex ();
        CNStview->pB_ilk->setEnabled (row>0);
        CNStview->pB_ncki->setEnabled(row > 0);
        CNStview->pB_snrki->setEnabled(row < CNSmodel->rowCount() - 1);
        CNStview->pB_son->setEnabled(row < CNSmodel->rowCount() - 1);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  CNSselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {

        if (Index.isValid())
        {
            // 011-01 mapper indexi ayarla
            CNSmapper->setCurrentModelIndex(Index);

            // 011-02 filter
//            QSqlRecord record = CNSmodel->record(Index.row());
//            int id = record.value("id_mkcins").toInt();

//            MRKmodel->setFilter(QString("mkcins_no = %1").arg(id));
//            MRKmodel->select();

            // 011-03 cins row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index  = CNStview->table->currentIndex ();
            sgnText = CNStview->table->model()->index( Index.row() ,
                                                       CNSmodel->fieldIndex
                                                       ("cinsi") ).data().toString();

            emit Mkn_Cinsi::sgnCmmy (sgnText);

        }



    });
    qDebug ()<<"cins pB 010 nav 3";
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  CNSselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        CNSmapper->setCurrentModelIndex(Index);
    });

    qDebug ()<<"cins pB 010 nav  sonnn";

}

Mkn_Cinsi::~Mkn_Cinsi()
= default;
