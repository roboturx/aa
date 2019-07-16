#include "frm.h"

hC_FRM::hC_FRM() : hC_tBcreator ()
{
    qDebug ()<<"Firma Constructor ********************************";
    //************************************************************
    //*****************  F İ R M A  ****************************


    win_Label->setText ( "FİRMA BİLGİLERİ");
    *tb_name  = "frm_dbtb" ;
    *tb_ndex  = "frm_unvan";

    tb_flds = new hC_ArrD (12, 4);
    tb_flds->setValue ( 0, "frm_ID"   , "INTEGER", "FirmaID", "0" ) ;
    tb_flds->setValue ( 1, "frm_unvan", "TEXT"   , "Firma Ünvanı" );
    tb_flds->setValue ( 2, "frm_adres", "TEXT"   , "Adres" );
    tb_flds->setValue ( 3, "frm_sehir", "TEXT"   , "sehir");
    tb_flds->setValue ( 4, "frm_vd"   , "TEXT"   , "Vergi Dairesi"   );
    tb_flds->setValue ( 5, "frm_vdno" , "TEXT"   , "Vergi D. No"   );
    tb_flds->setValue ( 6, "frm_tel"  , "TEXT"   , "Telefon"    );
    tb_flds->setValue ( 7, "frm_eposta"   , "TEXT"   , "e-posta"   );
    tb_flds->setValue ( 8, "frm_ytklisim" , "TEXT"   , "Yetkili Adı");
    tb_flds->setValue ( 9, "frm_ytklsoyad", "TEXT"   , "Yetkili Soyadı");
    tb_flds->setValue (10, "frm_ytkltel"  , "TEXT"   , "Yetkili Telefon");
    tb_flds->setValue (11, "frm_resim"    , "BLOB"   , "Resim" , "0" );

    tb_wdgts = new QList <QWidget*> ;
    tb_wdgts->append ( nullptr    ) ;
    tb_wdgts->append ( lE_unvan = new QLineEdit  ) ;
    tb_wdgts->append ( lE_adres = new QLineEdit  ) ;
    tb_wdgts->append ( lE_sehir = new QLineEdit ) ;
    tb_wdgts->append ( lE_vd = new QLineEdit    ) ;
    tb_wdgts->append ( lE_vdno = new QLineEdit    ) ;
    tb_wdgts->append ( lE_tel = new QLineEdit     ) ;
    tb_wdgts->append ( lE_eposta = new QLineEdit   ) ;
    tb_wdgts->append ( lE_yisim = new QLineEdit    ) ;
    tb_wdgts->append ( lE_ysoyad  = new QLineEdit   ) ;
    tb_wdgts->append ( lE_ytel  = new QLineEdit  ) ;
    tb_wdgts->append ( win_Rsm  = new QLabel    ) ;



}

void hC_FRM::tbsetup()
{
    qDebug() << "   setup FİRMA";

    tbCreate ( tb_flds );
    tbModel  ( tb_flds );
    tbView   ( tb_flds );
    tbMap    ( tb_flds, tb_wdgts );

    tbwdgt  ();
    tbui();
    tbkntrl ();
}



void hC_FRM::tbui()
{

    qDebug() << "   frm_ui";

    hC_FRM::setWindowTitle ( win_Label->text ());
    auto *win_Grid = new QGridLayout(this);
    win_Grid->addWidget ( tb_view  ,0 ,0 ,1 ,3 );
    win_Grid->addWidget ( win_Wdgt  ,0 ,3 ,1 ,7 );
}

void hC_FRM::tbwdgt()
{
    qDebug() << "   frm_wdgt";

    auto *lB_unvan  = new QLabel("Unvan"       );
    lB_unvan->setBuddy(lE_unvan);

    auto *lB_adres = new QLabel("Adres"       );
    lB_adres->setBuddy(lE_adres);

    auto *lB_sehir = new QLabel("Şehir"       );
    lB_sehir->setBuddy(lE_sehir);

    auto *lB_vd    = new QLabel("Vergi Dairesi" );
    lB_vd->setBuddy(lE_vd);

    auto *lB_vdno = new QLabel("VD No"  );
    lB_vdno->setBuddy(lE_vdno);

    auto *lB_tel  = new QLabel("Telefon "  );
    lB_tel->setBuddy(lE_tel);

    auto *lB_eposta    = new QLabel("e-posta"  );
    lB_eposta->setBuddy(lE_eposta);

    auto  *lB_yisim  = new QLabel("Yetkili İsim"  );
    lB_yisim->setBuddy(lE_yisim);

    auto  *lB_ysoyad   = new QLabel("Yetkili Soyad"  );
    lB_ysoyad->setBuddy(lE_ysoyad);

    auto  *lB_ytel = new QLabel("Yetkili Tel");
    lB_ytel->setBuddy(lE_ytel);


    hC_Rs resim(win_Rsm);


    ///////////////////////////////////////
    
    win_Wdgt->adjustSize();
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

void hC_FRM::tbkntrl()
{
    qDebug() << "   KNTRL";
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
        hC_Rs resim(win_Rsm, tb_view, tb_model, tbx_slctnMdl,
                           "frm_resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( win_Rsm, tb_view, tb_model, tbx_slctnMdl,
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
    // --- 011 row değiştiğinde 2 şey olsun
    connect(  tbx_slctnMdl , &QItemSelectionModel::currentRowChanged,
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
    connect(  tbx_slctnMdl ,
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

