#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class ElectionUIHandler;

	class ElectCitizenCommand : public ICommand
	{
	public:
		ElectCitizenCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.electCitizen(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}