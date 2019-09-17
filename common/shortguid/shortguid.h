#ifndef ZSHORTGUID_H
#define ZSHORTGUID_H

#include "shortguid_global.h"
#include <QUuid>

class SHORTGUIDSHARED_EXPORT zShortGuid
{
public:
    zShortGuid();
    //zShortGuid(QString value);
    static const zShortGuid Empty;

    explicit zShortGuid(QUuid guid);

    QUuid uuid;
    QString value;

    static zShortGuid createNew();

    static QString Encode(QUuid);
    static QUuid Decode(QString);
};

#endif // ZSHORTGUID_H
