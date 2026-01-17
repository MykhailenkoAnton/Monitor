#ifndef SYSTEM_INFO_WIDGET_H
#define SYSTEM_INFO_WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartView>

class SystemInfoWidget : public QWidget
{
    Q_OBJECT

public:
    SystemInfoWidget(QWidget* parent = nullptr);

protected:
    inline QChartView& chartView() { return _chartView; }

public slots:

    virtual void updateSeries(const QVariant& data) = 0;

private:
    QChartView _chartView;
};

#endif  // SYSTEM_INFO_WIDGET_H