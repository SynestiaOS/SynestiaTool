#ifndef SYNESTIATOOL_H
#define SYNESTIATOOL_H

#include <AboutDialog.h>
#include <QMainWindow>
#include <SerialTool.h>


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

private:
    Ui::SynestiaTool *ui;

    AboutDialog aboutDialog;
    SerialTool serialTool;
};
#endif // SYNESTIATOOL_H
