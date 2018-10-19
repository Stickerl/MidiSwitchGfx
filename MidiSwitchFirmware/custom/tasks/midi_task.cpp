/*
 * midi_task.cpp
 *
 *  Created on: 21.09.2018
 *      Author: Erwin
 */


#include "midi_task.h"


#define configMidi_TASK_PRIORITY                (3)
#define configMidi_TASK_STK_SIZE                (1024)

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
    uint32_t midiSysTime = 0;
    DigitalOutput testPin(GPIOG, GPIO_PIN_9);
    Flash flash;
    ConfigManager cfgManager(flash);
    RingBuffer<128> rxBuffer;
    Midi_n::MidiDecoder midiDecoder(rxBuffer, midiSysTime, 100u);
    midiDecoder.register_control_change_cb(&cfgManager);
    midiDecoder.register_program_change_cb(&cfgManager);

    while(1)
    {
        midiSysTime++;
        midiDecoder.decode();
        testPin.toggle();
        vTaskDelay(10);
    }
}

#ifdef __cplusplus
    }
#endif

