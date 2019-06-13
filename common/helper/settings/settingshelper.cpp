#include "settingshelper.h"
#include "../../helper/ini/inihelper.h"
#include "../../helper/file/filehelper.h"
//#include <QSettings>
//#include <QApplication>
#include <QDir>
namespace com::helper
{

QString SettingsHelper::settingsPath;
QString SettingsHelper::settingsFile;
const QString SettingsHelper::NAME = QStringLiteral("settings");
ISettings* SettingsHelper::s;

SettingsHelper::SettingsHelper()
{
    //settingsFile= getFileName();
}

void SettingsHelper::init(const QString& _settingsPath, ISettings* _s)
{
    settingsPath = _settingsPath;
    settingsFile = getFileName();
    s = _s;
}

bool SettingsHelper::loadSettings()
{
    if(settingsFile.isEmpty()) return false;
    if(!s) return false;
    if(!QFile::exists(settingsFile)) return false;
    auto txt = FileHelper::load(settingsFile);
    auto map = IniHelper::parseIni(txt);
    s->parseIni(map);
    return true;
}

void SettingsHelper::saveSettings()
{
    if(settingsFile.isEmpty()) return;
    if(!s) return;

    auto m = s->toIni();
    auto txt = IniHelper::toString(m, NAME);
    FileHelper::save(txt, settingsFile);
}

QString SettingsHelper::getFileName()
{
    if(settingsPath.isEmpty()) return QString();
    return settingsPath+QDir::separator() + NAME+".ini";
}
}  // namespace com
