#ifndef COM_ZERROR_H
#define COM_ZERROR_H

#include <QString>
//#include <QTextBrowser>
//#include <QTabWidget>
//#include <zstringhelper.h>
#include "locinfo.h"
#include "logger_global.h"
#include "../macrofactory/macro.h"


//#if defined(Q_OS_LINUX)
//#define getLocInfo LocInfo(static_cast<const char*>(__PRETTY_FUNCTION__),__FILE__,__LINE__)
//#elif defined(Q_OS_WIN)
    #if defined(__GNUC__)
    #define getLocInfo LocInfo(static_cast<const char*>(__PRETTY_FUNCTION__) ,__FILE__,__LINE__)
    #elif defined(__MINGW32__)
    #define getLocInfo LocInfo(__PRETTY_FUNCTION__ ,__FILE__,__LINE__)
    #elif defined (_MSC_VER )
    #define getLocInfo LocInfo(__FUNCSIG__ ,__FILE__,__LINE__)
    #endif
//#endif


#define zError(msg) Log::error2((msg), getLocInfo)

#define zWarning(msg) Log::warning2((msg), getLocInfo);
#define zInfo(msg) Log::info2((msg), getLocInfo);
#define zDebug() Log::debug2(getLocInfo);
#define zTrace() Log::trace2(getLocInfo);

#define zError2(msg,i) Log::error2((msg), getLocInfo,(i));
#define zWarning2(msg,i) Log::warning2((msg), getLocInfo,(i));
#define zInfo2(msg,i) Log::info2((msg), getLocInfo,(i));


// 1. log egy messaget
// 2. szerez loc infot
// 3. szerez debug infot (stack)
//

namespace Errlevels{
    enum Levels:int {
        ERROR_,
        WARNING,
        INFO,
    };

    [[maybe_unused]]
    static QString toString  (const Levels &l){
        switch(l)
        {
        case ERROR_: return QStringLiteral("ERROR");
        case WARNING: return QStringLiteral("WARNING");
        case INFO: return QStringLiteral("INFO");
        default: return QStringLiteral("unknown");
        }        
    };
};

namespace Dbglevels{
enum Levels:int {
    NONE=0,
    TRACE,
    DEBUG,
//    INFOAPPEND,
//    INFOCLOSE
};

[[maybe_unused]]
static QString toString  (const Levels &l){
    switch(l){
        case NONE: return QStringLiteral("TRACE");
        case TRACE: return QStringLiteral("TRACE");
        case DEBUG: return QStringLiteral("DEBUG");
//    case INFOAPPEND: return QStringLiteral("INFO");
//    case INFOCLOSE: return QStringLiteral("INFO");
        default: return QStringLiteral("unknown");
    }
};
}

namespace GUIModes{
enum Modes:int{ INFO, INFOAPPEND, INFOCLOSE, WARNING, ERROR, DEBUG};
}

typedef void (*zLogGUIfn)(GUIModes::Modes mode, const QString &msg, const QString &loci, const QString &st, void *ui, int type);


class LOGGERSHARED_EXPORT Log
{
private:

private:          
    static zLogGUIfn _GUILogger;

    static bool _isBreakOnError;
    static bool _isVerbose;    
    static Errlevels::Levels _errlevel;
    static Dbglevels::Levels _dbglevel;

    static void *_ui;

    static QString ToErrorString(Errlevels::Levels, const QString&, const QString&, const QString&);
    static QString ToDebugString(Dbglevels::Levels level, const QString &msg, const QString &loci, const QString &st);

    static QString zStackTrace();
    static void err_message(Errlevels::Levels level, const QString& msg, int flag =0);
    static void dbg_message(Dbglevels::Levels level, const QString& msg, int flag =0);
public:        
    static const QString OK;
    static const QString ERROR_;
    static const QString WARNING;

    static void init(Errlevels::Levels level,
                     Dbglevels::Levels dbglevel,
                     zLogGUIfn ez, bool isBreak, void* ui, bool isVerbose);

    static void error2(const QString& msg, const LocInfo& l, int flag = 0);
    static void warning2(const QString& msg, const LocInfo& l, int flag = 0);
    static void info2(const QString& msg, const LocInfo& l, int flag = 0);
    static void info2(const QStringList& msg, const LocInfo& l, int flag = 0);
    static void debug2(const LocInfo& l);
    static void trace2(const LocInfo& l);

    static QString openInfo(const QString& txt);
    static void appendInfo(const QString& key, const QString& txt);
    static void closeInfo(const QString& key);        
};


#endif // ZERROR_H
