/*
 * gpio_helper_functions.h
 *
 *  Created on: 12.10.2018
 *      Author: Matze
 */

#ifndef MISC_GPIO_HELPER_FUNCTIONS_HPP_
#define MISC_GPIO_HELPER_FUNCTIONS_HPP_

#include "stm32F4xx.h"
#include "assert.h"

#ifdef __cplusplus
extern "C"{
#endif

void enable_gpio_clk(GPIO_TypeDef* port_name);

#ifdef __cplusplus
}
#endif

#endif /* MISC_GPIO_HELPER_FUNCTIONS_HPP_ */
