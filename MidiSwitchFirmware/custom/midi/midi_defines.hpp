/*
 * midi_defines.hpp
 *
 *  Created on: Aug 18, 2018
 *      Author: Erwin
 */

#ifndef MIDI_MIDI_DEFINES_HPP_
#define MIDI_MIDI_DEFINES_HPP_

#include "stdint.h"

namespace Midi_n
{

#define MIDI_CONROL_CHANGE      0xB0                // the low byte is the chanal number
#define MIDI_PROGRAM_CHANGE     0xC0                // the low byte is the chanal number
#define MIDI_BANK_SELECT_MSB    0x00
#define MIDI_BANK_SELECT_LSB    0x20

typedef enum
{
    SOUND_CONTROLLER_1  = 0x47,
    SOUND_CONTROLLER_0  = 0x46,
    SOUND_CONTROLLER_2  = 0x48,
    SOUND_CONTROLLER_3  = 0x49,
    SOUND_CONTROLLER_4  = 0x4A,
    SOUND_CONTROLLER_5  = 0x4B,
    SOUND_CONTROLLER_6  = 0x4C,
    SOUND_CONTROLLER_7  = 0x4D,
    SOUND_CONTROLLER_8  = 0x4E,
    SOUND_CONTROLLER_9  = 0x4F,
}sound_controller;

typedef enum
{
    GP_CONTROLLER_0   = 0x50,
    GP_CONTROLLER_1   = 0x51,
    GP_CONTROLLER_2   = 0x52,
    GP_CONTROLLER_3   = 0x53,
}general_purpose_controller;


typedef struct
{
    uint8_t     chanalNr;
    uint16_t    bankSelect;
    uint8_t     controllerNr;
    uint8_t     controllerVal;
    uint8_t     programNr;          // equals patch number
}midi_data;

} // namespace Midi_n


#endif /* MIDI_MIDI_DEFINES_HPP_ */
