#include "frm.h"




hC_FRM::hC_FRM(QWidget *parent) : QWidget(parent)
{
    qDebug ()<<"Firma Constructor";
    //************************************************************
    //*****************  F İ R M A  ****************************
}

void hC_FRM::setup()
{
    qDebug() << "setup FİRMA";



   wdgt  () ;

   ui    () ;

   kntrl () ;
}



void hC_FRM::ui()
{

    qDebug() << "  frm_ui";
    win_Label = new QLabel("FİRMA BİLGİLERİ");
    hC_FRM::setWindowTitle ( win_Label->text ());

    /////////////////////////////////////////////////////////
    // views
    tb_view = new hC_Tv(tb_model, tb_mapper, win_Wdgt);

    // /////////////////////////////////////
    // main layout

    auto *winGrid = new QGridLayout;
    winGrid->addWidget ( tb_view  ,0 ,0 ,1 ,3 );
    winGrid->addWidget ( win_Wdgt  ,0 ,3 ,1 ,7 );
 //   lYG_per->addWidget ( win_Rsm   ,1 ,3 ,1 ,7 );
    this->setLayout (winGrid);
}

void hC_FRM::wdgt()
{
    // ///////////////////////////////////////////////////////
    // wdgt lbls
    //
    qDebug() << "  frm_wdgt";

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


    win_Rsm = new QLabel ("Resim");
    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////


    lB_sehir->setMinimumSize (100,25);
    lE_sehir->setMinimumSize (150,25);


    wdgtGrid->addWidget(lB_unvan   , 0, 0, 1, 1);
    wdgtGrid->addWidget(lE_unvan   , 0, 1, 1, 2);
    wdgtGrid->addWidget(lB_adres   , 1, 0, 1, 1);
    wdgtGrid->addWidget(lE_adres   , 1, 1, 1, 2);
    wdgtGrid->addWidget(lB_sehir   , 2, 0, 1, 1);
    wdgtGrid->addWidget(lE_sehir   , 2, 1, 1, 2);
    wdgtGrid->addWidget(lB_vd      , 3, 0, 1, 1);
    wdgtGrid->addWidget(lE_vd      , 3, 1, 1, 2);
    wdgtGrid->addWidget(lB_vdno    , 4, 0, 1, 1);
    wdgtGrid->addWidget(lE_vdno    , 4, 1, 1, 2);
    wdgtGrid->addWidget(lB_tel     , 5, 0, 1, 1);
    wdgtGrid->addWidget(lE_tel     , 5, 1, 1, 2);
    wdgtGrid->addWidget(lB_eposta  , 6, 0, 1, 1);
    wdgtGrid->addWidget(lE_eposta  , 6, 1, 1, 2);
    wdgtGrid->addWidget(lB_yisim   , 7, 0, 1, 1);
    wdgtGrid->addWidget(lE_yisim   , 7, 1, 1, 2);
    wdgtGrid->addWidget(lB_ysoyad  , 8, 0, 1, 1);
    wdgtGrid->addWidget(lE_ysoyad  , 8, 1, 1, 2);
    wdgtGrid->addWidget(lB_ytel    , 9, 0, 1, 1);
    wdgtGrid->addWidget(lE_ytel    , 9, 1, 1, 2);
    wdgtGrid->addWidget(win_Rsm     ,10, 1, 2, 2);

}
/*
void hC_FRM::frm_view()
{
    qDebug()<<"setup view fr";

    tb_view->table->setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    tb_view->table->setColumnHidden(tb_model->fieldIndex("frm_kod"), true);
    tb_view->table->setColumnHidden(tb_model->fieldIndex("frm_resim"), true);


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



void hC_FRM::frm_map()
{
    qDebug()<<"  frm_map";
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    tb_mapper->addMapping(lE_unvan , tb_model->fieldIndex("frm_unvan"));
    tb_mapper->addMapping(lE_adres, tb_model->fieldIndex("frm_adres"));
    tb_mapper->addMapping(lE_sehir, tb_model->fieldIndex("frm_sehir"));
    tb_mapper->addMapping(lE_vd, tb_model->fieldIndex("frm_vd"));
    tb_mapper->addMapping(lE_vdno, tb_model->fieldIndex("frm_vdno"));
    tb_mapper->addMapping(lE_tel, tb_model->fieldIndex("frm_tel"));
    tb_mapper->addMapping(lE_eposta, tb_model->fieldIndex("frm_eposta"));
    tb_mapper->addMapping(lE_yisim, tb_model->fieldIndex("frm_yisim"));
    tb_mapper->addMapping(lE_ysoyad, tb_model->fieldIndex("frm_ysoyad"));
    tb_mapper->addMapping(lE_ytel, tb_model->fieldIndex("frm_ytel"));
    //tb_mapper->addMapping(win_Rsm, tb_model->fieldIndex("frm_resim"));

    /// firma ilk kayıda
    hC_FRM::tb_mapper->toFirst ();
}
*/
void hC_FRM::kntrl()
{

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {
        QSqlRecord rec = tb_model->record();

        // insert a new record (-1) with null date
        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "HATA - Firma kaydı eklenemedi ";
        }
        else
            qDebug() << "Firma Kaydı eklendi ";
        tb_model->select();
    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        hC_Rs resim(win_Rsm, tb_view, tb_model, tb_slctnMdl,
                           "frm_resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tb_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tb_slctnMdl,
                           "frm_resim", "değiştir" ) ;
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
                                        "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
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

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        emit hC_FRM::sgnfirma(tb_view->table->model()->index( Index.row() ,
                    tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
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



/*
QString hC_FRM::frm_VTd()
{
    QSqlQuery   q;
    QString     ct, mesaj ="  OK - Firma";
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



void hC_FRM::frm_model()
{
    qDebug() << "  frm model";
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

    tb_model = new QSqlRelationalTableModel;
   hC_Rm hC_Rm ( &FRMtableName,
                  tb_model,
                  &indexField ,
                  tB_FieldList) ;

}///FİRMA
*/
