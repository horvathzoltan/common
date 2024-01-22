#ifndef COM_DOWNLOADER_H
#define COM_DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "networkhelper_global.h"

namespace com { namespace helpers{
class COM_NETWORKHELPER_EXPORT NetworkHelper : public QObject
{
    Q_OBJECT

public:
    static QString mac_ethernet();
    static QString HwId();
};

}
} // namespace com::helpers
#endif // COM_DOWNLOADER_H
