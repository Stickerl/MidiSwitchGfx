/*
 * ICB_uart.hpp
 *
 *  Created on: 07.09.2018
 *      Author: Erwin
 */

#ifndef UART_ICB_UART_HPP_
#define UART_ICB_UART_HPP_

class ICB_Uart
{
public:
    ICB_Uart(){};
    virtual ~ICB_Uart(){};

    virtual void uartInterrupt();
};



#endif /* UART_ICB_UART_HPP_ */
