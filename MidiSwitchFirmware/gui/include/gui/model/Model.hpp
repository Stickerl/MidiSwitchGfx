#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
#include "I_config_manager.hpp"
#include "gui_queue.h"
#include "global_defines.hpp"
#include "guiMessageDefinitions.hpp"

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

    patchCfgMsg getPatchCfgData();

    globalCfgMsg getGlobalCfgData();

    /*****************************************************************
     * respond = application updates Gui
     * request = Gui requests new data from the application
     *****************************************************************/
    void requestProgramNrDecrement();

    void requestProgramNrIncrement();

    void requestOutputChange(std::uint8_t rowNr, std::uint8_t newVal);

    void requestGeneralSave();

    void requestProgNrChange(std::uint8_t newVal);

    void requestSwitchNrChange(std::uint8_t switchIndex, std::uint8_t switchNr);

    void requestSwitchValChange(std::uint8_t switchNr, std::uint8_t newVal);

    void requestMidiChannelChange(std::uint8_t newMidiChannel);

    void requestBankNrChange(std::uint16_t newBankNr);

    void requestInitialPatchChange(std::uint8_t newInitalPatchNr);

protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;
    globalCfgMsg globalCfgData;
    patchCfgMsg patchCfgData;
    GuiQueue& _queToMidi;
    GuiQueue& _queToGui;

};

#endif /* MODEL_HPP */
