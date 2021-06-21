#include "Party.h"

#include <iostream>
#include "Election.h"
#include "State.h"
#include "Counter.h"
#include "Citizen.h"
#include <string>
#include "UnifiedState.h"
#include "DividedState.h"

namespace elec
{
	int Party::_instances = 0;

	Party::Party(std::string name, Citizen* presidentialCandidate, Election* election)
		: _name(name), _presidentialCandidate(presidentialCandidate), _serial(_instances++), _election(election) {}

	std::ostream& operator<<(std::ostream& os, Party& other)
	{
		os << "Serial: " << other.getSerial() << "  Name: " << other._name << "  Presidential candidate ID: " << other.getPresidentialCandidate()->getID();
		os << "\n\nElectors:\n";
		other.printElectors();
		return os;
	}

	int Party::getTotalVotes() const
	{
		int count = 0;
		for (int i = 0; i < _election->getStates().size(); ++i)
		{
			State* cur = _election->findState(i);
			count += cur->getVotesCounter().get(_serial);
		}
		return count;
	}

	void Party::printElectors()
	{
		/*for (int i = 0; i < _election->getStates().size(); ++i)
		{
			std::vector<Citizen*> electors = _election->getStates()[i]->getElectorsByParty()[_serial];
			
			for (int j = 0; j < electors.size(); ++j)
				std::cout << *electors[j];
		}
		std::cout << std::endl;*/

		for (State* state : _election->getStates())
		{
			for (Citizen* elector : state->getElectorsByParty()[_serial])
			{
				std::cout << *elector;
			}
		}

		std::cout << '\n';
	}

	void Party::save(std::ostream& out) const
	{
		int size = _name.size();
		out.write(rcastccp(&size), sizeof(size));
		out.write(rcastccp(&_name[0]), size);

		out.write(rcastccp(&_instances), sizeof(_instances));
		out.write(rcastccp(&_serial), sizeof(_serial));

		if (!out.good())
			throw std::exception("Error: bad writing");
	}

	void Party::load(std::istream& in)
	{
		int size;
		in.read(rcastcp(&size), sizeof(size));
		_name.resize(size);
		in.read(rcastcp(&_name[0]), size);

		in.read(rcastcp(&_instances), sizeof(_instances));
		in.read(rcastcp(&_serial), sizeof(_serial));

		if (!in.good())
			throw std::exception("Error: bad reading");
	}

	void Party::savePresidentialCandidateID(std::ostream& out) const
	{
		int id;

		if (_presidentialCandidate)
			id = _presidentialCandidate->getID();
		else
			id = -1;

		out.write(rcastccp(&id), sizeof(id));
		
		if (!out.good())
			throw std::exception("Error: bad writing");
	}

	void Party::loadPresidentialCandidatePtr(std::istream& in)
	{
		int id;
		in.read(rcastcp(&id), sizeof(id));

		try
		{
			if (id == -1)
				_presidentialCandidate = nullptr;
			else
				_presidentialCandidate = _election->findCitizen(id);
		}
		catch (std::exception& err)
		{
			throw;
		}

		if (!in.good())
			throw std::exception("Error: bad reading");
	}

	int Party::getOverallNumOfElectors() const
	{
		int count = 0;

		for (auto elem : _election->getStates())
		{
			if (typeid(*elem) == typeid(UnifiedState))
			{
				if (elem->getLocalWinningParty().getSerial() == _serial)
				{
					count += elem->getMaxNumOfElectors();
				}
			}
			else if (typeid(*elem) == typeid(DividedState))
			{
				count += elem->getNumOfElectorsToGrantParty(_serial);
			}
		}

		return count;
	}

}