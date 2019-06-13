#ifndef ZLOCINFO_H
#define ZLOCINFO_H

#include <QString>

class LocInfo
{
public:
    QString func;
    QString file;
    int line;

    LocInfo(const char *func, const char *file, int line);
    QString toString() const;
};

#endif // ZLOCINFO_H
