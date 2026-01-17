#include "core/include/workers/processes_worker.h"
#include <QVariant>

#include "core/include/system_info/system_info.h"

namespace core
{
ProcessWorker::ProcessWorker(unsigned int delayTick)
{
    _delayTick = delayTick;
}

void ProcessWorker::callback()
{
    ProccessesInfoPtr data = ProccessesInfoPtr::create();
    SystemInfoBase::instance().GetProcessesInfo(*data);
    emit this->updateWorker(QVariant::fromValue(data));
}
}  // namespace core