#include "qdcmodel.h"
#include <QDebug>

QDCModel::QDCModel(const QString &pwmJson,
                   const QString &haltJson,
                   const QString &currentJson,
                   QDCWidget *dcController,
                   QObject *parent)
    : QObject(parent),
      pwmJsonKey(pwmJson),
      haltJsonKey(haltJson),
      currentJsonKey(currentJson),
      dcController(dcController)
{

}

QDCModel::~QDCModel()
{
}

void QDCModel::updateData(QByteArray data)
{
    const auto jsonDoc = QJsonDocument::fromJson(data);
    const auto jsonObj = jsonDoc.object();
    const int pwmValue = jsonObj.value(pwmJsonKey).toInt();
    const int haltState = jsonObj.value(haltJsonKey).toInt();
    const int mampsCurrent = jsonObj.value(currentJsonKey).toInt();

    bool leftLimitSwitchState = false;
    bool rightLimitSwitchState = false;
    switch(haltState)
    {
    case static_cast<int>(HALT::CLOCKWISE):
        rightLimitSwitchState = true;
        break;
    case static_cast<int>(HALT::COUNTERCLOCKWISE):
        leftLimitSwitchState = true;
        break;
    case static_cast<int>(HALT::WTF):
        leftLimitSwitchState = true;
        rightLimitSwitchState = true;
        break;
    default:
        break;
    }

    qDebug() << jsonDoc;

    apply_parsed_data(leftLimitSwitchState, rightLimitSwitchState, pwmValue);
    dcController->setCurrent(mampsCurrent);

    if(haltState != static_cast<int>(HALT::NO_HALT))
        apply_halt();
}

void QDCModel::apply_parsed_data(bool leftSwitch, bool rightSwitch, int pwm)
{
    dcController->setLeftLimitSwitchState(leftSwitch);
    dcController->setRightLimitSwitchState(rightSwitch);
    dcController->setPwmValue(pwm);
}

void QDCModel::apply_halt()
{
    dcController->emergencyHalt();
}

QString QDCModel::getHaltJsonKey() const
{
    return haltJsonKey;
}

QString QDCModel::getPwmJsonKey() const
{
    return pwmJsonKey;
}
