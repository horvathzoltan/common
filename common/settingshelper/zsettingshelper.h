#ifndef ZSETTINGSHELPER_H
#define ZSETTINGSHELPER_H

#include "settingshelper_global.h"
#include "isettings.h"
#include <QString>

class SETTINGSHELPERSHARED_EXPORT zSettingsHelper
{
public:
    zSettingsHelper();
    static bool loadSettings();
    static void saveSettings();
    static void init(const QString &, ISettings *);
private:
    static QString settingsPath;
    static ISettings *s;
    static QString settingsFile;
    static const QString NAME;
    static QString getFileName();
};

#endif // ZSETTINGSHELPER_H

