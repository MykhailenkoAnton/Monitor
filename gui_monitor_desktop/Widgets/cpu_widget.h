#ifndef CPU_WIDGET_H
#define CPU_WIDGET_H

#include "system_info_widget.h"

#include <QtCharts/qpieseries.h>

class CpuWidget : public SystemInfoWidget
{
    Q_OBJECT

public:
    explicit CpuWidget(QWidget* parent = nullptr);

public slots:

    virtual void updateSeries(const QVariant& data) override;

private:
    QPieSeries* _series;
};

#endif  // CPU_WIDGET_H