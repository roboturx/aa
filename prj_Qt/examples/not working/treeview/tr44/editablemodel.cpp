#include "editablemodel.h"

EditableModel::EditableModel()
{
    
}
///
bool EditableModel::setData(QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        Node *node = nodeForIndex(index);
        node->text = value.toString();
        QModelIndex topLeft = index;
        QModelIndex bottomRight = index;
        emit dataChanged (topLeft, bottomRight);
        return true;
    }
    return false;
}
////
Qt::ItemFlags EditableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = ReadOnlyModel::flags(index);
    if (index.isValid()) {
        return Qt::ItemIsEditable | defaultFlags;
    }
    return defaultFlags;
}
