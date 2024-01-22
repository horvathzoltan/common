#include <execinfo.h>
#include <cxxabi.h>

#include "stackhelper.h"


// [[maybe_unused]]
// static QString Demangle_private(const char* x) {
//     int status;
//     auto a =  abi::__cxa_demangle(x, NULL, NULL, &status);
//     return a;
// }

#ifdef Q_OS_LINUX
QString StackHelper::Trace()
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
QString StackHelper::Trace()
{
    QStringList e;

    // unsigned int max_frames = 64;

    e << QStringLiteral("stack trace:");

    // WIN implementációt adni
    e << QStringLiteral("?");

    auto a =  e.join('\n');

    return a;
}
#endif
