#include "mkn_modeli.h"


hC_MKMODL::hC_MKMODL(QDialog *parent) : QDialog(parent)
{

    //************************************************************
    //*****************  M K  M O D L ****************************
    qDebug() << "Cnstrctr mkmodl";
}

void hC_MKMODL::setup()
{

    qDebug ()  <<"MODEL ";
    wdgt  () ;
    ui    () ;
    kntrl () ;
}


void hC_MKMODL::ui()
{
    qDebug() << "  ui";

   // winLabel = new QLabel("ARAÇ MODEL");
    this->setWindowTitle (win_Label->text ());
    this->setGeometry(500,50,300,600);
    // this->showMaximized ();

   // tb_view = new hC_Tv (this, tb_model, tb_mapper, winWdgt);

    auto *winGrid = new QGridLayout();

    winGrid->addWidget( win_Rsm     , 0,   0 , 1, 1);
    winGrid->addWidget( tb_view   , 1,   0 , 4, 1);

    this->setLayout(winGrid);

}

void hC_MKMODL::wdgt()
{
    win_Rsm = new QLabel ("Resim");
    win_Rsm->setMinimumSize(60,100);
    hC_Rs resim (win_Rsm);

    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgt_Grid = new QGridLayout();
    win_Wdgt->setLayout(wdgt_Grid);

    ///////////////////////////////////////

    wdgt_Grid ->addWidget(win_Rsm  , 0, 0, 1, 1);
}

/*
void hC_MKMODL::view()
{

    // Set the model and hide the ID column
    tb_view-> table-> setModel(tb_model);
    tb_slctnMdl = tb_view-> table-> selectionModel();


    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("resim"), true);
    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("mkmark_no"), true);
    tb_view-> table-> setColumnHidden(tb_model->fieldIndex("id"), true);

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

void hC_MKMODL::map()
{

    qDebug()<<"  mkModl map";
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    //CNSmapper->addMapping(lE_unvan , tb_model->fieldIndex("frm_unvan"));

    tb_mapper->toFirst ();

}
*/
void hC_MKMODL::kntrl()
{
qDebug()<<"  mkModl kntrl";
    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
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
        if (q->exec("INSERT INTO _dbtb ( mkmark_no )"
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
            dlg = QMessageBox::question (this,
                                         "KAYIT SİL",  val +
                                         "\n Modeli kaydı silinsin mi? ?" ,
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



    ///// tableview kontrol connectleri
    ///
    ///


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
        // 011-01 mapper indexi ayarla
        tb_mapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

            // 011-02 marka row değiştiğinde cmmy etrafa yayınlayalım
            QModelIndex Index = tb_view->table->currentIndex ();
            sgnText = new QString;
            *sgnText = tb_view->table->model()->index( Index.row() ,
                                                     tb_model->fieldIndex
                                                     ("modeli") ).data().toString() ;



            emit hC_MKMODL::sgnmkModl (sgnText);

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //  emit Cw_fr::sgnfirma(tb_view->table->model()->index( Index.row() ,
        //                                                      tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });

}






hC_MKMODL::~hC_MKMODL()
= default;





///// MODEL
///
///*
/*
QString hC_MKMODL::VTd()
{
    //qDebug() << " db Modeli CREATE  ";
    QString ct, mesaj = "  OK - Model";
    QSqlQuery q;
    QString MDLtableName ( "_dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( MDLtableName ))
    {
        ct =  "CREATE TABLE IF NOT EXISTS " + MDLtableName +
              "("
              "modeli TEXT, "
              "resim BLOB, "
              "mkmark_no INTEGER,"
              "id INTEGER PRIMARY key )"  ;


        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Modeli Dosyası Oluşturulamadı"
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj= "OK - Modeli Dosyası YENİ Oluşturuldu";


            QStringList inserts;
            inserts << "INSERT INTO "+ MDLtableName +" ( modeli, mkmark_no ) values(' - '       ,1)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmark_no ) values('Fiesta 1.4',2)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmark_no ) values('Focus 1.6' ,2)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmark_no ) values('Mondeo 2.0',2)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmark_no ) values('Clio'      ,3)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmark_no ) values('Laguna'    ,3)" ;
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




void hC_MKMODL::model ()
{
    qDebug() << "  db model";

    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Model");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Marka Nosu");
    tB_FieldList->append("Model kodu");

    QString MODLtableName{"_dbtb"} ;
    QString indexField = "modeli";
    tb_model = new QSqlRelationalTableModel ;
  hC_Rm hC_Rm ( &MODLtableName,
                  tb_model,
                  &indexField ,
                  tB_FieldList) ;

}///MDLİ
*/
