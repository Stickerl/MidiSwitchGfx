#ifndef PATCHCONFIG_PRESENTER_HPP
#define PATCHCONFIG_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "guiMessageDefinitions.hpp"

using namespace touchgfx;

class PatchConfigView;

class PatchConfigPresenter : public Presenter, public ModelListener
{
public:
    PatchConfigPresenter(PatchConfigView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~PatchConfigPresenter() {};

    virtual void prevButtonPressed();

    virtual void nextButtonPressed();

    virtual void saveButtonPressed();

    virtual void patchConfigChanged();

    virtual void defaultOutputChanged(std::uint8_t newVal);

private:
    PatchConfigPresenter();

    PatchConfigView& view;
};


#endif // PATCHCONFIG_PRESENTER_HPP
