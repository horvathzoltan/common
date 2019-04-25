#include "filenamehelper.h"
#include <QDir>

const QString zFileNameHelper::urlpattern = QStringLiteral(R"(^(?:http(s)?:\/\/)?[\w.-]+(?:\.[\w\.-]+){2,}[\w\-\._~:\/?#[\]@!\$&'\(\)\*\+,;=.]+$)");

const QRegularExpression zFileNameHelper::urlregexp = QRegularExpression(urlpattern);

bool zFileNameHelper::isURL(const QString &path)
{
    return urlregexp.match(path).hasMatch();
}

bool zFileNameHelper::isAppLocal(const QString &path)
{

    if(!path.contains(QDir::separator())) return true;
    //TODO
    //QString p = zFileNameHelper::append(QDir::homePath(), beallitasok.approot);
    QString p = "aaa";
    if(path.startsWith(p)) return true;
    return false;
}

bool zFileNameHelper::isRelative(const QString &path)
{
    QFileInfo fi(path);
    return fi.isRelative();
}
