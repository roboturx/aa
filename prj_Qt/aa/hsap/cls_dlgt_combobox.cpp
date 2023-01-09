#include "cls_dlgt_combobox.h"
//#include "hsap/taskitem.h"

#include <QComboBox>

cls_dlgt_ComboBox::cls_dlgt_ComboBox(QObject *parent)
    : QStyledItemDelegate(parent)
{
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

    cb->addItem(QString("Konum"));
    cb->setItemData(0,QColor(Qt::blue),Qt::BackgroundRole);
    cb->addItem(QString("Şirket"));
    cb->setItemData(1,QColor(Qt::green),Qt::BackgroundRole);
    cb->addItem(QString("Şahıs"));
    cb->setItemData(2,QColor(Qt::yellow),Qt::BackgroundRole);
    cb->addItem(QString("Aktif Hesap"));
    cb->setItemData(3,QColor(Qt::red),Qt::BackgroundRole);
    cb->addItem(QString("Pasif Hesap"));
    cb->setItemData(4,QColor(Qt::cyan),Qt::BackgroundRole);
    cb->addItem(QString("Araç"));
    cb->setItemData(5,"0xff0000",Qt::BackgroundRole);
    cb->addItem(QString("Malzeme"));
    cb->setItemData(6,QColor(0,0,255),Qt::BackgroundRole);
    cb->addItem(QString("Gayrimenkul"));
    cb->setItemData(7,QColor(255,255,0),Qt::BackgroundRole);
    cb->addItem(QString("Menkul"));
    cb->setItemData(8,QColor("#7FCDCD"),Qt::BackgroundRole);

    return cb;
}


void cls_dlgt_ComboBox::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
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

