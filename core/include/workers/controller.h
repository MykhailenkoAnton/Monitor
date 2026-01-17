#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

#include "core/include/workers/processes_worker.h"
#include "core/include/workers/cpu_load_worker.h"
#include "core/include/workers/memory_used_worker.h"
#include "core/include/workers/worker_base.h"

namespace core
{
class Controller : public QObject
{
    Q_OBJECT

public:
    Controller() {}
    ~Controller()
    {
        for (const auto& pair : workersThreads)
        {
            if (pair.first->isRunning())
            {
                pair.first->quit();
                pair.first->wait();
            }

            delete pair.first;
        }
    }

    template <typename T>
    void addWorker(unsigned int delayTick = 1000)
    {
        QThread* workerThread = new QThread();
        WorkerBase* worker = new T(delayTick);
        worker->moveToThread(workerThread);

        connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::startJob, worker, &WorkerBase::start);

        if constexpr (std::is_same_v<T, ProcessWorker>)
        {
            connect(worker, &WorkerBase::updateWorker, this, &Controller::updateProcesses);
        }
        else if constexpr (std::is_same_v<T, CPULoadWoker>)
        {
            connect(worker, &WorkerBase::updateWorker, this, &Controller::updateCpuData);
        }
        else if constexpr (std::is_same_v<T, MemoryUseWorker>)
        {
            connect(worker, &WorkerBase::updateWorker, this, &Controller::updateMemoryData);
        }

        workerThread->start();
        workersThreads.push_back({workerThread, worker});
    }

signals:
    void startJob();

    void updateProcesses(const QVariant& data);
    void updateCpuData(const QVariant& data);
    void updateMemoryData(const QVariant& data);

private:
    std::vector<std::pair<QThread*, WorkerBase*>> workersThreads;
};

}  // namespace core

#endif