#pragma once
#include <iostream>
#include "State.h"
#include "Election.h"
#include <string>

namespace elec
{
	class Election;

	class UnifiedState : public State
	{
	public:
		UnifiedState(std::string name, const int amountOfElectors, Election* election);
		UnifiedState(std::istream& in) { load(in); };
		UnifiedState(const UnifiedState& other) = delete;
		void print(std::ostream& os) const override;

	public:
		void save(std::ostream& out) const;
		void load(std::istream& in);
	};
}