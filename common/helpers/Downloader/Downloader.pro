QT -= gui
QT += network

TEMPLATE = lib
DEFINES += COM_DOWNLOADER_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    downloader.cpp

HEADERS += \
    downloader_global.h \
    downloader.h

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++17

include($$PWD/../../../libinstall//common.prf)

unix:!macx:
{
LIBS += -L$$HOME/$$COMMON_LIBS/ -llogger -lProcessHelper
}

# win32:
# {
# WINLIBS = $$system_path($$HOME/$$COMMON_LIBS/)
# LIBS += -L$$WINLIBS -llogger -lprocesshelper
# }

include($$PWD/../../../libinstall//libinstall.prf)
