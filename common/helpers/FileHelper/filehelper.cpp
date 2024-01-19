//#include "globals.h"
#include "../../macrofactory/macro.h"
#include "filehelper.h"
//#include "../../helpers/StringHelper//stringhelper.h"
#include "../../logger/log.h"
#include "filenamehelper.h"
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QIODevice>
#include <QTextCodec>

namespace com {
namespace helpers{

QString FileHelper::load2(const QString& filename) {
    auto ikey = Log::openInfo(QStringLiteral("Beolvasás: %1").arg(filename));
    QFileInfo fi(filename);    
    if(!fi.isAbsolute())
    {
        zInfo(zfn()+" "+QStringLiteral("nem abszolut path: %1").arg(filename));
        Log::appendInfo(ikey, "error");
        Log::closeInfo(ikey);
        //return zStringHelper::Empty;
    }

    if(!fi.exists())
    {
        zInfo(QStringLiteral("a fájl nem létezik: %1").arg(filename));
        Log::appendInfo(ikey, "error");
        Log::closeInfo(ikey);
        return QString();
    }    

    QFile f(filename);
    QString e;   

    // TODO ha relatív a filename, akkor abszolúttá kell tenni
    // egyébként megnyitható azaz

    if (f.open(QFile::ReadOnly | QFile::Text))  {
        Log::appendInfo(ikey, Log::OK);
        Log::closeInfo(ikey);
        //zInfo(QStringLiteral("Beolvasás: %1").arg(filename));
        e =  QTextStream(&f).readAll();
    }
    else{
        Log::appendInfo(ikey, Log::ERROR_);
        Log::closeInfo(ikey);
        zInfo(QStringLiteral("A fájl nem nyitható meg: %1 %2").arg(filename, Log::ERROR_));
        e= QString();
    }
    Log::closeInfo(ikey);
    return e;
}

/*
A txt-t nem feltétlenül kell itt validálni
- üres fájl mentése/létrehozása lehet egy valós igény
*/

void FileHelper::save(const QString& txt, const QString& fn, bool isAppend)
{
    if(fn.length()>256)
    {
        zInfo(QStringLiteral("Fájlnév túl hosszú: %1 %2").arg(fn, Log::ERROR_));
        return;
    }
//    QFile logfile(lfn);
//    logfile.open(QIODevice::Append | QIODevice::Text);
//    QTextStream out(&logfile);
//    out << lftxt << endl;

    QFileInfo fi(fn);
    QDir a = fi.dir();
    if(!a.exists())
    {
        a.mkpath(".");
    }

    QFile f(fn);

    QFlags<QIODevice::OpenModeFlag> om = QIODevice::WriteOnly | QIODevice::Text; // openmode
    if(isAppend) om |= QIODevice::Append;

    if (!f.open(om))
    {
        auto err = f.error();
        auto errDesc = f.errorString();
        //
        auto errstr = QStringLiteral("nem menthető: %1 %2:%3").arg(fn).arg(err).arg(errDesc);
        //zError2(errstr,1);
        Log::error2(errstr, getLocInfo);
        return;
    }


    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QTextStream out(&f);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out.setGenerateByteOrderMark(true);
    out << txt.toUtf8();
    f.close();
    //QFileInfo fi(fn);
    zInfo(QStringLiteral("File saved: %1").arg(fi.absoluteFilePath()));
}

auto FileHelper::Save(const QByteArray& data, const QString& fn, bool isAppend, QFileDevice::FileError*err) -> bool
{
    if(fn.length()>256) return false;
    QFileInfo fi(fn);
    QDir a = fi.dir();

    if(!a.exists()) a.mkpath(QStringLiteral("."));
    QFile f(fn);
    QFlags<QIODevice::OpenModeFlag> om = QIODevice::WriteOnly; // openmode
    if(isAppend) om |= QIODevice::Append;

    if (!f.open(om))
    {
        if(err) *err = f.error();
        return false;
    }

    auto u = f.write(data);
    if(u==-1 && err) *err = f.error();
    f.close();
    return u != -1;
}

// TODO ha URL vagy ha filename wrapper file megszerzésére
//

QString FileHelper::load(const QString& url)
{
    if(FilenameHelper::isURL(url))
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

    QString outfilename = com::helpers::FilenameHelper::appendToBaseName(filename, now);

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
    bool valid = FnValidate(filename, nullptr);
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


bool FileHelper::FnValidate(const QString& filename, Errors *err)
{
    bool valid = true;
    if(filename.isEmpty())
    {
        if(_verbose) zInfo(QStringLiteral("no file name").arg(filename));
        if(err != nullptr) *err= Errors::NoFileName;
        valid = false;
    }else{
        QFileInfo fi(filename);

        if(!fi.isAbsolute())
        {
            if(_verbose) zInfo(QStringLiteral("path is not absolute: %1").arg(filename));
            if(err != nullptr) *err= Errors::PathIsNotAbsolute;
            valid = false;
        }

        if(!fi.exists())
        {
            if(_verbose) zInfo(QStringLiteral("file not exist: %1").arg(filename));
            if(err != nullptr) *err= Errors::FileNotExists;
            valid = false;
        }
    }

    return valid;
}

}  // namespace helper
}  // namespace com
