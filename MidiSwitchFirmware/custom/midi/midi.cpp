/*
 * midi.c
 *
 * Created: 2/25/2018 8:15:53 PM
 *  Author: Erwin
 */ 

#include "midi.hpp"
#include "stddef.h"

namespace Midi_n
{


MidiDecoder::MidiDecoder(I_RingBuffer& midiRxBuffer, uint32_t& sysTime, uint32_t timeout):
    _midiRxBuffer(midiRxBuffer),
    _sysTime(sysTime),
    _timeout(timeout),
    mainState(WAIT_ON_MESSAGE),
    prevTimeStamp(0)
{
    _midiRxBuffer.clear();
    _programmChange = NULL;
    _controlChange = NULL;
}

void MidiDecoder::decode()
{
    uint16_t byteCnt = _midiRxBuffer.get_cnt();
    uint8_t byte = 0x00;

    if ((_sysTime - prevTimeStamp) > _timeout)
    {
        mainState = WAIT_ON_MESSAGE;    // reset the statemachine and ignore previous data
    }

    if(byteCnt > 0)
    {
        prevTimeStamp = _sysTime;
    }

    for (uint16_t i = 0; i < byteCnt; i++)
    {
        _midiRxBuffer.get_from_buffer(&byte, 1);
        switch (mainState)
        {
            case WAIT_ON_MESSAGE:
                if((byte & 0xF0) == MIDI_CONROL_CHANGE)
                {
                    curData.chanalNr = (byte & 0x0F);               // save the chanal number
                    mainState = CONTROL_CHANGE;
                }
                else if ((byte & 0xF0) == MIDI_PROGRAM_CHANGE)
                {
                    curData.chanalNr = (byte & 0x0F);               // save the chanal number
                    mainState = PROGRAM_CHANGE;
                }
                else{}                                              // any other command was received
                break;

            case PROGRAM_CHANGE:
                curData.programNr = byte;
                if(_programmChange != NULL)
                {
                    _programmChange->program_change_cb(curData);     // call the program (patch) change callback and pass the current data
                }
                mainState = WAIT_ON_MESSAGE;                        // message was processed completely => wait for the next one
                break;

            case CONTROL_CHANGE:
                if (byte == MIDI_BANK_SELECT_MSB)
                {
                    mainState = BANK_SELECT_MSB;
                }
                else if (byte == MIDI_BANK_SELECT_LSB)
                {
                    mainState = BANK_SELECT_LSB;
                }
                else if (((byte >= SOUND_CONTROLLER_0) & (byte <= SOUND_CONTROLLER_9)) |
                         ((byte >= GP_CONTROLLER_0) & (byte <= GP_CONTROLLER_3)))
                {
                    curData.controllerNr = byte;
                    mainState = CONTROLLER_NR;
                }
                else
                {
                    // message unknown => wait on the next massage
                    mainState = WAIT_ON_MESSAGE;
                }
                break;

            case BANK_SELECT_LSB:
                // set the low byte of bank select
                curData.bankSelect = (curData.bankSelect & 0xFF00) | byte;
                mainState = WAIT_ON_MESSAGE;        // message was processed completely => wait for the next one
                break;

            case BANK_SELECT_MSB:
                // set the high byte of bank select
                curData.bankSelect = (curData.bankSelect & 0x00FF) | (((uint16_t) byte) << 8);
                mainState = WAIT_ON_MESSAGE;        // message was processed completely => wait for the next one
                break;

            case CONTROLLER_NR:
                // save the controller number
                curData.controllerVal = byte;
                if(_controlChange != NULL)
                {
                    _controlChange->control_change_cb(curData);  // call the control change callback and pass the current data
                }
                mainState = WAIT_ON_MESSAGE;                    // message was processed completely => wait for the next one
                break;

            default:
                // command unknown => reset the state machine
                mainState = WAIT_ON_MESSAGE;
                break;
        }
    }
}

void MidiDecoder::register_control_change_cb(I_MidiControlChangeCb* callBack)
{
    _controlChange = callBack;
}

void MidiDecoder::register_program_change_cb(I_MidiProgrammChangeCb* callBack)
{
    _programmChange = callBack;
}

} // namespace Midi_n


