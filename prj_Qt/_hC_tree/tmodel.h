#ifndef TMODEL_H
#define TMODEL_H


#pragma once

#include <QAbstractItemModel>

class tModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit tModel(QObject *parent = nullptr);

    // Reimplementation of QAbstractItemModel methods
    int rowCount(const QModelIndex &index) const override;
    int columnCount(const QModelIndex &index) const override;
    QModelIndex index(const int row, const int column,
                      const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &childIndex) const override;
    QVariant data(const QModelIndex &index, const int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 const int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addRow(const QModelIndex &parent, const QVector<QVariant> &values);
    void removeRow(const QModelIndex &index);

private:
    struct Item
    {
        ~Item();

        // This could individual members, or maybe some other object that
        // contains the data we want to display/edit
        QVector<QVariant> values;

        // It is this information that the model needs to be able to answer
        // questions like "What's the parent QModelIndex of this QModelIndex?"
        QVector<Item *> children;
        Item *parent = nullptr;

        // Convenience method that's used in several places
        int rowInParent() const;
    };
    Item *m_root;
};


#endif // TMODEL_H
