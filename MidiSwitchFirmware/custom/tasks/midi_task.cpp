/*
 * midi_task.cpp
 *
 *  Created on: 21.09.2018
 *      Author: Erwin
 */


#include "midi_task.h"
#include "gui_queue.h"
#include "guiCommunication.hpp"


#define configMidi_TASK_PRIORITY                (3)
#define configMidi_TASK_STK_SIZE                (1024)
#define CONFIG_MANAGER_FLASH_ID                 1

#ifdef __cplusplus
    extern "C"{
#endif


void midi_task_create(void)
{
    xTaskCreate(midi_task_run, (TASKCREATE_NAME_TYPE)"MidiTask",
                configMidi_TASK_STK_SIZE,
                NULL,
                configMidi_TASK_PRIORITY,
                NULL);
}


void midi_task_run(void* params)
{
    //DigitalOutput testPin(GPIOG, GPIO_PIN_9);
    uint32_t midiSysTime = 0;
    uint32_t rxCnt = 0;

    // configure the midi Uart
    UartIrqs midiUartIrqReg;
    UartIrqBased::Pin midiUart_tx(GPIOA, GPIO_PIN_0, GPIO_AF8_UART4);
    UartIrqBased::Pin midiUart_rx(GPIOA, GPIO_PIN_1, GPIO_AF8_UART4);
    RingBuffer<0> midiTxBuffer; // not used as the tx pin is not routed at the board
    RingBuffer<128> midiRxBuffer;
    UartIrqBased midiUart({115200, midiTxBuffer, midiRxBuffer, UartIrqBased::UART_4,
                       midiUart_tx, midiUart_rx, midiUartIrqReg});
    midiUart.start_receive();

    // set up configuration sotrage management
    Flash::sector_t sec1(FLASH_SECTOR_22, (uint8_t*) 0x081C0000, 0x20000); // Sector 22 size 128k
    Flash::sector_t sec2(FLASH_SECTOR_23, (uint8_t*) 0x081E0000, 0x20000); // Sector 23 size 128k
    Flash flash(sec1, sec2);
    ConfigManager cfgManager(flash, CONFIG_MANAGER_FLASH_ID);

    GuiCommunication guiCom(cfgManager);
    // GuiCommunication has to register in the cfgManager
    cfgManager.init();

    // set up midi decoder
    Midi_n::MidiDecoder midiDecoder(midiRxBuffer, midiSysTime, 100u);
    midiDecoder.register_control_change_cb(&cfgManager);
    midiDecoder.register_program_change_cb(&cfgManager);

    while(1)
    {
        midiSysTime++;
        midiDecoder.decode();
        guiCom.run();
        vTaskDelay(10);
    }
}

#ifdef __cplusplus
    }
#endif

