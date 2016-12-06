#ifndef QDCMODEL_H
#define QDCMODEL_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "QDCController/qdcmodelinterface.h"
#include "QDCController/qdcwidget.h"

class QDCModel : public QObject, public QDCModelInterface
{
    Q_OBJECT

public:
    QDCModel(const QString &leftLimitSwitchJson,
             const QString &rightLimitSwitchJson,
             const QString &pwmJson,
             const QString &haltJson,
             QDCWidget *dcController,
             QObject *parent=nullptr);
    ~QDCModel();

    void updateData(QByteArray data);


    QString getLeftLimitSwitchKey() const;

    QString getRightLimitSwitchKey() const;

    QString getPwmJsonKey() const;

private:
    void apply_parsed_data(bool leftSwitch, bool rightSwitch, int pwm);
    void apply_halt();


    const QString leftLimitSwitchKey;
    const QString rightLimitSwitchKey;
    const QString pwmJsonKey;
    const QString haltJsonKey;
    QDCWidget *dcController;

    enum class HALT {
        NO_HALT = 0,
        CLOCKWISE = 1,
        COUNTERCLOCKWISE = -1
    };
};

#endif // QDCMODEL_H
