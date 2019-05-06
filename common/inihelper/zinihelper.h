#ifndef ZINIHELPER_H
#define ZINIHELPER_H


#include "inihelper_global.h"
#include <QString>
#include <QMap>

class INIHELPERSHARED_EXPORT zIniHelper
{

public:
    static QMap<QString, QString> parseIni(const QString& ini);
    static QString toString(const QMap<QString, QString>&, const QString&);
};

#endif // ZINIHELPER_H
