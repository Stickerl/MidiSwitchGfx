#include <gui/patchconfig_screen/PatchConfigView.hpp>

PatchConfigView::PatchConfigView()
{

}

void PatchConfigView::setupScreen()
{

}

void PatchConfigView::tearDownScreen()
{

}

void PatchConfigView::setProgramNumber(uint8_t programNr)
{
	Unicode::snprintf(progNrValBuffer, PROGNRVAL_SIZE, "%i", programNr);
	progNrVal.invalidate();
}

void PatchConfigView::setControllerNumber(uint8_t controllerNr)
{
	Unicode::snprintf(switch1ConNrValBuffer, SWITCH1CONNRVAL_SIZE, "%i", controllerNr);
	switch1ConNrVal.invalidate();
}

void PatchConfigView::setControllerValue(uint8_t controllerVal)
{
	Unicode::snprintf(switch1ConValueValBuffer, SWITCH1CONVALUEVAL_SIZE, "%i", controllerVal);
	switch1ConValueVal.invalidate();
}

