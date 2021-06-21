#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class ShowResultsCommand : public ICommand
	{
	public:
		ShowResultsCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.showResults(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}