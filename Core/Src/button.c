#include "stm32f4xx.h"
#include "state_machine.h"

void button_init(void)
{
//    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
//    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
//    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//
//    GPIOC->MODER &= ~(3 << (13 * 2));
//    GPIOC->PUPDR &= ~(3 << (13 * 2));
//    GPIOC->PUPDR |=  (1 << (13 * 2));
//
//    GPIOB->MODER &= ~(3 << (3 * 2));
//    GPIOB->PUPDR &= ~(3 << (3 * 2));
//    GPIOB->PUPDR |=  (1 << (3 * 2));

    SYSCFG->EXTICR[3] &= ~(0xF << 4 * (13 - 12));
    SYSCFG->EXTICR[3] |=  (0x2 << 4 * (13 - 12));

    SYSCFG->EXTICR[0] &= ~(0xF << 4 * 3);
    SYSCFG->EXTICR[0] |=  (0x1 << 4 * 3);

    EXTI->IMR  |= (1 << 13) | (1 << 3);
    EXTI->FTSR |= (1 << 13) | (1 << 3);

    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(EXTI3_IRQn);
}
