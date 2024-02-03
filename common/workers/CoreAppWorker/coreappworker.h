#ifndef COM_COREAPPWORKER_H
#define COM_COREAPPWORKER_H

#include "coreappworker_global.h"
#include <QObject>
#include <QCommandLineParser>

namespace com{
namespace workers{
class COM_COREAPPWORKER_EXPORT CoreAppWorker : public QObject
{
    Q_OBJECT
public:
    CoreAppWorker();
    CoreAppWorker(int (*fn)(), QCoreApplication *app, QCommandLineParser *parser);
    int doWork();
public slots:
    int run();
signals:
    void finished();
private:
    static int (*workerFn)();
    static QCommandLineParser* parser;
};
}}

#endif // COREAPPWORKER_H
