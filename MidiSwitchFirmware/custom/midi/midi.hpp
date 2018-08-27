/*
 * midi.h
 *
 * Created: 2/25/2018 8:17:23 PM
 *  Author: Erwin
 */ 


#ifndef MIDI_H_
#define MIDI_H_

#include "stdint.h"
#include "I_ring_buffer.hpp"
#include "midi_defines.hpp"
#include "I_midi_callbacks.hpp"


namespace Midi_n
{

class MidiDecoder
{
public:

    MidiDecoder(I_RingBuffer& midiRxBuffer, uint32_t& sysTime, uint32_t timeout);
    ~MidiDecoder();

    // decode the received data
    void decode();

    // register a callback for a received control change message
    void register_control_change_cb(I_MidiControlChangeCb* callBack);

    // register a callback for a received program change message
    void register_program_change_cb(I_MidiProgrammChangeCb* callBack);


private:
    typedef enum
    {
        WAIT_ON_MESSAGE = 0,
        PROGRAM_CHANGE  = 1,
        BANK_SELECT_MSB = 2,
        BANK_SELECT_LSB = 3,
        CONTROL_CHANGE  = 4,
        CONTROLLER_NR   = 5,
    } states;

    states      mainState;
    uint32_t&   _sysTime;               // sys tick relation
    uint32_t    _timeout;               // timeout in case of comunication loss
    uint32_t    prevTimeStamp;          // timestamp of the last call
    I_RingBuffer& _midiRxBuffer;
    midi_data   curData;

    I_MidiControlChangeCb*      _controlChange;
    I_MidiProgrammChangeCb*     _programmChange;

};

} // namespace Midi_n

#endif /* MIDI_H_ */
