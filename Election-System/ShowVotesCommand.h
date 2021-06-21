#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class ShowVotesCommand : public ICommand
	{
	public:
		ShowVotesCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.showVotes(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}