#ifndef PROCESS_VIEW_WIDGET_H
#define PROCESS_VIEW_WIDGET_H

#include <QtWidgets/QTableView>
#include "core/include/models/processes_model.h"
#include <QtWidgets/QHBoxLayout>

class ProccesViewWidet : public QTableView
{

public:
    ProccesViewWidet(QWidget* parent = nullptr);
    core::models::ProcessesModel* processesModel;
};

#endif  // PROCESS_VIEW_WIDGET_H