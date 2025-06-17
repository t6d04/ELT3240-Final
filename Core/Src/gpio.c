#include "stm32f4xx.h"

void gpio_init(void)
{
    // Enable GPIO Clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // ===== MQ-5 Sensor: PA0 (Analog input) =====
    GPIOA->MODER &= ~(3 << (0 * 2));
    GPIOA->MODER |=  (0 << (0 * 2));

    // ===== Relay: PA8 (Output) =====
    GPIOA->MODER &= ~(3 << (8 * 2));
    GPIOA->MODER |=  (1 << (8 * 2));
    GPIOA->OTYPER &= ~(1 << 8);
    GPIOA->OSPEEDR |= (3 << (8 * 2));

    // ===== LED1: PB0 (Output) =====
    GPIOB->MODER &= ~(3 << (0 * 2));
    GPIOB->MODER |=  (1 << (0 * 2));
    GPIOB->OTYPER &= ~(1 << 0);

    // ===== LED2: PB1 (Output) =====
    GPIOB->MODER &= ~(3 << (1 * 2));
    GPIOB->MODER |=  (1 << (1 * 2));
    GPIOB->OTYPER &= ~(1 << 1);

    // ===== SW2: PB3 (Input, Pull-up) =====
    GPIOB->MODER &= ~(3 << (3 * 2));
    GPIOB->PUPDR &= ~(3 << (3 * 2));
    GPIOB->PUPDR |=  (1 << (3 * 2));

    // ===== LCD I2C: PB6 (SCL), PB7 (SDA), AF4, Open-drain =====
    GPIOB->MODER &= ~(3 << (6 * 2));
    GPIOB->MODER |=  (2 << (6 * 2));
    GPIOB->OTYPER |=  (1 << 6);
    GPIOB->PUPDR |=  (1 << (6 * 2));

    GPIOB->MODER &= ~(3 << (7 * 2));
    GPIOB->MODER |=  (2 << (7 * 2));
    GPIOB->OTYPER |=  (1 << 7);
    GPIOB->PUPDR |=  (1 << (7 * 2));

    // ===== Buzzer: PB10 (Output) =====
    GPIOB->MODER &= ~(3 << (10 * 2));
    GPIOB->MODER |=  (1 << (10 * 2));
    GPIOB->OTYPER &= ~(1 << 10);

    // ===== LED Xanh lá: PC0 (Output) =====
    GPIOC->MODER &= ~(3 << (0 * 2));
    GPIOC->MODER |=  (1 << (0 * 2));

    // ===== LED Xanh dương: PC1 (Output) =====
    GPIOC->MODER &= ~(3 << (1 * 2));
    GPIOC->MODER |=  (1 << (1 * 2));

    // ===== LED Vàng: PC2 (Output) =====
    GPIOC->MODER &= ~(3 << (2 * 2));
    GPIOC->MODER |=  (1 << (2 * 2));

    // ===== LED Đỏ: PC3 (Output) =====
    GPIOC->MODER &= ~(3 << (3 * 2));
    GPIOC->MODER |=  (1 << (3 * 2));

    // ===== SW1: PC13 (Input, Pull-up) =====
    GPIOC->MODER &= ~(3 << (13 * 2));
    GPIOC->PUPDR &= ~(3 << (13 * 2));
    GPIOC->PUPDR |=  (1 << (13 * 2));
}
