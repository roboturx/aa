#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QMessageBox::information(this,"AutoRun","Apllication is started!");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    // Otomatik çalıştırma klasörünün yolu
    QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0)
                            + QLatin1String("/autostart");
    // Otomatik çalıştırma dosyasının saklanacağı bir dizin olup olmadığını kontrol edin.

    QDir autorunDir(autostartPath);
    if(!autorunDir.exists()){
        // Eğer yoksa, o zaman yaratırız
        autorunDir.mkpath(autostartPath);
    }
    QFile autorunFile(autostartPath + QLatin1String("/AutorunLinux.desktop"));
    /* İşaretliyse, onay kutusunun durumunu kontrol ediyoruz,
     * ardından otomatik çalıştırmaya uygulamalar ekliyoruz.
     * Aksi takdirde, silin
     * */
    if(ui->checkBox->isChecked()) {
        // Ardından, otomatik çalıştırma dosyasının kendisinin varlığını kontrol ediyoruz.
        if(!autorunFile.exists()){

            /* Ardından, dosyayı açın ve gerekli verileri içine yazın.
             * QCoreApplication :: applicationFilePath () kullanılarak
             * yürütülebilir dosyanın yolunu belirtme
             * */
            if(autorunFile.open(QFile::WriteOnly)){

                QString autorunContent("[Desktop Entry]\n"
                                       "Type=Application\n"
                                       "Exec=" + QCoreApplication::applicationFilePath() + "\n"
                                       "Hidden=false\n"
                                       "NoDisplay=false\n"
                                       "X-GNOME-Autostart-enabled=true\n"
                                       "Name[en_GB]=AutorunLinux\n"
                                       "Name=AutorunLinux\n"
                                       "Comment[en_GB]=AutorunLinux\n"
                                       "Comment=AutorunLinux\n");
                QTextStream outStream(&autorunFile);
                outStream << autorunContent;
                // Dosyayı yürütmek de dahil olmak üzere erişim haklarını belirliyoruz,
                // aksi takdirde otomatik çalıştırma çalışmayacaktır


                autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                                       QFileDevice::WriteUser|QFileDevice::ReadUser);
                autorunFile.close();
            }
        }
    } else {
        // Otomatik çalıştırma dosyasını silin
        if(autorunFile.exists()) autorunFile.remove();
    }
}
