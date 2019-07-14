#include "mkn_cinsi.h"

hC_MKCINS::hC_MKCINS(QDialog *parent) : QDialog(parent)
{
    //************************************************************
    //*****************  M K  C I N S ****************************
    qDebug() << "Cnstrctr mkcins";
}

void hC_MKCINS::setup()
{
    qDebug ()  <<"  setup";
    wdgt ();
    ui();
    kntrl ();

}


void hC_MKCINS::ui()
{
    qDebug() << "  ui";
    this->setWindowTitle (win_Label->text ());
    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget( win_Rsm     , 0,   0 , 1, 1);
    winGrid->addWidget( tb_view   , 1,   0 , 4, 1);
}

void hC_MKCINS::wdgt()
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
void hC_MKCINS::view()
{
    // Set the model and hide the ID column
    tb_view-> table-> setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel();

    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("id_mkcins"), true);
    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("resim"), true);
    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    tb_view->table->setCurrentIndex(
                tb_model->index(0, 1)
                );
    // with blue rect
    tb_view->table->setFocus();
    //   QTimer::singleShot(0, tb_view->table, SLOT(setFocus()));

}

void hC_MKCINS::map()
{
    qDebug()<<"  mkcins map";
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    //tb_mapper->addMapping(lE_unvan , tb_model->fieldIndex("frm_unvan"));

    tb_mapper->toFirst ();
}

*/
void hC_MKCINS::kntrl()
{
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
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                      "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
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
            tb_slctnMdl->
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
            [this]()
    {
        tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);
    });
*/
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
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
    qDebug ()<<"cins pB 010 nav 3";
    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });

    qDebug ()<<"cins pB 010 nav  sonnn";

}

hC_MKCINS::~hC_MKCINS()
= default;



/*
///// CINS
///
///
QString hC_MKCINS::VTd()
{
    //qDebug() << "db Cinsi CREATE  ";
    QString ct, mesaj = "  OK - Cinsi";
    QSqlQuery q;
    QString CNStableName ( "_dbtb");

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

void hC_MKCINS::model ()
{
    qDebug() << "  mkcins model ";
    QString CNStableName ("_dbtb");
    QString indexField = "cinsi";
    QStringList *tB_FieldList = new QStringList ;

    tB_FieldList->append("Cinsi");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Cinsi Kodu");

    tb_model = new QSqlRelationalTableModel ;
   hC_Rm hC_Rm ( &CNStableName,
                  tb_model,
                  &indexField ,
                  tB_FieldList) ;

}///CNS
*/


