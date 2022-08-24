#ifndef CLS_DLGT_COMBOBOX_H
#define CLS_DLGT_COMBOBOX_H

#include <QStyledItemDelegate>

class cls_dlgt_ComboBox : public QStyledItemDelegate
{
    Q_OBJECT
public:

    cls_dlgt_ComboBox(QObject *parent = nullptr);
    ~cls_dlgt_ComboBox();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};
#endif // CLS_DLGT_COMBOBOX_H




class cls_Hesaplar
{
public:
    cls_Hesaplar();
    ~cls_Hesaplar();

    void setHesaplar(const QString &hAd, const qint64 &hKod);
    QMap<QString, qint64> getHesaplar();
private:
    QMap<QString, qint64> map_hesapAdKod;
};
