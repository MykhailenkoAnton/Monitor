#ifndef WORKER_BASE_H
#define WORKER_BASE_H

#include <QObject>

namespace core
{
class WorkerBase : public QObject
{
    Q_OBJECT

public slots:
    virtual void start();

protected:
    virtual void callback() = 0;

protected:
    unsigned int _delayTick = -1;

signals:
    void updateWorker(const QVariant& data);
};
}  // namespace core

#endif  // CPU_LOAD_WORKER_H