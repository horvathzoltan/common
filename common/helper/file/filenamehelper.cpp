#include "filenamehelper.h"
#include <QDir>

namespace com::helper{
const QString FilenameHelper::urlpattern = QStringLiteral(R"(^(?:http(s)?:\/\/)?[\w.-]+(?:\.[\w\.-]+){2,}[\w\-\._~:\/?#[\]@!\$&'\(\)\*\+,;=.]+$)");

const QRegularExpression FilenameHelper::urlregexp = QRegularExpression(urlpattern);

bool FilenameHelper::isURL(const QString &path)
{
    return urlregexp.match(path).hasMatch();
}

bool FilenameHelper::isAppLocal(const QString &path)
{

    if(!path.contains(QDir::separator())) return true;
    //TODO
    //QString p = zFileNameHelper::append(QDir::homePath(), beallitasok.approot);
    QString p = "aaa";
    if(path.startsWith(p)) return true;
    return false;
}

bool FilenameHelper::isRelative(const QString &path)
{
    QFileInfo fi(path);
    return fi.isRelative();
}


QString FilenameHelper::appendToBaseName(const QString& fileName, const QString& a)
{
    QFileInfo fi(fileName);

    QString ns = QFileInfo(fi.dir(), fi.baseName()+"_"+a+"."+fi.completeSuffix()).filePath();

    return ns;
}
} // namespace namespace com::helper
