#include "core/include/workers/memory_used_worker.h"
#include <QVariant>

#include "core/include/system_info/system_info.h"

namespace core
{
MemoryUseWorker::MemoryUseWorker(unsigned int delayTick)
{
    _delayTick = delayTick;
}

void MemoryUseWorker::callback()
{
    const double memoryUsed = SystemInfoBase::instance().memoryUsed();
    emit this->updateWorker(QVariant::fromValue(memoryUsed));
}
}  // namespace core