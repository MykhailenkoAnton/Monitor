#include "cpu_widget.h"

#include "core/include/system_info/system_info.h"

CpuWidget::CpuWidget(QWidget* parent) : SystemInfoWidget(parent), _series(new QPieSeries(this))
{
    _series->setHoleSize(0.35);
    _series->append("CPU Load", 30.0);
    _series->append("CPU Free", 70.0);

    if (QChart* chart = chartView().chart())
    {
        chart->addSeries(_series);
        chart->setTitle("CPU average load");
    }
}

void CpuWidget::updateSeries()
{
    const double cpuLoadAvarage = SystemInfoBase::instance().cpuLoadAverage();
    _series->clear();
    _series->append("Load", cpuLoadAvarage);
    _series->append("Free", 100.0 - cpuLoadAvarage);
}