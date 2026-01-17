#ifndef CPU_LOAD_WORKER_H
#define CPU_LOAD_WORKER_H

#include "core/include/workers/worker_base.h"

namespace core
{
class CPULoadWoker : public WorkerBase
{
    Q_OBJECT

public:
    CPULoadWoker(unsigned int delayTick = 1000);

protected:
    virtual void callback() override;
};
}  // namespace core

#endif  // CPU_LOAD_WORKER_H