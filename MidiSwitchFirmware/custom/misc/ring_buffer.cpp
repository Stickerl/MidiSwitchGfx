/*
 * ring_buffer.c
 *
 * Created: 2/3/2018 9:19:12 PM
 *  Author: Erwin
 */ 

#include "ring_buffer.hpp"

RingBuffer::RingBuffer(uint8_t& buffer, uint16_t size):
    _baseAddr(buffer)
{
    _headAddr    = (&_baseAddr + size -1);
    _head        = &_baseAddr;
    _tail        = &_baseAddr;
    _size        = size;
}

RingBuffer::~RingBuffer()
{
    clear();
}


// copy a number of bytes to the buffer; returns false if there is not enought space in the buffer
bool RingBuffer::copy_to_buffer(uint8_t* data, uint16_t cnt)
{
    bool success = false;
    if ((_size - get_cnt()) >= cnt)
    {
        for(uint16_t index = 0; index < cnt; index++)
        {
            byte_to_buffer(data[index]);
        }
        success = true;
    }
    return success;
}

// read a number of bytes from the buffer to the destination; returns false if there is not enougth data in the buffer
bool RingBuffer::get_from_buffer(uint8_t* dest, uint16_t cnt)
{
    bool success = false;
    if (get_cnt() >= cnt)
    {
         for(uint16_t index = 0; index < cnt; index++)
         {
             dest[index] = byte_from_buffer();
         }
         success = true;
    }
    return success;
}

// gets the number of bytes in the buffer
uint16_t RingBuffer::get_cnt()
{
    uint16_t cnt = 0;
    if (_head == _tail)
    {
        // buffer is empty
    }
    else if (_head == dec_addr((uint32_t)_tail))
    {
        // buffer is full
        cnt = _size;
    }
    else if(_head > _tail)
    {
        cnt = _head - _tail;
    }
    else
    {
        // tail address is greater than head address
        cnt =  _headAddr - _tail;
        cnt += (_head - &_baseAddr) + 1;         // there is a byte at head and base address
    }
    return cnt;
}

// gets the number of free bytes in the buffer
uint16_t RingBuffer::get_space_left()
{
    return (_size - get_cnt());
}

// discards all data in the buffer
void RingBuffer::clear()
{
    // reset head and tail => RB_get_cnt returns 0 and buffer assumed to be empty
    _head = &_baseAddr;
    _tail = &_baseAddr;
}


// increments a buffer address
uint8_t* RingBuffer::inc_addr(uint32_t addr)
{
    if (addr == (uint32_t)_headAddr)
    {
        // addr is at the end of the buffer => restart to base address;
        addr = (uint32_t)&_baseAddr;
    }
    else
    {
        addr++;
    }
    return (uint8_t*)addr;
}

// decrements a buffer address
uint8_t* RingBuffer::dec_addr(uint32_t addr)
{
    if (addr == (uint32_t)_baseAddr)
    {
        // addr is at the base of the buffer => "underflow";
        addr = (uint32_t)_headAddr;
    }
    else
    {
        addr--;
    }
    return (uint8_t*)addr;
}

// adds one byte to the buffer; there is no check if some space is left in the buffer!
void RingBuffer::byte_to_buffer(uint8_t data)
{
    //increment the head address
    _head = inc_addr((uint32_t) _head);

    // copy the byte in the buffer
    *_head = data;
}

// gets a byte from the buffer; there is no check if the buffer is empty ore not!
uint8_t RingBuffer::byte_from_buffer()
{
    //increment the tail address
    _tail = inc_addr((uint32_t)_tail);

    // read the byte and return it
    return (uint8_t) *_tail;
}


