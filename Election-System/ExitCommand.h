#pragma once
#include "ICommand.h"
#include "Application.h"

namespace elec
{
	class Application;

	class ExitCommand : public ICommand
	{
	public:
		ExitCommand(Application& app) : _app(app) {};

	public:
		virtual void execute() override { _app.close(); };

	private:
		Application& _app;
	};
}