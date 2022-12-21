#ifndef CLS_DLGT_COMBOBOX_H
#define CLS_DLGT_COMBOBOX_H

#include <QStyledItemDelegate>
#include <QSqlQuery>

class cls_dlgt_ComboBox : public QStyledItemDelegate
{
    Q_OBJECT
public:

    cls_dlgt_ComboBox( QMap<QString, qint64>* map, QObject *parent = nullptr);
    ~cls_dlgt_ComboBox();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    QMap<QString, qint64>* liste;

};





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

#endif // CLS_DLGT_COMBOBOX_H
