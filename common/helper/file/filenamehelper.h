#ifndef ZFILENAMEHELPER_H
#define ZFILENAMEHELPER_H

#include <QRegularExpression>
#include <QString>

namespace com::helper{
class FilenameHelper
{
public:
    static const QString urlpattern;
    static const QRegularExpression urlregexp;


    static bool isURL(const QString& path);
    static bool isAppLocal(const QString& path);
    static bool isRelative(const QString& path);
};
} // namespace com::helper
#endif // ZFILENAMEHELPER_H
