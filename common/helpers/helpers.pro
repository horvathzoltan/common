TEMPLATE = subdirs

SUBDIRS += \
    CommandLineParserHelper \
    ProcessHelper \
    Downloader \
    SettingsHelper \
    SignalHelper \
    StringHelper \
    FileNameHelper \
    FileHelper \
    IniHelper \
    TextFileHelper \
    XmlHelper \
    NetworkHelper \

FileHelper.depends = StringHelper
IniHelper.depends = StringHelper
SettingsHelper.depends = StringHelper FileHelper FileNameHelper TextFileHelper IniHelper
XmlHelper.depends = StringHelper FileHelper FileNameHelper TextFileHelper IniHelper
Downloader.depends = ProcessHelper


