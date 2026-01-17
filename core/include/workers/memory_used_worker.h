#ifndef MEMORY_USED_WORKER_H
#define MEMORY_USED_WORKER_H

#include "core/include/workers/worker_base.h"

namespace core
{
class MemoryUseWorker : public WorkerBase
{
    Q_OBJECT

public:
    MemoryUseWorker(unsigned int delayTick = 1000);

protected:
    virtual void callback() override;
};
}  // namespace core

#endif  // MEMORY_USED_WORKER_H