/*
 * I_midi_callbacks.hpp
 *
 *  Created on: Aug 18, 2018
 *      Author: Erwin
 */

#ifndef MIDI_I_MIDI_CALLBACKS_HPP_
#define MIDI_I_MIDI_CALLBACKS_HPP_

#include "midi_defines.hpp"


class I_MidiControlChangeCb
{
public:
    I_MidiControlChangeCb(){};
    virtual ~I_MidiControlChangeCb(){};
    virtual void control_change_cb(midi_data currentData) = 0;
};

class I_MidiProgrammChangeCb
{
public:
    I_MidiProgrammChangeCb(){};
    virtual ~I_MidiProgrammChangeCb(){};
    virtual void program_change_cb(midi_data currentData) = 0;
};




#endif /* MIDI_I_MIDI_CALLBACKS_HPP_ */
