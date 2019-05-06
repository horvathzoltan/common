#include <QtTest>
#include <../common/stringhelper/stringhelper.h>
#include <../common/filehelper/filehelper.h>
#include <../common/inihelper/zinihelper.h>
#include <QFileInfo>
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
void test_case2();
void test_case3();
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

void test2::test_case2()
{
    QString e = "Hello2";
    QString fn = "testfile";
    zFileHelper::save(e, fn);

    auto isExist = QFileInfo::exists(fn);
    QVERIFY(isExist);

    QString e2 = zFileHelper::load(fn);    
    QVERIFY(e == e2);
}

void test2::test_case3()
{
    QMap<QString, QString> m;

    QString k1="k1";
    QString k2="k2";
    QString v1="v1";
    QString v2="v2";
    auto fn = QStringLiteral("valami");

    m.insert(k1, v1);
    m.insert(k2, v2);

    auto a = zIniHelper::toString(m, fn);
    qDebug() << a;

    zFileHelper::save(a, fn);

    auto isExist = QFileInfo::exists(fn);
    QVERIFY(isExist);

    auto b = zFileHelper::load(fn);

    auto n = zIniHelper::parseIni(b);

    QVERIFY(n.contains(k1));
    QVERIFY(n.contains(k2));
    QVERIFY(n[k1]==v1);
    QVERIFY(n[k2]==v2);


    QVERIFY(!a.isEmpty());
}
//zFileHelper::save(e, fn);
QTEST_APPLESS_MAIN(test2)

#include "tst_test2.moc"
