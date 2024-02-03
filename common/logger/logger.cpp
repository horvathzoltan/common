//#include "globals.h"
#include "logger.h"
#include "stackhelper.h"
//#include "../shortguid/shortguid.h"
//#include <QMessageBox>
//#include <QTextCodec>
#include <csignal>
#ifdef Q_OS_LINUX

#include <QDebug>
#endif


ErrLevel::Levels Logger::_errlevel = ErrLevel::INFO;
DbgLevel::Levels Logger::_dbglevel = DbgLevel::TRACE;

bool Logger::_isBreakOnError = false;
bool Logger::_isVerbose = false;
bool Logger::_isInited = false;

// zLogGUIfn Logger::_GUILogger = nullptr;
// void* Logger::_ui = nullptr;

const QString Logger::OK = QStringLiteral("ok");
const QString Logger::ERROR_ = QStringLiteral("error");
const QString Logger::WARNING = QStringLiteral("warning");

// zLogGUIfn ez, void* uiptr,
//     _GUILogger = ez;
// _ui=uiptr;
void Logger::init(ErrLevel::Levels errlevel,
               DbgLevel::Levels dbglevel,
                bool isBreakOnError, bool isVerbose)
{
    _isInited = false;
     _errlevel = errlevel;
     _dbglevel = dbglevel;

    _isBreakOnError = isBreakOnError;

    _isVerbose = isVerbose;
    _isInited = true;
}


QString Logger::ToString(DbgLevel::Levels level, const QString &msg, const QString &loci, const QString &st)
{
    auto txt = DbgLevel::ToString(level);
    QString msg3;

    switch(level){
    case DbgLevel::TRACE:
        msg3= txt+": "+loci;
        break;
    case DbgLevel::DEBUG:
        msg3= txt+": "+msg+"\n"+loci+"\n"+st;
        break;
    default: break;
    }
    return msg3;
}

QString Logger::ToString(ErrLevel::Levels errlevel, const QString &msg, const QString &loci, const QString &st)
{
    QString txt = ErrLevel::ToString(errlevel);
    QString msg3;

    switch (errlevel) {
    case ErrLevel::ERROR_:
        msg3 = txt + ": " + msg + "\n" + loci + "\n" + st;
        break;
    case ErrLevel::WARNING:
        msg3 = txt + ": " + msg + "\n" + loci;
        break;

    case ErrLevel::INFO:
        msg3 = txt + ": " + msg;
        if (_isVerbose)
            msg3 += "\n" + loci;
        break;
    default:
        break;
    }

    return msg3;
}





void Logger::error2(const QString& msg,  const LocInfo& locinfo){
    if(!_isInited) return;
    if(_errlevel>ErrLevel::ERROR_) return;

    auto li = locinfo.toString();
    auto st = StackHelper::Trace();

    auto msg2 = ToString(ErrLevel::ERROR_, msg, li, st);
    err_message(ErrLevel::ERROR_, msg2);
    }

void Logger::warning2(const QString& msg, const LocInfo& locinfo){
    if(!_isInited) return;
    if(_errlevel>ErrLevel::WARNING) return;

    auto li = locinfo.toString();    
    auto msg2 = ToString(ErrLevel::WARNING, msg, li, nullptr);

    err_message(ErrLevel::WARNING, msg2);
    }

void Logger::info2(const QString& msg, const LocInfo& locinfo)
{
    if(!_isInited) return;
    if(_errlevel>ErrLevel::INFO) return;

    QString li;
    if(_isVerbose)
    {
        li = locinfo.toString();
    }

    auto msg2 = ToString(ErrLevel::INFO, msg, li, nullptr);
    err_message(ErrLevel::INFO, msg2);
}

void Logger::info2(const QStringList& msgl, const LocInfo& locinfo)
{
    if(!_isInited) return;
    if(_errlevel>ErrLevel::INFO) return;

    QString li;
    if(_isVerbose)
    {
        li = locinfo.toString();
    }

    for(auto&msg:msgl)
    {
        auto msg2 = ToString(ErrLevel::INFO, msg, nullptr, nullptr);
        err_message(ErrLevel::INFO, msg2);
    }
}

void Logger::debug2(const LocInfo& locinfo){
    if(!_isInited) return;
    if(_dbglevel==DbgLevel::NONE || _dbglevel>DbgLevel::DEBUG) return;

    auto li = locinfo.toString();
    auto st = StackHelper::Trace();

    auto msg2 = ToString(DbgLevel::DEBUG, nullptr, li, st);
    dbg_message(DbgLevel::DEBUG, msg2);
    }

void Logger::trace2(const LocInfo& locinfo){
    if(_dbglevel==DbgLevel::NONE || _dbglevel>DbgLevel::TRACE) return;
    auto li = locinfo.toString();
    auto msg2 = ToString(DbgLevel::TRACE, nullptr, li, nullptr);
    dbg_message(DbgLevel::TRACE, msg2);
    }

// QString Log::openInfo(const QString& msg)
// {
//     QString e= zShortGuid::createNew().value;

//     if(_GUILogger){
//         _GUILogger(GUIModes::INFO, e+' '+msg, nullptr, nullptr, _ui, 0);
//     }

//     return e;
// }

// void Log::appendInfo(const QString& key, const QString& msg)
// {
//     if(_GUILogger){
//         _GUILogger(GUIModes::INFOAPPEND, msg, key, nullptr, _ui, 0);
//     }
// }

// void Log::closeInfo(const QString& key)
// {
//     if(_GUILogger) {
//         _GUILogger(GUIModes::INFOCLOSE, nullptr, key, nullptr, _ui, 0);
//     }
// }

void Logger::err_message(ErrLevel::Levels level, const QString& msg)
{
    //GUIModes::Modes guimode;

#ifdef QT_DEBUG
#ifdef Q_OS_WIN
    auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    switch(level)
    {
    case ErrLevel::ERROR_:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).critical().noquote()<<msg;
      //  guimode = GUIModes::ERROR;
        break;
    case ErrLevel::WARNING:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).warning().noquote()<<msg;
       // guimode = GUIModes::WARNING;
        break;
    case ErrLevel::INFO:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).info().noquote()<<msg;
       // guimode = GUIModes::INFO;
        break;
    default:
        //guimode = GUIModes::INFO;
        break;
    }
    // if(_GUILogger) {
    //     _GUILogger(guimode, msg, "", "", _ui, flag);
    // }
#ifdef Q_OS_LINUX
    if((level==ErrLevel::ERROR_) && _isBreakOnError) std::raise(SIGTRAP);
#endif
#endif
}


void Logger::dbg_message(DbgLevel::Levels level, const QString& msg)
{
    //GUIModes::Modes guimode;
#ifdef QT_DEBUG
#ifdef Q_OS_WIN
        auto a = __FUNCTION__;
#elif defined(Q_OS_LINUX)
    auto a = static_cast<const char*>(__PRETTY_FUNCTION__);
#endif
    switch(level){
    case DbgLevel::DEBUG:
    case DbgLevel::TRACE:
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, a).debug().noquote()<<msg;
      //  guimode = GUIModes::DEBUG;
        break;
    default:
      //  guimode = GUIModes::DEBUG;
        break;
    }

    // if(_GUILogger){
    //     _GUILogger(guimode, msg, "", "", _ui, flag);
    // }
#ifdef Q_OS_LINUX
    if((level ==DbgLevel::DEBUG) && _isBreakOnError) std::raise(SIGTRAP);
#endif
#endif
}
