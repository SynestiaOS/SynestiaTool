#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include <QDockWidget>
#include <QSerialPortInfo>
#include <QSerialPort>

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

private:
    Ui::SerialTool *ui;

    QList<QSerialPortInfo> serialList;

    QSerialPort serialPort;

    bool connectionState = false;

    void initUi();

    void initSerialPorts();

    void onDataReceived(QByteArray data);
    void onTimeout();
    void onSerialError(QSerialPort::SerialPortError serialPortError);

    void chanageConnectButtonState();
};

#endif // SERIALTOOL_H
