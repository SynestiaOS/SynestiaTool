#ifndef SYNESTIATOOL_H
#define SYNESTIATOOL_H

#include "osmonitor.h"

#include <aboutdialog.h>
#include <downloadtool.h>
#include <QMainWindow>
#include <serialtool.h>


QT_BEGIN_NAMESPACE
namespace Ui { class SynestiaTool; }
QT_END_NAMESPACE

class SynestiaTool : public QMainWindow
{
    Q_OBJECT

public:
    SynestiaTool(QWidget *parent = nullptr);
    ~SynestiaTool();

private slots:
    void on_actionAbout_triggered();

    void on_actionSerial_Tool_triggered();

    void on_actionDownload_Tool_triggered();

    void on_actionOS_Monitor_triggered();

private:
    Ui::SynestiaTool *ui;

    AboutDialog aboutDialog;
    SerialTool serialTool;
    DownloadTool downloadTool;
    OsMonitor osMonitor;
};
#endif // SYNESTIATOOL_H
