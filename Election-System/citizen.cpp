#include "Citizen.h"

#include <iostream>

#include "Counter.h"
#include "State.h"
#include "Party.h"
#include "Election.h"
#include "StateLoader.h"

namespace elec
{
	Citizen::Citizen(std::string name, const int id, const int yearOfBirth, State* state, Election* election)
		: _name(name), _id(id), _yearOfBirth(yearOfBirth), _state(state), _party(nullptr), _voted(false), _election(election) 
	{
		if (id < 100000000 || id > 999999999)
			throw std::invalid_argument("Error: invalid id format");

		int age = _election->getDate().getYear() - yearOfBirth;

		if (age < 18)
			throw std::invalid_argument("Error: unvalid age");
	}

	Citizen::Citizen(std::string name, const int id, const int yearOfBirth, Election* election) 
		: Citizen(name, id, yearOfBirth, nullptr, election) {}

	std::ostream& operator<<(std::ostream& os, const Citizen& other)
	{
		os << "Name: " << other._name << "  ID: " << other._id << "  Year of birth: " << other.getYearOfBirth();
		os << "  State number: " << other._state->getSerial() << std::endl;
		return os;
	}

	void Citizen::vote(int partySerial)
	{
		_state->getVotesCounter().addOne(partySerial);
		_voted = true;
	}

	void Citizen::becomeElector(int partySerial, int stateSerial)
	{
		_election->findState(stateSerial)->addPartyElector(this, partySerial);
		_party = _election->findParty(partySerial);
	}

	void Citizen::save(std::ostream& out) const
	{
		int size = _name.size();
		out.write(rcastccp(&size), sizeof(size));
		out.write(rcastccp(&_name[0]), size);

		out.write(rcastccp(&_id), sizeof(_id));
		out.write(rcastccp(&_yearOfBirth), sizeof(_yearOfBirth));
		out.write(rcastccp(&_voted), sizeof(_voted));

		if(!out.good())
			throw std::exception("Error: bad writing to file");
	}

	void Citizen::load(std::istream& in)
	{
		int size;
		in.read(rcastcp(&size), sizeof(size));
		_name.resize(size);
		in.read(rcastcp(&_name[0]), size);
		
		in.read(rcastcp(&_id), sizeof(_id));
		in.read(rcastcp(&_yearOfBirth), sizeof(_yearOfBirth));
		in.read(rcastcp(&_voted), sizeof(_voted));

		if (!in.good())
			throw std::exception("Error: bad reading to file");
	}

	void Citizen::saveStateSerial(std::ostream& out) const
	{
		int serial;

		if (_state)
			serial = _state->getSerial();
		else
			serial = -1;

		out.write(rcastccp(&serial), sizeof(serial));

		if(!out.good())
			throw std::exception("Error: bad writing to file");
	}

	void Citizen::loadStatePtr(std::istream& in)
	{
		int serial;
		in.read(rcastcp(&serial), sizeof(serial));

		if (serial == -1)
			_state = nullptr;
		else
			_state = _election->findState(serial);

		if (!in.good())
			throw std::exception("Error: bad reading to file");
	}

	void Citizen::savePartySerial(std::ostream& out) const
	{
		int serial;

		if (_party)
			serial = _party->getSerial();
		else
			serial = -1;

		out.write(rcastccp(&serial), sizeof(serial));

		if(!out.good())
			throw std::exception("Error: bad writing to file");
	}

	void Citizen::loadPartyPtr(std::istream& in)
	{
		int serial;
		in.read(rcastcp(&serial), sizeof(serial));

		if (serial == -1)
			_party = nullptr;
		else
			_party = _election->findParty(serial);

		if (!in.good())
			throw std::exception("Error: bad reading to file");
	}

}