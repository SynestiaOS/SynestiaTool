#include "osmonitor.h"
#include "ui_osmonitor.h"

OSMonitor::OSMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSMonitor)
{
    ui->setupUi(this);
}

OSMonitor::~OSMonitor()
{
    delete ui;
}
