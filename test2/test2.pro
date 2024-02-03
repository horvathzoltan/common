QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++14
msvc:QMAKE_CXXFLAGS += /std:c++14

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

equals(BUILD,release){
    COMMON_LIBS = $$COMMON_LIBS"_release"
}

#equals(BUILD,release) {
#    #message( "build is _ release" )
#}
#message( "QT_ARCH= "$$QT_ARCH )
#message( "QMAKE_TARGET.arch= "$$QMAKE_TARGET.arch )

equals(QT_ARCH, x86_64){
    COMMON_LIBS = $$COMMON_LIBS"_64"
}

equals(QT_ARCH, x86){
    COMMON_LIBS = $$COMMON_LIBS"_32"
}

equals(QT_ARCH, arm){
#    COMMON_LIBS = $$COMMON_LIBS"_arm"
    MV33 = $$find(QMAKE_CFLAGS, -march.*)
    MV34 = $$split(MV33, =)
    MARCH = $$member(MV34, 1)
    COMMON_LIBS = $$COMMON_LIBS"_"$$MARCH
}

message( "architecture = "$$QT_ARCH )
message( "commonlibs folder = "$$COMMON_LIBS )

#unix:HOME = $$system(echo $HOME)
#win32:HOME = $$system(echo %userprofile%)

# INSTALLDIR = $$COMMON_LIBS
COMMON_LIBS_FULLPATH = $$shell_path($$HOME/$$COMMON_LIBS)

message("COMMON_LIBS_FULLPATH: " $$COMMON_LIBS_FULLPATH);
message("COMMON_LIBS: " $$COMMON_LIBS);

#itt nem az installdirből kellene felszedni, hanem a fordítottból
#unix:!macx: LIBS += -L$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper/ -lstringhelper
#unix:!macx: LIBS += -L$$PWD/../../$$INSTALLDIR/ -lstringhelper
unix:!macx:
{
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lStringHelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lTextFileHelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lFileNameHelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lFileHelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lshortguid
LIBS += -L$$COMMON_LIBS_FULLPATH/ -llogger
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -lmacrofactory
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lIniHelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lSettingsHelper
}

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../build-common-Desktop_Qt_5_9_0_GCC_64bit-Debug/stringhelper"
#QMAKE_LFLAGS += -Wl,-rpath,"$$PWD/../../$$INSTALLDIR"
# QMAKE_LFLAGS += -Wl,-rpath, "$$system_path($$HOME/$$INSTALLDIR)"


#target.path = += $$[QT_INSTALL_PLUGINS]/stringhelper
#target.files += /stringhelper/stringhelper.so
#INSTALLS += target
