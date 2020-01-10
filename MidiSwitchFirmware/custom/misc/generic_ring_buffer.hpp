/*
 * generic_ring_buffer.hpp
 *
 * Created: 2/3/2018 9:19:34 PM
 *  Author: Erwin
 */ 


#ifndef GENERIC_RING_BUFFER_H_
#define GENERIC_RING_BUFFER_H_

#include <cstdint>
#include <cstdbool>

template <typename type, std::uint32_t SIZE>
class GenericRingBuffer
{
public:
    GenericRingBuffer() {
        clear();
    }

    ~GenericRingBuffer() {
        clear();
    }

    // copy a number of elements to the buffer; returns false if there is not enought space in the buffer
    bool add(type* data, std::uint32_t cnt = 1) {
        bool success = false;
        if ((SIZE - getCnt()) >= cnt) {
            for(uint16_t index = 0; index < cnt; index++) {
                incIndex(head);
                buffer[head] = data[index]; // type needs to implement a copy constructor
            }
            success = true;
        }
        return success;
    }

    // read a number of elements from the buffer to the destination; returns false if there is not enougth data in the buffer
    bool get(type* dest, std::uint32_t cnt = 1) {
        bool success = false;
        if (getCnt() >= cnt) {
             for(std::uint32_t index = 0; index < cnt; index++) {
                incIndex(tail);
                dest[index] = buffer[tail]; // type needs to implement a copy constructor
             }
             success = true;
        }
        return success;
    }

    // gets the number of elements in the buffer
    std::uint32_t getCnt() {
    	std::uint32_t cnt = 0;
        if (head == tail) {
            // buffer is empty
        }
        else if (head == decIndex(tail)) {
            cnt = SIZE; // buffer is full
        }
        else if(head > tail) {
            cnt = head - tail; // head - tail bytes in buffer
        }
        else {
            cnt = (SIZE + 1) - (tail - head); // tail > head index
        }
        return cnt;
    }

    // gets the number of free elements in the buffer
    std::uint32_t getSpaceLeft() {
        return (SIZE - getCnt());
    }

    // discards all data in the buffer
    void clear() {
        // reset head and tail => RB_getCnt returns 0 and buffer assumed to be empty
        head = 0;
        tail = 0;
    }

private:
    std::uint32_t head; // index of most recently added byte
    std::uint32_t tail; // index of the next byte to read
    type buffer[SIZE + 1]; // allocate buffer memory

    // increments a buffer address
    void incIndex(std::uint32_t& index) {
        if(index < (SIZE)) {
            index++;
        }
        else {
            index = 0;
        }
    }

    // decrements a buffer address
    std::uint32_t decIndex(std::uint32_t index) {
    	std::uint32_t newIndex = SIZE;
        if(index != 0) {
            newIndex = index - 1;
        }
        return newIndex;
    }
};

#endif /* RING_BUFFER_H_ */
