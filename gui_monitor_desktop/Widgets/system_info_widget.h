#ifndef SYSTEM_INFO_WIDGET_H
#define SYSTEM_INFO_WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartView>
#include <QtCore/QTimer>

class SystemInfoWidget : public QWidget
{
    Q_OBJECT

public:
    SystemInfoWidget(QWidget* parent = nullptr, int startDelayMs = 500, int updateDelayMs = 1000);

protected:
    inline QChartView& chartView() { return _chartView; }

protected slots:

    virtual void updateSeries() = 0;

private:
    QTimer _refreshTimer;
    QChartView _chartView;
};

#endif  // SYSTEM_INFO_WIDGET_H