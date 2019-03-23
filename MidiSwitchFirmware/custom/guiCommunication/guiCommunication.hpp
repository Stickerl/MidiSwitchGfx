/*
 * guiCommunication.hpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#ifndef GUICOMMUNICATION_HPP_
#define GUICOMMUNICATION_HPP_

#include "I_config_manager.hpp"
#include <touchgfx/Callback.hpp>
#include "gui_queue.h"

class GuiCommunication {
public:
    GuiCommunication(I_ConfigManager& configManager);
    virtual ~GuiCommunication();
    void sendCurrentPatchData(I_ConfigManager& configManager);
    void run();

private:
    touchgfx::Callback<GuiCommunication, I_ConfigManager& > configChangedCb;
    // set up the connection to the gui via queues
    GuiQueue& queueToGui = GuiQueue::getQueToGuiRef();
    GuiQueue& queueToMidi = GuiQueue::getQueToMidiRef();
    GuiQueue::GuiMessage_t txMsg;
    GuiQueue::GuiMessage_t rxMsg;
    I_ConfigManager& cfgManager;

};

#endif /* GUICOMMUNICATION_HPP_ */
