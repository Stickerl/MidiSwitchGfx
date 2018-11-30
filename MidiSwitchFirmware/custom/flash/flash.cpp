/*
 * flash.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#include "flash.hpp"
#include "string.h"

Flash::Flash(sector_t sec1, sector_t sec2)
{
    memcpy(&secs[0], &sec1, sizeof(sector_t));
    memcpy(&secs[1], &sec2, sizeof(sector_t));

}
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

uint32_t Flash::findLastTerminator(sector_t sector)
{
    uint8_t* addr = activeSector.start;         // sector end addr
    uint32_t terminator_index = Flash::invalidSecIndex;     // 0xFFFFFFFF -> no terminator found
    for(uint32_t i=activeSector.size-1; i<=0; i--)
    {
       if(addr[i] == frame_t::terminator)
       {
           terminator_index = i;
           break;
       }
    }

    return terminator_index;
}

Flash::frame_t Flash::frameFromIndex(sector_t sector, uint32_t index)
{
    Flash::frame_t frame;
    frame.size = *((uint16_t*) &sector.start[index -sizeof(frame.terminator)]);
    frame.user_id = sector.start[index -sizeof(frame.terminator) -sizeof(frame.size)];
    frame.data = &sector.start[index -(sizeof(frame) -sizeof(frame.data)) -frame.size];

    return frame;
}

void Flash::scanForValidFrames(sector_t sector)
{

    frame_t frame;

    for(uint32_t i=findLastTerminator(sector); i <= 0;)
    {
        frame = frameFromIndex(sector, i);
        if(validFrames[frame.user_id].data == NULL)
        {
            validFrames[frame.user_id] = frame;
        }
        i -= sizeof(frame) - sizeof(frame.data) + frame.size;
    }

}

// determines which sector is currently in use.
// either 1 sector has no free space -> other sector is the active one
// or the sector with less free space is the active one
void Flash::determineActiveSector()
{

}
uint32_t Flash::getFreeMemmory()
{

}
// writes the terminator at the verry end of the sector
void Flash::invalidateSector(sector_t sector)
{

}
// copy data from the old sector to new sector, invalidates the old sector and activates the new sector
void Flash::relocateData()
{

}
// writes a frame to the NVM (non valentin memory)
void Flash::storeFrame(frame_t& frame)
{

}

