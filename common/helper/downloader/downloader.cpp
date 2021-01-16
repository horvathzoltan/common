#include "downloader.h"
#include "../../logger/log.h"
#include "../../helper/ProcessHelper/processhelper.h"
#include <QEventLoop>

namespace com::helper{
Downloader::Downloader(QObject *parent) : QObject(parent)
{
    _manager = nullptr;
}

QByteArray Downloader::download(const QString& urlstring)
{
    _manager = new QNetworkAccessManager(this);
    //auto ikey = zInfo::openInfo(QStringLiteral("Beolvasás: %1").arg(urlstring));

    //auto url = QUrl(QStringLiteral("https://docs.google.com/document/export?format=html&id=1qqYuhCY5iTAfzBiwQGfzRdU7C1jm1pNnNajVrSrWAfU"));
    auto url = QUrl(urlstring);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "zDownloader 1.0");

    QNetworkReply* reply = _manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray e;
    if(reply->error())
    {
        auto err = reply->errorString();
        zError(err);
    }
    else{

        e = reply->readAll();
    }

    //zLog::appendInfo(ikey, zLog::OK);
    //zLog::closeInfo(ikey);
    return e;
}

void Downloader::DownloadAsync(const QString& urlstring)
{
    _manager = new QNetworkAccessManager(this);

    //auto url = QUrl(QStringLiteral("https://docs.google.com/document/export?format=html&id=1qqYuhCY5iTAfzBiwQGfzRdU7C1jm1pNnNajVrSrWAfU"));
    auto url = QUrl(urlstring);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "zDownloader 1.0");

    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    //QNetworkReply* reply =
    _manager->get(request);
}

bool Downloader::Wget(const QString &url, const QString &filename)
{
    if(url.isEmpty()) return false;
    auto cmd = QStringLiteral(R"(wget "%1" -O "%2"")").arg(url).arg(filename);
    auto out = com::helper::ProcessHelper::Execute(cmd);
    if(!out.exitCode) return true;
    return false;
}

void Downloader::ReplyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        zError(reply->errorString());
    }
    else
    {
        reply->readAll();

        //qDebug()<<e;
        //        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        //        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        //        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        //        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        //        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        //        QFile *file = new QFile("C:/Qt/Dummy/downloaded.txt");
        //        if(file->open(QFile::Append))
        //        {
        //            auto e = reply->readAll();
        //            file->write(e);
        //            file->flush();
        //            file->close();
        //        }
        //        delete file;
    }

    reply->deleteLater();
}
}
