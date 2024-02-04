#ifndef COM_ZSETTINGSHELPER_H
#define COM_ZSETTINGSHELPER_H

#include "settingshelper_global.h"
#include "isettings.h"
#include <QString>

namespace com { namespace helpers{
class COM_SETTINGSHELPERSHARED_EXPORT SettingsHelper
{
public:
    SettingsHelper();
    static bool LoadSettings();
    static bool SaveSettings();
    static void init(const QString &, ISettings *);
private:
    static QString _userSettingsFileName;
    static QString _globalSettingsFileName;
    static const QString NAME;
    static ISettings *_s;
};
}
}  // namespace com
#endif // ZSETTINGSHELPER_H

