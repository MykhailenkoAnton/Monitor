#pragma once

#include <QtCore/QString>

struct ProcessInfo
{
    QString _processDateStart{};
    QString _processName{};
    QString _processPath{};
    unsigned int _PID = 0;
    unsigned int _processThreadsCount = 0;
    qulonglong _processMemoryCount = 0;
};
