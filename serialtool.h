#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include <QDockWidget>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <SerialPortReader.h>

namespace Ui {
class SerialTool;
}

class SerialTool : public QDockWidget
{
    Q_OBJECT

public:
    explicit SerialTool(QWidget *parent = nullptr);
    ~SerialTool();

private slots:
    void on_connectionRefreshBtn_clicked();

    void on_serialPorts_activated(int index);

    void on_connectionConnectBtn_clicked();

    void on_buadList_activated(const QString &arg1);

    void on_dataBits_activated(int index);

    void on_checkBits_activated(int index);

    void on_stopBits_activated(int index);

    void on_connectionCloseBtn_clicked();

    void on_commandClearBtn_clicked();

    void on_sendBtn_clicked();

    void on_recvClearBtn_clicked();

private:
    Ui::SerialTool *ui;

    QList<QSerialPortInfo> serialList;

    QSerialPort serialPort;

    SerialPortReader serialPortReader;

    bool connectionState = false;

    void initUi();

    void initSerialPorts();

    void onDataReceived(QByteArray data);
    void onTimeout(int sec);
    void onSerialError(QSerialPort::SerialPortError serialPortError);

    void chanageConnectButtonState();
};

#endif // SERIALTOOL_H
