#include "../../macrofactory/macro.h"
#include "../../helper/string/stringhelper.h"
#include "xmlhelper.h"

#include <QDateTime>

namespace com::helper{
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
        *ptr = com::helper::StringHelper::toBool(b);
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
    zforeach(n0, n){
        if(putXmlAttr(a, *n0, ptr)) return true;
    }
    return false;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, int *ptr){
    zforeach(n0, n){
        if(putXmlAttr(a, *n0, ptr)) return true;
    }
    return false;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, bool *ptr){
    zforeach(n0, n){
        if(putXmlAttr(a, *n0, ptr)) return true;
    }
    return false;
}

bool XmlHelper::putXmlAttr(const QXmlStreamAttributes& a, const QStringList& n, QDateTime *ptr){
    zforeach(n0, n){
        if(putXmlAttr(a, *n0, ptr)) return true;
    }
    return false;
}
} // namespace com::helper
