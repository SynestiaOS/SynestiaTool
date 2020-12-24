#include "synestiatool.h"
#include "ui_synestiatool.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextCodec>
#include <serialportreader.h>
#include <functional>

SynestiaTool::SynestiaTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SynestiaTool)
{
    ui->setupUi(this);
}

SynestiaTool::~SynestiaTool()
{
    delete ui;
}

void SynestiaTool::on_actionAbout_triggered()
{
    this->ui->welcomePanel->setVisible(false);
    this->aboutDialog.show();
}


void SynestiaTool::on_actionSerial_Tool_triggered()
{
    this->ui->welcomePanel->setVisible(false);
    this->serialTool.setParent(this);
    this->serialTool.show();
}

void SynestiaTool::on_actionDownload_Tool_triggered()
{
    this->ui->welcomePanel->setVisible(false);
    this->downloadTool.setParent(this);
    this->downloadTool.show();
}

void SynestiaTool::on_actionOS_Monitor_triggered()
{
    this->ui->welcomePanel->setVisible(false);
    this->osMonitor.setParent(this);
    this->osMonitor.show();
}
