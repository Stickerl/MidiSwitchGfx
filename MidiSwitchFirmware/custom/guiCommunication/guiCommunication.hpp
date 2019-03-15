/*
 * guiCommunication.hpp
 *
 *  Created on: Mar 15, 2019
 *      Author: Erwin
 */

#ifndef GUICOMMUNICATION_GUICOMMUNICATION_HPP_
#define GUICOMMUNICATION_GUICOMMUNICATION_HPP_

#include "I_config_manager.hpp"
#include <touchgfx/Callback.hpp>
#include "gui_queue.h"

class GuiCommunication {
public:
    GuiCommunication(I_ConfigManager& configManager);
    virtual ~GuiCommunication();
    void sendCurrentPatchData(const I_ConfigManager& configManager);

private:
    touchgfx::Callback<GuiCommunication, const I_ConfigManager& > configChangedCb;
    GuiQueue& queueToGui = GuiQueue::getQueToGuiRef();
    GuiQueue::GuiMessage_t txMsg;
};

#endif /* GUICOMMUNICATION_GUICOMMUNICATION_HPP_ */
