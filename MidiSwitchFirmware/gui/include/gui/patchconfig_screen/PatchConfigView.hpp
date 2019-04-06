#ifndef PATCHCONFIG_VIEW_HPP
#define PATCHCONFIG_VIEW_HPP

#include <gui_generated/patchconfig_screen/PatchConfigViewBase.hpp>
#include <gui/patchconfig_screen/PatchConfigPresenter.hpp>

class PatchConfigView : public PatchConfigViewBase
{
public:
    PatchConfigView();
    virtual ~PatchConfigView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void progNrClickCallback(const ClickEvent&);

    void setConfigNumber(uint8_t configNr);

    void setProgramNumber(uint8_t programNr);

    void setController1Number(uint8_t controllerNr);

    void setController1Value(uint8_t controllerVal);

    void setController2Number(uint8_t controllerNr);

    void setController2Value(uint8_t controllerVal);

    void setDefaultOutputCfg(std::uint8_t value);

    void prevButtonActionCb(const AbstractButton& button);

    void nextButtonActionCb(const AbstractButton& button);

    void saveButtonActionCb(const AbstractButton& button);

    void defaultOutputCfgActionCb(const OutputCfg& outputCfg);

protected:
    touchgfx::Callback<PatchConfigView, const AbstractButton& > prevButtonCb;
    touchgfx::Callback<PatchConfigView, const AbstractButton& > nextButtonCb;
    touchgfx::Callback<PatchConfigView, const AbstractButton& > saveButtonCb;

    touchgfx::Callback<PatchConfigView,const ClickEvent& > progNrClickCb;
    touchgfx::Callback<PatchConfigView,const OutputCfg& > defaultOutputCfgCb;

};

#endif // PATCHCONFIG_VIEW_HPP
