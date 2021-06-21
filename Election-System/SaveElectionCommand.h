#pragma once
#include "ICommand.h"
#include "Application.h"

namespace elec
{
	class Application;

	class SaveElectionCommand : public ICommand
	{
	public:
		SaveElectionCommand(Application& app) : _app(app) {};

	public:
		virtual void execute() override { _app.save(); };

	private:
		Application& _app;
	};
}