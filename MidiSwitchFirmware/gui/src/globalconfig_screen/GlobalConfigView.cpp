#include <gui/globalconfig_screen/GlobalConfigView.hpp>

GlobalConfigView::GlobalConfigView():
    touchMidiChanal(MidiChannelVal),
    touchBankNr(BankNrVal),
    numericKeyboard1(),
    textClickCb(this, &GlobalConfigView::textClickActionCb),
    textCancelCb(this, &GlobalConfigView::textCancelActionCb),
    textReturnCb(this, &GlobalConfigView::textReturnActionCb)
{
    touchMidiChanal.setReleasedCb(textClickCb);
    touchBankNr.setReleasedCb(textClickCb);
    add(touchMidiChanal);
    add(touchBankNr);
    add(numericKeyboard1);
    numericKeyboard1.setXY(250, 329);
    numericKeyboard1.setVisible(false);
    numericKeyboard1.setReturnCallback(textReturnCb);
}

void GlobalConfigView::setupScreen()
{

}

void GlobalConfigView::tearDownScreen()
{

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
    numericKeyboard1.initKeyboard(reinterpret_cast <TextAreaWithOneWildcard*> (&textField), numDigits);
}

void GlobalConfigView::textCancelActionCb(Drawable& textField, const ClickEvent& evt)
{

}
void GlobalConfigView::textReturnActionCb(TextAreaWithOneWildcard* textField)
{

}
