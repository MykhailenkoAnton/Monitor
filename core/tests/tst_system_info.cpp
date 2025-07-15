#include <QtTest/QTest>

#include <QVector>
#include "core/include/system_info/system_info.h"
#include "core/include/system_info/process_info.h"

#include "core/include/system_info/windows/system_info_windows.h"

class FakeSystem : public SystemInfoWindowsImpl
{
public:
    double calculateCpuLoadAverage(const QVector<qulonglong>& firstSample, const QVector<qulonglong>& secondSample)
    {
        return SystemInfoWindowsImpl::calculateCpuLoadAverage(firstSample, secondSample);
    }

    double calculateMemoryUsed(qulonglong allMemoryPhys, qulonglong allMemoryAvail)
    {
        return SystemInfoWindowsImpl::calculateMemoryUsed(allMemoryPhys, allMemoryAvail);
    }
};

class TestSystemInfo : public QObject
{
    Q_OBJECT
private slots:
    void GetProcessesInfoTest();
    void GetMemoryUsed();
    void GetCPUAvarage();
    //
    void CalculateCpuAvarage();
    void CalculateMemoryUsed();
};

void TestSystemInfo::GetProcessesInfoTest()
{
    SystemInfoBase::instance().init();

    QVector<ProcessInfo> processesInfo;
    SystemInfoBase::instance().GetProcessesInfo(processesInfo);
    QVERIFY(processesInfo.size() != 0);

    for (int i = 0; i < processesInfo.size(); i++)
    {
        QVERIFY(processesInfo[i]._PID != 0);
        QVERIFY(processesInfo[i]._processThreadsCount >= 1);
        QVERIFY(processesInfo[i]._processName != QString(""));
    }
}

void TestSystemInfo::GetMemoryUsed()
{
    SystemInfoBase::instance().init();
    const double memory = SystemInfoBase::instance().memoryUsed();
    QVERIFY(memory >= 0.0 && memory <= 100.0);
}

void TestSystemInfo::GetCPUAvarage()
{
    SystemInfoBase::instance().init();
    const double cpu = SystemInfoBase::instance().cpuLoadAverage();
    QVERIFY(cpu >= 0.0 && cpu <= 100.0);
}

void TestSystemInfo::CalculateCpuAvarage()
{
    QVector<qulonglong> first{100, 200, 300};
    QVector<qulonglong> second{150, 250, 350};

    FakeSystem system;
    const double avarage = system.calculateCpuLoadAverage(first, second);
    QCOMPARE(avarage, 50.0);
}

void TestSystemInfo::CalculateMemoryUsed()
{
    qulonglong allMemoryPhys = 80;
    qulonglong allMemoryAvail = 50;

    FakeSystem system;
    const double memoryUsed = system.calculateMemoryUsed(allMemoryPhys, allMemoryAvail);
    QCOMPARE(memoryUsed, 37.5);
}

QTEST_GUILESS_MAIN(TestSystemInfo)
#include "tst_system_info.moc"