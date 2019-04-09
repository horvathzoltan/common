#include <QtTest>
#include <../stringhelper/stringhelper.h>
// add necessary includes here
#include <QDebug>

class test2 : public QObject
{
Q_OBJECT

public:
test2();
~test2();

private slots:
void test_case1();

};

test2::test2()
{

}

test2::~test2()
{

}

void test2::test_case1()
{
    QString str = "Hello";
    //QString e = zStringHelper::toUpper(str);
    QVERIFY(str.toUpper() == "HELLO");
    //QVERIFY(e == "HELLO");

    QString a = "Apple";
    QString a2 = zStringHelper::zNormalize(a);

    qDebug() << a <<" _ " << a2;
}

QTEST_APPLESS_MAIN(test2)

#include "tst_test2.moc"
