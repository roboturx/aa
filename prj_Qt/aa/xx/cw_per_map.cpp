#include "cw_map_per.h"
#include "globals.h"

CW_per_MAP::CW_per_MAP()
{
    setWindowTitle(tr("Çalışan Bilgi Düzenleme"));
qDebug()<<"cls 1";
    setupView();
    qDebug()<<"cls 2";
    setupMap ();
    qDebug()<<"cls 3";
//    setupModel();


/// SLOTS
    connect(previousButton, &QPushButton::clicked,
            map_per, &QDataWidgetMapper::toPrevious);
    connect(nextButton, &QPushButton::clicked,
            map_per, &QDataWidgetMapper::toNext);
    connect(map_per, &QDataWidgetMapper::currentIndexChanged,
            this, &CW_per_MAP::updateButtons);

    connect(pb_ekle, &QPushButton::clicked,this,
            &CW_per_MAP::on_btnAdd_clicked);
    connect(pb_sil, &QPushButton::clicked,this,
            &CW_per_MAP::on_btnDelete_clicked);
    connect(pb_duzenle, &QPushButton::clicked,this,
            &CW_per_MAP::on_btnUpdate_clicked);
}


void CW_per_MAP::setupMap()
{

  /*  QSqlTableModel *relModel = mdl_per->relationModel(meslekIndex);
    qDebug() << "map 2";
    cb_meslek = new QComboBox;
    cb_meslek->setModel(relModel);
    cb_meslek->setModelColumn(relModel->fieldIndex("meslek"));
*/
qDebug()<<"cls 21";



if(VTKontrolEt::instance()->IsOpen())

    qDebug () <<"VT open in map_per for map_per";
    else
    qDebug () <<"VT NOT open in map_per for map_per";


//qDebug () << ;


    modell = new QSqlTableModel();
    modell->setTable("dbtb_clsn");
    //modell->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modell->select();
qDebug()<<"cls 22";

qDebug () << modell->index(0,1).data().toString();
qDebug () << modell->index(0,2).data().toString();
//modell->setData(ind ,"hacı");

    map_per = new QDataWidgetMapper();
    map_per->setModel(modell);
  //  map_per->setItemDelegate(new QSqlRelationalDelegate(this));
qDebug()<<"cls 23";
    map_per->addMapping(le_isim, 0);
qDebug()<<"cls 231";
    map_per->addMapping(le_soyad, modell->fieldIndex("soyad"));
    qDebug() << "map 15";
    map_per->addMapping(le_bolum, modell->fieldIndex("bolum"));
   // map_per->addMapping(cb_meslek, model->fieldIndex("meslek"));
    map_per->addMapping(le_gorev, modell->fieldIndex("gorev"));
    map_per->addMapping(le_adres, modell->fieldIndex("adres"));
    map_per->addMapping(le_sehir, modell->fieldIndex("sehir"));
    map_per->addMapping( le_tel_cep, modell->fieldIndex("tel_cep"));
    map_per->addMapping( le_tel_ev, modell->fieldIndex("tel_ev"));
    map_per->addMapping( le_eposta, modell->fieldIndex("eposta"));
    map_per->addMapping( le_username, modell->fieldIndex("username"));
    map_per->addMapping( le_password, modell->fieldIndex("password"));
    map_per->addMapping( le_yetki, modell->fieldIndex("yetki"));
    map_per->toFirst();
    qDebug() << "24";
}

void CW_per_MAP::loadClsn(const int index)
{

    QSqlQuery query;

    query.prepare(
                "SELECT * FROM "
                "dbtb_clsn "
                "ORDER BY "
                "kod_pr :index, 1"
                );

    query.bindValue(":index", index);

    if (query.exec()){
        while (query.next()) {
            if(query.isActive()){


                le_isim ->setText(query.value(1).toString());
                le_soyad->setText(query.value(2).toString());
                le_bolum->setText(query.value(3).toString());
                //cb_meslek->setText(query.value(4).toString());
                le_gorev->setText(query.value(5).toString());
                le_adres->setText(query.value(6).toString());
                le_sehir->setText(query.value(7).toString());
                le_tel_cep->setText(query.value(8).toString());
                le_tel_ev->setText(query.value(9).toString());
                le_eposta->setText(query.value(10).toString());
                le_username->setText(query.value(11).toString());
                le_password->setText(query.value(12).toString());
                le_yetki->setText(query.value(13).toString());



                qDebug() << "Çalışan Listelendi ...: " << index;
            }
        }
    } else {
        QMessageBox::warning(this, "Çalışan ", "HATA !!! ");
        qDebug() << query.lastError();
        return;
    }
}


//! [Set up the address type table]

//! [Slot for updating the buttons]
void CW_per_MAP::updateButtons(int row)
{
    previousButton->setEnabled(row > 0);
    nextButton->setEnabled(row < modell->rowCount() - 1);
}
//! [Slot for updating the buttons]



CW_per_MAP::~CW_per_MAP()
{

}


void CW_per_MAP::on_btnAdd_clicked()
{
    //QString barcode = ui->txtBarcode->text().trimmed();
    QString isim = le_isim->text().trimmed();
    QString soyad = le_soyad->text().trimmed();

    //if(this->CheckInputs()){
    if(VTKontrolEt::instance()->IsOpen()){

        QSqlQuery query;




        query.prepare(
                    "INSERT INTO dbtb_clsn "
                    "( "
                    "isim, soyad, "
                    "bolum, meslek, gorev, "
                    "adres, sehir, "
                    "tel_cep, tel_ev, eposta,"
                    "username, password, yetki"
                    ") "
                    "VALUES "
                    "("
                    ":isim, :soyad, "
                    ":bolum, :meslek, :gorev, "
                    ":adres, :sehir, "
                    ":tel_cep, :tel_ev, :eposta,"
                    ":username, :password, :yetki"
                    " )") ;

        query.bindValue(":isim", le_isim->text());
        query.bindValue(":soyad", le_soyad->text());
        query.bindValue(":bolum", le_bolum->text());
        //query.bindValue(":meslek", cb_meslek->itemData ());
        query.bindValue(":gorev", le_gorev->text() );
        query.bindValue(":adres", le_adres->text() );
        query.bindValue(":sehir", le_sehir->text() );
        query.bindValue(":tel_cep", le_tel_cep->text() );
        query.bindValue(":tel_ev", le_tel_ev ->text());
        query.bindValue(":eposta", le_eposta->text() );
        query.bindValue(":username", le_username->text() );
        query.bindValue(":password", le_password ->text());
        query.bindValue(":yetki", le_yetki ->text());



        if(query.exec()){
            if(query.isActive()){
               // this->Clear();
                //this->Refresh();
               // ui->cbID->addItem(barcode);
                QMessageBox::information(this, "Ürün", "Ürün başarıyla eklendi!");
                qDebug() << "Database query OK.";
                return;
            }
        } else {
            QMessageBox::warning(this, "Ürün", "Ürün eklenirken bir hata oluştu!");
            qDebug() << query.lastError();
            return;
        }
    } else {
        QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı kapalı!");
        qDebug() << "Database connection closed.";
        return;
    }
    //}
}

void CW_per_MAP::on_btnUpdate_clicked()
{
    //QString barcode = ui->txtBarcode->text().trimmed();
    //QString name = ui->txtName->text().trimmed();
    //QString description = ui->txtDescription->toPlainText().trimmed();

    /*if(QString::compare(barcode, ui->cbID->currentText(), Qt::CaseSensitive) != 0){
        QMessageBox::warning(this, "Ürün", "Güncellenmek istenen ürünün barkodu değiştirilemez!");
        ui->txtBarcode->setText(ui->cbID->currentText());
        return;
    }*/

    //if(this->CheckInputs()){
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Ürün", "Ürünü güncellemek istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        } else if (reply == QMessageBox::Yes){
            if(VTKontrolEt::instance()->IsOpen()){

                QSqlQuery query;

   /*             query.prepare(
                            "UPDATE "
                            "product "
                            "SET name = :name, description = :description , quantity = :quantity, purchasePrice = :purchasePrice, salePrice = :salePrice, dateUpdate = NOW() "
                            "WHERE barcode = :barcode"
                            );

                query.bindValue(":barcode", ui->cbID->currentText());
                query.bindValue(":name", name);
                query.bindValue(":description", description);
                query.bindValue(":quantity", ui->sbQuantity->value());
                query.bindValue(":purchasePrice", ui->sbPurchasePrice->value());
                query.bindValue(":salePrice", ui->sbSalePrice->value());

                if(query.exec()){
                    if(query.isActive()){
                        if(query.numRowsAffected() <= 0){
                            QMessageBox::warning(this, "Ürün", "Hata !!!");
                            qDebug() << query.lastError();
                            return;
                        }
                        this->Refresh();
                        this->LoadProduct(ui->cbID->currentText());
                        QMessageBox::information(this, "Ürün", "Ürün güncellenmesi sağlandı...");
                        qDebug() << "Database query OK.";
                        return;
                    }
                } else {
                    QMessageBox::warning(this, "Ürün", "Ürün güncellemede HATA !!!");
                    qDebug() << query.lastError();
                    return;
                }*/
            } else {
                QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı sağlanamdı !!!");
                qDebug() << "Veritabanı bağlantısı sağlanamdı !!!";
                return;
            }
        }
    //}
}

void CW_per_MAP::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Ürün", "Ürünü silmeyi onaylayın ... ", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    } else if (reply == QMessageBox::Yes){
        if(VTKontrolEt::instance()->IsOpen()){

            QSqlQuery query;

            query.prepare(
                        "DELETE FROM "
                        "dbtb_clsn "
                        "WHERE "
                        "kod_pr = :kod_pr"
                        );

            query.bindValue(":kod_pr", 2 );
                            //ui->cbID->currentText());

            if(query.exec()){
                if(query.isActive()){
                    if(query.numRowsAffected() <= 0){
                        QMessageBox::warning(this, "Ürün", "BARKOD hatası!");
                        qDebug() << query.lastError();
                        return;
                    }
                    //this->Clear();
                    //this->Refresh();
                    QMessageBox::information(this, "Ürün", "Ürün silindi!");
                    qDebug() << "Veritabanı sorgulama tamam ...";
                    //qDebug() << "Silinen Ürün......: " << ui->cbID->currentText();
                   // ui->cbID->removeItem(ui->cbID->currentIndex());
                    return;
                }
            } else {
                QMessageBox::warning(this, "Ürün", "Silme hatası !!!");
                qDebug() << query.lastError();
                return;
            }
        } else {
            QMessageBox::warning(this, "Ürün", "Veritabanı bağlantısı sağlanamadı !!!");
            qDebug() << "Veritabanı bağlantısı sağlanamadı !!!";
            return;
        }
    }
}





void CW_per_MAP::setupView()
{
    QLabel *lb_isim = new QLabel(tr("İ&sim"));
    QLineEdit *le_isim = new QLineEdit();
    //lb_isim->setBuddy(le_isim);

    QLabel *lb_soyad = new QLabel(tr("S&oyad"));
    QLineEdit *le_soyad = new QLineEdit();
    lb_soyad->setBuddy(le_soyad);

    QLabel *lb_bolum = new QLabel(tr("Bölü&m"));
    QLineEdit *le_bolum = new QLineEdit();
    lb_bolum->setBuddy(le_bolum);


    QLabel *lb_meslek = new QLabel(tr("M&eslek"));
    QComboBox *cb_meslek = new QComboBox();
    lb_meslek->setBuddy(cb_meslek);


    QLabel *lb_gorev = new QLabel(tr("Gö&rev"));
    QLineEdit *le_gorev = new QLineEdit();
    lb_gorev->setBuddy(le_gorev);

    QLabel *lb_adres = new QLabel(tr("Adre&s"));
    QLineEdit *le_adres = new QLineEdit();
    lb_adres->setBuddy(le_adres);

    QLabel *lb_sehir = new QLabel(tr("Şe&hir"));
    QLineEdit *le_sehir = new QLineEdit();
    lb_sehir->setBuddy(le_sehir);

    QLabel *lb_tel_cep = new QLabel(tr("Tel &1"));
    QLineEdit *le_tel_cep = new QLineEdit();
    lb_tel_cep->setBuddy(le_tel_cep);

    QLabel *lb_tel_ev = new QLabel(tr("Tel &2"));
    QLineEdit *le_tel_ev = new QLineEdit();
    lb_tel_ev->setBuddy(le_tel_ev);

    QLabel *lb_eposta = new QLabel(tr("E-&posta"));
    QLineEdit *le_eposta = new QLineEdit();
    lb_eposta->setBuddy(le_eposta);

    QLabel *lb_username = new QLabel(tr("Kullanıcı A&dı"));
    QLineEdit *le_username = new QLineEdit();
    lb_username->setBuddy(le_username);

    QLabel *lb_password = new QLabel(tr("Şi&fre"));
    QLineEdit *le_password = new QLineEdit();
    lb_password->setBuddy(le_password);

    QLabel *lb_yetki = new QLabel(tr("&Yetki"));
    QLineEdit *le_yetki = new QLineEdit();
    lb_yetki->setBuddy(le_yetki);

    nextButton = new QPushButton(tr("So&nraki"));
    previousButton = new QPushButton(tr("Önce&ki"));
    pb_ekle = new QPushButton(tr("&Ekle"));
    pb_sil= new QPushButton(tr("&Sil"));
    pb_duzenle= new QPushButton(tr("&Düzenle"));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(lb_isim      , 0, 0, 1, 1);
    layout->addWidget(le_isim      , 0, 1, 1, 2);
    layout->addWidget(lb_soyad     , 0, 3, 1, 1);
    layout->addWidget(le_soyad     , 0, 4, 1, 2);

    layout->addWidget(lb_meslek    , 1, 0, 1, 1);
    layout->addWidget(cb_meslek    , 1, 1, 1, 5);

    layout->addWidget(lb_bolum     , 2, 0, 1, 1);
    layout->addWidget(le_bolum     , 2, 1, 1, 2);
    layout->addWidget(lb_gorev     , 2, 3, 1, 1);
    layout->addWidget(le_gorev     , 2, 4, 1, 2);

    layout->addWidget(lb_adres     , 3, 0, 1, 1);
    layout->addWidget(le_adres     , 3, 1, 1, 5);
    layout->addWidget(lb_sehir     , 4, 0, 1, 1);
    layout->addWidget(le_sehir     , 4, 1, 1, 2);
    layout->addWidget(lb_tel_cep   , 5, 0, 1, 1);
    layout->addWidget(le_tel_cep   , 5, 1, 1, 2);
    layout->addWidget(lb_tel_ev    , 5, 3, 1, 1);
    layout->addWidget(le_tel_ev    , 5, 4, 1, 2);
    layout->addWidget(lb_eposta    , 6, 0, 1, 1);
    layout->addWidget(le_eposta    , 6, 1, 1, 5);
    layout->addWidget(lb_username  , 7, 0, 1, 1);
    layout->addWidget(le_username  , 7, 1, 1, 2);
    layout->addWidget(lb_password  , 7, 3, 1, 1);
    layout->addWidget(le_password  , 7, 4, 1, 2);
    layout->addWidget(lb_yetki     , 8, 0, 1, 1);
    layout->addWidget(le_yetki     , 8, 1, 1, 2);

    layout->addWidget(previousButton, 0, 6, 1, 1);
    layout->addWidget(nextButton    , 1, 6, 1, 1);
    layout->addWidget(pb_ekle       , 6, 6, 1, 1);
    layout->addWidget(pb_sil        , 7, 6, 1, 1);
    layout->addWidget(pb_duzenle    , 8, 6, 1, 1);
    setLayout(layout);
}
