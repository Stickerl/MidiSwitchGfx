/*
 * guiCommunication.cpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#include "guiCommunication.hpp"
#include <string.h>

GuiCommunication::GuiCommunication(I_ConfigManager& configManager) :
    configChangedCb(this, &GuiCommunication::sendCurrentPatchData),
    cfgManager(configManager)
{
    configManager.setConfigChangedCb(configChangedCb);
}

GuiCommunication::~GuiCommunication() {
    // TODO Auto-generated destructor stub
}

void GuiCommunication::sendCurrentPatchData(I_ConfigManager& configManager){
    I_ConfigManager::programConfig_t& currentCfg = configManager.getCurrentCfg();
    patchCfgMsg msgData;
    msgData.programNr = currentCfg.programNr;
    msgData.defaultOut = currentCfg.defaultOut;
    msgData.switch1Name = currentCfg.switches[0].switchName;
    msgData.switch1Output = currentCfg.switches[0].output;
    msgData.switch1Value = currentCfg.switches[0].switchOnVal;
    msgData.switch2Name = currentCfg.switches[1].switchName;
    msgData.switch2Output = currentCfg.switches[1].output;
    msgData.switch2Value = currentCfg.switches[1].switchOnVal;
    txMsg.name = GuiQueue::UPDATE_PATCH_CFG;
    memcpy(txMsg.data, &msgData, sizeof(patchCfgMsg));
    queueToGui.sendElement(txMsg);
}


void GuiCommunication::run()
{
    if(queueToMidi.getElement(rxMsg) == true)
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
            // TODO: Nix gut!! :(
            break;

        case GuiQueue::OUTPUT_CFG:
            cfgManager.setOutputCfg(((outputCfgMsg*) rxMsg.data)->outputCfgNr,
                                    ((outputCfgMsg*) rxMsg.data)->outputVal);
            break;

        default:
            // message unknown or not implemented
            break;
        }
    }
}
