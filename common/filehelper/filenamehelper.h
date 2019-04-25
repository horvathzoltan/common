#ifndef ZFILENAMEHELPER_H
#define ZFILENAMEHELPER_H

#include <QRegularExpression>
#include <QString>

class zFileNameHelper
{
public:
    static const QString urlpattern;
    static const QRegularExpression urlregexp;


    static bool isURL(const QString& path);
    static bool isAppLocal(const QString& path);
    static bool isRelative(const QString& path);
};

#endif // ZFILENAMEHELPER_H
