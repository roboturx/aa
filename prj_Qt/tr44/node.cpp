
////////////////////////////////////////
#include "node.h"


Node::Node(const QString aText, Node *aParent)
{
    
    this->text = aText;
    this->parent = aParent;
}

Node::~Node()
{
    qDeleteAll(children);
}
/*
QVariant Node::data() const
{
    QVariant x = {"Nodata",0};
    return x;
}*/

