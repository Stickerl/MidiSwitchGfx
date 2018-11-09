#ifndef MODEL_HPP
#define MODEL_HPP

#include "stdint.h"
#include "I_config_manager.hpp"
#include "gui_queue.h"
#include "global_defines.hpp"

class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */
class Model
{
public:

	typedef struct
	{
	    uint8_t     chanalNr;
	    uint16_t    bankSelect;
	    uint8_t     controllerNr;
	    uint8_t     controllerVal;
	    uint8_t     programNr;          // equals patch number
	}midi_data;


    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    /**
     * This function will be called automatically every frame. Can be used to e.g. sample hardware
     * peripherals or read events from the surrounding system and inject events to the GUI through
     * the ModelListener interface.
     */
    void tick();

    uint8_t getControllerNumber();

    uint16_t getConfigNumber();

    uint8_t getControllerValue();

    uint8_t getProgramNumber();

    /*****************************************************************
     * respond = application updates Gui
     * request = Gui requests new data from the application
     *****************************************************************/

    void respondMidiState(I_ConfigManager::programConfig_t& newConfig);

    void requestProgramNrDecrement();

    void requestProgramNrIncrement();

protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;

    I_ConfigManager::programConfig_t displayedCfg;

    midi_data midiData;
    uint8_t configNr;
    GuiQueue& _queToMidi;
    GuiQueue& _queToGui;

};

#endif /* MODEL_HPP */
