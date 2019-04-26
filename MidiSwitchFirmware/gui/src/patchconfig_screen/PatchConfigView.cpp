#include <gui/patchconfig_screen/PatchConfigView.hpp>
#include <cstdio>

PatchConfigView::PatchConfigView():
    prevButtonCb(this, &PatchConfigView::prevButtonActionCb),
    nextButtonCb(this, &PatchConfigView::nextButtonActionCb),
    saveButtonCb(this, &PatchConfigView::saveButtonActionCb),
    returnKeyCb(this, &PatchConfigView::keyboardReturnActionCb),
    cancelKeyCb(this, &PatchConfigView::keyboardCancleActionCb),
    textClickCb(this, &PatchConfigView::textClickActionCb),
    outputCfgCb(this, &PatchConfigView::outputCfgActionCb),
    touchProgNrVal(progNrVal),
    touchSwitch1ConNrVal(switch1ConNrVal),
    touchSwitch1ConValueVal(switch1ConValueVal),
    touchSwitch2ConNrVal(switch2ConNrVal),
    touchSwitch2ConValueVal(switch2ConValueVal),
    savingPopUpCounter(0)
{
	// event registrations
    Prev.setAction(prevButtonCb);
    Next.setAction(nextButtonCb);
    Save.setAction(saveButtonCb);
    numericKeyboard1.setVisible(false);
    numericKeyboard1.setReturnCallback(returnKeyCb);
    numericKeyboard1.setCancelCallback(cancelKeyCb);

    touchProgNrVal.setReleasedCb(textClickCb);
    touchSwitch1ConNrVal.setReleasedCb(textClickCb);
    touchSwitch1ConValueVal.setReleasedCb(textClickCb);
    touchSwitch2ConNrVal.setReleasedCb(textClickCb);
    touchSwitch2ConValueVal.setReleasedCb(textClickCb);
    add(touchProgNrVal);
    add(touchSwitch1ConNrVal);
    add(touchSwitch1ConValueVal);
    add(touchSwitch2ConNrVal);
    add(touchSwitch2ConValueVal);

    outputCfg_0.setAction(outputCfgCb);
    outputCfg_1.setAction(outputCfgCb);
    outputCfg_2.setAction(outputCfgCb);
}

void PatchConfigView::handleTickEvent()
{
    PatchConfigViewBase::handleTickEvent();
    if(savingPopUpCounter > 0)
    {
        savingPopUpCounter--;
        if(savingPopUpCounter == 0)
        {
            SaveingPopUp.setVisible(false);
            SaveingPopUp.invalidate();
        }
    }

}

void PatchConfigView::setupScreen()
{
    presenter->patchConfigChanged();
}

void PatchConfigView::tearDownScreen()
{

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
    outputCfg_0.invalidate();
}

void PatchConfigView::setSwitch1OutputCfg(std::uint8_t value)
{
    outputCfg_1.setValue(value);
    outputCfg_1.invalidate();
}

void PatchConfigView::setSwitch2OutputCfg(std::uint8_t value)
{
    outputCfg_2.setValue(value);
    outputCfg_2.invalidate();
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
    savingPopUpCounter = 60;    // equals 1s at 60 fps
    SaveingPopUp.setVisible(true);
    SaveingPopUp.invalidate();
}

void PatchConfigView::outputCfgActionCb(const OutputCfg& outputCfg)
{
    std::uint8_t outPutRowNr;
    if(&outputCfg == &outputCfg_0){
        outPutRowNr = 0;
    }
    else if(&outputCfg == &outputCfg_1){
        outPutRowNr = 1;
    }
    else if(&outputCfg == &outputCfg_2){
        outPutRowNr = 2;
    }

    presenter->outputChanged(outPutRowNr, outputCfg.getValue());
}

void PatchConfigView::textClickActionCb(Drawable& objRev, const ClickEvent& evt)
{
    std::uint16_t maxCharCnt = 0;
    if(&objRev == &progNrVal) {
        maxCharCnt = PROGNRVAL_SIZE;
    }
    else if(&objRev == &switch1ConNrVal) {
        maxCharCnt = SWITCH1CONNRVAL_SIZE;
    }
    else if(&objRev == &switch1ConValueVal) {
        maxCharCnt = SWITCH1CONVALUEVAL_SIZE;
    }
    else if(&objRev == &switch2ConNrVal) {
        maxCharCnt = SWITCH2CONNRVAL_SIZE;
    }
    else if(&objRev == &switch2ConValueVal) {
        maxCharCnt = SWITCH2CONVALUEVAL_SIZE;
    }
    numericKeyboard1.initKeyboard((touchgfx::TextAreaWithOneWildcard*)&objRev, maxCharCnt);
    numericKeyboard1.invalidate();
}

void PatchConfigView::keyboardReturnActionCb(touchgfx::TextAreaWithOneWildcard* element) {
    std::uint8_t inputVal = Unicode::atoi(element->getWildcard());
    if(element == &progNrVal) {
        presenter->progNrChanged(inputVal);
    }
    else if(element == &switch1ConNrVal) {
        presenter->switchNrChanged(0, inputVal);
    }
    else if(element == &switch1ConValueVal) {
        presenter->switchValChanged(0, inputVal);
    }
    else if(element == &switch2ConNrVal) {
        presenter->switchNrChanged(1, inputVal);
    }
    else if(element == &switch2ConValueVal) {
        presenter->switchValChanged(1, inputVal);
    }
}

void PatchConfigView::keyboardCancleActionCb(touchgfx::TextAreaWithOneWildcard* element) {
    if(element == &progNrVal) {

    }
    else if(element == &switch1ConNrVal) {

    }
    else if(element == &switch1ConValueVal) {

    }
    else if(element == &switch2ConNrVal) {

    }
    else if(element == &switch2ConValueVal) {

    }
    presenter->restorePatchConfig();
}


