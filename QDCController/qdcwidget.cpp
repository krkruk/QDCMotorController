#include "qdcwidget.h"
#include "ui_qdcwidget.h"
#include <QDebug>

QDCWidget::QDCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDCWidget)
{
    ui->setupUi(this);
}

QDCWidget::~QDCWidget()
{
    delete ui;
}

int QDCWidget::getPwmValue()
{
    return ui->horizontalSliderPWMRegulator->value();
}

void QDCWidget::setGroupLabel(const QString &label)
{
    ui->groupBoxMotorController->setTitle(label);
}

void QDCWidget::setDefaultView()
{
    setLeftLimitSwitchState(false);
    setRightLimitSwitchState(false);
    emergencyHalt();
}

void QDCWidget::setLeftLimitSwitchState(bool state)
{
    auto &style = state ? markStyle : defaultStyle;
    auto &mark = state ? stopMark : defaultMark;
    ui->labelLeftLimitSwitch->setStyleSheet(style);
    ui->labelLeftLimitSwitch->setText(mark);
}

void QDCWidget::setRightLimitSwitchState(bool state)
{
    auto &style = state ? markStyle : defaultStyle;
    auto &mark = state ? stopMark : defaultMark;
    ui->labelRightLimitSwitch->setStyleSheet(style);
    ui->labelRightLimitSwitch->setText(mark);
}

void QDCWidget::setPwmValue(int newValue)
{
    float fvalue = 100.0f * newValue / maxSliderValue;

    ui->lineEditPWMValue->setText(QString("%1%").arg(fvalue));
}

void QDCWidget::emergencyHalt()
{
    constexpr int STOP_VALUE = 0;
    setPwmValue(STOP_VALUE);
    ui->horizontalSliderPWMRegulator->setValue(STOP_VALUE);
}

void QDCWidget::on_horizontalSliderPWMRegulator_valueChanged(int value)
{
    setPwmValue(value);
    emit pwmValue(value);
}

void QDCWidget::on_pushButtonEmergencyStop_clicked()
{
    emergencyHalt();

    emit emergencyClicked();
}
