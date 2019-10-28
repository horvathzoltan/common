message(QMAKE_PLATFORM: $$QMAKE_PLATFORM)
message(QMAKE_COMPILER: $$QMAKE_COMPILER)
message(QMAKE_COMPILER_DEFINES: $$QMAKE_COMPILER_DEFINES)
message(MAKEFILE_GENERATOR: $$MAKEFILE_GENERATOR)

TEMPLATE = subdirs

SUBDIRS += \
    libinstall \
    common \
    test2

test2.depends = common

CONFIG += c++1z
msvc:QMAKE_CXXFLAGS += /std:c++17
