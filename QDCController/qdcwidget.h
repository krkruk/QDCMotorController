#ifndef QDCWIDGET_H
#define QDCWIDGET_H

#include <QWidget>
#include <cmath>


namespace Ui {
class QDCWidget;
}

class QDCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QDCWidget(QWidget *parent = 0);
    ~QDCWidget();
    int getPwmValue();
    void setGroupLabel(const QString &label);

signals:
    void emergencyClicked();
    void pwmValue(int value);

public slots:
    void setLeftLimitSwitchState(bool state);
    void setRightLimitSwitchState(bool state);
    void setPwmValue(int newValue);

private slots:
    void on_horizontalSliderPWMRegulator_valueChanged(int value);

    void on_pushButtonEmergencyStop_clicked();

private:
    Ui::QDCWidget *ui;

    const int maxSliderValue {400};

    const QString markStyle {"QLabel { color : red; }"};
    const QString defaultStyle {""};
    const QString stopMark {"STOP"};
    const QString defaultMark {"OK"};
};

#endif // QDCWIDGET_H
