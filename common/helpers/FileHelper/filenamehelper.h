#ifndef COM_ZFILENAMEHELPER_H
#define COM_ZFILENAMEHELPER_H

#include <QRegularExpression>
#include <QString>
#include "filehelper_global.h"

namespace com { namespace helpers{
class FILEHELPERSHARED_EXPORT FilenameHelper
{
public:
    static const QString urlpattern;
    static const QRegularExpression urlregexp;


    static bool isURL(const QString& path);
    static bool isAppLocal(const QString& path);
    static bool isRelative(const QString& path);

    static QString appendToBaseName(const QString& fileName, const QString& a );
    static QString GetAbsolutPath(const QString &dirName, bool isCreate = false);
};
}
} // namespace com::helper
#endif // ZFILENAMEHELPER_H
