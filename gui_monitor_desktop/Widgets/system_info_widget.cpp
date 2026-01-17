#include "system_info_widget.h"

#include <QtWidgets/QHBoxLayout>

SystemInfoWidget::SystemInfoWidget(QWidget* parent) : QWidget(parent), _chartView(this)
{
    _chartView.setRenderHint(QPainter::Antialiasing);
    _chartView.chart()->legend()->setVisible(false);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(&_chartView);
    setLayout(layout);
}