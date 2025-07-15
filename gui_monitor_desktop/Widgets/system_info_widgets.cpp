#include "system_info_widgets.h"
#include "core/include/system_info/system_info.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolTip>

DiagramWidget::DiagramWidget(QWidget* parent) : QStackedWidget(parent), _cpuWidget(this), _memoryWidget(this)
{
    // SystemInfoBase::instance().init();

    this->addWidget(&_cpuWidget);
    this->addWidget(&_memoryWidget);

    this->setCurrentWidget(&_memoryWidget);

    connect(this, &DiagramWidget::onMouseButtonClicked, this, [this]() { setCurrentIndex((currentIndex() + 1) % count()); });

    connect(this, &DiagramWidget::onMouseEnter, this,
        [this]() { QToolTip::showText(QCursor::pos() += QPoint(0, -50), "Click to switch widget", this); });
}

bool DiagramWidget::event(QEvent* e)
{
    switch (e->type())
    {
        case QEvent::MouseButtonPress: emit onMouseButtonClicked(); break;

        case QEvent::Enter: emit onMouseEnter(); break;

        default: break;
    }

    return QWidget::event(e);
}
