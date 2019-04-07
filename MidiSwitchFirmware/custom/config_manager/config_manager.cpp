/*
 * config_manager.cpp
 *
 * Created: 8/25/2018 3:57:32 PM
 *  Author: Erwin
 */

#include "config_manager.hpp"


ConfigManager::ConfigManager(I_Flash& flashManager, std::uint16_t flashUserId):
    _flashManager(flashManager),
    currentCfg(0),
    _bankNr(0),
    _chanalNr(0),
    _flashUserId(flashUserId),
    _startupProgNr(0)
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::init()
{
    if((false == readGlobalSettings()) || (false == readCfgList())){
        // no config found => write a default config
        _chanalNr = 0;
        _bankNr = 0;
        _startupProgNr = 42;
        for(std::uint8_t i = 0U; i < (sizeof(ramCfgList)/sizeof(ramCfgList[0])); i++){
            ramCfgList[i].programNr = i;
            ramCfgList[i].defaultOut = 0;
            ramCfgList[i].switches[0].output = 0;
            ramCfgList[i].switches[0].switchName = 0;
            ramCfgList[i].switches[0].switchOnVal = 0;
            ramCfgList[i].switches[1].output = 0;
            ramCfgList[i].switches[1].switchName = 0;
            ramCfgList[i].switches[1].switchOnVal = 0;
        }
        store();
    }
    switchCfg(_startupProgNr);
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
        for (std::uint8_t i = 0; i < NUMBER_OF_PROGRAMS; i++)
        {
            if (currentData.programNr == ramCfgList[i].programNr)
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
    std::uint8_t newOutState = 0;
    if ((currentData.chanalNr == _chanalNr) && (currentData.bankSelect == _bankNr))
    {
        for(std::uint8_t index = 0; index < SWITCHES_PER_PROGRAM; index++)
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
        //configChangedCb->execute(*this); not clear whether GUI need to be updated
        // TODO Teach function is missing!
    }
}

I_ConfigManager::programConfig_t& ConfigManager::getCurrentCfg()
{
    return *currentCfg;
}

I_ConfigManager::programConfig_t& ConfigManager::switchCfg(std::uint8_t programNr)
{
    currentCfg = &ramCfgList[programNr];
    configChangedCb->execute(*this);
    return *currentCfg;
}

void ConfigManager::setChanalNr(std::uint8_t chanalNr)
{
    _chanalNr = chanalNr;
}

void ConfigManager::setBankNr(std::uint16_t bankNr)
{
    _bankNr = bankNr;
}

void ConfigManager::readCfg(std::uint8_t index)
{
    std::uint32_t readAddr = CFG_STORAGE_ADDR;
    readAddr += CFG_SIZE * (index+1);
    _flashManager.read(_flashUserId, ((std::uint8_t*)&ramCfgList[index]), CFG_SIZE, readAddr);
}

bool ConfigManager::readCfgList()
{
    return _flashManager.read(_flashUserId, (std::uint8_t*)ramCfgList, (CFG_SIZE * NUMBER_OF_PROGRAMS), CFG_STORAGE_ADDR);
}

void ConfigManager::storeCfg(std::uint8_t index)
{
    std::uint32_t writeAddr = CFG_STORAGE_ADDR;
    writeAddr += CFG_SIZE * (index+1);
    _flashManager.store(_flashUserId, ((std::uint8_t*)&ramCfgList[index]), CFG_SIZE, writeAddr);
}

void ConfigManager::storeCfgList()
{
    _flashManager.store(_flashUserId, (std::uint8_t*)ramCfgList, (CFG_SIZE * NUMBER_OF_PROGRAMS), CFG_STORAGE_ADDR);
}

void ConfigManager::storeGlobalSettings()
{
    // TODO use one store statement (each statement writes one container to the flash!)
    _flashManager.store(_flashUserId, (std::uint8_t*)&_bankNr, sizeof(_bankNr), BANK_NR_STORE_ADDR);
    _flashManager.store(_flashUserId, (std::uint8_t*)&_chanalNr, sizeof(_chanalNr), CHANAL_NR_STORE_ADDR);
    _flashManager.store(_flashUserId, (std::uint8_t*)&_startupProgNr, sizeof(_startupProgNr), STARTUP_PROG_NR);
}

bool ConfigManager::readGlobalSettings()
{
    bool ret = _flashManager.read(_flashUserId, (std::uint8_t*)&_bankNr, sizeof(_bankNr), BANK_NR_STORE_ADDR);
    _flashManager.read(_flashUserId, (std::uint8_t*)&_chanalNr, sizeof(_chanalNr), CHANAL_NR_STORE_ADDR);
    _flashManager.read(_flashUserId, (std::uint8_t*)&_startupProgNr, sizeof(_startupProgNr), STARTUP_PROG_NR);
    return ret;
}

void ConfigManager::setOutput(std::uint8_t out)
{

}

void ConfigManager::setOutputCfg(std::uint8_t cfgNum, std::uint8_t value)
{
    if(0 == cfgNum)
    {
        currentCfg->defaultOut = value;
    }
    else
    {
        currentCfg->switches[cfgNum - 1].output = value;
    }
}

void ConfigManager::setSwitchCfg(std::uint8_t index, std::uint8_t switchName, std::uint8_t switchOnVal)
{
    // TODO in case of invalid data ignore the change request
    currentCfg->switches[index].switchName = switchName;
    currentCfg->switches[index].switchOnVal = switchOnVal;
    configChangedCb->execute(*this);
}




