#include <gui/patchconfig_screen/PatchConfigView.hpp>

PatchConfigView::PatchConfigView():
    prevButtonCb(this, &PatchConfigView::prevButtonActionCb),
    nextButtonCb(this, &PatchConfigView::nextButtonActionCb),
    saveButtonCb(this, &PatchConfigView::saveButtonActionCb),
    progNrClickCb(this, &PatchConfigView::progNrClickCallback),
    defaultOutputCfgCb(this, &PatchConfigView::defaultOutputCfgActionCb)
{
	// event registrations
    Prev.setAction(prevButtonCb);
    Next.setAction(nextButtonCb);
    Save.setAction(saveButtonCb);
    //progNrVal.setClickCb(progNrClickCb);
    outputCfg_0.setAction(defaultOutputCfgCb);
	
    progNrVal.setTouchable(true);

}

void PatchConfigView::setupScreen()
{
    presenter->patchConfigChanged();
}

void PatchConfigView::tearDownScreen()
{

}

void PatchConfigView::progNrClickCallback(const ClickEvent&)
{
    numericKeyboard1.initKeyboard(&progNrVal, PROGNRVAL_SIZE);
    numericKeyboard1.invalidate();
}

void PatchConfigView::setProgramNumber(uint8_t programNr)
{
	Unicode::snprintf(progNrValBuffer, PROGNRVAL_SIZE, "%i", programNr);
	progNrVal.invalidate();
}

void PatchConfigView::setController1Number(uint8_t controllerNr)
{
	Unicode::snprintf(switch1ConNrValBuffer, SWITCH1CONNRVAL_SIZE, "%i", controllerNr);
	switch1ConNrVal.invalidate();
}

void PatchConfigView::setController1Value(uint8_t controllerVal)
{
	Unicode::snprintf(switch1ConValueValBuffer, SWITCH1CONVALUEVAL_SIZE, "%i", controllerVal);
	switch1ConValueVal.invalidate();
}

void PatchConfigView::setController2Number(uint8_t controllerNr)
{
    Unicode::snprintf(switch2ConNrValBuffer, SWITCH2CONNRVAL_SIZE, "%i", controllerNr);
    switch2ConNrVal.invalidate();
}

void PatchConfigView::setController2Value(uint8_t controllerVal)
{
    Unicode::snprintf(switch2ConValueValBuffer, SWITCH2CONVALUEVAL_SIZE, "%i", controllerVal);
    switch2ConValueVal.invalidate();
}

void PatchConfigView::setDefaultOutputCfg(std::uint8_t value)
{
    outputCfg_0.setValue(value);
}

void PatchConfigView::prevButtonActionCb(const AbstractButton& button)
{
    presenter->prevButtonPressed();
}

void PatchConfigView::nextButtonActionCb(const AbstractButton& button)
{
    presenter->nextButtonPressed();
}

void PatchConfigView::saveButtonActionCb(const AbstractButton& button)
{
    presenter->saveButtonPressed();
}

void PatchConfigView::defaultOutputCfgActionCb(const OutputCfg& outputCfg)
{
    std::uint8_t tmp = outputCfg.getValue();
    presenter->defaultOutputChanged(tmp);
}

