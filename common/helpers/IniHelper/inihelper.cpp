#include "inihelper.h"
#include "../../macrofactory/macro.h"
#include "../../helpers/StringHelper/stringhelper.h"

namespace com { namespace helpers{
QMap<QString, QString> IniHelper::Parse(const QStringList& lines, const QChar& sep)
{
    bool valid = !lines.isEmpty();
    QMap<QString, QString> m;
    if(valid){
        for(auto&line:lines)
        {
            bool validLine = !line.isEmpty() && !line.startsWith('#');
            if(validLine){
                int ix = line.indexOf(sep);
                if(ix>0){
                    m.insert(line.left(ix), line.mid(ix+1));
                }
            }
        }
    }
    return m;
}

bool IniHelper::TryGetValue(QMap<QString, QString>m, const QString &key, QString *value)
{
    bool retval = false;
    bool valid = !m.isEmpty() && !key.isEmpty() && value != nullptr;
    if(valid){
        if(m.contains(key))
        {
            *value = m[key];
            retval = true;
        }
    }
    return retval;
}

QString IniHelper::toString(const QMap<QString, QString> &m, const QString &desc)
{
    QString e;
    e+=QStringLiteral("# ")+desc + " ini"+StringHelper::NewLine+StringHelper::NewLine;
    zforeach(i, m)
    {
        e+=i.key()+"="+i.value()+StringHelper::NewLine;
    }
    return e;
}

}
}//namespace com::helper
