#ifndef COM_LOGICEXCEPTION_H
#define COM_LOGICEXCEPTION_H

#include <QString>
#include <QException>
#include <QDebug>
#include "logicexception_global.h"

class LOGICEXCEPTION_EXPORT LogicException: public QException
{
private:
    const QString& msg;
public:
    explicit LogicException(const QString& _msg);

    void raise() const override;
    LogicException *clone() const override;
};

#endif // ZLOGICEXCEPTION_H
