#pragma once

#include <QtCore/QString>
#include <QSharedPointer>
#include <QVector>

namespace core
{
struct ProcessInfo
{
    QString _processDateStart{};
    QString _processName{};
    QString _processPath{};
    unsigned int _PID = 0;
    unsigned int _processThreadsCount = 0;
    qulonglong _processMemoryCount = 0;
};

using ProccessesInfoPtr = QSharedPointer<QVector<ProcessInfo>>;
Q_DECLARE_METATYPE(ProccessesInfoPtr)
}  // namespace core
