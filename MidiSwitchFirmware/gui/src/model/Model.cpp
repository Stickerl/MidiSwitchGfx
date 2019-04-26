#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <new>


Model::Model() :
modelListener(0),
_queToMidi(GuiQueue::getQueToMidiRef()),
_queToGui(GuiQueue::getQueToGuiRef()),
patchCfgData{0},
globalCfgData{0}
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

        case GuiQueue::UPDATE_GLOBAL_CFG:
            memcpy(&globalCfgData, rxMsg.data, sizeof(globalCfgData));
            modelListener->globalConfigChanged();
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
    progNrMsg& payload = *(new(txMsg.data) progNrMsg);
    if(patchCfgData.programNr == 0)
    {
        payload.programNr = (NUMBER_OF_PROGRAMS - 1);
    }
    else
    {
        payload.programNr = patchCfgData.programNr - 1;
    }
    _queToMidi.sendElement(txMsg);
}


void Model::requestProgramNrIncrement()
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::PROG_NR;
    progNrMsg& payload = *(new(txMsg.data) progNrMsg);
    if(patchCfgData.programNr >= (NUMBER_OF_PROGRAMS - 1))
    {
        payload.programNr = 0;
    }
    else
    {
        payload.programNr = patchCfgData.programNr + 1;
    }
    _queToMidi.sendElement(txMsg);
}

void Model::requestOutputChange(std::uint8_t rowNr, std::uint8_t newVal)
{
    GuiQueue::GuiMessage_t txMsg;
    outputCfgMsg& payload = *(new(txMsg.data) outputCfgMsg);
    payload.outputCfgNr = rowNr;
    payload.outputVal = newVal;
    txMsg.name = GuiQueue::OUTPUT_CFG;
    _queToMidi.sendElement(txMsg);
}

void Model::requestGeneralSave()
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::SAVE_BUTTON;
    _queToMidi.sendElement(txMsg);
}

void Model::requestProgNrChange(std::uint8_t newVal)
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::PROG_NR;
    progNrMsg& payload = *(new(txMsg.data) progNrMsg);
    payload.programNr = newVal;
    _queToMidi.sendElement(txMsg);
}

void Model::requestSwitchNrChange(std::uint8_t switchIndex, std::uint8_t switchNr)
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::SWITCH_SETTING;
    switchSettingMsg& payload = *(new(txMsg.data) switchSettingMsg);
    payload.switchIndex = switchIndex;
    payload.switchNumber = switchNr;
    payload.switchValue = (0 == switchIndex) ? patchCfgData.switch1Value : patchCfgData.switch2Value;
    _queToMidi.sendElement(txMsg);
}

void Model::requestSwitchValChange(std::uint8_t switchIndex, std::uint8_t newVal)
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::SWITCH_SETTING;
    switchSettingMsg& payload = *(new(txMsg.data) switchSettingMsg);
    payload.switchIndex = switchIndex;
    payload.switchNumber = (0 == switchIndex) ? patchCfgData.switch1Name : patchCfgData.switch2Name;
    payload.switchValue = newVal;
    _queToMidi.sendElement(txMsg);
}

void Model::requestMidiChannelChange(std::uint8_t newMidiChannel)
{
	GuiQueue::GuiMessage_t txMsg;
	txMsg.name = GuiQueue::MIDI_CHANNEL;
	midiChanMsg& payload = *(new(txMsg.data) midiChanMsg);
	payload.midiChannel = newMidiChannel;
	_queToMidi.sendElement(txMsg);
}

void Model::requestBankNrChange(std::uint16_t newBankNr)
{
	GuiQueue::GuiMessage_t txMsg;
	txMsg.name = GuiQueue::BANK_NR;
	bankNrMsg& payload = *(new(txMsg.data) bankNrMsg);
	payload.bankNr = newBankNr;
	_queToMidi.sendElement(txMsg);
}

void Model::requestInitialPatchChange(std::uint8_t newInitalPatchNr)
{
    GuiQueue::GuiMessage_t txMsg;
    txMsg.name = GuiQueue::INITIAL_PATCH;
    initalPatchNrMsg& payload = *(new(txMsg.data) initalPatchNrMsg);
    payload.initialPatchNr = newInitalPatchNr;
    _queToMidi.sendElement(txMsg);
}

patchCfgMsg Model::getPatchCfgData()
{
    return patchCfgData;
}

globalCfgMsg Model::getGlobalCfgData()
{
	return globalCfgData;
}

