#pragma once
#include "Menu.h"
#include <iostream>
#include "Button.h"

namespace elec
{
	void Menu::draw() const
	{
		system("cls");

		std::cout << _title;

		for (int i = 0; i < _buttons.size(); ++i)
		{
			std::cout << _buttons[i].getActivationString() << ". " << _buttons[i].getLabel() << std::endl;
		}

		std::cout << std::endl;
	}

	void Menu::addButton(ICommand* command, const std::string label, const std::string activationString)
	{
		_buttons.push_back(Button(command, label, activationString));
	}

	void Menu::setTitle(const std::string title)
	{
		_title = title;
	}

	Button& Menu::getButton(const std::string activationString)
	{
		for (int i = 0; i < _buttons.size(); ++i)
			if (_buttons[i].getActivationString() == activationString)
				return _buttons[i];
		
		throw std::exception("Error: button doesn't exist");
	}
}