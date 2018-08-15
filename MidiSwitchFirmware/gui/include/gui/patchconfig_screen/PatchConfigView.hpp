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

    void setConfigNumber(uint8_t configNr);

    void setProgramNumber(uint8_t programNr);

    void setControllerNumber(uint8_t controllerNr);

    void setControllerValue(uint8_t controllerVal);

protected:
};

#endif // PATCHCONFIG_VIEW_HPP
