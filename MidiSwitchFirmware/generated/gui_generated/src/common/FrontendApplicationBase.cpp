/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <new>
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Texts.hpp>
#include <gui/welcome_screen/WelcomeView.hpp>
#include <gui/welcome_screen/WelcomePresenter.hpp>
#include <gui/patchconfig_screen/PatchConfigView.hpp>
#include <gui/patchconfig_screen/PatchConfigPresenter.hpp>
#include <gui/globalconfig_screen/GlobalConfigView.hpp>
#include <gui/globalconfig_screen/GlobalConfigPresenter.hpp>

using namespace touchgfx;


FrontendApplicationBase::FrontendApplicationBase(Model& m, FrontendHeap& heap)
    : touchgfx::MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
    Texts::setLanguage(GB);
}

/*
 * Screen Transition Declarations
 */
// Welcome

void FrontendApplicationBase::gotoWelcomeScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplication::gotoWelcomeScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoWelcomeScreenNoTransitionImpl()
{
    makeTransition<WelcomeView, WelcomePresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// PatchConfig

void FrontendApplicationBase::gotoPatchConfigScreenSlideTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplication::gotoPatchConfigScreenSlideTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoPatchConfigScreenSlideTransitionWestImpl()
{
    makeTransition<PatchConfigView, PatchConfigPresenter, touchgfx::SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}


void FrontendApplicationBase::gotoPatchConfigScreenSlideTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplication::gotoPatchConfigScreenSlideTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoPatchConfigScreenSlideTransitionEastImpl()
{
    makeTransition<PatchConfigView, PatchConfigPresenter, touchgfx::SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// GlobalConfig

void FrontendApplicationBase::gotoGlobalConfigScreenSlideTransitionNorth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplication::gotoGlobalConfigScreenSlideTransitionNorthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoGlobalConfigScreenSlideTransitionNorthImpl()
{
    makeTransition<GlobalConfigView, GlobalConfigPresenter, touchgfx::SlideTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

