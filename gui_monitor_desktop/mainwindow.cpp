#include "mainwindow.h"

#include <QtWidgets/QTableView>
#include <QtWidgets/QGridLayout>

#include <QtCore/QDebug>

#include "core/include/system_info/system_info.h"

#include "Widgets/widget_switcher.h"

#include "core/include/workers/cpu_load_worker.h"
#include "core/include/workers/memory_used_worker.h"
#include "core/include/workers/processes_worker.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    auto& sysInst = core::SystemInfoBase::instance();
    sysInst.init();
    _controller = std::make_unique<core::Controller>();

    // add widgets
    QWidget* central = new QWidget(parent);
    QGridLayout* grid = new QGridLayout(central);
    central->setLayout(grid);

    // processes list
    QTableView* tableWidget = new QTableView(central);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _processesModel = std::make_unique<core::models::ProcessesModel>(sysInst);
    tableWidget->setModel(_processesModel.get());
    _controller->addWorker<core::ProcessWorker>();
    connect(_controller.get(), &core::Controller::updateProcesses, _processesModel.get(),
        &core::models::ProcessesModel::updateProcessesData, Qt::QueuedConnection);

    // cpu and memory view
    WidgetSwitcher* widgetSwitcher = new WidgetSwitcher(central);
    widgetSwitcher->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(_controller.get(), &core::Controller::updateCpuData, widgetSwitcher->GetCpuWidget(), &CpuWidget::updateSeries,
        Qt::QueuedConnection);
    _controller->addWorker<core::CPULoadWoker>();
    connect(_controller.get(), &core::Controller::updateMemoryData, widgetSwitcher->GetMemoryWidget(), &MemoryWidget::updateSeries,
        Qt::QueuedConnection);
    _controller->addWorker<core::MemoryUseWorker>(500);

    grid->addWidget(tableWidget, 0, 0);
    grid->addWidget(widgetSwitcher, 0, 1);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);

    setCentralWidget(central);

    // starts all workers
    _controller->startJob();
}

MainWindow::~MainWindow() {}