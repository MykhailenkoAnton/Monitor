#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include <memory>

#include "core/include/models/processes_model.h"
#include "core/include/workers/controller.h"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<core::models::ProcessesModel> _processesModel;
    std::unique_ptr<core::Controller> _controller;
};

#endif