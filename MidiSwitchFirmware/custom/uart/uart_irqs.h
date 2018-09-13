/*
 * uart_irqs.h
 *
 *  Created on: 07.09.2018
 *      Author: Erwin
 */

#ifndef UART_UART_IRQS_H_
#define UART_UART_IRQS_H_

#include "stdint.h"
#include "stddef.h"
#include "assert.h"
#include "ICB_uart.hpp"
#include "IREG_UartIrq.hpp"

class UartIrqs:public IREG_UartIrq{
public:
    UartIrqs();
    virtual ~UartIrqs();
    void register_obj(ICB_Uart* obj, uint8_t index);
    static void usart1_irq_handler();
    static void usart2_irq_handler();
    static void usart3_irq_handler();
    static void uart4_irq_handler();
    static void uart5_irq_handler();
    static ICB_Uart* uart_obj_list[5U];
private:

};

#endif /* UART_UART_IRQS_H_ */
