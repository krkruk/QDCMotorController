#include "qdcmodel.h"
#include <QDebug>

QDCModel::QDCModel(const QString &leftLimitSwitchJson,
                   const QString &rightLimitSwitchJson, const QString &pwmJson,
                   QDCWidget *dcController,
                   QObject *parent)
    : QObject(parent),
      leftLimitSwitchKey(leftLimitSwitchJson),
      rightLimitSwitchKey(rightLimitSwitchJson),
      pwmJsonKey(pwmJson),
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
    const bool leftLimitSwitchState = (bool)jsonObj.value(leftLimitSwitchKey).toInt();
    const bool rightLimitSwitchState = (bool)jsonObj.value(rightLimitSwitchKey).toInt();
    const int pwmValue = jsonObj.value(pwmJsonKey).toInt();

    qDebug() << jsonDoc;

    apply_parsed_data(leftLimitSwitchState, rightLimitSwitchState, pwmValue);
}

void QDCModel::apply_parsed_data(bool leftSwitch, bool rightSwitch, int pwm)
{
    (*dcController).setLeftLimitSwitchState(leftSwitch);
    (*dcController).setRightLimitSwitchState(rightSwitch);
    (*dcController).setPwmValue(pwm);
}

QString QDCModel::getPwmJsonKey() const
{
    return pwmJsonKey;
}

QString QDCModel::getRightLimitSwitchKey() const
{
    return rightLimitSwitchKey;
}

QString QDCModel::getLeftLimitSwitchKey() const
{
    return leftLimitSwitchKey;
}
