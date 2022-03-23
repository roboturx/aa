#ifndef MODELLE_H
#define MODELLE_H

#include <QAbstractTableModel>
#include<QTimer>



class Modelle : public QAbstractTableModel
{
    Q_OBJECT

public:
    Modelle(QObject *parent = nullptr);
    ~Modelle();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


    int cc();
    int count;
    QTimer* timer;


private slots:
    void timerHit();

};
#endif // MODELLE_H
