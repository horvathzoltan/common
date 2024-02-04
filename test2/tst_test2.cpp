#include <QtTest>
#include <../../common/common/helpers/StringHelper/stringhelper.h>
#include <../../common/common/helpers/FileHelper/filehelper.h>
#include <../../common/common/helpers/TextFileHelper/textfilehelper.h>
#include <../../common/common/helpers/IniHelper/inihelper.h>
#include <../../common/common/helpers/SettingsHelper/settingshelper.h>
#include <QFileInfo>
// add necessary includes here
#include <QDebug>

//csiga

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
void test_case4();
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
    QString a2 = com::helpers::StringHelper::zNormalize(a);

    qDebug() << a <<" _ " << a2;
}

void test2::test_case2()
{
    QString e = "Hello2";
    QString fn = "testfile";
    com::helpers::FileHelper::Save(e, fn);

    auto isExist = QFileInfo::exists(fn);
    QVERIFY(isExist);

    QString e2 = com::helpers::FileHelper::Load(fn);
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

    auto a = com::helpers::IniHelper::toString(m, fn);
    qDebug() << a;

    com::helpers::FileHelper::Save(a, fn);

    auto isExist = QFileInfo::exists(fn);
    QVERIFY(isExist);

    com::helpers::FileHelper::Errors err;
    auto b = com::helpers::TextFileHelper::LoadLines(fn,&err);

    if(err == com::helpers::FileHelper::Errors::Ok){
        auto n = com::helpers::IniHelper::Parse(b, ',');
        QVERIFY(n.contains(k1));
        QVERIFY(n.contains(k2));
        QVERIFY(n[k1]==v1);
        QVERIFY(n[k2]==v2);
    }




    QVERIFY(!a.isEmpty());
}

//class Settings : public ISettings
//{

//};

void test2::test_case4()
{
    //Settings s;
    //zSettingsHelper::init("s", &s);

}
//zFileHelper::save(e, fn);
QTEST_APPLESS_MAIN(test2)

#include "tst_test2.moc"
