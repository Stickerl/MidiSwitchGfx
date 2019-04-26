#include <gui/globalconfig_screen/GlobalConfigView.hpp>
#include <gui/globalconfig_screen/GlobalConfigPresenter.hpp>

GlobalConfigPresenter::GlobalConfigPresenter(GlobalConfigView& v)
    : view(v)
{
}

void GlobalConfigPresenter::activate()
{
    restoreGlobalConfig();
}

void GlobalConfigPresenter::deactivate()
{

}

void GlobalConfigPresenter::restoreGlobalConfig()
{
	globalCfgMsg globalCfg = model->getGlobalCfgData();
	view.setMidiChanal(globalCfg.midiChanel);
	view.setBankNr(globalCfg.bankNr);
	view.setInitialPatch(globalCfg.initialPatch);
}

void GlobalConfigPresenter::midiChannelChanged(std::uint8_t newValue)
{
	model->requestMidiChannelChange(newValue);
}

void GlobalConfigPresenter::bankNrChanged(std::uint16_t newValue)
{
	model->requestBankNrChange(newValue);
}

void GlobalConfigPresenter::initalPatchChanged(std::uint8_t newValue)
{
    model->requestInitialPatchChange(newValue);
}

void GlobalConfigPresenter::globalConfigChanged()
{
    restoreGlobalConfig();
};
