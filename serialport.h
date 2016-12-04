#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QDebug>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();
    void setPortName(const QString &portName);
    bool open();
    bool isOpen();
    void close();
    void write(const QByteArray &data);

signals:
    void lineRead(QByteArray data);
    void connectionClosed(QSerialPort::SerialPortError e, const QString &stringError);

private slots:
    void on_serial_read();
    void on_serial_error(QSerialPort::SerialPortError error);

private:
    void plumbing();

    QSerialPort *serial;

};

#endif // SERIALPORT_H
