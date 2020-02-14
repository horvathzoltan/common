QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++1z
msvc:QMAKE_CXXFLAGS += /std:c++17

TEMPLATE = app

SOURCES +=  tst_test2.cpp


#/home/zoli/build-test1-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper
#libstringhelper.so

unix:HOME = $$system(echo $HOME)
win32:HOME = $$system(echo %userprofile%)

CONFIG(debug, debug|release){
BUILD = debug
} else {
BUILD = release
}

COMMON_LIBS = commonlib

equals(BUILD,debug) {
    #message( "build is _ debug" )
    COMMON_LIBS = $$COMMON_LIBS"_debug"
}
#equals(BUILD,release) {
#    #message( "build is _ release" )
#}


!contains(QMAKE_TARGET.arch, x86_64) {
    !contains(QT_ARCH, x86_64) {
        COMMON_LIBS = $$COMMON_LIBS"_32"
    }
}

unix:HOME = $$system(echo $HOME)
win32:HOME = $$system(echo %userprofile%)

# INSTALLDIR = $$COMMON_LIBS
COMMON_LIBS_FULLPATH = $$shell_path($$HOME/$$COMMON_LIBS)

#itt nem az installdirből kellene felszedni, hanem a fordítottból
#unix:!macx: LIBS += -L$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper/ -lstringhelper
#unix:!macx: LIBS += -L$$PWD/../../$$INSTALLDIR/ -lstringhelper
unix:!macx:
{
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lstringhelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lfilehelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lshortguid
LIBS += -L$$COMMON_LIBS_FULLPATH/ -llogger
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lmacrofactory
LIBS += -L$$COMMON_LIBS_FULLPATH/ -linihelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lsettingshelper
}

#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper"
#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../$$INSTALLDIR"
# QMAKE_LFLAGS += -Wl,-rpath, "$$system_path($$HOME/$$INSTALLDIR)"

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

#target.path = += $$[QT_INSTALL_PLUGINS]/stringhelper
#target.files += /stringhelper/stringhelper.so
#INSTALLS += target
