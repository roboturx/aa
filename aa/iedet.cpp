#include "iedet.h"

hC_IEDET::hC_IEDET(QWidget *parent) : QWidget (parent)
{
    qDebug ()<<"İş Emri Constructor";
    //************************************************************
    //*****************  İ Ş   E M R İ  **************************
}

void hC_IEDET::iedet_setup()
{
    qDebug() << "ie setup ";
    iedet_VTd();
    iedet_ui();

    IEDETmodel = new QSqlRelationalTableModel;
    iedet_model( IEDETmodel ) ;

    iedet_view();
    iedet_map();
    iedet_kntrl ();

}








void hC_IEDET::iedet_ui()
{
    auto *gLl = new QGridLayout(this);

    lbl_mkn = new QLabel("İş Emri ");
    lbl_IE = new QLabel("İş Emri Detay");

    IEDETtview = new hC_Tv;

   // gLl->addWidget(IEtview->table,      0, 0, 1, 1 );
    gLl->addWidget(IEDETtview,   0, 1, 1, 1 );
}
//////////////////////////////////
///
/// İŞ EMRİ DETAY
///
///
/// MODEL
/// VIEW


void hC_IEDET::iedet_model()
{
    IEDETmodel = new QSqlRelationalTableModel();
    IEDETmodel->setTable("dbtb_iedet");
    IEDETmodel->setEditStrategy(QSqlTableModel::OnFieldChange);

    ////  kolon başlıkları
    IEDETmodel->setHeaderData(
                IEDETmodel->fieldIndex("iedet_ie_no"),
                Qt::Horizontal, tr("İş Emri No"));
    IEDETmodel->setHeaderData(
                IEDETmodel->fieldIndex("iedet_aciklama"),
                Qt::Horizontal, tr("Yapılan İşin Cinsi"));
    IEDETmodel->setHeaderData(
                IEDETmodel->fieldIndex("iedet_tamiryeri"),
                Qt::Horizontal, tr("Tamirhane"));

    // Populate the model_mkstok
    if (!IEDETmodel->select())
    {
        qDebug () << IEDETmodel->lastError();
    }
}

void hC_IEDET::iedet_view()
{
    IEDETtview->table->setModel(IEDETmodel);
    IEDETtview->table->setSelectionMode(QAbstractItemView::SingleSelection);
    IEDETtview->table->setSelectionBehavior(QAbstractItemView::SelectItems);
    IEDETtview->table->resizeColumnsToContents();
    IEDETtview->table->resizeRowsToContents();
    IEDETtview->table->setCurrentIndex(IEDETmodel->index(0,0));

    /// mapper IEdet
    IEDETmapper = new QDataWidgetMapper(this);
    IEDETmapper->setModel(IEDETmodel);
   // mpp->setItemDelegate(new IEDelegate(this));

    //// kullanıcı bu alanları görmesin
    IEDETtview->table->setColumnHidden(
                IEDETmodel->fieldIndex("iedet_resim"), true);
    //IEDETtview->table->setColumnHidden(
      //          IEDETmodel->fieldIndex("iedet_iedet_no"), true);
    IEDETtview->table->setColumnHidden(
                IEDETmodel->fieldIndex("id_IEdet"), true);

    IEDETmodel->select();
    IEDETtview->table->setContextMenuPolicy(Qt::CustomContextMenu);
    // ie - iedet set filter

    /// ie sağ tık menu kontrollerini
    /// bu fonksiyonun içinden kontrol edelim



    bool sccs (true);
    sccs = connect(IEDETtview, &QTableView::customContextMenuRequested,this,
                   &hC_IE::rightMenu_IEDET);
    if (! sccs)
    {
        qDebug()<<"HATA - iedet Right Menu Connection";
    }
    else
    {
        qDebug()<<"iedet Right Menu Connected";
    }

}




void hC_IEDET::rowChanged_IEDET(QModelIndex IEDETindex)
{

    //QModelIndex index = IEDETtview->table->currentIndex();
    if (IEDETindex.isValid())
    {
        QSqlRecord record = IEDETmodel->record(IEDETindex.row());
        QString ieno = record.value("id_iedet").toString() ;
        ///setfiltr to tasinir and iscilik
        TSmodel->setFilter (QString("ts_iedet_id = '%1'" ).arg(ieno));
        TSmodel->select();
         TStview->setFocus();
        SCmodel->setFilter (QString("sc_iedet_id = '%1'" ).arg(ieno));
        SCmodel->select();
SCtview->setFocus();

        /*lbl_IE->
                setText((record.value("mknstk_no").toString()+
                         " - " +
                         record.value("ie_no").toString() ));*/
    } else
    {
//        TSmodel->setFilter("id_tasinir = -1");
  //      SCmodel->setFilter("id_iscilik = -1");
    }

 /*   // qDebug () <<"iedet row changggggedd 2";
    //IEDETmodel->select();
    TStview->setFocus();
    SCtview->setFocus();
    IEDETmodel->select();


    //qDebug () <<"iedet row changggggedd 3";
*/
     IEDETtview->table->setFocus();
}


void hC_IEDET::onmnIE_IEDETekle()
{
    IEno = new QString;
    IE_idno = new QString;
    //QSqlQuery q;
    //QVariant ino = " " ;
    QModelIndex index = IEtview->table->currentIndex();
    if (index.isValid())
    {
        // tv index i ile model de recordu bulduk
        QSqlRecord record = IEmodel->record(index.row());
        *IEno = record.value("ie_ie_no").toString();
        *IE_idno = record.value("id_IE").toString();

    }
    else
    {
        QMessageBox msgBox;
        QPushButton *pb_tmm = msgBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
        msgBox.setWindowTitle("İŞ EMRİ DETAY KAYIT EKLEME HATASI                               -");
        msgBox.setText("İş Emri Detay kaydı \n"
                       "Kayıt Eklenemedi ...");
        msgBox.setInformativeText("tV_ie index is invalid");        msgBox.exec();
        if (msgBox.clickedButton() == pb_tmm)
        {
            return;
        }
    }


    // IEdet_no yu oluşturalım
    // ioi_no + hangi yıl + yılın kaçıncı günündeyiz
    QString IEdet = *IEno;
    IEdet.append(":");
    IEdetno = new QString;
    *IEdetno = IEdet ;
    int IEdetcount = 1;

           qDebug ()<< "1 iedetcount :" << IEdetcount ;

    // how mny-- records?
    QSqlQuery query;
    query.prepare("SELECT * FROM dbtb_iedet ");
    if (!query.exec())
    {
        qDebug() << "SQL error: "<< query.lastError().text() << endl;
    }
    else
    {
        QString lttl ="" ;
        query.first();
        while (query.next())
        {
            lttl= query.value("iedet_iedet_no").toString();
            lttl.chop(3) ;
           qDebug ()<< "iecount :" << IEdetcount ;
            if (lttl == *IEno)
            {
                IEdetcount++;
                qDebug ()<< "iecount ---:" << IEdetcount ;
            }
        }
    }
    ///// yeni iedetno son hali
    *IEdetno += "0"+QString::number(IEdetcount);
    QWidget *wdgt_TSekle = new QWidget;
    wdgt_TSekle->setWindowTitle("İş Emri Detay Yeni Kayıt");
    wdgt_TSekle->setVisible(false);
    wdgt_TSekle->show();

    auto *TsL = new QGridLayout;
    wdgt_TSekle->setLayout(TsL);


    QLabel *lB_IEdetno = new QLabel("İş Emri Detay No ");
    TsL->addWidget(lB_IEdetno        ,0,0,1,1,nullptr);
    lE_IEdetno = new QLineEdit;
    lE_IEdetno->setText (*IEdetno);
    lE_IEdetno->setReadOnly (true);
    TsL->addWidget(lE_IEdetno   ,0,1,1,3,nullptr);
    lB_IEdetno->setBuddy(lE_IEdetno);

    QLabel *lB_acklm = new QLabel("Yapılacak İş");
    TsL->addWidget(lB_acklm        ,1,0,1,1,nullptr);
    lE_IEdetaciklama = new QLineEdit;
    TsL->addWidget(lE_IEdetaciklama   ,1,1,1,3,nullptr);
    lB_acklm->setBuddy(lE_IEdetaciklama);


    QLabel *lB_ust = new QLabel("Tamir Yeri");
    TsL->addWidget(lB_ust        ,3,0,1,1,nullptr);
    cbx_IEdetkurumicdis = new QComboBox;                    //dbtb_clsn
    QStringList tylist {"Atolye","Arazi","Yetkili Servis","Dış Servis"};
    cbx_IEdetkurumicdis->addItems(tylist);
    TsL->addWidget(cbx_IEdetkurumicdis   ,3,1,1,3,nullptr);
    lB_ust->setBuddy(cbx_IEdetkurumicdis);

    QLabel *lB_tm = new QLabel("Atolye Bolüm");
    TsL->addWidget(lB_tm        ,2,0,1,1,nullptr);
    cbx_IEdettamiryeri = new QComboBox;
    QStringList ablist {"Boya","Kaporta","Motor","Torna","Mekanik"};
    cbx_IEdettamiryeri->addItems(ablist);
    TsL->addWidget(cbx_IEdettamiryeri  ,2,1,1,3,nullptr);
    lB_tm->setBuddy(cbx_IEdettamiryeri );

    QLabel *lB_dr = new QLabel("İş Emri Detay Durum");
    TsL->addWidget(lB_dr        ,4,0,1,1,nullptr);
    cbx_IEdetdurum = new QComboBox;                    // dbtb_durum
    QStringList drlist { "-","Parça Bekliyor","Usta Bekliyor","Tamamlandı"};
    cbx_IEdetdurum->addItems(drlist);
    TsL->addWidget(cbx_IEdetdurum   ,4,1,1,3,nullptr);
    lB_dr->setBuddy(cbx_IEdetdurum);
//    QPushButton *pb_durum = new QPushButton("+");
//    TsL->addWidget(pb_durum   ,4,4,1,1,nullptr);
//    connect(pb_durum, &QPushButton::clicked, this, &hC_IE::clk_IEdetdurum);

    QLabel *lB_gt = new QLabel("Araç Giriş Tarihi");
    TsL->addWidget(lB_gt        ,7,0,1,1,nullptr);
    dE_IEdetgirtarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEdetgirtarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEdetgirtarihi->setMinimumDate(QDate(01, 01, 1900));
    dE_IEdetgirtarihi->setMaximumDate(QDate(valiDDate));
    dE_IEdetgirtarihi->setCalendarPopup(true);
    TsL->addWidget(dE_IEdetgirtarihi   ,7,1,1,3,nullptr);
    lB_gt->setBuddy(dE_IEdetgirtarihi);

    QLabel *lB_ct = new QLabel("Araç Çıkış Tarihi");
    TsL->addWidget(lB_ct        ,8,0,1,1,nullptr);
    dE_IEdetciktarihi = new QDateTimeEdit(QDate::currentDate());
    dE_IEdetciktarihi->setDisplayFormat("dd.MM.yyyy");
    dE_IEdetciktarihi->setMinimumDate(QDate (01, 01, 1900));
    dE_IEdetciktarihi->setMaximumDate(QDate ( valiDDate ));
    dE_IEdetciktarihi->setCalendarPopup(true);
    TsL->addWidget(dE_IEdetciktarihi   ,8,1,1,3,nullptr);
    lB_ct->setBuddy(dE_IEdetciktarihi);

    //QLabel *lB_rsm = new QLabel("Resim");


    QPushButton *pb_kaydet = new QPushButton("Yeni Ekle");
    connect (pb_kaydet, &QPushButton::clicked,
             this, & hC_IE::clk_IEDETbosh );
    TsL->addWidget(pb_kaydet        ,10,5,1,1,nullptr);

    QPushButton *TStview = new QPushButton("Vazgeç");
    connect (TStview, &QPushButton::clicked, wdgt_TSekle, &QWidget::close );
    TsL->addWidget(TStview        ,10,3,1,1,nullptr);




    //IEmapper->addMapping(IEmapper, mdl_mkn->fieldIndex("ie_mknstk_no"));
    IEDETmapper->addMapping(lE_IEdetno, IEDETmodel->fieldIndex("iedet_iedet_no"));
    IEDETmapper->addMapping(lE_IEdetaciklama , IEDETmodel->fieldIndex("iedet_aciklama"));
    IEDETmapper->addMapping(cbx_IEdettamiryeri , IEDETmodel->fieldIndex("iedet_tamiryeri"));
    IEDETmapper->addMapping(cbx_IEdetkurumicdis, IEDETmodel->fieldIndex("iedet_kurumicdis"));
    IEDETmapper->addMapping(cbx_IEdetdurum, IEDETmodel->fieldIndex("iedet_yap"));
    IEDETmapper->addMapping(dE_IEdetgirtarihi , IEDETmodel->fieldIndex("ie_gir_tar"));
    IEDETmapper->addMapping(dE_IEdetciktarihi , IEDETmodel->fieldIndex("ie_cik_tar"));
qDebug ()<< "::::: 5" ;
//        IEmapper->addMapping(cbx_ykt, mdl_mkn->fieldIndex("ie_resim"));


    QPushButton *pb_ilk = new QPushButton("İlk");
    connect( pb_ilk, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toFirst );
    TsL->addWidget( pb_ilk   ,10,1,1,1,nullptr);

    QPushButton *pb_pr = new QPushButton("Önceki");
    connect( pb_pr, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toPrevious );
    TsL->addWidget( pb_pr   ,10,2,1,1,nullptr);

    QPushButton *pb_lr = new QPushButton("Sonraki");
    connect( pb_lr, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toNext );
    TsL->addWidget( pb_lr   ,10,3,1,1,nullptr);

    QPushButton *pb_ls = new QPushButton("Son");
    connect( pb_ls, &QPushButton::clicked,
             IEDETmapper, &QDataWidgetMapper::toLast );
    TsL->addWidget( pb_ls   ,10,4,1,1,nullptr);


}


void hC_IEDET::clk_IEDETbosh()
{
    /// yeni IE iş emri detay kaydı için
    /// sahaları boşaltalım


    lE_IEdetno->setText( *IEdetno) ;
    lE_IEdetaciklama->setText ("");
    cbx_IEdettamiryeri->setCurrentText ("");
    cbx_IEdetkurumicdis->setCurrentText ("");
    cbx_IEdetdurum->setCurrentText ("");
    dE_IEdetgirtarihi->setDate(QDate::currentDate());
    dE_IEdetciktarihi->setDate(QDate::currentDate());


    hC_IE::IEDETekle();

}




void hC_IEDET::IEDETekle()
{

    ////////////////////////////////
    QSqlQuery q;
    QString q_s;
    q_s="INSERT INTO dbtb_IEdet ( "
        "iedet_ie_id, iedet_iedet_no   , iedet_aciklama, iedet_tamiryeri, "
        "iedet_durum, iedet_girtar , iedet_ciktar "
        " )"
        " values( ?, ?, ?, ?, ?, ?, ? )";
    q.prepare(q_s);

    q.bindValue(0, *IE_idno  );   //*IEno
    q.bindValue(1, *IEdetno );
    q.bindValue(2, lE_IEdetaciklama->text ());
    q.bindValue(3, cbx_IEdettamiryeri->currentText ());
    q.bindValue(4, cbx_IEdetkurumicdis->currentText ());

    q.bindValue(5, cbx_IEdetdurum->currentText ());
    q.bindValue(6, dE_IEdetgirtarihi->text());
    q.bindValue(7, dE_IEdetciktarihi->text());

    q.exec();

    if (q.isActive())
    {
        qDebug () <<"İş Emri Detay Yeni Kayıt Eklendi - "<< lE_IEdetno->text() << " -   Eklendi";
    }
    else
    {
        qDebug () << "İş Emri Detay Yeni Kayıt Eklenemedi - " << q.lastError().text() ;
    }




    IEDETmodel->select();
    IEDETtview->table->setFocus();

    // iş emri detay ekle
    ///////////////////////////////////////////////////



}






hC_IEDET::~hC_IEDET()
= default;



void hC_IE::sil_IEDET()
{
    // iedet  kayıt sil
    QMessageBox msgBox;
    QPushButton *pb_tmm = msgBox.addButton(tr("BU İŞ EMRİ DETAYINA AİT TÜM KAYITLARI SİL"), QMessageBox::ActionRole);
    QPushButton *pb_vzg = msgBox.addButton(tr("VAZGEÇ"),QMessageBox::ActionRole);


    msgBox.setIcon(QMessageBox::Critical );
    msgBox.setWindowTitle("!! DİKKAT !!");
    msgBox.setText("!! DİKKAT !!\n"
                   "İş Emri Detay Kaydını silerseniz;\n"
                   "bu İş Emri Detayına bağlı (taşınır ve işçilik)\n "
                   "tüm kayıtlarda silinir\n "
                   "\n"
                   "Silmek istediğinizden eminmisiniz ?");
    msgBox.exec();



    if (msgBox.clickedButton() == pb_tmm)
    {
        QSqlQuery q_qry;
        QString s_qry;
        QModelIndex iedet_indx = IEDETtview->table->currentIndex ();
        QString ino = IEDETmodel->data
                (IEDETmodel->index
                 (iedet_indx.row (),
                  IEDETmodel->fieldIndex ("id_iedet"))).toString ();

        s_qry = QString("DELETE FROM dbtb_iedet "
                        "WHERE id_iedet = %1").arg( ino );

        q_qry.exec (s_qry);
        if (q_qry.isActive ())
        {
            qDebug()<< " İş Rmri Detay Kaydı Silindi ";
            //   mdl_mkn->submitAll ();
            IEDETmodel->select ();
        }
        else
        {

            qDebug()<< " HATA - İş Emri Detay Kaydı Silinemedi "
                    << q_qry.lastError ().text ();

        }
    }
    else if (msgBox.clickedButton() == pb_vzg)
    {
        msgBox.close(); // abort
    }

}       /// iedet_sil


