#ifndef MEMORY_WIDGET_H
#define MEMORY_WIDGET_H

#include "system_info_widget.h"

#include <QtCharts/qlineseries.h>

class MemoryWidget : public SystemInfoWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget* parent = nullptr);

public slots:

    virtual void updateSeries(const QVariant& data) override;

private:
    QLineSeries* _series;
    qint64 _pointPositionX;
};

#endif  // MEMORY_WIDGET_H