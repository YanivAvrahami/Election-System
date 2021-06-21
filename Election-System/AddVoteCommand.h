#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class AddVoteCommand : public ICommand
	{
	public:
		AddVoteCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.addVote(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}