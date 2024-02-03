#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T21:24:07
#
#-------------------------------------------------

QT       -= gui

#TARGET = xmlhelper
TEMPLATE = lib

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17

DEFINES += COM_XMLHELPER_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../../../libinstall//common.prf)

SOURCES += \
        xmlhelper.cpp

HEADERS += \
        xmlhelper.h \
        xmlhelper_global.h 

unix:!macx:
{
LIBS += -L$$HOME/$$COMMON_LIBS/ -llogger -lStringHelper
}

win32:
{
WINLIBS = $$system_path($$HOME/$$COMMON_LIBS/)
LIBS += -L$$WINLIBS -lStringHelper
#message(win32libs=$$WINLIBS)
}

include($$PWD/../../../libinstall//libinstall.prf)

#HOME = $$system(echo $HOME)
#INSTALLDIR = commonlib

#unix {
#    target.path = /home/zoli/commonlib; #$$HOME/$$INSTALLDIR;#/usr/lib
#    INSTALLS += target
#}
