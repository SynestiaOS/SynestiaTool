#include "synestiatool.h"
#include "ui_synestiatool.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextCodec>
#include <SerialPortReader.h>
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
    this->serialTool.size().setWidth(this->ui->centralwidget->size().width());
    this->serialTool.setParent(this);
    this->serialTool.show();
}
