#include "humanproxymodel.h"

HumanProxyModel::HumanProxyModel()
{

}

HumanProxyModel lessThan(QString source_left, QString source_right);
{
data_left = source_left.data()
        data_right = source_right.data()
        if type(data_left) == type(data_right) == str:
        return _human_key(data_left) < _human_key(data_right)
        return super(HumanProxyModel, self).lessThan(source_left, source_right)
        }
//   @property
void filters()
{
    if (not hasattr("_filters"))
    {
        _filters = [];
        return _filters;
    }
}
// @filters.setter
void filters( filters)
{
    print(f"filters() called.")

            self._filters = filters
            self.invalidateFilter()
}
bool  filterAcceptsRow( int sourceRow, int sourceParent)
{
    for i, text in self.filters:
        if 0 <= i < self.columnCount():
      ix = self.sourceModel().index(sourceRow, i, sourceParent)
      data = ix.data()
      if text not in data:
      return false
      return true
}


      float _human_key(key)
    {
        parts = re.split(r'(\d*\.\d+|\d+)', key)
                return tuple((e.swapcase() if i % 2 == 0 else float(e))
                             for i, e in enumerate(parts))
    }
