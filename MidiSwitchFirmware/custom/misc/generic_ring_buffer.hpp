/*
 * generic_ring_buffer.h
 *
 * Created: 2/3/2018 9:19:34 PM
 *  Author: Erwin
 */ 


#ifndef GENERIC_RING_BUFFER_H_
#define GENERIC_RING_BUFFER_H_


#include "stdbool.h"
#include "string.h"


template <uint32_t SIZE>

class GenericRingBuffer
{
public:
    GenericRingBuffer()
    {
        clear();
    }

    ~GenericRingBuffer()
    {
        clear();
    }
	

	// copy a number of elements to the buffer; returns false if there is not enought space in the buffer
	bool copy_to_buffer(type& data, uint32_t cnt)
	{
	    bool success = false;
	    if ((SIZE - get_cnt()) >= cnt)
	    {
	        for(uint16_t index = 0; index < cnt; index++)
	        {
	            elementToBuffer(data[index]);
	        }
	        success = true;
	    }
	    return success;
	}

	// read a number of elements from the buffer to the destination; returns false if there is not enougth data in the buffer
	bool get_from_buffer(type& dest, uint32_t cnt)
	{
	    bool success = false;
	    if (get_cnt() >= cnt)
	    {
	         for(uint32_t index = 0; index < cnt; index++)
	         {
	             elementFromBuffer(dest[index]);
	         }
	         success = true;
	    }
	    return success;
	}

	// gets the number of elements in the buffer
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

	// gets the number of free elements in the buffer
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
    type      	 buffer[SIZE + 1];    // allocate buffer memory


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
    void elementToBuffer(type& data)
    {
        //increment the head address
        head = inc_index(head);
        memcpy(&_buffer[head], &data, sizeof(type)); // copy the byte into the buffer memory
    }

    // gets a element from the buffer; there is no check if the buffer is empty ore not!
    void elementFromBuffer(type& dest)
    {
        //increment the tail address
        tail = inc_index(tail);
        memcpy(&dest, &_buffer[_tailIndex], sizeof(type)); // read the element and copy it to the destination
    }
};

#endif /* RING_BUFFER_H_ */
