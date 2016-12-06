#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialSelect = ui->comboBoxSerialSelect;

    serial = new SerialPort(this);


    motor1 = new QDCWidget(this);
    motor2 = new QDCWidget(this);
    motor3 = new QDCWidget(this);

    model1 = new QDCModel("m1ls", "m1rs", "mot1", "h1", motor1, this);
    model2 = new QDCModel("m2ls", "m2rs", "mot2", "h2", motor2, this);
    model3 = new QDCModel("m3ls", "m3rs", "mot3", "h3", motor3, this);

    timer = new QTimer(this);
    timer->setInterval(TIMER_INTERVAL);

    motors.append(motor1);
    motors.append(motor2);
    motors.append(motor3);

    models.append(model1);
    models.append(model2);
    models.append(model3);

    ui->verticalLayout->addWidget(motor1);
    ui->verticalLayout->addWidget(motor2);
    ui->verticalLayout->addWidget(motor3);

    motor1->setGroupLabel("Motor1");

    scan_for_serial_devices();
    plumbing();
}

MainWindow::~MainWindow()
{
    delete timer;

    models.clear();

    if(serial->isOpen()) {
        serial->close();
    }
    delete serial;

    delete motor3;
    delete motor2;
    delete motor1;
    delete ui;
}

void MainWindow::onLineRead(QByteArray data)
{
    for(auto model : models)
        model->updateData(data);
}

void MainWindow::onConnectionClosedSerialError(QSerialPort::SerialPortError e, const QString &stringError)
{
    qDebug() << e << stringError;
    set_connection_state(false);
    scan_for_serial_devices();
}

void MainWindow::update_motor_driver()
{
    const int mot1 = motor1->getPwmValue();
    const int mot2 = motor2->getPwmValue();
    const int mot3 = motor3->getPwmValue();

    const auto cmd = QString(R"({"mot1":%1,"mot2":%2,"mot3":%3})").arg(mot1)
            .arg(mot2).arg(mot3);
    const auto dataCmd = cmd.toLatin1();

    serial->write(dataCmd + "\n");
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_pushButtonConnect_clicked()
{
    if(!isConnected)
    {
        auto portName = serialSelect->currentText();
        serial->setPortName(portName);

        if(serial->open())
            set_connection_state(true);
    }
    else
    {
        set_connection_state(false);
        serial->close();
    }
}

void MainWindow::on_pushButtonReload_clicked()
{
    if(isConnected) return;

    scan_for_serial_devices();
}

void MainWindow::plumbing()
{
    connect(serial, SIGNAL(lineRead(QByteArray)), this, SLOT(onLineRead(QByteArray)));
    connect(serial, SIGNAL(connectionClosed(QSerialPort::SerialPortError,QString)), this, SLOT(onConnectionClosedSerialError(QSerialPort::SerialPortError,QString)));

    connect(timer, SIGNAL(timeout()), this, SLOT(update_motor_driver()));
}

void MainWindow::set_connection_state(bool state)
{
    isConnected = state;

    if(state)
    {
        ui->pushButtonConnect->setText("Disco&nnect");
        ui->pushButtonReload->setEnabled(false);
        QTimer::singleShot(2000, this, [&](){timer->start();});
    }
    else
    {
        ui->pushButtonConnect->setText("Co&nnect");
        ui->pushButtonReload->setEnabled(true);
        for( auto dcWidget : motors )
            dcWidget->setDefaultView();

        timer->stop();
    }
}

void MainWindow::scan_for_serial_devices()
{
    serialSelect->clear();
    for(auto port : QSerialPortInfo::availablePorts())
        serialSelect->addItem(port.portName());
}
