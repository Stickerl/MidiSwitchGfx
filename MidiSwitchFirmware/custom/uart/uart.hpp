/*
 * uart.hpp
 *
 *  Created on: 17.08.2018
 *      Author: Erwin
 */

#ifndef UART_UART_HPP_
#define UART_UART_HPP_

#include "I_ring_buffer.hpp"
#include "stm32f4xx_hal.h"
#include "I_uart.hpp"
#include "IREG_UartIrq.hpp"

class UartIrqBased : public I_UartIrqBased, public ICB_Uart
{
public:
    typedef enum
    {
        STOP_BITS_1 = 0,
        STOP_BITS_2 = 1
    }stop_bit_cfg;

    typedef enum
    {
        PARITY_NONE = 0,
        PARITY_ODD = 1,
        PARITY_EVEN = 2
    }parity_cfg;

    typedef struct {
        parity_cfg parity;
        stop_bit_cfg stop_bit;
    }uart_cfg;

    typedef struct init_struct_t {
        uint32_t baud_rate;
        I_RingBuffer& tx_buffer;
        I_RingBuffer& rx_buffer;
        IREG_UartIrq& irq_registry;
        init_struct_t(uint32_t baud_rate_in, I_RingBuffer& tx_buffer_in,
                      I_RingBuffer& rx_buffer_in, IREG_UartIrq& irq_registry_in):
            baud_rate(baud_rate_in),
            tx_buffer(tx_buffer_in),
            rx_buffer(rx_buffer_in),
            irq_registry(irq_registry_in){};
    }init_struct;

    UartIrqBased(init_struct std_init);
    UartIrqBased(init_struct std_init, uart_cfg config);
    ~UartIrqBased();
    void change_baud_rate(uint32_t baud_rate);
    void send(uint8_t* data, uint32_t cnt);
    void start_receive();
    void stop_receive();
    bool get_data(uint8_t* dest, uint32_t cnt);
    void uartInterrupt(); // override
    uint32_t get_rx_cnt();

private:
    I_RingBuffer& _tx_buffer;
    I_RingBuffer& _rx_buffer;
    UART_HandleTypeDef _uart_handle;
    void init_uart();
    void start_tx();
};



#endif /* UART_UART_HPP_ */
