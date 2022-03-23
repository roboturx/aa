#ifndef MODELLE_H
#define MODELLE_H

#include <QAbstractTableModel>
#include <QString>

const int ROWS = 3;
const int COLS = 4;


class Modelle : public QAbstractTableModel
{
    Q_OBJECT

public:
    Modelle(QObject *parent = nullptr);
    ~Modelle();


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QString m_gridData[ROWS][COLS];  //holds text entered into QTableView
signals:
    void editCompleted(const QString &);


};
#endif // MODELLE_H
