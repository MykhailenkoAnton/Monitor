#include "core/include/workers/cpu_load_worker.h"
#include <QVariant>

#include "core/include/system_info/system_info.h"

namespace core
{
CPULoadWoker::CPULoadWoker(unsigned int delayTick)
{
    _delayTick = delayTick;
}

void CPULoadWoker::callback()
{
    const double cpuLoadAvarage = SystemInfoBase::instance().cpuLoadAverage();
    emit this->updateWorker(QVariant::fromValue(cpuLoadAvarage));
}
}  // namespace core
