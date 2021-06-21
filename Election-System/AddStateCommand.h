#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class AddStateCommand : public ICommand
	{
	public:
		AddStateCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.addState(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}