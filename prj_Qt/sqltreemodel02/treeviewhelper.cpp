#include <QMetaType>
#include <QObject>
#include <QtGui>
#include <QtCore>


#include "application.h"
#include "data/datamanager.h"
#include "data/localsettings.h"
#include "sqltreemodel.h"

#include <QTreeView>
#include <QHeaderView>
#include <QTextDocument>
#include <QHelpEvent>
#include <QToolTip>
#include <QList>
#include "treeviewhelper.h"




TreeViewHelper::TreeViewHelper( QTreeView* view ) :
    m_view( view )
{

    static bool registered = false;

    if ( !registered )
    {
         qRegisterMetaType <ExpandedNodeList>();
        qRegisterMetaType <ExpandedNode>();
        registered = true;
    }
}

TreeViewHelper::~TreeViewHelper()
{
}

void TreeViewHelper::initializeView( ViewFlags flags )
{
    m_view->setSortingEnabled( ( flags & NotSortable ) == 0 );
    m_view->setRootIsDecorated( ( flags & TreeStyle ) != 0 );

    if ( flags & TreeStyle )
        m_view->setExpandsOnDoubleClick( false );

    if ( flags & MultiSelect )
        m_view->setSelectionMode( QAbstractItemView::ExtendedSelection );

    m_view->setUniformRowHeights( true );

    m_view->header()->setStretchLastSection( false );
    m_view->header()->setSectionsMovable( false );

    m_view->setContextMenuPolicy( Qt::CustomContextMenu );
    m_view->header()->setContextMenuPolicy( Qt::CustomContextMenu );

    if ( ( flags & NoAutoToolTip ) == 0 )
        m_view->setItemDelegate( new AutoToolTipDelegate( m_view ) );
}

QModelIndex TreeViewHelper::selectedIndex()
{
    if ( !m_view->selectionModel() )
        return QModelIndex();

    QModelIndexList selection = m_view->selectionModel()->selectedRows();
    if ( selection.isEmpty() )
        return QModelIndex();

    return selection.at( 0 );
}

void TreeViewHelper::saveColumnWidths( const QString& key )
{
    int count = m_view->model()->columnCount();

    QList<int> widths;
    for ( int i = 0; i < count; i++ )
        widths.append( m_view->columnWidth( i ) );

    //application->applicationSettings()->setValue( key, QVariant::fromValue( widths ) );
}

void TreeViewHelper::loadColumnWidths( const QString& key, const QList<int>& defaultWidths )
{
    int count = m_view->model()->columnCount();

    QList<int> widths = application->applicationSettings()
            ->value( key ).value<LocalSettings::IntList>();

    if ( widths.count() != count )
        widths = defaultWidths;

    for ( int i = 0; i < count; i++ )
        m_view->setColumnWidth( i, widths.value( i, 150 ) );
}

void TreeViewHelper::saveColumnWidths( const QString& key, const QList<int>& columns )
{
    int count = m_view->model()->columnCount();

    QMap<int, int> widths = dataManager->connectionSettings()
            ->value( key ).value<LocalSettings::IntMap>();

    for ( int i = 0; i < count; i++ ) {
        if ( !m_view->isColumnHidden( i ) )
            widths.insert( columns.at( i ), m_view->columnWidth( i ) );
    }

    dataManager->connectionSettings()->setValue( key,
                    QVariant::fromValue( widths ) );
}

void TreeViewHelper::loadColumnWidths( const QString& key, const QList<int>& columns, const QMap<int, int>& defaultWidths )
{
    int count = m_view->model()->columnCount();

    QMap<int, int> widths = dataManager->connectionSettings()
            ->value( key ).value<LocalSettings::IntMap>();

    for ( int i = 0; i < count; i++ )
        m_view->setColumnWidth( i, widths.value( columns.at( i ), defaultWidths.value( columns.at( i ), 150 ) ) );
}

void TreeViewHelper::saveExpandedNodes( const QString& key )
{
    SqlTreeModel* model = qobject_cast<SqlTreeModel*>( m_view->model() );
    if ( !model )
        return;

    QList<ExpandedNode> nodes;

    QList<QModelIndex> indexes;
    indexes.append( QModelIndex() );

    while ( !indexes.isEmpty() ) {
        QModelIndex parent = indexes.takeFirst();

        int count = model->rowCount( parent );

        for ( int i = 0; i < count; i++ ) {
            QModelIndex index = model->index( i, 0, parent );
            if ( m_view->isExpanded( index ) ) {
                nodes.append(ExpandedNode( model->levelOf( index ),
                                               model->rowId( index ) ) );
                indexes.append( index );
            }
        }
    }

    dataManager->connectionSettings()->setValue( key,
                QVariant::fromValue( nodes ) );
}

void TreeViewHelper::loadExpandedNodes( const QString& key )
{
    SqlTreeModel* model = qobject_cast<SqlTreeModel*>( m_view->model() );
    if ( !model )
        return;

    QList<ExpandedNode> nodes = dataManager->connectionSettings()
            ->value( key ).value<ExpandedNodeList>();

    foreach ( const ExpandedNode& node, nodes ) {
        QModelIndex index = model->findIndex( node.m_level, node.m_id, 0 );
        if ( index.isValid() )
            m_view->setExpanded( index, true );
    }
}

AutoToolTipDelegate::AutoToolTipDelegate( QObject* parent ) : QStyledItemDelegate( parent )
{
}

AutoToolTipDelegate::~AutoToolTipDelegate()
{
}

bool AutoToolTipDelegate::helpEvent( QHelpEvent* e, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& index )
{
    if ( !e || !view )
        return false;

    if ( e->type() == QEvent::ToolTip ) {
        QRect rect = view->visualRect( index );
        QSize size = sizeHint( option, index );
        if ( rect.width() < size.width() ) {
            QVariant tooltip = index.data( Qt::DisplayRole );
            if ( tooltip.canConvert<QString>() ) {
                QToolTip::showText( e->globalPos(), QString( "<div>%1</div>" ).arg( tooltip.toString().toHtmlEscaped() ), view );
                return true;
            }
        }
        if ( !QStyledItemDelegate::helpEvent( e, view, option, index ) )
            QToolTip::hideText();
        return true;
    }

    return QStyledItemDelegate::helpEvent( e, view, option, index );
}
