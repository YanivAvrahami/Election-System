#pragma once

namespace elec
{
	class ICommand
	{
	public:
		virtual void execute() = 0;
	};
}