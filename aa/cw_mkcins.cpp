#include "cw_mkcins.h"
#include "ftr_frmekle.h"
#include "globals.h"
#include "dbase.h"

WW_Mkcins::WW_Mkcins(QDialog *parent) : QDialog(parent)
{

    qDebug ()  <<"CİNS MARKA MODEL YIL ";
    set_uiCNS();

    set_modelCNS ();
    set_viewCNS ();
    set_mapCNS ();
    set_kntrlCNS ();

    set_modelMRK ();
    set_viewMRK ();
    set_mapMRK ();
    set_kntrlMRK ();

    set_modelMDL ();
    set_viewMDL ();
    set_mapMDL ();
    set_kntrlMDL ();
}


void WW_Mkcins::set_uiCNS()
{
    qDebug() << "  setup_uicns";

    this->setWindowTitle ("Cins - Marka _ Model Giriş");
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);

    lB_rsm = new QLabel ("Resim");
    lB_rsm->setMinimumSize(60,100);
    Resim resim (lB_rsm);

    lB_rsm1 = new QLabel ("Resim");
    lB_rsm1->setMinimumSize(60,100);
    Resim resim1 (lB_rsm1);

    lB_rsm2 = new QLabel ("Resim");
    lB_rsm2->setMinimumSize(60,100);
    Resim resim2 (lB_rsm2);


    CNStview = new HC_TableView;
    MRKtview = new HC_TableView;
    MDLtview = new HC_TableView;


    auto *gL = new QGridLayout();

    int str{};
    int stn{};
    gL->addWidget( CNStview   , 0,   0 , 4, 1);
    gL->addWidget( lB_rsm     , 4,   0 , 1, 1);
    gL->addWidget( MRKtview   , 0,   1 , 4, 1);
    gL->addWidget( lB_rsm1    , 4,   1 , 1, 1);
    gL->addWidget( MDLtview   , 0,   2 , 4, 1);
    gL->addWidget( lB_rsm2    , 4,   2 , 1, 1);


    /*gL->addWidget(pb_eklE_cns , ,0,1,1);
    //gL->addWidget(pb_sil_cns  ,21,1,1,1);

    gL->addWidget(MRKtview   ,0,3,20,2);
    gL->addWidget(pb_eklE_mrk ,21,3,1,1);
    gL->addWidget(pb_sil_mrk  ,21,4,1,1);

    gL->addWidget(MDLtview   ,0,5,20,2);
    gL->addWidget(pb_eklE_mdl ,21,5,1,1);
    gL->addWidget(pb_sil_mdl  ,21,6,1,1);
    gL->addWidget(pb_tmm     ,22,6,1,1);
*/
    this->setLayout(gL);
    //pnc->show();



}

void WW_Mkcins::set_modelCNS()
{
    qDebug()<<"setup model cns";

    CNSmodel = new QSqlRelationalTableModel ;
    CNSmodel = dbase->modelCinsi() ;
    qDebug()<<"setup model cns son";
}
void WW_Mkcins::set_viewCNS()
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

void WW_Mkcins::set_mapCNS()
{
    qDebug()<<"setup mapcns";
    CNSmapper = new QDataWidgetMapper(this);
    CNSmapper->setModel(CNSmodel);

    //CNSmapper->addMapping(lE_unvan , CNSmodel->fieldIndex("frm_unvan"));

    CNSmapper->toFirst ();
}


void WW_Mkcins::set_kntrlCNS()
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
            QModelIndex Index1 = MRKtview->table->currentIndex ();
            QModelIndex Index2 = MDLtview->table->currentIndex ();
            sgnText1 = CNStview->table->model()->index( Index.row() ,
                                                       CNSmodel->fieldIndex
                                                       ("cinsi") ).data().toString();

            sgnText2 = MRKtview->table->model()->index( Index1.row() ,
                                                     MRKmodel->fieldIndex
                                                     ("marka") ).data().toString();

            sgnText3 = MDLtview->table->model()->index( Index2.row() ,
                                                     MDLmodel->fieldIndex
                                                     ("modeli") ).data().toString() ;
            emit WW_Mkcins::sgnCmmy (sgnText1, sgnText2, sgnText3);

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

void WW_Mkcins::set_modelMRK()
{

    MRKmodel = new QSqlRelationalTableModel ;
    MRKmodel = dbase->modelMarka() ;


}

void WW_Mkcins::set_viewMRK()
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

void WW_Mkcins::set_mapMRK()
{

    qDebug()<<"setup mapcns";
    MRKmapper = new QDataWidgetMapper(this);
    MRKmapper->setModel(MRKmodel);

    //CNSmapper->addMapping(lE_unvan , MRKmodel->fieldIndex("frm_unvan"));

    MRKmapper->toFirst ();
}

void WW_Mkcins::set_kntrlMRK()
{

    // pB 001 yeni ekle
    connect(MRKtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        // ekle marka

        // markaya yeni kayıt eklemek için cins kodunu üğrenelim
        int id =-1;
        QModelIndex index = CNStview->table->currentIndex();
        if (index.isValid())
        {
            QSqlRecord record = CNSmodel->record(index.row());
            id = record.value("id_mkcins").toInt();
        }

        QSqlQuery *q = new QSqlQuery;
        if (q->exec("INSERT INTO mkmark__dbtb ( mkcins_no )"
                    " values(" + QString::number( id) +   ")"   ))
            qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
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
        Resim resim;
        resim.resimUpdate (lB_rsm1, MRKtview, MRKmodel, MRKselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MRKselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        Resim resim;
        resim.resimUpdate (lB_rsm1, MRKtview, MRKmodel, MRKselectionMdl,
                           "resim");
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


            QSqlRecord record = MRKmodel->record(Index.row());
            int id = record.value("id_mkmark").toInt();

            // 011-02 filter
            MDLmodel->setFilter(QString("mkmark_no = %1").arg(id));
            MDLmodel->select();

            // 011-03 marka row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index  = CNStview->table->currentIndex ();
            QModelIndex Index1 = MRKtview->table->currentIndex ();
            QModelIndex Index2 = MDLtview->table->currentIndex ();
            sgnText1 = CNStview->table->model()->index( Index.row() ,
                                                       CNSmodel->fieldIndex
                                                       ("cinsi") ).data().toString();

            sgnText2 = MRKtview->table->model()->index( Index1.row() ,
                                                     MRKmodel->fieldIndex
                                                     ("marka") ).data().toString();

            sgnText3 = MDLtview->table->model()->index( Index2.row() ,
                                                     MDLmodel->fieldIndex
                                                     ("modeli") ).data().toString() ;
            emit WW_Mkcins::sgnCmmy (sgnText1, sgnText2, sgnText3);
        }
        else
        {
            MDLmodel->setFilter("id_mkmark = -1");
        }
        MDLtview->table->setFocus();

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  MRKselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        MRKmapper->setCurrentModelIndex(Index);
    });


}

void WW_Mkcins::set_modelMDL()
{
    MDLmodel = new QSqlRelationalTableModel ;
    MDLmodel = dbase->modelModeli() ;
}

void WW_Mkcins::set_viewMDL()
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

void WW_Mkcins::set_mapMDL()
{

    qDebug()<<"setup mapmodeli";
    MDLmapper = new QDataWidgetMapper(this);
    MDLmapper->setModel(MDLmodel);

    //CNSmapper->addMapping(lE_unvan , MDLmodel->fieldIndex("frm_unvan"));

    MDLmapper->toFirst ();

}

void WW_Mkcins::set_kntrlMDL()
{
qDebug()<<"kntrl mdl ";
    // pB 001 yeni ekle
    connect(MDLtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        // ekle model

        // modele yeni kayıt eklemek için marka kodunu üğrenelim
        int id =-1;
        QModelIndex index = MRKtview->table->currentIndex();
        if (index.isValid())
        {
            QSqlRecord record = MRKmodel->record(index.row());
            id = record.value("id_mkmark").toInt();
        }

        QSqlQuery *q = new QSqlQuery;
        if (q->exec("INSERT INTO mkmodl__dbtb ( mkmark_no )"
                    " values(" + QString::number( id) +   ")"   ))
            qDebug () <<"Yeni Kayıt - "<< id << " -   Eklendi";
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
        Resim resim;
        resim.resimUpdate (lB_rsm2, MDLtview, MDLmodel, MDLselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MDLselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        qDebug()<<"kntrl mdl11111 ";
        Resim resim;
        resim.resimUpdate (lB_rsm2, MDLtview, MDLmodel, MDLselectionMdl,
                           "resim");
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
            QModelIndex Index  = CNStview->table->currentIndex ();
            QModelIndex Index1 = MRKtview->table->currentIndex ();
            QModelIndex Index2 = MDLtview->table->currentIndex ();
            sgnText1 = CNStview->table->model()->index( Index.row() ,
                                                       CNSmodel->fieldIndex
                                                       ("cinsi") ).data().toString();

            sgnText2 = MRKtview->table->model()->index( Index1.row() ,
                                                     MRKmodel->fieldIndex
                                                     ("marka") ).data().toString();

            sgnText3 = MDLtview->table->model()->index( Index2.row() ,
                                                     MDLmodel->fieldIndex
                                                     ("modeli") ).data().toString() ;



            emit WW_Mkcins::sgnCmmy (sgnText1, sgnText2, sgnText3);

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






WW_Mkcins::~WW_Mkcins()
= default;


