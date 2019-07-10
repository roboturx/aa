#include "mkn_cinsi.h"

hC_MKCINS::hC_MKCINS(QDialog *parent) : QDialog(parent)
{
    //************************************************************
    //*****************  M K  C I N S ****************************
    qDebug() << "Cnstrctr mkcins";
}

void hC_MKCINS::mkCins_setup()
{
    qDebug ()  <<"  mkcins_setup";
    mkCins_VTd();
    mkCins_model ();
    mkCins_wdgt ();
    mkCins_map ();
    mkCins_ui();
    mkCins_view ();
    mkCins_kntrl ();

}


void hC_MKCINS::mkCins_ui()
{
    qDebug() << "  mkcins_ui";

    ////////////////////////////////////////// window
    winLabel = new QLabel("ARAÇ CİNSİ");

    this->setWindowTitle (winLabel->text ());
    //this->setGeometry(500,50,300,600);

    CNStview = new hC_Tv (CNSmodel, CNSmapper, winWdgt);

    auto *winGrid = new QGridLayout();

    winGrid->addWidget( winRsm     , 0,   0 , 1, 1);
    winGrid->addWidget( CNStview   , 1,   0 , 4, 1);

    this->setLayout(winGrid);

}

void hC_MKCINS::mkCins_wdgt()
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

void hC_MKCINS::mkCins_view()
{
    // Set the model and hide the ID column
    CNStview-> table-> setModel(CNSmodel);
    CNSslctnMdl = CNStview->table->selectionModel();

    CNStview-> table-> setColumnHidden(CNSmodel->fieldIndex("id_mkcins"), true);
    CNStview-> table-> setColumnHidden(CNSmodel->fieldIndex("resim"), true);
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

void hC_MKCINS::mkCins_map()
{
    qDebug()<<"  mkcins map";
    CNSmapper = new QDataWidgetMapper(this);
    CNSmapper->setModel(CNSmodel);

    //CNSmapper->addMapping(lE_unvan , CNSmodel->fieldIndex("frm_unvan"));

    CNSmapper->toFirst ();
}


void hC_MKCINS::mkCins_kntrl()
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
        hC_Rs resim ( winRsm, CNStview, CNSmodel, CNSslctnMdl,
                      "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  CNSslctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( winRsm, CNStview, CNSmodel, CNSslctnMdl,
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
            CNSslctnMdl->
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
    /*
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
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  CNSslctnMdl , &QItemSelectionModel::currentRowChanged,
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
            sgnText = new QString;
            *sgnText = CNStview->table->model()->index( Index.row() ,
                                  CNSmodel->fieldIndex
                                 ("cinsi") ).data().toString();

            emit hC_MKCINS::sgnCmmy (sgnText);

        }



    });
    qDebug ()<<"cins pB 010 nav 3";
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  CNSslctnMdl ,
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
QString hC_MKCINS::mkCins_VTd()
{
    //qDebug() << "db Cinsi CREATE  ";
    QString ct, mesaj = "  OK - Cinsi";
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

void hC_MKCINS::mkCins_model ()
{
    qDebug() << "  mkcins model ";
    QString CNStableName ("mkcins__dbtb");
    QString indexField = "cinsi";
    QStringList *tB_FieldList = new QStringList ;

    tB_FieldList->append("Cinsi");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Cinsi Kodu");

    CNSmodel = new QSqlRelationalTableModel ;
  /*  hC_Rm hC_Rm ( &CNStableName,
                  CNSmodel,
                  &indexField ,
                  tB_FieldList) ;
*/
}///CNS



