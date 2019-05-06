#include "zsettingshelper.h"
#include "../inihelper/zinihelper.h"
#include "../filehelper/filehelper.h"
#include <QSettings>
//#include <QApplication>
#include <QDir>

QString zSettingsHelper::settingsPath;
QString zSettingsHelper::settingsFile;
const QString zSettingsHelper::NAME = QStringLiteral("settings");
ISettings* zSettingsHelper::s;

zSettingsHelper::zSettingsHelper()
{
    //settingsFile= getFileName();
}

void zSettingsHelper::init(const QString& _settingsPath, ISettings* _s)
{
    settingsPath = _settingsPath;
    settingsFile = getFileName();
    s = _s;
}

bool zSettingsHelper::loadSettings()
{
    if(settingsFile.isEmpty()) return false;
    if(!s) return false;
    if(!QFile::exists(settingsFile)) return false;
    auto txt = zFileHelper::load(settingsFile);    
    auto map = zIniHelper::parseIni(txt);    
    s->parseIni(map);
    return true;
}

void zSettingsHelper::saveSettings()
{
    if(settingsFile.isEmpty()) return;
    if(!s) return;

    auto m = s->toIni();
    auto txt = zIniHelper::toString(m, NAME);
    zFileHelper::save(txt, settingsFile);
}

QString zSettingsHelper::getFileName()
{
    if(settingsPath.isEmpty()) return QString();
    return settingsPath+QDir::separator() + NAME+".ini";
}
