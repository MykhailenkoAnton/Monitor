#include "memory_widget.h"

#include <QtCharts/QAreaSeries>

constexpr int CHAR_X_RANGE_COUNT = 50;
constexpr int CHAR_X_RANGE_MAX = CHAR_X_RANGE_COUNT - 1;

constexpr int COLOR_DARK_BLUE = 0x209fdf;
constexpr int COLOR_LIGHT_BLUE = 0xbfdfef;
constexpr int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget* parent) : SystemInfoWidget(parent), _series(new QLineSeries(this)), _pointPositionX(0)
{
    QPen pen(COLOR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(1.0, COLOR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    QAreaSeries* areaSeries = new QAreaSeries(_series);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);

    QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    chart->setTitle("Memory used");
    chart->createDefaultAxes();

    chart->axisX()->setVisible(false);

    QVariant minX = QVariant::fromValue(0);
    QVariant maxX = QVariant::fromValue(CHAR_X_RANGE_MAX);
    chart->axisX()->setRange(minX, maxX);

    QVariant minY = QVariant::fromValue(0);
    QVariant maxY = QVariant::fromValue(100);
    chart->axisY()->setRange(minY, maxY);
}

void MemoryWidget::updateSeries(const QVariant& data)
{
    const double memoryUsed = data.value<double>();
    _series->append(_pointPositionX++, memoryUsed);

    if (_series->count() > CHAR_X_RANGE_COUNT)
    {
        QChart* chart = chartView().chart();
        chart->scroll(chart->plotArea().width() / CHAR_X_RANGE_MAX, 0);
        _series->remove(0);
    }
}