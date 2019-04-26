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
    globalCfg{0},
    _flashUserId(flashUserId)
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::init()
{
    if((false == readGlobalSettings()) || (false == readCfgList())){
        // no config found => write a default config
        globalCfg.midiChannel = 0;
        globalCfg.bankNr = 0;
        globalCfg.initialPatch = 0;
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
    switchCfg(globalCfg.initialPatch);
    if(NULL != globalConfigChangedCb)
    {
        globalConfigChangedCb->execute(*this);
    }
}

void ConfigManager::store()
{
    storeGlobalSettings();
    storeCfgList();
}

void ConfigManager::program_change_cb(midi_data currentData)
{
    if ((currentData.chanalNr == globalCfg.midiChannel) && (currentData.bankSelect == globalCfg.bankNr))
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
    if ((currentData.chanalNr == globalCfg.midiChannel) && (currentData.bankSelect == globalCfg.bankNr))
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
        //configChangedCb->execute(*this); not clear whether GUI needs to be updated
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
    if(NULL != configChangedCb)
    {
    	configChangedCb->execute(*this);
    }
    return *currentCfg;
}

void ConfigManager::setChanalNr(std::uint8_t chanalNr)
{
    globalCfg.midiChannel = chanalNr;
    if(NULL != globalConfigChangedCb)
	{
		globalConfigChangedCb->execute(*this);
	}
}

void ConfigManager::setBankNr(std::uint16_t bankNr)
{
    globalCfg.bankNr = bankNr;
    if(NULL != globalConfigChangedCb)
	{
    	globalConfigChangedCb->execute(*this);
	}
}

void ConfigManager::setInitialPatch(std::uint8_t patchNr)
{
    globalCfg.initialPatch = patchNr;
    if(NULL != globalConfigChangedCb)
    {
        globalConfigChangedCb->execute(*this);
    }
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
    _flashManager.store(_flashUserId, (std::uint8_t*)&globalCfg, sizeof(globalCfg), GLOBAL_CFG_ADDR);
}

bool ConfigManager::readGlobalSettings()
{
    return _flashManager.read(_flashUserId, (std::uint8_t*)&globalCfg, sizeof(globalCfg), GLOBAL_CFG_ADDR);
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
    if(NULL != configChangedCb)
    {
        configChangedCb->execute(*this);
    }
}

void ConfigManager::setSwitchCfg(std::uint8_t index, std::uint8_t switchName, std::uint8_t switchOnVal)
{
    // TODO in case of invalid data ignore the change request
    currentCfg->switches[index].switchName = switchName;
    currentCfg->switches[index].switchOnVal = switchOnVal;
    if(NULL != configChangedCb)
    {
    	configChangedCb->execute(*this);
    }
}

ConfigManager::actualGlobalCfg ConfigManager::getGlobalCfg()
{
	return globalCfg;
}




