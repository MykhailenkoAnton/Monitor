#ifndef PROCESSES_WORKER_H
#define PROCESSES_WORKER_H

#include <QObject>

#include "core/include/workers/worker_base.h"

namespace core
{
class ProcessWorker : public WorkerBase
{
    Q_OBJECT

public:
    ProcessWorker(unsigned int delayTick = 1000);

protected:
    virtual void callback() override;
};
}  // namespace core

#endif  // PROCESSES_WORKER_H