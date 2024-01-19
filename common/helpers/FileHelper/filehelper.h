#ifndef COM_ZTEXTFILEHELPER_H
#define COM_ZTEXTFILEHELPER_H


#include <QFile>
#include <QFileInfo>
#include <QString>
//#include <QTextCodec>
#include <QTextStream>
#include "filehelper_global.h"

namespace com { namespace helpers{
class FILEHELPERSHARED_EXPORT FileHelper
{
public:

    enum Errors:int{
        Ok = 0,
        NoFileName,
        PathIsNotAbsolute,
        FileNotExists,
        CannotRead,
        CannotWrite
    };
    static void SetVerbose(bool v){_verbose = v;}
    static void save(const QString& txt, const QString& fileName, bool isAppend = false);
    static auto Save(const QByteArray& data, const QString& fn, bool isAppend = false, QFileDevice::FileError* = nullptr)-> bool;
    static QString load(const QString& filename);
    //static void append(QString line, QString fileName);
    bool backup(const QString& filename);
    static bool isEmpty(const QFileInfo& fi);
    static bool isEmpty(const QString& dir);

    static bool FnValidate(const QString& filename, Errors *err);
    static QString GetFileName(const QString &fn);
    static bool Exists(const QString& fn);
    static bool Delete(const QString& fn);


private:
    static bool _verbose;
    static QString load2(const QString& filename);
};
}
} // namespace com::helper
#endif // ZTEXTFILEHELPER_H
