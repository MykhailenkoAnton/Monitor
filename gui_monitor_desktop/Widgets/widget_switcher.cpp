#include "widget_switcher.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolTip>

WidgetSwitcher::WidgetSwitcher(QWidget* parent) : QStackedWidget(parent), _cpuWidget(this), _memoryWidget(this)
{
    this->addWidget(&_cpuWidget);
    this->addWidget(&_memoryWidget);

    this->setCurrentWidget(&_memoryWidget);

    connect(this, &WidgetSwitcher::onMouseButtonClicked, this, [this]() { setCurrentIndex((currentIndex() + 1) % count()); });

    connect(this, &WidgetSwitcher::onMouseEnter, this,
        [this]() { QToolTip::showText(QCursor::pos() += QPoint(0, -50), "Click to switch widget", this); });
}

bool WidgetSwitcher::event(QEvent* e)
{
    switch (e->type())
    {
        case QEvent::MouseButtonPress: emit onMouseButtonClicked(); break;

        case QEvent::Enter: emit onMouseEnter(); break;

        default: break;
    }

    return QWidget::event(e);
}
