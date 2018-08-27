/*
 * uart.cpp
 *
 *  Created on: 17.08.2018
 *      Author: Erwin
 */

#include "uart.hpp"

UartIrqBased::UartIrqBased(uint32_t baud_rate, I_RingBuffer& tx_buffer, I_RingBuffer& rx_buffer):
    _tx_buffer(tx_buffer),
    _rx_buffer(rx_buffer)
{
    switch
    _uart_handle = &uart1_handle;
    _uart_handle.Init.BaudRate = baud_rate;
    _uart_handle.Init.Parity = UART_PARITY_NONE;
    _uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    _uart_handle.Init.StopBits = UART_STOPBITS_1;
    init_uart();
}

UartIrqBased::UartIrqBased(uint32_t baud_rate, I_RingBuffer& tx_buffer, I_RingBuffer& rx_buffer,
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
void UartIrqBased::change_baud_rate(uint32_t baud_rate);

// write data to tx buffer and trigger transmission
void UartIrqBased::send(uint8_t* data, uint32_t cnt)
{
    _tx_buffer.copy_to_buffer(data, cnt);
    start_tx();
}
void UartIrqBased::start_receive();
void UartIrqBased::stop_receive();

// Copy received bytes from buffer to destination
// returns false if #bytes available < cnt
bool UartIrqBased::get_data(uint8_t* dest, uint32_t cnt)
{
    return _rx_buffer.get_from_buffer(dest, cnt);
}

// get remaining bytes in rx buffer
uint32_t UartIrqBased::get_rx_cnt()
{
    return _rx_buffer.get_cnt();
}

void UartIrqBased::init_uart()
{
    _uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    _uart_handle.Init.Mode = UART_MODE_TX_RX;
    _uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&_uart_handle);
}

void UartIrqBased::start_tx()
{

}
