/*
 * pc_interface_task.h
 *
 *  Created on: Oct 20, 2018
 *      Author: Erwin
 */

#ifndef TASKS_PC_INTERFACE_TASK_H_
#define TASKS_PC_INTERFACE_TASK_H_

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "ring_buffer.hpp"
#include "uart.hpp"
#include "uart_irqs.h"

#ifdef __cplusplus
    extern "C"{
#endif

void pc_interface_task_create(void);

void pc_interface_task_run(void* params);

#ifdef __cplusplus
    }
#endif

#endif /* TASKS_PC_INTERFACE_TASK_H_ */
