#include "stm32f4xx.h"
#include "uart.h"

void uart1_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    USART1->BRR = 0x0683;
    USART1->CR1 = USART_CR1_TE | USART_CR1_UE;
}

void uart1_send_char(char c) {
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void uart1_send_string(const char* str) {
    while (*str) {
        uart1_send_char(*str++);
    }
}
