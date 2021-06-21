#include "StateLoader.h"
#include "state.h"
#include <iostream>
#include <fstream>
#include "UnifiedState.h"
#include "DividedState.h"
#include <typeinfo>
#include "Election.h"

namespace elec
{
	void StateLoader::save(State* state, std::ostream& out)
	{
		int type;

		if (typeid(*state) == typeid(UnifiedState))
		{
			type = static_cast<int>(StateType::UNIFIED);
			out.write(rcastccp(&type), sizeof(type));
		}
		else if (typeid(*state) == typeid(DividedState))
		{
			type = static_cast<int>(StateType::DIVIDED);
			out.write(rcastccp(&type), sizeof(type));
		}

		try
		{
			state->save(out);
		}
		catch (std::exception& err)
		{
			throw;
		}

		if (!out.good())
		{
			throw std::exception("Error: bad writing");
		}
	}

	State* StateLoader::load(std::istream& in)
	{
		int type;

		in.read(rcastcp(&type), sizeof(type));

		StateType stateType = static_cast<StateType>(type);

		try
		{
			switch (stateType)
			{
			case StateType::UNIFIED:
				return new UnifiedState(in);
				break;

			case StateType::DIVIDED:
				return new DividedState(in);
				break;
			}
		}
		catch (std::exception& err)
		{
			throw;
		}

		if (!in.good())
			throw std::exception("Error: bad reading");
	}
}