#include "system_info_widget.h"

#include <QtWidgets/QHBoxLayout>

SystemInfoWidget::SystemInfoWidget(QWidget* parent, int startDelayMs, int updateDelayMs) : QWidget(parent), _chartView(this)
{
    _refreshTimer.setInterval(updateDelayMs);
    connect(&_refreshTimer, &QTimer::timeout, this, &SystemInfoWidget::updateSeries);
    QTimer::singleShot(startDelayMs, [this] { _refreshTimer.start(); });

    _chartView.setRenderHint(QPainter::Antialiasing);
    _chartView.chart()->legend()->setVisible(false);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(&_chartView);
    setLayout(layout);
}