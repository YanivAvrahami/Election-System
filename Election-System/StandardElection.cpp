#include "StandardElection.h"
#include "ElectionLoader.h"

namespace elec
{
	void StandardElection::save(std::ostream& out) const
	{
		try
		{
			Election::save(out);
		}
		catch (std::exception& err)
		{
			throw;
		}
	}

    void StandardElection::load(std::istream& in)
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