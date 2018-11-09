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

void PatchConfigPresenter::controllerNumberChanged()
{
	view.setControllerNumber(model->getControllerNumber());
}

void PatchConfigPresenter::controllerValueChanged()
{
	view.setControllerValue(model->getControllerValue());
}

void PatchConfigPresenter::programNumberChanged()
{
	view.setProgramNumber(model->getProgramNumber());
}

void PatchConfigPresenter::prevButtonPressed()
{
    model->requestProgramNrDecrement();
}

void PatchConfigPresenter::nextButtonPressed()
{
    model->requestProgramNrIncrement();
}


