/*
 * I_config_manager.hpp
 *
 *  Created on: Aug 25, 2018
 *      Author: Erwin
 */

#ifndef CONFIG_MANAGER_I_CONFIG_MANAGER_HPP_
#define CONFIG_MANAGER_I_CONFIG_MANAGER_HPP_

#include "stdint.h"


#define SWITCHES_PER_PROGRAM

class I_ConfigManager
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
    virtual ~I_ConfigManager();

    virtual void store(programConfig_t progCfg) = 0;    // stores a configuration in the flash

};



#endif /* CONFIG_MANAGER_I_CONFIG_MANAGER_HPP_ */
