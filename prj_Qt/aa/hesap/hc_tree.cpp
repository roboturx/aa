#include "hc_tree.h"

hC_tree::hC_tree(QWidget *parent )
    : QWidget{parent}
{
    const QStringList headers({tr("Title"), tr("Description")});
    treemodel = new TreeModel (headers,this);
    treeview = new QTreeView(this);
    treeview->setModel(treemodel);
    for (int column = 0; column < treemodel->columnCount(); ++column)
        treeview->resizeColumnToContents(column);

    connect(treeview->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &hC_tree::updateActions);
    //connect(exitAction, &QAction::triggered, qApp,
                    //&QCoreApplication::quit);


    QPushButton pB_show("show");
    QPushButton pB_insRow("Dal Ekle");
    QPushButton pB_insCol("Kolon Ekle");
    QPushButton pB_delRow("Dal Sil");
    QPushButton pB_delCol("Kolon Sil");
    QPushButton pB_insChild("Yaprak Ekle");


    connect(&pB_show, &QPushButton::clicked, this,
            &hC_tree::updateActions);
    connect(&pB_insRow, &QPushButton::clicked, this,
                     &hC_tree::insertRow);
    connect(&pB_insCol, &QPushButton::clicked, this,
                     &hC_tree::insertColumn);
    connect(&pB_delRow, &QPushButton::clicked, this,
                     &hC_tree::removeRow);
    connect(&pB_delCol, &QPushButton::clicked, this,
                     &hC_tree::removeColumn);
    connect(&pB_insChild, &QPushButton::clicked, this,
                     &hC_tree::insertChild);

    updateActions();
}



void hC_tree::insertChild()
{
    const QModelIndex index = treeview->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeview->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
    }

    treeview->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool hC_tree::insertColumn()
{
    QAbstractItemModel *model = treeview->model();
    int column = treeview->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

void hC_tree::insertRow()
{
    const QModelIndex index = treeview->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeview->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }
}

bool hC_tree::removeColumn()
{
    QAbstractItemModel *model = treeview->model();
    const int column = treeview->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    const bool changed = model->removeColumn(column);
    if (changed)
        updateActions();

    return changed;
}

void hC_tree::removeRow()
{
    const QModelIndex index = treeview->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeview->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void hC_tree::updateActions()
{
    const bool hasSelection = !treeview->selectionModel()->selection().isEmpty();
    //removeRowAction->setEnabled(hasSelection);
    //removeColumnAction->setEnabled(hasSelection);

    const bool hasCurrent = treeview->selectionModel()->currentIndex().isValid();
    //insertRowAction->setEnabled(hasCurrent);
    //insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        treeview->closePersistentEditor(treeview->selectionModel()->currentIndex());

        const int row = treeview->selectionModel()->currentIndex().row();
        const int column = treeview->selectionModel()->currentIndex().column();
        if (treeview->selectionModel()->currentIndex().parent().isValid())
            ; //statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            ;//statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}


