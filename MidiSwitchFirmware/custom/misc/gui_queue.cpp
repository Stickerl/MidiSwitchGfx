/*
 * gui_queue.cpp
 *
 *  Created on: Oct 20, 2018
 *      Author: Erwin
 */

#include <gui_queue.h>

const uint32_t GuiQueue::QUEUE_ITEM_SIZE = sizeof(GuiMessage_t);
const uint32_t GuiQueue::QUEUE_LENGTH = 10;


GuiQueue queueToGui;
GuiQueue queueToMidi;

GuiQueue::GuiQueue():
    _queue(xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE))
{

}

GuiQueue::~GuiQueue()
{
    vQueueDelete(_queue);
}

bool GuiQueue::getElement(GuiMessage_t& rxMsg)
{
    bool ret = true;
    if(xQueueReceive(_queue, &rxMsg, 0) != pdTRUE)
    {
        ret = false;
    }
    return ret;
}

bool GuiQueue::sendElement(GuiMessage_t txMsg)
{
    bool ret = true;
    if(xQueueSendToBack(_queue, &txMsg, 0) != pdTRUE)
    {
        ret = false;
    }
    return ret;
}

GuiQueue& GuiQueue::getQueToGuiRef()
{
    return queueToGui;
}

GuiQueue& GuiQueue::getQueToMidiRef()
{
    return queueToMidi;
}
