/*
 * config_manager.hpp
 *
 * Created: 8/25/2018 3:57:00 PM
 *  Author: Erwin
 */


#ifndef CONFIG_MANAGER_HPP_
#define CONFIG_MANAGER_HPP_

#include "I_config_manager.hpp"
#include "I_flash.hpp"
#include "global_defines.hpp"
#include <cstdint>



class ConfigManager : public I_ConfigManager, public I_MidiControlChangeCb, public I_MidiProgrammChangeCb
{

public:
    ConfigManager(I_Flash& flashManager, std::uint16_t flashUserId);
    virtual ~ConfigManager();

    void init();     // reads the configuration list from the flash and sets the output to the configured default
    void store();    // stores the ram configuration list in the flash
    void program_change_cb(midi_data currentData);          // implements the callback interface for the program change signal
    void control_change_cb(midi_data currentData);          // implements the callback interface for the conrol change signal
    programConfig_t& getCurrentCfg();                       // getter for the reference to the currently active configuration
    actualGlobalCfg getGlobalCfg();
    programConfig_t& switchCfg(std::uint8_t programNr);          // interface to set a specific configuration active. returns the reference to the configuration
    void setChanalNr(std::uint8_t chanalNr);                     // setter for the chanal number
    void setBankNr(std::uint16_t bankNr);                        // setter for the bank number
    void setInitialPatch(std::uint8_t patchNr);                  // setter for initial patch number
    void setOutputCfg(std::uint8_t cfgNum, std::uint8_t value);
    void setSwitchCfg(std::uint8_t index, std::uint8_t switchName, std::uint8_t switchOnVal);

private:
    actualGlobalCfg globalCfg;
    static const std::uint32_t GLOBAL_CFG_ADDR = 0;
    static const std::uint32_t CFG_STORAGE_ADDR = GLOBAL_CFG_ADDR + sizeof(globalCfg);
    const std::uint16_t _flashUserId;

    programConfig_t ramCfgList[NUMBER_OF_PROGRAMS];
    static const std::uint32_t CFG_SIZE = sizeof(programConfig_t);
    I_Flash& _flashManager;
    programConfig_t* currentCfg;


    void readCfg(std::uint8_t index);                    // reads a specific configuration from flash to the ramCfgList
    bool readCfgList();                             // reads all configurations from flash to the ramCfgList
    bool readGlobalSettings();                      // reads the global settings from flash
    void storeCfg(std::uint8_t index);                   // stores a specific configuration from the ram list to the flash
    void storeCfgList();                            // stores the whole list in the flash
    void storeGlobalSettings();                     // stores the global settings into flash
    void setOutput(std::uint8_t out);                    // sets the outputs

};



#endif // CONFIG_MANAGER_HPP_


