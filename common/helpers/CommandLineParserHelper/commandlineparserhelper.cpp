#include "commandlineparserhelper.h"
#include <QStringList>

namespace com { namespace helpers{

CommandLineParserHelper::CommandLineParserHelper()= default;

bool CommandLineParserHelper::addOption(QCommandLineParser *p,
                                        const QString& o, const QString& description){

    QString optionName = o.at(0);
    //if(p->optionNames().contains(optionName)) return false;
    return p->addOption({{optionName,o},description,o});
}

// option without value
bool CommandLineParserHelper::addOptionBool(QCommandLineParser *p,
                                            const QString& o, const QString& description){
    QString optionName = o.at(0);
    //if(p->optionNames().contains(optionName)) return false;
    return p->addOption({{optionName,o},description});
}

}
}
