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
    explicit SerialPortReader(QObject *parent = nullptr);

    void init(QSerialPort *serialPort,  std::function<void(QByteArray)> onDataHandler,
              std::function<void(QSerialPort::SerialPortError)> onErrorHandler,
              std::function<void(int)> onTimeHandler);

    void conn(int sec);

    void send(QString command);

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serialPort = nullptr;
    QByteArray readData;
    QTimer timer;

    int waitTime = 0;

    std::function<void(QByteArray)> onDataHandler;
    std::function<void(QSerialPort::SerialPortError)> onErrorHandler;
    std::function<void(int)> onTimeHandler;
};

#endif // SERIALPORTREADER_H
