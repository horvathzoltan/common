#ifndef ZTEXTFILEHELPER_H
#define ZTEXTFILEHELPER_H


#include <QFile>
#include <QString>
#include <QTextCodec>
#include <QTextStream>

namespace com::helper{
class FileHelper
{
public:
    static void save(const QString& txt, const QString& fileName, bool isAppend = false);
    static QString load(const QString& filename);
    //static void append(QString line, QString fileName);
private:
    static QString load2(const QString& filename);
};
} // namespace com::helper
#endif // ZTEXTFILEHELPER_H