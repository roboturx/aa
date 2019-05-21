QT += widgets
  requires(qtConfig(completer))

  HEADERS   = \
              mainwindow.h
  SOURCES   = \
              main.cpp \
              mainwindow.cpp
  RESOURCES = completer.qrc

  # install
   target.path = $$/home/mr/test
   INSTALLS += target
