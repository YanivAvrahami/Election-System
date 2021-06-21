#pragma once
#include "ICommand.h"
#include "Application.h"

namespace elec
{
	class Application;

	class CreateElectionCommand : public ICommand
	{
	public:
		CreateElectionCommand(Application& app) : _app(app) {};

	public:
		virtual void execute() override { _app.createElection(); };

	private:
		Application& _app;
	};
}