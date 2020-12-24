#include "osmonitor.h"
#include "ui_osmonitor.h"

OsMonitor::OsMonitor(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::OsMonitor)
{
    ui->setupUi(this);
}

OsMonitor::~OsMonitor()
{
    delete ui;
}
