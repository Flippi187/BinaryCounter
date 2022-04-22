#include <QHBoxLayout>
#include "counterwidget.h"
#include "config.h"

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent), m_count(0), m_timer(this), m_gpio(this)
{
    m_number = 0;
    setWindowTitle("BinaryCounter");
    resize(300, 200);
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);

    // QLCDNumber zur Anzeige des Zaehlerstandes dezimal:
    m_output = new QLCDNumber();
    layout->addWidget(m_output);
    m_output->display(m_number);

    connect(&m_timer, &QTimer::timeout, this, &CounterWidget::updateCounter);
    m_timer.start(T_UPDATE);
}

CounterWidget::~CounterWidget()
{

}

void CounterWidget::outputLEDS()
{
    for(int idx = 0; idx < 4; idx++) m_gpio.set(LEDS[idx], (m_number >> idx) & 1);
}

// Zaehlerstand im Widget und dual ueber LEDs anzeigen:
void CounterWidget::updateCounter()
{
    m_output->display(m_number);
    outputLEDS();

    if(m_gpio.isActivated(BUTTONS[2])) m_number = (m_number + 1) & 15;
    if(m_gpio.isActivated(BUTTONS[0])) m_number = (m_number - 1) & 15;
    if(m_gpio.isActivated(BUTTONS[1])) m_number = 0;

}


