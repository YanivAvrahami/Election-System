#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class AddCitizenCommand : public ICommand
	{
	public:
		AddCitizenCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.addCitizen(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}