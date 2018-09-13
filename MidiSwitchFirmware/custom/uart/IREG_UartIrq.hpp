/*
 * IREG_UartIrq.hpp
 *
 *  Created on: 07.09.2018
 *      Author: Erwin
 */

#ifndef UART_IREG_UARTIRQ_HPP_
#define UART_IREG_UARTIRQ_HPP_
#include "ICB_uart.hpp"
#include "stdint.h"

class IREG_UartIrq
{
public:
    IREG_UartIrq(){};
    virtual ~IREG_UartIrq(){};
    virtual void register_obj(ICB_Uart* obj, uint8_t index) = 0;
};



#endif /* UART_IREG_UARTIRQ_HPP_ */
