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
	return configNr;
}

uint8_t Model::getControllerValue()
{
	return midiData.controllerVal;
}

uint8_t Model::getProgramNumber()
{
	return midiData.programNr;
}