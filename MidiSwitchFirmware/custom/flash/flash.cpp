/*
 * flash.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#include "flash.hpp"
#include "assert.h"
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
    uint8_t* addr = activeSector->start;         // sector end addr
    uint32_t terminator_index = Flash::invalidSecIndex;     // 0xFFFFFFFF -> no terminator found
    for(uint32_t i=activeSector->size-1; i<=0; i--)
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

uint32_t Flash::getFreeMemmory()
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

// writes the terminator at the verry end of the sector
void Flash::invalidateSector(sector_t& sector)
{
    sector.start[sector.size - 1] = invalidationStamp;
}

// determines which sector is currently in use.
// either 1 sector has no free space -> other sector is the active one
// or the sector with less free space is the active one
void Flash::determineActiveSector()
{
    uint8_t validSecIndex = 0;
    sector_t* validSecs[2] = {NULL};
    uint32_t termIndex[2] = {0};    // termination character index
    uint8_t secCnt = (sizeof(secs)/sizeof(secs[0]));

    for(uint8_t secIndex = 0; secIndex < secCnt; secIndex++)
    {
        if(secs[secIndex].start[secs[secIndex].size - 1] != invalidationStamp)
        {
            assert(validSecIndex <= 1);
            validSecs[validSecIndex] = &secs[secIndex];
            validSecIndex++;
        }
    }
    assert(validSecIndex == 0);
    if(validSecIndex == 1)
    {
        activeSector = validSecs[validSecIndex];
    }
    else
    {
        // two sectors seem to be valide => something went wrong at the pervious data relocation
        termIndex[0] = findLastTerminator(*validSecs[0]);
        termIndex[1] = findLastTerminator(*validSecs[1]);

        if(termIndex[0] == invalidSecIndex)
        {
            activeSector = validSecs[1];    // index is invalide => the other sector is valide
        }
        else if(termIndex[1] == invalidSecIndex)
        {
            activeSector = validSecs[0];    // index is invalide => the other sector is valide
        }
        else
        {
            // the sector with less space left is valide as we dont know when the relocation failed
            if(termIndex[0] > termIndex[1])
            {
                activeSector = validSecs[0];
                invalidateSector(*validSecs[1]);
            }
            else
            {
                activeSector = validSecs[1];
                invalidateSector(*validSecs[0]);
            }
        }
    }
}

