#include "UnifiedState.h"
#include <iostream>
#include <fstream>
#include "Election.h"

namespace elec
{
	UnifiedState::UnifiedState(std::string name, const int amountOfElectors, Election* election) 
        : State(name, amountOfElectors, election)
	{
	}

	void UnifiedState::save(std::ostream& out) const
    {
        try
        {
            State::save(out);
        }
        catch(std::exception& err)
        {
            throw;
        }
    }

    void UnifiedState::load(std::istream& in)
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

	void UnifiedState::print(std::ostream& os) const
	{
		os << "Serial: " << _serial << "  Name: " << _name << "  Number of representatives: " << _numOfElectors << "  Type: Unified\n";
	}
}