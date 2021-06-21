#pragma once
#include "Menu.h"

namespace elec
{
	class MenuFactory
	{
	public:
		MenuFactory(Application& app) : _app(app) {}

	public:
		Menu* createMainMenu();
		Menu* createStandardMenu();
		Menu* createSimpleMenu();

	private:
		Application& _app;
	};
}