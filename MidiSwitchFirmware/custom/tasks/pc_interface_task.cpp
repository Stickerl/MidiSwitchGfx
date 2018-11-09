/*
 * pc_interface_task.cpp
 *
 *  Created on: Oct 20, 2018
 *      Author: Erwin
 */

#include "pc_interface_task.h"

#define PC_INTERFACE_TASK_PRIORITY                (4)
#define PC_INTERFACE_TASK_STK_SIZE                (1024)

#ifdef __cplusplus
    extern "C"{
#endif


void pc_interface_task_create(void)
{
    xTaskCreate(pc_interface_task_run, (TASKCREATE_NAME_TYPE)"PCInterfaceTask",
                PC_INTERFACE_TASK_PRIORITY,
                NULL,
                PC_INTERFACE_TASK_STK_SIZE,
                NULL);
}

void pc_interface_task_run(void* params)
{
    // set up the communication Uart for pc connection
    UartIrqs uartIrqReg;
    UartIrqBased::Pin uart6_tx(GPIOG, GPIO_PIN_14, GPIO_AF8_USART6);
    UartIrqBased::Pin uart6_rx(GPIOG, GPIO_PIN_9,  GPIO_AF8_USART6);
    RingBuffer<20> txBuffer;
    RingBuffer<20> rxBuffer;
    UartIrqBased uart({115200, txBuffer, rxBuffer, UartIrqBased::UART_6,
                       uart6_tx, uart6_rx, uartIrqReg});
    uart.start_receive();
    uint8_t rxCnt = 0;
    uint8_t loopBackBuffer[20];
    while(1)
    {
        rxCnt = uart.get_rx_cnt();
        if(rxCnt > 0)
        {
            uart.get_data(loopBackBuffer, rxCnt);
            uart.send(loopBackBuffer, rxCnt);
        }
        vTaskDelay(1);
    }

}

#ifdef __cplusplus
    }
#endif
