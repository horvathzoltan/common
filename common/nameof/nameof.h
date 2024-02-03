#ifndef NAMEOF_H
#define NAMEOF_H

#include "nameof_global.h"

#include <QRegularExpression>
#include <QString>

#define nameof(x) NameOf::_nameof_ulong(#x, sizeof(x))
#define nameof_fn(x) NameOf::_nameof_fn(#x, (void*)x)

class COM_NAMEOF_EXPORT NameOf
{
private:
    static QString NameOf_private(const QString &x);
public:
    static QString _nameof_fn(const char *y, void *);
    static QString _nameof(const char *y, std::size_t);
    static QString _nameof_ulong(char const *y, unsigned long);
};

#endif // NAMEOF_H
