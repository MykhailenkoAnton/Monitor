#include "core/include/system_info/windows/system_info_windows.h"

#include <iostream>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <winternl.h>

#include <QtCore/QDebug>

//
namespace core
{
static void printError(TCHAR const* msg)
{
    TCHAR sysMsg[256];
    TCHAR* p;
    DWORD eNum;
    eNum = GetLastError();

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, eNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Default language
        sysMsg, 256, NULL);

    QString formatSysMsg = QString::fromWCharArray(sysMsg).trimmed();
    if (formatSysMsg.endsWith("."))
    {
        formatSysMsg.remove(".");
    }

    // Display the message
    qDebug().noquote() << "WARNING: %s" << QString::fromWCharArray(msg) << "failed with error" << eNum << "(%s)" << "(" << formatSysMsg
                       << ")";
}

class SystemInfoWindowsImpl::Impl
{
public:
    qulonglong convertFileTime(const FILETIME& ft) const
    {
        ULARGE_INTEGER largeInt;

        largeInt.LowPart = ft.dwLowDateTime;
        largeInt.HighPart = ft.dwHighDateTime;

        return largeInt.QuadPart;
    }

    QVector<qulonglong> cpuRawData()
    {
        FILETIME idleTime, kernelTime, userTime;
        GetSystemTimes(&idleTime, &kernelTime, &userTime);

        QVector<qulonglong> rawData;

        rawData.push_back(convertFileTime(idleTime));
        rawData.push_back(convertFileTime(kernelTime));
        rawData.push_back(convertFileTime(userTime));

        return rawData;
    }

    bool GetProcessList(QVector<ProcessInfo>& processesInfo) const
    {
        HANDLE hProcessSnap;
        HANDLE hProcess;
        PROCESSENTRY32 pe32;
        DWORD dwPriorityClass;

        // Take a snapshot of all processes in the system.
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
            return false;
        }

        // Set the size of the structure before using it.
        pe32.dwSize = sizeof(PROCESSENTRY32);

        // Retrieve information about the first process,
        // and exit if unsuccessful
        if (!Process32First(hProcessSnap, &pe32))
        {
            printError(TEXT("Process32First"));  // show cause of failure
            CloseHandle(hProcessSnap);           // clean the snapshot object
            return (FALSE);
        }

        // Now walk the snapshot of processes, and
        // display information about each process in turn
        do
        {
            qDebug("\n=====================================================");
            QString qs_str = QString::fromWCharArray(pe32.szExeFile);
            qDebug() << "PROCESS NAME: " << qs_str;
            qDebug("=====================================================");

            dwPriorityClass = 0;

            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);

            if (hProcess == nullptr)
            {
                printError(TEXT("OpenProcess"));
                continue;
            }
            else if (!GetPriorityClass(hProcess))
            {
                printError(TEXT("GetPriorityClass"));
                CloseHandle(hProcess);
                continue;
            }

            {

                ProcessInfo ProcInfo;
                ProcInfo._PID = pe32.th32ProcessID;
                ProcInfo._processThreadsCount = pe32.cntThreads;
                ProcInfo._processDateStart = GetProcessTime(&hProcess);
                ProcInfo._processName = QString::fromWCharArray(pe32.szExeFile);
                ProcInfo._processPath = GetProcessPath(&hProcess);
                ProcInfo._processMemoryCount = GetProcessMemoryBytes(&hProcess);  /// 1024;  // just KB now

                processesInfo.push_back(ProcInfo);
            }

            CloseHandle(hProcess);

        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);

        return true;
    }

    QString GetProcessPath(const HANDLE* const h) const
    {
        TCHAR filename[MAX_PATH];
        QString test;
        if (GetModuleFileNameEx(*h, NULL, filename, MAX_PATH) == NULL)
        {
            printError(TEXT("Failed to get module filename."));
            return QString{"N/A"};
        }
        else
        {
            qDebug() << "PROCESS PATH: " << filename;
        }

        return QString::fromWCharArray(filename);
    }

    QString GetProcessTime(const HANDLE* const h) const
    {
        FILETIME fProcessTime, ftExit, ftKernel, ftUser;
        SYSTEMTIME sProcessTime;
        if (!GetProcessTimes(*h, &fProcessTime, &ftExit, &ftKernel, &ftUser))
        {
            return QString("N/A");
        }

        FileTimeToSystemTime(&fProcessTime, &sProcessTime);

        QString time = QString("%1/%2/%3 %4:%5:%6")
                           .arg(sProcessTime.wDay, 2, 10, QChar('0'))
                           .arg(sProcessTime.wMonth, 2, 10, QChar('0'))
                           .arg(sProcessTime.wYear, 2, 10, QChar('0'))
                           .arg(sProcessTime.wHour, 2, 10, QChar('0'))
                           .arg(sProcessTime.wMinute, 2, 10, QChar('0'))
                           .arg(sProcessTime.wSecond, 2, 10, QChar('0'));

        qDebug() << "PROCESS START TIME:" << time;

        return time;
    }

    size_t GetProcessMemoryBytes(const HANDLE* const handle) const
    {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(*handle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
        {
            return static_cast<size_t>(pmc.PrivateUsage) / 1024 / 1024;  // to do
        }

        return {};
    }

public:
    QVector<qulonglong> _cpuLoadLastValues{};
};

// base
SystemInfoWindowsImpl::SystemInfoWindowsImpl() : SystemInfoBase(), pImpl(std::make_unique<Impl>()) {}

SystemInfoWindowsImpl::~SystemInfoWindowsImpl() = default;

void SystemInfoWindowsImpl::init()
{
    pImpl->_cpuLoadLastValues = pImpl->cpuRawData();
}

double SystemInfoWindowsImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = pImpl->_cpuLoadLastValues;
    QVector<qulonglong> secondSample = pImpl->cpuRawData();
    pImpl->_cpuLoadLastValues = secondSample;

    return calculateCpuLoadAverage(firstSample, secondSample);
}

double SystemInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);

    return calculateMemoryUsed(memoryStatus.ullTotalPhys, memoryStatus.ullAvailPhys);
}

void SystemInfoWindowsImpl::GetProcessesInfo(QVector<ProcessInfo>& processesInfo) const
{
    pImpl->GetProcessList(processesInfo);
}

double SystemInfoWindowsImpl::calculateCpuLoadAverage(const QVector<qulonglong>& firstSample, const QVector<qulonglong>& secondSample)
{
    qulonglong currentIdle = secondSample[0] - firstSample[0];
    qulonglong currentKernel = secondSample[1] - firstSample[1];
    qulonglong currentUser = secondSample[2] - firstSample[2];
    qulonglong currentSystem = currentUser + currentKernel;

    double percent = (currentSystem - currentIdle) * 100.0 / currentSystem;  // just for windows. for linux you can (current / all) * 100.0

    return qBound(0.0, percent, 100.0);
}

double SystemInfoWindowsImpl::calculateMemoryUsed(qulonglong ullTotalPhys, qulonglong ullAvailPhys)
{
    qulonglong memoryPhysicalUsed = ullTotalPhys - ullAvailPhys;

    return (double)memoryPhysicalUsed / (double)ullTotalPhys * 100.0;
}
}  // namespace core