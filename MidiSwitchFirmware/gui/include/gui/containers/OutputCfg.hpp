#ifndef OUTPUTCFG_HPP
#define OUTPUTCFG_HPP

#include <gui_generated/containers/OutputCfgBase.hpp>

class OutputCfg : public OutputCfgBase
{
public:
    OutputCfg();
    virtual ~OutputCfg() {}
    void readValue(const AbstractButton& button);
protected:
    uint8_t value;
    touchgfx::Callback<OutputCfg, const AbstractButton& > readValueCb;
};

#endif // OUTPUTCFG_HPP
