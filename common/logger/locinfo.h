#ifndef COM_ZLOCINFO_H
#define COM_ZLOCINFO_H

#include <QString>
#include "logger_global.h"

class LOGGERSHARED_EXPORT LocInfo
{
public:
    QString func;
    QString file;
    int line;

    LocInfo(const char *func, const char *file, int line);
    QString toString() const;
};

#endif // ZLOCINFO_H
