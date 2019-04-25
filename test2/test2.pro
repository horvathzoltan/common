QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test2.cpp


#/home/zoli/build-test1-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper
#libstringhelper.so

HOME = $$system(echo $HOME)
INSTALLDIR = commonlib

#itt nem az installdirből kellene felszedni, hanem a fordítottból
#unix:!macx: LIBS += -L$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper/ -lstringhelper
#unix:!macx: LIBS += -L$$PWD/../../$$INSTALLDIR/ -lstringhelper
unix:!macx: LIBS += -L$$HOME/$$INSTALLDIR/ -lstringhelper

#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper"
#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../$$INSTALLDIR"
QMAKE_LFLAGS += -Wl,-rpath,"$$HOME/$$INSTALLDIR"

INCLUDEPATH += $$PWD/../stringhelper
DEPENDPATH += $$PWD/../stringhelper

#target.path = += $$[QT_INSTALL_PLUGINS]/stringhelper
#target.files += /stringhelper/stringhelper.so
#INSTALLS += target
