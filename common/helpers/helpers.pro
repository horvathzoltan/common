TEMPLATE = subdirs

SUBDIRS += \
    CommandLineParserHelper \
    ProcessHelper \
    Downloader \
    settings \
    SignalHelper \
    StringHelper \
    FileHelper \
    IniHelper \
    TextFileHelper \
    xml \
    NetworkHelper \

FileHelper.depends = StringHelper
IniHelper.depends = StringHelper
settings.depends = StringHelper IniHelper FileHelper
xml.depends = StringHelper IniHelper FileHelper


