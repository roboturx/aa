#include "frm.h"
//#include "dbase.h"
//#include "globals.h"
#include "ftr_frmekle.h"



hC_FRM::hC_FRM(QWidget *parent) : QWidget(parent)
{
    qDebug ()<<"Firma Constructor";
    //************************************************************
    //*****************  F İ R M A  ****************************
}

void hC_FRM::frm_setup()
{
    qDebug() << "setup FİRMA";

    frm_VTd();
    frm_ui();

    qDebug()<<"setup model fr";
    FRMmodel = new QSqlRelationalTableModel;
    frm_model ( FRMmodel );

    qDebug() << "setup_Firma END";
    frm_view();
    frm_map();
    frm_kntrl();
}



void hC_FRM::frm_ui()
{

    qDebug() << "  frm_ui";

    hC_FRM::setWindowTitle ("FİRMA");
    hC_FRM::showMaximized ();


    // ///////////////////////////////////////////////////////

    lB_fr  = new QLabel ("Firma");
    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);

    // ///////////////////////////////////////////////////////
    // views
    FRMtview = new hC_Tv();

    // ///////////////////////////////////////////////////////
    // wdgt lbls
    //

    auto *lB_unvan  = new QLabel(tr("Unvan"        ));
    lE_unvan = new QLineEdit() ;
    lB_unvan->setBuddy(lE_unvan);
    auto *lB_adres = new QLabel(tr("Adres"       ));
    lE_adres = new QLineEdit();
    lB_adres->setBuddy(lE_adres);
    auto *lB_sehir = new QLabel(tr("Şehir"       ));
    lE_sehir = new QLineEdit();
    lB_sehir->setBuddy(lE_sehir);
    auto *lB_vd    = new QLabel(tr("Vergi Dairesi" ));
    lE_vd = new QLineEdit();
    lB_vd->setBuddy(lE_vd);
    auto *lB_vdno = new QLabel(tr("VD No"  ));
    lE_vdno = new QLineEdit();
    lB_vdno->setBuddy(lE_vdno);
    auto *lB_tel  = new QLabel(tr("Telefon "  ));
    lE_tel = new QLineEdit();
    lB_tel->setBuddy(lE_tel);
    auto *lB_eposta    = new QLabel(tr("e-posta"  ));
    lE_eposta = new QLineEdit();
    lB_eposta->setBuddy(lE_eposta);
    auto  *lB_yisim  = new QLabel(tr("Yetkili İsim"  ));
    lE_yisim = new QLineEdit();
    lB_yisim->setBuddy(lE_yisim);
    auto  *lB_ysoyad   = new QLabel(tr("Yetkili Soyad"  ));
    lE_ysoyad = new QLineEdit();
    lB_ysoyad->setBuddy(lE_ysoyad);
    auto  *lB_ytel = new QLabel(tr("Yetkili Tel"));
    lE_ytel = new QLineEdit();
    lB_ytel->setBuddy(lE_ytel);


    auto *frm_mly = new QGridLayout;

    frm_mly->addWidget(lB_unvan   , 0, 0, 1, 1);
    frm_mly->addWidget(lE_unvan   , 0, 1, 1, 2);
    frm_mly->addWidget(lB_adres   , 1, 0, 1, 1);
    frm_mly->addWidget(lE_adres   , 1, 1, 1, 2);
    frm_mly->addWidget(lB_sehir   , 2, 0, 1, 1);
    frm_mly->addWidget(lE_sehir   , 2, 1, 1, 2);
    frm_mly->addWidget(lB_vd      , 3, 0, 1, 1);
    frm_mly->addWidget(lE_vd      , 3, 1, 1, 2);
    frm_mly->addWidget(lB_vdno    , 4, 0, 1, 1);
    frm_mly->addWidget(lE_vdno    , 4, 1, 1, 2);
    frm_mly->addWidget(lB_tel     , 5, 0, 1, 1);
    frm_mly->addWidget(lE_tel     , 5, 1, 1, 2);
    frm_mly->addWidget(lB_eposta  , 6, 0, 1, 1);
    frm_mly->addWidget(lE_eposta  , 6, 1, 1, 2);
    frm_mly->addWidget(lB_yisim   , 7, 0, 1, 1);
    frm_mly->addWidget(lE_yisim   , 7, 1, 1, 2);
    frm_mly->addWidget(lB_ysoyad  , 8, 0, 1, 1);
    frm_mly->addWidget(lE_ysoyad  , 8, 1, 1, 2);
    frm_mly->addWidget(lB_ytel    , 9, 0, 1, 1);
    frm_mly->addWidget(lE_ytel    , 9, 1, 1, 2);
    //frm_mly->addWidget(lB_rsm    , 9, 1, 1, 2);
    // /////////////////////////////////////
    // main layout

    auto *lYG_per = new QGridLayout(this);
    lYG_per->addWidget ( FRMtview ,0 ,0 ,2 ,1 );
    lYG_per->addLayout ( frm_mly   ,0 ,1 ,1 ,1);
    lYG_per->addWidget ( lB_rsm   ,1 ,1 ,1 ,1);

}

void hC_FRM::frm_view()
{
    qDebug()<<"setup view fr";

    FRMtview->table->setModel(FRMmodel);
    FRMtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    FRMtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    FRMselectionMdl = FRMtview->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    FRMtview->table->setColumnHidden(FRMmodel->fieldIndex("frm_kod"), true);
    FRMtview->table->setColumnHidden(FRMmodel->fieldIndex("frm_resim"), true);

    FRMtview->table->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);
    FRMtview->table->horizontalHeader()->setStretchLastSection(true);
    FRMtview->table->horizontalHeader()->resizeContentsPrecision();
    FRMtview->table->resizeRowsToContents ();
    FRMtview->table->resizeColumnsToContents();

    // select first item
    // selection model does not hide the frm_kod
    // so index 0,1 must be select
    FRMtview->table->setCurrentIndex(
                FRMmodel->index(0, 1)
                );
    // with blue rect
    FRMtview->table->setFocus();
    //   QTimer::singleShot(0, FRMtview->table, SLOT(setFocus()));
}


/* user interface */
void hC_FRM::frm_map()
{
    qDebug()<<"setup mapfr";
    FRMmapper = new QDataWidgetMapper(this);
    FRMmapper->setModel(FRMmodel);

    FRMmapper->addMapping(lE_unvan , FRMmodel->fieldIndex("frm_unvan"));
    FRMmapper->addMapping(lE_adres, FRMmodel->fieldIndex("frm_adres"));
    FRMmapper->addMapping(lE_sehir, FRMmodel->fieldIndex("frm_sehir"));
    FRMmapper->addMapping(lE_vd, FRMmodel->fieldIndex("frm_vd"));
    FRMmapper->addMapping(lE_vdno, FRMmodel->fieldIndex("frm_vdno"));
    FRMmapper->addMapping(lE_tel, FRMmodel->fieldIndex("frm_tel"));
    FRMmapper->addMapping(lE_eposta, FRMmodel->fieldIndex("frm_eposta"));
    FRMmapper->addMapping(lE_yisim, FRMmodel->fieldIndex("frm_yisim"));
    FRMmapper->addMapping(lE_ysoyad, FRMmodel->fieldIndex("frm_ysoyad"));
    FRMmapper->addMapping(lE_ytel, FRMmodel->fieldIndex("frm_ytel"));
    FRMmapper->addMapping(lB_rsm, FRMmodel->fieldIndex("frm_resim"));

    /// firma ilk kayıda
    hC_FRM::FRMmapper->toFirst ();
}

void hC_FRM::frm_kntrl()
{

    // pB 001 yeni ekle
    connect(FRMtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QSqlRecord rec = FRMmodel->record();

        // insert a new record (-1) with null date
        if ( ! FRMmodel->insertRecord(-1,rec))
        {
            qDebug() << "HATA - Firma kaydı eklenemedi ";
        }
        else
            qDebug() << "Firma Kaydı eklendi ";
        FRMmodel->select();
    });

    // pB 002 yeni resim ekle
    connect(FRMtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(lB_rsm, FRMtview, FRMmodel, FRMselectionMdl,
                           "frm_resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  FRMselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, FRMtview, FRMmodel, FRMselectionMdl,
                           "frm_resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(FRMtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   FRMtview->table->currentIndex();
        if( sample.row() >= 0 )
        {
            QSqlRecord rec = FRMmodel->record();
            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                FRMmodel->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                FRMmodel->select();
            }
        }
    });

    // pB 006 ilk
    connect(FRMtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        FRMtview->hC_TvPb ("ilk", FRMmodel, FRMmapper);
    });

    // pB 007 önceki
    connect(FRMtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        FRMtview->hC_TvPb ("ncki", FRMmodel, FRMmapper);
    });

    // pB 008 sonraki
    connect(FRMtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
    FRMtview->hC_TvPb ("snrki", FRMmodel, FRMmapper);
    });

    // pB 009 son
    connect(FRMtview->pB_son, &QPushButton::clicked,
            [this]()
    {
        FRMtview->hC_TvPb ("son", FRMmodel, FRMmapper);
    });

    // pB 010 nav tuslari kontrol
    connect(FRMmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]( )
    {
        FRMtview->hC_TvPb ("yenile", FRMmodel, FRMmapper);
    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  FRMselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        FRMmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        emit hC_FRM::sgnfirma(FRMtview->table->model()->index( Index.row() ,
                    FRMmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  FRMselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        FRMmapper->setCurrentModelIndex(Index);
    });



}



void hC_FRM::showEvent(QShowEvent *)
{
    qDebug() << "ShowEvent Firma dosyası açılıyor";
}


hC_FRM::~hC_FRM()
= default;




/// date does not take null value
/// line 126 at QDateEdit declaration
/// with the
/// dT_dotar->setSpecialValueText ("  ");
/// line
/// an invalid date value represents " "
///
//    dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );




QString hC_FRM::frm_VTd()
{
    QSqlQuery   q;
    QString     ct, mesaj ="OK - Firma";
    QStringList inserts;
    QString FRMtableName ( "frm__dbtb");

    if ( ! VTKontrolEt::instance()->
         GetDB().tables().contains( FRMtableName ))
    {
        ct = "CREATE TABLE IF NOT EXISTS " + FRMtableName +
             "("
             "  frm_kod    INTEGER PRIMARY KEY  , "
             "  frm_unvan	TEXT ,"
             "  frm_adres	TEXT ,"
             "  frm_sehir    TEXT ,"
             "  frm_vd       TEXT ,"
             "  frm_vdno     TEXT ,"
             "  frm_tel 	    TEXT ,"
             "  frm_eposta   TEXT ,"
             "  frm_yisim	TEXT ,"
             "  frm_ysoyad	TEXT ,"
             "  frm_ytel 	TEXT ,"
             "  frm_resim    BLOB  )" ;

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Firma Dosyası Oluşturulamadı - "
                    "<br>------------------------------------<br>"+
                    q.lastError().text()+
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - FİRMA Dosyası YENİ Oluşturuldu ";
            inserts << "INSERT INTO " + FRMtableName +
                       "( "
                       "frm_unvan , frm_adres, frm_sehir , "
                       "frm_vd    , frm_vdno , frm_tel   , "
                       "frm_eposta, frm_yisim, frm_ysoyad, "
                       "frm_ytel  , frm_resim  "
                       ") "
                       "VALUES "
                       "("
                       "'-', '-', ' ', "
                       "' ', ' ', ' ', "
                       "' ', ' ', ' ', "
                       "' ', ' ' "
                       " )" ;


            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {
                    mesaj = mesaj + "<br>İLK Firma Kaydı Eklenemedi "
                                    "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else{
                    mesaj = mesaj + "<br>İLK Firma Eklendi ";
                }
            } // foreach
        }
    }
    qDebug()  << mesaj ;
    return mesaj ;
}   /// FİRMA



void hC_FRM::frm_model(QSqlRelationalTableModel *model)
{
    qDebug() << " frm model";
    QString indexField = "frm_unvan";
    QString FRMtableName ("frm__dbtb");

    QStringList *tB_FieldList = new QStringList ;
    tB_FieldList->append("Firma Kod");
    tB_FieldList->append("Firma Unvanı");
    tB_FieldList->append("Adres");
    tB_FieldList->append("Şehir");
    tB_FieldList->append("Vergi Dairesi");
    tB_FieldList->append("VD No");
    tB_FieldList->append("Telefon");
    tB_FieldList->append("e-posta");
    tB_FieldList->append("Yetkili İsim");
    tB_FieldList->append("Yetkili Soyad");
    tB_FieldList->append("Yetkili Telefon");
    // tB_FieldList->append("resim");


     hC_Rm hC_Rm ( &FRMtableName,
                  model,
                  &indexField ,
                  tB_FieldList) ;

}///FİRMA





//QString DBase::VTd_FRMA()
//{
//    QSqlQuery   q;
//    QString     ct, mesaj ="OK - Firma";
//    QStringList inserts;
//    FRMtableName = new QString( "frm__dbtb");

//    if ( ! VTKontrolEt::instance()->
//         GetDB().tables().contains( *FRMtableName ))
//    {
//        ct = "CREATE TABLE IF NOT EXISTS " + *FRMtableName +
//             "("
//             "  frm_kod    INTEGER PRIMARY KEY  , "
//             "  frm_unvan	TEXT ,"
//             "  frm_adres	TEXT ,"
//             "  frm_sehir    TEXT ,"
//             "  frm_vd       TEXT ,"
//             "  frm_vdno     TEXT ,"
//             "  frm_tel 	    TEXT ,"
//             "  frm_eposta   TEXT ,"
//             "  frm_yisim	TEXT ,"
//             "  frm_ysoyad	TEXT ,"
//             "  frm_ytel 	TEXT ,"
//             "  frm_resim    BLOB  )" ;

//        if (!q.exec( ct ))
//        {
//            mesaj = "<br>HATA - Firma Dosyası Oluşturulamadı - "
//                    "<br>------------------------------------<br>"+
//                    q.lastError().text()+
//                    "<br>------------------------------------<br>";
//        }
//        else
//        {
//            mesaj = "OK - FİRMA Dosyası YENİ Oluşturuldu ";
//            inserts << "INSERT INTO " + *FRMtableName +
//                       "( "
//                       "frm_unvan , frm_adres, frm_sehir , "
//                       "frm_vd    , frm_vdno , frm_tel   , "
//                       "frm_eposta, frm_yisim, frm_ysoyad, "
//                       "frm_ytel  , frm_resim  "
//                       ") "
//                       "VALUES "
//                       "("
//                       "'-', '-', ' ', "
//                       "' ', ' ', ' ', "
//                       "' ', ' ', ' ', "
//                       "' ', ' ' "
//                       " )" ;


//            foreach (QString qry , inserts)
//            {
//                if ( !q.exec(qry) )
//                {
//                    mesaj = mesaj + "<br>İLK Firma Kaydı Eklenemedi "
//                                    "<br>------------------------------------<br>"+
//                            q.lastError().text ()+
//                            "<br>------------------------------------<br>";
//                }
//                else{
//                    mesaj = mesaj + "<br>İLK Firma Eklendi ";
//                }
//            } // foreach
//        }
//    }
//    qDebug()  << mesaj ;
//    return mesaj ;
//}   /// FİRMA



//void DBase::modelFirma(QSqlRelationalTableModel *model)
//{
//    qDebug() << " mdlfrm";
//    QString indexField = "frm_unvan";
//    FRMtableName = new QString("frm__dbtb");

//    QStringList *tB_FieldList = new QStringList ;
//    tB_FieldList->append("Firma Kod");
//    tB_FieldList->append("Firma Unvanı");
//    tB_FieldList->append("Adres");
//    tB_FieldList->append("Şehir");
//    tB_FieldList->append("Vergi Dairesi");
//    tB_FieldList->append("VD No");
//    tB_FieldList->append("Telefon");
//    tB_FieldList->append("e-posta");
//    tB_FieldList->append("Yetkili İsim");
//    tB_FieldList->append("Yetkili Soyad");
//    tB_FieldList->append("Yetkili Telefon");
//    // tB_FieldList->append("resim");


//     hC_Rm hC_Rm (FRMtableName,
//                  model,
//                  &indexField ,
//                  tB_FieldList) ;

//      //FRMmodel = new QSqlRelationalTableModel;
//     //    mdlfrm->setTable( "frm_dbtb" );
////    mdlfrm->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
////    mdlfrm->setSort(mdlfrm->fieldIndex ( indexField ),Qt::AscendingOrder );

////    for(int i = 0, j = 0; i < tB_FieldList->size (); i++, j++)
////    {
////        mdlfrm->setHeaderData(i,Qt::Horizontal,tB_FieldList->value (j));
////    }

////    // Populate the model_mkstok
////    if (!mdlfrm->select())
////    {
////        qDebug () <<  " HATA - Model firma select "
////                   <<mdlfrm->lastError();
////    }


//}///FİRMA

