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
    determineActiveSector();
    scanForValidFrames(*activeSector);

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

void Flash::store(uint16_t id, uint32_t* source, uint32_t size, uint32_t addr)
{
    assert(getFreeMemmory() >= (size + frameOverhad));
    uint32_t writeIndex = findLastTerminator(*activeSector);
    uint32_t spaceInSector = activeSector->size - writeIndex;
    if(spaceInSector < (size + frameOverhad))
    {
        relocateData();
    }
    else
    {
        if(validFrames[id].data != NULL) // there is already data available
        {

        }
        else
        {

        }
    }




    scanForValidFrames(*activeSector); // update the valid frames array
}

void Flash::copyToNvm(uint32_t writeIndex, uint8_t* data, uint32_t size)
{
    // determine chunk sizes for efficient flash programming
    uint8_t byteCnt         = size & 0x01;          // take care of the last bit only. Everything above can be divided by 16
    uint8_t halfWordCnt     = (size >> 1) & 0x01;   // divide by 16 and take care of the last bit only. Everything above can be divided by 32
    uint8_t wordCnt         = (size >> 2) & 0x01;   // divide by 32 and take care of the last bit only. Everything above can be divided by 64
    uint32_t doubleWordCnt  = size >> 3;            // divide by 64 => double word count

    uint32_t dataIndex = 0;

    HAL_FLASH_Unlock();
    FLASH_Erase_Sector(FLASH_SECTOR_23, VOLTAGE_RANGE_3);
    while(doubleWordCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, ((uint32_t)activeSector->start + writeIndex + 1), *((uint64_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint64_t);
        doubleWordCnt--;
    }
    if(wordCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ((uint32_t)activeSector->start + writeIndex + 1), *((uint32_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint32_t);
    }
    if(halfWordCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ((uint32_t)activeSector->start + writeIndex + 1), *((uint16_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint16_t);
    }
    if(byteCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((uint32_t)activeSector->start + writeIndex + 1), data[dataIndex]);
    }
    HAL_FLASH_Lock();
}

// reduceSize size number of bytes from the end of the frame
void Flash::reduceSize(uint16_t id, uint32_t size)
{

}

void Flash::read(uint16_t id, uint32_t addr, uint32_t* target, uint32_t size)
{

}


uint32_t Flash::findLastTerminator(sector_t sector)
{
    uint8_t* addr = activeSector->start;                     // sector end addr
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
    frame.data = &sector.start[index -(frameOverhad) -frame.size];

    return frame;
}

void Flash::scanForValidFrames(sector_t sector)
{

    frame_t frame;

    for(uint32_t i = findLastTerminator(sector); i <= 0;)
    {
        frame = frameFromIndex(sector, i);
        if(validFrames[frame.user_id].data == NULL)
        {
            validFrames[frame.user_id] = frame;
        }
        i -= frameOverhad + frame.size;
    }
}


uint32_t Flash::getFreeMemmory()
{
    uint32_t spaceLeft = activeSector->size;

    for(uint32_t index = 0; index < numFrameIds; index++)
    {
        if(validFrames[index].data != NULL)
        {
            spaceLeft -= frameOverhad + validFrames[index].size;
        }
    }
}

// copy data from the old sector to new sector, invalidates the old sector and activates the new sector
void Flash::relocateData()
{

    assert(false); // TODO implement this function!?!? :(
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

