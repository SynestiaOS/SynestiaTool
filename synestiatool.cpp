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

    this->serialList = QSerialPortInfo::availablePorts();

    this->initUi();

}

SynestiaTool::~SynestiaTool()
{
    delete ui;
}

void SynestiaTool::initUi()
{
    ui->buadList->addItem("1200");
    ui->buadList->addItem("2400");
    ui->buadList->addItem("4800");
    ui->buadList->addItem("9600");
    ui->buadList->addItem("19200");
    ui->buadList->addItem("38400");
    ui->buadList->addItem("57600");
    ui->buadList->addItem("115200");


    ui->dataBits->addItem("5");
    ui->dataBits->addItem("6");
    ui->dataBits->addItem("7");
    ui->dataBits->addItem("8");

    ui->stopBits->addItem("OneStop");
    ui->stopBits->addItem("OneAndHalfStop");
    ui->stopBits->addItem("TwoStop");

    ui->checkBits->addItem("NoParity");
    ui->checkBits->addItem("EvenParity");
    ui->checkBits->addItem("OddParity");
    ui->checkBits->addItem("SpaceParity");
    ui->checkBits->addItem("MarkParity");

    ui->serialCheckBox->setEnabled(false);
    ui->buadCheckBox->setEnabled(false);
    ui->dataCheckBox->setEnabled(false);
    ui->chechCheckBox->setEnabled(false);
    ui->stopCheckBox->setEnabled(false);

    ui->connectionConnectBtn->setEnabled(false);
    ui->connectionCloseBtn->setEnabled(false);
    ui->connectionState->setChecked(false);
    ui->connectionState->setEnabled(false);

    this->initSerialPorts();
}

void SynestiaTool::initSerialPorts()
{
    QStringList serials;
    for(int i = 0;i<this->serialList.size();i++){
        serials.push_back(this->serialList.at(i).portName());
    }

    ui->serialPorts->clear();
    ui->serialPorts->addItems(serials);
}

void SynestiaTool::chanageConnectButtonState()
{
    if(ui->serialCheckBox->checkState()==Qt::CheckState::Checked &&
            ui->buadCheckBox->checkState()==Qt::CheckState::Checked&&
            ui->dataCheckBox->checkState()==Qt::CheckState::Checked&&
            ui->chechCheckBox->checkState()==Qt::CheckState::Checked&&
            ui->stopCheckBox->checkState()==Qt::CheckState::Checked &&
            this->connectionState == false){
        ui->connectionConnectBtn->setEnabled(true);
    }
}


void SynestiaTool::on_connectionRefreshBtn_clicked()
{
    this->serialList = QSerialPortInfo::availablePorts();
    this->initSerialPorts();
}

void SynestiaTool::on_serialPorts_activated(int index)
{
    QSerialPortInfo selectedInfo =  this->serialList.at(index);
    this->ui->selectedSerialPort->setText(selectedInfo.portName());
    this->serialPort.setPortName(selectedInfo.portName());

    this->ui->serialCheckBox->setCheckState(Qt::CheckState::Checked);
}

void SynestiaTool::on_connectionConnectBtn_clicked()
{

    int selectederialPort = this->ui->serialPorts->currentIndex();
    QSerialPortInfo selectedInfo =  this->serialList.at(selectederialPort);


    if (!this->serialPort.open(QIODevice::ReadOnly)) {
        this->ui->recvViewer->setHtml("<span style=\"color:'red'\">Failed to open port!</span>");
    }else{
        this->ui->connectionConnectBtn->setEnabled(false);
        this->ui->connectionCloseBtn->setEnabled(true);
        this->ui->connectionState->setChecked(true);

        this->connectionState = true;
        this->ui->buadList->setEnabled(false);
        this->ui->serialPorts->setEnabled(false);
        this->ui->dataBits->setEnabled(false);
        this->ui->checkBits->setEnabled(false);
        this->ui->stopBits->setEnabled(false);
        this->ui->connectionRefreshBtn->setEnabled(false);

        SerialPortReader serialPortReader(&this->serialPort,
                                          std::bind(&SynestiaTool::onDataReceived,this,std::placeholders::_1),
                                          std::bind(&SynestiaTool::onSerialError,this,std::placeholders::_1),
                                          std::bind(&SynestiaTool::onTimeout,this));
    }
}

void SynestiaTool::on_buadList_activated(const QString &arg1)
{
    this->serialPort.setBaudRate(arg1.toInt());
    this->ui->buadCheckBox->setCheckState(Qt::CheckState::Checked);
    this->chanageConnectButtonState();
}

void SynestiaTool::on_dataBits_activated(int index)
{
    switch(index){
    case 0:
        this->serialPort.setDataBits((QSerialPort::DataBits::Data5));
        break;
    case 1:
        this->serialPort.setDataBits((QSerialPort::DataBits::Data6));
        break;
    case 2:
        this->serialPort.setDataBits((QSerialPort::DataBits::Data7));
        break;
    case 3:
        this->serialPort.setDataBits((QSerialPort::DataBits::Data8));
        break;
    }

    this->ui->dataCheckBox->setCheckState(Qt::CheckState::Checked);
    this->chanageConnectButtonState();
}

void SynestiaTool::on_checkBits_activated(int index)
{
    switch(index){
    case 0:
        this->serialPort.setParity((QSerialPort::Parity::NoParity));
        break;
    case 1:
        this->serialPort.setParity((QSerialPort::Parity::EvenParity));
        break;
    case 2:
        this->serialPort.setParity((QSerialPort::Parity::OddParity));
        break;
    case 3:
        this->serialPort.setParity((QSerialPort::Parity::SpaceParity));
        break;
    case 4:
        this->serialPort.setParity((QSerialPort::Parity::MarkParity));
        break;
    }

    this->ui->chechCheckBox->setCheckState(Qt::CheckState::Checked);
    this->chanageConnectButtonState();
}


void SynestiaTool::on_stopBits_activated(int index)
{
    switch(index){
    case 0:
        this->serialPort.setStopBits((QSerialPort::StopBits::OneStop));
        break;
    case 1:
        this->serialPort.setStopBits((QSerialPort::StopBits::OneAndHalfStop));
        break;
    case 2:
        this->serialPort.setStopBits((QSerialPort::StopBits::TwoStop));
        break;
    }

    this->ui->stopCheckBox->setCheckState(Qt::CheckState::Checked);
    this->chanageConnectButtonState();
}

void SynestiaTool::on_connectionCloseBtn_clicked()
{
    this->serialPort.close();
    this->connectionState = false;
    this->ui->connectionConnectBtn->setEnabled(true);
    this->ui->connectionCloseBtn->setEnabled(false);
    this->ui->connectionRefreshBtn->setEnabled(true);
    this->ui->connectionState->setChecked(false);

    this->ui->buadList->setEnabled(true);
    this->ui->serialPorts->setEnabled(true);
    this->ui->dataBits->setEnabled(true);
    this->ui->checkBits->setEnabled(true);
    this->ui->stopBits->setEnabled(true);
}

void SynestiaTool::onDataReceived(QByteArray data)
{
    this->ui->recvViewer->append("data recv.");
}

void SynestiaTool::onTimeout()
{
    this->ui->recvViewer->append("time out.");
}

void SynestiaTool::onSerialError(QSerialPort::SerialPortError serialPortError)
{
    this->ui->recvViewer->append("error.");
}

void SynestiaTool::on_actionAbout_triggered()
{
    this->aboutDialog.show();
}
