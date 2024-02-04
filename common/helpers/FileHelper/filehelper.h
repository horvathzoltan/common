#ifndef COM_ZTEXTFILEHELPER_H
#define COM_ZTEXTFILEHELPER_H


#include <QFile>
#include <QFileInfo>
#include <QString>
//#include <QTextCodec>
#include <QTextStream>
#include "filehelper_global.h"

namespace com { namespace helpers{
class COM_FILEHELPERSHARED_EXPORT FileHelper
{
public:

    enum Errors:int{
        Ok = 0,
        NoFileName,
        PathIsNotAbsolute,
        FileNotExists,
        CannotRead,
        CannotWrite, FileNameTooLong
    };
    static void SetVerbose(bool v){_verbose = v;}
    static bool Save(const QString& txt, const QString& fileName, FileHelper::Errors *err);
    static bool Save(const QByteArray& data, const QString& fn, FileHelper::Errors *err);
    static bool Append(const QString& txt, const QString& fileName, FileHelper::Errors *err);
    static bool Append(const QByteArray& data, const QString& fn, FileHelper::Errors *err);

    static QString Load(const QString& filename);
    //static void append(QString line, QString fileName);
    bool backup(const QString& filename);
    static bool isEmpty(const QFileInfo& fi);
    static bool isEmpty(const QString& dir);

    static bool FnValidate_Load(const QString& filename, Errors *err);
    static bool FnValidate_Save(const QString& filename, Errors *err);
    static QString GetFileName(const QString &fn);
    static bool Exists(const QString& fn);
    static bool Delete(const QString& fn);


private:
    static bool _verbose;
    static QString load2(const QString& filename);

    static bool Save_private(const QString& txt, const QString& fileName, FileHelper::Errors *err, bool isAppend);
    static bool Save_private(const QByteArray& data, const QString& fn, FileHelper::Errors *err, bool isAppend);
};
}
} // namespace com::helper
#endif // ZTEXTFILEHELPER_H
