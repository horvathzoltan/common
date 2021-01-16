TEMPLATE = subdirs

SUBDIRS += \
    CommandLineParserHelper \
    ProcessHelper \
    downloader \
    settings \
    signalhelper \
    string \
    file \
    ini \
    textfilehelper \
    xml \

file.depends = string
ini.depends = string
settings.depends = string ini file
xml.depends = string ini file


