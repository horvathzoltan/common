#include "textfilehelper.h"
#include "../../logger/log.h"

#include <QFileInfo>
#include <QTextCodec>
#include <QTextStream>

namespace com::helper{


QString TextFileHelper::load(const QString& filename) {
    QFileInfo fi(filename);
    if(!fi.isAbsolute())
    {
        zInfo(QStringLiteral("path is not absolute: %1").arg(filename));
        return QString();
    }

    if(!fi.exists())
    {
        zInfo(QStringLiteral("file not exist: %1").arg(filename));
        return QString();
    }

    QFile f(filename);
    QString e;

    // TODO ha relatív a filename, akkor abszolúttá kell tenni
    // egyébként megnyitható azaz

    if (f.open(QFile::ReadOnly | QFile::Text))  {
        zInfo(QStringLiteral("loaded: %1").arg(filename));
        QTextStream st(&f);
        st.setCodec("UTF-8");
        e = st.readAll();
    }
    else{
        zInfo(QStringLiteral("cannot open file: %1 ERROR").arg(filename));
        e= QString();
    }
    return e;
}

QStringList TextFileHelper::loadLines(const QString& filename) {
    QFileInfo fi(filename);
    if(!fi.isAbsolute())
    {
        zInfo(QStringLiteral("path is not absolute: %1").arg(filename));
        return QStringList();
    }

    if(!fi.exists())
    {
        zInfo(QStringLiteral("file not exist: %1").arg(filename));
        return QStringList();
    }

    QFile f(filename);
    QStringList e;

    // TODO ha relatív a filename, akkor abszolúttá kell tenni
    // egyébként megnyitható azaz

    if (f.open(QFile::ReadOnly | QFile::Text))  {
        zInfo(QStringLiteral("loaded: %1").arg(filename));
        QTextStream st(&f);
        st.setCodec("UTF-8");

        while (!st.atEnd())
        {
            e << st.readLine();
        }
        f.close();

    }
    else{
        zInfo(QStringLiteral("cannot open file: %1 ERROR").arg(filename));
        e= QStringList();
    }
    return e;
}


bool TextFileHelper::save(const QString& txt, const QString& fn, bool isAppend) {

//    QFile logfile(lfn);
//    logfile.open(QIODevice::Append | QIODevice::Text);
//    QTextStream out(&logfile);
//    out << lftxt << endl;

    QFile f(fn);

    auto om = QIODevice::WriteOnly | QIODevice::Text; // openmode
    if(isAppend) om |= QIODevice::Append;

    if (!f.open(om)){
        zError(QStringLiteral("cannot open file to write or append: ")+fn);
        //zLog::dialogError("nem menthető: "+fn);
        return false;
        }


    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QTextStream out(&f);
    //out.setCodec(QTextCodec::codecForName("UTF-8"));
    //out.setGenerateByteOrderMark(true);
    out << txt;//.toUtf8();
    f.close();
    return true;
}

} // namespace com::helper
