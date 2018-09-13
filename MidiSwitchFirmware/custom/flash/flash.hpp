/*
 * flash.hpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#ifndef FLASH_FLASH_HPP_
#define FLASH_FLASH_HPP_

#include "I_flash.hpp"

class Flash :  public I_Flash
{
public:
    Flash(){};
    virtual ~Flash(){};

    // writes a number of bytes to the flash
    virtual void writeBytes(uint32_t addr, uint8_t* data, uint32_t size);   // override

    // writes uint16_t words to the flash
    virtual void writeWords(uint32_t addr, uint16_t* data, uint32_t size);  // override

    // writes uint32_t words to the flash
    virtual void writeLong(uint32_t addr, uint32_t* data, uint32_t size);   // override

    // reads a number of bytes from the flash
    virtual void readBytes(uint32_t addr, uint8_t* target, uint32_t size);  // override

    // reads a number of uint16_t words from the flash
    virtual void readWords(uint32_t addr, uint16_t* target, uint32_t size); // override

    // reads a number of uint32_t words from the flash
    virtual void readLong(uint32_t addr, uint32_t* target, uint32_t size);  // override
};


#endif /* FLASH_FLASH_HPP_ */
