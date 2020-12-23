#include "SerialPortReader.h"

#include <QCoreApplication>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, std::function<void(QByteArray)> onDataHandler,
                                   std::function<void(QSerialPort::SerialPortError)> onErrorHandler,
                                   std::function<void()> onTimeHandler, QObject *parent) :
    QObject(parent),
    serialPort(serialPort),
    onDataHandler(onDataHandler),
    onErrorHandler(onErrorHandler),
    onTimeHandler(onTimeHandler)
{
    connect(serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
    connect(serialPort, &QSerialPort::errorOccurred, this, &SerialPortReader::handleError);
    connect(&timer, &QTimer::timeout, this, &SerialPortReader::handleTimeout);

    timer.start(5000);
}

void SerialPortReader::handleReadyRead()
{
    QByteArray dd =  serialPort->readAll();
    readData.append(dd);
    this->onDataHandler(dd);

    if (!timer.isActive()){
        timer.start(5000);
    }
}

void SerialPortReader::handleTimeout()
{
    if (readData.isEmpty()) {
        this->onTimeHandler();
    } else {
        this->onDataHandler(readData);
    }
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    this->onErrorHandler(serialPortError);
}
