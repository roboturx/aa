#include "tsnr.h"

hC_TSNR::hC_TSNR(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"cnstrct Taşınır İstek ";
    //************************************************************
    //************  T A Ş I N I R   İ S T E K  *******************
}

void hC_TSNR:: setup()
{
    qDebug() << "  tsnr setup ";
      wdgt  () ;
      ui    () ;

     kntrl () ;
}


void hC_TSNR:: ui()
{
    qDebug() << "   ui";
    win_Label = new QLabel("TAŞINIR İSTEK");
    hC_TSNR::setWindowTitle (win_Label->text ());




    // ///////////////////////////////////////////////////////
    // views
    tb_view = new hC_Tv (tb_model, tb_mapper, win_Wdgt);


    auto *winGrid = new QGridLayout(this);
    winGrid->addWidget (tb_view  , 0, 0, 1, 1);
    winGrid->addWidget (win_Wdgt   , 0, 1, 1, 1);
}

void hC_TSNR:: wdgt()
{

    auto *lB_tsno = new QLabel("Taşınır No");

    lE_TSno = new QLineEdit;
    lE_TSno->setText (*TSdetno);
    lE_TSno->setReadOnly (true);

    lB_tsno->setBuddy(lE_TSno);

    qDebug ()<<"ts 142";
    QLabel *lB_gt = new QLabel("Tarih");

    dE_TStarih = new QDateTimeEdit(QDate::currentDate());
    dE_TStarih->setDisplayFormat("dd.MM.yyyy");
    dE_TStarih->setMinimumDate(QDate(01, 01, 1900));
    dE_TStarih->setMaximumDate(QDate(valiDDate));
    dE_TStarih->setCalendarPopup(true);

    lB_gt->setBuddy(dE_TStarih);


    QLabel *lB_us = new QLabel("İstenen Malzeme Adı");

    cbx_TSmalzeme = new QComboBox;                    //dbtb_TSNR
    lB_us->setBuddy(cbx_TSmalzeme);


    qDebug ()<<"ts 143";


    QLabel *lB_tm = new QLabel("Miktar");

    lE_TSmiktar = new QLineEdit;

    lB_tm->setBuddy(lE_TSmiktar );

    QLabel *lB_usb = new QLabel("Birim");

    cbx_TSbirim = new QComboBox;                    //dbtb_TSNR

    lB_usb->setBuddy(cbx_TSbirim);

    QLabel *lB_bf = new QLabel("Birim Fiyat");

    lE_TSbfiyat = new QLineEdit;
    lB_bf->setBuddy(lE_TSbfiyat);


    QLabel *lB_dr = new QLabel("Durum");
    cbx_TSdurum = new QComboBox;                    // dbtb_durum
    cbx_TSdurum->addItem ("-");
    cbx_TSdurum->addItem ("Parça Bekliyor");
    cbx_TSdurum->addItem ("Usta Bekliyor");
    cbx_TSdurum->addItem ("Tamamlandı");

    lB_dr->setBuddy(cbx_TSdurum);

    QLabel *lB_acklm = new QLabel("Açıklama");

    lE_TSaciklama = new QLineEdit;
    lB_acklm->setBuddy(lE_TSaciklama);


    win_Rsm = new QLabel("Resim ");
    win_Rsm = new QLabel("Taşınır İstek");

    ///////////////////////////////////////
    win_Wdgt = new QWidget;
    win_Wdgt->setGeometry (0,0,800,300);
    auto wdgtGrid = new QGridLayout();
    win_Wdgt->setLayout(wdgtGrid);

    ///////////////////////////////////////
    lE_TSaciklama->setMinimumSize (200,25);


    wdgtGrid->addWidget(lB_tsno        ,0,0,1,1,nullptr);
    wdgtGrid->addWidget(lE_TSno   ,0,1,1,3,nullptr);
    wdgtGrid->addWidget(lB_gt        ,1,0,1,1,nullptr);
    wdgtGrid->addWidget(dE_TStarih   ,1,1,1,3,nullptr);
    wdgtGrid->addWidget(lB_us        ,2,0,1,1,nullptr);
    wdgtGrid->addWidget(cbx_TSmalzeme   ,2,1,1,3,nullptr);
    wdgtGrid->addWidget(lB_tm        ,3,0,1,1,nullptr);
    wdgtGrid->addWidget(lB_usb        ,4,0,1,1,nullptr);
    wdgtGrid->addWidget(cbx_TSbirim   ,4,1,1,3,nullptr);
    wdgtGrid->addWidget(lB_bf        ,5,0,1,1,nullptr);
    wdgtGrid->addWidget(lE_TSbfiyat   ,5,1,1,3,nullptr);

    wdgtGrid->addWidget(lB_dr        ,6,0,1,1,nullptr);
    wdgtGrid->addWidget(cbx_TSdurum   ,6,1,1,3,nullptr);
    wdgtGrid->addWidget(lB_acklm        ,7,0,1,1,nullptr);
    wdgtGrid->addWidget(lE_TSaciklama   ,7,1,1,3,nullptr);


}
/*
void hC_TSNR:: view()
{
    qDebug()<<"tsnr view ";
    tb_view->table->setModel(tb_model);
    tb_slctnMdl = tb_view->table->selectionModel();

    tb_view->table->setColumnHidden(tb_model->fieldIndex(" mknstk_no"), true);
    tb_view->table->setColumnHidden(tb_model->fieldIndex("id_tsnr"), true);
    tb_view->table->setColumnHidden(tb_model->fieldIndex(" resim"), true);


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


void hC_TSNR:: map()
{
    qDebug()<<"tsnr map ";
    tb_mapper = new QDataWidgetMapper(this);
    tb_mapper->setModel(tb_model);

    //tb_modelapper->addMapping(tb_modelapper, mdl_mkn->fieldIndex(" mknstk_no"));
    tb_mapper->addMapping(lE_TSno, tb_model->fieldIndex("ts_no"));
    tb_mapper->addMapping(dE_TStarih , tb_model->fieldIndex("ts_tarih"));
    tb_mapper->addMapping(cbx_TSmalzeme , tb_model->fieldIndex("ts_malzeme"));
    tb_mapper->addMapping(lE_TSmiktar, tb_model->fieldIndex("ts_miktar"));
    tb_mapper->addMapping(cbx_TSbirim , tb_model->fieldIndex("ts_birim"));
    tb_mapper->addMapping(lE_TSbfiyat, tb_model->fieldIndex("ts_bfiyat"));
    tb_mapper->addMapping(cbx_TSdurum, tb_model->fieldIndex("ts_durum"));
    tb_mapper->addMapping(lE_TSaciklama , tb_model->fieldIndex("ts_aciklama"));

    tb_mapper->toFirst ();
}


*/




void hC_TSNR:: kntrl()
{

    qDebug()<<"  kontroltsnr ";

    // pB 001 yeni ekle
    connect(tb_view->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = tb_model->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        //dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! tb_model->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        tb_model->select();
        qDebug ()<<"ts 17";
        ////////////////////////////////
        /*
        q.bindValue(0, *TSdet_idno  );
        q.bindValue(1, lE_TSno->text() );
        q.bindValue(2, dE_TStarih->text ());
        q.bindValue(3, cbx_TSmalzeme->currentText ());
        q.bindValue(4, lE_TSmiktar->text() );
        q.bindValue(5, cbx_TSbirim->currentText ());
        q.bindValue(6, lE_TSbfiyat->text() );
        q.bindValue(7, cbx_TSdurum->currentText ());
        q.bindValue(8, lE_TSaciklama->text() );
        */
        QSqlQuery q;
        QString q_s;
        q_s="INSERT INTO dbtb_tasinir ( "
            "ts_tsnrdet_id, ts_no    , ts_tarih, ts_malzeme , ts_miktar, "
            "ts_birim   , ts_bfiyat, ts_durum, ts_aciklama  "
            " )"
            " values(?, ?, ?, ?, ?, ?, ?, ?, ? )";
        q.prepare(q_s);


        qDebug ()<<"ts 17***** " <<  *TSdet_idno  << " *****" << q.lastError();


        q.bindValue(0, *TSdet_idno  );
        q.bindValue(1, lE_TSno->text() );
        q.bindValue(2, dE_TStarih->text ());
        q.bindValue(3, 0 );
        q.bindValue(4, 0 );
        q.bindValue(5, 0 );
        q.bindValue(6, 0 );
        q.bindValue(7, 0 );
        q.bindValue(8, "" );

        q.exec();
        qDebug ()<<"ts 18";
        if (q.isActive())
        {
            qDebug () <<"Taşınır Yeni Kayıt Eklendi - "<< lE_TSno->text() << " -   Eklendi";
        }
        else
        {
            qDebug () << "Taşınır Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
        }



        tb_model->select();
        tb_view->setFocus();

        // tasinir ekle
        ///////////////////////////////////////////////////

        qDebug ()<<"ts 19";

    });

    // pB 002 yeni resim ekle
    connect(tb_view->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim( win_Rsm, tb_view, tb_model, tb_slctnMdl,
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
        // tasinir  kayıt sil
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("TAŞINIR KAYDI SİL"), QMessageBox::ActionRole);
        QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


        msgBox.setIcon(QMessageBox::Critical );
        msgBox.setWindowTitle("!! DİKKAT !!");
        msgBox.setText("!! DİKKAT !!\n"
                       "Taşınır kaydı silinecek ;\n"
                       "\n"
                       "Silmek istediğinizden eminmisiniz ?");
        msgBox.exec();



        if (msgBox.clickedButton() == pb_tmm)
        {
            // şimdi taşınır silelim
            QSqlQuery q_qry;
            QString s_qry;
            QModelIndex tasinir_indx = tb_view->table->currentIndex ();
            QString ino = tb_model->data
                    (tb_model->index
                     (tasinir_indx.row (),
                      tb_model->fieldIndex ("id_tasinir"))).toString ();

            s_qry = QString("DELETE FROM dbtb_tasinir "
                            "WHERE id_tasinir = %1").arg( ino );

            q_qry.exec (s_qry);
            if (q_qry.isActive ())
            {
                qDebug()<< " Taşınır Kaydı Silindi ";
                //  tb_model->submitAll ();
                tb_model->select ();
            }
            else
            {

                qDebug()<< " HATA - Taşınr Kaydı Silinemedi "
                        << q_qry.lastError ().text ();

            }
        }
        else if (msgBox.clickedButton() == pb_vzg)
        {
            msgBox.close(); // abort
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
    {tb_view->hC_TvPb ("son", tb_model, tb_mapper);
    });



    // pB 010 nav tuslari kontrol
    connect(tb_mapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {tb_view->hC_TvPb ("yenile", tb_model, tb_mapper);

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
        //     emit hC_TSNR::sgn(tb_view->table->model()->index( Index.row() ,
        //               tb_model->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  tb_slctnMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        tb_mapper->setCurrentModelIndex(Index);
    });


}




hC_TSNR::~hC_TSNR()
= default;



/*
QString hC_TSNR:: VTd ()
{
    QSqlQuery q;
    QString ct ,
            mesaj = "OK - Taşınır İstek",
            tB_Name = "sclk__dbtb";
    QStringList inserts;

    if ( ! VTKontrolEt::instance()->GetDB().tables().
         contains( tB_Name ))
    {
        ct ="CREATE TABLE IF NOT EXISTS "+ tB_Name +
                "("
                "ts_iedet_id   TEXT, "
                "ts_no   TEXT, "
                "ts_tarih      TEXT, "
                "ts_malzeme    INTEGER, "
                "ts_miktar       TEXT, "
                "ts_Birim       TEXT, "
                "ts_bfiyat     TEXT, "
                "ts_durum      TEXT, "
                "ts_aciklama   TEXT, "
                "ts_resim      BLOB, "
                "id_tasinir integer primary key  )"  ;

        if (!q.exec( ct ))
        {
            mesaj = "<br>HATA - Taşınır İstek Dosyası Oluşturulamadı  "
                    "<br>------------------------------------<br>"+
                    q.lastError().text() +
                    "<br>------------------------------------<br>";
        }
        else
        {
            mesaj = "OK - Taşınır İstek Dosyası YENİ Oluşturuldu ";
            inserts << "INSERT INTO " + tB_Name + " ( ts_iedet_id )"
                                                  " values( 1 )";


            foreach (QString qry , inserts)
            {
                if ( !q.exec(qry) )
                {
                    mesaj = mesaj + "<br>İLK Taşınır İstek Eklenemdi"+
                            "<br>------------------------------------<br>"+
                            q.lastError().text ()+
                            "<br>------------------------------------<br>";
                }
                else
                {
                    mesaj = mesaj + "<br>İLK Taşınır İstek eklendi.";
                }
            } // foreach
        }
    }
    qDebug ()<< mesaj;
    return mesaj ;




} //TAŞINIR





void hC_TSNR:: model()
{
    qDebug() << " tsnr mdl";
    QString indexField = "tsnr";
    QString tB_Name = " _dbtb";
    QStringList *tB_FieldList = new QStringList;

    tB_FieldList->append("İş Emri No");
    tB_FieldList->append("İş Emri Tarihi");
    tB_FieldList->append("Bölüm");
    tB_FieldList->append("Durum");
    tB_FieldList->append("Araç Giriş Tarihi");
    tB_FieldList->append("Araç Çıkış Tarihi");
    tB_FieldList->append("Yetkili");
    tB_FieldList->append("Yetkili");

    tb_model = new QSqlRelationalTableModel;
  hC_Rm hC_Rm ( &tB_Name,
                 tb_model,
                 &indexField ,
                 tB_FieldList) ;

}
*/
