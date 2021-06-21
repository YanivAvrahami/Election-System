#pragma once
#include "ICommand.h"
#include "ElectionUIHandler.h"

namespace elec
{
	class AddStuffCommand : public ICommand
	{
	public:
		AddStuffCommand(const ElectionUIHandler& electionUIHandler) : _electionUIHandler(electionUIHandler) {};

	public:
		virtual void execute() override { _electionUIHandler.addStuff(); };

	private:
		const ElectionUIHandler& _electionUIHandler;
	};
}