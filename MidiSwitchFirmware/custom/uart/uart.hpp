/*
 * uart.hpp
 *
 *  Created on: 17.08.2018
 *      Author: Erwin
 */

#ifndef UART_UART_HPP_
#define UART_UART_HPP_

#include <gpio_helper_functions.hpp>
#include "I_ring_buffer.hpp"
#include "stm32f4xx_hal.h"
#include "I_uart.hpp"
#include "IREG_UartIrq.hpp"
#include "assert.h"

class UartIrqBased : public I_UartIrqBased, public ICB_Uart
{
public:
    typedef enum
    {
        STOP_BITS_1 = 0,
        STOP_BITS_2 = 1
    }StopBitCfg;

    typedef enum
    {
        PARITY_NONE = 0,
        PARITY_ODD = 1,
        PARITY_EVEN = 2
    }ParityCfg;

    typedef enum
    {
        UART_1 = 1,
        UART_2 = 2,
        UART_3 = 3,
        UART_4 = 4,
        UART_5 = 5,
        UART_6 = 6,
        UART_7 = 7,
        UART_8 = 8,
    }UartModuleEnum;

    typedef struct pin_t{
        GPIO_TypeDef* port;
        uint16_t pin_nr;
        uint32_t alternate;

       pin_t(GPIO_TypeDef* port_in, uint16_t pin_nr_in, uint32_t alternate_in):
            port(port_in),
            pin_nr(pin_nr_in),
            alternate(alternate_in){};
    }Pin;

    typedef struct {
        ParityCfg parity;
        StopBitCfg stop_bit;
    }UartCfg;

    typedef struct init_struct_t {
        uint32_t baud_rate;
        I_RingBuffer& tx_buffer;
        I_RingBuffer& rx_buffer;
        UartModuleEnum uart_module;
        Pin tx_pin;
        Pin rx_pin;
        IREG_UartIrq& irq_registry;

        init_struct_t(uint32_t baud_rate_in, I_RingBuffer& tx_buffer_in,
                      I_RingBuffer& rx_buffer_in, UartModuleEnum uart_module,
                      Pin tx_pin, Pin rx_pin, IREG_UartIrq& irq_registry_in):
            baud_rate(baud_rate_in),
            tx_buffer(tx_buffer_in),
            rx_buffer(rx_buffer_in),
            uart_module(uart_module),
            tx_pin(tx_pin),
            rx_pin(rx_pin),
            irq_registry(irq_registry_in){};
    }InitStruct;

    UartIrqBased(InitStruct std_init);
    UartIrqBased(InitStruct std_init, UartCfg config);
    ~UartIrqBased();
    void change_baud_rate(uint32_t baud_rate); // override
    void send(uint8_t* data, uint32_t cnt); // override
    void start_receive(); // override
    void stop_receive(); // override
    void start_tx(); // override
    bool get_data(uint8_t* dest, uint32_t cnt); // override
    void uartInterrupt(); // override
    uint32_t get_rx_cnt(); // override

private:
    I_RingBuffer& _tx_buffer;
    I_RingBuffer& _rx_buffer;
    UART_HandleTypeDef _uart_handle;
    IREG_UartIrq& _irq_registry;
    void init_uart(UartModuleEnum uart_module);
    void pin_init(UartModuleEnum uart_module, Pin tx_pin, Pin rx_pin);
};

#endif /* UART_UART_HPP_ */
