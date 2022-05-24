#include <QFile>
#include <QSqlQuery>

#include <QSqlQuery>

#include "treesqlmodel.h"
#include "hc_tree.h"

hC_Tree::hC_Tree(QWidget *parent)
    : QWidget{parent}
{
    const QStringList headers01({tr("Title"), tr("Description")});

    // const QStringList headers02({tr("ID Mosel"), tr("SQL AccCode"), tr("GrpCode")});

    QTreeView *hC_TreeView = new QTreeView(this);

            TreeSqlModel *modelSQL = new TreeSqlModel(this);
    hC_TreeView->setModel(modelSQL);
    for (int column = 0; column < modelSQL->columnCount(); ++column)
        hC_TreeView->resizeColumnToContents(column);
    hC_TreeView->expandAll();


//    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

//    connect(hC_TreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
//            this, &hC_Tree::updateActions);




//    connect(actionsMenu, &QMenu::aboutToShow, this, &hC_Tree::updateActions);
//    connect(insertRowAction, &QAction::triggered, this, &hC_Tree::insertRow);
//    connect(insertColumnAction, &QAction::triggered, this, &hC_Tree::insertColumn);
//    connect(removeRowAction, &QAction::triggered, this, &hC_Tree::removeRow);
//    connect(removeColumnAction, &QAction::triggered, this, &hC_Tree::removeColumn);
//    connect(insertChildAction, &QAction::triggered, this, &hC_Tree::insertChild);

    updateActions();

}

void hC_Tree::insertChild()
{
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = hC_TreeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No itemdata]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
    }

    hC_TreeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                   QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool hC_Tree::insertColumn()
{
    QAbstractItemModel *model = hC_TreeView->model();
    int column = hC_TreeView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

void hC_Tree::insertRow()
{
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = hC_TreeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No itemdata]")), Qt::EditRole);
    }
}

bool hC_Tree::removeColumn()
{
    QAbstractItemModel *model = hC_TreeView->model();
    const int column = hC_TreeView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    const bool changed = model->removeColumn(column);
    if (changed)
        updateActions();

    return changed;
}

void hC_Tree::removeRow()
{
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = hC_TreeView->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void hC_Tree::updateActions()
{
    const bool hasSelection = !hC_TreeView->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    const bool hasCurrent = hC_TreeView->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        hC_TreeView->closePersistentEditor(hC_TreeView->selectionModel()->currentIndex());

        const int row = hC_TreeView->selectionModel()->currentIndex().row();
        const int column = hC_TreeView->selectionModel()->currentIndex().column();
        if (hC_TreeView->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}
