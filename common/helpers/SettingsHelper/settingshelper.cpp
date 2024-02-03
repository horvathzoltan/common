#include "settingshelper.h"
#include "../../helpers/IniHelper/inihelper.h"
#include "../../helpers/TextFileHelper/textfilehelper.h"
//#include <QSettings>
//#include <QApplication>
#include <QDir>
namespace com{ namespace helpers{

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

    FileHelper:: Errors err;
        QStringList lines = TextFileHelper::LoadLines(globalSettingsFileName, &err);
    if(err == FileHelper::Errors::Ok)
    {
        auto map = IniHelper::Parse(lines, ',');
        s->parseIni(map);
        isok = true;
    }


    lines = TextFileHelper::LoadLines(userSettingsFileName, &err);
    if(err == FileHelper::Errors::Ok)
    {
        auto map = IniHelper::Parse(lines, ',');
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
}
}  // namespace com
