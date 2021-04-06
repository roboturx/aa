#include "mainwindow.h"
#include "ui_mainwindow.h"


// database
QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  ui->txt_id->hide();
    // QMainWindow::showMaximized();


    mydb.setDatabaseName("db.db");
    if (!mydb.open()) {
        qDebug() << "Cannot open database\n"
                    "Unable to establish a database connection.\n"
                    "This example needs SQLite support. Please read "
                    "the Qt SQL driver documentation for information how "
                    "to build it.\n\n"
                    "Click Cancel to exit.";

    } else {
        qDebug() << "Veritabanı BAĞLANDI...";
    }

    QSqlQuery query(mydb);
    query.prepare("CREATE TABLE telefon ("
	"id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
	"adsoyad TEXT,"
	"telefon TEXT,"
	"cep    TEXT,"
	"mail     TEXT   )"  );


    if (!query.exec()) {
        
        qDebug() << "Telefon tablosu oluşturulamadı " << query.lastError().text();
    }
    
    QMessageBox msg;
    if(!mydb.open()) {
        msg.setWindowTitle("Hata");
        msg.setText("Veritabanı Bağlantısı Yapılamadı.");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    } else {
        QString sql = "SELECT *FROM TELEFON";
        listele(sql);
    }
    ui->txt_adsoyad->setFocus();
}

// TABLOYU SORGUYA GORE LISTELE
void MainWindow::listele(QString sql) {
    QSqlQuery query(mydb);
    QSqlQueryModel *model = new QSqlQueryModel();
    //ui->txt_adsoyad->setText(sql);
    query.exec(sql);
    model->setQuery(query);
    ui->tbl_liste->setModel(model);
    ui->tbl_liste->hideColumn(0);
    ui->tbl_liste->setColumnWidth(1,200);
    ui->tbl_liste->setColumnWidth(4,140); // email alanı
}

// PENCERE GENISLERSE WIDGET ORTALA
void MainWindow::resizeEvent(QResizeEvent *){
    QPoint ort = ( MainWindow::window()->rect().center() - ui->widget->rect().center());
    ui->widget->move(ort);
}

MainWindow::~MainWindow(){
    delete ui;
}

// KAYIT ISLEMLERI
void MainWindow::on_btn_kaydet_clicked(){
    QMessageBox msg;
    QString adsoyad = ui->txt_adsoyad->text().trimmed();
    int id = ui->txt_id->text().toInt();
    //ui->txt_telefon->setText(QString::number(id));
    ui->txt_adsoyad->setText(adsoyad);
    if(adsoyad == "") {
        msg.setText("Ad Soyad Boş Bırakılamaz!");
        msg.exec();
    }
    else {
        QString telefon = ui->txt_telefon->text().trimmed();
        QString cep = ui->txt_cep->text().trimmed();
        QString mail = ui->txt_mail->text().trimmed();
        // guncelle
        if(id > 0) {
            QString sql = "UPDATE TELEFON SET adsoyad='"+adsoyad+"', "
                        "telefon='" + telefon + "', cep='"+cep+"', mail='"+mail+"'"
                        " WHERE id="+QString::number(id);

            QSqlQuery query(mydb);
            int rc = query.exec(sql);
            if(rc == true) {
                msg.setWindowTitle("İşlem Tamam");
                msg.setText("Güncellendi");
                msg.setIcon(QMessageBox::Information);
                msg.exec();
                sql = "SELECT *FROM TELEFON";
                listele(sql);

            } else {
                msg.setWindowTitle("Hata");
                msg.setText("HATA"+query.lastError().text());
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        }
        //kaydet
        else {
            QString sql = "INSERT INTO TELEFON VALUES(NULL,'"+adsoyad+"','"+telefon+"',"
                            "'"+cep+"','"+mail+"');";

            QSqlQuery query(mydb);
            int rc = query.exec(sql);
            if(rc == true) {
                sql = "SELECT *FROM TELEFON";
                listele(sql);
                QString son_id = query.lastInsertId().toString();
                ui->txt_id->setText(son_id);
                msg.setWindowTitle("İşlem Tamam");
                msg.setText("Kaydedildi");
                msg.setIcon(QMessageBox::Information);
                msg.exec();
            } else {
                msg.setWindowTitle("Hata");
                msg.setText("HATA"+query.lastError().text());
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        } // guncelle - kaydet
    } // else
}

void MainWindow::on_tbl_liste_doubleClicked(const QModelIndex &index){
    if (index.isValid()) {
        QString id = index.sibling(index.row(), 0).data().toString();
        qDebug() << "aaaaaaaaaaaaaaaaaa  " <<id;
        QString adsoyad = index.sibling(index.row(), 1).data().toString();
        QString telefon = index.sibling(index.row(), 2).data().toString();
        QString cep = index.sibling(index.row(), 3).data().toString();
        QString mail = index.sibling(index.row(), 4).data().toString();
        ui->txt_id->setText(id);
        ui->txt_adsoyad->setText(adsoyad);
        ui->txt_telefon->setText(telefon);
        ui->txt_cep->setText(cep);
        ui->txt_mail->setText(mail);
    }
}

void MainWindow::on_btn_yeni_clicked(){
    ui->txt_id->setText("");
    ui->txt_adsoyad->setText("");
    ui->txt_telefon->setText("");
    ui->txt_cep->setText("");
    ui->txt_mail->setText("");
    ui->txt_adsoyad->setFocus();
}

void MainWindow::on_btn_sil_clicked(){
    QMessageBox msgBox;

    int id = ui->txt_id->text().toInt();
    if(id <1 ) {
        msgBox.setWindowTitle("Hata");
        msgBox.setText("Kayıt Seçilmemiş.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }
    msgBox.setWindowTitle("İşlemi Onayla");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("İşlemin geri dönüşü yoktur. Emin misiniz?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes ) {
        QString sql = "DELETE FROM TELEFON WHERE id="+QString::number(id);
        QSqlQuery query(mydb);
        query.exec(sql);
        on_btn_yeni_clicked();
        sql = "SELECT *FROM TELEFON";
        listele(sql);
    }
}

void MainWindow::on_btn_sil_2_clicked(){
    exit(0);
}

void MainWindow::on_txt_ara_textChanged(const QString &arg1){
    QString sql = "SELECT *FROM TELEFON WHERE adsoyad LIKE '%"+arg1+"%'";
    listele(sql);
}
