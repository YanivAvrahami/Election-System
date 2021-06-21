#include "ElectionLoader.h"
#include "StandardElection.h"
#include "SimpleElection.h"

namespace elec
{
	void ElectionLoader::save(Election* election, std::ostream& out)
	{
		int type;
		if (typeid(*election) == typeid(StandardElection))
		{
			type = static_cast<int>(ElectionType::STANDARD);
			out.write(rcastccp(&type), sizeof(type));
		}
		else if (typeid(*election) == typeid(SimpleElection))
		{
			type = static_cast<int>(ElectionType::SIMPLE);
			out.write(rcastccp(&type), sizeof(type));
		}

		try
		{
			election->save(out);
		}
		catch (std::exception& err)
		{
			throw;
		}

		if (!out.good())
			throw std::exception("Error: bad reading");
	}

	Election* ElectionLoader::load(std::istream& in)
	{
		int type;
		in.read(rcastcp(&type), sizeof(type));

		if (!in.good())
			return nullptr;

		ElectionType electionType = static_cast<ElectionType>(type);

		try
		{
			switch (electionType)
			{
			case ElectionType::STANDARD:
				return new StandardElection(in);
				break;

			case ElectionType::SIMPLE:
				return new SimpleElection(in);
				break;
			}
		}
		catch (std::exception* err)
		{
			throw;
		}
	}
}