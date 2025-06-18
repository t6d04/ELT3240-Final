#include "stm32f4xx.h"

void gpio_init(void)
{
    // Enable GPIO Clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // ===== MQ-5 Sensor: PA0 (Analog input) =====
    GPIOA->MODER &= ~(3 << (0 * 2));
    GPIOA->MODER |=  (0 << (0 * 2));

    // ===== Relay: PB12 (Output) =====
    GPIOB->MODER &= ~(3 << (12 * 2));
    GPIOB->MODER |=  (1 << (12 * 2));

    GPIOB->OTYPER &= ~(1 << 12);
    GPIOB->OSPEEDR |= (3 << (12 * 2));
    GPIOB->PUPDR &= ~(3 << (12 * 2));

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

    // ===== LCD I2C=====
    GPIOB->MODER &= ~(3 << (8 * 2));
    GPIOB->MODER |=  (2 << (8 * 2));
    GPIOB->AFR[1] &= ~(0xF << ((8 - 8) * 4));
    GPIOB->AFR[1] |=  (4 << ((8 - 8) * 4));
    GPIOB->OTYPER |= (1 << 8);
    GPIOB->PUPDR &= ~(3 << (8 * 2));
    GPIOB->PUPDR |=  (1 << (8 * 2));

    GPIOB->MODER &= ~(3 << (9 * 2));
    GPIOB->MODER |=  (2 << (9 * 2));
    GPIOB->AFR[1] &= ~(0xF << ((9 - 8) * 4));
    GPIOB->AFR[1] |=  (4 << ((9 - 8) * 4));
    GPIOB->OTYPER |= (1 << 9);
    GPIOB->PUPDR &= ~(3 << (9 * 2));
    GPIOB->PUPDR |=  (1 << (9 * 2));

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


    // ===== UART PA9 (Output) =====
    GPIOA->MODER &= ~(3 << (9 * 2));
    GPIOA->MODER |=  (2 << (9 * 2));
    GPIOA->AFR[1] &= ~(0xF << ((9 - 8) * 4));
    GPIOA->AFR[1] |=  (7 << ((9 - 8) * 4));

}
