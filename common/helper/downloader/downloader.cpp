#include "downloader.h"
#include "../../logger/log.h"
#include "../../helper/ProcessHelper/processhelper.h"
#include <QEventLoop>
#include <QUrlQuery>
#include <QNetworkReply>

namespace com { namespace helper{
Downloader::Downloader(QObject *parent) : QObject(parent)
{
    _manager = nullptr;
    //_isInited = true;
}

Downloader::Downloader(const QString& urlstring, QObject *parent) : QObject(parent)
{
    //_manager = nullptr;
    _manager = new QNetworkAccessManager(this);
    _url = new QUrl(urlstring);
    _request = new QNetworkRequest();
    //_request->setUrl(url);
    _request->setRawHeader("User-Agent", "zDownloader 1.0");
    //_isInited = true;
}

QByteArray Downloader::download(const QString& pathstr, const QString& querystr, QString *err)
{
    //if(!_isInited) return {};
//    if(!_url) return {};
//    if(!_manager) return {};
//    if(!_request) return {};
    if(!pathstr.isEmpty()) _url->setPath('/'+pathstr);
    if(!querystr.isEmpty()) _url->setQuery(querystr);//'?'+

    _request->setUrl(*_url);

    QNetworkReply* reply = _manager->get(*_request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    auto a = reply->readAll();

    auto error = reply->error();
    if(error!=QNetworkReply::NoError)
    {        
        auto msg = reply->errorString();
        if(err) *err = msg;
        zInfo(QStringLiteral("request: %3 response: %4 status: (%1) %2")
                  .arg(error)
                  .arg(msg)
                  .arg(_url->toString())
                  .arg(QString(a))
              );
    }

    return a;
}

QByteArray Downloader::post(const QString& pathstr, const QString& querystr, QString *err, const QByteArray &b)
{
//     if(!_isInited) return {};
//    if(!_url) return {};
    if(!pathstr.isEmpty()) _url->setPath('/'+pathstr);
    if(!querystr.isEmpty()) _url->setQuery(querystr);//'?'+

    _request->setUrl(*_url);

    QNetworkReply* reply = _manager->post(*_request, b);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    auto a = reply->readAll();

    auto error = reply->error();
    if(error!=QNetworkReply::NoError)
    {
        auto msg = reply->errorString();
        if(err) *err = reply->errorString();
        return {};
    }

    return a;//reply->readAll();
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
}
