/*
 * uart.cpp
 *
 *  Created on: 17.08.2018
 *      Author: Erwin
 */

#include "uart.hpp"

UartIrqBased::UartIrqBased(init_struct std_init):
    _tx_buffer(std_init.tx_buffer),
    _rx_buffer(std_init.rx_buffer)
{
    _uart_handle.Init.BaudRate = std_init.baud_rate;
    _uart_handle.Init.Parity = UART_PARITY_NONE;
    _uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    _uart_handle.Init.StopBits = UART_STOPBITS_1;
    init_uart();
}

UartIrqBased::UartIrqBased(init_struct std_init, uart_cfg config):
    _tx_buffer(std_init.tx_buffer),
    _rx_buffer(std_init.rx_buffer)
{

    _uart_handle.Init.WordLength = UART_WORDLENGTH_8B;

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

    _uart_handle.Init.BaudRate = std_init.baud_rate;
    init_uart();
}

UartIrqBased::~UartIrqBased()
{

}

void UartIrqBased::change_baud_rate(uint32_t baud_rate)
{

}

// write data to tx buffer and trigger transmission
void UartIrqBased::send(uint8_t* data, uint32_t cnt)
{
    _tx_buffer.copy_to_buffer(data, cnt);
    start_tx();
}

void UartIrqBased::start_receive()
{

}

void UartIrqBased::stop_receive()
{

}

// Copy received bytes from buffer to destination
// returns false if #bytes available < cnt
bool UartIrqBased::get_data(uint8_t* dest, uint32_t cnt)
{
    return _rx_buffer.get_from_buffer(dest, cnt);
}

void UartIrqBased::uartInterrupt()
{
    /**
      * @brief  This function handles UART interrupt request.
      * @param  huart: pointer to a UART_HandleTypeDef structure that contains
      *                the configuration information for the specified UART module.
      * @retval None
      */
    uint32_t flag = 0, irq_match = 0;

    flag      = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_PE);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_PE);
    /* UART parity error (PE) interrupt occurred ------------------------------------*/
    if((flag != RESET) && (irq_match != RESET))
    {
    __HAL_UART_CLEAR_PEFLAG(&_uart_handle);

    _uart_handle.ErrorCode |= HAL_UART_ERROR_PE;
    }

    flag = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_FE);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_ERR);
    /* UART frame error (FE) interrupt occurred -------------------------------------*/
    if((flag != RESET) && (irq_match != RESET))
    {
    __HAL_UART_CLEAR_FEFLAG(&_uart_handle);

    _uart_handle.ErrorCode |= HAL_UART_ERROR_FE;
    }

    flag = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_NE);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_ERR);
    /* UART noise error interrupt occurred -------------------------------------*/
    if((flag != RESET) && (irq_match != RESET))
    {
    __HAL_UART_CLEAR_NEFLAG(&_uart_handle);

    _uart_handle.ErrorCode |= HAL_UART_ERROR_NE;
    }

    flag = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_ORE);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_ERR);
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if((flag != RESET) && (irq_match != RESET))
    {
    __HAL_UART_CLEAR_OREFLAG(&_uart_handle);

    _uart_handle.ErrorCode |= HAL_UART_ERROR_ORE;
    }

    flag = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_RXNE);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_RXNE);
    /* UART in mode Receiver ---------------------------------------------------*/
    if((flag != RESET) && (irq_match != RESET))
    {
      _rx_buffer.copy_to_buffer((uint8_t*) &(_uart_handle.Instance->DR), 1);
    }

    flag = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_TXE);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_TXE);
    /* UART in mode Transmitter ------------------------------------------------*/
    if((flag != RESET) && (irq_match != RESET))
    {
    // UART_Transmit_IT(huart);
      if(_tx_buffer.get_from_buffer((uint8_t*) &(_uart_handle.Instance->DR), 1), 1 == false)
      {
          __HAL_UART_DISABLE_IT(&_uart_handle, UART_IT_TXE);
      }
    }
    // TODO: Nachricht nach dem Piepton, hier weitermachen
    /*flag = __HAL_UART_GET_FLAG(&_uart_handle, UART_FLAG_TC);
    irq_match = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_TC);
    /* UART in mode Transmitter end --------------------------------------------
    if((flag != RESET) && (irq_match != RESET))
    {
    UART_EndTransmit_IT(&_uart_handle);
    }

    if(_uart_handle.ErrorCode != HAL_UART_ERROR_NONE)
    {
    // Set the UART state ready to be able to start again the process
        _uart_handle.State = HAL_UART_STATE_READY;

    HAL_UART_ErrorCallback(_uart_handle);
    }*/
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
