#include "coreappworker.h"
#include <QCoreApplication>
#include <QDebug>

namespace com{
CoreAppWorker::CoreAppWorker() = default;

int (*CoreAppWorker::workerFn)();
QCommandLineParser* CoreAppWorker::parser;

CoreAppWorker::CoreAppWorker(int (*fn)(), QCoreApplication *app, QCommandLineParser *p)
{
    workerFn = fn;
    parser = p;
    QObject::connect(this, &CoreAppWorker::finished, app, &QCoreApplication::quit, Qt::QueuedConnection);
    //qDebug() << "new AppWorker";
}

int CoreAppWorker::doWork()
{
    //int e = *workerFn();
    //auto m = new char[40];
    //m=new char[2];
    qDebug() << "Class1 doWork()";
    //qDebug() << "worker called";
    return 0;
}

int CoreAppWorker::run()
{
    //doWork();
    int e = workerFn();
    // Same implementation as before
    // Emit signal when finished
    emit finished();
    return e;
}

}
