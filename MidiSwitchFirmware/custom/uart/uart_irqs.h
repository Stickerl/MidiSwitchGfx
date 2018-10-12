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
    static ICB_Uart* uart_obj_list[6U];
private:

};

#endif /* UART_UART_IRQS_H_ */
