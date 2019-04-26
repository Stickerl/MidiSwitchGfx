/*
 * gui_queue.h
 *
 *  Created on: Oct 20, 2018
 *      Author: Erwin
 */

#ifndef MISC_GUI_QUEUE_H_
#define MISC_GUI_QUEUE_H_

#include "stdint.h"
#include "string.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "guiMessageDefinitions.hpp"


class GuiQueue {
public:
    static const uint32_t QUEUE_LENGTH;
    static const uint32_t QUEUE_DATA_LENGTH = 16;

    // Message names
    typedef enum
    {
        NONE              = 0,
        PROG_NR           = 1,
        SWITCH_SETTING    = 2,
        OUTPUT_CFG        = 3,
        TEACH_BUTTON      = 4,
        SAVE_BUTTON       = 5,
        OPTIONS_BUTON     = 6,
        UPDATE_PATCH_CFG  = 7,
		MIDI_CHANNEL	  = 8,
		BANK_NR			  = 9,
		UPDATE_GLOBAL_CFG = 10
    }GuiControls;

    typedef struct GuiMessage
    {
        GuiControls name;
        uint8_t data[QUEUE_DATA_LENGTH];
        GuiMessage():name(GuiControls::NONE), data{0}{};
        GuiMessage(GuiControls name_in, uint8_t data_in[QUEUE_DATA_LENGTH]):
            name(name_in)
            {
                memcpy(data, data_in, sizeof(data));
            }
    }GuiMessage_t;

    GuiQueue();
    virtual ~GuiQueue();

    bool getElement(GuiMessage_t& rxMsg);
    bool sendElement(GuiMessage_t txMsg);
    static GuiQueue& getQueToGuiRef();
    static GuiQueue& getQueToMidiRef();

private:
    static const uint32_t QUEUE_ITEM_SIZE;

    xQueueHandle _queue;

};



#endif /* MISC_GUI_QUEUE_H_ */
