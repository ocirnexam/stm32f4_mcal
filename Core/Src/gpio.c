#include "gpio.h"

#define GPIO_OFFSET 0x400UL


void GPIO_Config(IOPin p)
{
    int shift_pin = p.pin * 2;
    volatile int gpio_rcc_register = (int) ((p.port - GPIOA) * sizeof(GPIO_TypeDef) / GPIO_OFFSET);
    // enable gpio clock
    RCC->AHB1ENR |= (1 << gpio_rcc_register);

    // set pin mode
    p.port->MODER &= ~(0b11 << shift_pin);
    p.port->MODER |= (p.io_type << shift_pin);

    if (p.io_type == GPIO_ALT_FUNCION) {
        p.port->AFR[((int) p.pin / 8)] |= (p.alt_function << p.pin * 4);
    } else if (p.io_type == GPIO_ANALOG_MODE) {
        switch(p.alt_function) {
            case ADC1_IN0:
                RCC->APB2ENR |= 1 << 8;
                ADC1->CR2 |= 1; // Enable ADC1
                ADC1->CR2 |= 1 << 1; // Enable Continuous Conversion
                ADC1->CR2 |= 1 << 30; // Enable SWStart
                ADC1->SMPR2 |= 0b001 << 0; // Sample time of 15 cycles
                break;
            default:
                break;
        }
    }

    // configure push pull
    p.port->OTYPER &= ~(1 << p.pin);
    p.port->PUPDR |= 1;
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

uint8_t GPIO_ReadPin(IOPin p)
{
    return (p.port->IDR >> p.pin) & 1;
}

uint16_t GPIO_ReadAnalogPin(IOPin p)
{
    switch(p.alt_function)
    {
        case ADC1_IN0:
            return ADC1->DR;
            break;
        default:
            break;
    }
}