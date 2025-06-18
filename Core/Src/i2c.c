#include "stm32f4xx.h"
#include "i2c.h"

void i2c2_init(void) {
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
