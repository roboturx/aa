#ifndef HUMANPROXYMODEL_H
#define HUMANPROXYMODEL_H

#include <QSortFilterProxyModel>

class HumanProxyModel : public QSortFilterProxyModel
{
public:
    HumanProxyModel();

    _human_key lessThan(self, source_left, source_right):
           //     return _human_key(data_left) < _human_key(data_right)
           // return super(HumanProxyModel, self).lessThan(source_left, source_right)
       void _human_key(key);


        void filters();
            //return self._filters
        filters(filters);
        filterAcceptsRow(sourceRow, sourceParent);
};

#endif // HUMANPROXYMODEL_H
