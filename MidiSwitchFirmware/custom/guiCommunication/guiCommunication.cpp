/*
 * guiCommunication.cpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#include "guiCommunication.hpp"
#include <string.h>
#include <new>

GuiCommunication::GuiCommunication(I_ConfigManager& configManager) :
    configChangedCb(this, &GuiCommunication::sendCurrentPatchData),
	globalConfigChangedCb(this, &GuiCommunication::sendGlobalCfg),
    cfgManager(configManager)
{
    configManager.setConfigChangedCb(configChangedCb);
    configManager.setGlobalConfigChangedCb(globalConfigChangedCb);
}

GuiCommunication::~GuiCommunication() {

}

void GuiCommunication::sendCurrentPatchData(I_ConfigManager& configManager){
    I_ConfigManager::programConfig_t& currentCfg = configManager.getCurrentCfg();
    patchCfgMsg& msgData = *(new(txMsg.data) patchCfgMsg);
    msgData.programNr = currentCfg.programNr;
    msgData.defaultOut = currentCfg.defaultOut;
    msgData.switch1Name = currentCfg.switches[0].switchName;
    msgData.switch1Output = currentCfg.switches[0].output;
    msgData.switch1Value = currentCfg.switches[0].switchOnVal;
    msgData.switch2Name = currentCfg.switches[1].switchName;
    msgData.switch2Output = currentCfg.switches[1].output;
    msgData.switch2Value = currentCfg.switches[1].switchOnVal;
    txMsg.name = GuiQueue::UPDATE_PATCH_CFG;
    queueToGui.sendElement(txMsg);
}

void GuiCommunication::sendGlobalCfg(I_ConfigManager& configManager)
{
	I_ConfigManager::actualGlobalCfg currentCfg = configManager.getGlobalCfg();
	globalCfgMsg& msgData = *(new(txMsg.data) globalCfgMsg);
	msgData.midiChanel = currentCfg.midiChannel;
	msgData.bankNr = currentCfg.bankNr;
	msgData.initialPatch = currentCfg.initialPatch;
	txMsg.name = GuiQueue::UPDATE_GLOBAL_CFG;
	queueToGui.sendElement(txMsg);
}

void GuiCommunication::run()
{
    if(true == queueToMidi.getElement(rxMsg))
    {
        switch(rxMsg.name)
        {
        case GuiQueue::PROG_NR:
            txMsg.name = GuiQueue::UPDATE_PATCH_CFG;
            cfgManager.switchCfg(reinterpret_cast<progNrMsg*>(rxMsg.data)->programNr);
            sendCurrentPatchData(cfgManager);
            break;

        case GuiQueue::SAVE_BUTTON:
            cfgManager.store();
            break;

        case GuiQueue::SWITCH_SETTING:
            cfgManager.setSwitchCfg(((switchSettingMsg*)rxMsg.data)->switchIndex,
                                    ((switchSettingMsg*)rxMsg.data)->switchNumber,
                                    ((switchSettingMsg*)rxMsg.data)->switchValue);
            break;

        case GuiQueue::OUTPUT_CFG:
            cfgManager.setOutputCfg(((outputCfgMsg*) rxMsg.data)->outputCfgNr,
                                    ((outputCfgMsg*) rxMsg.data)->outputVal);
            break;

        case GuiQueue::MIDI_CHANNEL:
        	cfgManager.setChanalNr(((midiChanMsg*)rxMsg.data)->midiChannel);
        	break;

        case GuiQueue::BANK_NR:
        	cfgManager.setBankNr(((bankNrMsg*)rxMsg.data)->bankNr);
        	break;

        default:
            // message unknown or not implemented
            break;
        }
    }
}
