TEMPLATE = subdirs

SUBDIRS += \
    CommandLineParserHelper \
    ProcessHelper \
    downloader \
    settings \
    SignalHelper \
    StringHelper \
    FileHelper \
    ini \
    TextFileHelper \
    xml \

file.depends = StringHelper
ini.depends = StringHelper
settings.depends = StringHelper ini FileHelper
xml.depends = StringHelper ini FileHelper


