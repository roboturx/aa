#ifndef INSERTREMOVEMODEL_H
#define INSERTREMOVEMODEL_H

#include "editablemodel.h"
#include <QtCore/qglobal.h>

class InsertRemoveModel : public EditableModel
{
    Q_OBJECT
public:
    InsertRemoveModel();
    ~InsertRemoveModel();

    void insertNode(Node *parentNode, int pos, Node *node);
    void removeNode(Node *node);
    void removeAllNodes();
    
    
};

#endif // INSERTREMOVEMODEL_H
