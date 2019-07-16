#include "mkn_modeli.h"


hC_MKMODL::hC_MKMODL()  : hC_tBcreator ()
{
    //************************************************************
    //*****************  M K  M O D L ****************************
    qDebug() << "Cnstrctr mkmodl *********************************";

    win_Label->text ()= "ARAÇ MODEL BİLGİLERİ";
    *tb_name   = "mkmodl_dbtb" ;
    *tb_ndex     = "mkmodl_modeli";

    tb_flds = new hC_ArrD ( 4, 4);
    tb_flds->setValue ( 0, "mkmodl_ID"       , "INTEGER", "ModeliID", "0" ) ;
    tb_flds->setValue ( 1, "mkmodl_mkmark_no", "INTEGER", "Marka No", "0" );
    tb_flds->setValue ( 2, "mkmodl_modeli"   , "TEXT"   , "Modeli" );
    tb_flds->setValue ( 3, "mkmodl_resim"    , "BLOB"   , "Resim" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;




}

void hC_MKMODL::tbsetup()
{

    qDebug ()  <<"MODEL ";
    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_MKMODL::tbui()
{
    qDebug() << "  ui";

    this->setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout();
    win_Grid->addWidget( win_Rsm     , 0,   0 , 1, 1);
    win_Grid->addWidget( tb_view   , 1,   0 , 4, 1);
    this->setLayout(win_Grid);

}

void hC_MKMODL::tbwdgt()
{
    win_Rsm->setMinimumSize(60,100);
    hC_Rs resim (win_Rsm);

    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->adjustSize();
    auto wdgt_Grid = new QGridLayout();
    win_Wdgt->setLayout(wdgt_Grid);

    ///////////////////////////////////////

    wdgt_Grid ->addWidget(win_Rsm  , 0, 0, 1, 1);
}

void hC_MKMODL::tbkntrl()
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
        if (q->exec("INSERT INTO _dbtb ( mkmodl_no )"
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
              "mkmodl_no INTEGER,"
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
            inserts << "INSERT INTO "+ MDLtableName +" ( modeli, mkmodl_no ) values(' - '       ,1)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmodl_no ) values('Fiesta 1.4',2)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmodl_no ) values('Focus 1.6' ,2)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmodl_no ) values('Mondeo 2.0',2)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmodl_no ) values('Clio'      ,3)"
                    << "INSERT INTO "+ MDLtableName +" ( modeli, mkmodl_no ) values('Laguna'    ,3)" ;
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
