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

    HAL_FLASH_Unlock();
    FLASH_Erase_Sector(FLASH_SECTOR_23, VOLTAGE_RANGE_3);
    HAL_FLASH_Lock();

    determineActiveSector();
    scanForValidFrames(*activeSector);
    char testGordon[] = "GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?"
            "            GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?GordonFlusht!?";

    for(uint32_t i = activeSector->size; i >= (sizeof(testGordon) + frameOverhead); )
    {
        store(1, (uint8_t*)testGordon, sizeof(testGordon), 0);
        i -= (sizeof(testGordon) + frameOverhead);
    }
    store(1, (uint8_t*)testGordon, sizeof(testGordon), 0);
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

void Flash::store(uint16_t id, uint8_t* source, uint32_t size, uint32_t addr)
{
    uint32_t writeIndex = findLastTerminator(*activeSector);
    uint32_t spaceInSector = activeSector->size - writeIndex;
    uint32_t currentSize = 0;
    uint32_t requestSize = size + addr;
    uint8_t frameHeader[frameOverhead] = {0};
    frameHeader[frameOverhead - sizeof(frame_t::terminator)] = frame_t::terminator;
    *(uint16_t*)&frameHeader[frameOverhead - sizeof(frame_t::terminator) - sizeof(validFrames[0].user_id) - sizeof(validFrames[0].size)] = id;

    (writeIndex == invalidSecIndex) ? (writeIndex = 0) : (writeIndex++); // if the write index is invalid nothing was written to the flash so far

    if(validFrames[id].data != NULL)    // old frame available?
    {
        if(validFrames[id].size > requestSize) // is it larger than the new frame (= size + addr)
        {
            requestSize = validFrames[id].size; // resulting framelength = size of the old frame
        }
    }

    // set the new size
    *(uint16_t*)&frameHeader[frameOverhead - sizeof(frame_t::terminator) - sizeof(validFrames[0].size)] = requestSize;

    assert(getFreeMemory() >= (requestSize + frameOverhead)); // the number of bytes to be stored in the flash is greater than 128k
    if(spaceInSector < (requestSize + frameOverhead))
    {
        relocateData();
        writeIndex = findLastTerminator(*activeSector) + 1;
    }

    crateAndStoreFrame
    // TODO write the new frame
    /*
    // store the new frame in the flash
    if(validFrames[id].data != NULL)
    {
        copyToNvm(writeIndex, validFrames[id].data, addr);
    }
    writeIndex += addr;
    copyToNvm(writeIndex, source, size);
    writeIndex += size;
    if(validFrames[id].data != NULL)
    {
        copyToNvm(writeIndex, &validFrames[id].data[addr+size], (requestSize - (size + addr)));
        writeIndex += (requestSize - (size + addr));
    }

    // add the frame header
    copyToNvm(writeIndex, frameHeader, sizeof(frameHeader));

    scanForValidFrames(*activeSector); // update the valid frames array
     */
}

Flash::frame_t Flash::crateAndStoreFrame(Flash::frame_t oldFrame, )
{
    // store the new frame in the flash
    if(validFrames[id].data != NULL)
    {
        copyToNvm(writeIndex, validFrames[id].data, addr);
    }
    writeIndex += addr;
    copyToNvm(writeIndex, source, size);
    writeIndex += size;
    if(validFrames[id].data != NULL)
    {
        copyToNvm(writeIndex, &validFrames[id].data[addr+size], (requestSize - (size + addr)));
        writeIndex += (requestSize - (size + addr));
    }

    // add the frame header
    copyToNvm(writeIndex, frameHeader, sizeof(frameHeader));

    scanForValidFrames(*activeSector); // update the valid frames array
}

void Flash::copyToNvm(uint32_t writeIndex, uint8_t* data, uint32_t size)
{
    assert(data != NULL);
    // determine chunk sizes for efficient flash programming
    uint8_t byteCnt = 0;
    uint8_t halfWordCnt = 0;
    uint32_t wordCnt = 0;

    uint32_t dataIndex = 0;
    uint32_t startAddress = (uint32_t)activeSector->start + writeIndex;
    uint8_t alignment = startAddress & 3;
    uint8_t alignCnt = (size > (4-alignment)) ? (4-alignment) : size;

    HAL_FLASH_Unlock();
    for(uint8_t i = 0; i < alignCnt; i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((uint32_t)activeSector->start + writeIndex + dataIndex), data[dataIndex]);
        dataIndex++;
    }
    /*switch(alignment) // TODO what happens if we want to write less bytes than needed to aligne the data
    {
    case 1:
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((uint32_t)activeSector->start + writeIndex + dataIndex), data[dataIndex]);
        dataIndex++;
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ((uint32_t)activeSector->start + writeIndex + dataIndex), *((uint16_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint16_t);
        break;
    case 2:
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ((uint32_t)activeSector->start + writeIndex + dataIndex), *((uint16_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint16_t);
        break;
    case 3:
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((uint32_t)activeSector->start + writeIndex + dataIndex), data[dataIndex]);
        dataIndex++;
        break;
    default:
        alignment = 4;
        break;
    }*/

    byteCnt     = (size - (alignCnt))  & 0x01;         // take care of the last bit only. Everything above can be divided by 16
    halfWordCnt = ((size - (alignCnt)) >> 1) & 0x01;   // divide by 16 and take care of the last bit only. Everything above can be divided by 32
    wordCnt     = ((size - (alignCnt)) >> 2);          // divide by 32 => double word count

    while(wordCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ((uint32_t)activeSector->start + writeIndex + dataIndex), *((uint32_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint32_t);
        wordCnt--;
    }
    if(halfWordCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ((uint32_t)activeSector->start + writeIndex + dataIndex), *((uint16_t*)(&data[dataIndex])));
        dataIndex += sizeof(uint16_t);
    }
    if(byteCnt > 0)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, ((uint32_t)activeSector->start + writeIndex + dataIndex), data[dataIndex]);
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
    uint8_t* addr = sector.start;                     // sector end addr
    uint32_t terminator_index = Flash::invalidSecIndex;     // 0xFFFFFFFF -> no terminator found
    for(uint32_t i = sector.size-1; i > 0; i--)
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
    assert(sector.start[index] == frame_t::terminator);
    memcpy(&frame.size, &sector.start[index - (frameOverhead - sizeof(frame.user_id) - 1)], sizeof(frame.size));
    memcpy(&frame.user_id, &sector.start[index - (frameOverhead - 1)], sizeof(frame.user_id));
    frame.data = &sector.start[index - (frameOverhead + frame.size - 1)];

    return frame;
}

void Flash::scanForValidFrames(sector_t sector)
{
    frame_t frame;
    uint32_t lastTerminator = findLastTerminator(sector);
    if(lastTerminator != invalidSecIndex)
    {
        for(uint32_t i = lastTerminator; i > 0;)
        {
            frame = frameFromIndex(sector, i);
            if(validFrames[frame.user_id].data < frame.data)
            {
                validFrames[frame.user_id] = frame;
            }
            (i > (frameOverhead + frame.size)) ? (i -= frameOverhead + frame.size) : (i = 0);
        }
    }
}


uint32_t Flash::getFreeMemory()
{
    uint32_t spaceLeft = activeSector->size;

    for(uint32_t index = 0; index < numFrameIds; index++)
    {
        if(validFrames[index].data != NULL)
        {
            spaceLeft -= frameOverhead + validFrames[index].size;
        }
    }
    return spaceLeft;
}

// copy data from the old sector to new sector, invalidates the old sector and activates the new sector
void Flash::relocateData()
{
    sector_t* oldSector = activeSector;
    activeSector = (&secs[0] == activeSector) ? &secs[1] : &secs[0];
    uint32_t targetIndex = 0;

    for(uint8_t user_id = 0; user_id < numFrameIds; user_id++)
    {
        if(validFrames[user_id].data != NULL)
        {
            copyToNvm(targetIndex, validFrames[user_id].data, (validFrames[user_id].size + frameOverhead));
        }
    }
    invalidateSector(*oldSector);
    // invalidate the validFrames array as it is not valid anymore :(
    for(uint8_t index = 0; index < numFrameIds; index++)
    {
        validFrames[index].data = NULL;
    }
}

// writes the terminator at the verry end of the sector
void Flash::invalidateSector(sector_t& sector)
{
    HAL_FLASH_Unlock();
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, (uint32_t)&sector.start[sector.size - 1] , invalidationStamp);
    HAL_FLASH_Lock();
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
    assert(validSecIndex != 0);
    if(validSecIndex == 1)
    {
        activeSector = validSecs[validSecIndex];
    }
    else
    {
        // two sectors seem to be valid => something went wrong at the pervious data relocation
        termIndex[0] = findLastTerminator(*validSecs[0]);
        termIndex[1] = findLastTerminator(*validSecs[1]);

        if(termIndex[0] == invalidSecIndex)
        {
            activeSector = validSecs[1];    // index is invalid => the other sector is valid
        }
        else if(termIndex[1] == invalidSecIndex)
        {
            activeSector = validSecs[0];    // index is invalid => the other sector is valid
        }
        else
        {
            // the sector with less space left is valid as we dont know when the relocation failed
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


/**
  * @brief  Flush the instruction and data caches
  * @retval None
  */
void Flash::flushCaches(void)
{
  /* Flush instruction cache  */
  if(READ_BIT(FLASH->ACR, FLASH_ACR_ICEN)!= RESET)
  {
    /* Disable instruction cache  */
    __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
    /* Reset instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_RESET();
    /* Enable instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
  }

  /* Flush data cache */
  if(READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != RESET)
  {
    /* Disable data cache  */
    __HAL_FLASH_DATA_CACHE_DISABLE();
    /* Reset data cache */
    __HAL_FLASH_DATA_CACHE_RESET();
    /* Enable data cache */
    __HAL_FLASH_DATA_CACHE_ENABLE();
  }
}

