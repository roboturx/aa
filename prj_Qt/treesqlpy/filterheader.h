#ifndef FILTERHEADER_H
#define FILTERHEADER_H

#include <QHeaderView>

class FilterHeader : public QHeaderView
{

        //filterActivated = QtCore.pyqtSignal()
      public:
          FilterHeader();



        void setFilterBoxes(int count);
        QSize sizeHint();

        void updateGeometries();
            void adjustPositions();
            QString filterText(QModelIndex &index);

        void setFilterText(QModelIndex &index, QString &text);
        void clearFilters();

};

#endif // FILTERHEADER_H
