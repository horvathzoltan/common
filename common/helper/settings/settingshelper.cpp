#include "settingshelper.h"
#include "../../helper/ini/inihelper.h"
#include "../../helper/file/filehelper.h"
//#include <QSettings>
//#include <QApplication>
#include <QDir>
namespace com::helper
{

QString SettingsHelper::userSettingsFileName;
//QString SettingsHelper::settingsFile;
QString SettingsHelper::globalSettingsFileName;
const QString SettingsHelper::NAME = QStringLiteral("settings");
ISettings* SettingsHelper::s;

SettingsHelper::SettingsHelper()
{
    //settingsFile= getFileName();
}

void SettingsHelper::init(const QString& userFN, ISettings* _s)
{
    userSettingsFileName = userFN;
    //settingsFile = getFileName();
    globalSettingsFileName = NAME+".ini";
    s = _s;
}


bool SettingsHelper::loadSettings()
{
    bool isok = false;
    if(!s) return false;
    if(QFile::exists(globalSettingsFileName)){
        auto txt = FileHelper::load(globalSettingsFileName);
        auto map = IniHelper::parseIni(txt);
        s->parseIni(map);
        isok=true;
    }

    if(QFile::exists(userSettingsFileName))
    {
        auto txt = FileHelper::load(userSettingsFileName);
        auto map = IniHelper::parseIni(txt);
        s->parseIni(map);
        isok=true;
    }
    return isok;
}

void SettingsHelper::saveSettings()
{
    if(userSettingsFileName.isEmpty()) return;
    if(!s) return;

    auto m = s->toIni();
    auto txt = IniHelper::toString(m, NAME);
    FileHelper::save(txt, userSettingsFileName);
}

//QString SettingsHelper::getFileName()
//{
//    if(userSettingsFileName.isEmpty()) return QString();
//    return userSettingsFileName+QDir::separator() + NAME+".ini";
//}
}  // namespace com
