/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef PATCHCONFIG_VIEW_BASE_HPP
#define PATCHCONFIG_VIEW_BASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/patchconfig_screen/PatchConfigPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>

#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/containers/OutputCfg.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/containers/numericKeyboard.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>


// todo move this stuff out of the base class!
class touchableText : public touchgfx::TextAreaWithOneWildcard
{
public:
    void handleClickEvent(const ClickEvent& evt)
    {
        if(ClickEvent::RELEASED == evt.getType()){
            clickCallback->execute(evt);
        }
    }

    void setClickCb(touchgfx::GenericCallback<const ClickEvent& >& clickCb)
    {
        clickCallback = &clickCb;
    }
private:
    touchgfx::GenericCallback<const ClickEvent& >* clickCallback;
};


class PatchConfigViewBase : public touchgfx::View<PatchConfigPresenter>
{
public:
    PatchConfigViewBase();
    virtual ~PatchConfigViewBase() {}

    virtual void setupScreen();
    virtual void handleTickEvent();
    virtual void afterTransition();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image ConfigBG;
    touchgfx::Container ContrastBoxes;
    touchgfx::Box Switch2Box;
    touchgfx::Box Switch1Box;
    touchgfx::Box ProgrammBox;
    touchgfx::Box ConfigNrBox;
    touchgfx::Box HeadlineBox;

    touchgfx::Button Next;
    touchgfx::Button Prev;
    touchgfx::FadeAnimator< touchgfx::TextArea > Switch2Nr;
    touchgfx::FadeAnimator< touchgfx::TextArea > Switch1Nr;
    touchgfx::FadeAnimator< touchgfx::TextArea > ProgramNr;
    touchgfx::FadeAnimator< touchgfx::TextArea > PatchConfigHeadline;
    touchgfx::Container OutputBox;
    touchgfx::Box OutputCfgBox;
    touchgfx::TextArea OutputConfig;
    OutputCfg outputCfg_2;
    OutputCfg outputCfg_1;
    OutputCfg outputCfg_0;

    touchgfx::Button options;
    touchgfx::Button Save;
    touchgfx::ToggleButton TeachButton;
    touchgfx::Container SaveingPopUp;
    touchgfx::Box SaveingBox;
    touchgfx::TextArea Saveing;

    //touchgfx::TextAreaWithOneWildcard progNrVal;
    touchableText progNrVal; // todo move this stuff out of the base class!
    touchgfx::TextAreaWithOneWildcard switch1ConNrVal;
    touchgfx::TextAreaWithOneWildcard switch1ConValueVal;
    touchgfx::TextAreaWithOneWildcard switch2ConNrVal;
    touchgfx::TextAreaWithOneWildcard switch2ConValueVal;
    touchgfx::FadeAnimator< touchgfx::TextArea > DefaultOutput;
    numericKeyboard numericKeyboard1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t PROGNRVAL_SIZE = 4;
    touchgfx::Unicode::UnicodeChar progNrValBuffer[PROGNRVAL_SIZE];
    static const uint16_t SWITCH1CONNRVAL_SIZE = 3;
    touchgfx::Unicode::UnicodeChar switch1ConNrValBuffer[SWITCH1CONNRVAL_SIZE];
    static const uint16_t SWITCH1CONVALUEVAL_SIZE = 3;
    touchgfx::Unicode::UnicodeChar switch1ConValueValBuffer[SWITCH1CONVALUEVAL_SIZE];
    static const uint16_t SWITCH2CONNRVAL_SIZE = 3;
    touchgfx::Unicode::UnicodeChar switch2ConNrValBuffer[SWITCH2CONNRVAL_SIZE];
    static const uint16_t SWITCH2CONVALUEVAL_SIZE = 3;
    touchgfx::Unicode::UnicodeChar switch2ConValueValBuffer[SWITCH2CONVALUEVAL_SIZE];

private:

    /*
     * Interaction Handlers
     */
    void headlinFadeEndedCallbackHandler(const touchgfx::FadeAnimator<touchgfx::TextArea>& comp);
    void programmFadeEndedCallbackHandler(const touchgfx::FadeAnimator<touchgfx::TextArea>& comp);
    void switch1FadeEndedCallbackHandler(const touchgfx::FadeAnimator<touchgfx::TextArea>& comp);
    void switch2FadeEndedCallbackHandler(const touchgfx::FadeAnimator<touchgfx::TextArea>& comp);
    void defaultOutputFadeEndedCallbackHandler(const touchgfx::FadeAnimator<touchgfx::TextArea>& comp);

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Delay Variable Declarations
     */
    static const uint16_t SAVINGDELAY_DURATION = 60;
    uint16_t savingDelayCounter;

    /*
     * Callback Declarations
     */
    touchgfx::Callback<PatchConfigViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Interaction Callback Declarations
     */
    touchgfx::Callback < PatchConfigViewBase, const touchgfx::FadeAnimator<touchgfx::TextArea>& >  headlinFadeEndedCallback;
    touchgfx::Callback < PatchConfigViewBase, const touchgfx::FadeAnimator<touchgfx::TextArea>& >  programmFadeEndedCallback;
    touchgfx::Callback < PatchConfigViewBase, const touchgfx::FadeAnimator<touchgfx::TextArea>& >  switch1FadeEndedCallback;
    touchgfx::Callback < PatchConfigViewBase, const touchgfx::FadeAnimator<touchgfx::TextArea>& >  switch2FadeEndedCallback;
    touchgfx::Callback < PatchConfigViewBase, const touchgfx::FadeAnimator<touchgfx::TextArea>& >  defaultOutputFadeEndedCallback;

};

#endif // PATCHCONFIG_VIEW_BASE_HPP
