#ifndef SYSTEM_INFO_WINDOWS_H
#define SYSTEM_INFO_WINDOWS_H

#include "core/include/system_info/system_info.h"

#include <QtCore/QtTypes>
#include <QtCore/QVector>

#include <memory>

namespace core
{
class SystemInfoWindowsImpl : public SystemInfoBase
{
public:
    SystemInfoWindowsImpl();
    ~SystemInfoWindowsImpl();

    virtual void init() override;
    virtual double cpuLoadAverage() override;
    virtual double memoryUsed() override;

    //
    virtual void GetProcessesInfo(QVector<ProcessInfo>& processesInfo) const override;

protected:
    double calculateCpuLoadAverage(const QVector<qulonglong>& firstSample, const QVector<qulonglong>& secondSample);
    double calculateMemoryUsed(qulonglong ullTotalPhys, qulonglong ullAvailPhys);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};
}  // namespace core

#endif  // SYSTEM_INFO_WINDOWS_H