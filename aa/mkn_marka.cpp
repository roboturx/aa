#include "mkn_marka.h"


hC_MKMARK::hC_MKMARK(QDialog *parent) : QDialog(parent)
{
    //************************************************************
    //*****************  M K  M A R K ****************************
    qDebug() << "Cnstrctr mkmark";
}

void hC_MKMARK::mkMark_setup()
{
    qDebug ()  <<"  mkMark_setup";
    mkMark_VTd   () ;
    mkMark_model () ;
    mkMark_wdgt  () ;
    mkMark_map   () ;
    mkMark_ui    () ;
    mkMark_view  () ;
    mkMark_kntrl () ;
}


void hC_MKMARK::mkMark_ui()
{
    qDebug() << "  mkmark_ui";

    winLabel = new QLabel("ARAÇ MARKA");
    this->setWindowTitle (winLabel->text ());
    this->setGeometry(500,50,300,600);
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);
    MRKtview = new hC_Tv (MRKmodel, MRKmapper, winWdgt);

    auto *winGrid = new QGridLayout();

    winGrid->addWidget( winWdgt     , 0,   0 , 1, 1);
    winGrid->addWidget( MRKtview   , 1,   0 , 4, 1);
    this->setLayout(winGrid);
}


void hC_MKMARK::mkMark_wdgt()
{

    winRsm = new QLabel ("Resim");
    winRsm->setMinimumSize(60,100);
    hC_Rs resim (winRsm);

    ///////////////////////////////////////
    winWdgt = new QWidget;
    winWdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    winWdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////

    wdgtGrid ->addWidget(winRsm  , 0, 0, 1, 1);
}



void hC_MKMARK::mkMark_view()
{

    // Set the model and hide the ID column
    MRKtview-> table-> setModel(MRKmodel);
    MRKslctnMdl = MRKtview-> table-> selectionModel();

    MRKtview-> table-> setColumnHidden(MRKmodel->fieldIndex("id_mkmark"), true);
    MRKtview-> table-> setColumnHidden(MRKmodel->fieldIndex("resim"), true);
    MRKtview-> table-> setColumnHidden(MRKmodel->fieldIndex("mkcins_no"), true);

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

void hC_MKMARK::mkMark_map()
{

    qDebug()<<"  setup mapcns";
    MRKmapper = new QDataWidgetMapper(this);
    MRKmapper->setModel(MRKmodel);

    //CNSmapper->addMapping(lE_unvan , MRKmodel->fieldIndex("frm_unvan"));

    MRKmapper->toFirst ();
}

void hC_MKMARK::mkMark_kntrl()
{
    qDebug()<<"  setup mapcns";
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
        hC_Rs resim ( winRsm, MRKtview, MRKmodel, MRKslctnMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MRKslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( winRsm, MRKtview, MRKmodel, MRKslctnMdl,
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
/*
    // pB 006 ilk
    connect(MRKtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        MRKtview->hC_TvPb ("ilk", MRKmodel, MRKmapper);
    });

    // pB 007 önceki
    connect(MRKtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        MRKtview->hC_TvPb ("ncki", MRKmodel, MRKmapper);
    });

    // pB 008 sonraki
    connect(MRKtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        MRKtview->hC_TvPb ("snrki", MRKmodel, MRKmapper);
    });

    // pB 009 son
    connect(MRKtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        MRKtview->hC_TvPb ("son", MRKmodel, MRKmapper);
    });

    // pB 010 nav tuslari kontrol
    connect(MRKmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]( )
    {
        MRKtview->hC_TvPb ("yenile", MRKmodel, MRKmapper);
    });*/

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  MRKslctnMdl , &QItemSelectionModel::currentRowChanged,
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
            sgnText = new QString;
            *sgnText = MRKtview->table->model()->index( Index.row() ,
                                                     MRKmodel->fieldIndex
                                                     ("marka") ).data().toString();

            emit hC_MKMARK::sgnmkMark (sgnText);
        }
        else
        {
    //        MRKmodel->setFilter("id_mkmark = -1");
        }
        MRKtview->table->setFocus();

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  MRKslctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        MRKmapper->setCurrentModelIndex(Index);
    });


}

hC_MKMARK::~hC_MKMARK()
= default;




///// MARKA
///
///
QString hC_MKMARK::mkMark_VTd()
{
    //qDebug() << " db Marka CREATE  ";
    QString ct, mesaj = "OK - Marka";
    QSqlQuery q;
    QString MRKtableName( "mkmark__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( MRKtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + MRKtableName +
             "("
             "marka TEXT, "
             "resim BLOB, "
             "mkcins_no INTEGER,"
             "id_mkmark INTEGER PRIMARY key )"  ;



        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Marka Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Marka Dosyası YENİ Oluşturuldu";


            QStringList inserts;
            inserts << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' - ',1)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' FORD '  ,2)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' RENAULT',2)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' OPEL '  ,2)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' VW'     ,2)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' JEEP '  ,3)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' TOYOTA' ,3)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' NISSAN ',4)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' ISUZU'  ,4)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',5)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',6)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',7)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' MERCEDES-BENZ',8)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' BAOLI'        ,9)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' ÇUKUROVA'     ,9)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' CATERPILLAR'  ,10)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' JVC'          ,11)"
                    << "INSERT INTO "+ MRKtableName +" ( marka,mkcins_no ) values(' HITACHI'      ,12)";
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


void hC_MKMARK::mkMark_model ()
{
    qDebug() << "  modelmarka";
    QString MRKtableName("mkmark__dbtb");
    QString indexField = "marka";
    QStringList *tB_FieldList = new QStringList ;

    tB_FieldList->append("Marka");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Cinsi Nosu");
    tB_FieldList->append("Marka kodu");

    MRKmodel = new QSqlRelationalTableModel ;
   /* hC_Rm hC_Rm (&MRKtableName,
                 MRKmodel,
                 &indexField ,
                 tB_FieldList) ;
*/
}///MRK

