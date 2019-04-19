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
    virtual void textClickActionCb(Drawable& textField, const ClickEvent& evt);
    virtual void textCancelActionCb(Drawable& textField, const ClickEvent& evt);
    virtual void textReturnActionCb(touchgfx::TextAreaWithOneWildcard* textField);
protected:
    touchgfx::Callback<GlobalConfigView, Drawable&, const ClickEvent& > textClickCb;
    touchgfx::Callback<GlobalConfigView, Drawable&, const ClickEvent& > textCancelCb;
    touchgfx::Callback<GlobalConfigView, touchgfx::TextAreaWithOneWildcard* > textReturnCb;
    touch_event_extension touchMidiChanal;
    touch_event_extension touchBankNr;
    numericKeyboard numericKeyboard1;

};

#endif // GLOBALCONFIG_VIEW_HPP
