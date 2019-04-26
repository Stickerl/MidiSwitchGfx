#ifndef GLOBALCONFIG_VIEW_HPP
#define GLOBALCONFIG_VIEW_HPP

#include <gui_generated/globalconfig_screen/GlobalConfigViewBase.hpp>
#include <gui/globalconfig_screen/GlobalConfigPresenter.hpp>
#include "touch_event_extension.hpp"
#include "gui/containers/numericKeyboard.hpp"

class GlobalConfigView : public GlobalConfigViewBase
{
public:
    GlobalConfigView();
    virtual ~GlobalConfigView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void setMidiChanal(std::uint8_t midiChanal);
    void setBankNr(std::uint16_t bankNr);
    void setInitialPatch(std::uint8_t initialPatchNr);

    virtual void textClickActionCb(Drawable& textField, const ClickEvent& evt);
    virtual void textCancelActionCb(touchgfx::TextAreaWithOneWildcard* textField);
    virtual void textReturnActionCb(touchgfx::TextAreaWithOneWildcard* textField);

protected:
    touchgfx::Callback<GlobalConfigView, Drawable&, const ClickEvent& > textClickCb;
    touchgfx::Callback<GlobalConfigView, touchgfx::TextAreaWithOneWildcard* > textCancelCb;
    touchgfx::Callback<GlobalConfigView, touchgfx::TextAreaWithOneWildcard* > textReturnCb;
    touch_event_extension touchMidiChanal;
    touch_event_extension touchBankNr;
    touch_event_extension touchInitialPatch;
    numericKeyboard numericKeyboard1;

};

#endif // GLOBALCONFIG_VIEW_HPP
