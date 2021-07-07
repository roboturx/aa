#ifndef EDITABLEMODEL_H
#define EDITABLEMODEL_H

#include "readonlymodel.h"
#include <QtCore/qglobal.h>

class EditableModel : public ReadOnlyModel
{
    Q_OBJECT
public:
    EditableModel();
    bool setData(QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags (const QModelIndex &index) const;
    
};

#endif // EDITABLEMODEL_H
