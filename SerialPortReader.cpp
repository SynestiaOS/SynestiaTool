#include "SerialPortReader.h"

#include <QCoreApplication>

SerialPortReader::SerialPortReader(QObject *parent) :
    QObject(parent){

}

void SerialPortReader::init(QSerialPort *serialPort, std::function<void (QByteArray)> onDataHandler, std::function<void (QSerialPort::SerialPortError)> onErrorHandler, std::function<void (int)> onTimeHandler)
{
    this->serialPort = serialPort;
    this->onDataHandler = onDataHandler;
    this->onErrorHandler = onErrorHandler;
    this->onTimeHandler = onTimeHandler;
}

void SerialPortReader::conn(int sec)
{
    connect(this->serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
    connect(this->serialPort, &QSerialPort::errorOccurred, this, &SerialPortReader::handleError);
    connect(&this->timer, &QTimer::timeout, this, &SerialPortReader::handleTimeout);
    this->waitTime = sec;
    this->timer.start(sec);
}

void SerialPortReader::send(QString command)
{
    serialPort->write(command.toUtf8());
}

void SerialPortReader::handleReadyRead()
{
    QByteArray dd =  serialPort->readAll();
    readData.append(dd);
    this->onDataHandler(dd);

    if (!timer.isActive()){
        timer.start(this->waitTime);
    }
}

void SerialPortReader::handleTimeout()
{
//   this->onTimeHandler(this->waitTime);
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    this->onErrorHandler(serialPortError);
}
