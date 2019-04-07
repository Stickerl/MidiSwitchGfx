#ifndef NUMERICKEYBOARD_HPP
#define NUMERICKEYBOARD_HPP

#include <gui_generated/containers/numericKeyboardBase.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class numericKeyboard : public numericKeyboardBase
{
public:
    numericKeyboard();
    virtual ~numericKeyboard() {}

    virtual void initialize();

    void initKeyboard(touchgfx::TextAreaWithOneWildcard* element, std::uint16_t charCnt);

    void setReturnCallback(touchgfx::GenericCallback<touchgfx::TextAreaWithOneWildcard* >& returnCallback);
    void setCancelCallback(touchgfx::GenericCallback<touchgfx::TextAreaWithOneWildcard* >& cancleCallback);

protected:
    touchgfx::Callback<numericKeyboard, const AbstractButton& > readKeyCb;
    touchgfx::Callback<numericKeyboard, const AbstractButton& > cancleKeyCb;
    touchgfx::Callback<numericKeyboard, const AbstractButton& > returnKeyCb;
    touchgfx::GenericCallback<touchgfx::TextAreaWithOneWildcard* >* cancleCb;
    touchgfx::GenericCallback<touchgfx::TextAreaWithOneWildcard* >* returnCb;
    touchgfx::TextAreaWithOneWildcard* textWithOneWildcard;
    std::uint16_t wildcardSize;

    void readKeyCallback(const AbstractButton& button);
    void cancelKeyCallback(const AbstractButton& button);
    void returnKeyCallback(const AbstractButton& button);
};

#endif // NUMERICKEYBOARD_HPP
