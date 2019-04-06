#include <gui/patchconfig_screen/PatchConfigView.hpp>
#include <gui/patchconfig_screen/PatchConfigPresenter.hpp>

PatchConfigPresenter::PatchConfigPresenter(PatchConfigView& v)
    : view(v)
{
}

void PatchConfigPresenter::activate()
{

}

void PatchConfigPresenter::deactivate()
{

}

void PatchConfigPresenter::prevButtonPressed()
{
    model->requestProgramNrDecrement();
}

void PatchConfigPresenter::nextButtonPressed()
{
    model->requestProgramNrIncrement();
}

void PatchConfigPresenter::patchConfigChanged()
{
    patchCfgMsg newPatchConfig = model->getPatchCfgData();
    view.setProgramNumber(newPatchConfig.programNr);
    view.setController1Number(newPatchConfig.switch1Name);
    view.setController1Value(newPatchConfig.switch1Value);
    view.setController2Number(newPatchConfig.switch2Name);
    view.setController2Value(newPatchConfig.switch2Value);
    view.setDefaultOutputCfg(newPatchConfig.defaultOut);
}

void PatchConfigPresenter::defaultOutputChanged(std::uint8_t newVal)
{
    model->requestDefaultOutputChange(newVal);
}

void PatchConfigPresenter::saveButtonPressed()
{
    model->requestGeneralSave();
}
