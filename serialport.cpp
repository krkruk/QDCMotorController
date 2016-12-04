#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
{
    serial = new QSerialPort(this);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    plumbing();
}

void SerialPort::setPortName(const QString &portName)
{
    if(serial)
        serial->setPortName(portName);
}

bool SerialPort::open()
{
    if(serial->isOpen()) return false;

    return serial->open(QSerialPort::ReadWrite);
}

bool SerialPort::isOpen()
{
    return serial->isOpen();
}

void SerialPort::close()
{
    if(serial->isOpen()) serial->close();
}

void SerialPort::write(const QByteArray &data)
{
    if(serial->isOpen())
        serial->write(data);
}

void SerialPort::on_serial_read()
{
    if(serial->canReadLine())
    {
        auto data = serial->readLine();
        emit lineRead(data);
    }
}

void SerialPort::on_serial_error(QSerialPort::SerialPortError error)
{
    switch(error)
    {
    case QSerialPort::NoError: break;
    default:
        if(serial->isOpen()) serial->close();
        emit connectionClosed(error, serial->errorString());
        break;
    }
}

void SerialPort::plumbing()
{
    connect(serial, SIGNAL(readyRead()), this, SLOT(on_serial_read()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(on_serial_error(QSerialPort::SerialPortError)));
}

SerialPort::~SerialPort()
{
    if(serial->isOpen()) serial->close();
    delete serial;
}
