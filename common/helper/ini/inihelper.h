#ifndef ZINIHELPER_H
#define ZINIHELPER_H


#include "inihelper_global.h"
#include <QString>
#include <QMap>
namespace com::helper{
class INIHELPERSHARED_EXPORT IniHelper
{

public:
    static QMap<QString, QString> parseIni(const QString& ini);
    static QString toString(const QMap<QString, QString>&, const QString&);
};
} //namespace com::helper
#endif // ZINIHELPER_H
