#include "gpio.h"

#define GPIO_OFFSET 0x400UL

void GPIO_Config(GPIO_TypeDef *GPIO, int io_type, int pin)
{
    volatile int gpio_rcc_register = (int) ((GPIO - GPIOA) * sizeof(GPIO_TypeDef) / GPIO_OFFSET);
    // enable gpioa clock
    RCC->AHB1ENR |= (1 << gpio_rcc_register);

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