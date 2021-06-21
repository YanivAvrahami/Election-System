#pragma once
#include "Election.h"

namespace elec
{
	enum class ElectionType
	{
		STANDARD,
		SIMPLE
	};

	class ElectionLoader
	{
	public:
		static void save(Election* election, std::ostream& out);
		static Election* load(std::istream& in);
	};
}