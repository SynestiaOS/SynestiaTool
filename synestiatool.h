#ifndef SYNESTIATOOL_H
#define SYNESTIATOOL_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class SynestiaTool; }
QT_END_NAMESPACE

class SynestiaTool : public QMainWindow
{
    Q_OBJECT

public:
    SynestiaTool(QWidget *parent = nullptr);
    ~SynestiaTool();

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
    Ui::SynestiaTool *ui;

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
#endif // SYNESTIATOOL_H
