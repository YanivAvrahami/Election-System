#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class AddPartyCommand : public ICommand
	{
	public:
		AddPartyCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.addParty(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}