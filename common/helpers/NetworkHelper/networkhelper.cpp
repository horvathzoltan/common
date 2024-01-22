#include "networkhelper.h"
//#include "../../logger/log.h"

#include <QNetworkInterface>


namespace com { namespace helpers{

QString NetworkHelper::mac_ethernet(){
    auto a= QNetworkInterface::allInterfaces();
    for(auto&i:a)
    {
        if(i.type()==QNetworkInterface::Ethernet){
            return i.hardwareAddress();
        }
    }
    return QString();
}


QString NetworkHelper::HwId(){
    QString mac = mac_ethernet();
    return mac.toLower().remove(':');
}

}  // namespace helper
}  // namespace com
