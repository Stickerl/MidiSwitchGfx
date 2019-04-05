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

    void readKeyCallback(const AbstractButton& button);
    void cancelCallback(const AbstractButton& button);
    void returnCallback(const AbstractButton& button);

protected:
    touchgfx::Callback<numericKeyboard, const AbstractButton& > readKeyCb;
    touchgfx::Callback<numericKeyboard, const AbstractButton& > cancleCb;
    touchgfx::Callback<numericKeyboard, const AbstractButton& > returnCb;
    touchgfx::TextAreaWithOneWildcard* textWithOneWildcard;
    std::uint16_t wildcardSize;
};

#endif // NUMERICKEYBOARD_HPP
