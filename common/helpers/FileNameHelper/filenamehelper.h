#ifndef COM_ZFILENAMEHELPER_H
#define COM_ZFILENAMEHELPER_H

#include <QRegularExpression>
#include <QString>
#include "filenamehelper_global.h"

namespace com { namespace helpers{
class COM_FILENAMEHELPERSHARED_EXPORT FileNameHelper
{
private:
    static QString _projectPath;
    static bool _isTest;
    static bool _inited;
public:
    static bool Init(const char *file = __FILE__);
    static void SetTestMode(bool v){_isTest=v;};

    static const QString urlpattern;
    static const QRegularExpression urlregexp;


    static bool isURL(const QString& path);
    static bool isAppLocal(const QString& path);
    static bool isRelative(const QString& path);

    static QString appendToBaseName(const QString& fileName, const QString& a );
    static QString GetAbsolutPath(const QString &dirName, bool isCreate = false);

    static QString GetTestFolderPath();
    static QString GetWorkingFolder();
};
}
} // namespace com::helper
#endif // ZFILENAMEHELPER_H
