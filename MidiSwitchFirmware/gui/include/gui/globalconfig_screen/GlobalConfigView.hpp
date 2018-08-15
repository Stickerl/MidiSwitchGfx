#ifndef GLOBALCONFIG_VIEW_HPP
#define GLOBALCONFIG_VIEW_HPP

#include <gui_generated/globalconfig_screen/GlobalConfigViewBase.hpp>
#include <gui/globalconfig_screen/GlobalConfigPresenter.hpp>

class GlobalConfigView : public GlobalConfigViewBase
{
public:
    GlobalConfigView();
    virtual ~GlobalConfigView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // GLOBALCONFIG_VIEW_HPP
