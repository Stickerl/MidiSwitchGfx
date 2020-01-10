/*
 * ring_buffer.h
 *
 * Created: 2/3/2018 9:19:34 PM
 *  Author: Erwin
 */ 


#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdbool.h"
#include "I_ring_buffer.hpp"

template <uint32_t SIZE>

class RingBuffer : public I_RingBuffer{

public:

	RingBuffer()
	{
	    clear();
	}

	~RingBuffer()
	{
	    clear();
	}

	// copy a number of bytes to the buffer; returns false if there is not enought space in the buffer
	bool copy_to_buffer(uint8_t* data, uint32_t cnt)
	{
	    bool success = false;
	    if ((SIZE - get_cnt()) >= cnt)
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
	bool get_from_buffer(uint8_t* dest, uint32_t cnt)
	{
	    bool success = false;
	    if (get_cnt() >= cnt)
	    {
	         for(uint32_t index = 0; index < cnt; index++)
	         {
	             dest[index] = byte_from_buffer();
	         }
	         success = true;
	    }
	    return success;
	}

	// gets the number of bytes in the buffer
	uint32_t get_cnt()
	{
	    uint32_t cnt = 0;
	    if (head == tail)
	    {
	        // buffer is empty
	    }
	    else if (head == dec_index(tail))
	    {
	        // buffer is full
	        cnt = SIZE;
	    }
	    else if(head > tail)
	    {
	        // head - tail bytes in buffer
	        cnt = head - tail;
	    }
	    else
	    {
	        // tail > head index
	        cnt =  (SIZE + 1) - (tail - head);
	    }
	    return cnt;
	}

	// gets the number of free bytes in the buffer
	uint32_t get_space_left()
	{
	    return (SIZE - get_cnt());
	}

	// discards all data in the buffer
	void clear()
	{
	    // reset head and tail => RB_get_cnt returns 0 and buffer assumed to be empty
	    head = 0;
	    tail = 0;
	}

private:
    uint32_t     head;            // index of most recently added byte
    uint32_t     tail;            // index of the next byte to read
    uint8_t      buffer[SIZE + 1];    // allocate buffer memory


    // increments a buffer address
    uint32_t inc_index(uint32_t index)
    {
        uint32_t new_index = 0;
        if (index != (SIZE))
        {
            // index is at the end of the buffer => restart
            new_index = index + 1;
        }
        return new_index;
    }

    // decrements a buffer address
    uint32_t dec_index(uint32_t index)
    {
        uint32_t new_index = SIZE;
        if(index != 0)
        {
            new_index = index - 1;
        }
        return new_index;
    }

    // adds one byte to the buffer; there is no check if some space is left in the buffer!
    void byte_to_buffer(uint8_t data)
    {
        //increment the head address
        head = inc_index(head);

        // copy the byte into the buffer
        buffer[head] = data;
    }

    // gets a byte from the buffer; there is no check if the buffer is empty ore not!
    uint8_t byte_from_buffer()
    {
        //increment the tail address
        tail = inc_index(tail);

        // read the byte and return it
        return buffer[tail];
    }

};

#endif /* RING_BUFFER_H_ */
