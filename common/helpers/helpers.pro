TEMPLATE = subdirs

SUBDIRS += \
    CommandLineParserHelper \
    ProcessHelper \
    Downloader \
    SettingsHelper \
    SignalHelper \
    StringHelper \
    FileError \
    FileNameHelper \
    FileHelper \
    IniHelper \
    TextFileHelper \
    XmlHelper \
    NetworkHelper \

FileHelper.depends = StringHelper
IniHelper.depends = StringHelper
TextFileHelper.depends = FileError FileHelper
SettingsHelper.depends = StringHelper FileError FileHelper FileNameHelper TextFileHelper IniHelper
XmlHelper.depends = StringHelper FileError FileHelper FileNameHelper TextFileHelper IniHelper
Downloader.depends = ProcessHelper


