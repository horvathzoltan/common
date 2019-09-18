#ifndef ZTEXTFILEHELPER_H
#define ZTEXTFILEHELPER_H


#include <QFile>
#include <QString>
#include <QTextCodec>
#include <QTextStream>
#include "filehelper_global.h"

namespace com::helper{
class FILEHELPERSHARED_EXPORT FileHelper
{
public:
    static void save(const QString& txt, const QString& fileName, bool isAppend = false);
    static QString load(const QString& filename);
    //static void append(QString line, QString fileName);
    bool backup(const QString& filename);
private:
    static QString load2(const QString& filename);
};
} // namespace com::helper
#endif // ZTEXTFILEHELPER_H
