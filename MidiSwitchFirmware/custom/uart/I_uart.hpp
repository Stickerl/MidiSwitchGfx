/*
 * I_uart.hpp
 *
 *  Created on: 26.08.2018
 *      Author: Erwin
 */

#ifndef UART_I_UART_HPP_
#define UART_I_UART_HPP_

#include "stdint.h"

class I_UartIrqBased{
public:
    I_UartIrqBased() {};
    virtual ~I_UartIrqBased(){};
    virtual void change_baud_rate(uint32_t baud_rate) = 0;
    virtual void send(uint8_t* data, uint32_t cnt) = 0;
    virtual void start_receive() = 0;
    virtual void stop_receive() = 0;
    virtual bool get_data(uint8_t* dest, uint32_t cnt) = 0;
    virtual uint32_t get_rx_cnt() = 0;
};

#endif /* UART_I_UART_HPP_ */
