#ifndef COM_PROCESSHELPER_H
#define COM_PROCESSHELPER_H

#include "ProcessHelper_global.h"
#include <QString>

namespace com::helper{
class COM_PROCESSHELPER_EXPORT ProcessHelper
{
public:
    struct Output
    {
    public:
        QString stdOut;
        QString stdErr;
        int exitCode;
        QString ToString();
    };
public:
    static const QString SEPARATOR;

    //static QString Execute(const QString& cmd);
    static QString Execute(const QStringList &cmds);
    static Output Execute(const QString &cmd);
};
}
#endif // COM_PROCESSHELPER_H
