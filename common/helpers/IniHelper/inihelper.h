#ifndef COM_ZINIHELPER_H
#define COM_ZINIHELPER_H


#include "inihelper_global.h"
#include <QString>
#include <QMap>
namespace com { namespace helpers{
class COM_INIHELPERSHARED_EXPORT IniHelper
{

public:
    static QMap<QString, QString> Parse(const QStringList& lines,const QChar& sep='=');
    static bool TryGetValue(QMap<QString, QString>m, const QString& key, QString *value);

    static QString toString(const QMap<QString, QString>&, const QString&);
};
}
} //namespace com::helper
#endif // ZINIHELPER_H
