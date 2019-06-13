#ifndef ISETTINGS_H
#define ISETTINGS_H

#include <QMap>

class ISettings
{
public:
    virtual ~ISettings()= default;
    
    virtual void parseIni(QMap<QString, QString>)=0;
    virtual QMap<QString, QString> toIni()=0;
};

#endif // ISETTINGS_H
