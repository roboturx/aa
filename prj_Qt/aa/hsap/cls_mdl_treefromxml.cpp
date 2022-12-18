#include "cls_mdl_treefromxml.h"

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

/// fields' count
const int ColumnCount = 6;
enum Column {HesapAd, HesapAciklama, Topluhesap,
              HesapTuru, UstHesap, HesapKod };

const int MaxCompression = 9;
const QString MimeType = "application/vnd.qtrac.xml.task.z";
}

/// XML:004
/// make editable, checkable, drag-dropable
/// variables for XML file
///
Qt::ItemFlags cls_mdl_TreeFromXml::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
    //    if (index.isValid())
    //    {
    //        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled;

    //

    if (index.isValid())
    {

        if (index.column() == HesapAd ||
                index.column() == HesapAciklama ||
                index.column() == HesapTuru ||
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
QVariant cls_mdl_TreeFromXml::data(const QModelIndex &index, int role) const
{
    if (!rootItem || !index.isValid() || index.column() < 0 ||
            index.column() >= ColumnCount)
        return QVariant();

    if (TaskItem *item = itemForIndex(index))
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (index.column()) {
            case HesapAd:   return item->hesapAd();
            case HesapAciklama:   return item->hesapAcklm();
            case Topluhesap:return item->isTopluHesap();
            case HesapTuru: return item->hesapTuru();
            case UstHesap:  return item->ustHesap();
            case HesapKod:  return item->hesapKod();
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
        if (role == Qt::DecorationRole
                && index.column() == HesapKod
                && timedItem
                && item == timedItem
                && !m_icon.isNull())
            return m_icon;
    }
    return QVariant();
}

/// XML:006
/// headers
/// variables for XML file
///
QVariant cls_mdl_TreeFromXml::headerData(int section,
                               Qt::Orientation orientation, int role) const
{
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

    }
    return QVariant();
}

/// XML:007
/// setdata
/// variables for XML file
///
bool cls_mdl_TreeFromXml::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
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
bool cls_mdl_TreeFromXml::insertRows(int row, int count,
                           const QModelIndex &parent)
{
    qDebug() << "*XMLmodeel nsert rows******************************************"
             << rowCount(parent);
  //  qDebug()<<"             cls_mdl_TreeFromXml.cpp-insertrows içinde pi-max-hesp-id " << pi_max_Hesap_ID <<"-"<< *pi_max_Hesap_ID;
    if (!rootItem)
    {
        qDebug()<<"  rootitem yokk     ";
        rootItem = new TaskItem("ROOThspad","ROOTAcklm",0,"ROOTturu","ROOTusthsp",0);

        qDebug() << "ROOOOOOT Cnt" << rowCount(parent) ;
        qDebug() << "hkod:" << rootItem->hesapKod ()
                 << " :ad:" << rootItem->hesapAd ()
                 << " :tpl:" << QString::number(rootItem->isTopluHesap())
                 << " :tur:" << rootItem->hesapTuru()
                 << " :ust:" << rootItem->ustHesap()
                 << "ROOOOOOOOYT" ;


    }
    qDebug()<<" parentitem ???????????????????????????????????      ";

    TaskItem *parentItem = parent.isValid() ? itemForIndex(parent)
                                            : rootItem;
    qDebug() << "parentItem rowcount" << rowCount(parent) ;
    qDebug() << " pkod:" << parentItem->hesapKod ();
    qDebug() << " :ad:" << parentItem->hesapAd ();
    qDebug() << " :tpl:  :" << QString::number(parentItem->isTopluHesap());
    qDebug() << " :tur:" << parentItem->hesapTuru();
    qDebug() << " :ust:" << parentItem->ustHesap();
    qDebug() << "parentItem" ;

    beginInsertRows(parent, row, row + count - 1);
    qDebug() << "111";
    for (int i = 0; i < count; ++i)
    {
        qDebug() << "111we";
        // hesaba en yüksek id yi ver
        //qDebug()<<"nsertrows pi-max-hesp-id " << pi_max_Hesap_ID <<"-"<< *pi_max_Hesap_ID;
        ++*pi_max_Hesap_ID;
        qDebug()<<"nsertrows pi-max-hesp-id after ++ " << pi_max_Hesap_ID <<"-"<< *pi_max_Hesap_ID;
        // hesap adını kod olarak ayarla
        // QString str_hesapADI =   QString::number(*pi_max_Hesap_ID) ;
 qDebug() << "111ddd";
        // yeni bir hesap oluştur
        TaskItem *item = new TaskItem("","",0,"","",*pi_max_Hesap_ID) ;
 qDebug() << "1112222";
        parentItem->insertChild(row, item);
        qDebug() << "item" << i << " rowcount" << rowCount(parent) ;
        qDebug() << "item" << i << " hesapkod :" << item->hesapKod ();
        qDebug() << "item" << i << " hesap ad :" << item->hesapAd ();
        qDebug() << "item" << i << " istoplu  :" << QString::number(item->isTopluHesap());
        qDebug() << "item" << i << " hesapturu:" << item->hesapTuru();
        qDebug() << "item" << i << " usthesap :" << item->ustHesap();
        qDebug() << "item" << i ;
    }
    qDebug() << "cls_mdl_TreeFromXml.cpp-::insertRows(*****************"
                "end***************************";
    endInsertRows();
    return true;
}


/// XML:009
/// changing
/// variables for XML file
///
void cls_mdl_TreeFromXml::announceItemChanged(TaskItem *item)
{
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
void cls_mdl_TreeFromXml::readTasks(QXmlStreamReader *reader,
                          TaskItem *task)
{

    //cB_hesapAds = new QComboBox{} ;

    hesapListesi = new cls_Hesaplar;
    pi_max_Hesap_ID = new quint64{};
    *pi_max_Hesap_ID = 0;
    while (!reader->atEnd())
    {
        reader->readNext();
        if (reader->isStartElement())
        {
            if (reader->name() == TaskTag)
            {
                const quint64 hesapKod = reader->attributes()
                        .value(HesapKodAttribute).toULongLong ();
qDebug()<<"         MODEL readTasks readerda *pi-max-hesp-id " << *pi_max_Hesap_ID <<"-"<< *pi_max_Hesap_ID;
qDebug()<<"         MODEL readTasks readerda okunan *hesadpkod " << hesapKod;
                if (hesapKod > *pi_max_Hesap_ID)
                {
                    *pi_max_Hesap_ID = hesapKod;
                }

                const QString hesapAd = reader->attributes()
                        .value(HesapAdAttribute).toString();

                // hspdetay transfer hesaplarda kullanılacak liste
                hesapListesi->setHesaplar(hesapAd,hesapKod);

                //cB_hesapAds->addItem (hesapAd);

                const QString hesapAcklm = reader->attributes()
                        .value(AcklmAttribute).toString();
                bool topluHesap = reader->attributes()
                        .value(TopluHesapAttribute).toInt();
                const QString hesapTuru = reader->attributes()
                        .value(HesapTuruAttribute).toString();
                const QString ustHesap = reader->attributes()
                        .value(UstHesapAttribute).toString();

                //                reader->attributes().value(TopluHesapAttribute)
                //                        .toString () == "1";
                //                reader->attributes().value(HesapTuruAttribute)
                //                        .toString () == "hhhesapturu2";
                //                reader->attributes().value(UstHesapAttribute)
                //                        .toString () == "uuuusthesap3";
  qDebug()<<"       eeFromXml::readTasks    new taskitem";
                task = new TaskItem(hesapAd, hesapAcklm, topluHesap,
                        hesapTuru, ustHesap, hesapKod, task);

            }
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
              qDebug()<<"eeFromXml::readTasks    rgf2222";
        }

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
    qDebug()<<"eeFromXml::readTasks    enddddd     readerda pi-max-hesp-id son hali " << pi_max_Hesap_ID <<"-"<< *pi_max_Hesap_ID;
}

/// XML:011
/// save XML file
/// variables for XML file
///
void cls_mdl_TreeFromXml::save(const QString &filename)
{
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
void cls_mdl_TreeFromXml::writeTaskAndChildren(QXmlStreamWriter *writer,
                                     TaskItem *task) const
{
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



int cls_mdl_TreeFromXml::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    TaskItem *parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}


int cls_mdl_TreeFromXml::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() && parent.column() != 0 ? 0 : ColumnCount;
}


QModelIndex cls_mdl_TreeFromXml::index(int row, int column,
                             const QModelIndex &parent) const
{
    if (!rootItem || row < 0 || column < 0 || column >= ColumnCount
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    TaskItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if (TaskItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}


TaskItem *cls_mdl_TreeFromXml::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (TaskItem *item = static_cast<TaskItem*>(
                    index.internalPointer()))
            return item;
    }
    return rootItem;
}


QModelIndex cls_mdl_TreeFromXml::parent(const QModelIndex &index) const
{
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



bool cls_mdl_TreeFromXml::removeRows(int row, int count,
                           const QModelIndex &parent)
{
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


QStringList cls_mdl_TreeFromXml::mimeTypes() const
{
    return QStringList() << MimeType;
}


QMimeData *cls_mdl_TreeFromXml::mimeData(const QModelIndexList &indexes) const
{
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


bool cls_mdl_TreeFromXml::dropMimeData(const QMimeData *mimeData,
                             Qt::DropAction action, int row,
                             int column,
                             const QModelIndex &parent)
{
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


bool cls_mdl_TreeFromXml::isChecked(const QModelIndex &index) const
{
    if (!index.isValid())
        return false;
    return data(index, Qt::CheckStateRole).toInt() == Qt::Checked;
}


QModelIndex cls_mdl_TreeFromXml::moveUp(const QModelIndex &index)
{
    if (!index.isValid() || index.row() <= 0)
        return index;
    TaskItem *item = itemForIndex(index);
    Q_ASSERT(item);
    TaskItem *parent = item->parent();
    Q_ASSERT(parent);
    return moveItem(parent, index.row(), index.row() - 1);
}


QModelIndex cls_mdl_TreeFromXml::moveItem(TaskItem *parent, int oldRow,
                                int newRow)
{
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


QModelIndex cls_mdl_TreeFromXml::moveDown(const QModelIndex &index)
{
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


QModelIndex cls_mdl_TreeFromXml::cut(const QModelIndex &index)
{
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


QModelIndex cls_mdl_TreeFromXml::paste(const QModelIndex &index)
{
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


QModelIndex cls_mdl_TreeFromXml::promote(const QModelIndex &index)
{
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


QModelIndex cls_mdl_TreeFromXml::demote(const QModelIndex &index)
{
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


void cls_mdl_TreeFromXml::setTimedItem(const QModelIndex &index)
{
    clearTimedItem();
    timedItem = itemForIndex(index);
    Q_ASSERT(timedItem);
    announceItemChanged(timedItem);
}


void cls_mdl_TreeFromXml::clearTimedItem()
{
    if (timedItem) {
        TaskItem *item = timedItem;
        timedItem = 0;
        announceItemChanged(item);
    }
}


bool cls_mdl_TreeFromXml::isTimedItem(const QModelIndex &index)
{
    return timedItem && itemForIndex(index) == timedItem;
}



void cls_mdl_TreeFromXml::addDateTimeToTimedItem(const QDateTime &start,
                                       const QDateTime &end)
{
    if (timedItem) {
        timedItem->addDateTime(start, end);
        announceItemChanged(timedItem);
    }
}


void cls_mdl_TreeFromXml::setIconForTimedItem(const QIcon &icon)
{
    m_icon = icon;
    if (timedItem)
        announceItemChanged(timedItem);
}


void cls_mdl_TreeFromXml::incrementEndTimeForTimedItem(int msec)
{
    if (timedItem) {
        timedItem->incrementLastEndTime(msec);
        announceItemChanged(timedItem);
    }
}


void cls_mdl_TreeFromXml::clear()
{
    delete rootItem;
    rootItem = 0;
    delete cutItem;
    cutItem = 0;
    timedItem = 0;
    //reset();         //deleted for Qt5
    beginResetModel(); //added for Qt5
    endResetModel();   //added for Qt5
}


void cls_mdl_TreeFromXml::load(const QString &filename)
{
    qDebug () << "          MODEL cls_mdl_treefromxml::load ";
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw AQP::Error(tr("no filename specified"));
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
        throw AQP::Error(file.errorString());

    clear();
    qDebug () << "cls_mdl_TreeFromXml::load     new root item";
    rootItem = new TaskItem("ROO","ROO",0,"ROO","ROOT",0);



    QXmlStreamReader reader(&file);
    readTasks(&reader, rootItem);
    if (reader.hasError())
        throw AQP::Error(reader.errorString());
    beginResetModel();
    endResetModel();
}


QStringList cls_mdl_TreeFromXml::pathForIndex(const QModelIndex &index) const
{
    QStringList path;
    QModelIndex thisIndex = index;
    while (thisIndex.isValid()) {
        path.prepend(data(thisIndex).toString());
        thisIndex = thisIndex.parent();
    }
    return path;
}


QModelIndex cls_mdl_TreeFromXml::indexForPath(const QStringList &path) const
{
    return indexForPath(QModelIndex(), path);
}


QModelIndex cls_mdl_TreeFromXml::indexForPath(const QModelIndex &parent,
                                    const QStringList &path) const
{
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
