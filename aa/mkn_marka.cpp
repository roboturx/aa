#include "mkn_marka.h"


hC_MKMARK::hC_MKMARK()  : hC_tBcreator ()

{
    //************************************************************
    //*****************  M K  M A R K ****************************
    qDebug() << "Constructor MAKİNA MARKA *********************************";


    win_Label->setText ( "ARAÇ MARKA BİLGİLERİ");
    *tb_name   = "mkmark_dbtb" ;
    *tb_ndex     = "mkmark_marka";

    tb_flds = new hC_ArrD ( 4, 4);
    tb_flds->setValue ( 0, "mkmark_ID"       , "INTEGER", "MarkaID", "0" ) ;
    tb_flds->setValue ( 1, "mkmark_mkcins_no", "INTEGER", "Cins No", "0" );
    tb_flds->setValue ( 2, "mkmark_marka"    , "TEXT"   , "Marka" );
    tb_flds->setValue ( 3, "mkmark_resim"   , "BLOB"   , "Resim" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ; // id
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;
}

void hC_MKMARK::tbsetup()
{
    qDebug ()  <<"   mkMark_setup";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}


void hC_MKMARK::tbui()
{
    qDebug() << "   mkmark_ui";


    this->setWindowTitle (win_Label->text ());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget( win_Wdgt     , 0,   0 , 1, 1);
    win_Grid->addWidget( tb_view   , 1,   0 , 4, 1);
}


void hC_MKMARK::tbwdgt()
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


void hC_MKMARK::tbkntrl()
{
    qDebug()<<"   KNTRL";
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
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                           "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
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

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  tbx_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });


}

hC_MKMARK::~hC_MKMARK()
{
    qDebug() << "*********** destructor MAKİNA MARKA";//    delete ui;
}


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
