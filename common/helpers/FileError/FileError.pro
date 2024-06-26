#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T08:27:00
#
#-------------------------------------------------

QT       -= gui

#TARGET = fileerror
TEMPLATE = lib

DEFINES += COM_FILEERROR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fileerror.cpp

HEADERS += \
    fileerror.h \
    fileerror_global.h \    

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17

include($$PWD/../../../libinstall//common.prf)

unix:!macx:
{
LIBS += -L$$HOME/$$COMMON_LIBS/ -llogger
}

win32:
{
WINLIBS = $$system_path($$HOME/$$COMMON_LIBS/)
LIBS += -L$$WINLIBS -llogger
#message(win32libs=$$WINLIBS)
}

#INCLUDEPATH += $$PWD
#DEPENDPATH += $$PWD

include($$PWD/../../../libinstall//libinstall.prf)
#HOME = $$system(echo $HOME)
#INSTALLDIR = commonlib
#createdir.commands = $(MKDIR) $$HOME/$$INSTALLDIR
#copydata.commands = $(COPY_FILE) $$quote(-r) $$OUT_PWD/*.so* $$HOME/$$INSTALLDIR
#first.depends = $(first) createdir copydata
#export(first.depends)
#export(createdir.commands)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first createdir copydata

# DISTFILES +=

