#pragma once
#include "State.h"
#include <iostream>
#include "Election.h"
#include <string>

namespace elec
{
	class Election;

	class DividedState : public State
	{
	public:
		DividedState(std::string name, const int amountOfElectors, Election* election)
			: State(name, amountOfElectors, election) {}
		DividedState(std::istream& in) { load(in); };
		DividedState(const DividedState& other) = delete;
		virtual void print(std::ostream& os) const override;

	public:
		void save(std::ostream& out) const;
		void load(std::istream& in);
	};
}