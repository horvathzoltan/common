//#include "globals.h"
//#include "../../macros/macro.h"
#include "filehelper.h"
//#include "../../helpers/StringHelper//stringhelper.h"
#include "../../logger/logger.h"
#include "../FileNameHelper/filenamehelper.h"
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QIODevice>
#include <QChar>
//#include <QTextCodec>

namespace com {
namespace helpers{

bool FileHelper::_verbose = false;

QString FileHelper::load2(const QString& filename)
{
    bool valid = FnValidator::Validate_Load(filename, nullptr);
    if(!valid) return QString();

    QFile f(filename);

    bool ok = f.open(QFile::ReadOnly | QFile::Text);
    if (!ok)  {
        if(_verbose) zInfo(QStringLiteral("A fájl nem nyitható meg: %1 %2").arg(filename, "error"));
        return QString();
    }

    QString e;
    e =  QTextStream(&f).readAll();
    return e;
}

/*
A txt-t nem feltétlenül kell itt validálni
- üres fájl mentése/létrehozása lehet egy valós igény
*/

bool FileHelper::Save(const QString& txt, const QString& filename, FileErrors *err){
    return Save_private(txt, filename, err, false);
}

bool FileHelper::Append(const QString& txt, const QString& filename, FileErrors *err){
    return Save_private(txt, filename, err, true);
}

bool FileHelper::Save(const QByteArray& txt, const QString& filename, FileErrors *err){
    return Save_private(txt, filename, err, false);
}

bool FileHelper::Append(const QByteArray& txt, const QString& filename, FileErrors *err){
    return Save_private(txt, filename, err, true);
}

bool FileHelper::Save_private(const QString& txt, const QString& filename, FileErrors *err, bool isAppend)
{    
    bool valid = FnValidator::Validate_Save(filename, err);
    if(!valid) return false;


    QFileInfo fi(filename);
    // QDir a = fi.dir();
    // if(!a.exists())
    // {
    //     a.mkpath(".");
    // }

    QFile f(filename);

    QFlags<QIODevice::OpenModeFlag> om = QIODevice::WriteOnly | QIODevice::Text; // openmode
    if(isAppend) om |= QIODevice::Append;

    bool ok = f.open(om);
    if (!ok)
    {
        auto errDesc = f.errorString();
        if(_verbose) zInfo(QStringLiteral("cannot save: %1, %2").arg(filename, errDesc));
        if(err != nullptr) *err = FileErrors::CannotWrite;
        return false;
    }

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QTextStream out(&f);
    //out.setCodec(QTextCodec::codecForName("UTF-8"));
    //out.setGenerateByteOrderMark(true);
    out << txt.toUtf8();
    f.close();
    //QFileInfo fi(fn);
    zInfo(QStringLiteral("File saved: %1").arg(fi.absoluteFilePath()));
    return true;
}

bool FileHelper::Save_private(const QByteArray& data, const QString& fn, FileErrors *err, bool isAppend)
{
    if(fn.length()>256) return false;
    QFileInfo fi(fn);
    QDir a = fi.dir();

    if(!a.exists()) a.mkpath(QStringLiteral("."));
    QFile f(fn);
    QFlags<QIODevice::OpenModeFlag> om = QIODevice::WriteOnly; // openmode
    if(isAppend) om |= QIODevice::Append;

    bool ok = f.open(om);
    if (!ok)
    {
        auto errDesc = f.errorString();
        if(_verbose) zInfo(QStringLiteral("cannot save: %1, %2").arg(fn, errDesc));
        if(err != nullptr) *err = FileErrors::CannotWrite;
        return false;
    }

    auto u = f.write(data);
    if(u==-1 && err){
        auto errDesc = f.errorString();
        if(_verbose) zInfo(QStringLiteral("cannot save: %1, %2").arg(fn, errDesc));
        if(err != nullptr) *err = FileErrors::CannotWrite;
        return false;
    }
    f.close();
    return u != -1;
}

// TODO ha URL vagy ha filename wrapper file megszerzésére
//

QString FileHelper::Load(const QString& url)
{
    if(FileNameHelper::isURL(url))
    {
    //zInfo("url");
    //auto e = downloader.download(QStringLiteral(R"(https://docs.google.com/document/export?format=html&id=1tPwsVMObxU9QmA3XR4RpbHPpjcG7hVbd7KQqLD_ABK8&includes_info_params=true)"));
    //return zStringHelper::HtmlDecode(e);
    }

    // ha nem absolut, akkor kell a project mappa a beállításokból
    //QString fn = zFileNameHelper::getCurrentProjectFileNameAbsolut(url);
    QString fn = url;
    return load2(fn);
}

//void zTextFileHelper::append(QString fn, QString txt){
//    save(txt, fn, true);
//}

bool FileHelper::backup(const QString& filename)
{
    QFile infile(filename);

    QString now = QDateTime::currentDateTime().toString("yyyyMMdd_hh:mm:ss");

    QString outfilename = com::helpers::FileNameHelper::appendToBaseName(filename, now);

    return QFile::copy(filename, outfilename);
}

auto FileHelper::isEmpty(const QFileInfo &fi) -> bool
{
    if(!fi.isDir()) return false;
    return QDir(fi.absoluteFilePath()).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries|QDir::Hidden).isEmpty();
}

auto FileHelper::isEmpty(const QString &fn) -> bool
{
    return isEmpty(QFileInfo(fn));
}

/**/
QString FileHelper::GetFileName(const QString &fn)
{
    QFileInfo fi(fn);
    QString e = fi.fileName();
    return e;
}

bool FileHelper::Exists(const QString &filename)
{
    bool valid = FnValidator::Validate_Load(filename, nullptr);
    if(!valid) return false;

    return true;
}

bool FileHelper::Delete(const QString &filename)
{
    bool valid = Exists(filename);
    if(!valid) return false;
    bool ok = QFile::remove(filename);
    return ok;
}


// bool FileHelper::FnValidate_Load(const QString& filename, FileErrors *err)
// {
//     bool valid = FnValidate_Save(filename, err);

//     if(!valid) return false;

//     QFileInfo fi(filename);

//     if(!fi.exists())
//     {
//         if(_verbose) zInfo(QStringLiteral("file not exist: %1").arg(filename));
//         if(err != nullptr) *err= Errors::FileNotExists;
//         return false;
//     }

//     return true;
// }

// bool FileHelper::FnValidate_Save(const QString& filename, Errors *err)
// {
//     if(filename.isEmpty())
//     {
//         if(_verbose) zInfo(QStringLiteral("no file name").arg(filename));
//         if(err != nullptr) *err= Errors::NoFileName;
//         return false;
//     }

//     if(filename.length()>256)
//     {
//         if(_verbose) zInfo(QStringLiteral("filename too long: %1").arg(filename));
//         if(err!=nullptr) *err = FileHelper::Errors::FileNameTooLong;
//         return false;
//     }

//     QFileInfo fi(filename);

//     if(!fi.isAbsolute())
//     {
//         if(_verbose) zInfo(QStringLiteral("path is not absolute: %1").arg(filename));
//         if(err != nullptr) *err= Errors::PathIsNotAbsolute;
//         return false;
//     }

//     return true;
// }

}  // namespace helper
}  // namespace com
