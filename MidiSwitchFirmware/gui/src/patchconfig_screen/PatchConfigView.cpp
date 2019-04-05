#include <gui/patchconfig_screen/PatchConfigView.hpp>

PatchConfigView::PatchConfigView():
    prevButtonCb(this, &PatchConfigView::prevButtonActionCb),
    nextButtonCb(this, &PatchConfigView::nextButtonActionCb),
    progNrClickCb(this, &PatchConfigView::progNrClickCallback)
{
    Prev.setAction(prevButtonCb);
    Next.setAction(nextButtonCb);
    numericKeyboard1.initKeyboard(&progNrVal, PROGNRVAL_SIZE);
    numericKeyboard1.invalidate();
    progNrVal.setTouchable(true);
    progNrVal.setClickCb(progNrClickCb);
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

void PatchConfigView::prevButtonActionCb(const AbstractButton& button)
{
    presenter->prevButtonPressed();
}

void PatchConfigView::nextButtonActionCb(const AbstractButton& button)
{
    presenter->nextButtonPressed();
}

