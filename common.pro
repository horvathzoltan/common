TEMPLATE = subdirs

SUBDIRS += \
    libinstall \
    common \
    test2

test2.depends = common

CONFIG += c++1z
QMAKE_CXXFLAGS += /std:c++17
