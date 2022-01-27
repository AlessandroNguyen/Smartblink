#include "gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    m_state = 0;
    m_LEDs = new Gpio(this);
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Gui::toggle);
    m_timer->start(TIMEOUT);
}

void Gui::on_blinkButton_clicked()
{
    m_modus = 1;
}
void Gui::on_lauflichtButton_clicked()
{
    m_modus = 0;
    counter = 1;
}

void Gui::on_speedSlider_valueChanged(int value)
{
    m_timer->start(1000/value);
}

void Gui::toggle()
{
    m_state = !m_state;
    if(m_modus == 1)
    {
        if(m_state == 1)
        {
            counter = 15;
        }else {
            counter = 0;
        }
        m_LEDs->set(counter);
    }
    if(m_modus == 0)
    {
        m_LEDs->set(counter);

            if(counter < 8)
            {
                counter = counter * 2;
            }
            else counter = 1;
    }
}

