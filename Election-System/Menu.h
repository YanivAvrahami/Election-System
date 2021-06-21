#pragma once
#include <string>
#include <vector>
#include "Button.h"

namespace elec
{
	class Application;

	class Menu
	{
	public:
		Menu(std::string title) : _title(title) {}
		Menu() : Menu("") {};
		Menu(const Menu& other) = delete;

	public:
		Menu& operator=(const Menu& other) = delete;

	public:
		void draw() const;
		void addButton(ICommand* command, const std::string label, const std::string activationString);
		void setTitle(const std::string title);
		Button& getButton(const std::string activationString);

	protected:
		std::string _title;
		std::vector<Button> _buttons;
		friend class Application;
	};
}