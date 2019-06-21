#include "ie.h"



hC_IE::hC_IE(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İş Emri Constructor";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IE::ie_setup()
{
    qDebug() << "ie setup ";
    ie_VTd();
    ie_ui();

    IEmodel = new QSqlRelationalTableModel;
    ie_model( IEmodel ) ;

    ie_view();
    ie_map();
    ie_kntrl ();

}


void hC_IE::ie_ui()
{


    qDebug() << "  clsn_ui";
    hC_IE::setWindowTitle ("İŞ EMRİ");
    hC_IE::showMaximized ();


    // ///////////////////////////////////////////////////////

    lB_ie  = new QLabel ("İŞ EMRİ");
    lB_rsm = new QLabel ("Resim");
    hC_Rs resim(lB_rsm);

    // ///////////////////////////////////////////////////////
    // views
    IEtview = new hC_Tv();

    /////*******************************************////////

    auto *gLl = new QGridLayout(this);

    IEtview = new hC_Tv;
    gLl->addWidget(IEtview->table,      0, 0, 1, 1 );
    gLl->addWidget(IEtview,   0, 1, 1, 1 );
}

void hC_IE::ie_view()
{
    qDebug()<<"ie view ";
    IEtview->table->setModel(IEmodel);
    IEselectionMdl = IEtview->table->selectionModel();

    //// kullanıcı bu alanları görmesin
    IEtview->table->setColumnHidden(IEmodel->fieldIndex("ie_mknstk_no"), true);
    IEtview->table->setColumnHidden(IEmodel->fieldIndex("id_IE"), true);
    IEtview->table->setColumnHidden(IEmodel->fieldIndex("ie_resim"), true);


}


void hC_IE::ie_map()
{
    /// mapper IE
    IEmapper = new QDataWidgetMapper(this);
    IEmapper->setModel(IEmodel);
    // mppMKN->setItemDelegate(new IEDelegate(this));
    IEmodel->select();

}




void hC_IE::ie_kntrl()
{
    /// iş emri ekran kontrolleri
    ///


    qDebug()<<"kontrolie";

    connect(IEtview->table->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_IE(QModelIndex)));

    ///
    connect(IEDETtview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_IEDET(QModelIndex)));

    /// ie column değiştiğinde modelindex de değişsin
       connect(IEtview->table->selectionModel(),
            SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
            IEmapper, SLOT(setCurrentModelIndex(QModelIndex)));

    /// ie row değiştiğinde modelindex de değişsin
    connect(IEtview->table->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            IEmapper, SLOT(setCurrentModelIndex(QModelIndex)));

/*    // ie - iedet set filter
    connect(TStview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_TASINIR(QModelIndex)));

    // ie - iedet set filter
    connect(SCtview->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(rowChanged_ISCILIK (QModelIndex)));

*/
    qDebug()<<"kontrolie sonu";
}



void hC_IE::ie_kntrl()
{


    // pB 001 yeni ekle
    connect(CLSNtview->pB_ekle, &QPushButton::clicked ,
            [this]()
    {

        QSqlRecord rec = CLSNmodel->record();
        // insert a new record (-1) with null date

        /// date does not take null value
        /// line 126 at QDateEdit declaration
        /// with the
        /// dT_dotar->setSpecialValueText ("  ");
        /// line
        /// an invalid date value represents " "
        ///
        dT_dotar->setDate( QDate::fromString( "01/01/0001", "dd/MM/yyyy" ) );


        if ( ! CLSNmodel->insertRecord(-1,rec))
        {
            qDebug() << "100111 -  HATA - Çalışan kayıt eklenemedi ";
        }
        else
            qDebug() << "100111 - Çalışan Kaydı eklendi ";
        CLSNmodel->select();

    });

    // pB 002 yeni resim ekle
    connect(CLSNtview->pB_eklersm, &QPushButton::clicked,
            [this]()
    {
        qDebug() << "new resim";
        hC_Rs resim(lB_rsm, CLSNtview, CLSNmodel, CLSNselectionMdl,
                    "resim", "ekle");
    });

    // -- 003   firm  değiştiğnde resmide değiştirelim
    connect(  CLSNselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]()
    {
        hC_Rs resim ( lB_rsm, CLSNtview, CLSNmodel, CLSNselectionMdl,
                      "resim", "değiştir" ) ;
    });


    // pB 004 yeni camera resim ekle


    // pB 005 sil

    connect(CLSNtview->pB_sil, &QPushButton::clicked,
            [this]()
    {
        QModelIndex sample =   CLSNtview->table->currentIndex();
        if( sample.row() >= 0 )
        {

            //         CLSNtview->table->selectionModel()->setCurrentIndex
            //             (sample,QItemSelectionModel::NoUpdate);

            QSqlRecord rec = CLSNmodel->record();
            QString val = rec.value(1).toString();// +" "+
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this,
                                        "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                // pmodel->beginRemoveColumn();
                CLSNmodel->removeRow(sample.row());
                //pmodel->endRemoveColumns();
                CLSNmodel->select();
            }
        }
    });

    // pB 006 ilk
    connect(CLSNtview->pB_ilk, &QPushButton::clicked ,
            [this]()
    {
        CLSNtview->hC_TvPb ("ilk", CLSNmodel, CLSNmapper);
    });

    // pB 007 önceki
    connect(CLSNtview->pB_ncki, &QPushButton::clicked,
            [this]()
    {
        CLSNtview->hC_TvPb ("ncki", CLSNmodel, CLSNmapper);
    });

    // pB 008 sonraki
    connect(CLSNtview->pB_snrki, &QPushButton::clicked,
            [this]()
    {
      CLSNtview->hC_TvPb ("snrki", CLSNmodel, CLSNmapper);
    });

    // pB 009 son
    connect(CLSNtview->pB_son, &QPushButton::clicked,
            [this]()
    {CLSNtview->hC_TvPb ("son", CLSNmodel, CLSNmapper);
    });



    // pB 010 nav tuslari kontrol
    connect(CLSNmapper, &QDataWidgetMapper::currentIndexChanged,
            [this]()
    {CLSNtview->hC_TvPb ("yenile", CLSNmodel, CLSNmapper);

    });

    // --- 011 row değiştiğinde 2 şey olsun
    connect(  CLSNselectionMdl , &QItemSelectionModel::currentRowChanged,
              [this]( QModelIndex Index )
    {
        // 011-01 mapper indexi ayarla
        CLSNmapper->setCurrentModelIndex(Index);
        if (Index.isValid())
        {

        }
        // 011-02 firmada row değiştiğinde firma ismini etrafa yayınlayalım
        //     emit hC_IE::sgn(CLSNtview->table->model()->index( Index.row() ,
        //               CLSNmodel->fieldIndex ("frm_unvan") ).data().toString() );
    });

    // --- 012 kolon değiştiğinde indexte değişsin
    connect(  CLSNselectionMdl ,
              &QItemSelectionModel::currentColumnChanged,
              [this]( QModelIndex Index )
    {
        CLSNmapper->setCurrentModelIndex(Index);
    });



}







//////////////////////////////////
///
/// İŞ EMRİ
///
///
/// MODEL
/// VIEW



void hC_IE::setup_ui()
{

        auto *gLl = new QGridLayout(this);

    lbl_mkn = new QLabel("İş Emri ");
    lbl_IE = new QLabel("İş Emri Detay");

    IEtview->table = new QTableView(this);
    IEDETtview = new QTableView;
    TStview = new QTableView;
    SCtview = new QTableView;

//     pB1 = new QPushButton("İş Emri");
//     pB2 = new QPushButton("İş Emri Detay ");
//     hL1 = new QHBoxLayout();
//     hL1->addWidget(lbl_mkn);
//     hL1->addStretch(2);
//     hL1->addWidget(pB1);
//     hL1->addWidget(pB2);


//     hL2 = new QHBoxLayout();
//     hL2->addWidget(lbl_IE);
//     pB3 = new QPushButton("Taşınır İstek Listesi");
//     hL2->addStretch(2);
//     hL2->addWidget(pB3);





//    gL->addLayout(hL1,        5, 0, 1, 4 );
    gLl->addWidget(IEtview->table,      0, 0, 1, 1 );
    gLl->addWidget(IEDETtview,   0, 1, 1, 1 );
 //   gL->addLayout(hL2,        2, 0, 1, 4 );
 //   gLl->addWidget(TStview, 0, 0 );
   // gLl->addWidget(SCtview, 1, 1 );
    // x->show();
    /*    connect( pB1, &QPushButton::clicked,
             this, &hC_IE::ekle_IEDET );
    connect( pB2, &QPushButton::clicked,
             this, &hC_IE::sil_IE );
    //connect( pB3, &QPushButton::clicked,
    //       this, &hC_IE::ieYaz );
    //connect( pB4, &QPushButton::clicked,
    //       this, &hC_IE::ieEkleDDD );
    //   connect( pB5, &QPushButton::clicked,
    //          this, &hC_IE::iedetEkle );
    connect( pB6, &QPushButton::clicked,
             this, &hC_IE::sil_IEDET );
    //connect( pB7, &QPushButton::clicked,
    //       this, &hC_IE::iedetayEkleDDD );
*/

}



///// SLOTS
///
///
///
///
/// ROWCHANGED

void hC_IE::rowChanged_IE(QModelIndex IEindex)
{

    if (IEindex.isValid())
    {
        QSqlRecord record = IEmodel->record(IEindex.row());
        QString ieno = record.value("id_ie").toString() ;
        //qDebug() <<"selected ie no : "<< ieno;
        IEDETmodel->setFilter (QString("iedet_ie_id = '%1'" ).arg(ieno));

        IEDETtview->setCurrentIndex(IEDETmodel->index(0,0));
        QModelIndex iedetindx = IEDETtview->currentIndex();
        hC_IE::rowChanged_IEDET(iedetindx);
        IEDETtview->setFocus ();
    }
    else
    {
        IEDETmodel->setFilter("ie_no = -1");
        TSmodel->setFilter("id_tasinir = -1");
        SCmodel->setFilter("id_iscilik = -1");

    }

    // IEtview->table->setFocus(); // detaya geç
    /*   IEDETmodel->select();
    IEDETtview->setFocus();    // iş emrine geri dön
*/
    IEtview->table->setFocus ();
}





hC_IE::~hC_IE()
= default;


void hC_IE::sil_IE()
{
    // ie  kayıt sil
    QMessageBox msgBox;
    QPushButton *pb_tmm = msgBox.addButton(tr("İŞ EMRİNİ SİL"), QMessageBox::ActionRole);
    QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


    msgBox.setIcon(QMessageBox::Critical );
    msgBox.setWindowTitle("!! DİKKAT !!");
    msgBox.setText("!! DİKKAT !!\n"
                   "İş emrini silerseniz;\n"
                   "bu İş Emri bağlı (iş emri detay, taşınır ve işçilik)\n "
                   "tüm kayıtlarda silinir\n "
                   "\n"
                   "Silmek istediğinizden eminmisiniz ?");
    msgBox.exec();



    if (msgBox.clickedButton() == pb_tmm)
    {
        /// önce bu iş emrine bağlı
        /// iedet
        /// iedet kayıtlarına bağlı
        /// taşınır
        /// işçilik kayıtlarını silelim



        // şimdi iş emrini silelim
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex ie_indx = IEtview->table->currentIndex ();
        QString ino = IEmodel->data
                (IEmodel->index
                 (ie_indx.row (),
                  IEmodel->fieldIndex ("id_IE"))).toString ();

        s_qry = QString("DELETE FROM dbtb_IE "
                        "WHERE id_IE = %1").arg( ino );

        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            qDebug()<< " İş Emri Kaydı Silindi ";
            IEmodel->submitAll ();
            IEmodel->select ();
        }
        else
        {

            qDebug()<< " HATA - İş Emri Kaydı Silinemedi "
                    << q_qry.lastError ().text ();

        }
    }
    else if (msgBox.clickedButton() == pb_vzg)
    {
        msgBox.close(); // abort
    }

}       ///      ie_sil




void hC_IE::ie_model()
{

    QString tableName = "dbtb_ie";
    QStringList fieldList;

    fieldList.append("İş Emri No");
    fieldList.append("İş Emri Tarihi");
    fieldList.append("Bölüm");
    fieldList.append("Durum");
    fieldList.append("Araç Giriş Tarihi");
    fieldList.append("Araç Çıkış Tarihi");
    fieldList.append("Yetkili");
    fieldList.append("Yetkili");


    IEmodel = new QSqlRelationalTableModel();
    IEmodel->setTable(tableName);
    IEmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    IEmodel->setSort(IEmodel->fieldIndex ("ie_tarih"),Qt::DescendingOrder );

    ////  kolon başlıkları

    for(int i = 1, j = 0; i < IEmodel->columnCount()-2; i++, j++)
    {
        IEmodel->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }


    // Populate the model_mkstok
    if (!IEmodel->select())
    {
        qDebug () << IEmodel->lastError();
    }
}
