#pragma once
#include "state.h"
#include <iostream>
#include <fstream>
#include "Election.h"

namespace elec
{
	enum class StateType
	{
		UNIFIED,
		DIVIDED
	};

	class StateLoader
	{
		public:
			static void save(State* state, std::ostream& out);
			static State* load(std::istream& in);
	};
}