#ifndef WELCOME_VIEW_HPP
#define WELCOME_VIEW_HPP

#include <gui_generated/welcome_screen/WelcomeViewBase.hpp>
#include <gui/welcome_screen/WelcomePresenter.hpp>

class WelcomeView : public WelcomeViewBase
{
public:
    WelcomeView();
    virtual ~WelcomeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // WELCOME_VIEW_HPP
