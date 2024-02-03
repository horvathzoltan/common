#include "../../macros/macro.h"
#include "../../helpers/StringHelper/stringhelper.h"
#include "xmlhelper.h"

#include <QDateTime>

namespace com { namespace helpers{
bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QString& n, QString *ptr){
    if(a.hasAttribute(n)){
        *ptr = (a.value(n)).toString();
        return true;
    }
    return false;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QString& n, int *ptr){
    if(a.hasAttribute(n)){
        *ptr = (a.value(n)).toInt();
        return true;
    }
    return false;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QString& n, bool *ptr){
    if(a.hasAttribute(n)){
        QString b = (a.value(n)).toString();
        *ptr = StringHelper::toBool(b);
        return true;
    }
    return false;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QString& n, QDateTime *ptr){
    if(a.hasAttribute(n)){
        QString b = (a.value(n)).toString();
        *ptr = QDateTime::fromString(b);
        return true;
    }
    return false;
}

// aliases

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, QString *ptr){
    for(auto&n0: n){
        putXmlAttr(a, n0, ptr);
    }
    return true;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, int *ptr){
    for(auto&n0: n){
        putXmlAttr(a, n0, ptr);
    }
    return true;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, bool *ptr){
    for(auto&n0: n){
        putXmlAttr(a, n0, ptr);
    }
    return true;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, QDateTime *ptr){
    for(auto&n0: n){
        putXmlAttr(a, n0, ptr);
    }
    return true;
}
}
} // namespace com::helper
