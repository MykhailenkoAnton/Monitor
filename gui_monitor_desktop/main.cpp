#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine enigne;
    enigne.loadFromModule("gui_monitor_desktop", "Main");

    return app.exec();
}