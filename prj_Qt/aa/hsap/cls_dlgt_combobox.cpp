#include "cls_dlgt_combobox.h"
//#include "hsap/taskitem.h"

#include <QComboBox>

cls_dlgt_ComboBox::cls_dlgt_ComboBox(cls_Hesaplar *map, QObject *parent)
    : QStyledItemDelegate(parent)
{
   // liste = new cls_Hesaplar;
    map2 = map->getHesaplar ();
}


cls_dlgt_ComboBox::~cls_dlgt_ComboBox()
{
}


QWidget *cls_dlgt_ComboBox::createEditor(QWidget *parent,
              const QStyleOptionViewItem &option,
                const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);
    const QString row = QString::number (index.row());

    QMapIterator<QString*, qint64> i(map2);
    while (i.hasNext()) {
        i.next();
        cb->addItem( row + *i.key () +  QString::number (i.value ()) );
    }

//    cb->addItem(QString("one in row %1").arg(row));
//    cb->addItem(QString("two in row %1").arg(row));
//    cb->addItem(QString("three in row %1").arg(row));
    return cb;
}


void cls_dlgt_ComboBox::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    // get the index of the text in the combobox that matches
    // the current value of the item
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);
    // if it is valid, adjust the combobox
    if (cbIndex >= 0)
       cb->setCurrentIndex(cbIndex);
}


void cls_dlgt_ComboBox::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);
}



//////////////////////////////////////
/// \brief cls_Hesaplar::cls_Hesaplar
///
/// hesap listesini oluş tur
/// hspdty da transfer hesapları göster


cls_Hesaplar::cls_Hesaplar()
{

}

cls_Hesaplar::~cls_Hesaplar()
{

}

void cls_Hesaplar::setHesaplar(QString *hAd, qint64 hKod)
{

    //map_hesapAdKod.insert("1", 1 );
    map_hesapAdKod.insert(hAd, hKod);
}

QMap<QString*, qint64> cls_Hesaplar::getHesaplar()
{
    return map_hesapAdKod;
}
