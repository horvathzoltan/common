#ifndef COM_TEXTFILEHELPER_H
#define COM_TEXTFILEHELPER_H

#include "textfilehelper_global.h"
#include <QStringList>
#include <QTextStream>

#include "../../helpers/FileHelper//filehelper.h"

namespace com { namespace helpers{
class TEXTFILEHELPER_EXPORT TextFileHelper
{
private:
    static bool _verbose;
public:    

    void SetVerbose(bool v){ _verbose = v;}

    static void SetUtf8Encoding(QTextStream* st);

    static QString Load(const QString& filename, FileHelper::Errors *err);
    static QStringList LoadLines(const QString& filename, FileHelper::Errors *err);
    static QStringList LoadLinesContains(const QString& filename, const QStringList& t1, FileHelper::Errors *err);

    static bool Save(const QString& txt, const QString& fileName, FileHelper::Errors *err, bool isAppend = false);
    static bool backup(const QString& filename);
};
}
}
#endif // TEXTFILEHELPER_H
