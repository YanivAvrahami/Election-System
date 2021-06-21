#pragma once
#include "Party.h"

namespace elec
{
	class ComparePartiesByNumOfElectors
	{
	public:
		int operator()(const Party* p1, const Party* p2) const
		{
			return p1->getOverallNumOfElectors() > p2->getOverallNumOfElectors();
		}
	};
}