/*
 * gpio_helper_functions.c
 *
 *  Created on: 12.10.2018
 *      Author: Matze -> des kann ja nix werden
 *      Support: www.funktioniert.net
 *      Output: C-Kot
 */

#include "gpio_helper_functions.hpp"

#ifdef __cplusplus
extern "C"{
#endif

void enable_gpio_clk(GPIO_TypeDef* port_name)
{
    switch((uint32_t) port_name)
    {
        case GPIOA_BASE:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case GPIOB_BASE:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case GPIOC_BASE:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case GPIOD_BASE:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case GPIOE_BASE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
        case GPIOF_BASE:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        case GPIOG_BASE:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case GPIOH_BASE:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        case GPIOI_BASE:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
        case GPIOJ_BASE:
            __HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
        case GPIOK_BASE:
            __HAL_RCC_GPIOK_CLK_ENABLE();
            break;
        default:
            assert(true);
            break;
    }
}

#ifdef __cplusplus
}
#endif
