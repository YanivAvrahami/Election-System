#pragma once
#include "ICommand.h"
#include "Application.h"

namespace elec
{
	class Application;

	class LoadElectionCommand : public ICommand
	{
	public:
		LoadElectionCommand(Application& app) : _app(app) {};

	public:
		virtual void execute() override { _app.load(); };

	private:
		Application& _app;
	};
}