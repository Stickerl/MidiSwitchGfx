/*
 * uart_irqs.cpp
 *
 *  Created on: 07.09.2018
 *      Author: Erwin
 */

#include "uart_irqs.h"


UartIrqs::UartIrqs():
    uart_obj_list({NULL})
{


}

UartIrqs::~UartIrqs() {

}

void UartIrqs::register_obj(ICB_Uart* obj, uint8_t index)
{
    assert((index > 0) && (index <= 5U));
    assert(uart_obj_list[index - 1U] == NULL);
    uart_obj_list[index - 1U] = obj;
}
void UartIrqs::usart1_irq_handler()
{
    uart_obj_list[0]->uartInterrupt();
}
void UartIrqs::usart2_irq_handler()
{
    uart_obj_list[1]->uartInterrupt();
}
void UartIrqs::usart3_irq_handler()
{
    uart_obj_list[2]->uartInterrupt();
}
void UartIrqs::uart4_irq_handler()
{
    uart_obj_list[3]->uartInterrupt();
}
void UartIrqs::uart5_irq_handler()
{
    uart_obj_list[4]->uartInterrupt();
}

#ifdef __cplusplus
 extern "C" {
#endif

void USART1_IRQHandler(void)
{
    UartIrqs::usart1_irq_handler();
}

void USART2_IRQHandler(void)
{
    UartIrqs::usart2_irq_handler();
}

void USART3_IRQHandler(void)
{
    UartIrqs::usart3_irq_handler();
}

void UART4_IRQHandler(void)
{
    UartIrqs::uart4_irq_handler();
}

void UART5_IRQHandler(void)
{
    UartIrqs::uart5_irq_handler()
}

#ifdef __cplusplus
}
#endif
