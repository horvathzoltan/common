#include "inihelper.h"
#include "../../macrofactory/macro.h"
#include "../../helper/string/stringhelper.h"

namespace com::helper{
QMap<QString, QString> IniHelper::parseIni(const QString& ini)
{
    QMap<QString, QString> m;

    if(ini.isEmpty()) return m;
    auto inilist = com::helper::StringHelper::toStringList(ini);

    zforeach(i, inilist)
    {
        if(i->isEmpty()||i->startsWith('#')) continue;
        auto kl = i->split('=');
        if(kl.count()==2)
        {
            m.insert(kl[0], kl[1]);
        }
    }
    return m;
}

QString IniHelper::toString(const QMap<QString, QString> &m, const QString &desc)
{
    QString e;
    e+=QStringLiteral("# ")+desc + " ini"+com::helper::StringHelper::NewLine+com::helper::StringHelper::NewLine;
    zforeach(i, m)
    {
        e+=i.key()+"="+i.value()+com::helper::StringHelper::NewLine;
    }
    return e;
}

}//namespace com::helper
