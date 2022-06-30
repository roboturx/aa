CONFIG	    += console debug
HEADERS	    += ../aqp/kuhn_munkres.hpp
SOURCES	    += ../aqp/kuhn_munkres.cpp
HEADERS	    += ../aqp/alt_key.hpp
SOURCES	    += ../aqp/alt_key.cpp
HEADERS	    += ../aqp/aqp.hpp
SOURCES	    += ../aqp/aqp.cpp
RESOURCES   += ../aqp/aqp.qrc
INCLUDEPATH += ../aqp
HEADERS	    += ../main/richtextlineedit.hpp
SOURCES	    += ../main/richtextlineedit.cpp
HEADERS	    += ../main/richtextdelegate.hpp
SOURCES	    += ../main/richtextdelegate.cpp
HEADERS	    += ../main/global.hpp
HEADERS	    += ../main/mainwindow.hpp
SOURCES     += ../main/mainwindow.cpp
SOURCES     += ../main/main.cpp
RESOURCES   += ../main/timelog.qrc
INCLUDEPATH += ../main
DEFINES	    += CUSTOM_MODEL
HEADERS	    += ../main/taskitem.hpp
SOURCES	    += ../main/taskitem.cpp
HEADERS	    += ../main/treemodel.hpp
SOURCES     += ../main/treemodel.cpp
QT += widgets sql  #added for Qt5
win32 { INCLUDEPATH += . }



debug {
    exists(../modeltest-0.2/modeltest.pri) {
	DEFINES	    += MODEL_TEST
	include(../modeltest-0.2/modeltest.pri)
    }
}
