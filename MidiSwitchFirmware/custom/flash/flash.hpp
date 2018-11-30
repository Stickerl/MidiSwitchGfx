/*
 * flash.hpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#ifndef FLASH_FLASH_HPP_
#define FLASH_FLASH_HPP_

#include "I_flash.hpp"
#include "stm32f4xx_hal.h"

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

private:
    typedef struct sector
    {
        uint8_t* start;
        uint32_t size;
    } sector_t;

    typedef struct frame
    {
        uint8_t* data;
        uint8_t user_id;
        uint16_t size;
        static const uint8_t terminator = 0xED; // marks the end of a frame
    } frame_t;

    // indicates that the sector is invalide
    // overrules the terminator (it can overwrite the terminator without an erase)
    static const uint8_t invalidationStamp = 0xAD;
    frame_t valideFrames[1]; // 1= make compiler happy => size needs to be defined

    frame_t last_frame;
    sector_t activeSector;

    // finds the last frame in the sector
    // if the data != terminator or FF the sector is invalid => no frame in the sector
    frame_t findLastFrame(sector_t sector);

    // scans the sector for all valid frames starting from the last frame in the sector
    void scanForValidFrames();

    // determines which sector is currently in use.
    // either 1 sector has no free space -> other sector is the active one
    // or the sector with less free space is the active one
    void determineActiveSector();

    uint32_t getFreeMemmory();

    // writes the terminator at the verry end of the sector
    void invalidateSector(sector_t sector);

    // copy data from the old sector to new sector, invalidates the old sector and activates the new sector
    void relocateData();
};


#endif /* FLASH_FLASH_HPP_ */
