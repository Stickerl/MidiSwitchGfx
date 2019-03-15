/*
 * guiCommunication.cpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#include "guiCommunication.hpp"
#include <string.h>

GuiCommunication::GuiCommunication(I_ConfigManager& configManager) :
    configChangedCb(this, &GuiCommunication::sendCurrentPatchData)
{
    configManager.setConfigChangedCb(configChangedCb);

}

GuiCommunication::~GuiCommunication() {
    // TODO Auto-generated destructor stub
}

void GuiCommunication::sendCurrentPatchData(const I_ConfigManager& configManager){
    I_ConfigManager::programConfig_t& currentCfg = configManager.getCurrentCfg();
    updatePatchCfgMsg msgData;
    msgData.programNr = currentCfg.programNr;
    msgData.defaultOut = currentCfg.defaultOut;
    msgData.switch1Name = currentCfg.switches[0].switchName;
    msgData.switch1Output = currentCfg.switches[0].output;
    msgData.switch1Value = currentCfg.switches[0].switchOnVal;
    msgData.switch2Name = currentCfg.switches[1].switchName;
    msgData.switch2Output = currentCfg.switches[1].output;
    msgData.switch2Value = currentCfg.switches[1].switchOnVal;
    txMsg.name = GuiQueue::UPDATE_PATCH_CFG;
    memcpy(txMsg.data, &msgData, sizeof(updatePatchCfgMsg));
    queueToGui.sendElement(txMsg);
}
