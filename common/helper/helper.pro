TEMPLATE = subdirs

SUBDIRS += \
    settings \
    string \
    file \
    ini \
    xml \

file.depends = string
ini.depends = string
settings.depends = string ini file
xml.depends = string ini file

