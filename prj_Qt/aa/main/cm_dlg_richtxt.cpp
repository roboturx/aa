

#include "libs/globals.h"
#include "main/cm_dlg_le_richtxt.h"
#include "main/cm_dlg_richtxt.h"


cm_dlG_RichTxt::cm_dlG_RichTxt(QObject *parent)
    : QStyledItemDelegate(parent)
{
    qDebug()<<"dlg-rtxt t construc***************************************";
    checkbox = new QCheckBox;
    checkbox->setFixedSize(
            qRound(1.3 * checkbox->sizeHint().height()),
            checkbox->sizeHint().height());
    label = new QLabel;
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(false);
}


void cm_dlG_RichTxt::paint(QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    bool selected = option.state & QStyle::State_Selected;
    QPalette palette(option.palette);
    palette.setColor(QPalette::Active, QPalette::Window,
                     selected ? option.palette.highlight().color()
                              : option.palette.base().color());
//    palette.setColor(QPalette::Active, QPalette::Window,
//                     selected ? option.palette.highlight().color()
//                              : option.palette.base().color());
    palette.setColor(QPalette::Active, QPalette::WindowText,
                     selected
                     ? option.palette.highlightedText().color()
                     : option.palette.text().color());

    int yOffset = checkbox->height() < option.rect.height()
            ? (option.rect.height() - checkbox->height()) / 2 : 0;
    QRect checkboxRect(option.rect.x(), option.rect.y() + yOffset,
            checkbox->width(), checkbox->height());
    checkbox->setPalette(palette);
    bool checked = index.model()->data(index, Qt::CheckStateRole)
                                       .toInt() == Qt::Checked;
    checkbox->setChecked(checked);

    QRect labelRect(option.rect.x() + checkbox->width(),
            option.rect.y(), option.rect.width() - checkbox->width(),
            option.rect.height());
    label->setPalette(palette);
    label->setFixedSize(qMax(0, labelRect.width()),
                        labelRect.height());
    QString html = index.model()->data(index, Qt::DisplayRole)
                                       .toString();
    label->setText(html);

    QString checkboxKey = QString("CHECKBOX:%1.%2").arg(selected)
                                                   .arg(checked);
    paintWidget(painter, checkboxRect, checkboxKey, checkbox);
    QString labelKey = QString("LABEL:%1.%2.%3x%4").arg(selected)
            .arg(html).arg(labelRect.width()).arg(labelRect.height());
    paintWidget(painter, labelRect, labelKey, label);
}


void cm_dlG_RichTxt::paintWidget(QPainter *painter,
        const QRect &rect, const QString &cacheKey,
        QWidget *widget) const
{
    QPixmap pixmap(widget->size());
#if QT_VERSION >= 0x040600
    if (!QPixmapCache::find(cacheKey, &pixmap)) {
#else
    if (!QPixmapCache::find(cacheKey, pixmap)) {
#endif
        widget->render(&pixmap);
        QPixmapCache::insert(cacheKey, pixmap);
    }
    painter->drawPixmap(rect, pixmap);
}


QSize cm_dlG_RichTxt::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    QString html = index.model()->data(index, Qt::DisplayRole)
                                       .toString();
    document.setDefaultFont(option.font);
    document.setHtml(html);
    return QSize(document.idealWidth(), option.fontMetrics.height());
}


QWidget *cm_dlG_RichTxt::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option, const QModelIndex&) const
{
    cm_dlG_le_RichTxt *editor = new cm_dlG_le_RichTxt(parent);
    editor->viewport()->setFixedHeight(option.rect.height());
    connect(editor, SIGNAL(returnPressed()),
            this, SLOT(closeAndCommitEditor()));
    return editor;
}


void cm_dlG_RichTxt::setEditorData(QWidget *editor,
        const QModelIndex &index) const
{
    QString html = index.model()->data(index, Qt::DisplayRole)
                                       .toString();
    cm_dlG_le_RichTxt *lineEdit = qobject_cast<cm_dlG_le_RichTxt*>(
                                              editor);
    Q_ASSERT(lineEdit);
    lineEdit->setHtml(html);
}


void cm_dlG_RichTxt::setModelData(QWidget *editor,
        QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug()<<"---------richtxt set model data----------------";

    cm_dlG_le_RichTxt *lineEdit =
            qobject_cast<cm_dlG_le_RichTxt*>(editor);
    Q_ASSERT(lineEdit);
    model->setData(index, lineEdit->toSimpleHtml());

//qDebug()<<"1111111111111111111111111111111111111111";
//    QModelIndex ind=model->index(index.row(),0);
//qDebug()<<"2222222222222";
//    QModelIndex ind2=model->index(index.row(),3);
//    //int i= model->data(ind2, Qt::ForegroundRole).toInt();
//qDebug()<<"3333333333333333333333333333";
//    qDebug()<<"model->data(ind, Qt::ForegroundRole)="
//           <<model->data(ind, Qt::ForegroundRole);
//    qDebug()<<"44444444444444444444444444444444444444444444444";
//    qDebug()<<"model->data(ind2, Qt::ForegroundRole)="
//           <<model->data(ind2, Qt::ForegroundRole);

//    model->setData(ind,model->data(ind2, Qt::ForegroundRole) ,
//                      Qt::ForegroundRole);
//qDebug()<<"-----------------------------------------------";
}


void cm_dlG_RichTxt::closeAndCommitEditor()
{
    cm_dlG_le_RichTxt *lineEdit = qobject_cast<cm_dlG_le_RichTxt*>(
                                              sender());
    Q_ASSERT(lineEdit);
    emit commitData(lineEdit);
    emit closeEditor(lineEdit);
}
