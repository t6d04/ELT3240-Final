#include "stm32f4xx.h"
#include "i2c.h"

void i2c2_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

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

    I2C1->CR2 = 16;
    I2C1->CCR = 80;
    I2C1->TRISE = 17;
    I2C1->CR1 |= I2C_CR1_PE;
}

uint8_t i2c2_check_address(uint8_t address) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = address;

    while ((I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) == 0);

    if (I2C1->SR1 & I2C_SR1_ADDR) {
        (void)I2C1->SR1;
        (void)I2C1->SR2;
        I2C1->CR1 |= I2C_CR1_STOP;
        return 1;
    } else {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return 0;
    }
}
