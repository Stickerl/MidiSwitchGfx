/*
 * I_ring_buffer.hpp
 *
 *  Created on: 26.08.2018
 *      Author: Erwin
 */

#ifndef I_RING_BUFFER_HPP_
#define I_RING_BUFFER_HPP_

#include "stdint.h"

class I_RingBuffer{

public:
    I_RingBuffer() {};
    virtual ~I_RingBuffer(){};

    // copy a number of bytes to the buffer; returns false if there is not enought space in the buffer
    virtual bool copy_to_buffer(uint8_t* data, uint32_t cnt) = 0;

    // read a number of bytes from the buffer to the destination; returns false if there is not enougth data in the buffer
    virtual bool get_from_buffer(uint8_t* dest, uint32_t cnt) = 0;

    // gets the number of bytes in the buffer
    virtual uint32_t get_cnt() = 0;

    // gets the number of free bytes in the buffer
    virtual uint32_t get_space_left() = 0;

    // discards all data in the buffer
    virtual void clear() = 0;
};



#endif /* I_RING_BUFFER_HPP_ */
