#ifndef COM_ZLOGICEXCEPTION_H
#define COM_ZLOGICEXCEPTION_H

#include <QString>
#include <QException>
#include <QDebug>
#include "zlogicexpression_global.h"

class MACROFACTORYSHARED_EXPORT zLogicException: public QException
{
private:
    const QString& msg;
public:
    explicit zLogicException(const QString& _msg);

    void raise() const override;
    zLogicException *clone() const override;
};

#endif // ZLOGICEXCEPTION_H
