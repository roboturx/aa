#ifndef hC_Tree_H
#define hC_Tree_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTreeView>

class hC_Tree : public QWidget
{
    Q_OBJECT
public:
    explicit hC_Tree(QWidget *parent = nullptr);

    QTreeView *hC_TreeView;

public slots:
    void updateActions();
private slots:
    void insertChild();
    bool insertColumn();
    void insertRow();
    bool removeColumn();
    void removeRow();

signals:

};

#endif // hC_Tree_H
