/*
 * config_manager.cpp
 *
 * Created: 8/25/2018 3:57:32 PM
 *  Author: Erwin
 */

#include "config_manager.hpp"


ConfigManager::ConfigManager(I_Flash& flashManager):
    _flashManager(flashManager),
    currentCfg(0),
    _bankNr(0),
    _chanalNr(0)
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::init()
{
    readGlobalSettings();
    readCfgList();
}

void ConfigManager::store()
{
    storeGlobalSettings();
    storeCfgList();
}

void ConfigManager::program_change_cb(midi_data currentData)
{
    if ((currentData.chanalNr == _chanalNr) && (currentData.bankSelect == _bankNr))
    {
        bool found = false;
        for (uint8_t i = 0; i < NUMBER_OF_PROGRAMS; i++)
        {
            if (currentData.programNr == ramCfgList[i].progrmNr)
            {
                // load the configuration
                switchCfg(currentData.programNr);
                setOutput(currentCfg->defaultOut);
                found = true;
                break;
            }
        }
        // TODO Teach function is missing!
    }
}

void ConfigManager::control_change_cb(midi_data currentData)
{
    uint8_t newOutState = 0;
    if ((currentData.chanalNr == _chanalNr) && (currentData.bankSelect == _bankNr))
    {
        for(uint8_t index = 0; index < SWITCHES_PER_PROGRAM; index++)
        {
            if(currentData.controllerNr == currentCfg->switches[index].switchName)
            {
                if(currentData.controllerVal == currentCfg->switches[index].switchOnVal)
                {
                    // set the output to the value configured for this switch
                    newOutState = currentCfg->switches[index].output;
                }
                else
                {
                    // reset the output to default
                    newOutState = currentCfg->defaultOut;
                }
            }
        }
        setOutput(newOutState);
        // TODO Teach function is missing!
    }
}

I_ConfigManager::programConfig_t& ConfigManager::getCurrentCfg()
{
    return (ramCfgList[currentCfg->progrmNr]);
}

I_ConfigManager::programConfig_t& ConfigManager::switchCfg(uint8_t programNr)
{
    currentCfg = &ramCfgList[programNr];
    return getCurrentCfg();
}

void ConfigManager::setChanalNr(uint8_t chanalNr)
{
    _chanalNr = chanalNr;
}

void ConfigManager::setBankNr(uint16_t bankNr)
{
    _bankNr = bankNr;
}


void ConfigManager::readCfg(uint8_t index)
{
    uint32_t readAddr = CFG_STORAGE_ADDR;
    readAddr += CFG_SIZE * (index+1);
    _flashManager.readBytes(readAddr, ((uint8_t*)&ramCfgList[index]), CFG_SIZE);
}

void ConfigManager::readCfgList()
{
    _flashManager.readBytes(CFG_STORAGE_ADDR, (uint8_t*)ramCfgList, (CFG_SIZE * NUMBER_OF_PROGRAMS));
}

void ConfigManager::storeCfg(uint8_t index)
{
    uint32_t writeAddr = CFG_STORAGE_ADDR;
    writeAddr += CFG_SIZE * (index+1);
    _flashManager.writeBytes(writeAddr, ((uint8_t*)&ramCfgList[index]), CFG_SIZE);
}

void ConfigManager::storeCfgList()
{
    _flashManager.readBytes(CFG_STORAGE_ADDR, (uint8_t*)ramCfgList, (CFG_SIZE * NUMBER_OF_PROGRAMS));
}

void ConfigManager::storeGlobalSettings()
{
    _flashManager.writeWords(BANK_NR_STORE_ADDR, &_bankNr, 1);
    _flashManager.writeBytes(CHANAL_NR_STORE_ADDR, &_chanalNr, 1);
}

void ConfigManager::readGlobalSettings()
{
    _flashManager.readWords(BANK_NR_STORE_ADDR, &_bankNr, 1);
    _flashManager.readBytes(CHANAL_NR_STORE_ADDR, &_chanalNr, 1);
}

void ConfigManager::setOutput(uint8_t out)
{

}







