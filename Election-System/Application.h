#pragma once
#include "MenuFactory.h"
#include <memory>

namespace elec
{
	class Menu;
	class Election;

	class Application
	{
	public:
		Application();

	public:
		//starts the application
		void run();
		//terminates the application
		void close();
		//pause the application until pressing 'enter'
		void pause() const;
		//returns current election
		Election* getCurrentElection() { return _currentElection; };
		//get choice
		const std::string getChoice() const;
		//sets menu to run
		void setCurrentMenu(Menu* menu);
		//sets election to run
		void setCurrentElection(Election* election);
		//creates a dialog with user to create new election
		void createElection();
		//saves application data
		void save() const;
		//loads application data
		void load();

	private:
		bool _running;
		Election* _currentElection;
		Menu* _currentMenu;
		MenuFactory _menuFactory;
	};
}