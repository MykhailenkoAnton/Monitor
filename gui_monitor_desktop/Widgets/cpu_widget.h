#ifndef CPU_WIDGET_H
#define CPU_WIDGET_H

#include "system_info_widget.h"

#include <QtCharts/qpieseries.h>

class CpuWidget : public SystemInfoWidget
{
    Q_OBJECT

public:
    explicit CpuWidget(QWidget* parent = nullptr);

protected slots:

    virtual void updateSeries() override;

private:
    QPieSeries* _series;
};

#endif  // CPU_WIDGET_H