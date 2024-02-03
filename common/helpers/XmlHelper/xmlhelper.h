#ifndef COM_XMLHELPER_H
#define COM_XMLHELPER_H

#include "xmlhelper_global.h"
#include <QXmlStreamWriter>

namespace com { namespace helpers{
class COM_XMLHELPERSHARED_EXPORT XmlHelper
{

public:
    static bool putXmlAttr(const QXmlStreamAttributes&, const QString& n, QString *ptr);
    static bool putXmlAttr(const QXmlStreamAttributes&, const QString& n, int *ptr);
    static bool putXmlAttr(const QXmlStreamAttributes&, const QString& n, bool *ptr);
    static bool putXmlAttr(const QXmlStreamAttributes&, const QString& n, QDateTime *ptr);


    static bool putXmlAttr(const QXmlStreamAttributes&, const QStringList& n, QString *ptr);
    static bool putXmlAttr(const QXmlStreamAttributes&, const QStringList& n, int *ptr);
    static bool putXmlAttr(const QXmlStreamAttributes&, const QStringList& n, bool *ptr);
    static bool putXmlAttr(const QXmlStreamAttributes&, const QStringList& n, QDateTime *ptr);
};
}
} // namespace com::helper
#endif // XMLHELPER_H
