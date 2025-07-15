#include "mainwindow.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>

#include "Widgets/system_info_widgets.h"
#include "Widgets/process_view_wdget.h"

#include <QtCore/QDebug>

#include <QtWidgets/QPushButton>

#include "core/include/system_info/system_info.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    // init manager
    SystemInfoBase::instance().init();

    // add widgets
    QWidget* central = new QWidget(parent);
    QGridLayout* grid = new QGridLayout(central);
    central->setLayout(grid);

    // t1
    ProccesViewWidet* widget1 = new ProccesViewWidet(central);
    widget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // t2
    DiagramWidget* widget2 = new DiagramWidget(central);
    widget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    grid->addWidget(widget1, 0, 0);
    grid->addWidget(widget2, 0, 1);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);

    setCentralWidget(central);
}

MainWindow::~MainWindow() {}