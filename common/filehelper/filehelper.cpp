//#include "globals.h"
#include "../macrofactory/macro.h"
#include "filehelper.h"
#include "../stringhelper/stringhelper.h"
#include "../zlog/zlog.h"
#include "filenamehelper.h"
#include <QFileInfo>
#include <QDir>

QString zFileHelper::load2(const QString& filename) {
    auto ikey = zLog::openInfo(QStringLiteral("Beolvasás: %1").arg(filename));
    QFileInfo fi(filename);    
    if(!fi.isAbsolute())
    {
        zInfo(zfn()+" "+QStringLiteral("nem abszolut path: %1").arg(filename));
        zLog::appendInfo(ikey, "error");
        zLog::closeInfo(ikey);
        //return zStringHelper::Empty;
    }

    if(!fi.exists())
    {
        zInfo(QStringLiteral("a fájl nem létezik: %1").arg(filename));
        zLog::appendInfo(ikey, "error");
        zLog::closeInfo(ikey);
        return zStringHelper::Empty;
    }    

    QFile f(filename);
    QString e;   

    // TODO ha relatív a filename, akkor abszolúttá kell tenni
    // egyébként megnyitható azaz

    if (f.open(QFile::ReadOnly | QFile::Text))  {
        zLog::appendInfo(ikey, zLog::OK);
        zLog::closeInfo(ikey);
        //zInfo(QStringLiteral("Beolvasás: %1").arg(filename));
        e =  QTextStream(&f).readAll();
    }
    else{
        zLog::appendInfo(ikey, zLog::ERROR);
        zLog::closeInfo(ikey);
        zInfo(QStringLiteral("A fájl nem nyitható meg: %1 %2").arg(filename, zLog::ERROR));
        e= zStringHelper::Empty;
    }
    zLog::closeInfo(ikey);
    return e;
}

/*
A txt-t nem feltétlenül kell itt validálni
- üres fájl mentése/létrehozása lehet egy valós igény
*/

void zFileHelper::save(const QString& txt, const QString& fn, bool isAppend) {

    if(fn.length()>256)
    {
        zInfo(QStringLiteral("Fájlnév túl hosszú: %1 %2").arg(fn, zLog::ERROR));
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

    auto om = QIODevice::WriteOnly | QFile::Text; // openmode
    if(isAppend) om |= QIODevice::Append;

    if (!f.open(om))
    {
        auto err = f.error();
        auto errDesc = f.errorString();
        //
        auto errstr = QStringLiteral("nem menthető: %1 %2:%3").arg(fn).arg(err).arg(errDesc);
        zLog::dialogError(errstr);
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


// TODO ha URL vagy ha filename wrapper file megszerzésére
//

QString zFileHelper::load(const QString& url)
{
    if(zFileNameHelper::isURL(url))
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
