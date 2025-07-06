#include <QtTest/QTest>

class TestQString2: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void TestQString2::toUpper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

QTEST_GUILESS_MAIN(TestQString2)
#include "tst_mytest2.moc"