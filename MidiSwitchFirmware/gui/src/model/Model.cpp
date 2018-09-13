#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>



Model::Model() :
modelListener(0),
configNr(0)
{
	midiData.controllerNr = 0;
	midiData.chanalNr = 0;
	midiData.controllerVal = 0;
	midiData.programNr = 0;
}

void Model::tick()
{
	midiData.controllerNr++;
	midiData.controllerVal = 132;
	midiData.programNr = 51;
	configNr--;

	modelListener->controllerNumberChanged();
	modelListener->bankSelectionChanged();
	modelListener->controllerValueChanged();
	modelListener->programNumberChanged();
	modelListener->configNumberChanged();
}

uint8_t Model::getControllerNumber()
{
	return midiData.chanalNr;
}

uint16_t Model::getConfigNumber()
{
	return displayedCfg.progrmNr;
}

uint8_t Model::getControllerValue()
{
	return displayedCfg.switches[0].switchOnVal;
}

uint8_t Model::getProgramNumber()
{
	return displayedCfg.progrmNr;
}

void Model::pushMidiState(I_ConfigManager::programConfig_t& newConfig)
{

    displayedCfg.progrmNr = newConfig.progrmNr;
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


