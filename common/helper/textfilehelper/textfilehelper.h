#ifndef TEXTFILEHELPER_H
#define TEXTFILEHELPER_H

#include "textfilehelper_global.h"
#include <QStringList>

namespace com::helper{
class TEXTFILEHELPER_EXPORT TextFileHelper
{
public:
    static QString load(const QString& filename);
    static QStringList loadLines(const QString& filename);
    static void save(const QString& txt, const QString& fileName, bool isAppend = false);
    static bool backup(const QString& filename);
};
}
#endif // TEXTFILEHELPER_H
