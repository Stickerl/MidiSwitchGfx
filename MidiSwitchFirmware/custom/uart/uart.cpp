/*
 * uart.cpp
 *
 *  Created on: 17.08.2018
 *      Author: Erwin - ich war's nicht
 */

#include "uart.hpp"

UartIrqBased::UartIrqBased(InitStruct std_init):
    _tx_buffer(std_init.tx_buffer),
    _rx_buffer(std_init.rx_buffer),
    _irq_registry(std_init.irq_registry)
{
    _uart_handle.Init.BaudRate = std_init.baud_rate;
    _uart_handle.Init.Parity = UART_PARITY_NONE;
    _uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    _uart_handle.Init.StopBits = UART_STOPBITS_1;
    pin_init(std_init.uart_module, std_init.tx_pin, std_init.rx_pin);
    init_uart(std_init.uart_module);
}

UartIrqBased::UartIrqBased(InitStruct std_init, UartCfg config):
    _tx_buffer(std_init.tx_buffer),
    _rx_buffer(std_init.rx_buffer),
    _irq_registry(std_init.irq_registry)
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
    pin_init(std_init.uart_module, std_init.tx_pin, std_init.rx_pin);
    init_uart(std_init.uart_module);
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
}

void UartIrqBased::start_receive()
{
    __HAL_UART_ENABLE_IT(&_uart_handle, UART_IT_RXNE);
}

void UartIrqBased::stop_receive()
{
    __HAL_UART_DISABLE_IT(&_uart_handle, UART_IT_RXNE);
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
    uint32_t flag = 0, irq_en = 0, irq_flags = 0;
    irq_flags = _uart_handle.Instance->SR; // read all irq flags at once

    flag      = irq_flags & UART_FLAG_PE;
    irq_en = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_PE);
    /* UART parity error (PE) interrupt occurred ------------------------------------*/
    if((flag != RESET) && (irq_en != RESET))
    {
        __HAL_UART_CLEAR_PEFLAG(&_uart_handle);
        _uart_handle.ErrorCode |= HAL_UART_ERROR_PE;
    }

    flag = irq_flags & UART_FLAG_FE;
    irq_en = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_ERR);
    /* UART frame error (FE) interrupt occurred -------------------------------------*/
    if((flag != RESET) && (irq_en != RESET))
    {
        __HAL_UART_CLEAR_FEFLAG(&_uart_handle);
        _uart_handle.ErrorCode |= HAL_UART_ERROR_FE;
    }

    flag = irq_flags & UART_FLAG_NE;
    irq_en = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_ERR);
    /* UART noise error interrupt occurred -------------------------------------*/
    if((flag != RESET) && (irq_en != RESET))
    {
        __HAL_UART_CLEAR_NEFLAG(&_uart_handle);
        _uart_handle.ErrorCode |= HAL_UART_ERROR_NE;
    }

    flag = irq_flags & UART_FLAG_ORE;
    irq_en = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_ERR);
    /* UART Over-Run interrupt occurred ----------------------------------------*/
    if((flag != RESET) && (irq_en != RESET))
    {
        __HAL_UART_CLEAR_OREFLAG(&_uart_handle);
        _uart_handle.ErrorCode |= HAL_UART_ERROR_ORE;
    }

    flag = irq_flags & UART_FLAG_RXNE;
    irq_en = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_RXNE);
    /* UART in mode Receiver, read data register not empty --------------------*/
    if((flag != RESET) && (irq_en != RESET))
    {
        _rx_buffer.copy_to_buffer((uint8_t*) &(_uart_handle.Instance->DR), 1);
    }

    flag = irq_flags & UART_FLAG_TXE;
    irq_en = __HAL_UART_GET_IT_SOURCE(&_uart_handle, UART_IT_TXE);
    /* UART in mode Transmitter, data register is empty-------------------------*/
    if((flag != RESET) && (irq_en != RESET))
    {
    // UART_Transmit_IT(huart);
      if(_tx_buffer.get_from_buffer((uint8_t*) &(_uart_handle.Instance->DR), 1) == false)
      {
          __HAL_UART_DISABLE_IT(&_uart_handle, UART_IT_TXE);
      }
    }
}

// get remaining bytes in rx buffer
uint32_t UartIrqBased::get_rx_cnt()
{
    return _rx_buffer.get_cnt();
}

void UartIrqBased::pin_init(UartModuleEnum uart_module, Pin tx_pin, Pin rx_pin)
{
    GPIO_InitTypeDef Uart_PinCfg;

    // TX Pin
    enable_gpio_clk(tx_pin.port);
    Uart_PinCfg.Alternate = tx_pin.alternate;
    Uart_PinCfg.Pin = tx_pin.pin_nr;
    Uart_PinCfg.Mode = GPIO_MODE_AF_PP;
    Uart_PinCfg.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &Uart_PinCfg);

    // RX Pint
    enable_gpio_clk(rx_pin.port);
    Uart_PinCfg.Alternate = rx_pin.alternate;
    Uart_PinCfg.Pin = rx_pin.pin_nr;
    HAL_GPIO_Init(GPIOG, &Uart_PinCfg);
}

void UartIrqBased::init_uart(UartModuleEnum uart_module)
{
    /*// enable USART6 CLK
    __HAL_RCC_USART6_CLK_ENABLE();

    GPIO_InitTypeDef Uart_PinCfg;

    // Enable CLK for GPIOG
    __HAL_RCC_GPIOG_CLK_ENABLE();

    // Generic USART6 Pin settings
    Uart_PinCfg.Alternate = GPIO_AF8_USART6;
    Uart_PinCfg.Speed = GPIO_SPEED_FREQ_MEDIUM;

    // Configure PG14 as USART6 TX
    Uart_PinCfg.Pin = GPIO_PIN_14;
    Uart_PinCfg.Mode = GPIO_MODE_AF_PP;
    Uart_PinCfg.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &Uart_PinCfg);

    // Configure PG9 as USART6 RX
    Uart_PinCfg.Pin = GPIO_PIN_9;
    Uart_PinCfg.Mode = GPIO_MODE_AF_PP;
    Uart_PinCfg.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &Uart_PinCfg);*/

    // Register UART
    _irq_registry.register_obj(this, uart_module);

    switch(uart_module)
    {
        case UART_1:
            _uart_handle.Instance = USART1;
            __HAL_RCC_USART1_CLK_ENABLE();
            break;
        case UART_2:
            _uart_handle.Instance = USART2;
            __HAL_RCC_USART2_CLK_ENABLE();
            break;
        case UART_3:
            _uart_handle.Instance = USART3;
            __HAL_RCC_USART3_CLK_ENABLE();
            break;
        case UART_4:
            _uart_handle.Instance = UART4;
            __HAL_RCC_UART4_CLK_ENABLE();
            break;
        case UART_5:
            _uart_handle.Instance = UART5;
            __HAL_RCC_UART5_CLK_ENABLE();
            break;
        case UART_6:
            _uart_handle.Instance = USART6;
            __HAL_RCC_USART6_CLK_ENABLE();
            break;
        case UART_7:
            _uart_handle.Instance = UART7;
            __HAL_RCC_UART7_CLK_ENABLE();
            break;
        case UART_8:
            _uart_handle.Instance = UART8;
            __HAL_RCC_UART8_CLK_ENABLE();
            break;
        default:
            assert(true);
            break;
    }
    // UART init settings
    _uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    _uart_handle.Init.Mode = UART_MODE_TX_RX;
    _uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&_uart_handle);
}

void UartIrqBased::start_tx()
{
    __HAL_UART_ENABLE_IT(&_uart_handle, UART_IT_TXE);
}
