
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QString mPath = "/home/";
    dirmodel = new QFileSystemModel (this);
    dirmodel->setFilter (QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath (mPath);

    ui->treeView->setModel (dirmodel);
    ui->treeView->resizeColumnToContents (1);



    filemodel = new QFileSystemModel (this);
   // filemodel->setFilter ( QDir::Files);
    filemodel->setRootPath (mPath);
    ui->listView->setModel (filemodel);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    // make dir
    QModelIndex index = ui->treeView->currentIndex ();
    if (!index.isValid ()) return;



    QString name = QInputDialog::getText (this,"Dizin Adı giriş",
                                                 "Yeni Dizin adı :");
    if (name.isEmpty ()) return;

    dirmodel->mkdir (index,name);

}

void Dialog::on_pushButton_2_clicked()
{
    // delete
    QModelIndex index = ui->treeView->currentIndex ();
    if (!index.isValid ()) return;

    if (dirmodel->fileInfo (index).isDir ())
    {
        //dir
        dirmodel->rmdir (index);
    }
    else
    {
        //file
        dirmodel->remove (index);
    }


}

void Dialog::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo (index).absoluteFilePath ();
    ui->listView ->setRootIndex (filemodel->setRootPath (sPath));
}
