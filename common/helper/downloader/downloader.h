#ifndef COM_DOWNLOADER_H
#define COM_DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "downloader_global.h"

namespace com::helper{
class COM_DOWNLOADER_EXPORT Downloader : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* _manager;
public:
    Downloader(QObject *parent = nullptr);
    QByteArray download(const QString&);
    void DownloadAsync(const QString&);
    static bool Wget(const QString&, const QString&);

signals:

public slots:
    void ReplyFinished (QNetworkReply *reply);


};
} // namespace com::helper
#endif // COM_DOWNLOADER_H
