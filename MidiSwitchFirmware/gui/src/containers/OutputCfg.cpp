#include <gui/containers/OutputCfg.hpp>

OutputCfg::OutputCfg():
    value(0),
    readValueCb(this, &OutputCfg::readValueCallback),
    listenerCb(NULL)
{
    Out_0.setAction(readValueCb);
    Out_1.setAction(readValueCb);
    Out_2.setAction(readValueCb);
    Out_3.setAction(readValueCb);
    Out_4.setAction(readValueCb);
    Out_5.setAction(readValueCb);
    Out_6.setAction(readValueCb);
    Out_7.setAction(readValueCb);
}

void OutputCfg::setAction(touchgfx::GenericCallback<const OutputCfg& >& actionCb)
{
    listenerCb = &actionCb;
}

std::uint8_t OutputCfg::getValue() const
{
    return value;
}

void OutputCfg::setValue(std::uint8_t newValue)
{
    value = newValue;
    std::uint8_t tmp = value;
    Drawable* element = this->getFirstChild();
    while(NULL != element)
    {
        reinterpret_cast<ToggleButton*>(element)->forceState((tmp & 0x80) == 0x80);
        tmp <<= 1;
        element = element->getNextSibling();
    }
}

void OutputCfg::readValueCallback(const AbstractButton& button)
{
    uint8_t tmp = 0;
    uint8_t index = 7;
    Drawable* element = this->getFirstChild();
    while(NULL != element)
    {
        tmp |= reinterpret_cast<ToggleButton*>(element)->getState() << index;
        element = element->getNextSibling();
        index--;
    }
    value = tmp;
    if(NULL != listenerCb)
    {
        listenerCb->execute(*this);
    }
}



