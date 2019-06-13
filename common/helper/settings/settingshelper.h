#ifndef ZSETTINGSHELPER_H
#define ZSETTINGSHELPER_H

#include "settingshelper_global.h"
#include "isettings.h"
#include <QString>

namespace com::helper{
class SETTINGSHELPERSHARED_EXPORT SettingsHelper
{
public:
    SettingsHelper();
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
}  // namespace com
#endif // ZSETTINGSHELPER_H
