/*
 * midi_task.hpp
 *
 *  Created on: 21.09.2018
 *      Author: Erwin
 */

#ifndef TASKS_MIDI_TASK_H_
#define TASKS_MIDI_TASK_H_

#include "FreeRTOSConfig.h"
#include "ring_buffer.hpp"
#include "uart.hpp"
#include "uart_irqs.h"
#include "config_manager.hpp"
#include "flash.hpp"
#include "DigitalOutput.h"
#include "midi.hpp"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#ifdef __cplusplus
    extern "C"{
#endif

void midi_task_create(void);

void midi_task_run(void* params);

#ifdef __cplusplus
    }
#endif

#endif /* TASKS_MIDI_TASK_H_ */


