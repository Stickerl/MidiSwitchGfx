/*
 * I_config_manager.hpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#ifndef CONFIG_MANAGER_I_CONFIG_MANAGER_HPP_
#define CONFIG_MANAGER_I_CONFIG_MANAGER_HPP_

#include "stdint.h"
#include "I_midi_callbacks.hpp"
#include "midi_defines.hpp"


#define SWITCHES_PER_PROGRAM 2



class I_ConfigManager: public I_MidiControlChangeCb, public I_MidiProgrammChangeCb
{
public:
    typedef struct
    {
        uint8_t switchName;         // name / value of the switch
        uint8_t switchOnVal;        // value to trigger the output switch
        uint8_t output;             // output configuration to be set after the switchOnVal was received
    }switchCfg_t;

    typedef struct
    {
        uint8_t progrmNr;                               // number of the program
        uint8_t defaultOut;                             // default output configuration
        switchCfg_t switches[SWITCHES_PER_PROGRAM];     // array of switch configurations
    }programConfig_t;

    I_ConfigManager(){};
    virtual ~I_ConfigManager(){};

    virtual void store() = 0;                                           // stores a configuration in the flash
    virtual void program_change_cb(midi_data currentData);              // implements the callback interface for the program change signal
    virtual void control_change_cb(midi_data currentData);              // implements the callback interface for the conrol change signal
    virtual programConfig_t& getCurrentCfg() = 0;                       // getter for the reference to the currently active configuration
    virtual programConfig_t& switchCfg(uint8_t programNr) = 0;          // interface to set a specific configuration active. returns the reference to the configuration
    virtual void setChanalNr(uint8_t chanalNr) = 0;                     // setter for the chanal number
    virtual void setBankNr(uint16_t bankNr) = 0;                        // setter for the bank number


};



#endif /* CONFIG_MANAGER_I_CONFIG_MANAGER_HPP_ */