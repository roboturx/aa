#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

#include "database.h"
#include "treemodel.h"
//#include "dbexception.h"

TreeItemModel::TreeItemModel(QObject *parent) : QAbstractItemModel(parent), root(0)
{
    root = new TreeItem(0, QString("ROOT"), tr("Category"));
    root->parent = NULL;
    setupModel(root);
}

TreeItemModel::~TreeItemModel()
{
    delete root;
}

void TreeItemModel::setRoot(TreeItem *node)
{
    beginResetModel();
    delete root;
    root = node;
    endResetModel();
}

QModelIndex TreeItemModel::index(int row, int col, const QModelIndex &parent) const
{
    TreeItem *parentNode = categoryFromIndex(parent);
    return createIndex(row, col, parentNode->children.value(row));
}

TreeItem *TreeItemModel::categoryFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? static_cast<TreeItem *>(index.internalPointer()) : root;
}

int TreeItemModel::rowCount(const QModelIndex &parent) const
{
    return categoryFromIndex(parent)->children.count();
}

int TreeItemModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QModelIndex TreeItemModel::parent(const QModelIndex &index) const
{
    TreeItem *node = categoryFromIndex(index);
    if (!node)
        return QModelIndex();
    TreeItem *parentNode = node->parent;
    if (!parentNode)
        return QModelIndex();
    return parentNode == root ? QModelIndex() : createIndex(parentNode->row(), 0, parentNode);
}

bool TreeItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return true;
}

QVariant TreeItemModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || index.column() > 0)
        return QVariant();
    TreeItem *node = categoryFromIndex(index);
    if (!node)
        return QVariant();
    return QVariant(node->name);
}

QVariant TreeItemModel::headerData(int sec, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && sec == 0)
        return tr("CategoryXXX");
    return QVariant();
}

Qt::ItemFlags TreeItemModel::flags(const QModelIndex &index) const
{
    return !index.isValid() ? Qt::ItemIsEnabled : Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void TreeItemModel::setupModel(TreeItem *parent)
{
    if (!parent || !parent->children.isEmpty()) {
        qDebug() << "setup model çalıştırılamadı";
        return;
    }
///////////////////////////////////////    
    qDebug() << "DBASE ............................";
    DataBase db;
    qDebug() << "DBASE OK..........................";
///////////////////////////////////////    
    QSqlQuery q(QSqlDatabase::database("main"));
    if (q.prepare("select * from table11 ( contractor_tree.GetCategoryTree"
                  "  (:pid,:depth) )"))

    {
        q.bindValue(":pid", parent->getId());
        q.bindValue(":depth", 9999);
        if (q.exec()) {
            QList<TreeItem *> parents;
            QList<int> levels;
            parents << parent;
            levels << 1;

            while (q.next()) {
                int level = q.value(0).toInt();
                if (level > levels.last()) {
                    if (parents.last()->children.count() > 0) {
                        parents << parents.last()->children.value(parents.last()->children.count()
                                                                  - 1);
                        levels << level;
                    }
                } else {
                    while (level < levels.last() && parents.count() > 0) {
                        parents.pop_back();
                        levels.pop_back();
                    }
                }
                TreeItem *n = new TreeItem(q.value(1).toInt(),
                                           q.value(3).toString(),
                                           q.value(4).toString());
                n->parent = parents.last();
                parents.last()->children.append(n);
            }
            return;
        }
    }
    //throw DatabaseException( q.lastError() );
}

void TreeItemModel::refreshModel()
{
    TreeItem *newRoot = new TreeItem(0, QString(), tr("Item"));
    newRoot->parent = NULL;
    setupModel(newRoot);
    setRoot(newRoot);
}
