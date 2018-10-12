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


class ConfigManager : public I_ConfigManager, public I_MidiControlChangeCb, public I_MidiProgrammChangeCb
{

public:
    ConfigManager(I_Flash& flashManager);
    virtual ~ConfigManager();

    void init();     // reads the configuration list from the flash and sets the output to the configured default
    void store();    // stores the ram configuration list in the flash
    void program_change_cb(midi_data currentData);  // implements the callback interface for the program change signal
    void control_change_cb(midi_data currentData);  // implements the callback interface for the conrol change signal
    programConfig_t& getCurrentCfg();                       // getter for the reference to the currently active configuration
    programConfig_t& switchCfg(uint8_t programNr);          // interface to set a specific configuration active. returns the reference to the configuration
    void setChanalNr(uint8_t chanalNr);                     // setter for the chanal number
    void setBankNr(uint16_t bankNr);                        // setter for the bank number

private:
    static const uint16_t NUMBER_OF_PROGRAMS = 128;
    static const uint32_t CFG_STORAGE_ADDR = 0;
    static const uint32_t BANK_NR_STORE_ADDR = 0;
    static const uint32_t CHANAL_NR_STORE_ADDR = 0;

    programConfig_t ramCfgList[NUMBER_OF_PROGRAMS];
    static const uint32_t CFG_SIZE = sizeof(ramCfgList[0]);
    I_Flash& _flashManager;
    programConfig_t* currentCfg;
    uint8_t _chanalNr;
    uint16_t _bankNr;


    void readCfg(uint8_t index);                    // reads a specific configuration from flash to the ramCfgList
    void readCfgList();                             // reads all configurations from flash to the ramCfgList
    void readGlobalSettings();                      // reads the global settings from flash
    void storeCfg(uint8_t index);                   // stores a specific configuration from the ram list to the flash
    void storeCfgList();                            // stores the whole list in the flash
    void storeGlobalSettings();                     // stores the global settings into flash
    void setOutput(uint8_t out);                    // sets the outputs

};



#endif // CONFIG_MANAGER_HPP_


