#include "Button.h"

namespace elec
{
	Button::Button() 
		: _command(nullptr), _label(""), _activationString("") {};

	Button::Button(ICommand* command, const std::string label, std::string activationString)
		: _command(command), _label(label), _activationString(activationString) {};

	void Button::click()
	{
		_command->execute();
	}
}
