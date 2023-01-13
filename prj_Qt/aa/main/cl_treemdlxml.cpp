#include "cl_treemdlxml.h"

/// fields :
/// change these for data manipulation
///
/// 001- -  in taskitem.h - field's variable declarations
/// 002- -  in taskitem.h - field variables' getters and setters
/// 003- fields, attributes, counts, enum
/// 004- make editable checkable etc.
/// 005- get data
/// 006- header data
/// 007- set data
/// 008- insert new record
/// 009- announce when data column changed
/// 010- read datas from XML file
/// 011- save XML file
/// 012- write datas to XML file
///



/// XML:003
/// fields, attributes, counts, enum
/// variables for XML file
///
namespace {

const QString TaskTag("ACCOUNT");
const QString NeZamanTag("WORKED");
const QString IlkAttribute("FROM: ");
const QString SonAttribute("TO: ");

/// fields for XML file
const QString HesapAdAttribute("AccNAME");
const QString AcklmAttribute("AccNOTE");
const QString TopluHesapAttribute("AccIsBATCH");
const QString HesapTuruAttribute("AccTYPE");
const QString UstHesapAttribute("AccsPARENT");
const QString HesapKodAttribute("AccCODE");
const QString DBFileAttribute("AccDBFile");

/// fields' count
const int ColumnCount = 7;
enum Column {HesapAd, HesapAciklama, Topluhesap,
              HesapTuru, UstHesap, HesapKod, DBFile };

const int MaxCompression = 9;
const QString MimeType = "application/vnd.qtrac.xml.task.z";
}

/// XML:004
/// make editable, checkable, drag-dropable
/// variables for XML file
///
Qt::ItemFlags cL_TreeMdlXML::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
    {

        if (index.column() == HesapAd ||
                index.column() == HesapAciklama ||
                index.column() == HesapTuru ||
                index.column() == DBFile ||
                index.column() == UstHesap         )
        {
            theFlags |= Qt::ItemIsSelectable|
                    Qt::ItemIsEnabled|
                    Qt::ItemIsEditable|
                    Qt::ItemIsDragEnabled|
                    Qt::ItemIsDropEnabled;
        }

        if (index.column() == Topluhesap)
        {
            theFlags |=  Qt::ItemIsUserCheckable|
                    Qt::ItemIsSelectable|
                    Qt::ItemIsEnabled|
                    Qt::ItemIsEditable|
                    Qt::ItemIsDragEnabled|
                    Qt::ItemIsDropEnabled;
        }
    }

    return theFlags;
}

/// XML:005
/// data
/// variables for XML file
///
QVariant cL_TreeMdlXML::data(const QModelIndex &index,
                                   int role) const
{
   // qDebug()<<"::Xmdl data";
    if (!rootItem || !index.isValid() || index.column() < 0 ||
            index.column() >= ColumnCount)
        return QVariant();


    if (TaskItem *item = itemForIndex(index))
    {

        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {

            switch (index.column()) {
            case HesapAd:

                return item->hesapAd();
            case HesapAciklama:   return item->hesapAcklm();
            case Topluhesap:return item->isTopluHesap();
            case HesapTuru: return item->hesapTuru();
            case UstHesap:  return item->ustHesap();
            case HesapKod:  return item->hesapKod();
                case DBFile:  return item->DBFile();
            default: Q_ASSERT(false);
            }
        }
        if (role == Qt::CheckStateRole &&
                index.column() == Topluhesap)
        {
            return static_cast<int>(item->
                 isTopluHesap() ? Qt::Checked : Qt::Unchecked);
        }
        if (role == Qt::TextAlignmentRole)
        {
            if (index.column() == DBFile )
            {
                return static_cast<int>(Qt::AlignVCenter|
                                        Qt::AlignCenter);
            }
            if (index.column() == HesapAd ||
                    index.column() == HesapAciklama ||
                    index.column() == HesapTuru ||
                    index.column() == UstHesap     )
            {
                return static_cast<int>(Qt::AlignVCenter|
                                        Qt::AlignLeft);
            }
            return static_cast<int>(Qt::AlignVCenter
                                    | Qt::AlignCenter);
        }
        if (role == Qt::DecorationRole)
           {
            if ( index.column() == 0 )
            {
                if (item->hesapTuru() == "Şirket" )
                {
                    return QIcon(":/rsm/icon/folder.png" );
                }
                if (item->hesapTuru() == "Konum" )
                {
                    return QIcon(":/rsm/icon/locations.png");
                }

                if (item->hesapTuru() == "Şahıs" )
                {
                    return QIcon(":/rsm/icon/person.jpeg");
                }
                if (item->hesapTuru() == "Aktif Hesap" )
                {
                    return QIcon(":/rsm/icon/nv_ekle2.png");
                }
                if (item->hesapTuru() == "Pasif Hesap" )
                {
                    return QIcon(":/rsm/icon/nv_eklee.png" );
                }
                if (item->hesapTuru() == "Araç" )
                {
                    return QIcon(":/rsm/icon/bobcat2.png");
                }
                if (item->hesapTuru() == "Emtia" )
                {
                    return QIcon(":/rsm/icon/plt.png");
                }
                if (item->hesapTuru() == "GayriMenkul" )
                {
                    return QIcon(":/rsm/icon/home.svg" );
                }
                if (item->hesapTuru() == "Menkul" )
                {
                    return QIcon(":/rsm/icon/candlestick.png");
                }
            }
        }

        if (role == Qt::DecorationRole
                && index.column() == HesapKod
                && timedItem
                && item == timedItem
                && !m_icon.isNull())
            return m_icon;

        if (  role == Qt::FontRole )
        {
            QFont font;
            font.setPointSize(12);
            return font;
        }

        if (  role == Qt::ForegroundRole )
            {
                if ( index.column() == 0 || index.column() == 3)
                {
                    if (item->hesapTuru() == "Konum" )
                    {
                        return QVariant( QColor( "#DFCFBE" ) );
                    }
                    if (item->hesapTuru() == "Şirket" )
                    {
                        return QVariant( QColor( "#EFC050" ) );
                    }
                    if (item->hesapTuru() == "Şahıs" )
                    {
                        return QVariant( QColor("#FAE03C" ) );
                    }
                    if (item->hesapTuru() == "Aktif Hesap" )
                    {
                        return QVariant( QColor( "#7FCDCD" ) );
                    }
                    if (item->hesapTuru() == "Pasif Hesap" )
                    {
                        return QVariant( QColor( "#E15D44" ) );
                    }
                    if (item->hesapTuru() == "Araç" )
                    {
                        return QVariant( QColor( "#88B04B" ) );
                    }
                    if (item->hesapTuru() == "Emtia" )
                    {
                        return QVariant( QColor( "#FF6F61" ) );
                    }
                    if (item->hesapTuru() == "GayriMenkul" )
                    {
                        return QVariant( QColor( "#92B6D5" ) );
                    }
                    if (item->hesapTuru() == "Menkul" )
                    {
                        return QVariant( QColor( "#D8AE47" ) );
                    }
//                    if (item->hesapTuru() == "" )
//                    {
//                        return QVariant( QColor(  ) );
//                    }
//                    if (item->hesapTuru() == "" )
//                    {
//                        return QVariant( QColor(  ) );
//                    }
//                    if (item->hesapTuru() == "" )
//                    {
//                        return QVariant( QColor(  ) );
//                    }
                }
                return QVariant( QColor( Qt::cyan ) );
            }

    }
    return QVariant();
}

/// XML:006
/// headers
/// variables for XML file
///
QVariant cL_TreeMdlXML::headerData(int section,
                               Qt::Orientation orientation, int role) const
{
   // qDebug()<<"::Xmdl headerdata";
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == HesapAd)
            return tr("Hesap Adı");
        else if (section == HesapAciklama)
            return tr("Açıklama");
        else if (section == Topluhesap)
            return tr("Toplu Hesap");
        else if (section == HesapTuru)
            return tr("Hesap Türü");
        else if (section == UstHesap)
            return tr("Üst Hesap");
        else if (section == HesapKod)
            return tr("Hesap Kodu");
        else if (section == DBFile)
            return tr("DBF");

    }
    return QVariant();
}

/// XML:007
/// setdata
/// variables for XML file
///
bool cL_TreeMdlXML::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
//    qDebug()<<"::Xmdl setdata";
    if (!index.isValid() ) //|| index.column() != HesapAd)
    {
        return false;
    }

    if (TaskItem *item = itemForIndex(index))
    {
        if (role == Qt::EditRole)
        {
            if (index.column() == HesapAd)
            {
                item->setHesapAd(value.toString());

            }
            if (index.column() == HesapAciklama)
            {
                item->setHesapAcklm(value.toString());
            }
            if (index.column() == HesapTuru)
            {
                item->setHesapTuru(value.toString());
            }
            if (index.column() == UstHesap)
            {
                item->setUstHesap(value.toString());
            }
            if (index.column() == DBFile)
            {
                item->setDBFile(value.toString());
            }
        }

        else if (role == Qt::CheckStateRole)
        {
            if (index.column() == Topluhesap )
            {
                item->setTopluHesap(value.toBool());
            }
        }
        else
        {
            return false;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/// XML:008
/// insertrows
/// variables for XML file
///
bool cL_TreeMdlXML::insertRows(int row, int count,
                           const QModelIndex &parent)
{
    qDebug()<<"::Xmdl insertrows";

    if (!rootItem)
    {

        rootItem = new TaskItem("T","T",0,"T","T",0);
        *pi_max_Hesap_ID = rootItem->hesapKod()  ;

 }

 TaskItem *parentItem = parent.isValid() ? itemForIndex(parent)
                                            : rootItem;
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i)
    {
         // hesaba en yüksek id yi ver

        ++*pi_max_Hesap_ID;

        // yeni bir hesap oluştur
        TaskItem *item = new TaskItem("","",0,"","",*pi_max_Hesap_ID) ;

        parentItem->insertChild(row, item);
    }
//    qDebug() << "cL_TreeMdlXML.cpp-::insertRows(*****************"
//                "end***************************";
    endInsertRows();
    return true;
}


/// XML:009
/// changing
/// variables for XML file
///
void cL_TreeMdlXML::announceItemChanged(TaskItem *item)
{
    qDebug()<<"::Xmdl announceitemchanged";

    if (item == rootItem)
        return;
    TaskItem *parent = item->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(item);

    QModelIndex startIndex = createIndex(row,
                 static_cast<int>(HesapAd), item);
    QModelIndex endIndex = createIndex(row,
                 static_cast<int>(UstHesap), item);

    emit dataChanged(startIndex, endIndex);

    // Update the parent & parent's parent etc too
    announceItemChanged(parent);
}

/// XML:010
/// read from XML
/// variables for XML file
///
void cL_TreeMdlXML::readTasks(QXmlStreamReader *reader,
                          TaskItem *task)
{
   // qDebug()<<"::Xmdl readtasks";
    //cB_hesapAds = new QComboBox{} ;
   // hesapListesi = new cls_Hesaplar;
   // QMap<QString, quint64> mapXML;
 //   listXML = new QList<QString,QString>;

    //mapXML = new QMap<QString, quint64>;

  //  pi_max_Hesap_ID = new quint64{};
   // *pi_max_Hesap_ID = 0;
    while (!reader->atEnd())
    {
        reader->readNext();
        /// İLK kayıt mı
        if (reader->isStartElement())
        {
            /// TASK lar
            if (reader->name() == TaskTag)
            {
                const quint64 hesapKod = reader->attributes()
                        .value(HesapKodAttribute).toULongLong ();

                if (hesapKod > *pi_max_Hesap_ID)
                {
                    // en büyük hesapkod u bul
                    *pi_max_Hesap_ID = hesapKod;
                }

                QString hesapAd = reader->attributes()
                        .value(HesapAdAttribute).toString();

                const QString hesapAcklm = reader->attributes()
                        .value(AcklmAttribute).toString();
                bool topluHesap = reader->attributes()
                        .value(TopluHesapAttribute).toInt();
                const QString hesapTuru = reader->attributes()
                        .value(HesapTuruAttribute).toString();
                const QString ustHesap = reader->attributes()
                        .value(UstHesapAttribute).toString();
                const QString DBFile = reader->attributes()
                        .value(DBFileAttribute).toString();

                task = new TaskItem(hesapAd, hesapAcklm,
                                    topluHesap, hesapTuru,
                                    ustHesap, hesapKod,
                                    DBFile, task);

                //// item ı listeye ekle
                ///  hspdetay transfer hesaplarda kullanılacak liste
                listXML<<task;
            }
            // NZAMAN lar
            else if (reader->name() == NeZamanTag) {
                const QDateTime start = QDateTime::fromString(
                            reader->attributes().value(IlkAttribute)
                            .toString(), Qt::ISODate);
                const QDateTime end = QDateTime::fromString(
                            reader->attributes().value(SonAttribute)
                            .toString(), Qt::ISODate);
                Q_ASSERT(task);
                task->addDateTime(start, end);
            }
        }
        // YOKSA son kayıt MI
        else if (reader->isEndElement())
        {
            if (reader->name() == TaskTag)
            {
                Q_ASSERT(task);
                task = task->parent();
                Q_ASSERT(task);
            }
        }
    } // while end
}

/// XML:011
/// save XML file
/// variables for XML file
///
void cL_TreeMdlXML::save(const QString &filename)
{
    qDebug()<<"::Xmdl save";
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw AQP::Error(tr("dosya adı belirtilmedi"));
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        throw AQP::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("KONUM");
    writer.writeAttribute("Sürüm", "2.0");
    writeTaskAndChildren(&writer, rootItem);
    writer.writeEndElement(); // KONUM
    writer.writeEndDocument();
}

/// XML:012
/// write to XML file
/// variables for XML file
///
void cL_TreeMdlXML::writeTaskAndChildren(QXmlStreamWriter *writer,
                                     TaskItem *task) const
{
    qDebug()<<"::Xmdl writetaskandchildren";
    if (task != rootItem) {
        writer->writeStartElement(TaskTag);

        writer->writeAttribute(HesapAdAttribute,
                               task->hesapAd());
        writer->writeAttribute(AcklmAttribute,
                               task->hesapAcklm());
        writer->writeAttribute(TopluHesapAttribute,
                               task->isTopluHesap() ? "1":"0");
        writer->writeAttribute(HesapTuruAttribute,
                               task->hesapTuru());
        writer->writeAttribute(UstHesapAttribute,
                               task->ustHesap());
        writer->writeAttribute(HesapKodAttribute,
                  QString::number (task->hesapKod() ));
        writer->writeAttribute(DBFileAttribute,
                               task->DBFile());


        QListIterator<
                QPair<QDateTime, QDateTime> > i(task->dateTimes());
        while (i.hasNext()) {
            const QPair<QDateTime, QDateTime> &dateTime = i.next();
            writer->writeStartElement(NeZamanTag);
            writer->writeAttribute(IlkAttribute,
                                   dateTime.first.toString(Qt::ISODate));
            writer->writeAttribute(SonAttribute,
                                   dateTime.second.toString(Qt::ISODate));
            writer->writeEndElement(); // WHEN
        }
    }
    foreach (TaskItem *child, task->children())
        writeTaskAndChildren(writer, child);
    if (task != rootItem)
        writer->writeEndElement(); // TASK
}

/////////////////////////////////////////////////////////////////
///
///
///
///
/////////////////////////////////////////////////////////////////



int cL_TreeMdlXML::rowCount(const QModelIndex &parent) const
{
   // qDebug()<<"::Xmdl rowcount";
    if (parent.isValid() && parent.column() != 0)
        return 0;
    TaskItem *parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}


int cL_TreeMdlXML::columnCount(const QModelIndex &parent) const
{
   // qDebug()<<"::Xmdl columncount";
    return parent.isValid() && parent.column() != 0 ? 0 : ColumnCount;
}


QModelIndex cL_TreeMdlXML::index(int row, int column,
                             const QModelIndex &parent) const
{
  //  qDebug()<<"::Xmdl index";
    if (!rootItem || row < 0 || column < 0 || column >= ColumnCount
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    TaskItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if (TaskItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}


TaskItem *cL_TreeMdlXML::itemForIndex(const QModelIndex &index) const
{
   // qDebug()<<"::Xmdl itemforindex";
    if (index.isValid()) {
        if (TaskItem *item = static_cast<TaskItem*>(
                    index.internalPointer()))
            return item;
    }
    return rootItem;
}


QModelIndex cL_TreeMdlXML::parent(const QModelIndex &index) const
{
    //qDebug()<<"::Xmdl parent ";
    if (!index.isValid())
        return QModelIndex();
    if (TaskItem *childItem = itemForIndex(index)) {
        if (TaskItem *parentItem = childItem->parent()) {
            if (parentItem == rootItem)
                return QModelIndex();
            if (TaskItem *grandParentItem = parentItem->parent()) {
                int row = grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}



bool cL_TreeMdlXML::removeRows(int row, int count,
                           const QModelIndex &parent)
{
    qDebug()<<"::Xmdl removeerows";
    if (!rootItem)
        return false;
    TaskItem *item = parent.isValid() ? itemForIndex(parent)
                                      : rootItem;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
        delete item->takeChild(row);
    endRemoveRows();
    return true;
}


QStringList cL_TreeMdlXML::mimeTypes() const
{
    qDebug()<<"::Xmdl mimetypes";
    return QStringList() << MimeType;
}


QMimeData *cL_TreeMdlXML::mimeData(const QModelIndexList &indexes) const
{
    qDebug()<<"::Xmdl mimedata";
    Q_ASSERT(indexes.count());
    if (indexes.count() != 1)
        return 0;
    if (TaskItem *item = itemForIndex(indexes.at(0))) {
        QMimeData *mimeData = new QMimeData;
        QByteArray xmlData;
        QXmlStreamWriter writer(&xmlData);
        writeTaskAndChildren(&writer, item);
        mimeData->setData(MimeType, qCompress(xmlData,
                                              MaxCompression));
        return mimeData;
    }
    return 0;
}


bool cL_TreeMdlXML::dropMimeData(const QMimeData *mimeData,
                             Qt::DropAction action, int row,
                             int column,
                             const QModelIndex &parent)
{
    qDebug()<<"::Xmdl dropmimedat";
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 ||
            !mimeData || !mimeData->hasFormat(MimeType))
        return false;
    if (TaskItem *item = itemForIndex(parent)) {
        emit stopTiming();
        QByteArray xmlData = qUncompress(mimeData->data(MimeType));
        QXmlStreamReader reader(xmlData);
        if (row == -1)
            row = parent.isValid() ? parent.row()
                                   : rootItem->childCount();
        beginInsertRows(parent, row, row);
        readTasks(&reader, item);
        endInsertRows();
        return true;
    }
    return false;
}


bool cL_TreeMdlXML::isChecked(const QModelIndex &index) const
{
    qDebug()<<"::Xmdl ischecked";
    if (!index.isValid())
        return false;
    return data(index, Qt::CheckStateRole).toInt() == Qt::Checked;
}


QModelIndex cL_TreeMdlXML::moveUp(const QModelIndex &index)
{
    qDebug()<<"::Xmdl moveup";
    if (!index.isValid() || index.row() <= 0)
        return index;
    TaskItem *item = itemForIndex(index);
    Q_ASSERT(item);
    TaskItem *parent = item->parent();
    Q_ASSERT(parent);
    return moveItem(parent, index.row(), index.row() - 1);
}


QModelIndex cL_TreeMdlXML::moveItem(TaskItem *parent, int oldRow,
                                int newRow)
{
    qDebug()<<"::Xmdl moveitem";
    Q_ASSERT(0 <= oldRow && oldRow < parent->childCount() &&
             0 <= newRow && newRow < parent->childCount());
    parent->swapChildren(oldRow, newRow);
    QModelIndex oldIndex = createIndex(oldRow, 0,
                                       parent->childAt(oldRow));
    QModelIndex newIndex = createIndex(newRow, 0,
                                       parent->childAt(newRow));
    emit dataChanged(oldIndex, newIndex);
    return newIndex;
}

QList<TaskItem *> cL_TreeMdlXML::getListXML() const
{
    foreach (TaskItem* item, listXML)
    {

        qDebug() <<"----------------"<< item->hesapAd ();
    }
    return listXML;
}

void cL_TreeMdlXML::setListXML(QList<TaskItem*> newListXML)
{
    listXML = newListXML;
}


QModelIndex cL_TreeMdlXML::moveDown(const QModelIndex &index)
{
    qDebug()<<"::Xmdl moveedown";
    if (!index.isValid())
        return index;
    TaskItem *item = itemForIndex(index);
    Q_ASSERT(item);
    TaskItem *parent = item->parent();
    int newRow = index.row() + 1;
    if (!parent || parent->childCount() <= newRow)
        return index;
    return moveItem(parent, index.row(), newRow);
}


QModelIndex cL_TreeMdlXML::cut(const QModelIndex &index)
{
    qDebug()<<"::Xmdl cut";
    if (!index.isValid())
        return index;
    delete cutItem;
    cutItem = itemForIndex(index);
    Q_ASSERT(cutItem);
    TaskItem *parent = cutItem->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(cutItem);
    Q_ASSERT(row == index.row());
    beginRemoveRows(index.parent(), row, row);
    TaskItem *child = parent->takeChild(row);
    endRemoveRows();
    Q_ASSERT(child == cutItem);
    child = 0; // Silence compiler unused variable warning

    if (row > 0) {
        --row;
        return createIndex(row, 0, parent->childAt(row));
    }
    if (parent != rootItem) {
        TaskItem *grandParent = parent->parent();
        Q_ASSERT(grandParent);
        return createIndex(grandParent->rowOfChild(parent), 0, parent);
    }
    return QModelIndex();
}


QModelIndex cL_TreeMdlXML::paste(const QModelIndex &index)
{
    qDebug()<<"::Xmdl paste";
    if (!index.isValid() || !cutItem)
        return index;
    TaskItem *sibling = itemForIndex(index);
    Q_ASSERT(sibling);
    TaskItem *parent = sibling->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(sibling) + 1;
    beginInsertRows(index.parent(), row, row);
    parent->insertChild(row, cutItem);
    TaskItem *child = cutItem;
    cutItem = 0;
    endInsertRows();
    return createIndex(row, 0, child);
}


QModelIndex cL_TreeMdlXML::promote(const QModelIndex &index)
{
    qDebug()<<"::Xmdl prğmğte";
    if (!index.isValid())
        return index;
    TaskItem *item = itemForIndex(index);
    Q_ASSERT(item);
    TaskItem *parent = item->parent();
    Q_ASSERT(parent);
    if (parent == rootItem)
        return index; // Already a top-level item

    int row = parent->rowOfChild(item);
    TaskItem *child = parent->takeChild(row);
    Q_ASSERT(child == item);
    TaskItem *grandParent = parent->parent();
    Q_ASSERT(grandParent);
    row = grandParent->rowOfChild(parent) + 1;
    grandParent->insertChild(row, child);
    QModelIndex newIndex = createIndex(row, 0, child);
    emit dataChanged(newIndex, newIndex);
    return newIndex;
}


QModelIndex cL_TreeMdlXML::demote(const QModelIndex &index)
{
    qDebug()<<"::Xmdl demote";
    if (!index.isValid())
        return index;
    TaskItem *item = itemForIndex(index);
    Q_ASSERT(item);
    TaskItem *parent = item->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(item);
    if (row == 0)
        return index; // No preceding sibling to move this under
    TaskItem *child = parent->takeChild(row);
    Q_ASSERT(child == item);
    TaskItem *sibling = parent->childAt(row - 1);
    Q_ASSERT(sibling);
    sibling->addChild(child);
    QModelIndex newIndex = createIndex(sibling->childCount() - 1, 0,
                                       child);
    emit dataChanged(newIndex, newIndex);
    return newIndex;
}


void cL_TreeMdlXML::setTimedItem(const QModelIndex &index)
{
    qDebug()<<"::Xmdl settimeditem";
    clearTimedItem();
    timedItem = itemForIndex(index);
    Q_ASSERT(timedItem);
    announceItemChanged(timedItem);
}


void cL_TreeMdlXML::clearTimedItem()
{
    qDebug()<<"::Xmdl cleartimeditem";
    if (timedItem) {
        TaskItem *item = timedItem;
        timedItem = 0;
        announceItemChanged(item);
    }
}


bool cL_TreeMdlXML::isTimedItem(const QModelIndex &index)
{
    qDebug()<<"::Xmdl istimeedata";
    return timedItem && itemForIndex(index) == timedItem;
}



void cL_TreeMdlXML::addDateTimeToTimedItem(const QDateTime &start,
                                       const QDateTime &end)
{
    qDebug()<<"::Xmdl adddatetime";
    if (timedItem) {
        timedItem->addDateTime(start, end);
        announceItemChanged(timedItem);
    }
}


void cL_TreeMdlXML::setIconForTimedItem(const QIcon &icon)
{
    qDebug()<<"::Xmdl seticonfor ";
    m_icon = icon;
    if (timedItem)
        announceItemChanged(timedItem);
}


void cL_TreeMdlXML::incrementEndTimeForTimedItem(int msec)
{
    qDebug()<<"::Xmdl incrementendtime";
    if (timedItem) {
        timedItem->incrementLastEndTime(msec);
        announceItemChanged(timedItem);
    }
}


void cL_TreeMdlXML::clear()
{
    qDebug()<<"::Xmdl clear";
    delete rootItem;
    rootItem = 0;
    delete cutItem;
    cutItem = 0;
    timedItem = 0;
    //reset();         //deleted for Qt5
    beginResetModel(); //added for Qt5
    endResetModel();   //added for Qt5
}


void cL_TreeMdlXML::load(const QString &filename)
{
    qDebug()<<"::Xmdl load";

    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw AQP::Error(tr("Dosya ismi belirtilmemiş"));
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
        throw AQP::Error(file.errorString());

    clear();
    qDebug () << "cL_TreeMdlXML::load     new root item";
    rootItem = new TaskItem("ROO","ROO",0,"ROO","ROOT",0);



    QXmlStreamReader reader(&file);
    readTasks(&reader, rootItem);
    if (reader.hasError())
        throw AQP::Error(reader.errorString());
    beginResetModel();
    endResetModel();
}


QStringList cL_TreeMdlXML::pathForIndex(const QModelIndex &index) const
{
    //qDebug()<<"::Xmdl pathforindex ";
    QStringList path;
    QModelIndex thisIndex = index;
    while (thisIndex.isValid()) {
        path.prepend(data(thisIndex).toString());
        thisIndex = thisIndex.parent();
    }
    return path;
}


QModelIndex cL_TreeMdlXML::indexForPath(const QStringList &path) const
{
    //qDebug()<<"::Xmdl indexforpath";
    return indexForPath(QModelIndex(), path);
}


QModelIndex cL_TreeMdlXML::indexForPath(const QModelIndex &parent,
                                    const QStringList &path) const
{
    //qDebug()<<"::Xmdl indexforpath xxx";
    if (path.isEmpty())
        return QModelIndex();
    for (int row = 0; row < rowCount(parent); ++row) {
        QModelIndex thisIndex = index(row, 0, parent);
        if (data(thisIndex).toString() == path.at(0)) {
            if (path.count() == 1)
                return thisIndex;
            thisIndex = indexForPath(thisIndex, path.mid(1));
            if (thisIndex.isValid())
                return thisIndex;
        }
    }
    return QModelIndex();
}
