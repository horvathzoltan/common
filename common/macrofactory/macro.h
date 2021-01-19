#ifndef COM_ZMACRO_H
#define COM_ZMACRO_H

#include <QRegularExpression>
//#include "zlogicexception.h"
#include "cxxabi.h"

#define GET(v, name) const decltype(v)& name() const {return v;}
#define SET(v, name) void name(const decltype(v)& m) {v = m;}
#define SET_UI(v, name, setui) void name(const decltype(v)& m) {v = m; setui();}

#define zforeach(var, container) for(auto (var) = (container).begin(); (var) != (container).end(); ++(var))
#define zforeach_from(var, container, ix) for(auto (var) = (container).begin()+(ix); (var) != (container).end(); ++(var))

#define nameof(x) z_macro_factory::_nameof<0>(#x, sizeof(x))
#define zfn() z_macro_factory::_zfn<0>((const char*)Q_FUNC_INFO)

#define nameof_type(x) z_macro_factory::_nmnm56(typeid(x).name())

#define nameof_fn() z_macro_factory::_zfn2(Q_FUNC_INFO)
#define nameof_fn_full() z_macro_factory::_zfn_full(Q_FUNC_INFO)

namespace z_macro_factory {

[[maybe_unused]]
static QString _nmnm56(const char* x) {
    int status;
    auto a =  abi::__cxa_demangle(x, NULL, NULL, &status);
    return a;
}

template<int a>
QString _nameof(const char* y, std::size_t)
{
    QString x(y);
    if(x.endsWith(QStringLiteral("()")))
    {
        QRegularExpression re(QStringLiteral(R"([\w]+(?:::|->|.)([\w]+)\(\))"));
        QRegularExpressionMatch m = re.match(x);

        if (m.hasMatch())
        {
            return m.captured(m.lastCapturedIndex());
        }
    }
    else
    {
        QRegularExpression re(QStringLiteral(R"(^&?([_a-zA-Z]\w*)\s*(->|\.|::)?\s*([_a-zA-Z]\w*)?$)"));
        QRegularExpressionMatch m = re.match(x);

        if (m.hasMatch()) {
            return m.captured(m.lastCapturedIndex());
        }
    }
    //QRegularExpression re("^&?([_a-zA-Z]\\w*(->|\\.|::))*([_a-zA-Z]\\w*)$");

    //throw zLogicException("A bad expression x in nameof(x). The expression is \"" + x + "\".");

    return QStringLiteral("A bad expression x in nameof(x). The expression is \" %1 \".").arg(x);
}

[[maybe_unused]]
static QString _zfn_full(const char* y){return y;}

template<int a>
QString _zfn(const char* y)
{
    QString x(y);

    QRegularExpression re(QStringLiteral(R"(([\w]+::[\w]+))"));
    QRegularExpressionMatch m = re.match(x);

    if (m.hasMatch()) return m.captured(m.lastCapturedIndex());

//    throw zLogicException("A bad expression x in _zfn(x). The expression is \"" + x + "\".");
    return QStringLiteral("unknown");
}

[[maybe_unused]]
static QString _zfn2(const char* y)
{
    QString x(y);

    QRegularExpression re(QStringLiteral(R"(([\w]+::[\w]+))"));
    QRegularExpressionMatch m = re.match(x);

    if (m.hasMatch()) return m.captured(m.lastCapturedIndex());
    return QStringLiteral("unknown");
}

}// namespace z_macro_factory


#endif // ZMACRO_H
