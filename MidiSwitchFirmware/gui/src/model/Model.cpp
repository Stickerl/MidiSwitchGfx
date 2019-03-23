#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>



Model::Model() :
modelListener(0),
_queToMidi(GuiQueue::getQueToMidiRef()),
_queToGui(GuiQueue::getQueToGuiRef()),
patchCfgData{0}
{

}

void Model::tick()
{
    GuiQueue::GuiMessage_t rxMsg;
    if(_queToGui.getElement(rxMsg) == true)
    {
        switch(rxMsg.name)
        {
        case GuiQueue::UPDATE_PATCH_CFG:
            memcpy(&patchCfgData, rxMsg.data, sizeof(patchCfgData));
            modelListener->patchConfigChanged();
            break;

        default:
            // message unknown or not implemented
            break;
        }
    }
}

void Model::requestProgramNrDecrement()
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::PROG_NR;
    if(patchCfgData.programNr == 0)
    {
        patchCfgData.programNr = (NUMBER_OF_PROGRAMS - 1);
    }
    else
    {
        patchCfgData.programNr--;
    }
    txMsg.data[0] = patchCfgData.programNr;
    _queToMidi.sendElement(txMsg);
}


void Model::requestProgramNrIncrement()
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::PROG_NR;
    if(patchCfgData.programNr >= (NUMBER_OF_PROGRAMS - 1))
    {
        patchCfgData.programNr = 0;
    }
    else
    {
        patchCfgData.programNr++;
    }
    txMsg.data[0] = patchCfgData.programNr;
    _queToMidi.sendElement(txMsg);
}


patchCfgMsg Model::getPatchCfgData(){
    return patchCfgData;
}

