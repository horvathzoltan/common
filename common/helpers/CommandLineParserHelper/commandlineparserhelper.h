#ifndef COM_COMMANLINEPARSERHELPER_H
#define COM_COMMANLINEPARSERHELPER_H

#include "commandlineparserhelper_global.h"

#include <QCommandLineParser>
namespace com { namespace helpers{
class COM_COMMANDLINEPARSERHELPER_EXPORT CommandLineParserHelper
{
public:
    CommandLineParserHelper();
    static bool addOption(QCommandLineParser *p, const QString& o, const QString& d);
    static bool addOptionBool(QCommandLineParser *p, const QString& o, const QString& d);
};
}
}
#endif // COMMANLINEPARSERHELPER_H
