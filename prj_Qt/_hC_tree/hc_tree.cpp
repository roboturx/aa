#include "hc_tree.h"

hC_Tree::hC_Tree(QWidget *parent)
    : QWidget{parent}
{
    qDebug()<<"hcT"<< "------ hctree ";
    view();
    modelSQL = new TreeSqlModel(this);
    hC_TreeView->setModel(modelSQL);
    for (int column = 0; column < modelSQL->columnCount(); ++column)
        hC_TreeView->resizeColumnToContents(column);
    hC_TreeView->expandAll();

    connect(butt_Exit, &QPushButton::clicked, this, &QApplication::quit);

    //  connect(butt_Act, &QPushButton::clicked, this, &hC_Tree::updateActions);
    connect(butt_insrow, &QPushButton::clicked, this, &hC_Tree::insertRow);
    connect(butt_inscol, &QPushButton::clicked, this, &hC_Tree::insertColumn);
    connect(butt_remrow, &QPushButton::clicked, this, &hC_Tree::removeRow);
    connect(butt_remcol, &QPushButton::clicked, this, &hC_Tree::removeColumn);
    connect(butt_Add, &QPushButton::clicked, this, &hC_Tree::insertChild);

    //const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();

    connect(hC_TreeView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &hC_Tree::updateActions);

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

    //  hC_TreeView->setAutoExpandDelay(1000);
    hC_TreeView->setIndentation(20);
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

bool hC_Tree::insertColumn()
{
    //   QAbstractItemModel *model = hC_TreeView->model();
    int column = hC_TreeView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = modelSQL->insertColumn(column + 1);
    if (changed)
        modelSQL->setHeaderData(column + 1,
                                Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);


    updateActions();

    return changed;
}

void hC_Tree::insertRow()
{
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    //   QAbstractItemModel *model = hC_TreeView->model();

    if (!modelSQL->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < modelSQL->columnCount(index.parent()); ++column) {
        const QModelIndex child = modelSQL->index(index.row() + 1, column, index.parent());
        modelSQL->setData(child, QVariant(tr("[No itemdata]")), Qt::EditRole);
    }
}

bool hC_Tree::removeColumn()
{
    //  QAbstractItemModel *model = hC_TreeView->model();
    const int column = hC_TreeView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    const bool changed = modelSQL->removeColumn(column);
    if (changed)
    {
        updateActions();
    }
    return changed;
}

void hC_Tree::removeRow()
{
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    //    QAbstractItemModel *model = hC_TreeView->model();
    if (modelSQL->removeRow(index.row(), index.parent()))
        updateActions();
}

void hC_Tree::updateActions()
{
    qDebug()<<"hcT"<< "--------------------------------------------------------update ";
    const QModelIndex index = hC_TreeView->selectionModel()->currentIndex();
    QModelIndex sblng_accName = index.siblingAtColumn(0);
    QModelIndex sblng_prntCode = index.siblingAtColumn(1);
    QModelIndex sblng_accCode = index.siblingAtColumn(2);

    m_prntCode = modelSQL->data (sblng_prntCode, Qt::DisplayRole ).toInt ();
    m_accCode = modelSQL->data (sblng_accCode , Qt::DisplayRole ).toInt ();
    m_accName = modelSQL->data (sblng_accName , Qt::DisplayRole ).toString ();

    qDebug()<<"hcT"<< m_prntCode
           << m_accCode
           << m_accName;

    const bool hasSelection = !hC_TreeView->selectionModel()->selection().isEmpty();
    butt_remrow->setEnabled(hasSelection);
    butt_remcol->setEnabled(hasSelection);

    const bool hasCurrent = hC_TreeView->selectionModel()->currentIndex().isValid();
    butt_insrow->setEnabled(hasCurrent);
    butt_inscol->setEnabled(hasCurrent);

    if (hasCurrent) {
        hC_TreeView->closePersistentEditor(hC_TreeView->selectionModel()->currentIndex());

        //  const int row = index.row();
        //  const int column = index.column();
        if (index.parent().isValid())
        {
            lab_status->setText(QString::number (m_prntCode));
            lab_status2->setText(QString::number (m_accCode));
            lab_status3->setText(m_accName);
        }
        else
        {
            lab_status->setText("ROOT "+QString::number (m_prntCode));
            lab_status2->setText(QString::number (m_accCode));
            lab_status3->setText(m_accName);
        }
    }
}




void hC_Tree::insertChild()
{
    const QModelIndex index = hC_TreeView->selectionModel()
            ->currentIndex();

    TreeSqlItem *item = modelSQL->getItem(index);


    qDebug()<<"hcT insertchild getitem row "
           << item->data(1).toInt()
           << item->data(2).toInt()
           << item->data(0).toString() <<"-"
              ;

    qDebug()<<"hcT "<<"insertchild üzerinde bulunulan row"
           << m_prntCode<<"-"
           << m_accCode
           << m_accName;

    if (modelSQL->columnCount(index) == 0)
    {
        if (!modelSQL->insertColumn(0, index))
            return;
    }

    if (!modelSQL->insertRow(0, index))
        return;

    bool ok;
    QString name = QInputDialog::getText(this,
                                         QString::number(m_accCode)+"=New ParentCode = " ,
                                         "Hesap Adı:",
                                         QLineEdit::Normal,
                                         tr("hesap adı giriniz"),
                                         &ok);
    if (ok && !name.isEmpty()) {
        // qDebug() << "Yeni Hesap Ekle" << name;

    }

    dBase db;
    db.addRecord(m_accCode, name);


    for (int column = 0;
         column < modelSQL->columnCount(index);
         ++column)
    {
        if (column == 0) // name
        {
            modelSQL->setData(index, QVariant( name ), Qt::EditRole);
        }
        if (column == 1) // parentcode
        {
            modelSQL->setData(index, QVariant( item->data(2) ), Qt::EditRole);
        }

        if (!modelSQL->headerData(column, Qt::Horizontal).isValid())
            modelSQL->setHeaderData(column, Qt::Horizontal,
                                    QVariant(tr("111")), Qt::EditRole);
    }

    hC_TreeView->selectionModel()->
            setCurrentIndex(modelSQL->index(0, 0, index),
                            QItemSelectionModel::ClearAndSelect);
    qDebug()<<"hcT "<<m_prntCode<<"---new mcde "<<m_accCode<<"  ---name "<<name;

    updateActions();
}
