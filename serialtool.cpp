#include "serialtool.h"
#include "ui_serialtool.h"

#include <QMessageBox>
#include <QTextCodec>
#include <serialportreader.h>

SerialTool::SerialTool(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SerialTool)
{
    ui->setupUi(this);
    this->serialList = QSerialPortInfo::availablePorts();
    this->initUi();
}

SerialTool::~SerialTool()
{
    delete ui;
}


void SerialTool::initUi()
{
    ui->buadList->addItem("115200");
    ui->buadList->addItem("1200");
    ui->buadList->addItem("2400");
    ui->buadList->addItem("4800");
    ui->buadList->addItem("9600");
    ui->buadList->addItem("19200");
    ui->buadList->addItem("38400");
    ui->buadList->addItem("57600");



    ui->dataBits->addItem("8");
    ui->dataBits->addItem("5");
    ui->dataBits->addItem("6");
    ui->dataBits->addItem("7");


    ui->stopBits->addItem("OneStop");
    ui->stopBits->addItem("OneAndHalfStop");
    ui->stopBits->addItem("TwoStop");

    ui->checkBits->addItem("NoParity");
    ui->checkBits->addItem("EvenParity");
    ui->checkBits->addItem("OddParity");
    ui->checkBits->addItem("SpaceParity");
    ui->checkBits->addItem("MarkParity");

    ui->connectionConnectBtn->setEnabled(true);
    ui->connectionCloseBtn->setEnabled(false);
    ui->connectionState->setChecked(false);
    ui->connectionState->setEnabled(false);

    this->ui->sendBtn->setEnabled(false);

    this->initSerialPorts();

    this->serialPort.setPortName(this->serialList.at(0).portName());
    this->serialPort.setDataBits((QSerialPort::DataBits::Data8));
    this->serialPort.setStopBits((QSerialPort::StopBits::OneStop));
    this->serialPort.setParity((QSerialPort::Parity::NoParity));
    this->serialPort.setBaudRate(115200);
}

void SerialTool::initSerialPorts()
{
    QStringList serials;
    for(int i = 0;i<this->serialList.size();i++){
        QString po;
        if(this->serialList.at(i).isBusy()){
            po.append("[Busy] ");
        }else{
            po.append("[Free] ");
        }
        po.append(this->serialList.at(i).portName());
        serials.push_back(po);
    }

    ui->serialPorts->clear();
    ui->serialPorts->addItems(serials);
}


void SerialTool::on_connectionRefreshBtn_clicked()
{
    this->serialList = QSerialPortInfo::availablePorts();
    this->initSerialPorts();
}

void SerialTool::on_serialPorts_activated(int index)
{
    QSerialPortInfo selectedInfo =  this->serialList.at(index);
    this->ui->selectedSerialPort->setText(selectedInfo.portName());
    this->serialPort.setPortName(selectedInfo.portName());

    this->ui->serialName->setText(selectedInfo.portName());
    this->ui->desc->setText(selectedInfo.description());
    this->ui->manfactor->setText(selectedInfo.manufacturer());
    this->ui->serialNumber->setText(selectedInfo.serialNumber());
}

void SerialTool::on_connectionConnectBtn_clicked()
{

    int selectederialPort = this->ui->serialPorts->currentIndex();
    QSerialPortInfo selectedInfo =  this->serialList.at(selectederialPort);


    if (!this->serialPort.open(QIODevice::ReadWrite)) {
        this->ui->recvViewer->setHtml("<p style=\"color:'red'\">Failed to open port!</p>");
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

        serialPortReader.init(&this->serialPort,
                              std::bind(&SerialTool::onDataReceived,this,std::placeholders::_1),
                              std::bind(&SerialTool::onSerialError,this,std::placeholders::_1),
                              std::bind(&SerialTool::onTimeout,this,std::placeholders::_1));
        serialPortReader.conn(5000);

        this->ui->sendBtn->setEnabled(true);
    }
}

void SerialTool::on_buadList_activated(const QString &arg1)
{
    this->serialPort.setBaudRate(arg1.toInt());
}

void SerialTool::on_dataBits_activated(int index)
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
}

void SerialTool::on_checkBits_activated(int index)
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
}


void SerialTool::on_stopBits_activated(int index)
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
}

void SerialTool::on_connectionCloseBtn_clicked()
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

    this->ui->sendBtn->setEnabled(false);
}

void SerialTool::on_commandClearBtn_clicked()
{
    this->ui->command->clear();
}

void SerialTool::onDataReceived(QByteArray data)
{
    QTextCodec *tc = QTextCodec::codecForName("UTF8");
    QTextCursor cursor = this->ui->recvViewer->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(tc->toUnicode(data));
}

void SerialTool::onTimeout(int sec)
{
    QString str;
    str.append(QString(sec/1000));
    str.append(" seconds no data.");
    this->ui->recvViewer->append(str);
}

void SerialTool::onSerialError(QSerialPort::SerialPortError serialPortError)
{
    this->ui->recvViewer->append("error");
}

void SerialTool::on_sendBtn_clicked()
{
    QString text = this->ui->command->toPlainText();
    this->serialPortReader.send(text);
}

void SerialTool::on_recvClearBtn_clicked()
{
    this->ui->recvViewer->clear();
}
