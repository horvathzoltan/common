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
    QNetworkRequest* _request;
    QUrl* _url;
public:
    Downloader(QObject *parent = nullptr);
    Downloader(const QString &url, QObject *parent = nullptr);
    QByteArray download(const QString&, const QString&, QString *err = nullptr);
    void DownloadAsync(const QString&);
    static bool Wget(const QString&, const QString&);

signals:

public slots:
    void ReplyFinished (QNetworkReply *reply);


};
} // namespace com::helper
#endif // COM_DOWNLOADER_H
