/*
 * I_config_manager.hpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#ifndef I_CONFIG_MANAGER_HPP_
#define I_CONFIG_MANAGER_HPP_

#include "stdint.h"
#include "stddef.h"
#include "I_midi_callbacks.hpp"
#include "midi_defines.hpp"
#include <touchgfx/Callback.hpp>
#include "cstdint"


#define SWITCHES_PER_PROGRAM 2



class I_ConfigManager
{
public:
    typedef struct
    {
        std::uint8_t switchName;         // name / value of the switch
        std::uint8_t switchOnVal;        // value to trigger the output switch
        std::uint8_t output;             // output configuration to be set after the switchOnVal was received
    }switchCfg_t;

    typedef struct
    {
        std::uint8_t programNr;                              // number of the program
        std::uint8_t defaultOut;                             // default output configuration
        switchCfg_t switches[SWITCHES_PER_PROGRAM];     // array of switch configurations
    }programConfig_t;

    struct actualGlobalCfg
	{
    	std::uint8_t midiChannel;
    	std::uint16_t bankNr;
    	std::uint8_t initialPatch;
	};

    I_ConfigManager():
    	configChangedCb(NULL),
    	globalConfigChangedCb(NULL)
    {};

    virtual ~I_ConfigManager(){};

    virtual void store() = 0;                                           // stores a configuration in the flash
    virtual programConfig_t& getCurrentCfg() = 0;                       // getter for the reference to the currently active configuration
    virtual actualGlobalCfg getGlobalCfg() = 0;
    virtual programConfig_t& switchCfg(std::uint8_t programNr) = 0;          // interface to set a specific configuration active. returns the reference to the configuration
    virtual void setChanalNr(std::uint8_t chanalNr) = 0;                     // setter for the chanal number
    virtual void setBankNr(std::uint16_t bankNr) = 0;                        // setter for the bank number
    virtual void setInitialPatch(std::uint8_t patchNr) = 0;                  // setter for initial patch number
    virtual void setOutputCfg(std::uint8_t cfgNum, std::uint8_t value) = 0;
    virtual void setSwitchCfg(std::uint8_t index, std::uint8_t switchName, std::uint8_t switchOnVal) = 0;

    virtual void setConfigChangedCb(touchgfx::GenericCallback<I_ConfigManager& >& callback)
    {
        configChangedCb = &callback;
    }

    virtual void setGlobalConfigChangedCb(touchgfx::GenericCallback<I_ConfigManager& >& callback)
    {
        globalConfigChangedCb = &callback;
    }

protected:
    touchgfx::GenericCallback< I_ConfigManager& >* configChangedCb;
    touchgfx::GenericCallback< I_ConfigManager& >* globalConfigChangedCb;

};



#endif /* I_CONFIG_MANAGER_HPP_ */
