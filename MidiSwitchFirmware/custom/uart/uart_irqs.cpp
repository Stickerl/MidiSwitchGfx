/*
 * uart_irqs.cpp
 *
 *  Created on: 07.09.2018
 *      Author: Erwin
 */

#include "uart_irqs.h"

ICB_Uart* UartIrqs::uart_obj_list[5U] = {NULL};

UartIrqs::UartIrqs()
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

#ifdef __cplusplus
 extern "C" {
#endif

void USART1_IRQHandler(void)
{
    assert(UartIrqs::uart_obj_list[0] != NULL);
    UartIrqs::uart_obj_list[0]->uartInterrupt();
}

void USART2_IRQHandler(void)
{
    assert(UartIrqs::uart_obj_list[1] != NULL);
        UartIrqs::uart_obj_list[1]->uartInterrupt();
}

void USART3_IRQHandler(void)
{
    assert(UartIrqs::uart_obj_list[2] != NULL);
        UartIrqs::uart_obj_list[2]->uartInterrupt();
}

void UART4_IRQHandler(void)
{
    assert(UartIrqs::uart_obj_list[3] != NULL);
        UartIrqs::uart_obj_list[3]->uartInterrupt();
}

void UART5_IRQHandler(void)
{
    assert(UartIrqs::uart_obj_list[4] != NULL);
        UartIrqs::uart_obj_list[4]->uartInterrupt();
}

#ifdef __cplusplus
}
#endif
