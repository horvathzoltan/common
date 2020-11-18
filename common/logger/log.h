#ifndef ZERROR_H
#define ZERROR_H

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
    #define getLocInfo LocInfo(__PRETTY_FUNCTION__ ,__FILE__,__LINE__)
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

// 1. log egy messaget
// 2. szerez loc infot
// 3. szerez debug infot (stack)
//

namespace Errlevels{
    enum Levels:int {
        ERROR_,
        WARNING,
        TRACE,
        DEBUG,
        INFO,
        INFOAPPEND,
        INFOCLOSE
    };

    [[maybe_unused]]
    static QString toString(const Levels &l){
        switch(l)
        {
        case ERROR_: return QStringLiteral("ERROR");
        case WARNING: return QStringLiteral("WARNING");
        case TRACE: return QStringLiteral("TRACE");
        case DEBUG: return QStringLiteral("DEBUG");
        case INFO: return QStringLiteral("INFO");
        case INFOAPPEND: return QStringLiteral("INFO");
        case INFOCLOSE: return QStringLiteral("INFO");
        }
    };
};

typedef void (*zLogGUIfn)(Errlevels::Levels errlevel, const QString &msg, const QString &loci, const QString &st, void *ui);

//QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC

class LOGGERSHARED_EXPORT Log
{
private:


//public:
    //enum class ErrLevels:int {ERROR, WARNING, TRACE, DEBUG, INFO, INFOAPPEND, INFOCLOSE};
private:          
    static zLogGUIfn GUILogger;
//    QTextBrowser *widget;
//    QTabWidget *tabwidget;
//    int tabindex;
    static void dialog(const QString&, Errlevels::Levels);
//    void log(const QString&, int);

//    static QTextBrowser *widget2;
//    static QTabWidget *tabwidget2;
//    static int tabindex2;
    static bool isBreakOnError;
    static bool isVerbose;

    static void *ui;

    static QString logToString(Errlevels::Levels, const QString&, const QString&, const QString&);


    //static QString zGetLocInfo(const char *func, const char *file, int line);
    static QString zStackTrace();

public:        
    static const QString OK;
    static const QString ERROR_;
    static const QString WARNING;

    //static const QMap<ErrLevels, QString> ErrLevelNames;

    //enum class ErrLevels:int {ERROR, WARNING, TRACE, DEBUG, INFO, INFOAPPEND, INFOCLOSE};
    //zLog();
    //~zLog();
    //static QString LevelToString(ErrLevels loglevel);

    //void init(QTextBrowser*, QTabWidget*, int,bool);
    static void init(zLogGUIfn ez, bool isBreak, void* ui, bool isVerbose);


//    [[deprecated]]
//    void log(const QString&);
//    void log(const QString&, int);

//    [[deprecated]]
//    void log(const QList<QString>&);

    /*message*/
    static void dialogMessage(const QString& str);
//    //void message(const char*);
//    void message(const QString&);
//    void message(const QList<QString>&);

//    /*ok*/
    static void dialogOk(const QString& str);
//    //void ok(const char*);
//    void ok(const QString&);
//    void ok(const QList<QString>&);

//    /*warning*/
    static void dialogWarning(const QString& str);
//    //void warning(const char*);
//    void warning(const QString&);
//    void warning(const QList<QString>&);

//    /*error*/
    static void dialogError(const QString& str);
//    //void error(const char*);
//    void error(const QString&);
//    void error(const QString&, const QString&);
//    void error(const QList<QString>&);

//    /*trace*/
    static void dialogTrace(const QString& str);
//    //void trace(const char*);
//    void trace(const QString&);
//   // void trace(const char*, const QString&);
//    void trace(const QString&, const QString&);
//    void trace(const QList<QString>&);

    static void error2(const QString& msg, const LocInfo& l);
    static void warning2(const QString& msg, const LocInfo& l);
    static void info2(const QString& msg, const LocInfo& l);
    static void info2(const QStringList& msg, const LocInfo& l);
    static void debug2(const LocInfo& l);
    static void trace2(const LocInfo& l);

    static QString openInfo(const QString& txt);
    static void appendInfo(const QString& key, const QString& txt);
    static void closeInfo(const QString& key);
};


#endif // ZERROR_H
