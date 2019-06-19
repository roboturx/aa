#include "mkn_cinsi.h"
#include "ftr_frmekle.h"
#include "globals.h"
#include "dbase.h"

hC_MKCINS::hC_MKCINS(QDialog *parent) : QDialog(parent)
{
}

void hC_MKCINS::mkcins_setup()
{
    qDebug ()  <<"CİNS MARKA MODEL YIL ";
    mkcins_VTd();
    set_uiCNS();


    CNSmodel = new QSqlRelationalTableModel ;
    mkcins_model ( CNSmodel ) ;


    set_viewCNS ();
    set_mapCNS ();
    set_kntrlCNS ();
}


void hC_MKCINS::set_uiCNS()
{
    qDebug() << "  setup_uicns";

    this->setWindowTitle ("Cinsi");
    this->setGeometry(500,50,300,600);

    //auto *pnc = new QWidget(this);

    lB_rsm = new QLabel ("Resim");
    lB_rsm->setMinimumSize(60,100);
    hC_Rs resim (lB_rsm);

    CNStview = new hC_Tv;

    auto *gL = new QGridLayout();

    gL->addWidget( lB_rsm     , 0,   0 , 1, 1);
    gL->addWidget( CNStview   , 1,   0 , 4, 1);

    this->setLayout(gL);

}

void hC_MKCINS::set_viewCNS()
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

void hC_MKCINS::set_mapCNS()
{
    qDebug()<<"setup mapcns";
    CNSmapper = new QDataWidgetMapper(this);
    CNSmapper->setModel(CNSmodel);

    //CNSmapper->addMapping(lE_unvan , CNSmodel->fieldIndex("frm_unvan"));

    CNSmapper->toFirst ();
}


void hC_MKCINS::set_kntrlCNS()
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
        hC_Rs resim ( lB_rsm, CNStview, CNSmodel, CNSselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  CNSselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, CNStview, CNSmodel, CNSselectionMdl,
                           "resim", "değiştir" );
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
         CNStview->hC_TvPb ("ilk", CNSmodel, CNSmapper);
    });

    // pB 007 önceki
    connect(CNStview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        CNStview->hC_TvPb ("ncki", CNSmodel, CNSmapper);
    });

    // pB 008 sonraki
    connect(CNStview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        CNStview->hC_TvPb ("snrki", CNSmodel, CNSmapper);
    });

    // pB 009 son
    connect(CNStview->pB_son, &QPushButton::clicked,
            [this]()
    {
        CNStview->hC_TvPb ("son", CNSmodel, CNSmapper);
    });

    // pB 010 nav tuslari kontrol
    connect(CNSmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        CNStview->hC_TvPb ("yenile", CNSmodel, CNSmapper);
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

            emit hC_MKCINS::sgnCmmy (sgnText);

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

hC_MKCINS::~hC_MKCINS()
= default;




///// CINS
///
///
QString hC_MKCINS::mkcins_VTd()
{
    //qDebug() << "db Cinsi CREATE  ";
    QString ct, mesaj = "OK - Cinsi";
    QSqlQuery q;
    QString CNStableName ( "mkcins__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( CNStableName ))
    {
        ct = "CREATE TABLE " + CNStableName +
             "("
             "cinsi TEXT, "
             "resim BLOB, "
             "id_mkcins INTEGER PRIMARY key "
             ") " ;


        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Cinsi Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Cinsi Dosyası YENİ Oluşturuldu";

            QStringList inserts;
            inserts << "INSERT INTO "+ CNStableName +" ( cinsi ) values(' - ')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Otomobil')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Arazi Aracı')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Pickup')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Kamyon')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Çekici 2x2')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Çekici 4x2')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Çekici 4x4')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Forklift')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Loader')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Backhoe')"
                    << "INSERT INTO "+ CNStableName +" ( cinsi ) values('Excavator')" ;
            int x{},y{};
            foreach (QString qry , inserts)
            {
                if ( q.exec(qry) )
                {
                    x++;
                }
                else
                {
                    y++;

                }
            }
            if (x>0)
            {
                mesaj = mesaj + QString::number (x) +
                        "<br>kayıt eklendi";
            }
            if (y>0)
            {
                mesaj = mesaj + QString::number (y) +
                        "<br>Kayıt EKLENEMEDİ "
                        "<br>------------------------------------<br>"+
                        q.lastError().text()+
                        "<br>------------------------------------<br>";
            }
        }
    }
    qDebug()<< mesaj ;
    return mesaj ;

}

void hC_MKCINS::mkcins_model ( QSqlRelationalTableModel *model)
{
    qDebug() << " db model cns";
    QString CNStableName ("mkcins__dbtb");
    QString indexField = "cinsi";
    QStringList *tableFieldList = new QStringList ;

    tableFieldList->append("Cinsi");
    tableFieldList->append("Resim");
    tableFieldList->append("Cinsi Kodu");
    hC_Rm hC_Rm ( &CNStableName,
                 model,
                 &indexField ,
                 tableFieldList) ;

}///CNS



