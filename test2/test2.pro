QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++1z
QMAKE_CXXFLAGS += /std:c++17

TEMPLATE = app

SOURCES +=  tst_test2.cpp


#/home/zoli/build-test1-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper
#libstringhelper.so

unix:HOME = $$system(echo $HOME)
win32:HOME = $$system(echo %userprofile%)

INSTALLDIR = commonlib

#itt nem az installdirből kellene felszedni, hanem a fordítottból
#unix:!macx: LIBS += -L$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper/ -lstringhelper
#unix:!macx: LIBS += -L$$PWD/../../$$INSTALLDIR/ -lstringhelper
unix:!macx:
{
LIBS += -L$$HOME/$$INSTALLDIR/ -lstringhelper
LIBS += -L$$HOME/$$INSTALLDIR/ -lfilehelper
LIBS += -L$$HOME/$$INSTALLDIR/ -lshortguid
LIBS += -L$$HOME/$$INSTALLDIR/ -llogger
LIBS += -L$$HOME/$$INSTALLDIR/ -lmacrofactory
LIBS += -L$$HOME/$$INSTALLDIR/ -linihelper
LIBS += -L$$HOME/$$INSTALLDIR/ -lsettingshelper
}

#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper"
#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../$$INSTALLDIR"
# QMAKE_LFLAGS += -Wl,-rpath, "$$system_path($$HOME/$$INSTALLDIR)"

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

#target.path = += $$[QT_INSTALL_PLUGINS]/stringhelper
#target.files += /stringhelper/stringhelper.so
#INSTALLS += target
