#include "filterheader.h"

FilterHeader::FilterHeader()
{

}

    //filterActivated = QtCore.pyqtSignal()

//    def __init__(self, parent):
  //      super().__init__(QtCore.Qt.Horizontal, parent)
        int _editors = [];
        int _padding = 4;
        setStretchLastSection(True);
        setSectionResizeMode(Stretch);
        setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setSortIndicatorShown(False);
        sectionResized.connect(adjustPositions);
        parent.horizontalScrollBar().valueChanged.connect(adjustPositions);

    def setFilterBoxes(self, count):
        while _editors:
            editor = _editors.pop()
            editor.deleteLater()
        for index in range(count):
            editor = QtWidgets.QLineEdit(parent())
            editor.setPlaceholderText('Filter')
            editor.setClearButtonEnabled(True)
            editor.returnPressed.connect(filterActivated.emit)
            _editors.append(editor)
        adjustPositions()

    def sizeHint(self):
        size = super().sizeHint()
        if _editors:
            height = _editors[0].sizeHint().height()
            size.setHeight(size.height() + height + _padding)
        return size

    def updateGeometries(self):
        if _editors:
            height = _editors[0].sizeHint().height()
            setViewportMargins(0, 0, 0, height + _padding)
        else:
            setViewportMargins(0, 0, 0, 0)
        super().updateGeometries()
        adjustPositions()

    def adjustPositions(self):
        for index, editor in enumerate(_editors):
            height = editor.sizeHint().height()
            editor.move(
                sectionPosition(index) - offset() + 2,
                height + (_padding // 2))
            editor.resize(sectionSize(index), height)

    def filterText(self, index):
        if 0 <= index < len(_editors):
            return _editors[index].text()
        return ''

    def setFilterText(self, index, text):
        if 0 <= index < len(_editors):
            _editors[index].setText(text)

    def clearFilters(self):
        for editor in _editors:
            editor.clear()
