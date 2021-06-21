#include "DividedState.h"
#include <iostream>
#include <fstream>
#include "Election.h"

namespace elec
{
	void DividedState::save(std::ostream& out) const
	{
		try
		{
			State::save(out);
		}
		catch (std::exception& err)
		{
			throw;
		}
	}

	void DividedState::load(std::istream& in)
	{
		try
		{
			State::load(in);
		}
		catch (std::exception& err)
		{
			throw;
		}
	}

	void DividedState::print(std::ostream& os) const
	{
		os << "Serial: " << _serial << "  Name: " << _name << "  Number of representatives: " << _numOfElectors << "  Type: Divided\n";
	}
}