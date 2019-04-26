#include <gui/patchconfig_screen/PatchConfigView.hpp>
#include <gui/patchconfig_screen/PatchConfigPresenter.hpp>

PatchConfigPresenter::PatchConfigPresenter(PatchConfigView& v)
    : view(v)
{
}

void PatchConfigPresenter::activate()
{
    restorePatchConfig();
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
    view.setDefaultOutputCfg(newPatchConfig.defaultOut);
    view.setController1Number(newPatchConfig.switch1Name);
    view.setController1Value(newPatchConfig.switch1Value);
    view.setSwitch1OutputCfg(newPatchConfig.switch1Output);
    view.setController2Number(newPatchConfig.switch2Name);
    view.setController2Value(newPatchConfig.switch2Value);
    view.setSwitch2OutputCfg(newPatchConfig.switch2Output);
}

void PatchConfigPresenter::restorePatchConfig()
{
    patchConfigChanged();
}

void PatchConfigPresenter::outputChanged(std::uint8_t rowNr, std::uint8_t newVal)
{
    model->requestOutputChange(rowNr, newVal);
}

void PatchConfigPresenter::progNrChanged(std::uint8_t newVal)
{
    model->requestProgNrChange(newVal);
}

void PatchConfigPresenter::switchNrChanged(std::uint8_t switchIndex, std::uint8_t switchNr)
{
    model->requestSwitchNrChange(switchIndex, switchNr);
}

void PatchConfigPresenter::switchValChanged(std::uint8_t switchIndex, std::uint8_t newVal)
{
    model->requestSwitchValChange(switchIndex, newVal);
}

void PatchConfigPresenter::saveButtonPressed()
{
    model->requestGeneralSave();
}
