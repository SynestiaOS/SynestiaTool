#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H


#include <QByteArray>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QSerialPort *serialPort,  std::function<void(QByteArray)> onDataHandler,
                              std::function<void(QSerialPort::SerialPortError)> onErrorHandler,
                              std::function<void()> onTimeHandler, QObject *parent = nullptr);

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serialPort = nullptr;
    QByteArray readData;
    QTimer timer;

    std::function<void(QByteArray)> onDataHandler;
    std::function<void(QSerialPort::SerialPortError)> onErrorHandler;
    std::function<void()> onTimeHandler;
};

#endif // SERIALPORTREADER_H
