#include "libs/cm_helptreexml.h"

//cm_HELPTreeXML::cm_HELPTreeXML(QObject *parent)
//    : QAbstractItemModel{parent}
//{

//}

/// fields :
/// change these for data manipulation
///
/// 001- -  in HelpItem.h - field's variable declarations
/// 002- -  in HelpItem.h - field variables' getters and setters
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

const QString HelpTag("HELP");

/// fields for XML file
const QString HelpAdAttribute("hlPNAME");
const QString HelpAcklmAttribute("hlPNOTE");
//const QString TopluHesapAttribute("hlPIsBATCH");
//const QString HesapTuruAttribute("hlPTYPE");
//const QString UstHesapAttribute("hlPsPARENT");
const QString HelpKodAttribute("hlPCODE");
const QString HelpDBFileAttribute("hlPDBFile");

/// fields' count
const int ColumnCount = 4;
enum Column {HelpAd, HelpAciklama, HelpKod, HelpDBFile };

const int MaxCompression = 9;
const QString MimeType = "application/vnd.qtrac.xml.help.z";
}

/// XML:004
/// make editable, checkable, drag-dropable
/// variables for XML file
///
Qt::ItemFlags cm_HELPTreeXML::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
    {

        if (index.column() == HelpAd ||
                index.column() == HelpAciklama ||
                index.column() == HelpDBFile        )
        {
            theFlags |= Qt::ItemIsSelectable|
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
QVariant cm_HELPTreeXML::data(const QModelIndex &index,
                                   int role) const
{
   // qDebug()<<"::Xmdl data";
    if (!rootItem || !index.isValid() || index.column() < 0 ||
            index.column() >= ColumnCount)
        return QVariant();


    if (HelpItem *item = itemForIndex(index))
    {

        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {

            qDebug() << "/*-/*-/*-/*-/*- : "<< index.column();
                    // << index.data (Qt::DisplayRole);

            switch (index.column()) {

            case HelpAd:       return item->helpAd();
            case HelpAciklama: return item->helpAcklm();
            case HelpKod:      return item->helpKod();
            case HelpDBFile:        return item->DBFile ();
            default: Q_ASSERT(false);
            }
        }
        if (role == Qt::TextAlignmentRole)
        {
            if (index.column() == HelpDBFile )
            {
                return static_cast<int>(Qt::AlignVCenter|
                                        Qt::AlignCenter);
            }
            if (index.column() == HelpAd ||
                    index.column() == HelpAciklama     )
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

                    return QIcon(":/rsm/icon/candlestick.png");

            }
        }

        if (role == Qt::DecorationRole
                && index.column() == HelpKod
                && timedItem
                && item == timedItem
                && !m_icon.isNull())
            return m_icon;

        if (  role == Qt::FontRole )
        {
            QFont font;
            font.setPointSize(14);
            return font;
        }

        if (  role == Qt::ForegroundRole )
            {
                if ( index.column() == 0 || index.column() == 3)
                {

                        return QVariant( QColor( "#D8AE47" ) );

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
QVariant cm_HELPTreeXML::headerData(int section,
                               Qt::Orientation orientation, int role) const
{
   // qDebug()<<"::Xmdl headerdata";
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == HelpAd)
            return tr("Yardım Adı");
        else if (section == HelpAciklama)
            return tr("Yardım Açıklama");
        else if (section == HelpKod)
            return tr("Yrdm Kod");
        else if (section == HelpDBFile)
            return tr("HelpDBF");

    }
    return QVariant();
}

/// XML:007
/// setdata
/// variables for XML file
///
bool cm_HELPTreeXML::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
//    qDebug()<<"::Xmdl setdata";
    if (!index.isValid() ) //|| index.column() != HesapAd)
    {
        return false;
    }

    if (HelpItem *item = itemForIndex(index))
    {
        if (role == Qt::EditRole)
        {
            if (index.column() == HelpAd)
            {
                item->setHelpAd(value.toString());

            }
            if (index.column() == HelpAciklama)
            {
                item->setHelpAcklm(value.toString());
            }
            if (index.column() == HelpDBFile)
            {
                item->setHelpDBFile (value.toString());
            }
        }

        else if (role == Qt::CheckStateRole)
        {
            return false;
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
bool cm_HELPTreeXML::insertRows(int row, int count,
                           const QModelIndex &parent)
{
    qDebug()<<"::Xmdl insertrows";

    if (!rootItem)
    {

        rootItem = new HelpItem(  "T","T",0,"T");
        *pi_max_Hesap_ID = rootItem->helpKod()  ;

 }

 HelpItem *parentItem = parent.isValid() ? itemForIndex(parent)
                                            : rootItem;
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i)
    {
         // hesaba en yüksek id yi ver

        ++*pi_max_Hesap_ID;

        // yeni bir hesap oluştur
        HelpItem *item = new HelpItem("","",*pi_max_Hesap_ID,"") ;

        parentItem->insertChild(row, item);
    }
//    qDebug() << "cm_HELPTreeXML.cpp-::insertRows(*****************"
//                "end***************************";
    endInsertRows();
    return true;
}


/// XML:009
/// changing
/// variables for XML file
///
void cm_HELPTreeXML::announceItemChanged(HelpItem *item)
{
    qDebug()<<"::Xmdl announceitemchanged";

    if (item == rootItem)
        return;
    HelpItem *parent = item->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(item);

    QModelIndex startIndex = createIndex(row,
                 static_cast<int>(HelpAd), item);
    QModelIndex endIndex = createIndex(row,
                 static_cast<int>(HelpDBFile), item);

    emit dataChanged(startIndex, endIndex);

    // Update the parent & parent's parent etc too
    announceItemChanged(parent);
}

/// XML:010
/// read from XML
/// variables for XML file
///
void cm_HELPTreeXML::readHelps(QXmlStreamReader *reader,
                          HelpItem *help)
{
   // qDebug()<<"::Xmdl readHelps";
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
            /// Help lar
            if (reader->name() == HelpTag)
            {
                const int helpKod = reader->attributes()
                        .value(HelpKodAttribute).toULongLong ();

                if (helpKod > *pi_max_Hesap_ID)
                {
                    // en büyük hesapkod u bul
                    *pi_max_Hesap_ID = helpKod;
                }

                QString helpAd = reader->attributes()
                        .value(HelpAdAttribute).toString();

                const QString helpAcklm = reader->attributes()
                        .value(HelpAcklmAttribute).toString();
                const QString helpDBFile = reader->attributes()
                        .value(HelpDBFileAttribute).toString();

                help = new HelpItem(helpAd, helpAcklm,helpKod,
                                    helpDBFile, help);

                //// item ı listeye ekle
                ///  hspdetay transfer hesaplarda kullanılacak liste
                listXML<<help;
            }
            // NZAMAN lar
//            else if (reader->name() == NeZamanTag) {
//                const QDateTime start = QDateTime::fromString(
//                            reader->attributes().value(IlkAttribute)
//                            .toString(), Qt::ISODate);
//                const QDateTime end = QDateTime::fromString(
//                            reader->attributes().value(SonAttribute)
//                            .toString(), Qt::ISODate);
//                Q_ASSERT(Help);
//                Help->addDateTime(start, end);
 //           }
        }
        // YOKSA son kayıt MI
        else if (reader->isEndElement())
        {
            if (reader->name() == HelpTag)
            {
                Q_ASSERT(help);
                help = help->parent();
                Q_ASSERT(help);
            }
        }
    } // while end
}

/// XML:011
/// save XML file
/// variables for XML file
///
void cm_HELPTreeXML::save(const QString &filename)
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
    writeHelpAndChildren(&writer, rootItem);
    writer.writeEndElement(); // KONUM
    writer.writeEndDocument();
}

/// XML:012
/// write to XML file
/// variables for XML file
///
void cm_HELPTreeXML::writeHelpAndChildren(QXmlStreamWriter *writer,
                                     HelpItem *help) const
{
    qDebug()<<"::Xmdl writeHelpandchildren";
    if (help != rootItem) {
        writer->writeStartElement(HelpTag);

        writer->writeAttribute(HelpAdAttribute,
                               help->helpAd());
        writer->writeAttribute(HelpAcklmAttribute,
                               help->helpAcklm());
        writer->writeAttribute(HelpKodAttribute,
                  QString::number (help->helpKod() ));
        writer->writeAttribute(HelpDBFileAttribute,
                               help->DBFile());


//        QListIterator<
//                QPair<QDateTime, QDateTime> > i(help->dateTimes());
//        while (i.hasNext()) {
//            const QPair<QDateTime, QDateTime> &dateTime = i.next();
//            writer->writeStartElement(NeZamanTag);
//            writer->writeAttribute(IlkAttribute,
//                                   dateTime.first.toString(Qt::ISODate));
//            writer->writeAttribute(SonAttribute,
//                                   dateTime.second.toString(Qt::ISODate));
//            writer->writeEndElement(); // WHEN
//        }
    }
    foreach (HelpItem *child, help->children())
        writeHelpAndChildren(writer, child);
    if (help != rootItem)
        writer->writeEndElement(); // Help
}

/////////////////////////////////////////////////////////////////
///
///
///
///
/////////////////////////////////////////////////////////////////



int cm_HELPTreeXML::rowCount(const QModelIndex &parent) const
{
   // qDebug()<<"::Xmdl rowcount";
    if (parent.isValid() && parent.column() != 0)
        return 0;
    HelpItem *parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}


int cm_HELPTreeXML::columnCount(const QModelIndex &parent) const
{
   // qDebug()<<"::Xmdl columncount";
    return parent.isValid() && parent.column() != 0 ? 0 : ColumnCount;
}


QModelIndex cm_HELPTreeXML::index(int row, int column,
                             const QModelIndex &parent) const
{
  //  qDebug()<<"::Xmdl index";
    if (!rootItem || row < 0 || column < 0 || column >= ColumnCount
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    HelpItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if (HelpItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}


HelpItem *cm_HELPTreeXML::itemForIndex(const QModelIndex &index) const
{
   // qDebug()<<"::Xmdl itemforindex";
    if (index.isValid()) {
        if (HelpItem *item = static_cast<HelpItem*>(
                    index.internalPointer()))
            return item;
    }
    return rootItem;
}


QModelIndex cm_HELPTreeXML::parent(const QModelIndex &index) const
{
    //qDebug()<<"::Xmdl parent ";
    if (!index.isValid())
        return QModelIndex();
    if (HelpItem *childItem = itemForIndex(index)) {
        if (HelpItem *parentItem = childItem->parent()) {
            if (parentItem == rootItem)
                return QModelIndex();
            if (HelpItem *grandParentItem = parentItem->parent()) {
                int row = grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}



bool cm_HELPTreeXML::removeRows(int row, int count,
                           const QModelIndex &parent)
{
    qDebug()<<"::Xmdl removeerows";
    if (!rootItem)
        return false;
    HelpItem *item = parent.isValid() ? itemForIndex(parent)
                                      : rootItem;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
        delete item->takeChild(row);
    endRemoveRows();
    return true;
}


QStringList cm_HELPTreeXML::mimeTypes() const
{
    qDebug()<<"::Xmdl mimetypes";
    return QStringList() << MimeType;
}


QMimeData *cm_HELPTreeXML::mimeData(const QModelIndexList &indexes) const
{
    qDebug()<<"::Xmdl mimedata";
    Q_ASSERT(indexes.count());
    if (indexes.count() != 1)
        return 0;
    if (HelpItem *item = itemForIndex(indexes.at(0))) {
        QMimeData *mimeData = new QMimeData;
        QByteArray xmlData;
        QXmlStreamWriter writer(&xmlData);
        writeHelpAndChildren(&writer, item);
        mimeData->setData(MimeType, qCompress(xmlData,
                                              MaxCompression));
        return mimeData;
    }
    return 0;
}


bool cm_HELPTreeXML::dropMimeData(const QMimeData *mimeData,
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
    if (HelpItem *item = itemForIndex(parent)) {
        emit stopTiming();
        QByteArray xmlData = qUncompress(mimeData->data(MimeType));
        QXmlStreamReader reader(xmlData);
        if (row == -1)
            row = parent.isValid() ? parent.row()
                                   : rootItem->childCount();
        beginInsertRows(parent, row, row);
        readHelps(&reader, item);
        endInsertRows();
        return true;
    }
    return false;
}


bool cm_HELPTreeXML::isChecked(const QModelIndex &index) const
{
    qDebug()<<"::Xmdl ischecked";
    if (!index.isValid())
        return false;
    return data(index, Qt::CheckStateRole).toInt() == Qt::Checked;
}


QModelIndex cm_HELPTreeXML::moveUp(const QModelIndex &index)
{
    qDebug()<<"::Xmdl moveup";
    if (!index.isValid() || index.row() <= 0)
        return index;
    HelpItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HelpItem *parent = item->parent();
    Q_ASSERT(parent);
    return moveItem(parent, index.row(), index.row() - 1);
}


QModelIndex cm_HELPTreeXML::moveItem(HelpItem *parent, int oldRow,
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
/////////////////////////////////////////////////////////////////
/// \brief cm_HELPTreeXML::hTurColor
///
/// hc_main - 445 signal i,le yollanan qcolor
/// hesap turu rengi olarak kullanılacak
///
void cm_HELPTreeXML::hTurColor(QColor color)
{
    qDebug()<<"------------htur siggggggnaaaaaaaaaaaal    " << color;
}

QList<HelpItem *> cm_HELPTreeXML::getListXML() const
{
    foreach (HelpItem* item, listXML)
    {

        qDebug() <<"----------------"<< item->helpAd ();
    }
    return listXML;
}

void cm_HELPTreeXML::setListXML(QList<HelpItem*> newListXML)
{
    listXML = newListXML;
}


QModelIndex cm_HELPTreeXML::moveDown(const QModelIndex &index)
{
    qDebug()<<"::Xmdl moveedown";
    if (!index.isValid())
        return index;
    HelpItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HelpItem *parent = item->parent();
    int newRow = index.row() + 1;
    if (!parent || parent->childCount() <= newRow)
        return index;
    return moveItem(parent, index.row(), newRow);
}


QModelIndex cm_HELPTreeXML::cut(const QModelIndex &index)
{
    qDebug()<<"::Xmdl cut";
    if (!index.isValid())
        return index;
    delete cutItem;
    cutItem = itemForIndex(index);
    Q_ASSERT(cutItem);
    HelpItem *parent = cutItem->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(cutItem);
    Q_ASSERT(row == index.row());
    beginRemoveRows(index.parent(), row, row);
    HelpItem *child = parent->takeChild(row);
    endRemoveRows();
    Q_ASSERT(child == cutItem);
    child = 0; // Silence compiler unused variable warning

    if (row > 0) {
        --row;
        return createIndex(row, 0, parent->childAt(row));
    }
    if (parent != rootItem) {
        HelpItem *grandParent = parent->parent();
        Q_ASSERT(grandParent);
        return createIndex(grandParent->rowOfChild(parent), 0, parent);
    }
    return QModelIndex();
}


QModelIndex cm_HELPTreeXML::paste(const QModelIndex &index)
{
    qDebug()<<"::Xmdl paste";
    if (!index.isValid() || !cutItem)
        return index;
    HelpItem *sibling = itemForIndex(index);
    Q_ASSERT(sibling);
    HelpItem *parent = sibling->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(sibling) + 1;
    beginInsertRows(index.parent(), row, row);
    parent->insertChild(row, cutItem);
    HelpItem *child = cutItem;
    cutItem = 0;
    endInsertRows();
    return createIndex(row, 0, child);
}


QModelIndex cm_HELPTreeXML::promote(const QModelIndex &index)
{
    qDebug()<<"::Xmdl prğmğte";
    if (!index.isValid())
        return index;
    HelpItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HelpItem *parent = item->parent();
    Q_ASSERT(parent);
    if (parent == rootItem)
        return index; // Already a top-level item

    int row = parent->rowOfChild(item);
    HelpItem *child = parent->takeChild(row);
    Q_ASSERT(child == item);
    HelpItem *grandParent = parent->parent();
    Q_ASSERT(grandParent);
    row = grandParent->rowOfChild(parent) + 1;
    grandParent->insertChild(row, child);
    QModelIndex newIndex = createIndex(row, 0, child);
    emit dataChanged(newIndex, newIndex);
    return newIndex;
}


QModelIndex cm_HELPTreeXML::demote(const QModelIndex &index)
{
    qDebug()<<"::Xmdl demote";
    if (!index.isValid())
        return index;
    HelpItem *item = itemForIndex(index);
    Q_ASSERT(item);
    HelpItem *parent = item->parent();
    Q_ASSERT(parent);
    int row = parent->rowOfChild(item);
    if (row == 0)
        return index; // No preceding sibling to move this under
    HelpItem *child = parent->takeChild(row);
    Q_ASSERT(child == item);
    HelpItem *sibling = parent->childAt(row - 1);
    Q_ASSERT(sibling);
    sibling->addChild(child);
    QModelIndex newIndex = createIndex(sibling->childCount() - 1, 0,
                                       child);
    emit dataChanged(newIndex, newIndex);
    return newIndex;
}


void cm_HELPTreeXML::setTimedItem(const QModelIndex &index)
{
    qDebug()<<"::Xmdl settimeditem";
    clearTimedItem();
    timedItem = itemForIndex(index);
    Q_ASSERT(timedItem);
    announceItemChanged(timedItem);
}


void cm_HELPTreeXML::clearTimedItem()
{
    qDebug()<<"::Xmdl cleartimeditem";
    if (timedItem) {
        HelpItem *item = timedItem;
        timedItem = 0;
        announceItemChanged(item);
    }
}


bool cm_HELPTreeXML::isTimedItem(const QModelIndex &index)
{
    qDebug()<<"::Xmdl istimeedata";
    return timedItem && itemForIndex(index) == timedItem;
}



void cm_HELPTreeXML::addDateTimeToTimedItem(const QDateTime &start,
                                       const QDateTime &end)
{
    qDebug()<<"::Xmdl adddatetime";
    if (timedItem) {
      //  timedItem->addDateTime(start, end);
        announceItemChanged(timedItem);
    }
}


void cm_HELPTreeXML::setIconForTimedItem(const QIcon &icon)
{
    qDebug()<<"::Xmdl seticonfor ";
    m_icon = icon;
    if (timedItem)
        announceItemChanged(timedItem);
}


void cm_HELPTreeXML::incrementEndTimeForTimedItem(int msec)
{
    qDebug()<<"::Xmdl incrementendtime";
    if (timedItem) {
      //  timedItem->incrementLastEndTime(msec);
        announceItemChanged(timedItem);
    }
}


void cm_HELPTreeXML::clear()
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


void cm_HELPTreeXML::load(const QString &filename)
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
    qDebug () << "cm_HELPTreeXML::load     new root item";
    rootItem = new HelpItem("ROO","ROO",0,"ROO");



    QXmlStreamReader reader(&file);
    readHelps(&reader, rootItem);
    if (reader.hasError())
        throw AQP::Error(reader.errorString());
    beginResetModel();
    endResetModel();
}


QStringList cm_HELPTreeXML::pathForIndex(const QModelIndex &index) const
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


QModelIndex cm_HELPTreeXML::indexForPath(const QStringList &path) const
{
    //qDebug()<<"::Xmdl indexforpath";
    return indexForPath(QModelIndex(), path);
}


QModelIndex cm_HELPTreeXML::indexForPath(const QModelIndex &parent,
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
