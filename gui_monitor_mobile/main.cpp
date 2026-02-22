#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "core/include/models/processes_model.h"
#include "core/include/system_info/windows/system_info_windows.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    core::models::ProcessesModel processesModel(core::SystemInfoBase::instance());
    engine.rootContext()->setContextProperty(QString("ProcessesModel"), &processesModel);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("gui_monitor_mobile", "Main");
    return app.exec();
}