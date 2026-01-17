#include "core/include/models/processes_model.h"

#include "core/include/system_info/system_info.h"

#include <QDebug>

namespace core
{

namespace models
{

ProcessesModel::ProcessesModel(SystemInfoBase& sysInfo, QObject* parent)
    : QAbstractTableModel(parent), _processesInfo(ProccessesInfoPtr::create())
{
    SystemInfoBase::instance().GetProcessesInfo(*_processesInfo);
}

int ProcessesModel::rowCount(const QModelIndex& parent) const
{
    return _processesInfo->size();
}

int ProcessesModel::columnCount(const QModelIndex& parent) const
{
    return COUNT;
}

QVariant ProcessesModel::data(const QModelIndex& index, int role) const
{
    if (!isValidIndex(index))
    {
        return QVariant();
    }

    const ProcessInfo& process = _processesInfo->at(index.row());

    switch (role)
    {
        case Qt::DisplayRole:
            switch (index.column())
            {
                case NAME: return process._processName; break;
                case PID: return process._PID; break;
                case PATH: return process._processPath; break;
                case DATE: return process._processDateStart; break;
                case THREADS: return process._processThreadsCount; break;
                case MEMORY: return process._processMemoryCount; break;
                default: break;
            }

        default: break;
    }

    return QVariant();
}

QVariant ProcessesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Orientation::Horizontal)
    {
        switch (section)
        {
            case NAME: return ProcessDescToString(NAME); break;
            case PID: return ProcessDescToString(PID); break;
            case PATH: return ProcessDescToString(PATH); break;
            case DATE: return ProcessDescToString(DATE); break;
            case THREADS: return ProcessDescToString(THREADS); break;
            case MEMORY: return ProcessDescToString(MEMORY); break;

            default: break;
        }
    }

    if (orientation == Qt::Orientation::Vertical)
    {
        return QString::number(section + 1);
    }

    return QVariant();
}

QString ProcessesModel::ProcessDescToString(const ProcessDisplayData value) const
{
    return QString::fromUtf8(QMetaEnum::fromType<ProcessDisplayData>().valueToKey(static_cast<int>(value)));
}

bool ProcessesModel::isValidIndex(const QModelIndex& index) const
{
    int row = index.row();
    if (row < 0 || row >= _processesInfo->size())
    {
        return false;
    }

    return true;
}

void ProcessesModel::updateProcessesData(const QVariant& data)
{
    if (_processesInfo->size() == data.value<ProccessesInfoPtr>()->size())
    {
        return;
    }

    beginResetModel();
    _processesInfo = data.value<ProccessesInfoPtr>();
    endResetModel();
}

}  // namespace models

}  // namespace core