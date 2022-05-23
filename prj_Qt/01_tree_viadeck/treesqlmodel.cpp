
#include "treesqlmodel.h"
#include "treesqlitem.h"

#include <QtWidgets>
#include <QSqlRecord>

//! [0]
TreeSqlModel::TreeSqlModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << tr("Parent Code") << tr("Account Code")<< tr("Account Name");
    rootItem = new TreeSqlItem(rootData);
    setupModelDataSQL(
        {
            "Şirket 1-Tab1-Tab2",
            "  Ş1Dal1-ş1d1tab1		-Ş1d1t2		-Ş1d		1t		3  ",
            "    Ş1D1d1			           ş1d1tab1    Ş1d1t2  Ş1d1t3  ",
            "  Designing a Component    			Creating a GUI for your application",
            "Creating a Dialog			How to create a dialog"
        }
        , rootItem);
    

    //   QString queryStr( "SELECT * FROM dbtb_accounts");
    //    setupModelData(queryStr, rootItem);
    //    for (const QString &header : headers)
    //        rootData << header;
    
    
    

}
//! [0]

//! [1]
TreeSqlModel::~TreeSqlModel()
{
    delete rootItem;
}
//! [1]


void TreeSqlModel::setupModelDataSQL(const QStringList &lines, TreeSqlItem *parent)
{
    ///lines içinde tablar olan satırlar --- records
    /// parents ın ilk itemı başlıklar

    QList<TreeSqlItem *> parents;
    QList<int> indentations;
    parents << parent;

    /// indentations parentcode lar
    /// ilk parentcode 0 olmalı
    indentations << 0;

    /// number kaç record olduğu
    int number = 0;
    qDebug()<<"#of lines "<<lines.count();

    QSqlQuery query("SELECT "
                    " f_parentCode, "
                    " f_AccountCode, "
                    " f_AccountName "
                    " FROM dbtb_accounts "
                    "ORDER BY f_accountCode ASC ");
    Q_ASSERT_X(query.isActive (),"dosya seçilemedi","setup");

    const QSqlRecord rec = query.record();

    /// tüm satırları-recordları incele
    /// -- dosya sonu gelinceye kadar
    while (query.next())/*(number < lines.count())*/
    {

        int intprnt_Code = query.value(
            rec.indexOf("f_parentCode")).toInt();
        QString prnt_Code = query.value(
                rec.indexOf("f_parentCode")).toString();
        QString acc_Code = query.value(
                rec.indexOf("f_AccountCode")).toString ();
        QString acc_Name = query.value(
                rec.indexOf("f_AccountName")).toString();
        qDebug()  << "######## "
                 << "pcode:"<< prnt_Code
                 << "acode:"<< acc_Code
                 << "aname:"<< acc_Name  ;
        int position = 0;

//        /// satırbaşında boşluk ara
//        /// boşluk 0 ise root itemdır
//        /// boşluk sayısı-position parentcode dur
//        /// -- record daki parentcode u al
//        while (position < lines[number].length())
//        {
////            qDebug()<<"lines ["<<number<<"].length "
////                     <<lines[number].length()
////                     <<"position"<<position
////                     <<lines[number].at(position);
//            if (lines[number].at(position) != ' ')// ' ')
//                break;
//            ++position;
//        }
//        /// positiondan sonraki kısım field lardır
//        ///
      //  const QString lineData = lines[number].mid(position).trimmed();
       // qDebug()<<"linedata" << lineData;

        /// fieldlar varsa
     //   if (!lineData.isEmpty())
       // {
            // Read the column data from the rest of the line.
            /// satırın geri kalanında tab ile
            /// ayrılmış kolonları bul
            /// -- recorddan fieldları getir
            const QStringList columnStrings =
                {prnt_Code , acc_Code,acc_Name};

            /// herbir kolonu columndata qvariantının içine at
            ///-- field ları columndataya ekle
            QList<QVariant> columnData;
            columnData.reserve(columnStrings.size());
            for (const QString &columnString : columnStrings)
                columnData << columnString;

            /// eğer satır başı boşluk sayısı
            /// boşluklar listinin sonuncusundan büyükse
            ///
            /// --- parentcode parents listesindeki
            /// --- son parentcode dan  büyükse
            /// --- yeni bir dal oluşacak
            if ( intprnt_Code > indentations.last())
            {
                /// The last child of the current parent is
                /// now the new parent
                /// unless the current parent has no children.

                /// şu anki parent ın son dalı
                /// eğer şu anki parent ın başka dalı yoksa
                /// yeni parent haline gelir

                /// eğer son parent itemın dal sayısı 0 dan
                /// fazlaysa
                if (parents.last()->childCount() > 0)
                {
                    ///+++ parent itemları listesine
                    /// ++
                    parents << parents.last()
                                   ->child(parents.last()
                                               ->childCount()-1);
                    indentations << intprnt_Code;
                }
            } else {
                while (intprnt_Code < indentations.last() &&
                       parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            /// Append a new item to the
            /// current parent's list of children.
            TreeSqlItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1
                                   , rootItem->columnCount());
            for (int column = 0;
                 column < columnData.size();
                 ++column)
                parent->child(parent->childCount() - 1)
                    ->setData(column, columnData[column]);

    }
}



void TreeSqlModel::setupModelData(const QStringList &lines,
                                  TreeSqlItem *parent)
{
    ///lines içinde tablar olan satırlar --- records
    /// parents ın ilk itemı başlıklar

    QList<TreeSqlItem *> parents;
    QList<int> indentations;
    parents << parent;

    /// indentations parentcode lar
    /// ilk parentcode 0 olmalı
    indentations << 0;

    /// number kaç record olduğu
    int number = 0;
    qDebug()<<"#of lines "<<lines.count();

    /// tüm satırları-recordları incele
    /// -- dosya sonu gelinceye kadar
    while (number < lines.count())
    {
        qDebug()  << "######## " << number;
        int position = 0;

        /// satırbaşında boşluk ara
        /// boşluk 0 ise root itemdır
        /// boşluk sayısı-position parentcode dur
        /// -- record daki parentcode u al
        while (position < lines[number].length())
        {
            qDebug()<<"lines ["<<number<<"].length "
                     <<lines[number].length()
                     <<"position"<<position
                     <<lines[number].at(position);
            if (lines[number].at(position) != ' ')// ' ')
                break;
            ++position;
        }
        /// positiondan sonraki kısım field lardır
        ///
        const QString lineData = lines[number].mid(position).trimmed();
        qDebug()<<"linedata" << lineData;

        /// fieldlar varsa
        if (!lineData.isEmpty())
        {
            // Read the column data from the rest of the line.
            /// satırın geri kalanında tab ile
            /// ayrılmış kolonları bul
            /// -- recorddan fieldları getir
            const QStringList columnStrings =
                lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);

            /// herbir kolonu columndata qvariantının içine at
            ///-- field ları columndataya ekle
            QList<QVariant> columnData;
            columnData.reserve(columnStrings.size());
            for (const QString &columnString : columnStrings)
                columnData << columnString;

            /// eğer satır başı boşluk sayısı
            /// boşluklar listinin sonuncusundan büyükse
            ///
            /// --- parentcode parents listesindeki
            /// --- son parentcode dan  büyükse
            /// --- yeni bir dal oluşacak
            if (position > indentations.last())
            {
                /// The last child of the current parent is
                /// now the new parent
                /// unless the current parent has no children.

                /// şu anki parent ın son dalı
                /// eğer şu anki parent ın başka dalı yoksa
                /// yeni parent haline gelir

                /// eğer son parent itemın dal sayısı 0 dan
                /// fazlaysa
                if (parents.last()->childCount() > 0)
                {
                    ///+++ parent itemları listesine
                    /// ++
                    parents << parents.last()
                                   ->child(parents.last()
                                               ->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() &&
                       parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            /// Append a new item to the
            /// current parent's list of children.
            TreeSqlItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1
                                   , rootItem->columnCount());
            for (int column = 0;
                 column < columnData.size();
                 ++column)
                parent->child(parent->childCount() - 1)
                    ->setData(column, columnData[column]);
        }
        ++number;
    }
}



//! [2]
int TreeSqlModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}
//! [2]

QVariant TreeSqlModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeSqlItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags TreeSqlModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
TreeSqlItem *TreeSqlModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeSqlItem *item = static_cast<TreeSqlItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeSqlModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex TreeSqlModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    //! [5]

    //! [6]
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeSqlItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [6]

bool TreeSqlModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeSqlModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeSqlModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeSqlItem *childItem = getItem(index);
    TreeSqlItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool TreeSqlModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeSqlModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeSqlItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int TreeSqlModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() > 0)
        return 0;

    const TreeSqlItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
//! [8]

bool TreeSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeSqlItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeSqlModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}
