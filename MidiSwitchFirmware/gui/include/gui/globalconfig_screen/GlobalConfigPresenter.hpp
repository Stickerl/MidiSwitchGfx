#ifndef GLOBALCONFIG_PRESENTER_HPP
#define GLOBALCONFIG_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GlobalConfigView;

class GlobalConfigPresenter : public Presenter, public ModelListener
{
public:
    GlobalConfigPresenter(GlobalConfigView& v);

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

    virtual ~GlobalConfigPresenter() {};

private:
    GlobalConfigPresenter();

    GlobalConfigView& view;
};


#endif // GLOBALCONFIG_PRESENTER_HPP
