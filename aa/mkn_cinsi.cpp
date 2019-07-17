#include "mkn_cinsi.h"

hC_MKCINS::hC_MKCINS() : hC_tBcreator ()
{
    //************************************************************
    //*****************  M K  C I N S ****************************
    qDebug() << "Constructor MAKİNA CİNSİ *********************************";
    win_Label->setText ( "ARAÇ CİNSİ");
    *tb_name   = "mkcins_dbtb" ;
    *tb_ndex     = "mkcins_cinsi";

    tb_flds = new hC_ArrD (3, 4);
    tb_flds->setValue ( 0, "mkcins_ID"   , "INTEGER", "CinsiID", "0" ) ;
    tb_flds->setValue ( 1, "mkcins_cins" , "TEXT"   , "Cinsi" );
    tb_flds->setValue ( 2, "mkcins_resim", "BLOB"   , "Resim" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;


}

void hC_MKCINS::tbsetup()
{
    qDebug ()  <<"  setup";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_MKCINS::tbui()
{
    qDebug() << "   UI";
    this->setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget( win_Rsm     , 0,   0 , 1, 1);
    win_Grid->addWidget( tb_view   , 1,   0 , 4, 1);
}

void hC_MKCINS::tbwdgt()
{
    qDebug() << "   WDGT";
    win_Rsm->setMinimumSize(60,100);
    hC_Rs resim (win_Rsm);

    ///////////////////////////////////////
    
    win_Wdgt->adjustSize();
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////

    wdgtGrid ->addWidget(win_Rsm  , 0, 0, 1, 1);
}
void hC_MKCINS::tbkntrl()
{
    qDebug() << "   KNTRL";
    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QSqlRecord rec = tb_model->record();
        // insert a new record (-1) with null date
        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "HATA - Cinsi kaydı eklenemedi ";
        }
        else
        {
            qDebug() << "Cinsi Kaydı eklendi ";
        }
        tb_model->submitAll();
        tb_model->select();
        tb_view->table->setCurrentIndex(tb_model->
                                         index(0,tb_model->columnCount()));

    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                      "resim", "değiştir" );
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        // sil currentrecord
        QModelIndex sample = tb_view->table->currentIndex();
        if( sample.row() >= 0 )
        {
            tbx_slctnMdl->
                    setCurrentIndex(sample,QItemSelectionModel::NoUpdate);

            QSqlRecord rec = tb_model->record();

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
                tb_model->removeRow(sample.row());
                //model->endRemoveColumns();
                tb_model->submitAll();
                tb_model->select();
            }
        }
    });
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {

        if (Index.isValid())
        {
            // 011-01 mapper indexi ayarla
            tb_mapper->setCurrentModelIndex(Index);

            // 011-02 filter
            //            QSqlRecord record = tb_model->record(Index.row());
            //            int id = record.value("id_mkcins").toInt();

            //            MRKmodel->setFilter(QString("no = %1").arg(id));
            //            MRKmodel->select();

            // 011-03 cins row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index  = tb_view->table->currentIndex ();
            sgnText = new QString;
            *sgnText = tb_view->table->model()->index( Index.row() ,
                                  tb_model->fieldIndex
                                 ("cinsi") ).data().toString();

            emit hC_MKCINS::sgnCmmy (sgnText);

        }



    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });



}

hC_MKCINS::~hC_MKCINS()
{
    qDebug() << "*********** destructor MAKİNA CİNSİ ";//    delete ui;
}

