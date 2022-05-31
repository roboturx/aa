
// https://riptutorial.com/qt/example/17086/a-simple-tree-model
#include "tmodel.h"

// Adapt this to own needs
static constexpr int COLUMNS = 3;

tModel::Item::~Item()
{
    qDeleteAll(children);
}
int tModel::Item::rowInParent() const
{
    if (parent) {
        return parent->children.indexOf(const_cast<Item *>(this));
    } else {
        return 0;
    }
}

tModel::tModel(QObject *parent)
    : QAbstractItemModel(parent), m_root(new Item) {}

int tModel::rowCount(const QModelIndex &parent) const
{
    // Parent being invalid means we ask for how many rows the root of the
    // model has, thus we ask the root item
    // If parent is valid we access the Item from the pointer stored
    // inside the QModelIndex
    return parent.isValid()
               ? static_cast<Item *>(parent.internalPointer())->children.size()
               : m_root->children.size();
}
int tModel::columnCount(const QModelIndex &parent) const
{
    return COLUMNS;
}

QModelIndex tModel::index(const int row, const int column,
                             const QModelIndex &parent) const
{
    // hasIndex checks if the values are in the valid ranges by using
    // rowCount and columnCount
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    // In order to create an index we first need to get a pointer to the Item
    // To get started we have either the parent index, which contains a pointer
    // to the parent item, or simply the root item

    Item *parentItem = parent.isValid()
                           ? static_cast<Item *>(parent.internalPointer())
                           : m_root;

    // We can now simply look up the item we want given the parent and the row
    Item *childItem = parentItem->children.at(row);

    // There is no public constructor in QModelIndex we can use, instead we need
    // to use createIndex, which does a little bit more, like setting the
    // model() in the QModelIndex to the model that calls createIndex
    return createIndex(row, column, childItem);
}
QModelIndex tModel::parent(const QModelIndex &childIndex) const
{
    if (!childIndex.isValid()) {
        return QModelIndex();
    }

    // Simply get the parent pointer and create an index for it
    Item *parentItem = static_cast<Item*>(childIndex.internalPointer())->parent;
    return parentItem == m_root
               ? QModelIndex() // the root doesn't have a parent
               : createIndex(parentItem->rowInParent(), 0, parentItem);
}

QVariant tModel::data(const QModelIndex &index, const int role) const
{
    // Usually there will be more stuff here, like type conversion from
    // QVariant, handling more roles etc.
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    Item *item = static_cast<Item *>(index.internalPointer());
    return item->values.at(index.column());
}
bool tModel::setData(const QModelIndex &index, const QVariant &value,
                        const int role)
{
    // As in data there will usually be more stuff here, like type conversion to
    // QVariant, checking values for validity etc.
    if (!index.isValid() || role != Qt::EditRole) {
        return false;
    }
    Item *item = static_cast<Item *>(index.internalPointer());
    item->values[index.column()] = value;
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}
Qt::ItemFlags tModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    } else {
        return Qt::NoItemFlags;
    }
}

// Simple add/remove functions to illustrate {begin,end}{Insert,Remove}Rows
// usage in a tree model
void tModel::addRow(const QModelIndex &parent,
                       const QVector<QVariant> &values)
{
    Item *parentItem = parent.isValid()
                           ? static_cast<Item *>(parent.internalPointer())
                           : m_root;
    beginInsertRows(parent,
                    parentItem->children.size(), parentItem->children.size());
    Item *item = new Item;
    item->values = values;
    item->parent = parentItem;
    parentItem->children.append(item);
    endInsertRows();
}
void tModel::removeRow(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    Item *item = static_cast<Item *>(index.internalPointer());
    Q_ASSERT(item != m_root);
    beginRemoveRows(index.parent(), item->rowInParent(), item->rowInParent());
    item->parent->children.removeOne(item);
    delete item;
    endRemoveRows();
}
