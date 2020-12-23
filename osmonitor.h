#ifndef OSMONITOR_H
#define OSMONITOR_H

#include <QMainWindow>

namespace Ui {
class OSMonitor;
}

class OSMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSMonitor(QWidget *parent = nullptr);
    ~OSMonitor();

private:
    Ui::OSMonitor *ui;
};

#endif // OSMONITOR_H
