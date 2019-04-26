#ifndef PATCHCONFIG_VIEW_HPP
#define PATCHCONFIG_VIEW_HPP

#include <gui_generated/patchconfig_screen/PatchConfigViewBase.hpp>
#include <gui/patchconfig_screen/PatchConfigPresenter.hpp>
#include "touch_event_extension.hpp"

class PatchConfigView : public PatchConfigViewBase
{
public:
    PatchConfigView();
    virtual ~PatchConfigView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    void setConfigNumber(uint8_t configNr);

    void setProgramNumber(uint8_t programNr);

    void setController1Number(uint8_t controllerNr);

    void setController1Value(uint8_t controllerVal);

    void setController2Number(uint8_t controllerNr);

    void setController2Value(uint8_t controllerVal);

    void setDefaultOutputCfg(std::uint8_t value);

    void setSwitch1OutputCfg(std::uint8_t value);

    void setSwitch2OutputCfg(std::uint8_t value);

    void prevButtonActionCb(const AbstractButton& button);

    void nextButtonActionCb(const AbstractButton& button);

    void saveButtonActionCb(const AbstractButton& button);

    void outputCfgActionCb(const OutputCfg& outputCfg);

    // keyboard realated callbacks
    void textClickActionCb(Drawable& objRev, const ClickEvent& evt);

    void keyboardReturnActionCb(touchgfx::TextAreaWithOneWildcard* element);

    void keyboardCancleActionCb(touchgfx::TextAreaWithOneWildcard* element);

protected:
    touchgfx::Callback<PatchConfigView, const AbstractButton& > prevButtonCb;
    touchgfx::Callback<PatchConfigView, const AbstractButton& > nextButtonCb;
    touchgfx::Callback<PatchConfigView, const AbstractButton& > saveButtonCb;
    touchgfx::Callback<PatchConfigView, touchgfx::TextAreaWithOneWildcard* > returnKeyCb;
    touchgfx::Callback<PatchConfigView, touchgfx::TextAreaWithOneWildcard* > cancelKeyCb;
    touchgfx::Callback<PatchConfigView, Drawable&, const ClickEvent& > textClickCb;
    touchgfx::Callback<PatchConfigView, const OutputCfg& > outputCfgCb;

    touch_event_extension touchProgNrVal;
    touch_event_extension touchSwitch1ConNrVal;
    touch_event_extension touchSwitch1ConValueVal;
    touch_event_extension touchSwitch2ConNrVal;
    touch_event_extension touchSwitch2ConValueVal;

    std::uint16_t savingPopUpCounter;


};

#endif // PATCHCONFIG_VIEW_HPP
