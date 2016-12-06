#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <QTimer>

#include "QDCController/qdcwidget.h"
#include "QDCController/qdcmodel.h"

#include "serialport.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onLineRead(QByteArray data);
    void onConnectionClosedSerialError(QSerialPort::SerialPortError e, const QString &stringError);
    void update_motor_driver();

    void on_action_Exit_triggered();

    void on_pushButtonConnect_clicked();

    void on_pushButtonReload_clicked();

private:
    void plumbing();
    void set_connection_state(bool state);
    void scan_for_serial_devices();

    Ui::MainWindow *ui;
    QComboBox *serialSelect;

    SerialPort *serial;
    bool isConnected {false};

    QDCWidget *motor1;
    QDCWidget *motor2;
    QDCWidget *motor3;

    QDCModel *model1;
    QDCModel *model2;
    QDCModel *model3;

    QList<QDCWidget *> motors;
    QList<QDCModel *> models;

    const int TIMER_INTERVAL {100};
    QTimer *timer;
};

#endif // MAINWINDOW_H
