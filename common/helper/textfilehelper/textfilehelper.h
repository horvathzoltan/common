#ifndef COM_TEXTFILEHELPER_H
#define COM_TEXTFILEHELPER_H

#include "textfilehelper_global.h"
#include <QStringList>

namespace com::helper{
class TEXTFILEHELPER_EXPORT TextFileHelper
{
public:
    static QString load(const QString& filename);
    static QStringList loadLines(const QString& filename);
    static bool save(const QString& txt, const QString& fileName, bool isAppend = false);
    static bool backup(const QString& filename);
};
}
#endif // TEXTFILEHELPER_H
