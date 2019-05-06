#include "zinihelper.h"
#include "../macrofactory/macro.h"
#include "../stringhelper/stringhelper.h"

QMap<QString, QString> zIniHelper::parseIni(const QString& ini)
{
    QMap<QString, QString> m;

    if(ini.isEmpty()) return m;
    auto inilist = zStringHelper::toStringList(ini);

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

QString zIniHelper::toString(const QMap<QString, QString> &m, const QString &desc)
{
    QString e;
    e+=QStringLiteral("# ")+desc + " ini"+zStringHelper::NewLine+zStringHelper::NewLine;
    zforeach(i, m)
    {
        e+=i.key()+"="+i.value()+zStringHelper::NewLine;
    }
    return e;
}

