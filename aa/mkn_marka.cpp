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

wdgt  () ;

    ui    () ;

   kntrl () ;
}


void hC_MKMARK::ui()
{
    qDebug() << "  mkmark_ui";

    win_Label = new QLabel("ARAÇ MARKA");
    this->setWindowTitle (win_Label->text ());
    this->setGeometry(500,50,300,600);
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);
    tb_view = new hC_Tv (this, tb_model, tb_mapper, win_Wdgt);

    auto *winGrid = new QGridLayout();

    winGrid->addWidget( win_Wdgt     , 0,   0 , 1, 1);
    winGrid->addWidget( tb_view   , 1,   0 , 4, 1);
    this->setLayout(winGrid);
}


void hC_MKMARK::wdgt()
{

    win_Rsm = new QLabel ("Resim");
    win_Rsm->setMinimumSize(60,100);
    hC_Rs resim (win_Rsm);

    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////

    wdgtGrid ->addWidget(win_Rsm  , 0, 0, 1, 1);
}


/*
void hC_MKMARK::mkMark_view()
{

    // Set the model and hide the ID column
    tb_view-> table-> setModel(tb_model);
    tb_slctnMdl = tb_view-> table-> selectionModel();

    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("id_mkmark"), true);
    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("resim"), true);
    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("mkcins_no"), true);

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    tb_view->table->setCurrentIndex(
                tb_model->index(0, 0)
                );
    // with blue rect
    tb_view->table->setFocus();
    //   QTimer::singleShot(0, CNStview->table, SLOT(setFocus()));


}

void hC_MKMARK::mkMark_map()
{

    qDebug()<<"  setup mapcns";
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    //CNSmapper->addMapping(lE_unvan , tb_model->fieldIndex("frm_unvan"));

    tb_mapper->toFirst ();
}
*/
void hC_MKMARK::kntrl()
{
    qDebug()<<"  setup mapcns";
    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
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

        tb_model->submitAll();
        tb_view->setFocus();
        tb_model->select();

    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                           "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(tb_view->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   tb_view->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = tb_model->record();
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
                tb_model->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                tb_model->select();
            }
        }
    });
/*
    // pB 006 ilk
    connect(tb_view->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        tb_view->hC_TvPb ("ilk", tb_model, tb_mapper);
    });

    // pB 007 önceki
    connect(tb_view->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("ncki", tb_model, tb_mapper);
    });

    // pB 008 sonraki
    connect(tb_view->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("snrki", tb_model, tb_mapper);
    });

    // pB 009 son
    connect(tb_view->pB_son, &QPushButton::clicked,
            [this]()
    {
        tb_view->hC_TvPb ("son", tb_model, tb_mapper);
    });

    // pB 010 nav tuslari kontrol
    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this]( )
    {
        tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);
    });*/

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        if (Index.isValid())
        {
            // 011-01 mapper indexi ayarla
            tb_mapper->setCurrentModelIndex(Index);


          //  QSqlRecord record = tb_model->record(Index.row());
        //    int id = record.value("id_mkmark").toInt();

            // 011-02 filter
//            MDLmodel->setFilter(QString("mkmark_no = %1").arg(id));
  //          MDLmodel->select();

            // 011-03 marka row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index = tb_view->table->currentIndex ();
            sgnText = new QString;
            *sgnText = tb_view->table->model()->index( Index.row() ,
                                                     tb_model->fieldIndex
                                                     ("marka") ).data().toString();

            emit hC_MKMARK::sgnmkMark (sgnText);
        }
        else
        {
    //        tb_model->setFilter("id_mkmark = -1");
        }
        tb_view->table->setFocus();

    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });


}

hC_MKMARK::~hC_MKMARK()
= default;


   /*

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

    tb_model = new QSqlRelationalTableModel ;
 hC_Rm hC_Rm (&MRKtableName,
                 tb_model,
                 &indexField ,
                 tB_FieldList) ;

}///MRK
*/
