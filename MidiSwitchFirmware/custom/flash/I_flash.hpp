/*
 * I_flash.hpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#ifndef FLASH_I_FLASH_HPP_
#define FLASH_I_FLASH_HPP_

#include "stdint.h"


class I_Flash
{
public:
    I_Flash(){};
    virtual ~I_Flash(){};

    virtual void store(uint16_t id, uint8_t* source, uint32_t size, uint32_t addr = 0) = 0;
    virtual bool read(uint16_t id, uint8_t* target, uint32_t size, uint32_t addr = 0) = 0;
    virtual uint32_t getFreeMemory() = 0;
    virtual uint32_t getIdSize(uint16_t id) = 0;
    };



#endif /* FLASH_I_FLASH_HPP_ */
