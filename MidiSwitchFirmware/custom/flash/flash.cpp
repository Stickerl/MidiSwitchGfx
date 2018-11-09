/*
 * flash.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#include "flash.hpp"

void Flash::writeBytes(uint32_t addr, uint8_t* data, uint32_t size)
{
    uint32_t address = addr;
    for(uint32_t i = 0; i < size; i++)
    {
        //FLASH_Program_Byte(address, data[i]);
        address++;
    }
}

void Flash::writeWords(uint32_t addr, uint16_t* data, uint32_t size)
{

}

void Flash::writeLong(uint32_t addr, uint32_t* data, uint32_t size)
{

}

void Flash::readBytes(uint32_t addr, uint8_t* target, uint32_t size)
{

}

void Flash::readWords(uint32_t addr, uint16_t* target, uint32_t size)
{

}

void Flash::readLong(uint32_t addr, uint32_t* target, uint32_t size)
{

}



