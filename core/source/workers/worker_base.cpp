#include "core/include/workers/worker_base.h"

#include <QTimer>
#include <QVariant>

namespace core
{
void WorkerBase::start()
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WorkerBase::callback);
    timer->start(_delayTick);
}
}  // namespace core
