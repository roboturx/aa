#include "mkn_modeli.h"
//#include "cw_mkcins.h"
#include "ftr_frmekle.h"
#include "globals.h"
#include "dbase.h"

hC_MKMODL::hC_MKMODL(QDialog *parent) : QDialog(parent)
{
}

void hC_MKMODL::mkmodl_setup()
{

    qDebug ()  <<"MODEL ";
    set_uiMDL();

    qDebug() << "  set_modelmdl";
    MDLmodel = new QSqlRelationalTableModel ;
    mkmodl_model ( MDLmodel ) ;

    set_viewMDL ();
    set_mapMDL ();
    set_kntrlMDL ();
}


void hC_MKMODL::set_uiMDL()
{
    qDebug() << "  set_uimodl";

    this->setWindowTitle ("Model Giriş");
    this->setGeometry(500,50,300,600);
    // this->showMaximized ();

    //auto *pnc = new QWidget(this);

    lB_rsm = new QLabel ("Resim");
    lB_rsm->setMinimumSize(60,100);
    hC_Rs resim (lB_rsm);

    MDLtview = new hC_Tv;

    auto *gL = new QGridLayout();

    gL->addWidget( lB_rsm     , 0,   0 , 1, 1);
    gL->addWidget( MDLtview   , 1,   0 , 4, 1);

    this->setLayout(gL);

}

void hC_MKMODL::set_viewMDL()
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

void hC_MKMODL::set_mapMDL()
{

    qDebug()<<"setup mapmodeli";
    MDLmapper = new QDataWidgetMapper(this);
    MDLmapper->setModel(MDLmodel);

    //CNSmapper->addMapping(lE_unvan , MDLmodel->fieldIndex("frm_unvan"));

    MDLmapper->toFirst ();

}

void hC_MKMODL::set_kntrlMDL()
{
qDebug()<<"kntrl mdl ";
    // pB 001 yeni ekle
    connect(MDLtview->pB_ekle, &QPushButton::clicked ,
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
        if (q->exec("INSERT INTO mkmodl__dbtb ( mkmark_no )"
                    " values(" + QString::number( 1 ) +   ")"   ))
            qDebug () <<"Yeni Kayıt - "<< 1 << " -   Eklendi";
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
        hC_Rs resim ( lB_rsm, MDLtview, MDLmodel, MDLselectionMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  MDLselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        qDebug()<<"kntrl mdl11111 ";
        hC_Rs resim ( lB_rsm, MDLtview, MDLmodel, MDLselectionMdl,
                           "resim", "değiştir" ) ;
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
        MDLtview->hC_TvPb ("ilk", MDLmodel, MDLmapper);
    });

    // pB 007 önceki
    connect(MDLtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        MDLtview->hC_TvPb ("ncki", MDLmodel, MDLmapper);
    });

    // pB 008 sonraki
    connect(MDLtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
        MDLtview->hC_TvPb ("snrki", MDLmodel, MDLmapper);
    });

    // pB 009 son
    connect(MDLtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        MDLtview->hC_TvPb ("son", MDLmodel, MDLmapper);
    });



    ///// tableview kontrol connectleri
    ///
    ///


    // pB 010 nav tuslari kontrol
    connect(MDLmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {
        MDLtview->hC_TvPb ("yenile", MDLmodel, MDLmapper);

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
            QModelIndex Index = MDLtview->table->currentIndex ();

            sgnText = MDLtview->table->model()->index( Index.row() ,
                                                     MDLmodel->fieldIndex
                                                     ("modeli") ).data().toString() ;



            emit hC_MKMODL::sgnCmmy (sgnText);

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






hC_MKMODL::~hC_MKMODL()
= default;





///// MODEL
///
///
QString hC_MKMODL::mkmodl_VTd()
{
    //qDebug() << " db Modeli CREATE  ";
    QString ct, mesaj = "OK - Model";
    QSqlQuery q;
    QString MDLtableName ( "mkmodl__dbtb");

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( MDLtableName ))
    {
        ct =  "CREATE TABLE IF NOT EXISTS " + MDLtableName +
              "("
              "modeli TEXT, "
              "resim BLOB, "
              "mkmark_no INTEGER,"
              "id_mkmodl INTEGER PRIMARY key )"  ;


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




void hC_MKMODL::mkmodl_model ( QSqlRelationalTableModel *model)
{
    qDebug() << " db model"<< model;

    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Model");
    tB_FieldList->append("Resim");
    tB_FieldList->append("Marka Nosu");
    tB_FieldList->append("Model kodu");

    QString MODLtableName{"mkmodl__dbtb"} ;
    QString indexField = "modeli";

    hC_Rm hC_Rm ( &MODLtableName,
                  model,
                  &indexField ,
                  tB_FieldList) ;

}///MDLİ

