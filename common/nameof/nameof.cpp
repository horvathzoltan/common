#include "nameof.h"

QString NameOf::NameOf_private(const QString &x)
{
    //QString x(y);
    // [\w]+(?:::|->|.)([\w]+)\(\)
    // (?:::|->|\.)?([\w]+)\(\)$
    static const QRegularExpression refn(QStringLiteral(R"((?:::|->|\.)?([\w]+)\(\)$)"));
    //^&([_a-zA-Z]\w*)\s*(->|\.|::)?\s*([_a-zA-Z]\w*)?$
    //(?:(?:[_a-zA-Z]\w*)(?:->|\.|::))*([_a-zA-Z]\w*)
    //(?:->|\.|::)?([_a-zA-Z]\w*)$
    static const QRegularExpression re(QStringLiteral(R"((?:->|\.|::)?([_a-zA-Z]\w*)$)"));
    QRegularExpressionMatch m;

    if(x.endsWith(QStringLiteral("()"))) m = refn.match(x);
    else m = re.match(x);

    if (m.hasMatch()) return m.captured(m.lastCapturedIndex());

    return QStringLiteral("A bad expression in nameof(%1)").arg(x);
}

QString NameOf::_nameof_fn(const char* y, void*)
{
    return NameOf_private(QString(y));
}

QString NameOf::_nameof(const char* y, std::size_t)
{
    return NameOf_private(QString(y));
}

QString NameOf::_nameof_ulong(char const *y, unsigned long)
{
    return NameOf_private(QString(y));
}

// [[maybe_unused]]
// static QString _zfn_full(const char* y){return y;}

// template<int a>
// QString _zfn(const char* y)
// {
//     QString x(y);

//     QRegularExpression re(QStringLiteral(R"(([\w]+::[\w]+))"));
//     QRegularExpressionMatch m = re.match(x);

//     if (m.hasMatch()) return m.captured(m.lastCapturedIndex());

//     //    throw zLogicException("A bad expression x in _zfn(x). The expression is \"" + x + "\".");
//     return QStringLiteral("unknown");
// }

// [[maybe_unused]]
// static QString _zfn2(const char* y)
// {
//     QString x(y);

//     QRegularExpression re(QStringLiteral(R"(([\w]+::[\w]+))"));
//     QRegularExpressionMatch m = re.match(x);

//     if (m.hasMatch()) return m.captured(m.lastCapturedIndex());
//     return QStringLiteral("unknown");
// }

