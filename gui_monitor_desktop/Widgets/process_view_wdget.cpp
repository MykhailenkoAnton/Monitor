#include "process_view_wdget.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include "core/include/system_info/system_info.h"

ProccesViewWidet::ProccesViewWidet(QWidget* parent)
    : QTableView(parent), processesModel(new core::models::ProcessesModel(SystemInfoBase::instance()))
{
    this->setModel(processesModel);
    // this->show();

    // core::Process proces;
    // core::Process proces2;
    // core::Process proces3;
    // core::Process proces4;

    // processesModel->addProcess(proces);
    // processesModel->addProcess(proces2);
    // processesModel->addProcess(proces3);
    // processesModel->addProcess(proces4);
}