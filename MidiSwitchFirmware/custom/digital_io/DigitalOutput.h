/*
 * DigitalOutput.h
 *
 * Created: 8/25/2018 3:57:32 PM
 *  Author: Erwin
 */

#ifndef DIGITAL_OUTPUT
#define DIGITAL_OUTPUT


#include "stm32f4xx.h"
#include "I_DigitalOutput.h"


class DigitalOutput : public I_DigitalOutput{

  public:
    // Constructor
    DigitalOutput( GPIO_TypeDef* port, uint32_t pin, bool invert = false, bool initState = false);

    // Destructor
    ~DigitalOutput();

    // State functions
    void set();
    void set(bool state);
    void clear();
    void toggle();
    bool read();

    // Inversion functions
    void setInversion(bool invert);
    bool getInversion();

  private:
    GPIO_TypeDef* _port;
    uint32_t _pin;
    bool _inv;
};

#endif
