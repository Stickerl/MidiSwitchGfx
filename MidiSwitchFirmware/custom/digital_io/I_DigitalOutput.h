/*
 * I_DigitalOutput.h
 *
 * Created: 8/25/2018 3:57:32 PM
 *  Author: Erwin
 */

#if !defined(I_DIGITAL_OUTPUT)
#define I_DIGITAL_OUTPUT



class I_DigitalOutput
{

public:
	I_DigitalOutput() {

	}

	virtual ~I_DigitalOutput() {

	}

    virtual void set() = 0;
    virtual void set(bool state) = 0;
    virtual void clear() = 0;
    virtual void toggle() = 0;
    virtual bool read() = 0;

};
#endif // !defined(I_DIGITAL_OUTPUT)
