#ifndef NODE_H
#define NODE_H

#include <QtCore/qglobal.h>

#include <QList>
#include <QString>


class Node
{
public:
    Node(const QString aText = "no Data", Node *aParent = 0);
    ~Node();

 //   QVariant data( ) const;
    QString text;
    Node *parent;
    QList<Node *> children;
};   
#endif // NODE_H
