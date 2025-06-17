#ifndef __UART_H
#define __UART_H

void uart1_init(void);
void uart1_send_char(char c);
void uart1_send_string(const char* str);

#endif
