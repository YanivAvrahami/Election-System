#pragma once
#include "Date.h"
#include "Election.h"
#include "Serializable.h"
#include <iostream>
#include <fstream>

namespace elec
{
	class SimpleElection : public Election
	{
	public:
		SimpleElection(Date date, int numOfElectors);
		SimpleElection(std::istream& in) { load(in); };

	public:
		// Inherited via ISerializable
		void save(std::ostream& out) const;
		// Inherited via ISerializable
		void load(std::istream& in);

	private:
		int _numOfElectors;
	};
}
