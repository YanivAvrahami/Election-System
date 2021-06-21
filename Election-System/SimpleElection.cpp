#include "SimpleElection.h"
#include "State.h"
#include "DividedState.h"

namespace elec
{
	SimpleElection::SimpleElection(Date date, int numOfElectors) : Election(date), _numOfElectors(numOfElectors)
	{
		try
		{
			addState(new DividedState("", numOfElectors, this));
		}
		catch(std::bad_alloc& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
			exit(-1);
		}
	}

	void SimpleElection::save(std::ostream& out) const
	{
		try
		{
			Election::save(out);
		}
		catch(std::exception& err)
		{
			throw;
		}
	}

	void SimpleElection::load(std::istream& in)
	{
		try
		{
			Election::load(in);
		}
		catch (std::exception& err)
		{
			throw;
		}
	}
}