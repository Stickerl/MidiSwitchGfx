#include <gui/globalconfig_screen/GlobalConfigView.hpp>
#include <cstdio>

GlobalConfigView::GlobalConfigView():
    touchMidiChanal(MidiChannelVal),
    touchBankNr(BankNrVal),
    touchInitialPatch(InitialPatchVal),
    numericKeyboard1(),
    textClickCb(this, &GlobalConfigView::textClickActionCb),
    textCancelCb(this, &GlobalConfigView::textCancelActionCb),
    textReturnCb(this, &GlobalConfigView::textReturnActionCb)
{
    touchMidiChanal.setReleasedCb(textClickCb);
    touchBankNr.setReleasedCb(textClickCb);
    touchInitialPatch.setReleasedCb(textClickCb);
    add(touchMidiChanal);
    add(touchBankNr);
    add(touchInitialPatch);
    add(numericKeyboard1);
    numericKeyboard1.setXY(250, 329);
    numericKeyboard1.setVisible(false);
    numericKeyboard1.setCancelCallback(textCancelCb);
    numericKeyboard1.setReturnCallback(textReturnCb);
}

void GlobalConfigView::setupScreen()
{

}

void GlobalConfigView::tearDownScreen()
{

}

void GlobalConfigView::setMidiChanal(std::uint8_t midiChanal)
{
	Unicode::snprintf((Unicode::UnicodeChar*) MidiChannelVal.getWildcard(), MIDICHANNELVAL_SIZE, "%i", midiChanal);
	MidiChannelVal.invalidate();
}

void GlobalConfigView::setBankNr(std::uint16_t bankNr)
{
	Unicode::snprintf((Unicode::UnicodeChar*) BankNrVal.getWildcard(), BANKNRVAL_SIZE, "%i", bankNr);
	BankNrVal.invalidate();
}

void GlobalConfigView::setInitialPatch(std::uint8_t initialPatchNr)
{
    Unicode::snprintf((Unicode::UnicodeChar*) InitialPatchVal.getWildcard(), INITIALPATCHVAL_SIZE, "%i", initialPatchNr);
    InitialPatchVal.invalidate();
}

void GlobalConfigView::textClickActionCb(Drawable& textField, const ClickEvent& evt)
{
    std::uint16_t numDigits = 0;

    if(&textField == &MidiChannelVal)
    {
        numDigits = MIDICHANNELVAL_SIZE;
    }
    if(&textField == &BankNrVal)
    {
        numDigits = BANKNRVAL_SIZE;
    }
    if(&textField == &InitialPatchVal)
    {
        numDigits = INITIALPATCHVAL_SIZE;
    }
    numericKeyboard1.initKeyboard(reinterpret_cast <TextAreaWithOneWildcard*> (&textField), numDigits);
}

void GlobalConfigView::textCancelActionCb(TextAreaWithOneWildcard* textField)
{
	presenter->restoreGlobalConfig();
}

void GlobalConfigView::textReturnActionCb(TextAreaWithOneWildcard* textField)
{
	std::uint16_t inputVal = Unicode::atoi(textField->getWildcard());
	    if(textField == &MidiChannelVal) {
	        presenter->midiChannelChanged(static_cast<std::uint8_t>(inputVal));
	    }
	    else if(textField == &BankNrVal) {
	        presenter->bankNrChanged(inputVal);
	    }
	    else if(textField == &InitialPatchVal){
	        presenter->initalPatchChanged(static_cast<std::uint8_t>(inputVal));
	    }
}
