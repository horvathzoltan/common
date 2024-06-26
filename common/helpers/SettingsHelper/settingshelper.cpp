#include "settingshelper.h"
#include "../../helpers/IniHelper/inihelper.h"
#include "../../helpers/FileHelper/filehelper.h"
#include "../../helpers/TextFileHelper/textfilehelper.h"
//#include <QSettings>
//#include <QApplication>
#include <QDir>
namespace com{ namespace helpers{

QString SettingsHelper::_userSettingsFileName;
//QString SettingsHelper::settingsFile;
QString SettingsHelper::_globalSettingsFileName;
const QString SettingsHelper::NAME = QStringLiteral("settings");
ISettings* SettingsHelper::_s;

SettingsHelper::SettingsHelper()
{
    //settingsFile= getFileName();
}

void SettingsHelper::init(const QString& userFN, ISettings* _s)
{
    _userSettingsFileName = userFN;
    //settingsFile = getFileName();
    _globalSettingsFileName = NAME+".ini";
    _s = _s;
}


bool SettingsHelper::LoadSettings()
{
    bool isok = false;
    if(!_s) return false;

    FileErrors err;
    QStringList lines = TextFileHelper::LoadLines(_globalSettingsFileName, &err);
    if(err == FileErrors::Ok)
    {
        auto map = IniHelper::Parse(lines, ',');
        _s->parseIni(map);
        isok = true;
    }


    lines = TextFileHelper::LoadLines(_userSettingsFileName, &err);
    if(err == FileErrors::Ok)
    {
        auto map = IniHelper::Parse(lines, ',');
        _s->parseIni(map);
        isok=true;
    }
    return isok;
}

bool SettingsHelper::SaveSettings()
{
    if(_userSettingsFileName.isEmpty()) return false;
    if(!_s) return false;

    auto m = _s->toIni();
    auto txt = IniHelper::toString(m, NAME);
    FileErrors err;

    FileHelper::Save(txt, _userSettingsFileName, &err);
    return err == FileErrors::Ok;
}

//QString SettingsHelper::getFileName()
//{
//    if(userSettingsFileName.isEmpty()) return QString();
//    return userSettingsFileName+QDir::separator() + NAME+".ini";
//}
}
}  // namespace com
