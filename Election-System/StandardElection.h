#pragma once
#include "Date.h"
#include "Election.h"
#include "Serializable.h"

namespace elec
{
	class StandardElection : public Election

	{
	public:
		StandardElection(Date date) : Election(date) {};
		StandardElection(std::istream& in) { load(in); }

	public:
		// Inherited via ISerializable
		void save(std::ostream& out) const;
		// Inherited via ISerializable
		void load(std::istream& in);
	};
}