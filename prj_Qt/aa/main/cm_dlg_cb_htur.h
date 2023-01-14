#ifndef cm_dlG_cb_hTur_H
#define cm_dlG_cb_hTur_H

#include <QStyledItemDelegate>
//#include <QSqlQuery>

//class cls_Hesaplar;

class cm_dlG_cb_hTur : public QStyledItemDelegate
{
    Q_OBJECT
public:

    cm_dlG_cb_hTur(QObject *parent = nullptr);
    ~cm_dlG_cb_hTur();

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;


};




class cls_Hesaplar
{
public:
    cls_Hesaplar();
    ~cls_Hesaplar();

    void setHesaplar(QString *hAd,  qint64 hKod);
    QMap<QString*, qint64> getHesaplar();
private:
    QMap<QString*, qint64> map_hesapAdKod;
};

#endif // cm_dlG_cb_hTur_H
