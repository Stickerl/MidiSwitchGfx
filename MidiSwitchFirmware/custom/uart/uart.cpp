/*
 * uart.cpp
 *
 *  Created on: 17.08.2018
 *      Author: Erwin
 */

#include "uart.hpp"

UartIrqBased::UartIrqBased(uint32_t baud_rate, RingBuffer& tx_buffer, RingBuffer& rx_buffer):
    _tx_buffer(tx_buffer),
    _rx_buffer(rx_buffer)
{
    _uart_handle.Init.BaudRate = baud_rate;
    _uart_handle.Init.Parity = UART_PARITY_NONE;
    _uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    _uart_handle.Init.StopBits = UART_STOPBITS_1;
    init_uart();
}

UartIrqBased::UartIrqBased(uint32_t baud_rate, RingBuffer& tx_buffer, RingBuffer& rx_buffer,
                           uart_cfg config):
    _tx_buffer(tx_buffer),
    _rx_buffer(rx_buffer)
{
    switch(config.word_length)
    {
    case WORD_LENGTH_8:
        _uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
        break;
    case WORD_LENGTH_9:
        _uart_handle.Init.WordLength = UART_WORDLENGTH_9B;
        break;
    default:
        break;
    };

    switch(config.parity)
    {
    case PARITY_NONE:
        _uart_handle.Init.Parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        _uart_handle.Init.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        _uart_handle.Init.Parity = UART_PARITY_EVEN;
        break;
    default:
        break;
    };

    switch(config.stop_bit)
    {
    case STOP_BITS_1:
        _uart_handle.Init.StopBits = UART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        _uart_handle.Init.StopBits = UART_STOPBITS_2;
        break;
    default:
        break;
    };

    _uart_handle.Init.BaudRate = baud_rate;
    init_uart();
}
/*    ~UartIrqBased();
    void change_baud_rate(uint32_t baud_rate);
    void start_receive();
    void start_send();
    void stop_receive();
    void stop_send();
private:
    RingBuffer& _tx_buffer;
    RingBuffer& _rx_buffer;
    */
void UartIrqBased::init_uart()
{
    _uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    _uart_handle.Init.Mode = UART_MODE_TX_RX;
    _uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&_uart_handle);
}
