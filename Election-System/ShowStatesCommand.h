#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class ShowStatesCommand : public ICommand
	{
	public:
		ShowStatesCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.showStates(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}