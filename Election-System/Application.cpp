#include "Application.h"
#include "Menu.h"
#include "Election.h"
#include "StandardElection.h"
#include "SimpleElection.h"
#include "ElectionLoader.h"
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include "Button.h"
#include <exception>

namespace elec
{
	Application::Application() 
		: _menuFactory(*this), _running(true)
	{
		setCurrentMenu(_menuFactory.createMainMenu());
	};

 	void Application::run()
	{
		while (_running)
		{
			_currentMenu->draw();
			std::string choice = getChoice();
			_currentMenu->draw();

			try
			{
				Button& button = _currentMenu->getButton(choice);
				button.click();
			}
			catch (std::exception& err)
			{
				std::cout << err.what() << std::endl;
				pause();
			}
		}
	}

	void Application::close()
	{
		_running = false;
		delete _currentElection;
	}

	void Application::pause() const
{
		std::cout << "\nPress 'enter' to continue\n";
		std::string temp;
		std::getline(std::cin, temp);
	}

	const std::string Application::getChoice() const
	{
		std::string choice;
		std::getline(std::cin, choice);
		return choice;
	}

	void Application::setCurrentMenu(Menu* menu)
	{
		delete _currentMenu;
		_currentMenu = menu;
	}

	void Application::setCurrentElection(Election* election)
	{
		delete _currentElection;

		_currentElection = election;

		if (typeid(*election) == typeid(StandardElection))
		{
			setCurrentMenu(_menuFactory.createStandardMenu());
		}
		else if (typeid(*election) == typeid(SimpleElection))
		{
			setCurrentMenu(_menuFactory.createSimpleMenu());
		}
	}

	void Application::createElection()
	{
		std::cout << "-----Create new election-----\n";

		Date date;

		try
		{
			int day, month, year;
			std::cout << "Election date (d m y): ";

			std::cin >> day >> month >> year;
			std::cin.ignore();

			date.setDay(day);
			date.setMonth(month);
			date.setYear(year);
		}
		catch(std::invalid_argument& err)
		{
			std::cout << err.what() << std::endl;
			pause();
			return;
		}

		int type;
		std::cout << "Election type (1-standard or 2-simple): ";
		std::cin >> type;
		std::cin.ignore();

		if (type == 1)
		{
			try
			{
				setCurrentElection(new StandardElection(date));
			}
			catch (std::bad_alloc& err)
			{
				std::cout << "Error: " << err.what() << std::endl;
				exit(-1);
			}
			setCurrentMenu(_menuFactory.createStandardMenu());
		}
		else if (type == 2)
		{
			int numOfElectors;
			std::cout << "Number of electors: ";
			std::cin >> numOfElectors;
			std::cin.ignore();
			try
			{
				setCurrentElection(new SimpleElection(date, numOfElectors));
			}
			catch (std::bad_alloc& err)
			{
				std::cout << "Error: " << err.what() << std::endl;
				exit(-1);
			}
			setCurrentMenu(_menuFactory.createSimpleMenu());
		}
	}

	void Application::save() const
	{
		std::cout << "------Save------\n";
		std::cout << "File name: ";
		std::string fileName;
		std::getline(std::cin, fileName);

		std::ofstream outfile(fileName, std::ios::binary | std::ios::trunc);

		if (!outfile)
			throw std::exception("Error: could not open file");

		try
		{
			ElectionLoader::save(_currentElection, outfile);
		}
		catch (std::exception& err)
		{
			throw;
		}

		outfile.close();
	}

	void Application::load()
	{
		std::cout << "------Load------\n";
		std::cout << "File name: ";
		std::string fileName;
		std::getline(std::cin, fileName);

		std::ifstream infile(fileName, std::ios::binary);

		if (!infile)
		{
			std::cout << "Error: could not open file\n";
			pause();
			return;
		}

		Election* temp;

		try
		{
			temp = ElectionLoader::load(infile);
		}
		catch (std::exception& err)
		{
			throw;
		}

		setCurrentElection(temp);

		infile.close();
	}
}