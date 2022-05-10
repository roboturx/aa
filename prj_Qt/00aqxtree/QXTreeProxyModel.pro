# -------------------------------------------------
# Project created by QtCreator 2011-01-01T10:37:11
# -------------------------------------------------
QT += sql gui widgets
TARGET = QXTreeProxyModel
TEMPLATE = app

INCLUDEPATH +=  ../   /../../../../boost_1_79_0/boost/
SOURCES += main.cpp \
    testdialog.cpp \
    qxtreeproxymodel.cpp \
    mysqlrelationaldelegate.cpp
HEADERS += testdialog.h \
    qxtreeproxymodel.h \
    mysqlrelationaldelegate.h
FORMS += testdialog.ui
exists(../ModelTest-0_2/modeltest.pri) { 
    DEFINES += MODEL_TEST
    include(../ModelTest-0_2/modeltest.pri)
}
DEFINES += ONMANUALSUBMIT=1 \
    ONFIELDCHANGE=2 \
    ONROWCHANGE=3 \
    QSQLTABLEMODEL=1 \
    QSQLRELATIONALTABLEMODEL=2 \
    QSTANDARDITEMMODEL=3
#DEFINES += SUBMITOPTION=ONMANUALSUBMIT

# DEFINES += SUBMITOPTION=ONROWCHANGE
 DEFINES += SUBMITOPTION=ONFIELDCHANGE
 DEFINES += AUTOINCREMENT
DEFINES += TABLEMODEL=QSQLRELATIONALTABLEMODEL
OTHER_FILES += README.txt
