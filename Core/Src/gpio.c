#include "gpio.h"

#define GPIO_OFFSET 0x400UL

void GPIO_Config(IOPin p, int io_type)
{
    p.pin *= 2;
    volatile int gpio_rcc_register = (int) ((p.port - GPIOA) * sizeof(GPIO_TypeDef) / GPIO_OFFSET);
    // enable gpioa clock
    RCC->AHB1ENR |= (1 << gpio_rcc_register);

    // set pin as output
    p.port->MODER &= ~(0b11 << p.pin);
    p.port->MODER |= io_type << p.pin;

    // configure OUTPUT MODE
    p.port->OTYPER = 0;
    p.port->OSPEEDR = 0;
}


void GPIO_WritePin(IOPin p, int value)
{
    p.port->BSRR |= (1 << (value + p.pin * 2));
}