#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class ShowCitizensCommand : public ICommand
	{
	public:
		ShowCitizensCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.showCitizens(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}