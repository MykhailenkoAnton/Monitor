#ifndef DIAGRAM_MEMORY_WIDGET_H
#define DIAGRAM_MEMORY_WIDGET_H

#include <QtWidgets/QStackedWidget>

#include "cpu_widget.h"
#include "memory_widget.h"

#include <map>

class DiagramWidget : public QStackedWidget
{
    Q_OBJECT

public:
    DiagramWidget(QWidget* parent = nullptr);

protected:
    bool event(QEvent* e) override;

signals:
    void onMouseButtonClicked();
    void onMouseEnter();

private:
    void switchWidget();

private:
    CpuWidget _cpuWidget;
    MemoryWidget _memoryWidget;
};

#endif  // PROCESS_VIEW_WIDGET_H