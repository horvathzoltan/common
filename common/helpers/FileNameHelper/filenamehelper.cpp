#include "filenamehelper.h"
#include <QCoreApplication>
#include <QDir>

namespace com { namespace helpers{
const QString FileNameHelper::urlpattern = QStringLiteral(R"(^(?:http(s)?:\/\/)?[\w.-]+(?:\.[\w\.-]+){2,}[\w\-\._~:\/?#[\]@!\$&'\(\)\*\+,;=.]+$)");

const QRegularExpression FileNameHelper::urlregexp = QRegularExpression(urlpattern);
QString FileNameHelper::_projectPath;
bool FileNameHelper::_isTest=false;
bool FileNameHelper::_inited=false;


bool FileNameHelper::Init(const char *file)
{
    _inited = false;

#if defined (STRING) && defined (TARGI) && defined (SOURCE_PATH)
    Q_UNUSED(file)
    _projectPath = STRING(SOURCE_PATH);
#else
    bool valid = file != nullptr;
    if(valid){
        QString path(file);
        if(path.endsWith("/helpers/filenamehelper.h")){
            auto ap = QFileInfo(path).absoluteDir();
            ap.cdUp();
            _projectPath = ap.absolutePath();
            _inited = true;
        }
    }
#endif

    return _inited;
}


bool FileNameHelper::isURL(const QString &path)
{
    return urlregexp.match(path).hasMatch();
}

bool FileNameHelper::isAppLocal(const QString &path)
{

    if(!path.contains(QDir::separator())) return true;
    //TODO
    //QString p = zFileNameHelper::append(QDir::homePath(), beallitasok.approot);
    QString p = "aaa";
    if(path.startsWith(p)) return true;
    return false;
}

bool FileNameHelper::isRelative(const QString &path)
{
    QFileInfo fi(path);
    return fi.isRelative();
}


QString FileNameHelper::appendToBaseName(const QString& fileName, const QString& a)
{
    QFileInfo fi(fileName);

    QString ns = QFileInfo(fi.dir(), fi.baseName()+"_"+a+"."+fi.completeSuffix()).filePath();

    return ns;
}

QString FileNameHelper::GetAbsolutPath(const QString& dirName, bool isCreate){
    auto projectDir = QDir(QDir::homePath()).filePath(dirName);
    if(isCreate)
    {
        if(!QDir(projectDir).exists())
            QDir(QDir::homePath()).mkpath(projectDir);
    }
    return projectDir;
}

QString FileNameHelper::GetTestFolderPath()
{
    auto pp = QDir(_projectPath).filePath("testdata");
    return pp;
}

QString FileNameHelper::GetWorkingFolder()
{
    QString workingFolder = _isTest?FileNameHelper::GetTestFolderPath():qApp->applicationDirPath();
    return workingFolder;
}

}
} // namespace namespace com::helper
