#include "gpio.h"

#define GPIO_OFFSET 0x0400UL

void GPIO_Config(GPIO_TypeDef *GPIO, int io_type, int pin, int gpionr)
{
    volatile int gpio_rcc_register = (int) ((GPIO - GPIOA) / GPIO_OFFSET);
    // enable gpioa clock
    RCC->AHB1ENR |= (1 << gpionr);

    // set pin as output
    GPIO->MODER &= ~(0b11 << pin);
    GPIO->MODER |= io_type << pin;

    // configure OUTPUT MODE
    GPIO->OTYPER = 0;
    GPIO->OSPEEDR = 0;
}


void GPIO_WritePin(GPIO_TypeDef *GPIO, int pin, int value)
{
    GPIO->BSRR |= (1 << (value + pin));
}