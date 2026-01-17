#ifndef DIAGRAM_MEMORY_WIDGET_H
#define DIAGRAM_MEMORY_WIDGET_H

#include <QtWidgets/QStackedWidget>

#include "cpu_widget.h"
#include "memory_widget.h"

class WidgetSwitcher : public QStackedWidget
{
    Q_OBJECT

public:
    WidgetSwitcher(QWidget* parent = nullptr);

    CpuWidget* GetCpuWidget() { return &_cpuWidget; }
    MemoryWidget* GetMemoryWidget() { return &_memoryWidget; }

protected:
    bool event(QEvent* e) override;

signals:
    void onMouseButtonClicked();
    void onMouseEnter();

private:
    CpuWidget _cpuWidget;
    MemoryWidget _memoryWidget;
};

#endif  // PROCESS_VIEW_WIDGET_H