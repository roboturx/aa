

#include "treesqlitem.h"
#include "treesqlmodel.h"
#include "hc_tree.h"
#include "dbase.h"

hC_Tree::hC_Tree(QWidget *parent)
    : QWidget{parent}
{
    //const QStringList headers01({tr("Title"), tr("Description")});
    //const QStringList headers02({tr("ID Mosel"), tr("SQL AccCode"), tr("GrpCode")});

    view();
    TreeSqlModel *modelSQL = new TreeSqlModel(this);
    hC_TreeView->setModel(modelSQL);
    for (int column = 0; column < modelSQL->columnCount(); ++column)
        hC_TreeView->resizeColumnToContents(column);
    hC_TreeView->expandAll();

    m_accName = new QString;
    m_accCode = new QString;
   // m_prntCode = new QString;

    connect(butt_Exit, &QPushButton::clicked, this, &QApplication::quit);

    connect(hC_TreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &hC_Tree::updateActions);




    //  connect(butt_Act, &QPushButton::clicked, this, &hC_Tree::updateActions);
    connect(butt_insrow, &QPushButton::clicked, this, &hC_Tree::insertRow);
    connect(butt_inscol, &QPushButton::clicked, this, &hC_Tree::insertColumn);
    connect(butt_remrow, &QPushButton::clicked, this, &hC_Tree::removeRow);
    connect(butt_remcol, &QPushButton::clicked, this, &hC_Tree::removeColumn);
    connect(butt_Add, &QPushButton::clicked, this, &hC_Tree::insertChild);

    updateActions();

}

void hC_Tree::view()
{

    butt_Exit = new QPushButton("Exit");
    butt_Add = new QPushButton("Ekle");
    butt_Act = new QPushButton("Act");
    butt_insrow = new QPushButton("rowEkle");
    butt_inscol = new QPushButton("colEkle");
    butt_remrow = new QPushButton("rowSil");
    butt_remcol = new QPushButton("colSil");
    lab_status = new QLabel;
    lab_status2 = new QLabel;
    lab_status3 = new QLabel;
    hC_TreeView = new QTreeView(this);
    hC_TreeView->setSelectionMode(QAbstractItemView::SingleSelection);
    hC_TreeView->resizeColumnToContents(0);
    hC_TreeView->setAutoExpandDelay(1000);
    hC_TreeView->setIndentation(10);
    hC_TreeView->setSelectionBehavior(QAbstractItemView::SelectItems);

    QGridLayout *lay_grid = new QGridLayout;
    this->setLayout(lay_grid);
    lay_grid->addWidget(butt_Add   ,  0, 0,  1, 1);
    lay_grid->addWidget(butt_insrow,  0, 1,  1, 1);
    lay_grid->addWidget(butt_inscol,  0, 2,  1, 1);
    lay_grid->addWidget(butt_remrow,  0, 3,  1, 1);
    lay_grid->addWidget(butt_remcol,  0, 4,  1, 1);
    lay_grid->addWidget(butt_Exit  ,  0, 5,  1, 1);
    lay_grid->addWidget(hC_TreeView,  1, 0, 10, 6);
    lay_grid->addWidget(lab_status , 12, 0,  1, 2);
    lay_grid->addWidget(lab_status2, 12, 2,  1, 2);
    lay_grid->addWidget(lab_status3, 12, 4,  1, 2);

}

void hC_Tree::insertChild()
{
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = hC_TreeView->model();

    qDebug()<< "prtt 1 "
            << model->index(index.row(),index.column()).data(Qt::DisplayRole).toString()
            << "prt 2 "
            << model->index(index.row(),index.column()+1).data(Qt::DisplayRole).toString()
            << "pat 3 "
            << model->index(index.row(),index.column()+2).data(Qt::DisplayRole).toString();



    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add task"), tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("hesap adı giriniz"),     &ok);
    if (ok && !name.isEmpty()) {
        qDebug() << "Yeni Hesap Ekle" << name;

    }

    for (int column = 0; column < model->columnCount(index); ++column)
    {
        const QModelIndex child = model->index(0, column, index);
        qDebug()<< model->index(0, column, index).data(Qt::DisplayRole).toString()
                <<model->headerData(column, Qt::Horizontal).toString();
        if (column == 0) // name
        {
            model->setData(child, QVariant( name ), Qt::EditRole);
        }
        if (column == 1) // parentcode
        {
            model->setData(child, QVariant( m_prntCode ), Qt::EditRole);
        }

        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal,
                                 QVariant(tr("111")), Qt::EditRole);
    }

    hC_TreeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                   QItemSelectionModel::ClearAndSelect);
    qDebug()<<"---mcde "<<m_prntCode<<"  ---name "<<name;
    dBase db;
    db.addRecord(m_prntCode, name);
    updateActions();
}

bool hC_Tree::insertColumn()
{
    QAbstractItemModel *model = hC_TreeView->model();
    int column = hC_TreeView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1,
                             Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

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
    butt_remrow->setEnabled(hasSelection);
    butt_remcol->setEnabled(hasSelection);

    const bool hasCurrent = hC_TreeView->selectionModel()->currentIndex().isValid();
    butt_insrow->setEnabled(hasCurrent);
    butt_inscol->setEnabled(hasCurrent);

    if (hasCurrent) {
        hC_TreeView->closePersistentEditor(hC_TreeView->selectionModel()->currentIndex());

        QModelIndex currentindx = hC_TreeView->selectionModel()->currentIndex();
        QModelIndex sibling = currentindx.siblingAtColumn(1);
        QModelIndex sibling2 = sibling.siblingAtColumn(2);

        const int row = currentindx.row();
        const int column = currentindx.column();
        if (currentindx.parent().isValid())
        {

            *m_accName = currentindx.data(Qt::DisplayRole).toString();
            *m_accCode = sibling.data(Qt::DisplayRole).toString();
            m_prntCode = sibling2.data(Qt::DisplayRole).toInt();

       //     lab_status->setText(tr("Position: (%1,%2)").arg(row).arg(column));

            lab_status->setText(*m_accName);
            lab_status2->setText(*m_accCode);
            lab_status3->setText(QString::number (m_prntCode));

        }
        else
        {
            lab_status->setText(tr("ROOT Position: (%1,%2) in top level").arg(row).arg(column));
        }
    }
}
