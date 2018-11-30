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

class Flash : public I_Flash
{
public:
    typedef struct sector
        {
            uint8_t* start;
            uint32_t size;
            sector():start(NULL),size(0){};
            sector(uint8_t* sec_start, uint32_t sec_size):
                start(sec_start),
                size(sec_size){};
        } sector_t;

    Flash(sector_t sec1, sector_t sec2);
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

    static const uint32_t invalidSecIndex = 0xFFFFFFFF;
    static const uint16_t numFrameIds = 3;
    frame_t validFrames[numFrameIds] = {NULL}; // 1= make compiler happy => size needs to be defined

    frame_t last_frame;
    sector_t activeSector;
    sector_t secs[2];

    // iterates over sector, stating at the end. If a terminator is found, the byte index
    // counting form start of sector, is returned.
    // Returns 0xFFFFFFFF if no terminator is found
    uint32_t findLastTerminator(sector_t sector);

    // reads a frame in sector from index (counting from start of sector)
    frame_t frameFromIndex(sector_t sector, uint32_t index);

    // scans the sector for all valid frames starting from the last frame in the sector
    void scanForValidFrames(sector_t sector);

    // determines which sector is currently in use.
    // either 1 sector has no free space -> other sector is the active one
    // or the sector with less free space is the active one
    void determineActiveSector();

    uint32_t getFreeMemmory();

    // writes the terminator at the verry end of the sector
    void invalidateSector(sector_t sector);

    // copy data from the old sector to new sector, invalidates the old sector and activates the new sector
    void relocateData();

    // writes a frame to the NVM (non valentin memory)
    void storeFrame(frame_t& frame);
};


#endif /* FLASH_FLASH_HPP_ */
