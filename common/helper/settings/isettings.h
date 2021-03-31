#ifndef COM_ISETTINGS_H
#define COM_ISETTINGS_H

#include <QMap>

namespace com { namespace helper{
class ISettings
{
public:
    virtual ~ISettings()= default;
    
    virtual void parseIni(QMap<QString, QString>)=0;
    virtual QMap<QString, QString> toIni()=0;
};
}
}
#endif // ISETTINGS_H
