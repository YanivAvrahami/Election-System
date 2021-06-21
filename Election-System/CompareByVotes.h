#pragma once
#include "Party.h"

namespace elec
{
	class CompareByVotes
	{
	public:
		int operator()(const Party* p1, const Party* p2) const
		{
			return p1->getTotalVotes() > p2->getTotalVotes();
		}
	};
}