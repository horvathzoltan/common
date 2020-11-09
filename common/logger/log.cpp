//#include "globals.h"
#include "log.h"
#include "../shortguid/shortguid.h"
//#include <QMessageBox>
#include <QTextCodec>
#include <csignal>
#ifdef Q_OS_LINUX
#include <execinfo.h>
#include <cxxabi.h>
#endif

bool Log::isBreakOnError = false;
zLogGUIfn Log::GUILogger = nullptr;
void* Log::ui = nullptr;
bool Log::isVerbose = false;

const QString Log::OK = QStringLiteral("ok");
const QString Log::ERROR_ = QStringLiteral("error");
const QString Log::WARNING = QStringLiteral("warning");

void Log::init(zLogGUIfn ez, bool _isBreakOnError, void* uiptr, bool _isVerbose)
{
    GUILogger = ez;
    isBreakOnError = _isBreakOnError;
    ui=uiptr;
    isVerbose = _isVerbose;
}

//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
QString Log::logToString(Errlevels::Levels errlevel, const QString &msg, const QString &loci, const QString &st)
{
    auto level = Errlevels::toString(errlevel);
    QString msg3;

    switch(errlevel)
    {
    case Errlevels::ERROR_:
        msg3= level+": "+msg+"\n"+loci+"\n"+st;
        break;
    case Errlevels::WARNING:
        msg3= level+": "+msg+"\n"+loci;
        break;
    case Errlevels::TRACE:
        msg3= level+": "+loci;
        break;
    case Errlevels::DEBUG:
        msg3= level+": "+msg+"\n"+loci+"\n"+st;
        break;
    case Errlevels::INFO:
        msg3= level+": "+msg;
        if(isVerbose)
        {
            msg3+="\n"+loci;
        }
        break;
    default:
        break;
    }

    return msg3;
}
//#pragma GCC diagnostic pop



#ifdef Q_OS_LINUX
QString Log::zStackTrace()
{
    QStringList e;

    unsigned int max_frames = 64;

    e << QStringLiteral("stack trace:");

    // storage array for stack trace address data
    void* addrlist[max_frames+1];

    // retrieve current stack addresses
    int addrlen = backtrace(static_cast<void**>(addrlist), sizeof(addrlist) / sizeof(void*));

    if (addrlen == 0)
    {
        e << QStringLiteral("<empty, possibly corrupt>");
        return e.join('\n');
    }

    // resolve addresses into strings containing "filename(function+address)", this array must be free()-ed
    auto symbollist = backtrace_symbols(static_cast<void**>(addrlist), addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    auto funcname = static_cast<char*>(malloc(funcnamesize));

    // iterate over the returned symbol lines. skip the first, it is the address of this function.
    for (int i = 1; i < addrlen; i++)
    {
    char *begin_name = nullptr, *begin_offset = nullptr, *end_offset = nullptr;

    for (char *p = symbollist[i]; *p; ++p)
    {
        if (*p == '(')
        {
            begin_name = p;
        }
        else if (*p == '+')
        {
            begin_offset = p;
        }
        else if (*p == ')' && begin_offset)
        {
            end_offset = p;
            break;
        }
    }

    if (begin_name && begin_offset && end_offset
        && begin_name < begin_offset)
    {
        *begin_name++ = '\0';
        *begin_offset++ = '\0';
        *end_offset = '\0';

        int status;
        char* ret = abi::__cxa_demangle(begin_name,funcname, &funcnamesize, &status);
        if (status == 0)
        {
            funcname = ret; // use possibly realloc()-ed string
            e << QStringLiteral("%1: %2 + %3").arg(symbollist[i],ret,begin_offset);
            //e << QStringLiteral("%1").arg(funcname);
        }
        else
        {
            // demangling failed. Output function name as a C function with
            // no arguments.
            e << QStringLiteral("%1: %2 + %3").arg(symbollist[i],begin_name,begin_offset);
            //e << QStringLiteral("%1").arg(begin_name);
        }
    }
    else
    {
        // couldn't parse the line? print the whole line.
        e << QString(symbollist[i]);
    }
    }

    free(funcname);
    free(symbollist);

    auto a =  e.join('\n');
    return a;
}

#endif

#ifdef Q_OS_WIN
QString Log::zStackTrace(){
    QStringList e;

   // unsigned int max_frames = 64;

    e << QStringLiteral("stack trace:");

    // WIN implementációt adni
    e << QStringLiteral("?");

    auto a =  e.join('\n');

    return a;
}
#endif


void Log::error2(const QString& msg,  const LocInfo& locinfo, int flag){
    auto li = locinfo.toString();
    auto st = Log::zStackTrace();

    if(GUILogger!=nullptr)
    {
        GUILogger(Errlevels::ERROR_, msg, li, st, ui, flag);
    }
    auto msg2 = logToString(Errlevels::ERROR_, msg, li, st);

#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).critical().noquote()<<msg2;
#ifdef Q_OS_LINUX
    if(isBreakOnError) std::raise(SIGTRAP);
#endif
#endif
    }

void Log::warning2(const QString& msg, const LocInfo& locinfo, int flag){
    auto li = locinfo.toString();
    if(GUILogger!=nullptr)
    {
        GUILogger(Errlevels::WARNING, msg, li, nullptr, ui, flag);
    }
    auto msg2 = logToString(Errlevels::WARNING, msg, li, nullptr);
#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).warning().noquote()<<msg2;
#endif
    }

void Log::info2(const QString& msg, const LocInfo& locinfo, int flag)
{
    QString li;
    if(isVerbose)
    {
        li = locinfo.toString();
    }
    if(GUILogger!=nullptr)
    {
        GUILogger(Errlevels::INFO, msg, nullptr, nullptr, ui, flag);
    }    

    auto msg2 = logToString(Errlevels::INFO, msg, li, nullptr);
#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).info().noquote()<<msg2;
#endif
}

void Log::info2(const QStringList& msgl, const LocInfo& locinfo, int flag)
{
    QString li;
    if(isVerbose)
    {
        li = locinfo.toString();
    }

    zforeach(msg,msgl)
    {
        if(GUILogger!=nullptr)
        {
            GUILogger(Errlevels::INFO, *msg, nullptr, nullptr, ui, flag);
        }
        auto msg2 = logToString(Errlevels::INFO, *msg, nullptr, nullptr);
#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
        auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).info().noquote()<<msg2;
#endif
    }
}

void Log::debug2(const LocInfo& locinfo){
    auto li = locinfo.toString();
    auto st = Log::zStackTrace();
//    if(GUILogger!=nullptr)
//    {
//        GUILogger(Errlevels::DEBUG, nullptr, li, st, ui);
//    }
    auto msg2 = logToString(Errlevels::DEBUG, nullptr, li, st);
#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).debug().noquote()<<msg2;
#ifdef Q_OS_LINUX
    if(isBreakOnError) std::raise(SIGTRAP);
#endif
#endif
    }

void Log::trace2(const LocInfo& locinfo){
    auto li = locinfo.toString();
//    if(GUILogger!=nullptr)
//    {
//        GUILogger(Errlevels::TRACE, nullptr, li, nullptr, ui);
//    }
    auto msg2 = logToString(Errlevels::TRACE, nullptr, li, nullptr);
#ifdef QT_DEBUG  
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
   QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).debug().noquote()<<msg2;
#endif
    }

QString Log::openInfo(const QString& msg)
    {

        QString e= zShortGuid::createNew().value;

        if(GUILogger!=nullptr)
        {
            GUILogger(Errlevels::INFO, e+' '+msg, nullptr, nullptr, ui, 0);
        }
      return e;
    }

void Log::appendInfo(const QString& key, const QString& msg)
    {

    if(GUILogger!=nullptr)
    {
        GUILogger(Errlevels::INFOAPPEND, msg, key, nullptr, ui, 0);
    }
    }

void Log::closeInfo(const QString& key)
    {

        if(GUILogger!=nullptr)
        {
            GUILogger(Errlevels::INFOCLOSE, nullptr, key, nullptr, ui, 0);
        }
    }
