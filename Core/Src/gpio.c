#include "gpio.h"

#define GPIO_OFFSET 0x400UL


void GPIO_Config(IOPin p, int io_type)
{
    int shift_pin = p.pin * 2;
    volatile int gpio_rcc_register = (int) ((p.port - GPIOA) * sizeof(GPIO_TypeDef) / GPIO_OFFSET);
    // enable gpio clock
    RCC->AHB1ENR |= (1 << gpio_rcc_register);

    // set pin mode
    p.port->MODER &= ~(0b11 << shift_pin);
    p.port->MODER |= (io_type << shift_pin);

    if (io_type == GPIO_ALT_FUNCION) {
        p.port->AFR[(int) p.pin / 8] |= (p.alt_function << p.pin * 4);
    }

    // configure push pull
    p.port->OTYPER &= ~(1 << p.pin);
}


/*
    GPIO Function to write output
    Parameters: IOPin (Port, pin), value = PIN_HIGH / PIN_LOW
*/
void GPIO_WritePin(IOPin p, int value)
{
    if(value == PIN_HIGH)
        p.port->ODR |= (1 << (p.pin));
    else if (value == PIN_LOW)
        p.port->ODR &= ~(1 << (p.pin));
}