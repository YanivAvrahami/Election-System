#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class ShowPartiesCommand : public ICommand
	{
	public:
		ShowPartiesCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.showParties(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}