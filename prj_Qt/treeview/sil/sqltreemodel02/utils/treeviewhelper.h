
#ifndef TREEVIEWHELPER_H
#define TREEVIEWHELPER_H

#include <QMap>
#include <QPair>
#include <QStyledItemDelegate>

class QTreeView;
class QModelIndex;
class QHelpEvent;
class QAbstractItemView;
class QStyleOptionViewItem;

/**
* Helper class for reading and applying settings of a tree view.
*/
class TreeViewHelper
{
public:
    enum ViewFlag
    {
        TreeStyle = 1,
        MultiSelect = 2,
        NotSortable = 4,
        NoAutoToolTip = 8
    };

    Q_DECLARE_FLAGS( ViewFlags, ViewFlag )

public:
    /**
    * Constructor.
    * @param view The associated tree view.
    */
    TreeViewHelper( QTreeView* view );

    /**
    * Destructor.
    */
    ~TreeViewHelper();

public:
    /**
    * Initialize common properties of the tree view.
    */
    void initializeView( ViewFlags flags = TreeStyle );

    /**
    * Return the index of selected item in the view.
    */
    QModelIndex selectedIndex();

    /**
    * Save static column widths from the tree view.
    */
    void saveColumnWidths( const QString& key );

    /**
    * Load static column widths to the tree view.
    */
    void loadColumnWidths( const QString& key, const QList<int>& defaultWidths );

    /**
    * Save dynamic column widths from the tree view.
    */
    void saveColumnWidths( const QString& key, const QList<int>& columns );

    /**
    * Load dynamic column widths to the tree view.
    */
    void loadColumnWidths( const QString& key, const QList<int>& columns, const QMap<int, int>& defaultWidths );

    /**
    * Save expanded nodes from the tree view.
    */
    void saveExpandedNodes( const QString& key );

    /**
    * Load expanded nodes to the tree view.
    */
    void loadExpandedNodes( const QString& key );

private:
    QTreeView* m_view;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( TreeViewHelper::ViewFlags )

class AutoToolTipDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    AutoToolTipDelegate( QObject* parent );
    ~AutoToolTipDelegate();

public slots:
    bool helpEvent( QHelpEvent* e, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& index );
};

#endif
