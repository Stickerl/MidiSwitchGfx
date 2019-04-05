#include <gui/containers/OutputCfg.hpp>

OutputCfg::OutputCfg():
    value(0),
    readValueCb(this, &OutputCfg::readValue)
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

void OutputCfg::readValue(const AbstractButton& button)
{
    uint8_t tmp = 0;
    uint8_t index = 0;
    Drawable* element = this->getFirstChild();
    while(NULL != element)
    {
        tmp |= reinterpret_cast<ToggleButton*>(element)->getState() << index;
        element = element->getNextSibling();
        index++;
    }
    value = tmp; // TODO this value needs to be further comunicated!
}

