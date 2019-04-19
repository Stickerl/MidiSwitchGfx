#include <gui/containers/numericKeyboard.hpp>
#include "string.h"

numericKeyboard::numericKeyboard() :
    readKeyCb(this, &numericKeyboard::readKeyCallback),
    cancleKeyCb(this, &numericKeyboard::cancelKeyCallback),
    returnKeyCb(this, &numericKeyboard::returnKeyCallback),
    wildcardSize(0),
    textWithOneWildcard(NULL),
    cancleCb(NULL),
    returnCb(NULL)
{
    key_0.setAction(readKeyCb);
    key_1.setAction(readKeyCb);
    key_2.setAction(readKeyCb);
    key_3.setAction(readKeyCb);
    key_4.setAction(readKeyCb);
    key_5.setAction(readKeyCb);
    key_6.setAction(readKeyCb);
    key_7.setAction(readKeyCb);
    key_8.setAction(readKeyCb);
    key_9.setAction(readKeyCb);
    cancel.setAction(cancleKeyCb);
    returnButton.setAction(returnKeyCb);
}

void numericKeyboard::initialize()
{
    numericKeyboardBase::initialize();
}

void numericKeyboard::initKeyboard(touchgfx::TextAreaWithOneWildcard* element, std::uint16_t charCnt)
{
    assert(NULL != element);
    if(NULL != textWithOneWildcard)
    {
        if(NULL != cancleCb) {
            cancleCb->execute(textWithOneWildcard);
        }
    }
    textWithOneWildcard = element;
    wildcardSize = charCnt;
    Unicode::UnicodeChar* wildcard = (Unicode::UnicodeChar*)textWithOneWildcard->getWildcard();
    memset(wildcard, 0, wildcardSize * sizeof(Unicode::UnicodeChar));
    setVisible(true);
    invalidate();
}

void numericKeyboard::setReturnCallback(touchgfx::GenericCallback<touchgfx::TextAreaWithOneWildcard* >& returnCallback) {
    returnCb = &returnCallback;
}

void numericKeyboard::setCancelCallback(touchgfx::GenericCallback<touchgfx::TextAreaWithOneWildcard* >& cancleCallback) {
    cancleCb = &cancleCallback;
}

void numericKeyboard::readKeyCallback(const AbstractButton& button)
{
    assert(NULL != textWithOneWildcard);
    int newNr = 0;
    if(&key_0 == &button){
        newNr = 0;
    }
    else if(&key_1 == &button){
        newNr = 1;
    }
    else if(&key_2 == &button){
        newNr = 2;
    }
    else if(&key_3 == &button){
        newNr = 3;
    }
    else if(&key_4 == &button){
        newNr = 4;
    }
    else if(&key_5 == &button){
        newNr = 5;
    }
    else if(&key_6 == &button){
        newNr = 6;
    }
    else if(&key_7 == &button){
        newNr = 7;
    }
    else if(&key_8 == &button){
        newNr = 8;
    }
    else if(&key_9 == &button){
        newNr = 9;
    }
    Unicode::UnicodeChar* wildcard = (Unicode::UnicodeChar*)textWithOneWildcard->getWildcard();
    std::uint16_t pos = Unicode::strlen(wildcard);
    if(pos < wildcardSize){
        Unicode::snprintf(&wildcard[pos], wildcardSize, "%i", newNr);
    }
    textWithOneWildcard->invalidate();
}

void numericKeyboard::cancelKeyCallback(const AbstractButton& button)
{
    if(NULL != cancleCb) {
        cancleCb->execute(textWithOneWildcard);
    }
    wildcardSize = 0;
    textWithOneWildcard = NULL;
    this->setVisible(false);
    this->invalidate();
}

void numericKeyboard::returnKeyCallback(const AbstractButton& button)
{
    if(NULL != returnCb) {
        returnCb->execute(textWithOneWildcard);
    }
    wildcardSize = 0;
    textWithOneWildcard = NULL;
    this->setVisible(false);
    this->invalidate();
}



