#include "gpio.h"

#include <lgpio.h>

Gpio::Gpio(QObject *parent) : QObject(parent)
{
    m_handle = lgGpiochipOpen(0);
    int init_lvl = 0;
    for(int pin : LEDS)
        lgGpioClaimOutput(m_handle, LFLAGS, pin, init_lvl);
}

Gpio::~Gpio()
{
    int init_lvl = 0;
    for(int pin : LEDS)
        lgGpioWrite(m_handle, pin, init_lvl);

    lgGpiochipClose(m_handle);
}

void Gpio::set(int pin,bool value)
{
    lgGpioWrite(m_handle, pin, value);
}

void Gpio::set(unsigned int pattern)
{
    int n = 0;
    bool value;
    unsigned int check = 0b0001;
    for(auto pin : LEDS)
    {
        value = check & pattern>>n;
        lgGpioWrite(m_handle, pin, value);
        n++;
    }
}
