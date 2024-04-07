#ifndef COM_ZERROR_H
#define COM_ZERROR_H

#include <QString>
#include "locinfo.h"
#include "logger_global.h"

#if defined(__GNUC__)
#define getLocInfo LocInfo(static_cast<const char*>(__PRETTY_FUNCTION__) ,__FILE__,__LINE__)
#elif defined(__MINGW32__)
#define getLocInfo LocInfo(__PRETTY_FUNCTION__ ,__FILE__,__LINE__)
#elif defined (_MSC_VER )
#define getLocInfo LocInfo(__FUNCSIG__ ,__FILE__,__LINE__)
#endif

#define zError(msg) Logger::error2((msg), getLocInfo)

#define zWarning(msg) Logger::warning2((msg), getLocInfo);
#define zInfo(msg) Logger::info2((msg), getLocInfo);
#define zDebug() Logger::debug2(getLocInfo);
#define zTrace() Logger::trace2(getLocInfo);

#define zError2(msg,i) Logger::error2((msg), getLocInfo,(i));
#define zWarning2(msg,i) Logger::warning2((msg), getLocInfo,(i));
#define zInfo2(msg,i) Logger::info2((msg), getLocInfo,(i));

#define zMessage(msg) Logger::message((msg));

// 1. log egy messaget
// 2. szerez loc infot
// 3. szerez debug infot (stack)
//

namespace ErrLevel{
    enum Levels:int {
        ERROR_,
        WARNING,
        INFO,
    };

    [[maybe_unused]]
    static QString ToString  (const Levels &l){
        switch(l) {
            case ERROR_: return QStringLiteral("ERROR");
            case WARNING: return QStringLiteral("WARNING");
            case INFO: return QStringLiteral("INFO");
            default: return QStringLiteral("undefined");
        }        
    };
};

namespace DbgLevel{
    enum Levels:int {
        NONE=0,
        TRACE,
        DEBUG,
    };

    [[maybe_unused]]
    static QString ToString  (const Levels &l){
        switch(l){
            case NONE: return QStringLiteral("TRACE");
            case TRACE: return QStringLiteral("TRACE");
            case DEBUG: return QStringLiteral("DEBUG");
            default: return QStringLiteral("undefined");
        }
    };
}

namespace GUIModes{
    enum Modes:int{ INFO, INFOAPPEND, INFOCLOSE, WARNING, ERROR, DEBUG};
}

class COM_LOGGERSHARED_EXPORT Logger
{
private:
    static bool _isBreakOnError;
    static bool _isVerbose;
    static bool _isInited;
    static ErrLevel::Levels _errlevel;
    static DbgLevel::Levels _dbglevel;

    static const QString OK;
    static const QString ERROR_;
    static const QString WARNING;

    static QString ToString(ErrLevel::Levels level, const QString& msg, const QString& loci, const QString& st);
    static QString ToString(DbgLevel::Levels level, const QString &msg, const QString &loci, const QString &st);

    static void err_message(ErrLevel::Levels level, const QString& msg);
    static void dbg_message(DbgLevel::Levels level, const QString& msg);

public:

    static void init(ErrLevel::Levels level,
                     DbgLevel::Levels dbglevel,
                     bool isBreak,
                     bool isVerbose); //void* ui // zLogGUIfn ez,

    static void error2(const QString& msg, const LocInfo& l);
    static void warning2(const QString& msg, const LocInfo& l);
    static void info2(const QString& msg, const LocInfo& l);
    static void info2(const QStringList& msg, const LocInfo& l);
    static void debug2(const LocInfo& l);
    static void trace2(const LocInfo& l);
    static void message(const QString& msg);
};


#endif // ZERROR_H
