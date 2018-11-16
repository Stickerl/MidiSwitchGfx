#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>



Model::Model() :
modelListener(0),
configNr(0),
_queToMidi(GuiQueue::getQueToMidiRef()),
_queToGui(GuiQueue::getQueToGuiRef())
{
	midiData.controllerNr = 0;
	midiData.chanalNr = 0;
	midiData.controllerVal = 0;
	midiData.programNr = 0;
}

void Model::tick()
{
	modelListener->controllerNumberChanged();
	modelListener->bankSelectionChanged();
	modelListener->controllerValueChanged();
	modelListener->configNumberChanged();

	GuiQueue::GuiMessage_t rxMsg;
	if(_queToGui.getElement(rxMsg) == true)
	{
	    switch(rxMsg.name)
	    {
	    case GuiQueue::PROG_NR:
	        midiData.programNr = rxMsg.data[0];
	        displayedCfg.programNr = rxMsg.data[0];
	        modelListener->programNumberChanged();
	        break;
	    default:
	        // message unknown or not implemented
	        break;
	    }
	}
}

uint8_t Model::getControllerNumber()
{
	return midiData.chanalNr;
}

uint16_t Model::getConfigNumber()
{
	return displayedCfg.programNr;
}

uint8_t Model::getControllerValue()
{
	return displayedCfg.switches[0].switchOnVal;
}

uint8_t Model::getProgramNumber()
{
	return displayedCfg.programNr;
}

void Model::respondMidiState(I_ConfigManager::programConfig_t& newConfig)
{

    displayedCfg.programNr = newConfig.programNr;
    displayedCfg.defaultOut = newConfig.defaultOut;
    for(uint8_t i = 0; i < 2; i++)
    {
        displayedCfg.switches[i].switchName = newConfig.switches[i].switchName;
        displayedCfg.switches[i].switchOnVal = newConfig.switches[i].switchOnVal;
        displayedCfg.switches[i].output = newConfig.switches[i].output;
    }
    modelListener->configNumberChanged();
    modelListener->programNumberChanged();
}


void Model::requestProgramNrDecrement()
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::PROG_NR;
    if(midiData.programNr == 0)
    {
        midiData.programNr = (NUMBER_OF_PROGRAMS - 1);
    }
    else
    {
        midiData.programNr--;
    }
    txMsg.data[0] = midiData.programNr;
    _queToMidi.sendElement(txMsg);
}


void Model::requestProgramNrIncrement()
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::PROG_NR;
    if(midiData.programNr == (NUMBER_OF_PROGRAMS - 1))
    {
        midiData.programNr = 0;
    }
    else
    {
        midiData.programNr++;
    }
    txMsg.data[0] = midiData.programNr;
    _queToMidi.sendElement(txMsg);
}


