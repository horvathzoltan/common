#ifndef ZFILENAMEHELPER_H
#define ZFILENAMEHELPER_H

#include <QRegularExpression>
#include <QString>
#include "filehelper_global.h"

namespace com::helper{
class FILEHELPERSHARED_EXPORT FilenameHelper
{
public:
    static const QString urlpattern;
    static const QRegularExpression urlregexp;


    static bool isURL(const QString& path);
    static bool isAppLocal(const QString& path);
    static bool isRelative(const QString& path);

    static QString appendToBaseName(const QString& fileName, const QString& a );
};
} // namespace com::helper
#endif // ZFILENAMEHELPER_H
