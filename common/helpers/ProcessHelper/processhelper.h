#ifndef COM_PROCESSHELPER_H
#define COM_PROCESSHELPER_H

#include "processhelper_global.h"
#include <QString>

namespace com { namespace helpers{
class COM_PROCESSHELPER_EXPORT ProcessHelper
{
private:
    static bool _verbose;
    static const QString SEPARATOR;
    static QString _password;

public:
    struct Output
    {
    public:
        QString stdOut;
        QString stdErr;
        int exitCode=1;
        qint64 elapsedMillis;

        QString ToString();
    };

    static void setVerbose(bool v){_verbose = v;}
    static void setPassword(const QString& v){_password=v;}

    static Output ShellExecute(const QString& cmd, int timeout_millis = -1);
    static Output ShellExecuteSudo(const QString& cmd, int timeout_millis = -1);
};
} }
#endif // COM_PROCESSHELPER_H
