#ifndef OUTPUTCFG_HPP
#define OUTPUTCFG_HPP

#include <gui_generated/containers/OutputCfgBase.hpp>

class OutputCfg : public OutputCfgBase
{
public:
    OutputCfg();
    virtual ~OutputCfg() {}
    virtual void setAction(touchgfx::GenericCallback<const OutputCfg& >& actionCb);
    virtual std::uint8_t getValue() const;
    virtual void setValue(std::uint8_t newValue);

protected:
    std::uint8_t value;
    touchgfx::Callback<OutputCfg, const AbstractButton& > readValueCb;
    touchgfx::GenericCallback<const OutputCfg& >* listenerCb;

    void readValueCallback(const AbstractButton& button);
};

#endif // OUTPUTCFG_HPP
