//#include "globals.h"
#include "log.h"
#include "../shortguid/shortguid.h"
//#include <QMessageBox>
#include <QTextCodec>
#include <csignal>
#ifdef Q_OS_LINUX
#include <execinfo.h>
#include <cxxabi.h>
#include <QDebug>
#endif

bool Log::_isBreakOnError = false;
zLogGUIfn Log::_GUILogger = nullptr;
void* Log::_ui = nullptr;
bool Log::_isVerbose = false;
Errlevels::Levels Log:: _errlevel = Errlevels::INFO;

const QString Log::OK = QStringLiteral("ok");
const QString Log::ERROR_ = QStringLiteral("error");
const QString Log::WARNING = QStringLiteral("warning");

void Log::init(Errlevels::Levels level, zLogGUIfn ez, bool isBreakOnError, void* uiptr, bool isVerbose)
{
     _errlevel = level;
    _GUILogger = ez;
    _isBreakOnError = isBreakOnError;
    _ui=uiptr;
    _isVerbose = isVerbose;
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
        if(_isVerbose)
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
    if(_errlevel>Errlevels::ERROR_) return;

    auto li = locinfo.toString();
    auto st = Log::zStackTrace();

    auto msg2 = logToString(Errlevels::ERROR_, msg, li, st);
    message(Errlevels::ERROR_, msg2, flag);
    }

void Log::warning2(const QString& msg, const LocInfo& locinfo, int flag){
    if(_errlevel>Errlevels::WARNING) return;
    auto li = locinfo.toString();
    auto msg2 = logToString(Errlevels::WARNING, msg, li, nullptr);
    message(Errlevels::WARNING, msg, flag);
    }

void Log::info2(const QString& msg, const LocInfo& locinfo, int flag)
{
    if(_errlevel>Errlevels::INFO) return;
    QString li;
    if(_isVerbose)
    {
        li = locinfo.toString();
    }

    auto msg2 = logToString(Errlevels::INFO, msg, li, nullptr);
    message(Errlevels::INFO, msg, flag);
}

void Log::info2(const QStringList& msgl, const LocInfo& locinfo, int flag)
{
    QString li;
    if(_isVerbose)
    {
        li = locinfo.toString();
    }

    for(auto&msg:msgl)
    {
        auto msg2 = logToString(Errlevels::INFO, msg, nullptr, nullptr);
        message(Errlevels::INFO, msg2, flag);
    }
}

void Log::debug2(const LocInfo& locinfo){
    auto li = locinfo.toString();
    auto st = Log::zStackTrace();

    auto msg2 = logToString(Errlevels::DEBUG, nullptr, li, st);
    message(Errlevels::DEBUG, msg2);
    }

void Log::trace2(const LocInfo& locinfo){
    auto li = locinfo.toString();
    auto msg2 = logToString(Errlevels::TRACE, nullptr, li, nullptr);
    message(Errlevels::TRACE, msg2);
    }

QString Log::openInfo(const QString& msg)
{
    QString e= zShortGuid::createNew().value;

    if(_GUILogger!=nullptr)
        _GUILogger(Errlevels::INFO, e+' '+msg, nullptr, nullptr, _ui, 0);

    return e;
}

void Log::appendInfo(const QString& key, const QString& msg)
{
    if(_GUILogger!=nullptr)
        _GUILogger(Errlevels::INFOAPPEND, msg, key, nullptr, _ui, 0);
}

void Log::closeInfo(const QString& key)
{
    if(_GUILogger!=nullptr)
        _GUILogger(Errlevels::INFOCLOSE, nullptr, key, nullptr, _ui, 0);
}

void Log::message(Errlevels::Levels level, const QString& msg, int flag){

    if((level!=Errlevels::DEBUG &&
        level!=Errlevels::TRACE )
            && _GUILogger!=nullptr)
        _GUILogger(level, msg, "", "", _ui, flag);

#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    switch(level)
    {
    case Errlevels::ERROR_:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).critical().noquote()<<msg;
        break;
    case Errlevels::WARNING:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).warning().noquote()<<msg;
        break;
    case Errlevels::INFO:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).info().noquote()<<msg;
        break;
    case Errlevels::DEBUG:
    case Errlevels::TRACE:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).debug().noquote()<<msg;
        break;
    default: break;
    }
#ifdef Q_OS_LINUX
    if((level==Errlevels::ERROR_ || level ==Errlevels::DEBUG)
            && _isBreakOnError) std::raise(SIGTRAP);
#endif
#endif
    }
