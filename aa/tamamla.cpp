#include "tamamla.h"
//#include "globals.h"
//#include <QMessageBox>
//#include <QPushButton>



/*
    cbx_IEdurum = new QComboBox(this);                    // dbtb_durum

    Tamamla *tmml_IEdurum = new Tamamla(":/rsm/mkndrm.txt");
    cbx_IEdurum->setEditable (true);
    cbx_IEdurum->setCompleter(tmml_IEdurum->completer);
*/



Tamamla::Tamamla(const QString& dosya)
{
    qDebug()<<"Tamamla class";
    completer = new QCompleter() ;
//    modelFromFile (dosya);
    completer->setModel(modelFromFile(dosya));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

}

QAbstractItemModel *Tamamla::modelFromFile(const QString& fileName)
{
    completer->setMaxVisibleItems(100);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

    QFile file(fileName);

    if (!file.open(QFile::ReadOnly))
    {
     qDebug()<< fileName <<" dosyası açılamadı"<<endl;
        return new QStringListModel(completer);
    }
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
        //qDebug()<<line.trimmed();
    }
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
        return new QStringListModel(words, completer);

}


///////////////////////////////////////////////////////////////
/// \brief Hata::Hata
///
///
/// class Hata
/// Gelen bilgileri Mesaj olarak ekrana yazar
///
/// Boş gelirse sadece hata yazar
///
Hata::Hata(const QString& Baslik, const QString& Mesaj, const QString& Aciklama="")
{
    QMessageBox msgBox ;
    QPushButton *pb_tmm = msgBox.addButton ("Tamam", QMessageBox::ActionRole);

    msgBox.setWindowTitle(Baslik);
    msgBox.setText(Mesaj);
    msgBox.setInformativeText(Aciklama);        msgBox.exec();
    if (msgBox.clickedButton() == pb_tmm)
    {
        return;
    }
}




