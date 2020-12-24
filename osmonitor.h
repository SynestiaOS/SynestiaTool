#ifndef OSMONITOR_H
#define OSMONITOR_H

#include <QDockWidget>
#include <QWidget>

namespace Ui {
class OsMonitor;
}

class OsMonitor : public QDockWidget
{
    Q_OBJECT

public:
    explicit OsMonitor(QWidget *parent = nullptr);
    ~OsMonitor();

private:
    Ui::OsMonitor *ui;
};

#endif // OSMONITOR_H
