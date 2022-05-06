QT += widgets sql
requires(qtConfig(treeview))

FORMS       = mainwindow.ui
HEADERS     = mainwindow.h \
              treeitem.h \
              treemodel.h \
              treesqlitem.h \
              treesqlmodel.h \
              viadecksqlmodel.h \
              viadecsqlitem.h
RESOURCES   = editabletreemodel.qrc
SOURCES     = mainwindow.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp \
              treesqlitem.cpp \
              treesqlmodel.cpp \
              viadecksqlmodel.cpp \
              viadecsqlitem.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
