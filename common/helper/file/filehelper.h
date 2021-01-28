#ifndef COM_ZTEXTFILEHELPER_H
#define COM_ZTEXTFILEHELPER_H


#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QTextCodec>
#include <QTextStream>
#include "filehelper_global.h"

namespace com::helper{
class FILEHELPERSHARED_EXPORT FileHelper
{
public:
    static void save(const QString& txt, const QString& fileName, bool isAppend = false);
    static auto Save(const QByteArray& data, const QString& fn, bool isAppend = false, QFileDevice::FileError* = nullptr)-> bool;
    static QString load(const QString& filename);
    //static void append(QString line, QString fileName);
    bool backup(const QString& filename);
    static bool isEmpty(const QFileInfo& fi);
    static bool isEmpty(const QString& dir);
private:
    static QString load2(const QString& filename);
};
} // namespace com::helper
#endif // ZTEXTFILEHELPER_H
