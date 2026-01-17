#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <QtCore/QVector>

#include "process_info.h"

namespace core
{
class SystemInfoBase
{
public:
    static SystemInfoBase& instance();

    virtual ~SystemInfoBase();

    virtual void init() = 0;
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;

    virtual void GetProcessesInfo(QVector<ProcessInfo>& processesInfo) const = 0;

protected:
    explicit SystemInfoBase();

private:
    SystemInfoBase(const SystemInfoBase&);
    SystemInfoBase& operator=(const SystemInfoBase&);
};

}  // namespace core

#endif  // SYSTEM_INFO_H