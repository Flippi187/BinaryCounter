#ifndef COUNTERWIDGET_H
#define COUNTERWIDGET_H

#include <QLCDNumber>
#include <QLabel>
#include <QTimer>
#include "gpio.h"

class CounterWidget : public QWidget
{
    Q_OBJECT

public:
    CounterWidget(QWidget *parent = nullptr);
    ~CounterWidget();
    void outputLEDS();

public slots:
    void updateCounter();

private:
     int m_count;
     int m_number;
     QTimer m_timer;
     Gpio m_gpio;
     QLCDNumber* m_output;
};

#endif // COUNTERWIDGET_H
