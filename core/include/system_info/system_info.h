#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <QtCore/QVector>

#include "process_info.h"

class SystemInfoBase
{
public:
    static SystemInfoBase& instance();

    virtual ~SystemInfoBase();

    virtual void init() = 0;
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;

    virtual void GetProcessesInfo(QVector<ProcessInfo>& processesInfo) const = 0;

signals:
    void OnProccessedUpdated();

protected:
    explicit SystemInfoBase();

protected:
    static int count_processes;

private:
    SystemInfoBase(const SystemInfoBase&);
    SystemInfoBase& operator=(const SystemInfoBase&);
};

#endif  // SYSTEM_INFO_H