#ifndef PROCESSES_MODEL_H
#define PROCESSES_MODEL_H

#include <QAbstractTableModel>
#include <QtCore>
#include <QtCore/QMetaEnum>

#include "core/include/system_info/system_info.h"
#include "core/include/system_info/process_info.h"

#include <memory>

namespace core
{

namespace models
{

class ProcessesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum ProcessDisplayData
    {
        NAME = 0,
        PID,
        PATH,
        DATE,
        THREADS,
        MEMORY,

        COUNT
    };
    Q_ENUM(ProcessDisplayData)

    ProcessesModel(SystemInfoBase& sysInfo, QObject* parent = nullptr);

public:
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

protected:
    QString ProcessDescToString(const ProcessDisplayData value) const;

private:
    bool isValidIndex(const QModelIndex& index) const;

private:
    std::unique_ptr<QVector<ProcessInfo>> _processesInfo;
};

}  // namespace models
}  // namespace core

#endif  // PROCESSES_MODEL_H