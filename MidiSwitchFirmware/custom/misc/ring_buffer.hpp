/*
 * ring_buffer.h
 *
 * Created: 2/3/2018 9:19:34 PM
 *  Author: Erwin
 */ 


#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdint.h"
#include "stdbool.h"

class RingBuffer{

public:
	RingBuffer(uint8_t& buffer, uint16_t size);
	~RingBuffer();

	// copy a number of bytes to the buffer; returns false if there is not enought space in the buffer
	bool copy_to_buffer(uint8_t* data, uint16_t cnt);

	// read a number of bytes from the buffer to the destination; returns false if there is not enougth data in the buffer
	bool get_from_buffer(uint8_t* dest, uint16_t cnt);

	// gets the number of bytes in the buffer
	uint16_t get_cnt();

	// gets the number of free bytes in the buffer
	uint16_t get_space_left();

	// discards all data in the buffer
	void clear();

private:
    uint16_t    _size;           // stores the size of the buffer
    uint8_t&    _baseAddr;       // points to the beginning of the buffer
    uint8_t*    _headAddr;       // points to the points to the end of the buffer
    uint8_t*    _head;           // points always to the most recently added byte
    uint8_t*    _tail;           // points always to the most recently read byte

    // increments a buffer address
    uint8_t* inc_addr(uint32_t addr);

    // decrements a buffer address
    uint8_t* dec_addr(uint32_t addr);

    // adds one byte to the buffer; there is no check if some space is left in the buffer!
    void byte_to_buffer(uint8_t data);

    // gets a byte from the buffer; there is no check if the buffer is empty ore not!
    uint8_t byte_from_buffer();
};



#endif /* RING_BUFFER_H_ */
