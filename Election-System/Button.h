#pragma once
#include "ICommand.h"
#include <string>

namespace elec
{
	class Button
	{
	public:
		Button();
		Button(ICommand* command, const std::string label, const std::string activationString);

	public:
		void click();

	public:
		const std::string& getLabel() const { return _label; };
		const std::string& getActivationString() const { return _activationString; };

	private:
		ICommand* _command;
		std::string _label;
		std::string _activationString;
	};
}